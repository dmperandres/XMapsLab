/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#include "palette_data.h"

using namespace _palette_data_ns;

/*************************************************************************/

_palette_data::_palette_data(const _palette_data &Vec_palette_data1):
Name(Vec_palette_data1.Name),Data_type(Vec_palette_data1.Data_type),Color_type(Vec_palette_data1.Color_type),Num_steps(Vec_palette_data1.Num_steps),Color(Vec_palette_data1.Color),Color_map(Vec_palette_data1.Color_map)
{
}

/*************************************************************************/

_palette_data &_palette_data::operator=(const _palette_data &Vec_palette_data1)
{
  Name=Vec_palette_data1.Name;
  Data_type=Vec_palette_data1.Data_type;
  Color_type=Vec_palette_data1.Color_type;
  Num_steps=Vec_palette_data1.Num_steps;
  Color=Vec_palette_data1.Color;
  Color_map=Vec_palette_data1.Color_map;

  return *this;
}

/*************************************************************************/

_palette_data::_palette_data(QString Name1, _data_type Data_type1, _color_type Color_type1, int Num_steps1, QColor Color1, _color_map_ns::_color_for_zero_value Color_for_zero_value1):
Name(Name1),Data_type(Data_type1),Color_type(Color_type1),Num_steps(Num_steps1),Color(Color1),Color_for_zero_value(Color_for_zero_value1)
{
  Color_map.color_for_zero_value(Color_for_zero_value1);
  Color_map.compute_regular_values(Num_steps);

  update();
}

/*************************************************************************/

void _palette_data::update()
{
  if (Data_type==_palette_data_ns::_data_type::DATA_TYPE_DISCRETE){
    if (Color_type==_palette_data_ns::_color_type::COLOR_TYPE_TONE){
      Color_map.compute_tones_sections(Color);
    }
    else{
      Color_map.compute_colors_sections(Color);
    }
  }
  else{
    if (Color_type==_palette_data_ns::_color_type::COLOR_TYPE_TONE){
      Color_map.compute_tones_interpolations(Color);
    }
    else{
      Color_map.compute_colors_interpolations(Color);
    }
  }
}

/*************************************************************************/

void _palette_data::color_type(_palette_data_ns::_color_type Color_type1)
{
  Color_type=Color_type1;

  update();
}

/*************************************************************************/

void _palette_data::data_type(_palette_data_ns::_data_type Data_type1)
{
  Data_type=Data_type1;
  update();
}

/*************************************************************************/

void _palette_data::num_steps(int Num_steps1)
{
  Num_steps=Num_steps1;
  Color_map.compute_regular_values(Num_steps);
  update();
}

/*************************************************************************/

void _palette_data::color(QColor Color1)
{
  Color=Color1;
  update();
}
