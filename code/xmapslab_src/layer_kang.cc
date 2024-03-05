/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "layer_kang.h"
#include "window.h"

using namespace _layer_kang_ns;

/*************************************************************************/

_layer_kang::_layer_kang()
{
  Kernel_size_center=KERNEL_SIZE_CENTER_DEFAULT;
  Kernel_size_surround=KERNEL_SIZE_SURROUND_DEFAULT;
  Kernel_size_line_length=KERNEL_SIZE_LINE_LENGTH_DEFAULT;
  Ro=RO_DEFAULT;

  Layer_type=_layer_ns::_layer_type::LAYER_TYPE_KANG;

  Num_channels=1;

  _shaders Shader;

  static const GLchar * P0_vs[]={
  #include "shaders/kang1_sobel.vert"
  };

  static const GLchar * P0_fs[]={
  #include "shaders/kang1_sobel.frag"
  };

  // load the program
  Program1=Shader.load_shaders(P0_vs,P0_fs);
  if (Program1==0){
    QMessageBox::critical(Window, Window->tr("Error"),Window->tr("Error with the GPU program 'kang1_sobel'"));
    QApplication::quit();
    exit(-1);
//    QMessageBox Message;
//    Message.setText("Error with the GPU program kang1_sobel");
//    Message.exec();
//    exit(-1);
  }

  static const GLchar * P1_vs[]={
  #include "shaders/kang2_etf.vert"
  };

  static const GLchar * P1_fs[]={
  #include "shaders/kang2_etf.frag"
  };

  // load the program
  Program2=Shader.load_shaders(P1_vs,P1_fs);
  if (Program2==0){
    QMessageBox::critical(Window, Window->tr("Error"),Window->tr("Error with the GPU program 'kang2_etf'"));
    QApplication::quit();
    exit(-1);
//    QMessageBox Message;
//    Message.setText("Error with the GPU program kang2_etf");
//    Message.exec();
//    exit(-1);
  }

  static const GLchar * P2_vs[]={
  #include "shaders/kang3_line1.vert"
  };

  static const GLchar * P2_fs[]={
  #include "shaders/kang3_line1.frag"
  };

  Program3=Shader.load_shaders(P2_vs,P2_fs);
  if (Program3==0){
    QMessageBox::critical(Window, Window->tr("Error"),Window->tr("Error with the GPU program 'kang3_line1'"));
    QApplication::quit();
    exit(-1);
//    QMessageBox Message;
//    Message.setText("Error with the GPU kang3_line1");
//    Message.exec();
//    exit(-1);
  }

  static const GLchar * P3_vs[]={
  #include "shaders/kang4_line2.vert"
  };

  static const GLchar * P3_fs[]={
  #include "shaders/kang4_line2.frag"
  };

  // load the program
  Program4=Shader.load_shaders(P3_vs,P3_fs);
  if (Program4==0){
    QMessageBox::critical(Window, Window->tr("Error"),Window->tr("Error with the GPU program 'kang3_line1'"));
    QApplication::quit();
    exit(-1);
//    QMessageBox Message;
//    Message.setText("Error with the GPU program kang3_line1");
//    Message.exec();
//    exit(-1);
  }
}

/*************************************************************************/

void _layer_kang::reset_data()
{
  Kernel_size_center=KERNEL_SIZE_CENTER_DEFAULT;
  Kernel_size_surround=KERNEL_SIZE_SURROUND_DEFAULT;
  Kernel_size_line_length=KERNEL_SIZE_LINE_LENGTH_DEFAULT;
  Ro=RO_DEFAULT;
}

/*************************************************************************/

