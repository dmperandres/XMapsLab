/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef FILTER_COLORMAP
#define FILTER_COLORMAP

#include <QDialog>
#include <QGroupBox>
#include <QSpinBox>
#include <QLabel>

// #include "line_edit.h"
#include <string>
#include "filter.h"

#include "filter_element.h"

#define DEFINED_FILTER_COLORMAP

namespace _f_colormap_ns
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
//  const std::string String_parameter1_tooltip("Controls the effect on the dilation");
//  const int Parameter1_divisor=10;

  // Default values
  const int THRESHOLD_DEFAULT=_filter_ns::THRESHOLD_DEFAULT;

  const std::string FILTER_NAME="Combination element";
}

class _window;
class _qtw_filter_colormap;

/*************************************************************************/

class _filter_colormap : public _filter
{
public:
  _filter_colormap();
  void reset_data();

  void threshold(int Threshold1){Threshold=Threshold1;}
  int threshold(){return Threshold;}

  void color(QColor Color1);
  QColor color(){return Color;}

  void update();

protected:
  int Threshold=_filter_ns::THRESHOLD_DEFAULT;
};

/*************************************************************************/

class _filter_colormap_ui : public _filter_colormap
{
public:
  _filter_colormap_ui(_window_xmapslab *Window1, std::string Name1="Arithmeti parameters");
  _filter_colormap_ui(_window_xmapslab *Window1,std::map<std::string,std::string> &Parameters,std::string Name1="Element parameters");
  ~_filter_colormap_ui();
  void reset_data();

  void show();
  void hide();
  void *get_link();
  void read_parameters(std::map<std::string,std::string> &Parameters);
  void write_parameters(std::map<std::string, std::string> &Parameters);

  void color(QColor Color1);

  void parameter1(int Value){_filter_colormap::threshold(Value);}
  int parameter1(){return _filter_colormap::threshold();}

  void parameter2(QColor Color1){_filter_colormap::color(Color1);}
  QColor parameter2(){return _filter_colormap::color();}

private:
  _qtw_filter_colormap *Qtw_filter_colormap=nullptr;
};

/*************************************************************************/

class _qtw_filter_colormap: public QWidget
{
  Q_OBJECT
public:

  _qtw_filter_colormap(_window_xmapslab *Window1, _filter_colormap_ui *Filter1, std::string Box_name="Element parameters");

  void show(){Group_box_main->show();}
  void hide(){Group_box_main->hide();}
  QGroupBox *get_link(){return Group_box_main;}

  void parameter1(int Value);
  void parameter2(QColor Color1);

protected slots:
  void parameter1_slot(int Value);
  void parameter2_slot(QColor Color1);

private:
  QGroupBox *Group_box_main=nullptr;
  QGroupBox *Group_box_parameter1=nullptr;

  // 0 Threshold
  QSpinBox *Spinbox_parameter1=nullptr;

  // color
  _button_color_simple *Button_parameter2=nullptr;

  _filter_colormap_ui *Filter=nullptr;
  _window_xmapslab *Window=nullptr;
};
#endif
