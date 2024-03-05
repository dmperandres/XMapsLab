/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "filter_wcvd.h"
#include "glwidget.h"

using namespace _f_wcvd_ns;

/*************************************************************************/

_filter_wcvd::_filter_wcvd()
{
  Percent_of_dots=WCVD_PERCENT_OF_DOTS_DEFAULT;
  Number_of_dark_dots=int(WCVD_NUMBER_OF_DARK_DOTS_DEFAULT);
  Number_of_dots=int(float(Number_of_dark_dots)*_f_wcvd_ns::DOTS_FACTOR);
  Number_of_good_dots=int(WCVD_NUMBER_OF_DOTS_DEFAULT);
  Selector_type=SELECTOR_TYPE_PERCENTAGE;

  Local_change=false;
  Moved_points=1e8;

  Num_channels_output_image_0=1;

  Type_filter=_f_filter_ns::FILTER_WCVD;

  Type_input_images[0]=_f_filter_ns::TYPE_UI_8;
  Type_output_0=_f_filter_ns::TYPE_UI_8;

  Scaling_factor=1;
  Change_output_image_size=false;
  Use_dots=false;
  Dark_points_counted=false;

  Save_intermediate_images=false;

  Percent_fixed_centroidals=WCVD_PERCENT_FIXED_CENTROIDALS;
  Number_of_iteractions=WCVD_NUM_ITERACTIONS_DEFAULT;

  C1.init(0,1);
  C1.set_seed(1000);

  // GPU
  // load shaders and create buffers

  _shaders Shader;

  /**********************************************************/
   // load the programs
   // Program for drawing the cones
   Program1=Shader.load_shaders("shaders/draw_cones_new1.vert","shaders/draw_cones_new1.frag");
   if (Program1==0){
     cout << "Error with program" << endl;
     exit(-1);
   }

   // program for computing the new centroids
   Program2=Shader.load_shaders("shaders/counter_colors_new1.vert","shaders/counter_colors_new1.frag");
   if (Program2==0){
     cout << "Error with program" << endl;
     exit(-1);
   }

   // program for checking if there is change in the positions of the centroids
   Program3=Shader.load_shaders("shaders/check_movement_new1.vert","shaders/check_movement_new1.frag");
   if (Program3==0){
     cout << "Error with program" << endl;
     exit(-1);
   }

   // program to do the prefix sum of the centroids that are moved
   Program4=Shader.load_shaders("shaders/prefix_sum_new1.vert","shaders/prefix_sum_new1.frag");
   if (Program4==0){
     cout << "Error with program" << endl;
     exit(-1);
   }
}

/*************************************************************************/

void _filter_wcvd::reset_data()
{
  Percent_of_dots=WCVD_PERCENT_OF_DOTS_DEFAULT;
  Number_of_dark_dots=int(WCVD_NUMBER_OF_DARK_DOTS_DEFAULT);
  Number_of_dots=int(float(Number_of_dark_dots)*_f_wcvd_ns::DOTS_FACTOR);
  Number_of_good_dots=int(WCVD_NUMBER_OF_DOTS_DEFAULT);
  Selector_type=SELECTOR_TYPE_PERCENTAGE;

  Percent_fixed_centroidals=WCVD_PERCENT_FIXED_CENTROIDALS;
  Number_of_iteractions=WCVD_NUM_ITERACTIONS_DEFAULT;

  C1.init(0,1);
  C1.set_seed(1000);
}

/*************************************************************************/

void _filter_wcvd::hsv_to_rbg(float h,float s, float v,unsigned char &r,unsigned char &g,unsigned char &b)
{
  int h_i;
  float f,p,q,t;

  h_i =int(h*6);
  f = h*6 - h_i;
  p = v * (1 - s);
  q = v * (1 - f*s);
  t = v * (1 - (1 - f) * s);
  switch(h_i){
  case 0:
    r=static_cast<unsigned char>(v*256);
    g=static_cast<unsigned char>(t*256);
    b=static_cast<unsigned char>(p*256);
    break;
  case 1:
    r=static_cast<unsigned char>(q*256);
    g=static_cast<unsigned char>(v*256);
    b=static_cast<unsigned char>(p*256);
    break;
  case 2:
    r=static_cast<unsigned char>(p*256);
    g=static_cast<unsigned char>(v*256);
    b=static_cast<unsigned char>(t*256);
    break;
  case 3:
    r=static_cast<unsigned char>(p*256);
    g=static_cast<unsigned char>(q*256);
    b=static_cast<unsigned char>(v*256);
    break;
  case 4:
    r=static_cast<unsigned char>(t*256);
    g=static_cast<unsigned char>(p*256);
    b=static_cast<unsigned char>(v*256);
    break;
  case 5:
    r=static_cast<unsigned char>(v*256);
    g=static_cast<unsigned char>(p*256);
    b=static_cast<unsigned char>(q*256);
    break;
  }
}

/*************************************************************************/
// compute the number of dots

void _filter_wcvd::percent_of_dots(int Percent_of_dots1)
{
  if (Percent_of_dots1<1) Percent_of_dots1=1;

  Percent_of_dots=Percent_of_dots1;
  // apply the percentage
  Number_of_good_dots=Number_of_dots*Percent_of_dots/100;
}

/*************************************************************************/
// compute the number of dots

void _filter_wcvd::number_of_dots(int Number_of_dots1)
{
  if (Number_of_dots1<1) Number_of_dots1=1;
  if (Number_of_dots1>Number_of_dots) Number_of_dots1=Number_of_dots;

  Percent_of_dots=static_cast<int>((float(Number_of_dots1)/float(Number_of_dots))*100.0f);

  Number_of_good_dots=Number_of_dots1;
}