void _layer_kang::compute_gaussian(int Kernel_size,vector<float> &Vec_values)
{
  const int SMALL_GAUSSIAN_SIZE = 7;
  static const float small_gaussian_tab[][SMALL_GAUSSIAN_SIZE] =   {
          {1.f},
          {0.25f, 0.5f, 0.25f},
          {0.0625f, 0.25f, 0.375f, 0.25f, 0.0625f},
          {0.03125f, 0.109375f, 0.21875f, 0.28125f, 0.21875f, 0.109375f, 0.03125f}
      };

  if (Kernel_size<0) Kernel_size=1;
  if (Kernel_size%2==0) Kernel_size++;

  float sigma = 0.3*((Kernel_size-1)*0.5 - 1) + 0.8;

  float Aux1;
  float Total=0;

  for (int i=0;i<Kernel_size;i++){
    if (Kernel_size<8){
      Vec_values[i]=small_gaussian_tab[Kernel_size/2][i];
    }
    else{
      Aux1=float(i)-(float(Kernel_size-1)/2.0f);
      Aux1*=Aux1;
      Aux1=Aux1/(2*(sigma*sigma));
      Vec_values[i]=exp(-Aux1);
      Total+=Vec_values[i];
    }
  }

  if (Kernel_size>7){
    for (int i=0;i<Kernel_size;i++){
      Vec_values[i]/=Total;
    }
  }
}

/*************************************************************************/

