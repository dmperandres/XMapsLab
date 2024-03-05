/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "filter_conversion_bin.h"
#include "glwidget_xmapslab_ge.h"
#include "window_xmapslab.h"

using namespace _f_element_ns;

/*************************************************************************/

_filter_conversion_bin::_filter_conversion_bin()
{
  Filter_type=_filter_ns::_filter_type::FILTER_TYPE_CONVERSION_TO_BIN_OP;
  Filter_class=_filter_ns::_filter_class::FILTER_CLASS_BINARY;

  Max_value=1.0f;
}

/*************************************************************************/

void _filter_conversion_bin::reset_data()
{
}

/*************************************************************************/

float _filter_conversion_bin::get_max_value()
{
  float Value1=Vec_input_filters[0]->get_max_value();

  return Value1;
}

/*************************************************************************/

void _filter_conversion_bin::update()
{
  float Value0=0;
  float Threshold1=float(Threshold)/100.0f;

  shared_ptr<cv::Mat> Input_A=Vec_input_data[0];
  shared_ptr<cv::Mat> Output=Vec_output_data[0];

  for (int Row=0;Row<Input_A->rows;Row++){
    for (int Col=0;Col<Input_A->cols;Col++){
      Value0=Input_A->at<float>(Row,Col);
      if (Value0>=Threshold1){
        Output->at<float>(Row,Col)=1.0f;
      }
      else{
        Output->at<float>(Row,Col)=0.0;
      }
    }
  }

  apply_colormap(Vec_output_data[0],Vec_output_images[0]);
}

/*************************************************************************/

_filter_conversion_bin_ui::_filter_conversion_bin_ui(_window_xmapslab *Window1, string Name1)
{
  Name=Name1;
  Qtw_filter_conversion_bin=new _qtw_filter_conversion_bin(Window1,this,Name1);
}

/*************************************************************************/

_filter_conversion_bin_ui::_filter_conversion_bin_ui(_window_xmapslab *Window1, std::map<string, string> &Parameters, string Name1)
{
  read_parameters(Parameters);
  Name=Name1;
  Qtw_filter_conversion_bin=new _qtw_filter_conversion_bin(Window1,this,Name1);
}

/*************************************************************************/

_filter_conversion_bin_ui::~_filter_conversion_bin_ui()
{
  delete Qtw_filter_conversion_bin;
}

/*************************************************************************/

void _filter_conversion_bin_ui::reset_data()
{
  _filter_conversion_bin::reset_data();
  Qtw_filter_conversion_bin->parameter1(parameter1());
  hide();
}

/*************************************************************************/

void _filter_conversion_bin_ui::show()
{
  Qtw_filter_conversion_bin->show();
}

/*************************************************************************/

void _filter_conversion_bin_ui::hide()
{
  Qtw_filter_conversion_bin->hide();
}

/*************************************************************************/

void *_filter_conversion_bin_ui::get_link()
{
  return Qtw_filter_conversion_bin->get_link();
}

/*************************************************************************/

void _filter_conversion_bin_ui::read_parameters(std::map<std::string,std::string> &Parameters)
{
  if (Parameters["_INI_"]=="EDITOR"){// default parameters
    parameter1(_f_conversion_bin_ns::THRESHOLD_DEFAULT);
  }
  else{// Parameters from file or from initialised filter
    try{
      if (Parameters["threshold"]=="default") parameter1(_f_conversion_bin_ns::THRESHOLD_DEFAULT);
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

void _filter_conversion_bin_ui::write_parameters(std::map<std::string,std::string> &Parameters)
{
  char Aux[100];

  sprintf(Aux,"%d",parameter1());
  Parameters["threshold"]=string(Aux);
}

/*************************************************************************/

_qtw_filter_conversion_bin::_qtw_filter_conversion_bin(_window_xmapslab *Window1,_filter_conversion_bin_ui *Filter1,string Box_name)
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
  Spinbox_parameter1->setSuffix(" %");
  Spinbox_parameter1->setToolTip(tr(_f_conversion_bin_ns::String_parameter1_tooltip.c_str()));

  parameter1(Filter->parameter1());

  QLabel *Label_parameter1=new QLabel("0 threshold");

  Grid_parameter1->addWidget(Label_parameter1,0,0,Qt::AlignRight);
  Grid_parameter1->addWidget(Spinbox_parameter1,0,1,Qt::AlignLeft);

  Frame_parameter1->setLayout(Grid_parameter1);

  connect(Spinbox_parameter1,SIGNAL(valueChanged(int)),this,SLOT(parameter1_slot(int)));

  //
  Vertical_box_main->addWidget(Frame_parameter1);

  Group_box_main->setLayout(Vertical_box_main);
}

/*************************************************************************/

void _qtw_filter_conversion_bin::parameter1(int Value)
{
  Spinbox_parameter1->blockSignals(true);
  Spinbox_parameter1->setValue(Value);
  Spinbox_parameter1->blockSignals(false);
}

/*************************************************************************/

//void _qtw_filter_conversion_bin::parameter2(QColor Color1)
//{
//  Button_parameter2->color(Color1);
//}

/*************************************************************************/

void _qtw_filter_conversion_bin::parameter1_slot(int Value)
{
  Filter->parameter1(Value);
  Window->update_filter(Filter->name());
}

/*************************************************************************/

//void _qtw_filter_conversion_bin::parameter2_slot(QColor Color1)
//{
//  Filter->parameter2(Color1);
//  Window->update_filter(Filter->name());
//}
