/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under Apache 2 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "layer_map_distance.h"
#include "window_xmapslab.h"

using namespace _layer_map_distance_ns;

/*************************************************************************/

_layer_map_distance::_layer_map_distance()
{
  Layer_type=_layer_xmapslab_ns::_layer_type::LAYER_TYPE_MAP_DISTANCE;

  // GPU
  // load shaders
  _shaders Shader;

  static const GLchar * P0_vs[]={
  #include "distance.vert"
  };

  static const GLchar * P0_fs[]={
  #include "distance.frag"
  };

  Program0=Shader.load_shaders(P0_vs,P0_fs);
  if (Program0==0){
    QMessageBox::critical(Window, Window->tr("Error"),Window->tr("Error with the GPU program 'distance'"));
    QApplication::quit();
    exit(-1);
  }
}

/*************************************************************************/

_layer_map_distance::~_layer_map_distance()
{
#ifdef DEBUG_XML
  cout << "terminando layer element" << endl;
#endif
}

/*************************************************************************/

void _layer_map_distance::create_buffers()
{
  Vec_color.resize(Vec_element_data.size());

  shared_ptr<cv::Mat> Image_normalized=Vec_input_images[0];

  // We are going to take the color from the input image (normalized) that correspond to each sample position
//  int Pos=0;
  for (unsigned int i=0;i<Vec_element_data.size();i++){
    // get the color OpenCV uses a left hand CS
    Vec_color[i]=Image_normalized->at<cv::Vec4f>(Vec_element_data[i].y,Vec_element_data[i].x);
  }

  // create the textures for the input images
  // At least one VAO
  glCreateVertexArrays(1,&VAO1);
  glBindVertexArray(VAO1);

  // the buffer for the normalized image. It is used as a texture
  if (Tex_input_image_normalized>0) glDeleteTextures(1,&Tex_input_image_normalized);
  glCreateTextures(GL_TEXTURE_2D,1,&Tex_input_image_normalized);
  glTextureStorage2D(Tex_input_image_normalized,1,GL_RGBA32F,Width,Height); //RGBA
  glTextureSubImage2D(Tex_input_image_normalized,0,0,0,Width,Height,GL_RGBA,GL_FLOAT,&Image_normalized->data[0]);

  // The buffer for the result. A float (it is saved in the red channedl)
  if (Tex_image_result>0) glDeleteTextures(1,&Tex_image_result);
  glCreateTextures(GL_TEXTURE_2D,1,&Tex_image_result);
  glTextureStorage2D(Tex_image_result,1,GL_R32F,Width,Height);

  // The buffer for the positions data (x,y,value). It will be a SSB
  glGenBuffers(1, &Element_data);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER,Element_data);
  glBufferData(GL_SHADER_STORAGE_BUFFER,Vec_element_data.size()*3*sizeof(GLfloat),&Vec_element_data[0],GL_STATIC_DRAW);

  // The buffer for the color of the input data. It will be a SSB
  glGenBuffers(1, &Colors);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER,Colors);
  glBufferData(GL_SHADER_STORAGE_BUFFER,Vec_color.size()*4*sizeof(GLfloat),&Vec_color[0],GL_STATIC_DRAW);

  // The buffer for the valid positions
  glGenBuffers(1, &Valid_positions);
  glBindBuffer(GL_SHADER_STORAGE_BUFFER,Valid_positions);
  glBufferData(GL_SHADER_STORAGE_BUFFER,Vec_active_positions.size()*sizeof(GLint),&Vec_active_positions[0],GL_STATIC_DRAW);

  glBindVertexArray(0);
}

/*************************************************************************/