/*************************************************************************/
// Draw the points depending the size on the tone of the image

void _filter_wcvd::draw_points(cv::Mat *Output_image)
{
  for (uint i=0;i<Points.size();i++){
    if (Points[i].x<0 ||Points[i].x>Window_width || Points[i].y<0 ||Points[i].y>Window_height){
    }
    else Output_image->at<unsigned char>(Points[i].y,Points[i].x)=0;
  }
}

/*************************************************************************/
// count number of dark pixels

void _filter_wcvd::count_dark_pixels(cv::Mat *Input_image)
{
  int Count=0;

  // count the number of dark pixels
  for (int Row=0;Row<Window_height;Row++){
    for (int Col=0;Col<Window_width;Col++){
      if (Input_image->at<unsigned char>(Row,Col)<255) Count++;
    }
  }

  // max number of WCVD dots
  Number_of_dark_dots=Count;
  // apply the percentage of dots to not fill the full image
  Number_of_dots=static_cast<int>(float(Number_of_dark_dots)*_f_wcvd_ns::DOTS_FACTOR);

  if(Selector_type==SELECTOR_TYPE_PERCENTAGE){
    Number_of_good_dots=static_cast<int>(float(Number_of_dots)*float(Percent_of_dots)/100.0f);
  }
  else{
    if (Number_of_good_dots>Number_of_dots) Number_of_good_dots=Number_of_dots;
    if (Number_of_good_dots==0)  Number_of_good_dots=1;

    Percent_of_dots=static_cast<int>((float(Number_of_good_dots)/float(Number_of_dots))*100.0f);
  }
}

/*************************************************************************/
// create the random points

void _filter_wcvd::create_random_points(cv::Mat *Input_image)
{
  _vertex3ui Vertex_aux(0,0,1);
  _random_uniform_int Position_x(2,Window_width-2);
  _random_uniform_int Position_y(2,Window_height-2);
  unsigned int Count, Count_errors=0;
  cv::Mat Selected_positions;

  // this image allows to remove duplicates
  Selected_positions.create(Window_height,Window_width,CV_8U);
  Selected_positions.setTo(255);

  Position_x.set_seed(1000);

  #ifdef DEBUG
  cout << "create_random_points Number of dots " << Number_of_good_dots << endl;
  #endif

  Count=0;
  Position_y.set_seed(5000);

  Offsets.resize(Number_of_good_dots);

  while (Count<Number_of_good_dots){
    Vertex_aux.x=roundf(Position_x.value());
    Vertex_aux.y=roundf(Position_y.value());
    Count_errors++;
    // controls that no point of a white zone is selected (probably it will produce a weight=0)
    if (Input_image->at<unsigned char>(Vertex_aux.y,Vertex_aux.x)<250 && Selected_positions.at<unsigned char>(Vertex_aux.y,Vertex_aux.x)==255){
      Offsets[Count]=Vertex_aux;
      Count++;
      // this postions has been selected
      Selected_positions.at<unsigned char>(Vertex_aux.y,Vertex_aux.x)=0;
      // plus the 8 neighbors
      Selected_positions.at<unsigned char>(Vertex_aux.y,Vertex_aux.x+1)=0;
      Selected_positions.at<unsigned char>(Vertex_aux.y+1,Vertex_aux.x+1)=0;
      Selected_positions.at<unsigned char>(Vertex_aux.y+1,Vertex_aux.x)=0;
      Selected_positions.at<unsigned char>(Vertex_aux.y+1,Vertex_aux.x-1)=0;
      Selected_positions.at<unsigned char>(Vertex_aux.y,Vertex_aux.x-1)=0;
      Selected_positions.at<unsigned char>(Vertex_aux.y-1,Vertex_aux.x-1)=0;
      Selected_positions.at<unsigned char>(Vertex_aux.y-1,Vertex_aux.x)=0;
      Selected_positions.at<unsigned char>(Vertex_aux.y-1,Vertex_aux.x+1)=0;
      //
      Count_errors=0;
    }
  }
}

/*************************************************************************/
// initialize the values

void _filter_wcvd::create_cone(vector<_vertex3f> &Vertices)
{
  float Radius;

  Radius=sqrt(Window_width*Window_width+Window_height*Window_height);
//  Radius=sqrt(2)*Radius/log2(Num_cones); // the radius must cover the rectangle
//  Radius=sqrt(2)*Radius/sqrt(Num_cones); // the radius must cover the rectangle

  // formula to compute the angle with an error (See article)
  int Error=1; // 1 pixel error
  float Angle=2*acos(float(int(Radius)-Error)/Radius);
  int Num_divisions=int(2*M_PI/Angle)+1;
  float Apex_height=60.0f;
  _vertex3f Vertex;

  Vertices.resize(Num_divisions+2);
  Vertices[0]=_vertex3f(0,0,Apex_height);
  for (int i=0;i<=Num_divisions;i++){
    Angle=2*M_PI*float(i)/float(Num_divisions);
    Vertex.x=Radius*cos(Angle);
    Vertex.y=Radius*sin(Angle);
    Vertices[i+1]=Vertex;
  }
}

/*************************************************************************/

