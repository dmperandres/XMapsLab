/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#include "layer_basic.h"
#include "window.h"

using namespace _f_basic_ns;

/*************************************************************************/

_layer_basic::_layer_basic()
{
  Transparence=0;
  State[0]=true;
  State[1]=true;

  Layer_type=_f_layer_ns::LAYER_TYPE_BASIC;
}

/*************************************************************************/

void _layer_basic::reset_data()
{
  Transparence=0;
}

/*************************************************************************/

/*************************************************************************/

void _layer_basic::update()
{
}

/*************************************************************************/

_layer_basic_ui::_layer_basic_ui(_window *Window1, std::string Name1)
{
  Name=Name1;
  Qtw_layer_basic=new _qtw_layer_basic(Window1,this,Name);
}

/*************************************************************************/

_layer_basic_ui::~_layer_basic_ui()
{
  delete Qtw_layer_basic;
}

/*************************************************************************/

void _layer_basic_ui::reset_data()
{
  _layer_basic::reset_data();
  Qtw_layer_basic->parameter1(parameter1());
  hide();
}

/*************************************************************************/

void _layer_basic_ui::show()
{
  Qtw_layer_basic->show();
}

/*************************************************************************/

void _layer_basic_ui::hide()
{
  Qtw_layer_basic->hide();
}

/*************************************************************************/

void *_layer_basic_ui::get_link()
{
  return Qtw_layer_basic->get_link();
}

/*************************************************************************/

_qtw_layer_basic::_qtw_layer_basic(_window *Window1,_layer_basic_ui *Filter1,std::string Box_name)
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

  //
  Vertical_box_main->addWidget(Group_box_parameter1);

  Group_box_main->setLayout(Vertical_box_main);
}

/*************************************************************************/

void _qtw_layer_basic::parameter1(int Value)
{
  QString Str;

  Str=Str.number(Value);
  Line_edit_parameter1->setText(Str);
  Slider_parameter1->blockSignals(true);
  Slider_parameter1->setValue((Value/2)-1);
  Slider_parameter1->blockSignals(false);
}

/*************************************************************************/

void _qtw_layer_basic::parameter1_slot(int Value)
{
  QString Str;
  char Aux[100];

  sprintf(Aux,"%2d",Value);
  Str=Aux;
  Line_edit_parameter1->setText(Str);
  Filter->parameter1(Value);
  Window->update_layer(Filter->name());
}