void _layer_kang::update()
{
  // Size of the output
  if (Image==nullptr){
    Image=make_shared<cv::Mat>();
  }
  else{
    Image->release();
  }

  cv::Mat Mat;
  cv::cvtColor(*Vec_input_images[0].get(),Mat,cv::COLOR_BGRA2GRAY,1);

  uint Width1=Mat.cols;
  uint Height1=Mat.rows;

  int Num_points=Width1*Height1;

  /***********************************************************************************************/
  // First program

  // it is necessary to create a VAO
  glCreateVertexArrays(1,&VAO1);
  glBindVertexArray(VAO1);

  // Generate 1 buffers for the Input image
  glGenBuffers(1, &Input_image_gl);

  // The buffer will be uses as SSB
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, Input_image_gl);
  glBufferData(GL_SHADER_STORAGE_BUFFER,Num_points*sizeof(GLint),nullptr,GL_DYNAMIC_COPY);
  //glBindBufferBase(GL_SHADER_STORAGE_BUFFER,0,Input_image_gl);

  // Initialization of the SSB with Vertices data
  GLint *Map_image=static_cast<GLint *>(glMapNamedBufferRange(Input_image_gl,0,Num_points*sizeof(GLint),GL_MAP_WRITE_BIT));
  for (unsigned int i=0;i<Height1;i++){
    for (unsigned int j=0;j<Width1;j++){
      Map_image[i*Width1+j]=GLint(Mat.at<unsigned char>(i,j));//    Vec_images[0].pixelColor(j,i)).red();
    }
  }
  glUnmapNamedBuffer(Input_image_gl);

  // Generate 5 buffers for the ETF (2 for x e y and 1 for magnitud)
  GLuint Buffer_ETF_x[2];
  GLuint Buffer_ETF_y[2];
  GLuint Buffer_ETF_magnitude;

  glGenBuffers(2, &Buffer_ETF_x[0]);
  glGenBuffers(2, &Buffer_ETF_y[0]);
  glGenBuffers(1, &Buffer_ETF_magnitude);

  // The buffer will be uses as SSB
  for (unsigned int i=0;i<2;i++){
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, Buffer_ETF_x[i]);
    glBufferData(GL_SHADER_STORAGE_BUFFER,Num_points*sizeof(GLfloat),nullptr,GL_DYNAMIC_COPY);
  }

  for (unsigned int i=0;i<2;i++){
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, Buffer_ETF_y[i]);
    glBufferData(GL_SHADER_STORAGE_BUFFER,Num_points*sizeof(GLfloat),nullptr,GL_DYNAMIC_COPY);
  }

  glBindBuffer(GL_SHADER_STORAGE_BUFFER, Buffer_ETF_magnitude);
  glBufferData(GL_SHADER_STORAGE_BUFFER,Num_points*sizeof(GLfloat),nullptr,GL_DYNAMIC_COPY);

  std::vector<float> Vec_gaussian_center_aux;
  std::vector<float> Vec_gaussian_center;
  std::vector<float> Vec_gaussian_surround;
  std::vector<float> Difference_of_gaussians;
  std::vector<float> Gauss_line_lenght;

  Difference_of_gaussians.resize(Kernel_size_surround);
  Vec_gaussian_center.resize(Kernel_size_surround);

  Vec_gaussian_center_aux.resize(Kernel_size_center);
  compute_gaussian(Kernel_size_center,Vec_gaussian_center_aux);

  Vec_gaussian_surround.resize(Kernel_size_surround);
  compute_gaussian(Kernel_size_surround,Vec_gaussian_surround);

  for (unsigned int i=0;i<Vec_gaussian_surround.size();i++) Vec_gaussian_surround[i]*=Ro;

  // shift the values
  int Aux=(Kernel_size_surround-Kernel_size_center)/2;
  for (int i=Kernel_size_center-1;i>=0;i--) Vec_gaussian_center[i+Aux]=Vec_gaussian_center_aux[i];

  for (unsigned int i=0;i<Difference_of_gaussians.size();i++) Difference_of_gaussians[i]=Vec_gaussian_center[i]-Vec_gaussian_surround[i];

  Gauss_line_lenght.resize(Kernel_size_line_length);
  compute_gaussian(Kernel_size_line_length,Gauss_line_lenght);

  GLuint DoG_line;
  glGenBuffers(1, &DoG_line);
  // The buffer will be uses as SSB
  glBindBuffer(GL_SHADER_STORAGE_BUFFER, DoG_line);
  glBufferData(GL_SHADER_STORAGE_BUFFER,Kernel_size_surround*sizeof(GLfloat),nullptr,GL_DYNAMIC_COPY);
  // Initialization of the SSB with Vertices data
  GLfloat *Map_layerloat=static_cast<GLfloat *>(glMapNamedBufferRange(DoG_line,0,Kernel_size_surround*sizeof(GLfloat),GL_MAP_WRITE_BIT));
  for (unsigned int i=0;i<Kernel_size_surround;i++){
    Map_layerloat[i]=Difference_of_gaussians[i];
  }
  glUnmapNamedBuffer(DoG_line);

  GLuint Gaussian_line;
  glGenBuffers(1, &Gaussian_line);
  // The buffer will be uses as SSB
  glBindBuffer(GL_SHADER_STORAGE_BUFFER,Gaussian_line);
  glBufferData(GL_SHADER_STORAGE_BUFFER,Kernel_size_line_length*sizeof(GLfloat),nullptr,GL_DYNAMIC_COPY);
  // Initialization of the SSB with Vertices data
  Map_layerloat=static_cast<GLfloat *>(glMapNamedBufferRange(Gaussian_line,0,Kernel_size_line_length*sizeof(GLfloat),GL_MAP_WRITE_BIT));
  for (unsigned int i=0;i<Kernel_size_line_length;i++){
    Map_layerloat[i]=Gauss_line_lenght[i];
  }
  glUnmapNamedBuffer(Gaussian_line);

  GLuint Line_image;
  glGenBuffers(1, &Line_image);
  // The buffer will be uses as SSB
  glBindBuffer(GL_SHADER_STORAGE_BUFFER,Line_image);
  glBufferData(GL_SHADER_STORAGE_BUFFER,Num_points*sizeof(GLfloat),nullptr,GL_DYNAMIC_COPY);

  // Process -----------------------------------------

  glBindVertexArray(VAO1);

  /**************************************************/
  // Step1
  // Compute the sobel  ETF_0

  glUseProgram(Program1);

  glBindBufferBase(GL_SHADER_STORAGE_BUFFER,0,Input_image_gl); // x
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER,1,Buffer_ETF_x[0]); // x
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER,2,Buffer_ETF_y[0]); // y
  glBindBufferBase(GL_SHADER_STORAGE_BUFFER,3,Buffer_ETF_magnitude); // magnitude

  glUniform1i(glGetUniformLocation(Program1, "uWidth"), Width1);
  glUniform1i(glGetUniformLocation(Program1, "uHeight"), Height1);

  glDrawArrays(GL_POINTS, 0, Width1*Height1); // launch one thread for each pixel.

  // Unbind
  glBindVertexArray(0);
  glUseProgram(0);

  /**************************************************/
  // Step2
  // Compute the ETF

  uint Num_pass=3;
  int Radius=5;

  glUseProgram(Program2);

  glBindBufferBase(GL_SHADER_STORAGE_BUFFER,4,Buffer_ETF_magnitude); // magnitude

  glUniform1i(glGetUniformLocation(Program2, "uWidth"), Width1);
  glUniform1i(glGetUniformLocation(Program2, "uHeight"), Height1);
  glUniform1i(glGetUniformLocation(Program2, "Radius"), Radius);

  for (uint i=0;i<Num_pass;i++){
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER,0,Buffer_ETF_x[i%2]); // x
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER,1,Buffer_ETF_y[i%2]); // y
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER,2,Buffer_ETF_x[(i+1)%2]); // x
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER,3,Buffer_ETF_y[(i+1)%2]); // y

    glDrawArrays(GL_POINTS, 0, Width1*Height1); // launch one thread for each pixel.
  }

  // Unbind
  glUseProgram(0);

  int Num_line_pass=3;

  for (int i=0;i<Num_line_pass;i++){
    // part 3
    // compute the lines
    glUseProgram(Program3);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER,0,Buffer_ETF_x[Num_pass%2]); // x
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER,1,Buffer_ETF_y[Num_pass%2]); // y
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER,2,DoG_line); // magnitude
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER,3,Gaussian_line); // magnitude
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER,4,Line_image); // magnitude
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER,5,Input_image_gl); // x

    glUniform1i(glGetUniformLocation(Program3, "uWidth"), Width1);
    glUniform1i(glGetUniformLocation(Program3, "uHeight"), Height1);
    glUniform1i(glGetUniformLocation(Program3, "Kernel_surround"), Kernel_size_surround/2);
    glUniform1i(glGetUniformLocation(Program3, "Kernel_size_line_length"), Kernel_size_line_length/2);

    glDrawArrays(GL_POINTS, 0, Width1*Height1); // launch one thread for each pixel.

    // Unbind
    glUseProgram(0);

    // part 4
    // compute the lines
    glUseProgram(Program4);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER,4,Line_image);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER,5,Input_image_gl);

    glDrawArrays(GL_POINTS, 0, Width1*Height1); // launch one thread for each pixel.

    // Unbind
    glUseProgram(0);
  }

  glBindVertexArray(0);

  Map_layerloat=static_cast<GLfloat *>(glMapNamedBufferRange(Line_image,0,Num_points*sizeof(GLfloat),GL_MAP_READ_BIT));
  for (uint i=0;i<Height1;i++){
   for (uint j=0;j<Width1;j++){
     Mat.at<unsigned char>(i,j)=static_cast<unsigned char>(Map_layerloat[i*Width1+j]);
   }
  }
  glUnmapNamedBuffer(Input_image_gl);

  cv::cvtColor(Mat,*Image,cv::COLOR_GRAY2BGRA,4);

  // transparence per pixel
  if (Pixel_transparence){
    for (unsigned int Pos=0;Pos<Image->total();Pos++){
      cv::Vec4b &Pixel = Image->at<cv::Vec4b>(Pos);
      // if pixel is white
      if (Pixel[0]==255 && Pixel[1]==255 && Pixel[2]==255){
          // set alpha to zero:
          Pixel[3]=0;
      }
    }
  }
}

