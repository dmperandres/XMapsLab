//LIC

#include "layer_basic_xmapslab.h"
#include "window_xmapslab.h"

using namespace _layer_basic_xmapslab_ns;


//HEA

_layer_basic_xmapslab::_layer_basic_xmapslab()
{
  Vec_transparency=0;
  State[0]=true;
  State[1]=true;

  Type=_layer_xmapslab_ns::_type::TYPE_IMAGE;
  Subtype=_layer_xmapslab_ns::_subtype::SUBTYPE_IMAGE;

  Num_channels=3;
}

//HEA

void _layer_basic_xmapslab::reset_data()
{
  Vec_transparency=0;
  State[0]=true;
  State[1]=true;
}

//HEA

void _layer_basic_xmapslab::update()
{
}

//HEA

_layer_basic_xmapslab_ui::_layer_basic_xmapslab_ui(_window_xmapslab *Window1, std::string Name1)
{
  Window=Window1;
  Name=Name1;
  Qtw_layer_basic_xmapslab=new _qtw_layer_basic_xmapslab(Window1,this,Name);
}

//HEA

_layer_basic_xmapslab_ui::~_layer_basic_xmapslab_ui()
{
  delete Qtw_layer_basic_xmapslab;
}

//HEA

void _layer_basic_xmapslab_ui::reset_data()
{
  _layer_basic_xmapslab::reset_data();
  Qtw_layer_basic_xmapslab->parameter1(parameter1());
  hide();
}

//HEA

void _layer_basic_xmapslab_ui::show()
{
  Qtw_layer_basic_xmapslab->show();
}

//HEA

void _layer_basic_xmapslab_ui::hide()
{
  Qtw_layer_basic_xmapslab->hide();
}

//HEA

void *_layer_basic_xmapslab_ui::get_link()
{
  return Qtw_layer_basic_xmapslab->get_link();
}

//HEA

void _layer_basic_xmapslab_ui::enable()
{
  Qtw_layer_basic_xmapslab->enable();
}

//HEA

void _layer_basic_xmapslab_ui::disable()
{
  Qtw_layer_basic_xmapslab->disable();
}

//HEA

_qtw_layer_basic_xmapslab::_qtw_layer_basic_xmapslab(_window_xmapslab *Window1,_layer_basic_xmapslab_ui *Filter1,std::string Box_name)
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

//HEA

void _qtw_layer_basic_xmapslab::parameter1(int Value)
{
  QString Str;

  Str=Str.number(Value);
  Line_edit_parameter1->setText(Str);
  Slider_parameter1->blockSignals(true);
  Slider_parameter1->setValue((Value/2)-1);
  Slider_parameter1->blockSignals(false);
}


//HEA

void _qtw_layer_basic_xmapslab::parameter1_slot(int Value)
{
  QString Str;
  char Aux[100];

  sprintf(Aux,"%2d",Value);
  Str=Aux;
  Line_edit_parameter1->setText(Str);
  Filter->parameter1(Value);
  Window->update_layer(Filter->name());
}


