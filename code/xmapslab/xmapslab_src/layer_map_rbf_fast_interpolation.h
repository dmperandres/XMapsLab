//LIC

#ifndef LAYER_MAP_RBF_FAST_INTERPOLATION_H
#define LAYER_MAP_RBF_FAST_INTERPOLATION_H

#include <GL/glew.h>
#include <opencv.hpp>
#include <QDialog>
#include <QGroupBox>
#include <QSlider>
#include <QLabel>
#include <QComboBox>
#include "line_edit.h"
#include <string>

#include "layer.h"
#include "color_bar_abstract.h"
#include "pigment_data.h"

#include "common.h"
#include "vertex.h"

#include "layer_map.h"

#define DEFINED_LAYER_MAP_RBF_FAST_INTERPOLATION

namespace _layer_map_rbf_fast_interpolation_ns
{
  // parameter 1
  const std::string String_group_box_parameter1("Transparence");
  const std::string String_label_parameter1_min("0");
  const std::string String_label_parameter1_max("1");
  const std::string String_label_parameter1_tooltip("Display the value of the transparence");
  const int Parameter1_min_value=0;
  const int Parameter1_max_value=255;
  const int Parameter1_single_step=1;
  const int Parameter1_page_step=1;
  const int Parameter1_tick_interval=25;
  const bool Parameter1_set_tracking=false;
  const std::string String_parameter1_tooltip("Controls the value of the transparence");

  // parameter 2
  const std::string String_group_box_parameter2("Color mixing");

  const std::string String_label_parameter2_title("Min threshold");
  const std::string String_label_parameter2_min("0");
  const std::string String_label_parameter2_max("1");
  const std::string String_label_parameter2_tooltip("Display the value of the transparence");
  const int Parameter2_min_value=0;
  const int Parameter2_max_value=255;
  const int Parameter2_single_step=1;
  const int Parameter2_page_step=1;
  const int Parameter2_tick_interval=25;
  const bool Parameter2_set_tracking=false;
  const std::string String_parameter2_tooltip("Controls the value of the transparence");

  // parameter 3
  const std::string String_label_parameter3_title("Max threshold");
  const std::string String_label_parameter3_min("0");
  const std::string String_label_parameter3_max("1");
  const std::string String_label_parameter3_tooltip("Display the value of the transparence");
  const int Parameter3_min_value=0;
  const int Parameter3_max_value=255;
  const int Parameter3_single_step=1;
  const int Parameter3_page_step=1;
  const int Parameter3_tick_interval=25;
  const bool Parameter3_set_tracking=false;
  const std::string String_parameter3_tooltip("Controls the value of the transparence");

  // parameter 4
  const std::string String_group_box_parameter4("Data type print");

  // parameter 5
  const std::string String_group_box_parameter5("Radius");
  const std::string String_label_parameter5_min("Min");
  const std::string String_label_parameter5_max("Max");
  const std::string String_label_parameter5_tooltip("Display the value of the Radius");
  const int Parameter5_min_value=0;
  const int Parameter5_max_value=255;
  const int Parameter5_single_step=1;
  const int Parameter5_page_step=10;
  const int Parameter_tick_interval=25;
  const std::string String_parameter5_tooltip("Controls the value of the Radius");


  const std::string BOX_TEXT="Basic parameters";

  const std::vector<std::string> COLOR_MAPS={"Red","Green","Blue","Autum","Bone","Jet","Winter","Rainbow","Ocean","Summer","Spring","cool","Hsv","Pink","Hot"};

  const std::vector<QString> Vec_names_position_interpolation_type={"Homogeneous","Heterogeneous"};
  enum class _position_normalization_type:unsigned char {POSITION_NORMALIZATION_HOMOGENEOUS,POSITION_NORMALIZATION_HETEROGENEOUS};
  const _position_normalization_type NORMALIZATION_TYPE_DEFAULT=_position_normalization_type::POSITION_NORMALIZATION_HOMOGENEOUS;

  const std::vector<QString> Vec_names_rbf_fast_function={"Linear","Gaussian","Inverse Multiquadrics","Bump"};
  const std::vector<std::string> Vec_short_names_rbf_fast_function={"LIN","GAU","INV","BUM"};
  enum class _rbf_fast_function:unsigned char {RBF_FUNCION_LINEAR,RBF_FUNCION_GAUSSIAN,RBF_FUNCION_INVERSE_MULTIQUADRICS,RBF_FUNCION_BUMP};
  const _rbf_fast_function RBF_FAST_FUNCTION_DEFAULT=_rbf_fast_function::RBF_FUNCION_LINEAR;

}

