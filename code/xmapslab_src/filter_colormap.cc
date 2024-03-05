/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "filter_colormap.h"
#include "glwidget_xmapslab_ge.h"
#include "window_xmapslab.h"

using namespace _f_element_ns;

/*************************************************************************/

_filter_colormap::_filter_colormap()
{
}

/*************************************************************************/

void _filter_colormap::reset_data()
{
}

/*************************************************************************/

void _filter_colormap::update()
{
  Vec_output_data[0]=Vec_input_data[0];
  apply_colormap(Vec_output_data[0],Vec_output_images[0]);
}

/*************************************************************************/

void _filter_colormap::color(QColor Color1)
{
  Color=Color1;
  // get the palette data of the object
  _palette_data &Vec_palette_data=Window->Map_filters_palette_data[Window->mapping_selected_filter_name()];
  Vec_palette_data.color(Color1);
  set_colormap(Vec_palette_data.vec_values(),Vec_palette_data.vec_colors(),Vec_palette_data.data_type());
}

/*************************************************************************/

_filter_colormap_ui::_filter_colormap_ui(_window_xmapslab *Window1, std::string Name1)
{
  Name=Name1;
  Window=Window1;
  Qtw_filter_colormap=new _qtw_filter_colormap(Window1,this,Name1);
}

/*************************************************************************/

_filter_colormap_ui::_filter_colormap_ui(_window_xmapslab *Window1, std::map<string, string> &Parameters, std::string Name1)
{
  read_parameters(Parameters);
  Name=Name1;
  Window=Window1;
  Qtw_filter_colormap=new _qtw_filter_colormap(Window1,this,Name1);
}

/*************************************************************************/

_filter_colormap_ui::~_filter_colormap_ui()
{
  delete Qtw_filter_colormap;
}

/*************************************************************************/

void _filter_colormap_ui::reset_data()
{
  _filter_colormap::reset_data();
  Qtw_filter_colormap->parameter1(parameter1());
  hide();
}

/*************************************************************************/

void _filter_colormap_ui::show()
{
  Qtw_filter_colormap->show();
}

/*************************************************************************/

void _filter_colormap_ui::hide()
{
  Qtw_filter_colormap->hide();
}

/*************************************************************************/

void *_filter_colormap_ui::get_link()
{
  return Qtw_filter_colormap->get_link();
}

/*************************************************************************/

void _filter_colormap_ui::read_parameters(std::map<std::string,std::string> &Parameters)
{
  if (Parameters["_INI_"]=="EDITOR"){// default parameters
    parameter1(_f_colormap_ns::THRESHOLD_DEFAULT);
  }
  else{// Parameters from file or from initialised filter
    try{
      if (Parameters["threshold"]=="default") parameter1(_f_colormap_ns::THRESHOLD_DEFAULT);
      else parameter1(atoi(Parameters["threshold"].c_str()));
    }
    catch (...) {
      QMessageBox MsgBox;
      MsgBox.setText("Error in the data of AND filter");
      MsgBox.exec();
      exit(-1);
    }
  }
}

/*************************************************************************/

void _filter_colormap_ui::write_parameters(std::map<std::string,std::string> &Parameters)
{
  char Aux[100];

  sprintf(Aux,"%d",parameter1());
  Parameters["threshold"]=std::string(Aux);
}

/*************************************************************************/

void _filter_colormap_ui::color(QColor Color1)
{
  Color=Color1;
  Qtw_filter_colormap->parameter2(Color);
}

/*************************************************************************/

_qtw_filter_colormap::_qtw_filter_colormap(_window_xmapslab *Window1,_filter_colormap_ui *Filter1,std::string Box_name)
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
//  Spinbox_parameter1=new QSpinBox;
//  Spinbox_parameter1->setRange(0,100);
//  Spinbox_parameter1->setAlignment(Qt::AlignRight);
//  Spinbox_parameter1->setSuffix(" %");

//  parameter1(Filter->parameter1());

//  connect(Spinbox_parameter1,SIGNAL(valueChanged(int)),this,SLOT(parameter1_slot(int)));

  // Parameter2
  float Factor=Window->screen_height()/1080.0f;
  Button_parameter2=new _button_color_simple(QColor(255,0,0),Factor);

  connect(Button_parameter2,SIGNAL(colorChanged(QColor)),this,SLOT(parameter2_slot(QColor)));

//  QLabel *Label_parameter1=new QLabel("0 threshold");
  QLabel *Label_parameter2=new QLabel("Color");

//  Grid_parameter1->addWidget(Label_parameter1,0,0,Qt::AlignRight);
//  Grid_parameter1->addWidget(Spinbox_parameter1,0,1,Qt::AlignLeft);
  Grid_parameter1->addWidget(Label_parameter2,1,0,Qt::AlignRight);
  Grid_parameter1->addWidget(Button_parameter2,1,1,Qt::AlignLeft);

  Frame_parameter1->setLayout(Grid_parameter1);

  //
  Vertical_box_main->addWidget(Frame_parameter1);

  Group_box_main->setLayout(Vertical_box_main);
}

/*************************************************************************/

void _qtw_filter_colormap::parameter1(int Value)
{
  Spinbox_parameter1->blockSignals(true);
  Spinbox_parameter1->setValue(Value);
  Spinbox_parameter1->blockSignals(false);
}

/*************************************************************************/

void _qtw_filter_colormap::parameter2(QColor Color1)
{
  Button_parameter2->color(Color1);
}

/*************************************************************************/

void _qtw_filter_colormap::parameter1_slot(int Value)
{
  Filter->parameter1(Value);
  Window->update_filter(Filter->name());
}

/*************************************************************************/

void _qtw_filter_colormap::parameter2_slot(QColor Color1)
{
  Filter->parameter2(Color1);
  Window->update_filter(Filter->name());
}

