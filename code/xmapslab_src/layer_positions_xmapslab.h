/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef LAYER_POSITIONS_XMAPSLAB_H
#define LAYER_POSITIONS_XMAPSLAB_H

#include <QDialog>
#include <QGroupBox>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>
#include <string>
#include <vector>
#include <QPainterPath>

#include "layer_xmapslab.h"
#include "layer_map_triangulation.h"
#include "pigment_data.h"

#include "project_data.h"

#include "delaunay.h"

#define DEFINED_LAYER_BASIC

namespace _layer_positions_xmapslab_ns
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

  const std::string BOX_TEXT="Basic parameters";

}

class _window;
class _qtw_layer_positions_xmapslab;

/*************************************************************************/

class _layer_positions_xmapslab : public _layer_xmapslab
{
public:
  _layer_positions_xmapslab();
  void reset_data();
  void add_valid_coordinates(std::vector<bool> Vec_valid_coordinates1);
  void add_coordinates(std::vector<float> Vec_coordinate_x1,std::vector<float> Vec_coordinate_y1);
  void add_coordinates_with_corners(std::vector<float> Vec_coordinate_x1,std::vector<float> Vec_coordinate_y1);

  void cs_origin(_project_data_ns::_cs_origin CS_origin1){CS_origin=CS_origin1;}
  void size(int Widht1,int Height1){Width=Widht1;Height=Height1;}
  void device_ratio(float Device_ratio1){Device_ratio=Device_ratio1;}
  void triangles(std::vector<_delaunay_triangulator_ns::_triangle> &Triangles1){Triangles=Triangles1;}
  void triangles_with_corners(std::vector<_delaunay_triangulator_ns::_triangle> &Triangles1){Triangles_with_corners=Triangles1;}

  void pixel_transparency(bool Value){Pixel_transparency=Value;}
  bool pixel_transparency(){return Pixel_transparency;}

  void parameters(int Display_font_size1,int Display_out_circle_size1,QColor Display_font_color1, QColor Display_out_circle_color1, QColor Display_in_circle_color1);

  void draw_positions(bool Value){Draw_positions=Value;}
  void draw_triangulation_mode(_layer_map_triangulation_ns::_triangulation_mode Triangulation_mode1){Triangulation_mode=Triangulation_mode1;}

  void draw(QPainter &Painter, float Width1, float Height1);

  void update();
protected:
  std::vector<float> Vec_coordinate_x;
  std::vector<float> Vec_coordinate_y;
  std::vector<float> Vec_coordinate_x_corners;
  std::vector<float> Vec_coordinate_y_corners;
  std::vector<bool> Vec_valid_coordinates;
  int Width;
  int Height;
  bool Pixel_transparency;
  _project_data_ns::_cs_origin CS_origin=_project_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT;
  float Device_ratio=1;

  int Display_font_size;
  int Display_out_circle_size;
  QColor Display_font_color;
  QColor Display_out_circle_color;
  QColor Display_in_circle_color;
  QColor Display_line_color;

  bool Draw_positions=false;
  _layer_map_triangulation_ns::_triangulation_mode Triangulation_mode=_layer_map_triangulation_ns::_triangulation_mode::TRIANGULATION_MODE_NONE;

  std::vector<_delaunay_triangulator_ns::_triangle> Triangles;
  std::vector<_delaunay_triangulator_ns::_triangle> Triangles_with_corners;
};

/*************************************************************************/

class _layer_positions_xmapslab_ui : public _layer_positions_xmapslab
{
public:
  _layer_positions_xmapslab_ui(_window_xmapslab *Window1, std::string Name1=_layer_positions_xmapslab_ns::BOX_TEXT);
  ~_layer_positions_xmapslab_ui();
  void reset_data();

  void show();
  void hide();
  void *get_link();
  void enable();
  void disable();
//  void read_parameters(std::map<std::string,std::string> &Parameters);
//  void write_parameters(std::map<std::string,std::string> &Parameters);
//  void get_parameters(std::map<std::string,std::string> &Parameters);

  void parameter1(int Value){_layer_positions_xmapslab::transparency(float(Value)/255.0f);}
  int parameter1(){return int(_layer_positions_xmapslab::transparency()*255.0f);}

  void parameter2(int Value){_layer_positions_xmapslab::pixel_transparency(bool(Value));}
  int parameter2(){return int(_layer_positions_xmapslab::pixel_transparency());}

private:
  _qtw_layer_positions_xmapslab *Qtw_layer_positions_xmapslab=nullptr;
};

/*************************************************************************/

class _qtw_layer_positions_xmapslab: public QWidget
{
  Q_OBJECT
public:
  _qtw_layer_positions_xmapslab(_window_xmapslab *Window1,_layer_positions_xmapslab_ui *Filter1,std::string Box_name="Canny parameters");

  void show(){Group_box_main->show();}
  void hide(){Group_box_main->hide();}
  QGroupBox *get_link(){return Group_box_main;}
  void enable(){Group_box_main->setEnabled(true);}
  void disable(){Group_box_main->setEnabled(false);}

  void parameter1(int Value);
  void parameter2(int Value);

protected slots:
  void parameter1_slot(int Value);
  void parameter2_slot(int Value);

private:
  QGroupBox *Group_box_main=nullptr;
  QGroupBox *Group_box_parameter1=nullptr;

  // Vec_transparency
  QSlider *Slider_parameter1=nullptr;
  QLineEdit *Line_edit_parameter1=nullptr;

  // Pixel transparency
  QCheckBox *Checkbox_parameter2=nullptr;

  _layer_positions_xmapslab_ui *Filter=nullptr;
  _window_xmapslab *Window=nullptr;
};
#endif