//void _layer_kang::update()
//{
//  if (Image==nullptr){
//    Image=make_shared<cv::Mat>();
//  }
//  else{
//    Image->release();
//  }

//  cv::Mat Mat;

//  cv::cvtColor(*Input_image,Mat,cv::COLOR_BGRA2GRAY,1);

//  cv::Mat Borders_kang_big,Borders_kang_small;

//  Borders_kang_big.create(Mat.rows,Mat.cols,CV_8U);
//  Borders_kang_small.create(Mat.rows,Mat.cols,CV_8U);
//  cv::GaussianBlur(Mat, Borders_kang_big,cv::Size(Big_gaussian_size,Big_gaussian_size),0,0);
//  cv::GaussianBlur(Mat, Borders_kang_small,cv::Size(Small_gaussian_size,Small_gaussian_size),0,0);
//  Borders_kang_big=Borders_kang_big-Borders_kang_small;
//  //invert
//  Borders_kang_big=255-Borders_kang_big;
//  cv::threshold(Borders_kang_big,Mat,Dog_threshold,255,cv::THRESH_BINARY);

//  cv::cvtColor(Mat,*Image,cv::COLOR_GRAY2BGRA,4);

//  // transparence per pixel
//  for (unsigned int Pos=0;Pos<Image->total();Pos++){
//    cv::Vec4b &Pixel = Image->at<cv::Vec4b>(Pos);
//    // if pixel is white
//    if (Pixel[0]==255 && Pixel[1]==255 && Pixel[2]==255){
//        // set alpha to zero:
//        Pixel[3]=0;
//    }
//  }
//}