void _layer_map_distance::update_map()
{
  // the computation of the distances is made only one time
  if (Computed==false){
    Computed=true;

    Window->GL_widget->makeCurrent();

    create_buffers();

    glBindVertexArray(VAO1);

    // program to add 1 to the color value to remove the 0 values (for the log operation)
    glUseProgram(Program0);
    glBindImageTexture(0,Tex_input_image_normalized,0,GL_FALSE,0,GL_READ_WRITE,GL_RGBA32F);
    glBindImageTexture(1,Tex_image_result,0,GL_FALSE,0,GL_READ_WRITE,GL_R32F);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER,0,Element_data);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER,1,Valid_positions);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER,2,Colors);

    glUniform1i(0,Width);
    glUniform1i(1,Height);
    glUniform1i(2,int(Vec_element_data.size()));

    // Probe
    glUniform1i(3,Probe);
    // Use colors
    glUniform1i(4,int(Use_colors[0]));
    glUniform1i(5,int(Use_colors[1]));
    glUniform1i(6,int(Use_colors[2]));
    // Use positions
    glUniform1i(7,int(Use_positions[0]));
    glUniform1i(8,int(Use_positions[1]));

    // size of the Diagonal
    float Diagonal=0;
    for (unsigned int i=0;i<Use_colors.size();i++){
      if (Use_colors[i]==true) Diagonal=Diagonal+1.0f;
    }

    // X
    if (Use_positions[0]==true){
      if (Position_normalization_type==_layer_map_distance_ns::_position_normalization_type::POSITION_NORMALIZATION_HOMOGENEOUS){
        Diagonal=Diagonal+1.0f;
      }
      else{
        if (Width>=Height) Diagonal=Diagonal+1.0f;
        else Diagonal=Diagonal+powf(float(Width)/float(Height),2); // the shape is not square so it is not a hypercube
      }
    }

    // Y
    if (Use_positions[1]==true){
      if (Position_normalization_type==_layer_map_distance_ns::_position_normalization_type::POSITION_NORMALIZATION_HOMOGENEOUS){
        Diagonal=Diagonal+1.0f;
      }
      else{
        if (Height>Width) Diagonal=Diagonal+1.0f;
        else Diagonal=Diagonal+powf(float(Height)/float(Width),2); // the shape is not square so it is not a hypercube
      }
    }

    // diagonal
    glUniform1f(9,sqrt(Diagonal));

    // color model
    glUniform1i(10,int(Color_model));

    // normaliaztion
    glUniform1i(11,Normalization);

    // position normalization
    glUniform1i(12,int(Position_normalization_type));

    //
    glViewport(0,0,Width,Height);
    // draw a point for each pixel
    glDrawArrays(GL_POINTS, 0, Width*Height);

//    std::vector<GLfloat> Data;
//    Data.resize(Width*Height*4*sizeof(GLfloat));

    // read the result
    if (Result_floats_image==nullptr){
      Result_floats_image=make_shared<cv::Mat>();
      Result_floats_image->create(Height,Width,CV_32FC1);
    }

    glBindTexture(GL_TEXTURE_2D,Tex_image_result);
    glGetTexImage(GL_TEXTURE_2D,0,GL_RED,GL_FLOAT,&Result_floats_image->data[0]);

    // to check if there are transparent pixels and put the pattern
//    cv::Vec4f Pixel;
//    for (int Row=0;Row<Vec_input_images[0]->rows;Row++){
//      for (int Col=0;Col<Vec_input_images[0]->cols;Col++){
//        Pixel=Vec_input_images[0]->at<cv::Vec4f>(Row,Col);
//        if (Pixel[3]==0.0f){
//          if (Col%20<10 && Row%20<10) Result_floats_image->at<float>(Row,Col)=1.0f;
//          else Result_floats_image->at<float>(Row,Col)=0.0f;
//        }
//      }
//    }

//    for (int Row=500;Row<501;Row++){
//      for (int Col=0;Col<50;Col++){
//        std::cout << "Row=" << Row << " Col=" << Col << " " << Result_floats_image->at<float>(Row,Col) << std::endl;
//      }
//    }

    glUseProgram(0);
    glBindVertexArray(0);

    glDeleteTextures(1,&Tex_input_image_normalized);
    glDeleteTextures(1,&Tex_image_result);
    glDeleteBuffers(1,&Element_data);
    glDeleteBuffers(1,&Valid_positions);
    glDeleteBuffers(1,&Colors);

    glDeleteProgram(Program0);
    glDeleteVertexArrays(1,&VAO1);

    apply_colormap();
    apply_color_mixing();
  }
  else{
    // only update if necessary
    if (Colormap_changed){
      Colormap_changed=false;
      apply_colormap();
    }
    if (Color_mixing_changed){
      Color_mixing_changed=false;
      apply_color_mixing();
    }
  }
}

/*************************************************************************/

void _layer_map_distance::update()
{
  update_map();
}

/*************************************************************************/
// Returns the normalized value for a position. This is for the charts

float _layer_map_distance::get_value(int Col,int Row)
{
//  return(float(Result_gray_image->at<unsigned char>(Row,Col))/255.0f);
  return(Result_floats_image->at<float>(Row,Col));
}


/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

/*************************************************************************/

_layer_map_distance_ui::_layer_map_distance_ui(_window_xmapslab *Window1, std::string Name1)
{
  Window=Window1;
  Name=Name1;
  Qtw_layer_map_distance_a=new _qtw_layer_map_distance(Window1,this,Name);
}

/*************************************************************************/

_layer_map_distance_ui::~_layer_map_distance_ui()
{
  delete Qtw_layer_map_distance_a;
}

/*************************************************************************/

void _layer_map_distance_ui::reset_data()
{
  _layer_map_distance::reset_data();
  Qtw_layer_map_distance_a->parameter1(parameter1());
  hide();
}

/*************************************************************************/

void _layer_map_distance_ui::show()
{
  Qtw_layer_map_distance_a->show();
}