void _filter_wcvd::create_colors(vector<_vertex3uc> &Colors, vector<_vertex3uc> &False_colors)
{
  _random_uniform_double C1;
  C1.init(0,1);
  C1.set_seed(1000);

  _vertex3uc Color;
  Colors.resize(Number_of_good_dots);
  False_colors.resize(Number_of_good_dots);
  // asign the color
  for (unsigned int i=0;i<Number_of_good_dots;i++){
    // Compute one color
    Color.r= (i & 0x00FF0000) >> 16;
    Color.g= (i & 0x0000FF00) >> 8;
    Color.b= i & 0x000000FF;
    Colors[i]=Color;

    hsv_to_rbg(C1.value(),0.75,0.75,Color.r,Color.g,Color.b);
    False_colors[i]=Color;
  }
}

/*************************************************************************/

void _filter_wcvd::wcvd(cv::Mat *Input_image0,cv::Mat *Output_image0)
{  
  int Count_pass=0;
  char Name_aux[200];
  string File_name;
  bool Save_intermediate_images=false;

  // Size of the output
  Window_width=Output_image0->cols;
  Window_height=Output_image0->rows;
  int Num_pixels=Window_width*Window_height;

  // the image to save the result
  QImage Image(Window_width,Window_height,QImage::Format_RGBA8888);

  GL_widget->makeCurrent();

  // Frame Buffer Object to do the off-screen rendering
  glGenFramebuffers(1,&FBO);
  glBindFramebuffer(GL_FRAMEBUFFER,FBO);

  // Texture for drawing
  glGenTextures(1,&Color_texture);
  glBindTexture(GL_TEXTURE_2D,Color_texture);
  // RGBA8
  glTexStorage2D(GL_TEXTURE_2D,1,GL_RGBA8, Window_width,Window_height);
  // this implies that there is not mip mapping
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

  // Texure for computing the depth
  glGenTextures(1,&Depth_texture);
  glBindTexture(GL_TEXTURE_2D,Depth_texture);
  // Float
  glTexStorage2D(GL_TEXTURE_2D,1,GL_DEPTH_COMPONENT24, Window_width,Window_height);

  // Attatchment of the textures to the FBO
  glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,Color_texture,0);
  glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,Depth_texture,0);

  // OpenGL will draw to these buffers (only one in this case)
  static const GLenum Draw_buffers[]={GL_COLOR_ATTACHMENT0};
  glDrawBuffers(1,Draw_buffers);

  count_dark_pixels(Input_image0);

  create_random_points(Input_image0);

  create_cone(Vertices_cone);

  create_colors(Colors,False_colors);

  /**********************************************************/
  // initialization of data

  // it is necessary to create a VAO
  glCreateVertexArrays(1,&VAO1a);
  glBindVertexArray(VAO1a);

  // Generate 2 buffers for the offsets. They will be used to do the ping-pong
  glGenBuffers(2, &Buffer_offsets[0]);

  // The buffer will be usesd as SSB
  // Offsets[0]
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, Buffer_offsets[0]);
  glBufferData(GL_SHADER_STORAGE_BUFFER,Number_of_good_dots*3*sizeof(GLuint),&Offsets[0],GL_DYNAMIC_COPY);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER,0,Buffer_offsets[0]);

  // Offsets[1]
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, Buffer_offsets[1]);
  glBufferData(GL_SHADER_STORAGE_BUFFER,Number_of_good_dots*3*sizeof(GLuint),nullptr,GL_DYNAMIC_COPY);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER,1,Buffer_offsets[1]);

  // Create a Vertex Buffer Object for cone vertices. They do not change
  glCreateBuffers(1,&VBO1a);
  // Reserve espace and initialice; if use NULL there is not initialization
  glNamedBufferStorage(VBO1a,Vertices_cone.size()*3*sizeof(float),&Vertices_cone[0],GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
  // Bind to VAO.
  glVertexArrayVertexBuffer(VAO1a,0,VBO1a,0,3*sizeof(float));
  // Format of the data
  glVertexArrayAttribFormat(VAO1a,0,3,GL_FLOAT,GL_FALSE,0);
  // Binding to layout 0 and port 0
  glVertexArrayAttribBinding(VAO1a,0,0);
  // Enable the attribute
  glEnableVertexArrayAttrib(VAO1a,0);

  // Create a Vertex Buffer Object for colors. They do not change
  glCreateBuffers(1,&VBO2a);
  // Reserve espace and initialice; if use NULL there is not initialization
  glNamedBufferStorage(VBO2a,Colors.size()*3*sizeof(unsigned char),&Colors[0],GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
  // Bind to VAO.
  glVertexArrayVertexBuffer(VAO1a,1,VBO2a,0,3*sizeof(unsigned char));
  // Format of the data
  glVertexArrayAttribFormat(VAO1a,1,3,GL_UNSIGNED_BYTE,GL_TRUE,0);
  // Binding to layout 0 and port 0
  glVertexArrayAttribBinding(VAO1a,1,1);
  // Enable the attribute
  glEnableVertexArrayAttrib(VAO1a,1);
  //
  glVertexAttribDivisor(1,1);

  // Create a Vertex Buffer Object for FALSE colors
  glCreateBuffers(1,&VBO3a);
  // Reserve espace and initialice; if use NULL there is not initialization
  glNamedBufferStorage(VBO3a,False_colors.size()*3*sizeof(unsigned char),&False_colors[0],GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
  // Bind to VAO.
  glVertexArrayVertexBuffer(VAO1a,2,VBO3a,0,3*sizeof(unsigned char));
  // Format of the data
  glVertexArrayAttribFormat(VAO1a,2,3,GL_UNSIGNED_BYTE,GL_TRUE,0);
  // Binding to layout 0 and port 0
  glVertexArrayAttribBinding(VAO1a,2,2);
  // Enable the attribute
  glEnableVertexArrayAttrib(VAO1a,2);
  //
  glVertexAttribDivisor(2,1);

  // Create the texture that will have the image that will be used as weights
  glCreateTextures(GL_TEXTURE_2D,1,&Image_texture);
  glTextureStorage2D(Image_texture,1,GL_RGBA8,Window_width,Window_height);
  glBindTexture(GL_TEXTURE_2D,Image_texture);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // fill with data of the image
  cv::Mat *Aux_image=new cv::Mat;
  cvtColor(*Input_image0,*Aux_image,cv::COLOR_GRAY2RGBA,4);
  glTextureSubImage2D(Image_texture,0,0,0,Window_width,Window_height,GL_RGBA,GL_UNSIGNED_BYTE,Aux_image->data);

  // Now create the buffer that will save the movements. It also serves to do the addition of how many points have been moved more than the
  // threshold value

  // For doing the addition, it must be a power of 2
  unsigned int Size1=static_cast<unsigned int>(log2(Number_of_good_dots))+1;
  Size1=static_cast<unsigned int>(powf(2,Size1));

  // Create the buffer for doing the addition
  glGenBuffers(1, &Buffer_movement);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, Buffer_movement);
  glBufferData(GL_SHADER_STORAGE_BUFFER,Size1*sizeof(GLuint),nullptr,GL_DYNAMIC_COPY);
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER,2,Buffer_movement);

  /**********************************************************/
  // Parameter to control when the process must be stopped
  // If the distance is > than the Distance_threshold, then the value of the movement is 1
  GLfloat Distance_threshold=1;

  // Variables to control each pass in the addition
  int Num_pass_addition=log2(Size1)-1;
  int Num_elements;
  int Counter;
  int Step1;
  int Step2;

  /**********************************************************/
  // Process

  int Num_max_pass=Number_of_good_dots;
  int Num_pass=0;
  int Min_threshold=Number_of_good_dots*0.05;

  Counter_movements=Number_of_good_dots;

  // Transformation
  QMatrix4x4 MVP;
  MVP.ortho(0,Window_width,0,Window_height,-100,100);

  while (Num_pass<Num_max_pass && Counter_movements>Min_threshold){
    /**************************************************/
    // Step1
    // Drawing using the Offset located in the SSB in layout 0
    glUseProgram(Program1);

    glEnable(GL_DEPTH_TEST);
    glViewport(0,0,Window_width,Window_height);
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glPolygonMode(GL_FRONT,GL_FILL);

    glUniform1i(0,Num_pass); // the current pass. It is used to select the input and ouput SSBOs
    glUniformMatrix4fv(1,1,GL_FALSE,MVP.data());
    glUniform1i(2, 0); // use IDs as colors

    glDrawArraysInstanced(GL_TRIANGLE_FAN,0,Vertices_cone.size(),Number_of_good_dots);

    glUseProgram(0);

    /**************************************************/
    // Step2
    // Count the number of pixels for each color, adding the coordinates in SSB in layout 1
    glUseProgram(Program2);

    // clean the second buffer which will save the new values
    glClearNamedBufferSubData(Buffer_offsets[(Num_pass+1)%2],GL_RGBA32UI,0,Number_of_good_dots*3*sizeof(GLuint),GL_RGBA,GL_UNSIGNED_INT,nullptr);

    // Bind the texture to binding point 0. This means we can access it in our shaders using  layout(binding=0)
    // and we can both read and write from it.
    glBindImageTexture(0, Color_texture, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA8UI);

    // Bind the image texture
    glBindImageTexture(1, Image_texture, 0, GL_FALSE, 0, GL_READ_ONLY, GL_RGBA8UI);

    // Change the values of the uniforms
    glUniform1i(0,Num_pass);
    glUniform1i(3, Window_width);
    glUniform1i(4, Window_height);
    // One instance for each pixel
    glDrawArrays(GL_POINTS, 0, Num_pixels);
    // make sure all computations are done, before we do the next pass, with a barrier.
    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    glUseProgram(0);

    /**************************************************/
    // Step3
    glUseProgram(Program3);

    // Clear the buffer
    glClearNamedBufferSubData(Buffer_movement,GL_R32UI,0,Size1*sizeof(GLuint),GL_RED,GL_UNSIGNED_INT,nullptr);

    glUniform1i(0,Num_pass);
    glUniform1f(5,Distance_threshold);

    glDrawArrays(GL_POINTS, 0, Number_of_good_dots);

    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

    glUseProgram(0);

    /**************************************************/
    // Step 4
    glUseProgram(Program4);

    // The addition is done by adding in a hierarchical way
    Counter=0;
    for (int i=Num_pass_addition;i>=0;i--){
      Num_elements=pow(2,i);
      Step1=pow(2,Counter+1);
      Step2=pow(2,Counter);
      glUniform1i(6,Step1);
      glUniform1i(7,Step2);
      glDrawArrays(GL_POINTS, 0, Num_elements); // launch one thread for each pixel.
      // This is very important. Otherwise it won't run right
      glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
      Counter++;
    }

    // take the number of movements of centroids
    Map=static_cast<GLuint *>(glMapNamedBufferRange(Buffer_movement,0,sizeof(GLuint),GL_MAP_READ_BIT));
    Counter_movements=Map[0];
    glUnmapNamedBuffer(Buffer_movement);

    glUseProgram(0);

    Num_pass++;

    // save the intermediante images
    if (Save_intermediate_images){
      glUseProgram(Program1);

      glEnable(GL_DEPTH_TEST);
      glViewport(0,0,Window_width,Window_height);
      glClearColor(1,1,1,1);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
      glPolygonMode(GL_FRONT,GL_FILL);
      // Transformation
      glUniform1i(2, 1); // use false color
      // Draw
      glDrawArraysInstanced(GL_TRIANGLE_FAN,0,Vertices_cone.size(),Number_of_good_dots);
      glUseProgram(0);

      glGetTextureImage(Color_texture,0,GL_RGBA,GL_UNSIGNED_BYTE,Window_width*Window_height*4*sizeof(GLubyte),Image.bits());
      sprintf(Name_aux,FILE_NAME,Count_pass);
      File_name=Name_aux;
      Image=Image.mirrored();
      Image.save(QString::fromStdString(File_name),"PNG");
      Count_pass++;
    }
  } // end while

  Points.resize(Number_of_good_dots);

  Map_offsets=static_cast<GLuint *>(glMapNamedBufferRange(Buffer_offsets[Num_pass%2],0,Number_of_good_dots*3*sizeof(GLuint),GL_MAP_READ_BIT));
  int Count=0;
  for (uint i=0;i<Number_of_good_dots;i++){
    Points[Count].x=Map_offsets[3*i];
    Points[Count].y=Map_offsets[3*i+1];
    Count++;
  }
  glUnmapNamedBuffer(Buffer_offsets[Num_pass%2]);

  glBindVertexArray(0);

  glDeleteBuffers(1,&VBO1a);
  glDeleteBuffers(1,&VBO2a);
  glDeleteBuffers(1,&VBO3a);
  glDeleteVertexArrays(1,&VAO1a);
  glDeleteFramebuffers(1,&FBO);

  // the normal framebuffer takes the control of drawing
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER,GL_widget->defaultFramebufferObject());

  draw_points(Output_image0);
}