/*************************************************************************/

_layer_kang_ui::_layer_kang_ui(_window *Window1, std::string Name1)
{
  Window=Window1;
  Name=Name1;
  Qtw_layer_kang=new _qtw_layer_kang(Window1,this,Name);
}

/*************************************************************************/

_layer_kang_ui::~_layer_kang_ui()
{
  delete Qtw_layer_kang;
}

/*************************************************************************/

void _layer_kang_ui::reset_data()
{
  _layer_kang::reset_data();
  Qtw_layer_kang->parameter1(parameter1());
//  Qtw_layer_kang->parameter4(parameter4());
//  Qtw_layer_kang->parameter5(parameter5());
//  Qtw_layer_kang->parameter6(parameter6());
  hide();
}

/*************************************************************************/

void _layer_kang_ui::show()
{
  Qtw_layer_kang->show();
}

/*************************************************************************/

void _layer_kang_ui::hide()
{
  Qtw_layer_kang->hide();
}

/*************************************************************************/

void *_layer_kang_ui::get_link()
{
  return Qtw_layer_kang->get_link();
}

/*************************************************************************/

void _layer_kang_ui::enable()
{
  Qtw_layer_kang->enable();
}

/*************************************************************************/

void _layer_kang_ui::disable()
{
  Qtw_layer_kang->disable();
}

/*************************************************************************/

//void _layer_kang_ui::read_parameters(std::map<std::string,std::string> &Parameters)
//{
//  if (Parameters["_INI_"]=="EDITOR"){// default parameters
//    parameter1(dog_SIZE_DEFAULT);
//    parameter2(dog_THRESHOLD1_DEFAULT);
//    parameter3(dog_THRESHOLD2_DEFAULT);
//  }
//  else{// Parameters from file or from initialised filter
//    try{
//      if (Parameters["kernel_size"]=="default") parameter1(dog_SIZE_DEFAULT);
//      else parameter1(atoi(Parameters["kernel_size"].c_str()));
//      if (Parameters["threshold1"]=="default") parameter2(dog_THRESHOLD1_DEFAULT);
//      else parameter2(atoi(Parameters["threshold1"].c_str()));
//      if (Parameters["threshold2"]=="default") parameter3(dog_THRESHOLD2_DEFAULT);
//      else parameter3(atoi(Parameters["threshold2"].c_str()));
//    }
//    catch (...) {
//      QMessageBox MsgBox;
//      MsgBox.setText("Error in the data of dog filter");
//      MsgBox.exec();
//      exit(-1);
//    }
//  }
//}

/*************************************************************************/