/*************************************************************************/

void _layer_map_distance_ui::hide()
{
  Qtw_layer_map_distance_a->hide();
}

/*************************************************************************/

void *_layer_map_distance_ui::get_link()
{
  return Qtw_layer_map_distance_a->get_link();
}

/*************************************************************************/

void _layer_map_distance_ui::enable()
{
  Qtw_layer_map_distance_a->enable();
}

/*************************************************************************/

void _layer_map_distance_ui::disable()
{
  Qtw_layer_map_distance_a->disable();
}

/*************************************************************************/

void _layer_map_distance_ui::parameter1_ui(float Value)
{
  Qtw_layer_map_distance_a->parameter1(int(Value*255.0f));
}

/*************************************************************************/

void _layer_map_distance_ui::parameter2_ui(float Value)
{
  Qtw_layer_map_distance_a->parameter2(int(Value*255.0f));
}

/*************************************************************************/

void _layer_map_distance_ui::parameter3_ui(float Value)
{
  Qtw_layer_map_distance_a->parameter3(int(Value*255.0f));
}

/*************************************************************************/

void _layer_map_distance_ui::parameter4_ui(int Value)
{
  Qtw_layer_map_distance_a->parameter4(Value);
}

/*************************************************************************/

void _layer_map_distance_ui::data_type_print(_palette_data_ns::_data_type_print Data_type_print1)
{
  Data_type_print=Data_type_print1;
  Qtw_layer_map_distance_a->parameter4(int(Data_type_print1));
}

/*************************************************************************/

_qtw_layer_map_distance::_qtw_layer_map_distance(_window_xmapslab *Window1,_layer_map_distance_ui *Filter1,std::string Box_name)
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

//  Line_edit_parameter1=new QLineEdit();
//  Line_edit_parameter1->setAlignment(Qt::AlignRight);
//  Line_edit_parameter1->setReadOnly(true);
//  Line_edit_parameter1->setEnabled(false);
//  Line_edit_parameter1->setToolTip(tr(String_label_parameter1_tooltip.c_str()));

  Slider_parameter1 = new QSlider(Qt::Horizontal);
  Slider_parameter1->setRange(Parameter1_min_value,Parameter1_max_value);
  Slider_parameter1->setSingleStep(Parameter1_single_step);
  Slider_parameter1->setPageStep(Parameter1_page_step);
  Slider_parameter1->setTickInterval(Parameter1_tick_interval);
  Slider_parameter1->setTickPosition(QSlider::TicksRight);
  Slider_parameter1->setTracking(Parameter1_set_tracking);
  Slider_parameter1->setToolTip(tr(String_parameter1_tooltip.c_str()));

  parameter1(Filter->parameter1());

