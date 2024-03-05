/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef LAYER_CANNY_H
#define LAYER_CANNY_H

#include <QDialog>
#include <QGroupBox>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>

#include "line_edit.h"
#include <string>
#include "layer.h"

#define DEFINED_LAYER_CANNY

namespace _layer_canny_ns
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

  // parameter 2
  const std::string String_group_box_parameter2("Pixel transparency");

  // parameter 3
  const std::string String_group_box_parameter3("Inversion");

  // parameter 4
  const std::string String_group_box_parameter4("Canny size");
  const std::string String_label_parameter4_min("3");
  const std::string String_label_parameter4_max("7");
  const std::string String_label_parameter4_tooltip("Display the value of Canny size");
  const int Parameter4_min_value=1;
  const int Parameter4_max_value=3;
  const int Parameter4_single_step=1;
  const int Parameter4_page_step=1;
  const int Parameter4_tick_interval=1;
  const bool Parameter4_set_tracking=false;
  const std::string String_parameter4_tooltip("Controls the appearance of borders: more to the left, less to the right");

  // parameter 5
  const std::string String_group_box_parameter5("Threshold 1");
  const std::string String_label_parameter5_min("0 ");
  const std::string String_label_parameter5_max("255");
  const std::string String_label_parameter5_tooltip("Display the value of threshold 1");
  const int Parameter5_min_value=0;
  const int Parameter5_max_value=255;
  const int Parameter5_single_step=1;
  const int Parameter5_page_step=10;
  const int Parameter5_tick_interval=15;
  const bool Parameter5_set_tracking=false;
  const std::string String_parameter5_slider_tooltip("Controls the appearance of borders: more to the left, less to the right");

  //parameter6
  const std::string String_group_box_parameter6("Threshold 2");
  const std::string String_label_parameter6_min("0 ");
  const std::string String_label_parameter6_max("255");
  const std::string String_label_parameter6_tooltip("Display the value of threshold 2");
  const int Parameter6_min_value=0;
  const int Parameter6_max_value=255;
  const int Parameter6_single_step=1;
  const int Parameter6_page_step=10;
  const int Parameter6_tick_interval=15;
  const bool Parameter6_set_tracking=false;
  const std::string String_parameter6_slider_tooltip("Controls the appearance of borders: more to the left, less to the right");

  // Default values
  const int CANNY_SIZE_DEFAULT=3;// take care of the previous warning
  const int CANNY_THRESHOLD1_DEFAULT=100;
  const int CANNY_THRESHOLD2_DEFAULT=200;
  const bool CANNY_PILXEL_TRANSPARENCE_DEFAULT=false;

  const std::string BOX_TEXT="Canny parameters";
}

class _window;
class _qtw_layer_canny;

/*************************************************************************/

class _layer_canny : public _layer
{
public:
  _layer_canny();
  void reset_data();

  void update_layer();
  void update();

  void pixel_transparence(bool Value){Pixel_transparence=Value;}
  bool pixel_transparence(){return Pixel_transparence;}

  void canny_size(int Size){Canny_size=Size;}
  int canny_size(){return Canny_size;}

  void threshold1(int Threshold){Threshold1=Threshold;}
  int threshold1(){return Threshold1;}

  void threshold2(int Threshold){Threshold2=Threshold;}
  int threshold2(){return Threshold2;}

protected:
  int Canny_size,Threshold1,Threshold2;
  bool Pixel_transparence;
};

/*************************************************************************/

class _layer_canny_ui : public _layer_canny
{
public:
  _layer_canny_ui(_window *Window1, std::string Name1=_layer_canny_ns::BOX_TEXT);
  ~_layer_canny_ui();
  void reset_data();

  void show();
  void hide();
  void *get_link();
  void enable();
  void disable();
//  void read_parameters(std::map<std::string,std::string> &Parameters);
//  void write_parameters(std::map<std::string,std::string> &Parameters);
//  void get_parameters(std::map<std::string,std::string> &Parameters);

  void parameter1(int Value){_layer_canny::transparence(float(Value)/255.0f);}
  int parameter1(){return int(_layer_canny::transparence()*255.0f);}

  void parameter2(int Value){_layer_canny::pixel_transparence(bool(Value));}
  int parameter2(){return int(_layer_canny::pixel_transparence());}

  void parameter3(int Value){_layer_canny::inversion(bool(Value));}
  int parameter3(){return int(_layer_canny::inversion());}

  void parameter4(int Value){_layer_canny::canny_size(Value);}
  int parameter4(){return _layer_canny::canny_size();}

  void parameter5(int Value){_layer_canny::threshold1(Value);}
  int parameter5(){return _layer_canny::threshold1();}

  void parameter6(int Value){_layer_canny::threshold2(Value);}
  int parameter6(){return _layer_canny::threshold2();}

private:
  _qtw_layer_canny *Qtw_layer_canny=nullptr;
};

/*************************************************************************/

class _qtw_layer_canny: public QWidget
{
  Q_OBJECT
public:
  _qtw_layer_canny(_window *Window1,_layer_canny_ui *Filter1,std::string Box_name=_layer_canny_ns::BOX_TEXT);

  void show(){Group_box_main->show();}
  void hide(){Group_box_main->hide();}
  QGroupBox *get_link(){return Group_box_main;}
  void enable(){Group_box_main->setEnabled(true);}
  void disable(){Group_box_main->setEnabled(false);}

  void parameter1(int Value);
  void parameter2(int Value);
  void parameter3(int Value);
  void parameter4(int Value);
  void parameter5(int Value);
  void parameter6(int Value);

protected slots:
  void parameter1_slot(int Value);
  void parameter2_slot(int Value);
  void parameter3_slot(int Value);
  void parameter4_slot(int Value);
  void parameter5_slot(int Value);
  void parameter6_slot(int Value);

private:
  QGroupBox *Group_box_main=nullptr;
  QGroupBox *Group_box_parameter1=nullptr;
  QGroupBox *Group_box_parameter2=nullptr;
  QGroupBox *Group_box_parameter3=nullptr;
  QGroupBox *Group_box_parameter4=nullptr;
  QGroupBox *Group_box_parameter5=nullptr;
  QGroupBox *Group_box_parameter6=nullptr;

  // Transparence
  QSlider *Slider_parameter1=nullptr;
  QLineEdit *Line_edit_parameter1=nullptr;

  // Pixel transparence
  QCheckBox *Checkbox_parameter2=nullptr;

  // Inversion
  QCheckBox *Checkbox_parameter3=nullptr;

  // canny size
  QSlider *Slider_parameter4=nullptr;
  QLineEdit *Line_edit_parameter4=nullptr;

  // threshold1
  QSlider *Slider_parameter5=nullptr;
  QLineEdit *Line_edit_parameter5=nullptr;

  // threshold2
  QSlider *Slider_parameter6=nullptr;
  QLineEdit *Line_edit_parameter6=nullptr;

  _layer_canny_ui *Filter=nullptr;
  _window *Window=nullptr;
};
#endif
