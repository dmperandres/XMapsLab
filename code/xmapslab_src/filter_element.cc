/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "filter_element.h"
#include "glwidget_xmapslab_ge.h"

using namespace _f_element_ns;

/*************************************************************************/

_filter_element::_filter_element()
{
  Filter_type=_filter_ns::_filter_type::FILTER_TYPE_ELEMENT;
  Filter_class=_filter_ns::_filter_class::FILTER_CLASS_ELEMENT;
}

/*************************************************************************/

void _filter_element::reset_data()
{
//  Kernel_size=BILATERAL_KERNEL_SIZE_DEFAULT;
}

/*************************************************************************/

float _filter_element::get_max_value()
{
  return Vec_max_value_input_data[0];
}

/*************************************************************************/

void _filter_element::update()
{
  Vec_max_value_output_data[0]=Vec_max_value_input_data[0];
}

/*************************************************************************/

_filter_element_ui::_filter_element_ui(_window_xmapslab *Window1, std::string Name1)
{
  Name=Name1;
  Qtw_filter_element=new _qtw_filter_element(Window1,this,Name1);
}

/*************************************************************************/

_filter_element_ui::_filter_element_ui(_window_xmapslab *Window1, std::map<string, string> &Parameters, std::string Name1)
{
  read_parameters(Parameters);
  Name=Name1;
  Qtw_filter_element=new _qtw_filter_element(Window1,this,Name1);
}

/*************************************************************************/

_filter_element_ui::~_filter_element_ui()
{
  delete Qtw_filter_element;
}

/*************************************************************************/

void _filter_element_ui::reset_data()
{
  _filter_element::reset_data();
//  Qtw_filter_element->parameter1(parameter1());
  hide();
}

/*************************************************************************/

void _filter_element_ui::show()
{
  Qtw_filter_element->show();
}

/*************************************************************************/

void _filter_element_ui::hide()
{
  Qtw_filter_element->hide();
}

/*************************************************************************/

void *_filter_element_ui::get_link()
{
  return Qtw_filter_element->get_link();
}

/*************************************************************************/

void _filter_element_ui::read_parameters(std::map<std::string,std::string> &Parameters)
{
  Q_UNUSED(Parameters)
//  if (Parameters["_INI_"]=="EDITOR"){// default parameters
////    parameter1(BILATERAL_KERNEL_SIZE_DEFAULT);!!!
//  }
//  else{// Parameters from file or from initialised filter
//    try{
////      if (Parameters["kernel_size"]=="default") parameter1(BILATERAL_KERNEL_SIZE_DEFAULT);!!!
////      else parameter1(atoi(Parameters["kernel_size"].c_str()));
//    }
//    catch (...) {
//      QMessageBox MsgBox;
//      MsgBox.setText("Error in the data of BILATERAL filter");
//      MsgBox.exec();
//      exit(-1);
//    }
//  }
}

/*************************************************************************/

void _filter_element_ui::write_parameters(std::map<std::string,std::string> &Parameters)
{
  Q_UNUSED(Parameters)
//  char Aux[100];

//  sprintf(Aux,"%d",parameter1());
//  Parameters["kernel_size"]=std::string(Aux);;
}

/*************************************************************************/

void _filter_element_ui::color(QColor Color1)
{
  Color=Color1;
//  Qtw_filter_combination_element->parameter2(Color);
}

/*************************************************************************/

_qtw_filter_element::_qtw_filter_element(_window_xmapslab *Window1,_filter_element_ui *Filter1,std::string Box_name)
{
  Window=Window1;
  Filter=Filter1;

  Group_box_main=new QGroupBox(tr(Box_name.c_str()));
  Group_box_main->setAlignment(Qt::AlignCenter);

//  QVBoxLayout *Vertical_box_main=new QVBoxLayout;

  // Parameter1
//  QGroupBox *Group_box_parameter1=new QGroupBox(tr(String_group_box_parameter1.c_str()));
//  Group_box_parameter1->setAlignment(Qt::AlignCenter);

//  QGridLayout *Grid_parameter1 = new QGridLayout;

//  QLabel *Label_parameter1_min= new QLabel(tr(String_label_parameter1_min.c_str()));
//  QLabel *Label_parameter1_max= new QLabel(tr(String_label_parameter1_max.c_str()));

//  Line_edit_parameter1=new QLineEdit();
//  Line_edit_parameter1->setAlignment(Qt::AlignRight);
//  Line_edit_parameter1->setReadOnly(true);
//  Line_edit_parameter1->setEnabled(false);
//  Line_edit_parameter1->setToolTip(tr(String_label_parameter1_tooltip.c_str()));

//  Slider_parameter1 = new QSlider(Qt::Horizontal);
//  Slider_parameter1->setRange(Parameter1_min_value,Parameter1_max_value);
//  Slider_parameter1->setSingleStep(Parameter1_single_step);
//  Slider_parameter1->setPageStep(Parameter1_page_step);
//  Slider_parameter1->setTickInterval(Parameter1_tick_interval);
//  Slider_parameter1->setTickPosition(QSlider::TicksRight);
//  Slider_parameter1->setTracking(Parameter1_set_tracking);
//  Slider_parameter1->setToolTip(tr(String_parameter1_tooltip.c_str()));

//  parameter1(Filter->parameter1());

//  Grid_parameter1->addWidget(Line_edit_parameter1,0,1,Qt::AlignCenter);
//  Grid_parameter1->addWidget(Label_parameter1_min,1,0,Qt::AlignRight);
//  Grid_parameter1->addWidget(Slider_parameter1,1,1);
//  Grid_parameter1->addWidget(Label_parameter1_max,1,2,Qt::AlignLeft);

//  Group_box_parameter1->setLayout(Grid_parameter1);

//  connect(Slider_parameter1, SIGNAL(valueChanged(int)),this,SLOT(parameter1_slot(int)));

  //
//  Vertical_box_main->addWidget(Group_box_parameter1);

//  Group_box_main->setLayout(Vertical_box_main);
}

/*************************************************************************/

//void _qtw_filter_element::parameter1(int Value)
//{
//  QString Str;

//  Str=Str.number(Value);
//  Line_edit_parameter1->setText(Str);
//  Slider_parameter1->blockSignals(true);
//  Slider_parameter1->setValue(Value);
//  Slider_parameter1->blockSignals(false);
//}

/*************************************************************************/

//void _qtw_filter_element::parameter2(QColor Color1)
//{
//  Button_parameter2->color(Color1);
//}

/*************************************************************************/

//void _qtw_filter_element::parameter1_slot(int Size)
//{
//  QString Str;

//  Str=Str.number(Size);
//  Line_edit_parameter1->setText(Str);
//  Filter->parameter1(Size);
////  Vec_gl_widget->update_effect(Filter->name());
//}

/*************************************************************************/

//void _qtw_filter_element::parameter2_slot(QColor Color1)
//{
//  Filter->parameter2(Color1);
//  Window->update_filter(Filter->name());
//}
