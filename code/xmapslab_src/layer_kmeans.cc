/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "layer_kmeans.h"
#include "window.h"

using namespace _layer_kmeans_ns;

/*************************************************************************/

_layer_kmeans::_layer_kmeans()
{
  Num_colors=KMEANS_NUM_COLORS_DEFAULT;

  Layer_type=_layer_ns::_layer_type::LAYER_TYPE_KMEANS;

  State[0]=true;
  State[1]=true;

  Num_channels=3;
}

/*************************************************************************/

void _layer_kmeans::reset_data()
{
  Num_colors=KMEANS_NUM_COLORS_DEFAULT;
}

/*************************************************************************/

void _layer_kmeans::update()
{
  if (Image==nullptr){
    Image=make_shared<cv::Mat>();
  }
  else{
    Image->release();
  }

  cv::Mat Image_aux;

  cv::cvtColor(*Vec_input_images[0],Image_aux,cv::COLOR_BGRA2BGR,3);

  Image_aux.convertTo(Image_aux,CV_32F);
  Image_aux = Image_aux.reshape(1,Vec_input_images[0]->total());

  // do kmeans
  cv::Mat labels, centers;
  kmeans(Image_aux,Num_colors,labels, cv::TermCriteria(cv::TermCriteria::MAX_ITER, 10, 1.0), 3,cv::KMEANS_RANDOM_CENTERS, centers);

  // reshape both to a single row of Vec3f pixels:
  centers = centers.reshape(3,centers.rows);
  Image_aux = Image_aux.reshape(3,Image_aux.rows);

  // replace pixel values with their center value:
  cv::Vec3f *p = Image_aux.ptr<cv::Vec3f>();
  for (size_t i=0; i<size_t(Image_aux.rows); i++) {
     int center_id = labels.at<int>(i);
     p[i] = centers.at<cv::Vec3f>(center_id);
  }

  // back to 2d, and uchar:
  Image_aux = Image_aux.reshape(3, Vec_input_images[0]->rows);
  Image_aux.convertTo(*Image, CV_8U);

  cv::cvtColor(*Image.get(),*Image.get(),cv::COLOR_BGR2BGRA,4);
}

/*************************************************************************/

_layer_kmeans_ui::_layer_kmeans_ui(_window *Window1, std::string Name1)
{
  Name=Name1;
  Qtw_layer_kmeans=new _qtw_layer_kmeans(Window1,this,Name);
}

/*************************************************************************/

_layer_kmeans_ui::~_layer_kmeans_ui()
{
  delete Qtw_layer_kmeans;
}

/*************************************************************************/

void _layer_kmeans_ui::reset_data()
{
  _layer_kmeans::reset_data();
  Qtw_layer_kmeans->parameter1(parameter1());
  Qtw_layer_kmeans->parameter2(parameter2());
  hide();
}

/*************************************************************************/

void _layer_kmeans_ui::show()
{
  Qtw_layer_kmeans->show();
}

/*************************************************************************/

void _layer_kmeans_ui::hide()
{
  Qtw_layer_kmeans->hide();
}

/*************************************************************************/

void *_layer_kmeans_ui::get_link()
{
  return Qtw_layer_kmeans->get_link();
}

/*************************************************************************/

void _layer_kmeans_ui::enable()
{
  Qtw_layer_kmeans->enable();
}

/*************************************************************************/

void _layer_kmeans_ui::disable()
{
  Qtw_layer_kmeans->disable();
}

/*************************************************************************/

//void _layer_kmeans_ui::read_parameters(std::map<std::string,std::string> &Parameters)
//{
//  if (Parameters["_INI_"]=="EDITOR"){// default parameters
//    parameter1(CANNY_SIZE_DEFAULT);
//    parameter2(CANNY_THRESHOLD1_DEFAULT);
//    parameter3(CANNY_THRESHOLD2_DEFAULT);
//  }
//  else{// Parameters from file or from initialised filter
//    try{
//      if (Parameters["kernel_size"]=="default") parameter1(CANNY_SIZE_DEFAULT);
//      else parameter1(atoi(Parameters["kernel_size"].c_str()));
//      if (Parameters["threshold1"]=="default") parameter2(CANNY_THRESHOLD1_DEFAULT);
//      else parameter2(atoi(Parameters["threshold1"].c_str()));
//      if (Parameters["threshold2"]=="default") parameter3(CANNY_THRESHOLD2_DEFAULT);
//      else parameter3(atoi(Parameters["threshold2"].c_str()));
//    }
//    catch (...) {
//      QMessageBox MsgBox;
//      MsgBox.setText("Error in the data of CANNY filter");
//      MsgBox.exec();
//      exit(-1);
//    }
//  }
//}

