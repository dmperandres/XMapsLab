/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef FILTER_LOGIC_NOT
#define FILTER_LOGIC_NOT

#include <QDialog>
#include <QGroupBox>
#include <QSpinBox>
#include <QLabel>

// #include "line_edit.h"
#include <string>
#include "filter.h"

#include "filter_element.h"

#define DEFINED_FILTER_LOGIC_NOT

namespace _f_logic_not_ns
{
  // parameter 1
  const std::string String_group_box_parameter1("0 threshold");
//  const std::string String_label_parameter1_min("1  ");
//  const std::string String_label_parameter1_max("100");
//  const std::string String_label_parameter1_tooltip("Display the value of Kernel size");
//  const int Parameter1_min_value=1;
//  const int Parameter1_max_value=100;
//  const int Parameter1_single_step=1;
//  const int Parameter1_page_step=5;
//  const int Parameter1_tick_interval=5;
//  const bool Parameter1_set_tracking=false;
  const std::string String_parameter1_tooltip("Controls the threshold value to convert the data to binary: data < Threshold -> 0");
//  const int Parameter1_divisor=10;

  // Default values
  const int THRESHOLD_DEFAULT=_filter_ns::THRESHOLD_DEFAULT;
  const std::string FILTER_NAME="Logic NOT";
}

class _window_xmapslab;
class _qtw_filter_logic_not;

/*************************************************************************/

class _filter_logic_not : public _filter
{
public:
  _filter_logic_not();
  void reset_data();

  void threshold(int Threshold1){Threshold=Threshold1;}
  int threshold(){return Threshold;}

//  void color(QColor Color1){Color=Color1;}
//  QColor color(){return Color;}

  float get_max_value();

  void update();

protected:
  int Threshold=_filter_ns::THRESHOLD_DEFAULT;
};

/*************************************************************************/

class _filter_logic_not_ui : public _filter_logic_not
{
public:
  _filter_logic_not_ui(_window_xmapslab *Window1,std::string Name1=_f_logic_not_ns::FILTER_NAME);
  _filter_logic_not_ui(_window_xmapslab *Window1,std::map<std::string,std::string> &Parameters,std::string Name1=_f_logic_not_ns::FILTER_NAME);
  ~_filter_logic_not_ui();
  void reset_data();

  void show();
  void hide();
  void *get_link();
  void read_parameters(std::map<std::string,std::string> &Parameters);
  void write_parameters(std::map<std::string, std::string> &Parameters);

//  void color(QColor Color1);

  void parameter1(int Value){_filter_logic_not::threshold(Value);}
  int parameter1(){return _filter_logic_not::threshold();}

//  void parameter2(QColor Color1){_filter_logic_not::color(Color1);}
//  QColor parameter2(){return _filter_logic_not::color();}

private:
  _qtw_filter_logic_not *Qtw_filter_logic_not=nullptr;
};

/*************************************************************************/

class _qtw_filter_logic_not: public QWidget
{
  Q_OBJECT
public:

  _qtw_filter_logic_not(_window_xmapslab *Window1,_filter_logic_not_ui *Filter1,std::string Box_name=_f_logic_not_ns::FILTER_NAME);

  void show(){Group_box_main->show();}
  void hide(){Group_box_main->hide();}
  QGroupBox *get_link(){return Group_box_main;}

  void parameter1(int Value);
//  void parameter2(QColor Color1);

protected slots:
  void parameter1_slot(int Value);
//  void parameter2_slot(QColor Color1);

private:
  QGroupBox *Group_box_main=nullptr;
  QGroupBox *Group_box_parameter1=nullptr;

  // 0 Threshold
  QSpinBox *Spinbox_parameter1=nullptr;

  // color
  _button_color_simple *Button_parameter2=nullptr;

  _filter_logic_not_ui *Filter=nullptr;
  _window_xmapslab *Window=nullptr;
};
#endif
