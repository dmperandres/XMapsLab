/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef LAYER_COMPOUND_FROM_ELEMENTS_H
#define LAYER_COMPOUND_FROM_ELEMENTS_H

#include <GL/glew.h>
#include <opencv.hpp>
#include <QDialog>
#include <QGroupBox>
#include <QSlider>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>
#include <string>

#include "layer_xmapslab.h"
#include "color_bar_abstract.h"
#include "pigment_data.h"

#include "common.h"
#include "vertex.h"

#include "layer_map.h"

#include "rbf/new_rbf_interpolation_2d.h"

#define DEFINED_LAYER_COMPOUND_FROM_ELEMENTS

namespace _layer_compound_from_elements_ns
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
  const std::string String_group_box_parameter2("Color mixing");

  const std::string String_label_parameter2_title("Min threshold");
  const std::string String_label_parameter2_min("0");
  const std::string String_label_parameter2_max("1");
  const std::string String_label_parameter2_tooltip("Display the value of the transparency");
  const int Parameter2_min_value=0;
  const int Parameter2_max_value=255;
  const int Parameter2_single_step=1;
  const int Parameter2_page_step=1;
  const int Parameter2_tick_interval=25;
  const bool Parameter2_set_tracking=false;
  const std::string String_parameter2_tooltip("Controls the value of the transparency");

  // parameter 3
  const std::string String_label_parameter3_title("Max threshold");
  const std::string String_label_parameter3_min("0");
  const std::string String_label_parameter3_max("1");
  const std::string String_label_parameter3_tooltip("Display the value of the transparency");
  const int Parameter3_min_value=0;
  const int Parameter3_max_value=255;
  const int Parameter3_single_step=1;
  const int Parameter3_page_step=1;
  const int Parameter3_tick_interval=25;
  const bool Parameter3_set_tracking=false;
  const std::string String_parameter3_tooltip("Controls the value of the transparency");

  // parameter 4
  const std::string String_group_box_parameter4("Data type print");

  const std::string BOX_TEXT="Basic parameters";

  const std::vector<std::string> COLOR_MAPS={"Red","Green","Blue","Autum","Bone","Jet","Winter","Rainbow","Ocean","Summer","Spring","cool","Hsv","Pink","Hot"};

//  enum class _triangulation_mode:unsigned char {TRIANGULATION_MODE_NONE,TRIANGULATION_MODE_NORMAL,TRIANGULATION_MODE_WITH_CORNERS};
}

class _window_xmapslab;
class _qtw_layer_compound_from_elements;

/*************************************************************************/

class _layer_compound_from_elements: public _layer_map
{
public:
  _layer_compound_from_elements();
  ~_layer_compound_from_elements();

  void add_input_data(std::vector<std::shared_ptr<cv::Mat>> &Vec_maps_intensities1, std::vector<float> &Vec_max_intensities1, std::vector<float> &Vec_percentages1, std::vector<float> &Vec_global_percentages1);
//  void add_triangles_data(vector<_delaunay_triangulator_ns::_triangle> Triangles1){Triangles=Triangles1;}
//  void create_buffers();

  float compute_operation(std::vector<float> &Vec_intensities);

  void update_map();
  void new_update_map();

  void update();

  float get_value(int Col,int Row);

  void data_type_print(_palette_data_ns::_data_type_print Data_type_print1){Data_type_print=Data_type_print1;}
  _palette_data_ns::_data_type_print data_type_print(){return Data_type_print;}

  float max_intensity(){return Max_intensity;}

protected:
//  std::vector<_delaunay_triangulator_ns::_triangle> Triangles;
  _palette_data_ns::_data_type_print Data_type_print;

  std::vector<std::shared_ptr<cv::Mat>> Vec_maps_intensities;
  std::vector<float> Vec_max_intensities;
  std::vector<float> Vec_percentages;
  std::vector<float> Vec_global_percentages;

  std::vector<std::vector<int>> Vec_permutations;

  int Num_elements=-1;

  float Max_intensity=0;
};

/*************************************************************************/

class _layer_compound_from_elements_ui : public _layer_compound_from_elements
{
public:
  _layer_compound_from_elements_ui(_window_xmapslab *Window1, std::string Name1=_layer_compound_from_elements_ns::BOX_TEXT);
  ~_layer_compound_from_elements_ui();
  void reset_data();

  void show();
  void hide();
  void *get_link();
  void enable();
  void disable();
//  void read_parameters(std::map<std::string,std::string> &Parameters);
//  void write_parameters(std::map<std::string,std::string> &Parameters);
//  void get_parameters(std::map<std::string,std::string> &Parameters);

  void parameter1(int Value){_layer_compound_from_elements::transparency(float(Value)/255.0f);}
  void parameter1_ui(float Value);
  int parameter1(){return int(_layer_compound_from_elements::transparency()*255.0f);}

  void parameter2(int Value){_layer_compound_from_elements::color_mixing_min(float(Value)/255.0f);}
  void parameter2_ui(float Value);
  int parameter2(){return int(_layer_compound_from_elements::color_mixing_min()*255.0f);}

  void parameter3(int Value){_layer_compound_from_elements::color_mixing_max(float(Value)/255.0f);}
  void parameter3_ui(float Value);
  int parameter3(){return int(_layer_compound_from_elements::color_mixing_max()*255.0f);}

  void parameter4(int Value){_layer_compound_from_elements::data_type_print(_palette_data_ns::_data_type_print(Value));}
  void parameter4_ui(int Value);
  int parameter4(){return int(_layer_compound_from_elements::data_type_print());}

//  void colormap(int Value);

  void data_type_print(_palette_data_ns::_data_type_print Data_type_print1);

private:
  _qtw_layer_compound_from_elements *Qtw_layer_compound_from_elements_a=nullptr;
};

/*************************************************************************/

class _qtw_layer_compound_from_elements: public QWidget
{
  Q_OBJECT
public:
  _qtw_layer_compound_from_elements(_window_xmapslab *Window1,_layer_compound_from_elements_ui *Filter1,std::string Box_name="Canny parameters");

  void show(){Group_box_main->show();Group_box_main->update();}
  void hide(){Group_box_main->hide();Group_box_main->update();}
  QGroupBox *get_link(){return Group_box_main;}
  void enable(){Group_box_main->setEnabled(true);}
  void disable(){Group_box_main->setEnabled(false);}

  void parameter1(int Value);
  void parameter2(int Value);
  void parameter3(int Value);
  void parameter4(int Value);

protected slots:
  void parameter1_slot(int Value);
  void parameter2_slot(int Value);
  void parameter3_slot(int Value);
  void parameter4_slot(int Value);

private:
  QGroupBox *Group_box_main=nullptr;
  QGroupBox *Group_box_parameter1=nullptr;
  QGroupBox *Group_box_parameter2=nullptr;
  QGroupBox *Group_box_parameter4=nullptr;
  // Vec_transparency
  QSlider *Slider_parameter1=nullptr;
//  QLineEdit *Line_edit_parameter1=nullptr;

  // color mixing min
  QSlider *Slider_parameter2=nullptr;

  // color mixing max
  QSlider *Slider_parameter3=nullptr;

  // Data type
  QComboBox *Combobox_parameter4=nullptr;

  _layer_compound_from_elements_ui *Filter=nullptr;
  _window_xmapslab *Window=nullptr;
};
#endif
