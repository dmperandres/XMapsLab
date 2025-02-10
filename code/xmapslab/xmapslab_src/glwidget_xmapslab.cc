//LIC

#include "glwidget_xmapslab.h"
#include "window_xmapslab.h"

#include "table_layers.h"
// #include "dialog_create_palette.h"

//using namespace _gl_widget_xmapslab_ns;

_gl_widget_xmapslab::_gl_widget_xmapslab(_window_xmapslab *Window1):Window(Window1)
{
  #ifdef DEBUG_XML
  cout << "_gl_widget_xmapslab constructor" << endl;
  #endif

  setMinimumSize(300, 300);
  setFocusPolicy(Qt::StrongFocus);
}

//HEA

_gl_widget_xmapslab::~_gl_widget_xmapslab()
{
#ifdef DEBUG_XML
  std::cout << "terminando gl_widget" << std::endl;
#endif
}

//HEA

GLuint _gl_widget_xmapslab::set_texture(shared_ptr<cv::Mat> Image)
{
  GLuint Texture;

  glCreateTextures(GL_TEXTURE_2D,1,&Texture);

#ifdef DEBUG_XML
  cout << "Texture=" << Texture << endl;
#endif

  glTextureStorage2D(Texture,1,GL_RGBA8,Image->cols,Image->rows);

  // std::cout << "set=" << Texture << " image=" << Image << " Color=" << Image->at<cv::Vec4b>(500,500) << std::endl;

  glBindTexture(GL_TEXTURE_2D,Texture);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // fill with data
  glTextureSubImage2D(Texture,0,0,0,Image->cols,Image->rows,GL_BGRA,GL_UNSIGNED_BYTE,&Image->data[0]);

  return Texture;
}

//HEA
// BGRA

void _gl_widget_xmapslab::update_texture(GLuint Texture, std::shared_ptr<cv::Mat> Image)
{
  makeCurrent();

  // std::cout << "update=" << Texture << " image=" << Image << " Color=" << Image->at<cv::Vec4b>(500,500) << std::endl;

  glBindVertexArray(VAO1);
  glBindTexture(GL_TEXTURE_2D,Texture);
  glTextureSubImage2D(Texture,0,0,0,Image->cols,Image->rows,GL_BGRA,GL_UNSIGNED_BYTE,&Image->data[0]);
  glBindVertexArray(0);
}

//HEA

void _gl_widget_xmapslab::update_size_texture(int Width1,int Height1)
{
  makeCurrent();

  Vertices[0]=_vertex3f(-Width1/2, -Height1/2, 0.0f);
  Vertices[1]=_vertex3f(Width1/2, -Height1/2, 0.0f);
  Vertices[2]=_vertex3f(-Width1/2, Height1/2, 0.0f);
  Vertices[3]=_vertex3f(Width1/2, -Height1/2, 0.0f);
  Vertices[4]=_vertex3f(Width1/2, Height1/2, 0.0f);
  Vertices[5]=_vertex3f(-Width1/2, Height1/2, 0.0f);

  glBindVertexArray(VAO1);
  // uptdate vertices coordinates
  glNamedBufferSubData(VBO1_1,0,Vertices.size()*3*sizeof(float),&Vertices[0]);

  glBindVertexArray(0);
}

//HEA

void _gl_widget_xmapslab::mousePressEvent(QMouseEvent *Event)
{
  Initial_position_X=Event->position().x();
  Initial_position_Y=Event->position().y();

  if (Event->buttons() & Qt::LeftButton) {
      if (Event->modifiers() & Qt::ShiftModifier){
        Start_box_position_X=Initial_position_X;
        Start_box_position_Y=Initial_position_Y;
        Start_box_position_X=Scale_factor*Start_box_position_X-Translation.x-Window_width*Scale_factor/2;
        Start_box_position_Y=Scale_factor*Start_box_position_Y+Translation.y-Window_height*Scale_factor/2;

        Select_zone=true;
      }
    else Change_pos=true;
  }
  else{
    if (Event->buttons() & Qt::RightButton) {
      Selection_position_X=Event->position().x();
      Selection_position_Y=(height()-Event->position().y());
    }
  }
}

//HEA

void _gl_widget_xmapslab::mouseReleaseEvent(QMouseEvent *Event)
{
  if (Event->button() & Qt::LeftButton){
    if (Event->modifiers() & Qt::ShiftModifier) Select_zone=false;
    else Change_pos=false;
  }
  else{
    compute_position();
  }
}

