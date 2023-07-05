/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#ifndef LAYER_BASIC_H
#define LAYER_BASIC_H

#include <QDialog>
#include <QGroupBox>
#include <QSlider>
#include <QLabel>
#include "line_edit.h"
#include <string>
#include "layer.h"

#define DEFINED_LAYER_BASIC

namespace _layer_basic_ns
{
  // parameter 1
  const std::string String_group_box_parameter1("Transparency");
  const std::string String_label_parameter1_min("0");
  const std::string String_label_parameter1_max("1");
  const std::string String_label_parameter1_tooltip("Display the value of the transparency");
  const int Parameter1_min_value=0;
  const int Parameter1_max_value=255;
  const int Parameter1_single_step=1;
  const int Parameter1_page_step=1;
  const int Parameter1_tick_interval=25;
  const bool Parameter1_set_tracking=false;
  const std::string String_parameter1_tooltip("Controls the value of the transparency");

  const std::string BOX_TEXT="Basic parameters";
}

class _window;
class _qtw_layer_basic;

/*************************************************************************/

class _layer_basic : public _layer
{
public:
  _layer_basic();
  void reset_data();

  void update();
};

/*************************************************************************/

class _layer_basic_ui : public _layer_basic
{
public:
  _layer_basic_ui(_window *Window1, std::string Name1=_layer_basic_ns::BOX_TEXT);
  ~_layer_basic_ui();
  void reset_data();

  void show();
  void hide();
  void *get_link();
  void enable();
  void disable();
//  void read_parameters(std::map<std::string,std::string> &Parameters);
//  void write_parameters(std::map<std::string,std::string> &Parameters);
//  void get_parameters(std::map<std::string,std::string> &Parameters);

  void parameter1(int Value){_layer_basic::transparency(float(Value)/255.0f);}
  int parameter1(){return int(_layer_basic::transparency()*255.0f);}

private:
  _qtw_layer_basic *Qtw_layer_basic=nullptr;
};

/*************************************************************************/

class _qtw_layer_basic: public QWidget
{
  Q_OBJECT
public:
  _qtw_layer_basic(_window *Window1,_layer_basic_ui *Filter1,std::string Box_name="Canny parameters");

  void show(){Group_box_main->show();}
  void hide(){Group_box_main->hide();}
  QGroupBox *get_link(){return Group_box_main;}
  void enable(){Group_box_main->setEnabled(true);}
  void disable(){Group_box_main->setEnabled(false);}

  void parameter1(int Value);

protected slots:
  void parameter1_slot(int Value);

private:
  QGroupBox *Group_box_main=nullptr;
  QGroupBox *Group_box_parameter1=nullptr;

  // Transparence
  QSlider *Slider_parameter1=nullptr;
  QLineEdit *Line_edit_parameter1=nullptr;

  _layer_basic_ui *Filter=nullptr;
  _window *Window=nullptr;
};
#endif
