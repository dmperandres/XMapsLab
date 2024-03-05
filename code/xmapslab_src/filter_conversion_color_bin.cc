/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "filter_conversion_color_bin.h"
#include "glwidget_xmapslab_ge.h"
#include "window_xmapslab.h"

using namespace _f_element_ns;

/*************************************************************************/

_filter_conversion_color_bin::_filter_conversion_color_bin()
{
  Filter_type=_filter_ns::_filter_type::FILTER_TYPE_CONVERSION_COLOR_TO_BIN_OP;
  Filter_class=_filter_ns::_filter_class::FILTER_CLASS_BINARY;

  Max_value=1.0f;
}

/*************************************************************************/

void _filter_conversion_color_bin::reset_data()
{
}

/*************************************************************************/

float _filter_conversion_color_bin::get_max_value()
{
  float Value1=Vec_input_filters[0]->get_max_value();

  return Value1;
}

/*************************************************************************/

void _filter_conversion_color_bin::update()
{
  if (Image_processed==false){
    Image_processed=true;
    HLS_image=std::make_shared<cv::Mat>();
    cv::Mat BGR_image;
    cv::cvtColor(*Vec_input_data[0],BGR_image,cv::COLOR_BGRA2BGR,3);
    cv::Vec4b Value1;
//    for (int Row=0;Row<Vec_input_data[0]->rows;Row++){
//      for (int Col=0;Col<Vec_input_data[0]->cols;Col++){
//        Value1=Vec_input_data[0]->at<cv::Vec4b>(Row,Col);
//        if (Row==500){
//          std::cout << int(Value1[0]) << " " << int(Value1[1]) << " " << int(Value1[2]) << " " << int(Value1[3]) << std::endl;
//        }
//      }
//    }

    cv::cvtColor(BGR_image,*HLS_image,cv::COLOR_BGR2HLS,3);
//    cv::Vec3b Value2;
//    for (int Row=0;Row<HLS_image->rows;Row++){
//      for (int Col=0;Col<HLS_image->cols;Col++){
//        Value2=HLS_image->at<cv::Vec3b>(Row,Col);
//        if (Row==500){
//          std::cout << int(Value2[0]) << " " << int(Value2[1]) << " " << int(Value2[2]) << " " << std::endl;
//        }
//      }
//    }
  }

  cv::Vec3b Value0;

  shared_ptr<cv::Mat> Input_A=HLS_image;
  shared_ptr<cv::Mat> Output=Vec_output_data[0];

  int Hue=Color.hue();
  int Min_interval=Hue-Threshold;
  if (Min_interval<0) Min_interval=Min_interval+360;

  int Max_interval=(Hue+Threshold)%360;
  bool Inverted=false;
  if ((Min_interval-Max_interval)>180) Inverted=true;

  for (int Row=0;Row<Input_A->rows;Row++){
    for (int Col=0;Col<Input_A->cols;Col++){
      Value0=Input_A->at<cv::Vec3b>(Row,Col);
      if (Inverted==false){
        if (Value0[0]*2>=Min_interval && Value0[0]*2<=Max_interval) Output->at<float>(Row,Col)=1.0f;
        else Output->at<float>(Row,Col)=0.0;
      }
      else{
        if (Value0[0]*2<=Max_interval || Value0[0]*2>=Min_interval) Output->at<float>(Row,Col)=1.0f;
        else Output->at<float>(Row,Col)=0.0;
      }
    }
  }

  apply_colormap(Vec_output_data[0],Vec_output_images[0]);
}

/*************************************************************************/

_filter_conversion_color_bin_ui::_filter_conversion_color_bin_ui(_window_xmapslab *Window1, string Name1)
{
  Name=Name1;
  Qtw_filter_conversion_color_bin=new _qtw_filter_conversion_color_bin(Window1,this,Name1);
}

/*************************************************************************/

_filter_conversion_color_bin_ui::_filter_conversion_color_bin_ui(_window_xmapslab *Window1, std::map<string, string> &Parameters, string Name1)
{
  read_parameters(Parameters);
  Name=Name1;
  Qtw_filter_conversion_color_bin=new _qtw_filter_conversion_color_bin(Window1,this,Name1);
}

/*************************************************************************/

_filter_conversion_color_bin_ui::~_filter_conversion_color_bin_ui()
{
  delete Qtw_filter_conversion_color_bin;
}

/*************************************************************************/

void _filter_conversion_color_bin_ui::reset_data()
{
  _filter_conversion_color_bin::reset_data();
  Qtw_filter_conversion_color_bin->parameter1(parameter1());
  hide();
}

/*************************************************************************/

void _filter_conversion_color_bin_ui::show()
{
  Qtw_filter_conversion_color_bin->show();
}

