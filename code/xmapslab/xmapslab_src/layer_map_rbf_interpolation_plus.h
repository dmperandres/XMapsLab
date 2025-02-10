//LIC

#ifndef LAYER_MAP_RBF_INTERPOLATION_PLUS_H
#define LAYER_MAP_RBF_INTERPOLATION_PLUS_H

#include <GL/glew.h>
#include <opencv.hpp>
#include <QDialog>
#include <QGroupBox>
#include <QSlider>
#include <QLabel>
#include <QComboBox>
#include <QMessageBox>
//#include "line_edit.h"
#include <string>

#include "layer_xmapslab.h"

#include "layer_map.h"

#include "layer_map_rbf_interpolation.h"

#include "rbf/new_rbf_interpolation_2d_plus.h"


#define DEFINED_LAYER_MAP_RBF_INTERPOLATION_PLUS

class _window;
class _qtw_layer_map_rbf_interpolation_plus;

//HEA

class _layer_map_rbf_interpolation_plus: public _layer_map_rbf_interpolation
{
public:
  _layer_map_rbf_interpolation_plus();
  ~_layer_map_rbf_interpolation_plus();

  void add_input_data(std::vector<float> &Vec_coordinate_x1, std::vector<float> &Vec_coordinate_y1, std::vector<float> &Vec_value1,float Epsilon1, std::vector<cv::Vec4f> &Vec_colors1);

  void update_map();

  void update();

protected:
  std::vector<cv::Vec4f> Colors;

  std::shared_ptr<cv::Mat> Image_normalized=nullptr;
};

//HEA

class _layer_map_rbf_interpolation_plus_ui: public _layer_map_rbf_interpolation_plus
{
public:
  _layer_map_rbf_interpolation_plus_ui(_window_xmapslab *Window1, std::string Name1=_layer_map_rbf_interpolation_ns::BOX_TEXT);
  ~_layer_map_rbf_interpolation_plus_ui();
  void reset_data();

  void show();
  void hide();
  void *get_link();
  void enable();
  void disable();
//  void read_parameters(std::map<std::string,std::string> &Parameters);
//  void write_parameters(std::map<std::string,std::string> &Parameters);
//  void get_parameters(std::map<std::string,std::string> &Parameters);

  void parameter1(int Value){_layer_map_rbf_interpolation_plus::transparency(float(Value)/255.0f);}
  void parameter1_ui(float Value);
  int parameter1(){return int(_layer_map_rbf_interpolation_plus::transparency()*255.0f);}

  void parameter2(int Value){_layer_map_rbf_interpolation_plus::color_mixing_min(float(Value)/255.0f);}
  void parameter2_ui(float Value);
  int parameter2(){return int(_layer_map_rbf_interpolation_plus::color_mixing_min()*255.0f);}

  void parameter3(int Value){_layer_map_rbf_interpolation_plus::color_mixing_max(float(Value)/255.0f);}
  void parameter3_ui(float Value);
  int parameter3(){return int(_layer_map_rbf_interpolation_plus::color_mixing_max()*255.0f);}

  void parameter4(int Value){_layer_map_rbf_interpolation_plus::data_type_print(_palette_data_ns::_data_type_print(Value));}
  void parameter4_ui(int Value);
  int parameter4(){return int(_layer_map_rbf_interpolation_plus::data_type_print());}

//  void colormap(int Value);

  void data_type_print(_palette_data_ns::_data_type_print Data_type_print1);

private:
  _qtw_layer_map_rbf_interpolation_plus *Qtw_layer_map_rbf_interpolation_plus_a=nullptr;
};

//HEA

class _qtw_layer_map_rbf_interpolation_plus: public QWidget
{
  Q_OBJECT
public:
  _qtw_layer_map_rbf_interpolation_plus(_window_xmapslab *Window1,_layer_map_rbf_interpolation_plus_ui *Filter1,std::string Box_name="Canny parameters");

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

  _layer_map_rbf_interpolation_plus_ui *Filter=nullptr;
  _window_xmapslab *Window=nullptr;
};
#endif
