/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "layer_map_triangulation.h"
#include "window_xmapslab.h"

using namespace _layer_map_triangulation_ns;

/*************************************************************************/

_layer_map_triangulation::_layer_map_triangulation()
{
  Layer_type=_layer_xmapslab_ns::_layer_type::LAYER_TYPE_MAP_TRIANGULATION;

  // GPU
  // load shaders
  _shaders Shader;

  static const GLchar * P0_vs[]={
  #include "triangulation.vert"
  };

  static const GLchar * P0_fs[]={
  #include "triangulation.frag"
  };

  Program0=Shader.load_shaders(P0_vs,P0_fs);
  if (Program0==0){
    QMessageBox::critical(Window, Window->tr("Error"),Window->tr("Error with the GPU program 'triangulation'"));
    QApplication::quit();
    exit(-1);
  }
}

/*************************************************************************/

_layer_map_triangulation::~_layer_map_triangulation()
{
#ifdef DEBUG_XML
  cout << "terminando layer element" << endl;
#endif
}

/*************************************************************************/

void _layer_map_triangulation::create_buffers()
{
  Vec_color.resize(Vec_element_data.size());

  std::vector<_vertex3f> Vertices_drawarray;
  std::vector<_vertex3f> Vertices_color_drawarray;

  // for each triangle, put the coordinates and the color.
  // for the color, we are goint use only the red channel
  Num_vertices=Triangles.size()*3;

  Vertices_drawarray.resize(Num_vertices);
  Vertices_color_drawarray.resize(Num_vertices);

  for (unsigned int i=0;i<Triangles.size();i++){
    // P1
    Vertices_drawarray[i*3].x=Vec_element_data[Triangles[i].P1].x;
    Vertices_drawarray[i*3].y=Vec_element_data[Triangles[i].P1].y;

    Vertices_color_drawarray[i*3].r=Vec_element_data[Triangles[i].P1].Value; // the value
    // P2
    Vertices_drawarray[i*3+1].x=Vec_element_data[Triangles[i].P2].x;
    Vertices_drawarray[i*3+1].y=Vec_element_data[Triangles[i].P2].y;

    Vertices_color_drawarray[i*3+1].r=Vec_element_data[Triangles[i].P2].Value;
    // P3
    Vertices_drawarray[i*3+2].x=Vec_element_data[Triangles[i].P3].x;
    Vertices_drawarray[i*3+2].y=Vec_element_data[Triangles[i].P3].y;

    Vertices_color_drawarray[i*3+2].r=Vec_element_data[Triangles[i].P3].Value;
  }

  // create the textures for the input images
  // At least one VAO
  glCreateVertexArrays(1,&VAO1);
  glBindVertexArray(VAO1);

  // Vertices
  glCreateBuffers(1,&VBO_vertices);
  glNamedBufferStorage(VBO_vertices,Vertices_drawarray.size()*3*sizeof(GLfloat),nullptr,GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
  glVertexArrayVertexBuffer(VAO1,1,VBO_vertices,0,3*sizeof(GLfloat)); // 0,VBO
  glVertexArrayAttribFormat(VAO1,1,3,GL_FLOAT,GL_FALSE,0);
  glVertexArrayAttribBinding(VAO1,1,1);// 1,0)
  glEnableVertexArrayAttrib(VAO1,1);
  // Color
  glCreateBuffers(1,&VBO_vertices_colors);
  glNamedBufferStorage(VBO_vertices_colors,Vertices_color_drawarray.size()*3*sizeof(float),nullptr,GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
  glVertexArrayVertexBuffer(VAO1,2,VBO_vertices_colors,0,3*sizeof(float)); // 1,VBO
  glVertexArrayAttribFormat(VAO1,2,3,GL_FLOAT,GL_FALSE,0);
  glVertexArrayAttribBinding(VAO1,2,2); //2,1)
  glEnableVertexArrayAttrib(VAO1,2);

  // Put data
  // vertices
  glNamedBufferSubData(VBO_vertices,0,Vertices_drawarray.size()*3*sizeof(GLfloat),&Vertices_drawarray[0]);
  // colors
  glNamedBufferSubData(VBO_vertices_colors,0,Vertices_color_drawarray.size()*3*sizeof(GLfloat),&Vertices_color_drawarray[0]);

  // The buffer for the result. A float (it is saved in the red channedl)
  if (Tex_image_result>0) glDeleteTextures(1,&Tex_image_result);
  glCreateTextures(GL_TEXTURE_2D,1,&Tex_image_result);
  glTextureStorage2D(Tex_image_result,1,GL_R32F,Width,Height);

  glBindVertexArray(0);
}

/*************************************************************************/

void _layer_map_triangulation::update_map()
{
  // the computation of the distances is made only one time
  if (Computed==false){
    Computed=true;

    Window->GL_widget->makeCurrent();

    create_buffers();

    GLuint FBO;

    // Frame Buffer Object to do the off-screen rendering
    glGenFramebuffers(1,&FBO);
    glBindFramebuffer(GL_FRAMEBUFFER,FBO);

    // Attatchment of the textures to the FBO
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,Tex_image_result,0);

    // OpenGL will draw to these buffers (only one in this case)
    static const GLenum Draw_buffers[]={GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1,Draw_buffers);

    glBindVertexArray(VAO1);
    glUseProgram(Program0);

    glBindImageTexture(1,Tex_image_result,0,GL_FALSE,0,GL_READ_WRITE,GL_R32F);

    QMatrix4x4 Model_view;

    Model_view.ortho(0,Width,0,Height,-100,100);

    glViewport(0,0,Width,Height);

    glUniform1i(2,Width);
    glUniform1i(3,Height);
    glUniformMatrix4fv(5,1,GL_FALSE,Model_view.data());

    // draw the triangles
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glDrawArrays(GL_TRIANGLES,0,Num_vertices);

    // read the result
    if (Result_floats_image==nullptr){
      Result_floats_image=make_shared<cv::Mat>();
      Result_floats_image->create(Height,Width,CV_32FC1);
    }

    glBindTexture(GL_TEXTURE_2D,Tex_image_result);
    glGetTexImage(GL_TEXTURE_2D,0,GL_RED,GL_FLOAT,&Result_floats_image->data[0]);

//    cout << "Result=" << Result_floats_image->at<float>(0) << endl;

    glUseProgram(0);
    glBindVertexArray(0);

//    glDeleteTextures(1,&Tex_input_image_normalized);
    glDeleteTextures(1,&Tex_image_result);
    glDeleteBuffers(1,&VBO_vertices);
    glDeleteBuffers(1,&VBO_vertices_colors);

    glDeleteProgram(Program0);
    glDeleteVertexArrays(1,&VAO1);

    glDeleteFramebuffers(1,&FBO);

    // the normal framebuffer takes the control of drawing
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER,Window->GL_widget->defaultFramebufferObject());

    // to check if there are transparent pixels
    shared_ptr<cv::Mat> Image_normalized=Vec_input_images[0];
    cv::Vec4f Pixel;
    for (int Row=0;Row<Result_floats_image->rows;Row++){
      for (int Col=0;Col<Result_floats_image->cols;Col++){
        Pixel=Image_normalized->at<cv::Vec4f>(Row,Col);
        if (Pixel[3]==0){
          if (Col%20<10 && Row%20<10) Result_floats_image->at<float>(Row,Col)=1.0f;
          else Result_floats_image->at<float>(Row,Col)=0.0f;
        }
      }
    }

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

void _layer_map_triangulation::update()
{
  update_map();
}

/*************************************************************************/

_layer_map_triangulation_ui::_layer_map_triangulation_ui(_window_xmapslab *Window1, std::string Name1)
{
  Window=Window1;
  Name=Name1;
  Qtw_layer_map_triangulation_a=new _qtw_layer_map_triangulation(Window1,this,Name);
}

/*************************************************************************/

_layer_map_triangulation_ui::~_layer_map_triangulation_ui()
{
  delete Qtw_layer_map_triangulation_a;
}

/*************************************************************************/

void _layer_map_triangulation_ui::reset_data()
{
  _layer_map_triangulation::reset_data();
  Qtw_layer_map_triangulation_a->parameter1(parameter1());
  hide();
}

/*************************************************************************/

void _layer_map_triangulation_ui::show()
{
  Qtw_layer_map_triangulation_a->show();
}

/*************************************************************************/

void _layer_map_triangulation_ui::hide()
{
  Qtw_layer_map_triangulation_a->hide();
}

/*************************************************************************/

void *_layer_map_triangulation_ui::get_link()
{
  return Qtw_layer_map_triangulation_a->get_link();
}

/*************************************************************************/

void _layer_map_triangulation_ui::enable()
{
  Qtw_layer_map_triangulation_a->enable();
}

/*************************************************************************/

void _layer_map_triangulation_ui::disable()
{
  Qtw_layer_map_triangulation_a->disable();
}

/*************************************************************************/

void _layer_map_triangulation_ui::parameter1_ui(float Value)
{
  Qtw_layer_map_triangulation_a->parameter1(int(Value*255.0f));
}

/*************************************************************************/

void _layer_map_triangulation_ui::parameter2_ui(float Value)
{
  Qtw_layer_map_triangulation_a->parameter2(int(Value*255.0f));
}

/*************************************************************************/

void _layer_map_triangulation_ui::parameter3_ui(float Value)
{
  Qtw_layer_map_triangulation_a->parameter3(int(Value*255.0f));
}

/*************************************************************************/

void _layer_map_triangulation_ui::parameter4_ui(int Value)
{
  Qtw_layer_map_triangulation_a->parameter4(Value);
}

/*************************************************************************/

void _layer_map_triangulation_ui::data_type_print(_palette_data_ns::_data_type_print Data_type_print1)
{
  Data_type_print=Data_type_print1;
  Qtw_layer_map_triangulation_a->parameter4(int(Data_type_print1));
}

/*************************************************************************/

_qtw_layer_map_triangulation::_qtw_layer_map_triangulation(_window_xmapslab *Window1,_layer_map_triangulation_ui *Filter1,std::string Box_name)
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

void _qtw_layer_map_triangulation::parameter1(int Value)
{
  Slider_parameter1->blockSignals(true);
  Slider_parameter1->setValue(Value);
  Slider_parameter1->blockSignals(false);
}

/*************************************************************************/

void _qtw_layer_map_triangulation::parameter2(int Value)
{
  Slider_parameter2->blockSignals(true);
  Slider_parameter2->setValue(Value);
  Slider_parameter2->blockSignals(false);
}

/*************************************************************************/

void _qtw_layer_map_triangulation::parameter3(int Value)
{
  Slider_parameter3->blockSignals(true);
  Slider_parameter3->setValue(Value);
  Slider_parameter3->blockSignals(false);
}

/*************************************************************************/

void _qtw_layer_map_triangulation::parameter4(int Value)
{
  Combobox_parameter4->blockSignals(true);
  Combobox_parameter4->setCurrentIndex(Value);
  Combobox_parameter4->blockSignals(false);
}

/*************************************************************************/

void _qtw_layer_map_triangulation::parameter1_slot(int Value)
{
  Filter->parameter1(Value);
  Window->update_layer(Filter->name());
}

/*************************************************************************/

void _qtw_layer_map_triangulation::parameter2_slot(int Value)
{
  Filter->parameter2(Value);
  Window->update_layer(Filter->name());
}

/*************************************************************************/

void _qtw_layer_map_triangulation::parameter3_slot(int Value)
{
  Filter->parameter3(Value);
  Window->update_layer(Filter->name());
}

/*************************************************************************/

void _qtw_layer_map_triangulation::parameter4_slot(int Value)
{
  Filter->parameter2(Value);
  Window->update_color_bar_data_type_print(Value);
}
