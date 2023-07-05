/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#ifndef PALETTE_DATA_H
#define PALETTE_DATA_H

#include <QString>
#include <QColor>
#include <vector>

#include "color_map.h"

namespace _palette_data_ns {
  const std::vector<QString> Vec_names_data_type_print={"Float","Scientific","Integer","Per cent"};
  enum class _data_type_print: unsigned char {DATA_TYPE_PRINT_FLOAT,DATA_TYPE_PRINT_SCIENTIFIC,DATA_TYPE_PRINT_INT,DATA_TYPE_PRINT_PERCENT};

  enum class _data_type: unsigned char {DATA_TYPE_DISCRETE,DATA_TYPE_CONTINUOUS};
  enum class _color_type: unsigned char {COLOR_TYPE_TONE,COLOR_TYPE_COLOR};

  struct _palette_data_aux{
    QString Name;
    _data_type Data_type;
    _color_type Color_type;
    int Num_steps;
  };

  const std::vector<_palette_data_aux> Vec_palette_data_aux={
    {"Discrete_tone_2_interval",_data_type::DATA_TYPE_DISCRETE,_color_type::COLOR_TYPE_TONE,3},
    {"Discrete_tone_3_interval",_data_type::DATA_TYPE_DISCRETE,_color_type::COLOR_TYPE_TONE,4},
    {"Discrete_tone_4_interval",_data_type::DATA_TYPE_DISCRETE,_color_type::COLOR_TYPE_TONE,5},
    {"Discrete_tone_5_interval",_data_type::DATA_TYPE_DISCRETE,_color_type::COLOR_TYPE_TONE,6},
    {"Discrete_color_2_interval",_data_type::DATA_TYPE_DISCRETE,_color_type::COLOR_TYPE_COLOR,3},
    {"Discrete_color_3_interval",_data_type::DATA_TYPE_DISCRETE,_color_type::COLOR_TYPE_COLOR,4},
    {"Discrete_color_4_interval",_data_type::DATA_TYPE_DISCRETE,_color_type::COLOR_TYPE_COLOR,5},
    {"Discrete_color_5_interval",_data_type::DATA_TYPE_DISCRETE,_color_type::COLOR_TYPE_COLOR,6},
    {"Continuous_color_1_interval",_data_type::DATA_TYPE_CONTINUOUS,_color_type::COLOR_TYPE_COLOR,2},
    {"Continuous_color_2_interval",_data_type::DATA_TYPE_CONTINUOUS,_color_type::COLOR_TYPE_COLOR,3},
    {"Continuous_color_3_interval",_data_type::DATA_TYPE_CONTINUOUS,_color_type::COLOR_TYPE_COLOR,4},
    {"Continuous_color_4_interval",_data_type::DATA_TYPE_CONTINUOUS,_color_type::COLOR_TYPE_COLOR,5},
    {"Continuous_color_5_interval",_data_type::DATA_TYPE_CONTINUOUS,_color_type::COLOR_TYPE_COLOR,6},
    {"Continuous_tone_2_interval",_data_type::DATA_TYPE_CONTINUOUS,_color_type::COLOR_TYPE_TONE,3},
    {"Continuous_tone_3_interval",_data_type::DATA_TYPE_CONTINUOUS,_color_type::COLOR_TYPE_TONE,4},
    {"Continuous_tone_4_interval",_data_type::DATA_TYPE_CONTINUOUS,_color_type::COLOR_TYPE_TONE,5},
    {"Continuous_tone_5_interval",_data_type::DATA_TYPE_CONTINUOUS,_color_type::COLOR_TYPE_TONE,6},
  };
}

/*************************************************************************/

class _palette_data
{
public:

  _palette_data(){};

  _palette_data(QString Name1,_palette_data_ns::_data_type Data_type1,_palette_data_ns::_color_type Color_type1,int Num_steps1,QColor Color1,_color_map_ns::_color_for_zero_value Color_for_zero_value1);

  _palette_data(const _palette_data &Vec_palette_data1);

  _palette_data &operator=(const _palette_data &Vec_palette_data1);

  void update_values();

  void name(QString Name1){Name=Name1;}
  QString name(){return Name;}

  void color_type(_palette_data_ns::_color_type Color_type1);
  _palette_data_ns::_color_type color_type(){return Color_type;}

  void data_type(_palette_data_ns::_data_type Data_type1);
  _palette_data_ns::_data_type data_type(){return Data_type;};

  void num_steps(int Num_steps1);
  int num_steps(){return Num_steps;}

  void color(QColor Color1);
  QColor color(){return Color;}

  void update();

  std::vector<float> &vec_values(){return Color_map.Vec_values;}
  std::vector<QColor> &vec_colors(){return Color_map.Vec_colors;}

protected:
  QString Name="";
  _palette_data_ns::_data_type Data_type;
  _palette_data_ns::_color_type Color_type; // tone or color  
  int Num_steps=0;
  QColor Color;
  _color_map Color_map;
  _color_map_ns::_color_for_zero_value Color_for_zero_value;
};

#endif

