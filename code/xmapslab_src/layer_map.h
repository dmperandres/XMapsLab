/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef LAYER_MAP_H
#define LAYER_MAP_H

#include <QString>
#include <vector>

#include <GL/glew.h>
#include <opencv.hpp>
//#include <QDialog>
//#include <QGroupBox>
//#include <QSlider>
//#include <QLabel>
//#include <QComboBox>
//#include "line_edit.h"
//#include <string>

#include "layer_xmapslab.h"
#include "color_bar_abstract.h"
#include "pigment_data.h"

#include "common.h"
//#include "vertex.h"

#define DEFINED_LAYER_MAP

namespace _layer_map_ns
{
//  const std::vector<QString> Vec_interpolation_method_names={"Minimum Hypercube Distance","Minimum 2D Cartesian Distance","RBF","RBF Fast","Triangulation"};
//  enum class _map_interpolation_methods:unsigned char {MAP_INTERPOLATION_TYPE_MINIMUM_HYPERCUBE_DISTANCE,MAP_INTERPOLATION_TYPE_MINIMUM_2D_CARTESIAN_DISTANCE,MAP_INTERPOLATION_TYPE_RBF, MAP_INTERPOLATION_TYPE_RBF_FAST, MAP_INTERPOLATION_TYPE_TRIANGULATION};

  const std::vector<QString> Vec_interpolation_method_names={"Minimum Hypercube Distance","Minimum 2D Cartesian Distance","RBF","Triangulation"};

  enum class _map_interpolation_methods:unsigned char {MAP_INTERPOLATION_TYPE_MINIMUM_HYPERCUBE_DISTANCE,MAP_INTERPOLATION_TYPE_MINIMUM_2D_CARTESIAN_DISTANCE,MAP_INTERPOLATION_TYPE_RBF, MAP_INTERPOLATION_TYPE_TRIANGULATION};

  enum class _sampling_location:unsigned char {SAMPLING_LOCATION_CORNERS,SAMPLING_LOCATION_CENTERS};

  enum class _position_interpolation_type:unsigned char {POSITION_INTERPOLATION_TYPE_HOMOGENEOUS,POSITION_INTERPOLATION_TYPE_HETEROGENEOUS};

  const _sampling_location SAMPLING_LOCATION=_sampling_location::SAMPLING_LOCATION_CENTERS;

  const _map_interpolation_methods MAP_INTERPOLATION_TYPE_DEFAULT=_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_HYPERCUBE_DISTANCE;

  const std::vector<QString> Vec_name_probe={"1x1","3x3","5x5","7x7","9x9","11x11","13x13","15x15","25x25","49x49"};
  const std::vector<int> Vec_value_probe={0,1,2,3,4,5,6,7,12,24}; //half the width (+1)

  const int PROBE_DEFAULT=1; // 3x3

  const int MAX_DIMENSION_DEFAULT=512;

  struct _data{
    float x;
    float y;
    float Value;
  };
}

class _window_xmapslab;

/*************************************************************************/

class _layer_map: public _layer_xmapslab
{
public:
  _layer_map();
  ~_layer_map();

  void reset_data();

  void size(int Widht1,int Height1){Width=Widht1;Height=Height1;}

  void add_input_data(std::vector<float> &Vec_coordinate_x1,std::vector<float> &Vec_coordinate_y1,std::vector<float> &Vec_value1);
  void add_valid_positions(std::vector<bool> Vec_active_positionss1);

  void data_type(_palette_data_ns::_palette_type Palette_type1){Palette_type=Palette_type1;}
  _palette_data_ns::_palette_type data_type(){return Palette_type;}

  void set_colormap(std::vector<float> &Vec_proportions, std::vector<QColor> &Vec_colors1, _palette_data_ns::_palette_type Palette_type);

  void apply_colormap();

  void apply_color_mixing();

  float get_value(int Col,int Row);

  QColor end_color(){return End_color;}

protected:
  _window_xmapslab *Window=nullptr;

  int Width=0;
  int Height=0;

  int Width_data;
  int Height_data;

  QColor End_color;

  std::shared_ptr<cv::Mat> Input_color_image=nullptr;

  GLuint Program0;
  GLuint VAO1;

  GLuint Tex_input_image_normalized=-1;
  GLuint Tex_image_result=-1;
  GLuint Element_data=-1;
  GLuint Colors=-1;
  GLuint Valid_positions=-1;

  GLuint VBO_vertices=-1;
  GLuint VBO_vertices_colors=-1;

  bool Created_buffers=false;

  std::shared_ptr<cv::Mat> Color_table=nullptr;

  int Color_map=0;
  bool Computed=false;

  int Num_vertices=-1;

  std::vector<_layer_map_ns::_data> Vec_element_data;
  std::vector<int> Vec_active_positions;
  std::vector<cv::Vec4f> Vec_color;

  _palette_data_ns::_palette_type Palette_type;

  bool Colormap_changed=true;
};

#endif
