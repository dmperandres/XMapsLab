//LIC

#ifndef LAYER_MAP_TRIANGULATION_H
#define LAYER_MAP_TRIANGULATION_H

#include <GL/glew.h>
#include <opencv.hpp>
#include <QDialog>
#include <QGroupBox>
#include <QSlider>
#include <QLabel>
#include <QComboBox>
#include <string>

#include "layer_xmapslab.h"
#include "color_bar_abstract.h"
#include "measurement_data.h"

#include "common.h"
#include "vertex.h"

#include "delaunay.h"

#include "layer_map.h"

#define DEFINED_LAYER_MAP_TRIANGULATION

namespace _layer_map_triangulation_ns
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

  const std::string BOX_TEXT="Basic parameters";

  const std::vector<std::string> COLOR_MAPS={"Red","Green","Blue","Autum","Bone","Jet","Winter","Rainbow","Ocean","Summer","Spring","cool","Hsv","Pink","Hot"};

  enum class _triangulation_mode:unsigned char {TRIANGULATION_MODE_NONE,TRIANGULATION_MODE_NORMAL,TRIANGULATION_MODE_WITH_CORNERS};
}

class _window;
class _qtw_layer_map_triangulation;

//HEA

class _layer_map_triangulation: public _layer_map
{
public:
  _layer_map_triangulation();
  ~_layer_map_triangulation();

  void add_triangles_data(std::vector<_delaunay_triangulator_ns::_triangle> Triangles1){Triangles=Triangles1;}

  void create_buffers();
  void update_map();
  void update();

  void data_type_print(_palette_data_ns::_data_type_print Data_type_print1){Data_type_print=Data_type_print1;}
  _palette_data_ns::_data_type_print data_type_print(){return Data_type_print;}

  void apply_transparence(std::shared_ptr<cv::Mat> Image_normalized);

protected:
  std::vector<_delaunay_triangulator_ns::_triangle> Triangles;
  _palette_data_ns::_data_type_print Data_type_print;
};

//HEA

class _layer_map_triangulation_ui : public _layer_map_triangulation
{
public:
  _layer_map_triangulation_ui(_window_xmapslab *Window1, std::string Name1=_layer_map_triangulation_ns::BOX_TEXT);
  ~_layer_map_triangulation_ui();
  void reset_data();

  void show();
  void hide();
  void *get_link();
  void enable();
  void disable();
//  void read_parameters(std::map<std::string,std::string> &Parameters);
//  void write_parameters(std::map<std::string,std::string> &Parameters);
//  void get_parameters(std::map<std::string,std::string> &Parameters);

  void parameter1(int Value){_layer_map_triangulation::transparency(float(Value)/255.0f);}
  void parameter1_ui(float Value);
  int parameter1(){return int(_layer_map_triangulation::transparency()*255.0f);}

  void parameter2(int Value){_layer_map_triangulation::color_mixing_min(float(Value)/255.0f);}
  void parameter2_ui(float Value);
  int parameter2(){return int(_layer_map_triangulation::color_mixing_min()*255.0f);}

  void parameter3(int Value){_layer_map_triangulation::color_mixing_max(float(Value)/255.0f);}
  void parameter3_ui(float Value);
  int parameter3(){return int(_layer_map_triangulation::color_mixing_max()*255.0f);}

  void parameter4(int Value){_layer_map_triangulation::data_type_print(_palette_data_ns::_data_type_print(Value));}
  void parameter4_ui(int Value);
  int parameter4(){return int(_layer_map_triangulation::data_type_print());}

//  void colormap(int Value);

  void data_type_print(_palette_data_ns::_data_type_print Data_type_print1);

private:
  _qtw_layer_map_triangulation *Qtw_layer_map_triangulation_a=nullptr;
};

//HEA

class _qtw_layer_map_triangulation: public QWidget
{
  Q_OBJECT
public:
  _qtw_layer_map_triangulation(_window_xmapslab *Window1,_layer_map_triangulation_ui *Filter1,std::string Box_name="Canny parameters");

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

  _layer_map_triangulation_ui *Filter=nullptr;
  _window_xmapslab *Window=nullptr;
};
#endif