//void _layer_kang_ui::write_parameters(std::map<std::string,std::string> &Parameters)
//{
//  char Aux[100];

//  sprintf(Aux,"%d",parameter1());
//  Parameters["kernel_size"]=string(Aux);
//  sprintf(Aux,"%d",parameter2());
//  Parameters["threshold1"]=string(Aux);
//  sprintf(Aux,"%d",parameter3());
//  Parameters["threshold2"]=string(Aux);
//}

/*************************************************************************/

_qtw_layer_kang::_qtw_layer_kang(_window *Window1,_layer_kang_ui *Filter1,string Box_name)
{
  Window=Window1;
  Filter=Filter1;

  Group_box_main=new QGroupBox(tr(Box_name.c_str()));
  Group_box_main->setAlignment(Qt::AlignCenter);

  QVBoxLayout *Vertical_box_main=new QVBoxLayout;

  // Parameter1
  QGroupBox *Group_box_parameter1=new QGroupBox(tr(String_group_box_parameter1.c_str()));
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
  QGroupBox *Group_box_parameter2=new QGroupBox(tr(String_group_box_parameter2.c_str()));
  Group_box_parameter2->setAlignment(Qt::AlignCenter);

  QHBoxLayout *Horizontal_box_parameter2=new QHBoxLayout;
  Horizontal_box_parameter2->setAlignment(Qt::AlignCenter);

  Checkbox_parameter2=new QCheckBox;

  Horizontal_box_parameter2->addWidget(Checkbox_parameter2);

  Group_box_parameter2->setLayout(Horizontal_box_parameter2);

  connect(Checkbox_parameter2, SIGNAL(stateChanged(int)),this,SLOT(parameter2_slot(int)));

//  // Parameter 4
//  Group_box_parameter4=new QGroupBox(tr(String_group_box_parameter4.c_str()));
//  Group_box_parameter4->setAlignment(Qt::AlignCenter);

//  QGridLayout *Grid_parameter4 = new QGridLayout;

//  QLabel *Label_parameter4_min= new QLabel(tr(String_label_parameter4_min.c_str()));
//  QLabel *Label_parameter4_max= new QLabel(tr(String_label_parameter4_max.c_str()));

//  Line_edit_parameter4=new QLineEdit();
//  Line_edit_parameter4->setAlignment(Qt::AlignRight);
//  Line_edit_parameter4->setReadOnly(true);
//  Line_edit_parameter4->setEnabled(false);
//  Line_edit_parameter4->setToolTip(tr(String_label_parameter4_tooltip.c_str()));

//  Slider_parameter4 = new QSlider(Qt::Horizontal);
//  Slider_parameter4->setRange(Parameter4_min_value,Parameter4_max_value);
//  Slider_parameter4->setSingleStep(Parameter4_single_step);
//  Slider_parameter4->setPageStep(Parameter4_page_step);
//  Slider_parameter4->setTickInterval(Parameter4_tick_interval);
//  Slider_parameter4->setTickPosition(QSlider::TicksRight);
//  Slider_parameter4->setTracking(Parameter4_set_tracking);
//  Slider_parameter4->setToolTip(tr(String_parameter4_tooltip.c_str()));

//  parameter4(Filter->parameter4());

//  Grid_parameter4->addWidget(Line_edit_parameter4,0,1,Qt::AlignCenter);
//  Grid_parameter4->addWidget(Label_parameter4_min,1,0,Qt::AlignRight);
//  Grid_parameter4->addWidget(Slider_parameter4,1,1);
//  Grid_parameter4->addWidget(Label_parameter4_max,1,4,Qt::AlignLeft);

//  Group_box_parameter4->setLayout(Grid_parameter4);

//  connect(Slider_parameter4, SIGNAL(valueChanged(int)),this,SLOT(parameter4_slot(int)));

//  // parameter 5
//  Group_box_parameter5=new QGroupBox(tr(String_group_box_parameter5.c_str()));
//  Group_box_parameter5->setAlignment(Qt::AlignCenter);

//  QGridLayout *Grid_parameter5 = new QGridLayout;

//  QLabel *Label_parameter5_min= new QLabel(tr(String_label_parameter5_min.c_str()));
//  QLabel *Label_parameter5_max= new QLabel(tr(String_label_parameter5_max.c_str()));

//  Line_edit_parameter5=new QLineEdit();
//  Line_edit_parameter5->setAlignment(Qt::AlignRight);
//  Line_edit_parameter5->setReadOnly(true);
//  Line_edit_parameter5->setEnabled(false);
//  Line_edit_parameter5->setToolTip(tr(String_label_parameter5_tooltip.c_str()));

//  Slider_parameter5 = new QSlider(Qt::Horizontal);
//  Slider_parameter5->setRange(Parameter5_min_value,Parameter5_max_value);
//  Slider_parameter5->setSingleStep(Parameter5_single_step);
//  Slider_parameter5->setPageStep(Parameter5_page_step);
//  Slider_parameter5->setTickInterval(Parameter5_tick_interval);
//  Slider_parameter5->setTickPosition(QSlider::TicksRight);
//  Slider_parameter5->setTracking(Parameter5_set_tracking);
//  Slider_parameter5->setToolTip(tr(String_parameter5_slider_tooltip.c_str()));

//  parameter5(Filter->parameter5());

//  Grid_parameter5->addWidget(Line_edit_parameter5,0,1,Qt::AlignCenter);
//  Grid_parameter5->addWidget(Label_parameter5_min,1,0,Qt::AlignRight);
//  Grid_parameter5->addWidget(Slider_parameter5,1,1);
//  Grid_parameter5->addWidget(Label_parameter5_max,1,2,Qt::AlignLeft);

//  Group_box_parameter5->setLayout(Grid_parameter5);

//  connect(Slider_parameter5, SIGNAL(valueChanged(int)),this,SLOT(parameter5_slot(int)));

//  // parameter 6
//  Group_box_parameter6=new QGroupBox(tr(String_group_box_parameter6.c_str()));
//  Group_box_parameter6->setAlignment(Qt::AlignCenter);

//  QGridLayout *Grid_parameter6 = new QGridLayout;

//  QLabel *Label_parameter6_min= new QLabel(tr(String_label_parameter6_min.c_str()));
//  QLabel *Label_parameter6_max= new QLabel(tr(String_label_parameter6_max.c_str()));

//  Line_edit_parameter6=new QLineEdit();
//  Line_edit_parameter6->setAlignment(Qt::AlignRight);
//  Line_edit_parameter6->setReadOnly(true);
//  Line_edit_parameter6->setEnabled(false);
//  Line_edit_parameter6->setToolTip(tr(String_label_parameter6_tooltip.c_str()));

//  Slider_parameter6 = new QSlider(Qt::Horizontal);
//  Slider_parameter6->setRange(Parameter6_min_value,Parameter6_max_value);
//  Slider_parameter6->setSingleStep(Parameter6_single_step);
//  Slider_parameter6->setPageStep(Parameter6_page_step);
//  Slider_parameter6->setTickInterval(Parameter6_tick_interval);
//  Slider_parameter6->setTickPosition(QSlider::TicksRight);
//  Slider_parameter6->setTracking(Parameter6_set_tracking);
//  Slider_parameter6->setToolTip(tr(String_parameter6_slider_tooltip.c_str()));

//  parameter6(Filter->parameter6());

//  Grid_parameter6->addWidget(Line_edit_parameter6,0,1,Qt::AlignCenter);
//  Grid_parameter6->addWidget(Label_parameter6_min,1,0,Qt::AlignRight);
//  Grid_parameter6->addWidget(Slider_parameter6,1,1);
//  Grid_parameter6->addWidget(Label_parameter6_max,1,2,Qt::AlignLeft);

//  Group_box_parameter6->setLayout(Grid_parameter6);

//  connect(Slider_parameter6, SIGNAL(valueChanged(int)),this,SLOT(parameter6_slot(int)));

  //
  Vertical_box_main->addWidget(Group_box_parameter1);
  Vertical_box_main->addWidget(Group_box_parameter2);

//  Vertical_box_main->addWidget(Group_box_parameter4);
//  Vertical_box_main->addWidget(Group_box_parameter5);
//  Vertical_box_main->addWidget(Group_box_parameter6);

  Group_box_main->setLayout(Vertical_box_main);
}