//  Grid_parameter1->addWidget(Line_edit_parameter1,0,1,Qt::AlignCenter);
  Grid_parameter1->addWidget(Label_parameter1_min,0,0,Qt::AlignRight);
  Grid_parameter1->addWidget(Slider_parameter1,0,1);
  Grid_parameter1->addWidget(Label_parameter1_max,0,2,Qt::AlignLeft);

  Group_box_parameter1->setLayout(Grid_parameter1);

  connect(Slider_parameter1, SIGNAL(valueChanged(int)),this,SLOT(parameter1_slot(int)));

  // Parameter2
  QGroupBox *Group_box_parameter2=new QGroupBox(tr(String_group_box_parameter2.c_str()));
  Group_box_parameter2->setAlignment(Qt::AlignCenter);

  QGridLayout *Grid_parameter2 = new QGridLayout;

  QLabel *Label_parameter2_title= new QLabel(tr(String_label_parameter2_title.c_str()));
  QLabel *Label_parameter2_min= new QLabel(tr(String_label_parameter2_min.c_str()));
  QLabel *Label_parameter2_max= new QLabel(tr(String_label_parameter2_max.c_str()));

  QLabel *Label_parameter3_title= new QLabel(tr(String_label_parameter3_title.c_str()));
  QLabel *Label_parameter3_min= new QLabel(tr(String_label_parameter3_min.c_str()));
  QLabel *Label_parameter3_max= new QLabel(tr(String_label_parameter3_max.c_str()));

  Slider_parameter2 = new QSlider(Qt::Horizontal);
  Slider_parameter2->setRange(Parameter2_min_value,Parameter2_max_value);
  Slider_parameter2->setSingleStep(Parameter2_single_step);
  Slider_parameter2->setPageStep(Parameter2_page_step);
  Slider_parameter2->setTickInterval(Parameter2_tick_interval);
  Slider_parameter2->setTickPosition(QSlider::TicksRight);
  Slider_parameter2->setTracking(Parameter2_set_tracking);
  Slider_parameter2->setToolTip(tr(String_parameter2_tooltip.c_str()));

  parameter2(Filter->parameter2());

  // parameter 3
  Slider_parameter3 = new QSlider(Qt::Horizontal);
  Slider_parameter3->setRange(Parameter3_min_value,Parameter3_max_value);
  Slider_parameter3->setSingleStep(Parameter3_single_step);
  Slider_parameter3->setPageStep(Parameter3_page_step);
  Slider_parameter3->setTickInterval(Parameter3_tick_interval);
  Slider_parameter3->setTickPosition(QSlider::TicksRight);
  Slider_parameter3->setTracking(Parameter3_set_tracking);
  Slider_parameter3->setToolTip(tr(String_parameter3_tooltip.c_str()));

  parameter3(Filter->parameter3());

  Grid_parameter2->addWidget(Label_parameter2_title,0,1,Qt::AlignCenter);
  Grid_parameter2->addWidget(Label_parameter2_min,1,0,Qt::AlignRight);
  Grid_parameter2->addWidget(Slider_parameter2,1,1);
  Grid_parameter2->addWidget(Label_parameter2_max,1,2,Qt::AlignLeft);

  Grid_parameter2->addWidget(Label_parameter3_title,2,1,Qt::AlignCenter);
  Grid_parameter2->addWidget(Label_parameter3_min,3,0,Qt::AlignRight);
  Grid_parameter2->addWidget(Slider_parameter3,3,1);
  Grid_parameter2->addWidget(Label_parameter3_max,3,2,Qt::AlignLeft);

  Group_box_parameter2->setLayout(Grid_parameter2);

  connect(Slider_parameter2, SIGNAL(valueChanged(int)),this,SLOT(parameter2_slot(int)));
  connect(Slider_parameter3, SIGNAL(valueChanged(int)),this,SLOT(parameter3_slot(int)));

  // Parameter 4
  QFrame *Frame_parameter4=new QFrame;
  Frame_parameter4->setFrameStyle(QFrame::Panel);

  QGridLayout *Grid_parameter4=new QGridLayout;

  QLabel *Label_operations1=new QLabel(tr(String_group_box_parameter4.c_str()));

  Combobox_parameter4 = new QComboBox;
  for (unsigned int i=0;i<_palette_data_ns::Vec_names_data_type_print.size();i++){
    Combobox_parameter4->addItem(_palette_data_ns::Vec_names_data_type_print[i]);
  }
  Combobox_parameter4->setCurrentIndex(Filter->parameter4());

  Grid_parameter4->addWidget(Label_operations1,0,0,Qt::AlignRight);
  Grid_parameter4->addWidget(Combobox_parameter4,0,1,Qt::AlignLeft);;

  Frame_parameter4->setLayout(Grid_parameter4);

  connect(Combobox_parameter4, SIGNAL(activated(int)), this,SLOT(parameter4_slot(int)));

  //
  Vertical_box_main->addWidget(Group_box_parameter1);
  Vertical_box_main->addWidget(Group_box_parameter2);
  Vertical_box_main->addWidget(Frame_parameter4);

  Group_box_main->setLayout(Vertical_box_main);
}

/*************************************************************************/

void _qtw_layer_map_distance::parameter1(int Value)
{
  Slider_parameter1->blockSignals(true);
  Slider_parameter1->setValue(Value);
  Slider_parameter1->blockSignals(false);
}

/*************************************************************************/

void _qtw_layer_map_distance::parameter2(int Value)
{
  Slider_parameter2->blockSignals(true);
  Slider_parameter2->setValue(Value);
  Slider_parameter2->blockSignals(false);
}

/*************************************************************************/

void _qtw_layer_map_distance::parameter3(int Value)
{
  Slider_parameter3->blockSignals(true);
  Slider_parameter3->setValue(Value);
  Slider_parameter3->blockSignals(false);
}

/*************************************************************************/

void _qtw_layer_map_distance::parameter4(int Value)
{
  Combobox_parameter4->blockSignals(true);
  Combobox_parameter4->setCurrentIndex(Value);
  Combobox_parameter4->blockSignals(false);
}

/*************************************************************************/

void _qtw_layer_map_distance::parameter1_slot(int Value)
{
  Filter->parameter1(Value);
  Window->update_layer(Filter->name());
}

/*************************************************************************/

void _qtw_layer_map_distance::parameter2_slot(int Value)
{
  Filter->parameter2(Value);
  Window->update_layer(Filter->name());
}

/*************************************************************************/

void _qtw_layer_map_distance::parameter3_slot(int Value)
{
  Filter->parameter3(Value);
  Window->update_layer(Filter->name());
}

/*************************************************************************/

void _qtw_layer_map_distance::parameter4_slot(int Value)
{
  Filter->parameter4(Value);
  Window->update_color_bar_data_type_print(Value);
}