/*************************************************************************/

//void _layer_kmeans_ui::write_parameters(std::map<std::string,std::string> &Parameters)
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

_qtw_layer_kmeans::_qtw_layer_kmeans(_window *Window1,_layer_kmeans_ui *Filter1,string Box_name)
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

  // Parameter 2
  Group_box_parameter2=new QGroupBox(tr(String_group_box_parameter2.c_str()));
  Group_box_parameter2->setAlignment(Qt::AlignCenter);

  QGridLayout *Grid_parameter2 = new QGridLayout;

  QLabel *Label_parameter2_min= new QLabel(tr(String_label_parameter2_min.c_str()));
  QLabel *Label_parameter2_max= new QLabel(tr(String_label_parameter2_max.c_str()));

  Line_edit_parameter2=new QLineEdit();
  Line_edit_parameter2->setAlignment(Qt::AlignRight);
  Line_edit_parameter2->setReadOnly(true);
  Line_edit_parameter2->setEnabled(false);
  Line_edit_parameter2->setToolTip(tr(String_label_parameter2_tooltip.c_str()));

  Slider_parameter2 = new QSlider(Qt::Horizontal);
  Slider_parameter2->setRange(Parameter2_min_value,Parameter2_max_value);
  Slider_parameter2->setSingleStep(Parameter2_single_step);
  Slider_parameter2->setPageStep(Parameter2_page_step);
  Slider_parameter2->setTickInterval(Parameter2_tick_interval);
  Slider_parameter2->setTickPosition(QSlider::TicksRight);
  Slider_parameter2->setTracking(Parameter2_set_tracking);
  Slider_parameter2->setToolTip(tr(String_parameter2_tooltip.c_str()));

  parameter2(Filter->parameter2());

  Grid_parameter2->addWidget(Line_edit_parameter2,0,1,Qt::AlignCenter);
  Grid_parameter2->addWidget(Label_parameter2_min,1,0,Qt::AlignRight);
  Grid_parameter2->addWidget(Slider_parameter2,1,1);
  Grid_parameter2->addWidget(Label_parameter2_max,1,2,Qt::AlignLeft);

  Group_box_parameter2->setLayout(Grid_parameter2);

  connect(Slider_parameter2, SIGNAL(valueChanged(int)),this,SLOT(parameter2_slot(int)));

  //
  Vertical_box_main->addWidget(Group_box_parameter1);
  Vertical_box_main->addWidget(Group_box_parameter2);

  Group_box_main->setLayout(Vertical_box_main);
}

/*************************************************************************/

void _qtw_layer_kmeans::parameter1(int Value)
{
  QString Str;

  Str=Str.number(Value);
  Line_edit_parameter1->setText(Str);
  Slider_parameter1->blockSignals(true);
  Slider_parameter1->setValue(Value);
  Slider_parameter1->blockSignals(false);
}

/*************************************************************************/

void _qtw_layer_kmeans::parameter2(int Value)
{
  QString Str;

  Str=Str.number(Value);
  Line_edit_parameter2->setText(Str);
  Slider_parameter2->blockSignals(true);
  Slider_parameter2->setValue(Value);
  Slider_parameter2->blockSignals(false);
}

/*************************************************************************/

void _qtw_layer_kmeans::parameter1_slot(int Value)
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

void _qtw_layer_kmeans::parameter2_slot(int Value)
{
  QString Str;
  char Aux[100];

  sprintf(Aux,"%2d",Value);
  Str=Aux;
  Line_edit_parameter2->setText(Str);
  Filter->parameter2(Value);
  Window->update_layer(Filter->name());
}