//HEA

void _gl_widget_xmapslab::mouseDoubleClickEvent(QMouseEvent *Event)
{
  if (Event->buttons() & Qt::LeftButton) {
    Translation.x=0;
    Translation.y=0;
  }
  else if (Event->buttons() & Qt::RightButton) {
    Scale_factor=1.0;
  }

  update();
}

//HEA

void _gl_widget_xmapslab::mouseMoveEvent(QMouseEvent *Event)
{
  int Last_position_X=Event->position().x();
  int Last_position_Y=Event->position().y();

  if (Change_pos==true){
    Translation.x+=Last_position_X-Initial_position_X;
    Translation.y+=Initial_position_Y-Last_position_Y;
    Initial_position_X=Last_position_X;
    Initial_position_Y=Last_position_Y;
  }

  if (Select_zone==true){
    End_box_position_X=Last_position_X;
    End_box_position_Y=Last_position_Y;
    End_box_position_X=Scale_factor*End_box_position_X-Translation.x-Window_width*Scale_factor/2;
    End_box_position_Y=Scale_factor*End_box_position_Y+Translation.y-Window_height*Scale_factor/2;
  }

  update();
}

//HEA

void _gl_widget_xmapslab::wheelEvent(QWheelEvent *Event)
{
  QPoint Num_degrees = Event->angleDelta();
  int Step = Num_degrees.y();

  if (Step<0) Scale_factor/=_common_ns::MOUSE_SCALING_FACTOR;
  else Scale_factor*=_common_ns::MOUSE_SCALING_FACTOR;

  update();
}

//HEA
// This function creates an image from the other textures, as in the update function, but only for the part
// of the image that is important (not the surround space)

void _gl_widget_xmapslab::create_texture(cv::Mat *Composed_image1)
{
  // check data
  int Counter=0;
  for (unsigned int i=0;i<Window->Vec_order_of_layers_by_name.size();i++){
    if (Window->Map_name_to_layer[Window->Vec_order_of_layers_by_name[i]].Layer->state(0)==true) Counter++;
  }

  if (Counter>0){
    int Width=Window->Map_name_to_layer[Window->Vec_order_of_layers_by_name[0]].Layer->width();
    int Height=Window->Map_name_to_layer[Window->Vec_order_of_layers_by_name[0]].Layer->height();

    // create the textures for the input images
    // At least one VAO
    glCreateVertexArrays(1,&VAO2);
    glBindVertexArray(VAO2);


    // The buffer for the result. RGBA
    GLuint Texture_result;
    glCreateTextures(GL_TEXTURE_2D,1,&Texture_result);
    glTextureStorage2D(Texture_result,1,GL_RGBA8,Width,Height);

    glUseProgram(Program2);
    glBindVertexArray(VAO2);

    // num of textures
    glUniform1i(0,Width);
    glUniform1i(1,Height);
    // Num of images
    glUniform1i(2,Counter);
    // background color
    glUniform3fv(3,1,(GLfloat*) &_common_ns::COLORS[_common_ns::WHITE]);

    // IMPORTANT!
    // Only 8 image units!

    int Pos=0;
    std::string Name;
    for (unsigned int i=0;i<Window->Vec_order_of_layers_by_name.size();i++){
      Name=Window->Vec_order_of_layers_by_name[i];
      if (Window->Map_name_to_layer[Name].Layer->state(0)==true){
        glUniform1i(50+Pos,int(Window->Map_name_to_layer[Name].Layer->type()));
        glUniform1f(60+Pos,Window->Map_name_to_layer[Name].Layer->transparency());
        glUniform1i(70+Pos,int(Window->Map_name_to_layer[Name].Layer->inversion()));
        glUniform1i(80+Pos,1); // color mixing

        glBindImageTexture(Pos,Window->Map_name_to_layer[Name].Texture,0,GL_FALSE,0,GL_READ_ONLY,GL_RGBA8UI);
        Pos++;
      }
    }

    // Bind the results
    glBindImageTexture(7,Texture_result,0,GL_FALSE,0,GL_READ_WRITE,GL_RGBA8UI);

    //
    glViewport(0,0,Width,Height);
    // draw a point for each pixel
    glDrawArrays(GL_POINTS, 0, Width*Height);

    // get the information from the texture.
    // the Mat where the data is saved
    Composed_image1->create(Height,Width,CV_8UC4);

    // There are two possibilities:
    // 1) To bind the texture with the result and read it (see below)
    //    glBindTexture(GL_TEXTURE_2D,Texture_result);
    //    glGetTexImage(GL_TEXTURE_2D,0,GL_BGRA,GL_UNSIGNED_BYTE,&Composed_image->data[0]);
    //
    // or
    // 2) To read directly the texture, as below. In that case, take care that the size is in bytes

    glGetTextureImage(Texture_result,0,GL_BGRA,GL_UNSIGNED_BYTE,Width*Height*4,&Composed_image1->data[0]);

    glUseProgram(0);
    glBindVertexArray(0);

    glDeleteTextures(1,&Texture_result);
    glDeleteVertexArrays(1,&VAO2);
  }
}