/*************************************************************************/

void _filter_wcvd::update_filter()
{
  Output_image_0->setTo(255);
  wcvd(Aux_input_images[0],Output_image_0);
  update_percent_of_dots();
  update_number_of_dots();
}

/*************************************************************************/

void _filter_wcvd::update()
{
  for (int i=0;i<_f_filter_ns::MAX_CONNECTIONS;i++) Aux_input_images[i]=nullptr;

  if (Changed_input==true){
    Output_image_0->release();
    if (Num_channels_output_image_0==-1){ // input->output
      if (Input_images[0]->channels()==3){
        Output_image_0->create(Input_images[0]->rows,Input_images[0]->cols,CV_8UC3);
      }
      else{
        Output_image_0->create(Input_images[0]->rows,Input_images[0]->cols,CV_8UC1);
      }
    }
    else{ // adjust
      if (Num_channels_output_image_0==3){
        Output_image_0->create(Input_images[0]->rows,Input_images[0]->cols,CV_8UC3);
      }
      else{
        Output_image_0->create(Input_images[0]->rows,Input_images[0]->cols,CV_8UC1);
      }
    }
    Changed_input=false;
  }

  // Check the number of output channels
  for (int i=0;i<_f_filter_ns::MAX_CONNECTIONS;i++){
    if (Input_images[i]!=nullptr){
      if (Input_images[i]->channels()==3 && Num_channels_output_image_0==1){// Different number of channels between input and output
        // conversion
        Aux_input_images[i]=new cv::Mat;
        Aux_input_images[i]->create(Input_images[0]->rows,Input_images[0]->cols,CV_8UC1);
        cvtColor(*Input_images[i],*Aux_input_images[i],cv::COLOR_BGR2GRAY,1);
      }
      else {
        Aux_input_images[i]=Input_images[i];
      }
    }
  }

  update_filter();

  for (int i=0;i<_f_filter_ns::MAX_CONNECTIONS;i++){
    if (Aux_input_images[i]!=nullptr && Aux_input_images[i]!=Input_images[i]) delete Aux_input_images[i];
  }
}