/*************************************************************************/

void _qtw_layer_kang::parameter1(int Value)
{
  QString Str;

  Str=Str.number(Value);
  Line_edit_parameter1->setText(Str);
  Slider_parameter1->blockSignals(true);
  Slider_parameter1->setValue(Value);
  Slider_parameter1->blockSignals(false);
}

/*************************************************************************/

void _qtw_layer_kang::parameter2(int Value)
{
  QString Str;

  Slider_parameter1->blockSignals(true);
  if (Value==0) Checkbox_parameter2->setCheckState(Qt::Unchecked);
  else Checkbox_parameter2->setCheckState(Qt::Checked);
  Slider_parameter1->blockSignals(false);
}

/*************************************************************************/

//void _qtw_layer_kang::parameter4(int Value)
//{
//  QString Str;

//  Str=Str.number(Value);
//  Line_edit_parameter4->setText(Str);
//  Slider_parameter4->blockSignals(true);
//  Slider_parameter4->setValue(Value);
//  Slider_parameter4->blockSignals(false);
//}

/*************************************************************************/

//void _qtw_layer_kang::parameter5(int Value)
//{
//  QString Str;

//  Str=Str.number(Value);
//  Line_edit_parameter5->setText(Str);
//  Slider_parameter5->blockSignals(true);
//  Slider_parameter5->setValue(Value);
//  Slider_parameter5->blockSignals(false);
//}