/*************************************************************************/

void _filter_conversion_color_bin_ui::hide()
{
  Qtw_filter_conversion_color_bin->hide();
}

/*************************************************************************/

void *_filter_conversion_color_bin_ui::get_link()
{
  return Qtw_filter_conversion_color_bin->get_link();
}

/*************************************************************************/

void _filter_conversion_color_bin_ui::read_parameters(std::map<std::string,std::string> &Parameters)
{
  if (Parameters["_INI_"]=="EDITOR"){// default parameters
    parameter1(_f_conversion_color_bin_ns::THRESHOLD_DEFAULT);
  }
  else{// Parameters from file or from initialised filter
    try{
      if (Parameters["threshold"]=="default") parameter1(_f_conversion_color_bin_ns::THRESHOLD_DEFAULT);
      else parameter1(atoi(Parameters["threshold"].c_str()));
    }
    catch (...) {
      QMessageBox MsgBox;
      MsgBox.setText("Error in the data of BIN filter");
      MsgBox.exec();
      exit(-1);
    }
  }
}

/*************************************************************************/

void _filter_conversion_color_bin_ui::write_parameters(std::map<std::string,std::string> &Parameters)
{
  char Aux[100];

  sprintf(Aux,"%d",parameter1());
  Parameters["threshold"]=string(Aux);
}

/*************************************************************************/

_qtw_filter_conversion_color_bin::_qtw_filter_conversion_color_bin(_window_xmapslab *Window1,_filter_conversion_color_bin_ui *Filter1,string Box_name)
{
  Window=Window1;
  Filter=Filter1;

  Group_box_main=new QGroupBox(tr(Box_name.c_str()));
  Group_box_main->setAlignment(Qt::AlignCenter);

  QVBoxLayout *Vertical_box_main=new QVBoxLayout;

  // Parameter 1
  QFrame *Frame_parameter1=new QFrame;
  Frame_parameter1->setFrameStyle(QFrame::Panel);

  QGridLayout *Grid_parameter1=new QGridLayout;

  // Parameter1
  // 0 thresold
  Spinbox_parameter1=new QSpinBox;
  Spinbox_parameter1->setRange(0,100);
  Spinbox_parameter1->setAlignment(Qt::AlignRight);
//  Spinbox_parameter1->setSuffix(" %");
  Spinbox_parameter1->setToolTip(tr(_f_conversion_color_bin_ns::String_parameter1_tooltip.c_str()));

  parameter1(Filter->parameter1());

  QLabel *Label_parameter1=new QLabel("Interval increase");

  Grid_parameter1->addWidget(Label_parameter1,0,0,Qt::AlignRight);
  Grid_parameter1->addWidget(Spinbox_parameter1,0,1,Qt::AlignLeft);

  Frame_parameter1->setLayout(Grid_parameter1);

  connect(Spinbox_parameter1,SIGNAL(valueChanged(int)),this,SLOT(parameter1_slot(int)));

  // Parameter2
  QFrame *Frame_parameter2=new QFrame;
  Frame_parameter2->setFrameStyle(QFrame::Panel);
  QGridLayout *Grid_parameter2=new QGridLayout;

  QLabel *Label_parameter2=new QLabel("Color selector");

  float Factor=Window->screen_height()/1080.0f;
  Button_parameter2=new _button_color_simple(QColor(255,0,0),Factor);

  Grid_parameter2->addWidget(Label_parameter2,0,0,Qt::AlignRight);
  Grid_parameter2->addWidget(Button_parameter2,0,1,Qt::AlignLeft);

  Frame_parameter2->setLayout(Grid_parameter2);

  connect(Button_parameter2,SIGNAL(colorChanged(QColor)),this,SLOT(parameter2_slot(QColor)));

  //
  Vertical_box_main->addWidget(Frame_parameter1);
  Vertical_box_main->addWidget(Frame_parameter2);

  Group_box_main->setLayout(Vertical_box_main);
}

/*************************************************************************/

void _qtw_filter_conversion_color_bin::parameter1(int Value)
{
  Spinbox_parameter1->blockSignals(true);
  Spinbox_parameter1->setValue(Value);
  Spinbox_parameter1->blockSignals(false);
}

/*************************************************************************/

void _qtw_filter_conversion_color_bin::parameter2(QColor Color1)
{
  Button_parameter2->color(Color1);
}

/*************************************************************************/

void _qtw_filter_conversion_color_bin::parameter1_slot(int Value)
{
  Filter->parameter1(Value);
  Window->update_filter(Filter->name());
}

/*************************************************************************/

void _qtw_filter_conversion_color_bin::parameter2_slot(QColor Color1)
{
  Filter->parameter2(Color1);

  Window->update_filter(Filter->name());
}