/*************************************************************************/

void _filter_wcvd::save_wcvd_image_to_file(string File_name)
{
  if (Aux_image.cols!=Window_height){
    Aux_image.release();
    Aux_image.create(Window_height,Window_width,CV_8UC3);

    Aux_image1.release();
    Aux_image1.create(Window_height,Window_width,CV_8UC3);

    Image_orig.release();
    Image_orig.create(Window_height,Window_width,CV_8UC3);

    cvtColor(*Aux_input_images[0],Image_orig,cv::COLOR_GRAY2RGB,3);
  }

  glReadBuffer(GL_FRONT);
  glPixelStorei(GL_PACK_ALIGNMENT,1);
  glReadPixels(0,0,Window_width,Window_height,GL_RGB,GL_UNSIGNED_BYTE,&Aux_image.data[0]);

  float Alpha=0.5;

  cv::addWeighted(Image_orig,1-Alpha,Aux_image,Alpha,0,Aux_image1);

	#ifdef WINDOWS
	string Aux_string;
	for (int i = 0; i<File_name.size(); i++) {
		if (File_name[i] == '/') {
			Aux_string.push_back('\\');
		}
		else Aux_string.push_back(File_name[i]);
	}
	File_name = Aux_string;
	#endif

  cv::flip(Aux_image1,Aux_image1,0);

  #ifdef WINDOWS
  cvSaveImage(File_name.c_str(), &(IplImage(Aux_image1)));
  #else
  imwrite(File_name,Aux_image1);
  #endif

}

/*************************************************************************/

