/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "layer_basic_positions.h"
#include "window_positions.h"

/*************************************************************************/

_layer_basic_positions::_layer_basic_positions()
{
  Transparence=0;
  State[0]=true;
  State[1]=true;

  Layer_type=_layer_positions_ns::_layer_type::LAYER_TYPE_BASIC;
}

/*************************************************************************/

void _layer_basic_positions::reset_data()
{
  Transparence=0;
}

/*************************************************************************/

void _layer_basic_positions::update()
{
}

/*************************************************************************/

_layer_basic_positions_ui::_layer_basic_positions_ui(_window_positions  *Window1, std::string Name1)
{
  Name=Name1;
  Qtw_layer_basic_positions=new _qtw_layer_basic_positions(Window1,this,Name);
}

/*************************************************************************/

_layer_basic_positions_ui::~_layer_basic_positions_ui()
{
  delete Qtw_layer_basic_positions;
}

/*************************************************************************/

void _layer_basic_positions_ui::reset_data()
{
  _layer_basic_positions::reset_data();
  Qtw_layer_basic_positions->parameter1(parameter1());
  hide();
}

/*************************************************************************/

void _layer_basic_positions_ui::show()
{
  Qtw_layer_basic_positions->show();
}

/*************************************************************************/

void _layer_basic_positions_ui::hide()
{
  Qtw_layer_basic_positions->hide();
}

/*************************************************************************/

void *_layer_basic_positions_ui::get_link()
{
  return Qtw_layer_basic_positions->get_link();
}

/*************************************************************************/

//void _layer_basic_positions_ui::read_parameters(std::map<std::string,std::string> &Parameters)
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
//    catch (const std::out_of_range) {
//      QMessageBox MsgBox;
//      MsgBox.setText("Error in the data of CANNY filter");
//      MsgBox.exec();
//      exit(-1);
//    }
//  }
//}

/*************************************************************************/

//void _layer_basic_positions_ui::write_parameters(std::map<std::string,std::string> &Parameters)
//{
//  char Aux[100];

//  sprintf(Aux,"%d",parameter1());
//  Parameters["kernel_size"]=std::string(Aux);
//  sprintf(Aux,"%d",parameter2());
//  Parameters["threshold1"]=std::string(Aux);
//  sprintf(Aux,"%d",parameter3());
//  Parameters["threshold2"]=std::string(Aux);
//}

/*************************************************************************/

_qtw_layer_basic_positions::_qtw_layer_basic_positions(_window_positions *Window1,_layer_basic_positions_ui *Filter1,std::string Box_name)
{
  Window=Window1;
  Filter=Filter1;

  Group_box_main=new QGroupBox(tr(Box_name.c_str()));
  Group_box_main->setAlignment(Qt::AlignCenter);

  QVBoxLayout *Vertical_box_main=new QVBoxLayout;

  // Parameter1
  QGroupBox *Group_box_parameter1=new QGroupBox(tr(_layer_basic_positions_ns::String_group_box_parameter1.c_str()));
  Group_box_parameter1->setAlignment(Qt::AlignCenter);

  QGridLayout *Grid_parameter1 = new QGridLayout;

  QLabel *Label_parameter1_min= new QLabel(tr(_layer_basic_positions_ns::String_label_parameter1_min.c_str()));
  QLabel *Label_parameter1_max= new QLabel(tr(_layer_basic_positions_ns::String_label_parameter1_max.c_str()));

  Line_edit_parameter1=new QLineEdit();
  Line_edit_parameter1->setAlignment(Qt::AlignRight);
  Line_edit_parameter1->setReadOnly(true);
  Line_edit_parameter1->setEnabled(false);
  Line_edit_parameter1->setToolTip(tr(_layer_basic_positions_ns::String_label_parameter1_tooltip.c_str()));

  Slider_parameter1 = new QSlider(Qt::Horizontal);
  Slider_parameter1->setRange(_layer_basic_positions_ns::Parameter1_min_value,_layer_basic_positions_ns::Parameter1_max_value);
  Slider_parameter1->setSingleStep(_layer_basic_positions_ns::Parameter1_single_step);
  Slider_parameter1->setPageStep(_layer_basic_positions_ns::Parameter1_page_step);
  Slider_parameter1->setTickInterval(_layer_basic_positions_ns::Parameter1_tick_interval);
  Slider_parameter1->setTickPosition(QSlider::TicksRight);
  Slider_parameter1->setTracking(_layer_basic_positions_ns::Parameter1_set_tracking);
  Slider_parameter1->setToolTip(tr(_layer_basic_positions_ns::String_parameter1_tooltip.c_str()));

  parameter1(Filter->parameter1());

  Grid_parameter1->addWidget(Line_edit_parameter1,0,1,Qt::AlignCenter);
  Grid_parameter1->addWidget(Label_parameter1_min,1,0,Qt::AlignRight);
  Grid_parameter1->addWidget(Slider_parameter1,1,1);
  Grid_parameter1->addWidget(Label_parameter1_max,1,2,Qt::AlignLeft);

  Group_box_parameter1->setLayout(Grid_parameter1);

  connect(Slider_parameter1, SIGNAL(valueChanged(int)),this,SLOT(parameter1_slot(int)));

  //
  Vertical_box_main->addWidget(Group_box_parameter1);

  Group_box_main->setLayout(Vertical_box_main);
}

/*************************************************************************/

void _qtw_layer_basic_positions::parameter1(int Value)
{
  QString Str;

  Str=Str.number(Value);
  Line_edit_parameter1->setText(Str);
  Slider_parameter1->blockSignals(true);
  Slider_parameter1->setValue((Value/2)-1);
  Slider_parameter1->blockSignals(false);
}

/*************************************************************************/

void _qtw_layer_basic_positions::parameter1_slot(int Value)
{
  QString Str;
  char Aux[100];

  sprintf(Aux,"%2d",Value);
  Str=Aux;
  Line_edit_parameter1->setText(Str);
  Filter->parameter1(Value);
  Window->update_layer(Filter->name());
}