//HEA

void _gl_widget_xmapslab::draw_objects()
{
  // check data
  int Counter=0;
  for (unsigned int i=0;i<Window->Vec_order_of_layers_by_name.size();i++){
    if (Window->Map_name_to_layer[Window->Vec_order_of_layers_by_name[i]].Layer->state(0)==true) Counter++;
  }

  // std::cout << "ratio=" << Device_pixel_ratio << std::endl;

  QMatrix4x4 Model_view;

  // the parameters imply that initially we define 1:1 ratio between the pixels of the device window and the camera window
  // the coordinate system is centered
  // for example, if the device window has a size of 1000 widh the origin a the top left corner with value 0 (left-handed c. system)
  // the GL camera window will be right-handed and centered, with coordinates -width/2 to +width/2
  // If we do a zoom out by a 2 factor, a value of 0.5, then GL camera window coordinates will be -width*0.5/2=-width/2 to +width/4
  Model_view.ortho(-Window_width*Scale_factor/2,Window_width*Scale_factor/2,-Window_height*Scale_factor/2, Window_height*Scale_factor/2,-100,100);
  Model_view.translate(Translation.x,Translation.y,0);

#ifdef LINUX
  // OpenGL is not aware of the device pixel ratio. If it is 2, it means that a true 2000 size is converted to 1000 for Qt but not for GL
  // It is necessary to scale the size of the window (GL drawing zone) by the device pixel ratio to get the true size

  glViewport(0,0,Window_width*Device_pixel_ratio,Window_height*Device_pixel_ratio);
#endif

  glClearColor(0.8f,0.8f,0.8f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glUseProgram(Program1);
  glBindVertexArray(VAO1);

  glUniformMatrix4fv(0,1,GL_FALSE,Model_view.data());

  if (Window->show_positions() || Window->show_triangulation()!=_layer_map_triangulation_ns::_triangulation_mode::TRIANGULATION_MODE_NONE) Counter++;

  // num of textures
  glUniform1i(20,Counter);
  // background color
  glUniform3fv(21,1,(GLfloat*) &_common_ns::COLORS[_common_ns::WHITE]);
  // Compose color
//  glUniform1i(22,int(Compose_colors));

  int Pos=0;
  std::string Name;
  for (unsigned int i=0;i<Window->Vec_order_of_layers_by_name.size();i++){
    Name=Window->Vec_order_of_layers_by_name[i];
    if (Window->Map_name_to_layer[Name].Layer->state(0)==true){
      glUniform1i(50+Pos,int(Window->Map_name_to_layer[Name].Layer->type()));
      glUniform1f(60+Pos,Window->Map_name_to_layer[Name].Layer->transparency());
      glUniform1i(70+Pos,int(Window->Map_name_to_layer[Name].Layer->inversion()));
      glUniform1i(80+Pos,1); // color mixing
      glBindTextureUnit(Pos,Window->Map_name_to_layer[Name].Texture);
      Pos++;
    }
  }
  // add the positions
  if (Window->show_positions() || Window->show_triangulation()!=_layer_map_triangulation_ns::_triangulation_mode::TRIANGULATION_MODE_NONE){
    glUniform1i(50+Pos,int(0));
    glUniform1f(60+Pos,0);
    glUniform1i(70+Pos,0);
    glBindTextureUnit(Pos,Window->Map_name_to_layer["Positions"].Texture);
  }


  glDrawArrays(GL_TRIANGLES,0,6);

  glBindVertexArray(0);
  glUseProgram(0);

//  if (Compose_colors){
//    // save the image in the buffer
//    if (Compose_image==nullptr){
//      Compose_image=make_shared<cv::Mat>();
//      Compose_image->create(Window->initial_height(),Window->initial_width(),CV_8UC4); // rows, cols
//    }
//    glReadBuffer(GL_FRONT);
//    glPixelStorei(GL_PACK_ALIGNMENT,1);
//    glReadPixels(0,0,Compose_image->cols,Compose_image->rows,GL_RGBA,GL_UNSIGNED_BYTE,&Compose_image->data[0]);
//  }
}


//HEA
// draw a box given the coordinates of left top corner, the width and the height

void _gl_widget_xmapslab::draw_box(QPainter& Painter)
{
  // this controls the width of the line. Adjust to device pixel ratio
  float Width=2*Scale_factor/Device_pixel_ratio+3;
  QPen pen;
  pen.setWidth(Width);

  pen.setColor(Qt::white);
  //pen.setDashPattern({ 0.0, 1.0 * scale, 1.0 * scale, 7.0 * scale });
  pen.setDashPattern({ 5.0, 5.0});
  Painter.setPen(pen);
  Painter.drawRect(Start_box_position_X, Start_box_position_Y, End_box_position_X-Start_box_position_X, End_box_position_Y-Start_box_position_Y);

  pen.setColor(Qt::black);
  pen.setDashPattern({ 5.0, 5.0});
  pen.setDashOffset(5.0);
  Painter.setPen(pen);
  Painter.drawRect(Start_box_position_X, Start_box_position_Y, End_box_position_X-Start_box_position_X, End_box_position_Y-Start_box_position_Y);
}

//HEA

void _gl_widget_xmapslab::paintEvent(QPaintEvent *Event)
{
  Q_UNUSED(Event)

  #ifdef DEBUG_XML
  cout << "_gl_widget_xmapslab paintEvent" << endl;
  #endif

  QPainter Painter;
  Painter.begin(this);

  Painter.beginNativePainting();
  draw_objects();
  Painter.endNativePainting();

  if (Select_zone==true || Activate_image_section==true){
    // It is necessary to set the window and the viewport! In case of changing device pixel ratio, the viewport has the true size instead of the scaled one.
    Painter.setWindow(QRect(-Window_width*Scale_factor/2-Translation.x, -Window_height*Scale_factor/2+Translation.y, Window_width*Scale_factor, Window_height*Scale_factor));
    Painter.setViewport(0,0,Window_width,Window_height);
    draw_box(Painter);
  }

  Painter.end();
}

//HEA

void _gl_widget_xmapslab::paintGL()
{
//  QPainter painter;
//  painter.begin(this);

//  painter.fillRect(0, 0, 128, 128, Qt::green);

//  painter.beginNativePainting();

//  draw_objects();

//  painter.endNativePainting();

//  painter.end();
}

//*************************************************************************
//
//*************************************************************************

void _gl_widget_xmapslab::resizeGL(int Width1, int Height1)
{
  #ifdef DEBUG_XML
  cout << "_gl_widget_xmapslab resizeGL" << endl;
  #endif

  Window_width=Width1;
  Window_height=Height1;

  glViewport(0,0,Width1*Device_pixel_ratio,Height1*Device_pixel_ratio);
}

//*************************************************************************
//
//*************************************************************************


void _gl_widget_xmapslab::initialize_object()
{  
  #ifdef DEBUG_XML
  cout << "_gl_widget_xmapslab initialize_object" << endl;
  #endif

  _shaders Shader;

  // basic
  static const GLchar * P0_vs[]={
  #include "basic_xmapslab.vert"
  };

  static const GLchar * P0_fs[]={
  #include "basic_xmapslab.frag"
  };

  Program1=Shader.load_shaders(P0_vs,P0_fs);
  if (Program1==0){
    QMessageBox::critical(Window, Window->tr("Error"),Window->tr("Error with the GPU program 'basic'"));
    QApplication::quit();
    exit(-1);
  }

  // compose
  static const GLchar * P1_vs[]={
  #include "compose.vert"
  };

  static const GLchar * P1_fs[]={
  #include "compose.frag"
  };

  Program2=Shader.load_shaders(P1_vs,P1_fs);
  if (Program2==0){
    QMessageBox::critical(Window, Window->tr("Error"),Window->tr("Error with the GPU program 'compose'"));
    QApplication::quit();
    exit(-1);
  }

  // adjust the sizes
  Vertices.resize(6);
  Tex_coordinates.resize(6);

  Tex_coordinates[0]=_vertex2f(0.0,0.0);
  Tex_coordinates[1]=_vertex2f(1.0,0.0);
  Tex_coordinates[2]=_vertex2f(0.0,1.0);
  Tex_coordinates[3]=_vertex2f(1.0,0.0);
  Tex_coordinates[4]=_vertex2f(1.0,1.0);
  Tex_coordinates[5]=_vertex2f(0.0,1.0);

  glCreateVertexArrays(1,&VAO1);
  glBindVertexArray(VAO1);

  // vertices coordinates
  // create
  glCreateBuffers(1,&VBO1_1);
  // reserve espace (and initialice; if use NULL there is not initialization)
  glNamedBufferStorage(VBO1_1,Vertices.size()*3*sizeof(float),&Vertices[0],GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
  // bind to VAO
  glVertexArrayVertexBuffer(VAO1,0,VBO1_1,0,3*sizeof(float));
  // state the format of the data
  glVertexArrayAttribFormat(VAO1,1,3,GL_FLOAT,GL_FALSE,0);
  // state what vertex buffer binding ot use for this attribute
  glVertexArrayAttribBinding(VAO1,1,0);
  // enable the attribute
  glEnableVertexAttribArray(1);


  glCreateBuffers(1,&VBO1_2);
  // reserve espace (and initialice; if use NULL there is not initialization)
  glNamedBufferStorage(VBO1_2,Tex_coordinates.size()*2*sizeof(float),&Tex_coordinates[0],GL_DYNAMIC_STORAGE_BIT);
  // bind to VAO
  glVertexArrayVertexBuffer(VAO1,1,VBO1_2,0,2*sizeof(float));
  // state the format of the data
  glVertexArrayAttribFormat(VAO1,2,2,GL_FLOAT,GL_FALSE,0);
  // state what vertex buffer binding ot use for this attribute
  glVertexArrayAttribBinding(VAO1,2,1);
  // enable the attribute
  glEnableVertexAttribArray(2);

  glBindVertexArray(0);

  //
  Scale_factor=1.0;
  Translation=_vertex2f(0,0);

  Image_changed=true;

  Device_pixel_ratio=devicePixelRatio();
}

//HEA

void _gl_widget_xmapslab::initializeGL()
{
#ifdef DEBUG_XML
  const GLubyte* strm;

  cout << "_gl_widget_xmapslab initializeGL" << endl;

  strm = glGetString(GL_VENDOR);
  cout << "Vendor: " << strm << "\n";
  strm = glGetString(GL_RENDERER);
  cout << "Renderer: " << strm << "\n";
  strm = glGetString(GL_VERSION);
  cout << "OpenGL Version: " << strm << "\n";

  if (strm[0] == '1'){
    cout << "Only OpenGL 1.X supported!\n";
    exit(-1);
    }

  strm = glGetString(GL_SHADING_LANGUAGE_VERSION);
  cout << "GLSL Version: " << strm << "\n";
#endif


  glewExperimental = GL_TRUE;
  int err = glewInit();
  if (GLEW_OK != err){
    // Problem: glewInit failed, something is seriously wrong.
//    cout << "Error: " << glewGetErrorString(err) << "\n";

    QMessageBox MsgBox(this);
    QFont Font=MsgBox.font();
    Font.setPointSize(20);
    MsgBox.setFont(Font);
    MsgBox.setText("Error: There is not OpenGL drivers\n\nPlease, look for the information of your GPU (AMD, INTEL or NVIDIA) and install the drivers");
    MsgBox.exec();
    Window->close();
    }

  #ifdef DEBUG_XML
  cout << "_gl_widget_xmapslab glewInit ok" << endl;
  #endif

  // este codigo es para limpiar un error que se produce con GLEW (inclido 1.10)
  // http://www.opengl.org/wiki/OpenGL_Loading_Library
  GLenum glErr;
  glErr = glGetError();
  while (glErr!=GL_NO_ERROR) glErr = glGetError();

//  //
//  int Max_texture_size=0;
//  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &Max_texture_size);
//  std::cout << "Max texture size: " << Max_texture_size << "\n";

//  int Max_texture_units=0;
//  glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &Max_texture_units);
//  std::cout << "Max texture units: " << Max_texture_units << "\n";

//  int Max_texture_units_shader=0;
//  glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &Max_texture_units_shader);
//  std::cout << "Max texture units per vertex shader: " << Max_texture_units_shader << "\n";

//  int Max_image_units_vertex_shader=0;
//  glGetIntegerv(GL_MAX_VERTEX_IMAGE_UNIFORMS, &Max_image_units_vertex_shader);
//  std::cout << "Max image units per vertex shader: " << Max_image_units_vertex_shader << "\n";

//  int Max_image_units_fragement_shader=0;
//  glGetIntegerv(GL_MAX_FRAGMENT_IMAGE_UNIFORMS, &Max_image_units_fragement_shader);
//  std::cout << "Max image units per fragment shader: " << Max_image_units_fragement_shader << "\n";

  Window_width=width();
  Window_height=height();

  initialize_object();
}

//HEA

void _gl_widget_xmapslab::add_table_layer(QString Name1,int Row)
{
  Q_UNUSED(Name1)
  Q_UNUSED(Row)

  // add the new widget at the same position
//  Verticalbox_layers->insertWidget(1,(QGroupBox *)(Window->Vec_layers.get_data(Name1.toStdString())->get_link()),0,Qt::AlignTop);

  for(unsigned int i=0; i<Window->Vec_order_of_layers_by_name.size();i++){
    Window->Map_name_to_layer[Window->Vec_order_of_layers_by_name[i]].Layer->hide();
  }

  Window->Map_name_to_layer[Window->Vec_order_of_layers_by_name[Window->Vec_order_of_layers_by_name.size()-1]].Layer->show();
}

//HEA

void _gl_widget_xmapslab::save_image(std::string File)
{
  QImage Image(Window->Initial_width,Window->Initial_height,QImage::Format_RGBA8888);

  makeCurrent();

  glReadPixels(0,0,Window->Initial_width,Window->Initial_height,GL_RGBA,GL_UNSIGNED_BYTE,Image.bits());
  Image=Image.mirrored();
  Image.save(QString::fromStdString(File),"PNG");
}

//HEA
// function to convert a position in device coordinates (left-handed) to GL camera coordinates (centered and scaled) and then
// to image coordinates (left-handed)
// For example, the device window size is (1000,800), the image has a size of 2000x4000, scale is 1.0.
// For device position (500,400) the GL coordinates will be (0,0) that correspond to (1000,2000) in the image

void _gl_widget_xmapslab::compute_position()
{
  // get the GL coordinates
  int xmax=int(roundf(float(Window_width)*Scale_factor/2.0f));
  int xmin=-xmax;
  int ymax=int(roundf(float(Window_height)*Scale_factor/2.0f));
  int ymin=-ymax;

  // we want to pass from device coordinates to GL camera coordinates
  // Selection_position is in device coordinates
  // Window width and height is the size of the window
  // GL_x=(GL_max_x-Gl_min_x)*(Selection_position_x - Device_min_x)/(Device_max_x-Device_min_x)+Gl_min_x

  int Pos_x=(xmax-xmin)*Selection_position_X/Window_width+xmin-Translation.x;
  int Pos_y=(ymax-ymin)*Selection_position_Y/Window_height+ymin+Translation.y; // para tener en cuenta la inversion de la Y se cambia el signo

  // now we have to convert the GL camera coordinates (right-handed and centered) to image coordinates (left-handed)

  Pos_x=Pos_x+Window->Initial_width/2;
  Pos_y=Pos_y+Window->Initial_height/2;

#ifdef STATISTIC_GRAPHS_ACTIVE
  _window_xmapslab_ns::_mode_chart Mode_chart=_window_xmapslab_ns::_mode_chart::MODE_CHART_INVALID;
  // check that the coordinates are inside the image
  if (Pos_x>=0 && Pos_x<Window->Initial_width && Pos_y>=0 && Pos_y<Window->Initial_height){  
    Mode_chart=_window_xmapslab_ns::_mode_chart::MODE_CHART_VALID;
  }

  Window->update_chart(Mode_chart, Pos_x,Pos_y);
#endif
}

//HEA

void _gl_widget_xmapslab::get_composed_image(cv::Mat *Composed_image1)
{
//  Get_composed_image=true;
//  Composed_image=Composed_image1;
  create_texture(Composed_image1);

  return;
}

//HEA

void _gl_widget_xmapslab::get_image_section(int &x1, int &y1, int &Width1, int &Height1)
{
  int Width=Window->Map_name_to_layer[Window->Vec_order_of_layers_by_name[0]].Layer->width();
  int Height=Window->Map_name_to_layer[Window->Vec_order_of_layers_by_name[0]].Layer->height();

  x1=Width/2+Start_box_position_X;
  y1=Height/2+Start_box_position_Y;
  Width1=int(fabs(End_box_position_X-Start_box_position_X));
  Height1=int(fabs(End_box_position_Y-Start_box_position_Y));
}