void _filter_wcvd::save_wcvd_image()
{
  if (Aux_image.cols!=Window_height){
    Aux_image.release();
    Aux_image.create(Window_height,Window_width,CV_8UC3);
  }

  glReadBuffer(GL_FRONT);
  glPixelStorei(GL_PACK_ALIGNMENT,1);
  glReadPixels(0,0,Window_width,Window_height,GL_RGB,GL_UNSIGNED_BYTE,&Aux_image.data[0]);
}

/*************************************************************************/

void _filter_wcvd::save_GL_state()
{
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
}

/*************************************************************************/

void _filter_wcvd::restore_GL_state()
{
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();
  glPopAttrib();
}

/*************************************************************************/

_filter_wcvd_ui::_filter_wcvd_ui(_gl_widget *GL_widget1,string Name1)
{
  GL_widget=GL_widget1;
  Name=Name1;
  Qtw_filter_wcvd=new _qtw_filter_wcvd(GL_widget1,this,Name);
}

/*************************************************************************/

_filter_wcvd_ui::_filter_wcvd_ui(_gl_widget *GL_widget1, std::map<string, string> &Parameters, string Box_name)
{
  read_parameters(Parameters);
  GL_widget=GL_widget1;
  Name=Box_name;
  Qtw_filter_wcvd=new _qtw_filter_wcvd(GL_widget1,this,Box_name);
}

/*************************************************************************/

_filter_wcvd_ui::~_filter_wcvd_ui()
{
  delete Qtw_filter_wcvd;
}

/*************************************************************************/

void _filter_wcvd_ui::reset_data()
{
  _filter_wcvd::reset_data();
  Qtw_filter_wcvd->parameter1(parameter1());
  hide();
}

/*************************************************************************/

void _filter_wcvd_ui::show()
{
  Qtw_filter_wcvd->show();
}

/*************************************************************************/

void _filter_wcvd_ui::hide()
{
  Qtw_filter_wcvd->hide();
}

/*************************************************************************/

void *_filter_wcvd_ui::get_link()
{
  return Qtw_filter_wcvd->get_link();
}

/*************************************************************************/

void _filter_wcvd_ui::read_parameters(std::map<std::string,std::string> &Parameters)
{
  if (Parameters["_INI_"]=="EDITOR"){// default parameters
    // ¡¡¡ it is necessary to change the order of reading to guarantee that percentage has priority over number of points
    parameter2(WCVD_NUMBER_OF_DOTS_DEFAULT);
    parameter1(WCVD_PERCENT_OF_DOTS_DEFAULT);
    parameter3(WCWD_SAVE_INTERMEDIATE_IMAGES_DEFAULT);
  }
  else{// Parameters from file or from initialised filter
    try{
      // ¡¡¡ it is necessary to change the order of reading to guarantee that percentage has priority over number of points
      if (Parameters["number_of_dots"]=="default") parameter2(WCVD_NUMBER_OF_DOTS_DEFAULT);
      else parameter2(atoi(Parameters["number_of_dots"].c_str()));

      if (Parameters["percent_of_dots"]=="default") parameter1(WCVD_PERCENT_OF_DOTS_DEFAULT);
      else parameter1(atoi(Parameters["percent_of_dots"].c_str()));

      if (Parameters["save_intermediate_images"]=="default") parameter3(WCWD_SAVE_INTERMEDIATE_IMAGES_DEFAULT);
      else{
        if (Parameters["save_intermediate_images"]=="true") parameter3(true);
        else parameter3(false);
      }
    }
    catch (const std::out_of_range) {
      QMessageBox MsgBox;
      MsgBox.setText("Error in the data of WCVD filter");
      MsgBox.exec();
      exit(-1);
    }
  }
}

/*************************************************************************/

void _filter_wcvd_ui::write_parameters(std::map<string, string> &Parameters)
{
  char Aux[100];
  
  sprintf(Aux,"%d",parameter1());
  Parameters["percent_of_dots"]=string(Aux);
  sprintf(Aux,"%d",parameter2());
  Parameters["number_of_dots"]=string(Aux);

  if (parameter3()) sprintf(Aux,"%s","true");
  else sprintf(Aux,"%s","false");
  Parameters["save_intermediate_images"]=string(Aux);
}

/*************************************************************************/

void _filter_wcvd_ui::update_percent_of_dots()
{
  Qtw_filter_wcvd->parameter1(parameter1());
}

/*************************************************************************/

void _filter_wcvd_ui::update_number_of_dots()
{
  Qtw_filter_wcvd->parameter2(parameter2());
}

/*************************************************************************/

