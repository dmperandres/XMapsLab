/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef LAYER_DOG_H
#define LAYER_DOG_H

#include <QDialog>
#include <QGroupBox>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>
#include <string>
#include "layer_xmapslab.h"

#define DEFINED_LAYER_DOG

namespace _layer_dog_ns
{
  // parameter 1
  const std::string String_group_box_parameter1("Vec_transparency");
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

  // parameter 4
  const std::string String_group_box_parameter4("Gaussian threshold");
  const std::string String_label_parameter4_min("0 ");
  const std::string String_label_parameter4_max("255");
  const std::string String_label_parameter4_tooltip("Display the size of the gaussian threshold");
  const int Parameter4_min_value=0;
  const int Parameter4_max_value=255;
  const int Parameter4_single_step=1;
  const int Parameter4_page_step=10;
  const int Parameter4_tick_interval=15;
  const bool Parameter4_set_tracking=false;
  const std::string String_parameter4_tooltip("Controls the appearance of borders: more to the left, less to the right");

  // big size
  // parameter 5
  const std::string String_group_box_parameter5("Big gaussian size");
  const std::string String_label_parameter5_min("5  ");
  const std::string String_label_parameter5_max("151");
  const std::string String_label_parameter5_tooltip("Display the size of the gaussian filter");
  const int Parameter5_min_value=5;
  const int Parameter5_max_value=151;
  const int Parameter5_single_step=1;
  const int Parameter5_page_step=10;
  const int Parameter5_tick_interval=10;
  const bool Parameter5_set_tracking=false;
  const std::string String_parameter5_slider_tooltip("Controls the size of the gaussian filter");

  // small size
  //parameter6
  const std::string String_group_box_parameter6("Small gaussian size");
  const std::string String_label_parameter6_min("3  ");
  const std::string String_label_parameter6_max("151");
  const std::string String_label_parameter6_tooltip("Display the value ofthe size of the small gaussian");
  const int Parameter6_min_value=3;
  const int Parameter6_max_value=151;
  const int Parameter6_single_step=1;
  const int Parameter6_page_step=10;
  const int Parameter6_tick_interval=10;
  const bool Parameter6_set_tracking=false;
  const std::string String_parameter6_slider_tooltip("Controls the size of the gaussian filter");

  // Default values
  const int DOG_THRESHOLD_DEFAULT=250;
  const int DOG_BIG_GAUSSIAN_SIZE_DEFAULT=25;
  const int DOG_SMALL_GAUSSIAN_SIZE_DEFAULT=13;

  const bool PIXEL_TRANSPARENCY_DEFAULT=false;
  const std::string BOX_TEXT="DoG parameters";
}

class _window;
class _qtw_layer_dog;

/*************************************************************************/

class _layer_dog : public _layer_xmapslab
{
public:
  _layer_dog();
  void reset_data();

  void update_layer();
  void update();

  void pixel_transparency(bool Value){Pixel_transparency=Value;}
  bool pixel_transparency(){return Pixel_transparency;}
  
  void dog_threshold(int Threshold);
  int dog_threshold(){return Dog_threshold;}

  void big_gaussian_size(int Size);
  int big_gaussian_size(){return Big_gaussian_size;}

  void small_gaussian_size(int Size);
  int small_gaussian_size(){return Small_gaussian_size;}

protected:
  int Dog_threshold,Big_gaussian_size,Small_gaussian_size;
  bool Pixel_transparency;
};

/*************************************************************************/

class _layer_dog_ui : public _layer_dog
{
public:
  _layer_dog_ui(_window_xmapslab *Window1, std::string Name1=_layer_dog_ns::BOX_TEXT);
  ~_layer_dog_ui();
  void reset_data();

  void show();
  void hide();
  void *get_link();
  void enable();
  void disable();

  void parameter1(int Value){_layer_dog::transparency(float(Value)/255.0f);}
  int parameter1(){return int(_layer_dog::transparency()*255.0f);}

  void parameter2(int Value){_layer_dog::pixel_transparency(bool(Value));}
  int parameter2(){return int(_layer_dog::pixel_transparency());}

  void parameter4(int Value){_layer_dog::dog_threshold(Value);}
  int parameter4(){return _layer_dog::dog_threshold();}

  void parameter5(int Value){_layer_dog::big_gaussian_size(Value);}
  int parameter5(){return _layer_dog::big_gaussian_size();}

  void parameter6(int Value){_layer_dog::small_gaussian_size(Value);}
  int parameter6(){return _layer_dog::small_gaussian_size();}

private:
  _qtw_layer_dog *Qtw_layer_dog=nullptr;
};

/*************************************************************************/

class _qtw_layer_dog: public QWidget
{
  Q_OBJECT
public:
  _qtw_layer_dog(_window_xmapslab *Window1,_layer_dog_ui *Filter1,std::string Box_name=_layer_dog_ns::BOX_TEXT);

  void show(){Group_box_main->show();}
  void hide(){Group_box_main->hide();}
  QGroupBox *get_link(){return Group_box_main;}
  void enable(){Group_box_main->setEnabled(true);}
  void disable(){Group_box_main->setEnabled(false);}

  void parameter1(int Value);
  void parameter2(int Value);

  void parameter4(int Value);
  void parameter5(int Value);
  void parameter6(int Value);

protected slots:
  void parameter1_slot(int Value);
  void parameter2_slot(int Value);

  void parameter4_slot(int Value);
  void parameter5_slot(int Value);
  void parameter6_slot(int Value);

private:
  QGroupBox *Group_box_main=nullptr;
  QGroupBox *Group_box_parameter1=nullptr;
  QGroupBox *Group_box_parameter2=nullptr;

  QGroupBox *Group_box_parameter4=nullptr;
  QGroupBox *Group_box_parameter5=nullptr;
  QGroupBox *Group_box_parameter6=nullptr;

  // Vec_transparency
  QSlider *Slider_parameter1=nullptr;
  QLineEdit *Line_edit_parameter1=nullptr;

  // Pixel transparency
  QCheckBox *Checkbox_parameter2=nullptr;

  // dog size
  QSlider *Slider_parameter4=nullptr;
  QLineEdit *Line_edit_parameter4=nullptr;

  // threshold1
  QSlider *Slider_parameter5=nullptr;
  QLineEdit *Line_edit_parameter5=nullptr;

  // threshold2
  QSlider *Slider_parameter6=nullptr;
  QLineEdit *Line_edit_parameter6=nullptr;

  _layer_dog_ui *Filter=nullptr;
  _window_xmapslab *Window=nullptr;
};
#endif