/*************************************************************************/

//void _qtw_layer_kang::parameter6(int Value)
//{
//  QString Str;

//  Str=Str.number(Value);
//  Line_edit_parameter6->setText(Str);
//  Slider_parameter6->blockSignals(true);
//  Slider_parameter6->setValue(Value);
//  Slider_parameter6->blockSignals(false);
//}

/*************************************************************************/

void _qtw_layer_kang::parameter1_slot(int Value)
{
  QString Str;
  char Aux[100];

  sprintf(Aux,"%2d",Value);
  Str=Aux;
  Line_edit_parameter1->setText(Str);
  Filter->parameter1(Value);
  Window->update_layer(Filter->name());
}

/*************************************************************************/

void _qtw_layer_kang::parameter2_slot(int Value)
{

  if (Value==Qt::Unchecked) Value=0;
  else Value=1;

  Filter->parameter2(Value);
  Window->update_layer(Filter->name());
}

/*************************************************************************/

//void _qtw_layer_kang::parameter4_slot(int Value)
//{
//  QString Str;
//  char Aux[100];

//  sprintf(Aux,"%2d",Value);
//  Str=Aux;
//  Line_edit_parameter4->setText(Str);
//  Filter->parameter4(Value);
//  Window->update_layer(Filter->name());
//}

/*************************************************************************/

//void _qtw_layer_kang::parameter5_slot(int Value)
//{
//  QString Str;
//  char Aux[100];

//  if (Value%2==0) Value++;
//  sprintf(Aux,"%2d",Value);
//  Str=Aux;
//  Line_edit_parameter5->setText(Str);
//  Filter->parameter5(Value);
//  Window->update_layer(Filter->name());
//}

/*************************************************************************/

//void _qtw_layer_kang::parameter6_slot(int Value)
//{
//  QString Str;
//  char Aux[100];

//  if (Value%2==0) Value++;
//  sprintf(Aux,"%2d",Value);
//  Str=Aux;
//  Line_edit_parameter6->setText(Str);
//  Filter->parameter6(Value);
//  Window->update_layer(Filter->name());
//}