_qtw_filter_wcvd::_qtw_filter_wcvd(_gl_widget *GL_widget1,_filter_wcvd_ui *Filter1,string Box_name)
{
  GL_widget=GL_widget1;
  Filter=Filter1;

  Group_box_main=new QGroupBox(tr(Box_name.c_str()));
  Group_box_main->setAlignment(Qt::AlignCenter);

  QVBoxLayout *Vertical_box_main=new QVBoxLayout;

  // Parameter1
  // percent of dots
  Group_box_parameter1=new QGroupBox(tr(String_group_box_parameter1.c_str()));
  Group_box_parameter1->setAlignment(Qt::AlignCenter);

  QGridLayout *Grid_parameter1 = new QGridLayout;

  QLabel *Label_parameter1_min= new QLabel(tr(String_label_parameter1_min.c_str()));
  QLabel *Label_parameter1_max= new QLabel(tr(String_label_parameter1_max.c_str()));

  Line_edit_parameter1=new QLineEdit();
  Line_edit_parameter1->setAlignment(Qt::AlignRight);
  Line_edit_parameter1->setReadOnly(true);
  Line_edit_parameter1->setEnabled(false);
  Line_edit_parameter1->setToolTip(tr(String_label_parameter1_tooltip.c_str()));

  Slider_parameter1 = new QSlider(Qt::Horizontal);
  Slider_parameter1->setRange(Parameter1_min_value,Parameter1_max_value);
  Slider_parameter1->setSingleStep(Parameter1_single_step);
  Slider_parameter1->setPageStep(Parameter1_page_step);
  Slider_parameter1->setTickInterval(Parameter1_tick_interval);
  Slider_parameter1->setTickPosition(QSlider::TicksRight);
  Slider_parameter1->setTracking(Parameter1_set_tracking);
  Slider_parameter1->setToolTip(tr(String_parameter1_tooltip.c_str()));

  parameter1(Filter->parameter1());

  Grid_parameter1->addWidget(Line_edit_parameter1,0,1,Qt::AlignCenter);
  Grid_parameter1->addWidget(Label_parameter1_min,1,0,Qt::AlignRight);
  Grid_parameter1->addWidget(Slider_parameter1,1,1);
  Grid_parameter1->addWidget(Label_parameter1_max,1,2,Qt::AlignLeft);

  Group_box_parameter1->setLayout(Grid_parameter1);

  connect(Slider_parameter1, SIGNAL(valueChanged(int)),this,SLOT(parameter1_slot(int)));

  // Parameter2
  // Number of points
  Group_box_parameter2=new QGroupBox(tr(String_group_box_parameter2.c_str()));
  Group_box_parameter2->setAlignment(Qt::AlignCenter);
  Group_box_parameter2->setEnabled(false);

  QVBoxLayout *Vertical_box_parameter2 = new QVBoxLayout;

  Spinbox_parameter2=new QSpinBox;
  Spinbox_parameter2->setRange(10,100000);
  Spinbox_parameter2->setToolTip(tr(String_parameter2_tooltip.c_str()));
  Spinbox_parameter2->setKeyboardTracking(false);
  Spinbox_parameter2->setAlignment(Qt::AlignRight);

  parameter2(Filter->parameter2());

  Vertical_box_parameter2->addWidget(Spinbox_parameter2);

  Group_box_parameter2->setLayout(Vertical_box_parameter2);

  connect(Spinbox_parameter2, SIGNAL(valueChanged(int)),this,SLOT(parameter2_slot(int)));

  // Save intermediate images
  // Parameter 3
  Group_box_parameter3=new QGroupBox(tr(String_group_box_parameter3.c_str()));
  Group_box_parameter3->setAlignment(Qt::AlignCenter);

  QVBoxLayout *Vertical_box_parameter3 = new QVBoxLayout;

  Checkbox_parameter3=new QCheckBox(tr(String_checkbox_parameter3.c_str()));
  Checkbox_parameter3->setToolTip(tr(String_parameter3_tooltip.c_str()));

  parameter3(Filter->parameter3());

  Vertical_box_parameter3->addWidget(Checkbox_parameter3);

  Group_box_parameter3->setLayout(Vertical_box_parameter3);

  connect(Checkbox_parameter3,SIGNAL(stateChanged(int)),this,SLOT(parameter3_slot(int)));

  // Parameter4
  // percent of fixed centroidals
  Group_box_parameter4=new QGroupBox(tr(String_group_box_parameter4.c_str()));
  Group_box_parameter4->setAlignment(Qt::AlignCenter);

  QGridLayout *Grid_parameter4 = new QGridLayout;

  QLabel *Label_parameter4_min= new QLabel(tr(String_label_parameter4_min.c_str()));
  QLabel *Label_parameter4_max= new QLabel(tr(String_label_parameter4_max.c_str()));

  Line_edit_parameter4=new QLineEdit();
  Line_edit_parameter4->setAlignment(Qt::AlignRight);
  Line_edit_parameter4->setReadOnly(true);
  Line_edit_parameter4->setEnabled(false);
  Line_edit_parameter4->setToolTip(tr(String_label_parameter4_tooltip.c_str()));

  Slider_parameter4 = new QSlider(Qt::Horizontal);
  Slider_parameter4->setRange(Parameter4_min_value,Parameter4_max_value);
  Slider_parameter4->setSingleStep(Parameter4_single_step);
  Slider_parameter4->setPageStep(Parameter4_page_step);
  Slider_parameter4->setTickInterval(Parameter4_tick_interval);
  Slider_parameter4->setTickPosition(QSlider::TicksRight);
  Slider_parameter4->setTracking(Parameter4_set_tracking);
  Slider_parameter4->setToolTip(tr(String_parameter4_tooltip.c_str()));

  parameter4(Filter->parameter4());

  Grid_parameter4->addWidget(Line_edit_parameter4,0,1,Qt::AlignCenter);
  Grid_parameter4->addWidget(Label_parameter4_min,1,0,Qt::AlignRight);
  Grid_parameter4->addWidget(Slider_parameter4,1,1);
  Grid_parameter4->addWidget(Label_parameter4_max,1,2,Qt::AlignLeft);

  Group_box_parameter4->setLayout(Grid_parameter4);

  connect(Slider_parameter4, SIGNAL(valueChanged(int)),this,SLOT(parameter4_slot(int)));

  // Parameter5
  // percent of fixed centroidals
  Group_box_parameter5=new QGroupBox(tr(String_group_box_parameter5.c_str()));
  Group_box_parameter5->setAlignment(Qt::AlignCenter);

  QVBoxLayout *Verticalbox_parameter5 = new QVBoxLayout;

  Spinbox_parameter5=new QSpinBox;

  Spinbox_parameter5 = new QSpinBox;
  Spinbox_parameter5->setMaximum(Filter->parameter5());
  Spinbox_parameter5->setAlignment(Qt::AlignRight);
  Spinbox_parameter5->setKeyboardTracking(false);
  Spinbox_parameter5->setToolTip(tr(String_parameter5_tooltip.c_str()));

  parameter5(Filter->parameter5());

  Verticalbox_parameter5->addWidget(Spinbox_parameter5);

  Group_box_parameter5->setLayout(Verticalbox_parameter5);

  connect(Spinbox_parameter5, SIGNAL(valueChanged(int)),this,SLOT(parameter5_slot(int)));

  // selector type
  // parameter 6
  Group_box_parameter6=new QGroupBox(tr(String_group_box_parameter6.c_str()));
  Group_box_parameter6->setAlignment(Qt::AlignCenter);

  QVBoxLayout *Vertical_box_parameter6 = new QVBoxLayout;

  Combo_parameter6 = new QComboBox;
  Combo_parameter6->addItem(tr("Percentage of dots"));
  Combo_parameter6->addItem(tr("Number of dots"));
  Combo_parameter6->setToolTip(tr(String_parameter6_tooltip.c_str()));

  parameter6(Filter->parameter6());

  Vertical_box_parameter6->addWidget(Combo_parameter6);

  Group_box_parameter6->setLayout(Vertical_box_parameter6);

  connect(Combo_parameter6, SIGNAL(currentIndexChanged(int)),this,SLOT(parameter6_slot(int)));

  //
  Vertical_box_main->addWidget(Group_box_parameter4);
  Vertical_box_main->addWidget(Group_box_parameter5);
  Vertical_box_main->addWidget(Group_box_parameter6);
  Vertical_box_main->addWidget(Group_box_parameter1);
  Vertical_box_main->addWidget(Group_box_parameter2);
  Vertical_box_main->addWidget(Group_box_parameter3);

  Group_box_main->setLayout(Vertical_box_main);
}