class _window;
class _qtw_layer_map_rbf_fast_interpolation;

//HEA

class _layer_map_rbf_fast_interpolation: public _layer_map
{
public:
  _layer_map_rbf_fast_interpolation();
  ~_layer_map_rbf_fast_interpolation();

//  void add_input_data(std::vector<float> &Vec_coordinate_x1, std::vector<float> &Vec_coordinate_y1, std::vector<float> &Vec_value1);
//  void add_triangles_data(vector<_delaunay_triangulator_ns::_triangle> Triangles1){Triangles=Triangles1;}
  void create_buffers();

  void update_map();
  void update();

  float get_value(int Col,int Row);

  void data_type_print(_palette_data_ns::_data_type_print Data_type_print1){Data_type_print=Data_type_print1;}
  _palette_data_ns::_data_type_print data_type_print(){return Data_type_print;}

  void radius(float Radius1){Radius=Radius1;}
  float radius(){return Radius;}

  void function(_layer_map_rbf_fast_interpolation_ns::_rbf_fast_function Function1){Function=Function1;}
  _layer_map_rbf_fast_interpolation_ns::_rbf_fast_function function(){return Function;}

protected:
  _palette_data_ns::_data_type_print Data_type_print;
  float Radius;
  _layer_map_rbf_fast_interpolation_ns::_rbf_fast_function Function;
};

//HEA

class _layer_map_rbf_fast_interpolation_ui : public _layer_map_rbf_fast_interpolation
{
public:
  _layer_map_rbf_fast_interpolation_ui(_window *Window1, std::string Name1=_layer_map_rbf_fast_interpolation_ns::BOX_TEXT);
  //_layer_map_rbf_fast_interpolation_ui(_window Window1,std::map<std::string,std::string> &Parameters,std::string Name1=_layer_canny_ns::BOX_TEXT);
  ~_layer_map_rbf_fast_interpolation_ui();
  void reset_data();

  void show();
  void hide();
  void *get_link();
  void enable();
  void disable();
//  void read_parameters(std::map<std::string,std::string> &Parameters);
//  void write_parameters(std::map<std::string,std::string> &Parameters);
//  void get_parameters(std::map<std::string,std::string> &Parameters);

  void parameter1(int Value){_layer_map_rbf_fast_interpolation::transparency(float(Value)/255.0f);}
  void parameter1_ui(float Value);
  int parameter1(){return int(_layer_map_rbf_fast_interpolation::transparency()*255.0f);}

  void parameter2(int Value){_layer_map_rbf_fast_interpolation::color_mixing_min(float(Value)/255.0f);}
  void parameter2_ui(float Value);
  int parameter2(){return int(_layer_map_rbf_fast_interpolation::color_mixing_min()*255.0f);}

  void parameter3(int Value){_layer_map_rbf_fast_interpolation::color_mixing_max(float(Value)/255.0f);}
  void parameter3_ui(float Value);
  int parameter3(){return int(_layer_map_rbf_fast_interpolation::color_mixing_max()*255.0f);}

  void parameter4(int Value){_layer_map_rbf_fast_interpolation::data_type_print(_palette_data_ns::_data_type_print(Value));}
  void parameter4_ui(int Value);
  int parameter4(){return int(_layer_map_rbf_fast_interpolation::data_type_print());}

//  void colormap(int Value);

  void data_type_print(_palette_data_ns::_data_type_print Data_type_print1);

private:
  _qtw_layer_map_rbf_fast_interpolation *Qtw_layer_map_rbf_fast_interpolation_a=nullptr;
};

//HEA

class _qtw_layer_map_rbf_fast_interpolation: public QWidget
{
  Q_OBJECT
public:
  _qtw_layer_map_rbf_fast_interpolation(_window *Window1,_layer_map_rbf_fast_interpolation_ui *Filter1,std::string Box_name="Canny parameters");

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
  // Transparence
  QSlider *Slider_parameter1=nullptr;
//  QLineEdit *Line_edit_parameter1=nullptr;

  // color mixing min
  QSlider *Slider_parameter2=nullptr;

  // color mixing max
  QSlider *Slider_parameter3=nullptr;

  // Data type
  QComboBox *Combobox_parameter4=nullptr;

  _layer_map_rbf_fast_interpolation_ui *Filter=nullptr;
  _window *Window=nullptr;
};
#endif