/*************************************************************************/

void _qtw_filter_wcvd::parameter1(int Value)
{
  QString Str;

  Str=Str.number(Value);
  Line_edit_parameter1->setText(Str);
  Slider_parameter1->blockSignals(true);
  Slider_parameter1->setValue(Value);
  Slider_parameter1->blockSignals(false);
}

/*************************************************************************/

void _qtw_filter_wcvd::parameter2(int Value)
{
  Spinbox_parameter2->blockSignals(true);
  Spinbox_parameter2->setValue(Value);
  Spinbox_parameter2->blockSignals(false);
}

/*************************************************************************/

void _qtw_filter_wcvd::parameter3(bool Value)
{
  Checkbox_parameter3->blockSignals(true);
  if (Value) Checkbox_parameter3->setChecked(true);
  else Checkbox_parameter3->setChecked(false);
  Checkbox_parameter3->blockSignals(false);
}

/*************************************************************************/

void _qtw_filter_wcvd::parameter4(int Value)
{
  QString Str;

  Str=Str.number(Value);
  Line_edit_parameter4->setText(Str);
  Slider_parameter4->blockSignals(true);
  Slider_parameter4->setValue(Value);
  Slider_parameter4->blockSignals(false);
}

/*************************************************************************/

void _qtw_filter_wcvd::parameter5(int Value)
{
  Spinbox_parameter5->blockSignals(true);
  Spinbox_parameter5->setValue(Value);
  Spinbox_parameter5->blockSignals(false);
}

/*************************************************************************/

void _qtw_filter_wcvd::parameter6(int Value)
{
  Combo_parameter6->blockSignals(true);
  Combo_parameter6->setCurrentIndex(Value);
  Combo_parameter6->blockSignals(false);
}

/*************************************************************************/

void _qtw_filter_wcvd::parameter1_slot(int Size)
{
  QString Str;
  char Aux[100];

  sprintf(Aux,"%2d",Size);
  Str=Aux;
  Line_edit_parameter1->setText(Str);
  Filter->parameter1(Size);
  GL_widget->update_effect(Filter->name());
}

/*************************************************************************/

void _qtw_filter_wcvd::parameter2_slot(int Size)
{
  Filter->parameter2(Size);
  GL_widget->update_effect(Filter->name());
}

/*************************************************************************/

void _qtw_filter_wcvd::parameter3_slot(int Value)
{
  if (Value==Qt::Checked) Filter->parameter3(true);
  else Filter->parameter3(false);

  GL_widget->update_effect(Filter->name());
  Checkbox_parameter3->blockSignals(true);
  Checkbox_parameter3->setChecked(false);
  Checkbox_parameter3->blockSignals(false);
}

/*************************************************************************/

void _qtw_filter_wcvd::parameter4_slot(int Size)
{
  QString Str;
  char Aux[100];

  sprintf(Aux,"%2d",Size);
  Str=Aux;
  Line_edit_parameter4->setText(Str);
  Filter->parameter4(Size);
  GL_widget->update_effect(Filter->name());
}

/*************************************************************************/

void _qtw_filter_wcvd::parameter5_slot(int Size)
{
  Filter->parameter5(Size);
  GL_widget->update_effect(Filter->name());
}

/*************************************************************************/

void _qtw_filter_wcvd::parameter6_slot(int Value)
{
  if (Value==0){
    Group_box_parameter1->setEnabled(true);
    Group_box_parameter2->setEnabled(false);
  }
  else{
    Group_box_parameter1->setEnabled(false);
    Group_box_parameter2->setEnabled(true);
  }

  Filter->parameter6(Value);
  GL_widget->update_effect(Filter->name());
}
