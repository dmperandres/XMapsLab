/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "palette_data.h"

using namespace _palette_data_ns;

/*************************************************************************/

_palette_data::_palette_data(const _palette_data &Vec_palette_data1):
    Name(Vec_palette_data1.Name),Type(Vec_palette_data1.Type),Color_type(Vec_palette_data1.Color_type),Num_stops(Vec_palette_data1.Num_stops),Color(Vec_palette_data1.Color),Color_map(Vec_palette_data1.Color_map)
{
}

/*************************************************************************/

_palette_data &_palette_data::operator=(const _palette_data &Vec_palette_data1)
{
  Name=Vec_palette_data1.Name;
  Type=Vec_palette_data1.Type;
  Color_type=Vec_palette_data1.Color_type;
  Num_stops=Vec_palette_data1.Num_stops;
  Color_assigning=Vec_palette_data1.Color_assigning;
  Color=Vec_palette_data1.Color;

  Color_map=Vec_palette_data1.Color_map;

  return *this;
}

/*************************************************************************/

_palette_data::_palette_data(QString Name1, _palette_type Palette_type1, _palette_color_type Palette_color_type1, int Num_stops1, _palette_color_assigning_type Palette_color_assigning1, QColor Color1, std::vector<_vertex3f> Colors_fixed_palette1, _color_map_ns::_color_for_zero_value Color_for_zero_value1):
    Name(Name1),Type(Palette_type1), Color_type(Palette_color_type1), Num_stops(Num_stops1), Color_assigning(Palette_color_assigning1), Color(Color1), Colors_fixed_palette(Colors_fixed_palette1), Color_for_zero_value(Color_for_zero_value1)
{
  Color_map.color_for_zero_value(Color_for_zero_value1);

  Color_map.compute_regular_values(Num_stops);

  update();
}

/*************************************************************************/

void _palette_data::update()
{
  if (Type==_palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE){
    if (Color_type==_palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE){
      Color_map.compute_tones_sections(Color);
    }
    else{
      if (Color_assigning==_palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_MUTABLE){
        Color_map.compute_colors_sections(Color);
      }
      else{ //use a fixed palette
        Color_map.compute_colors_sections_fixed_palette(Colors_fixed_palette);
      }
    }
  }
  else{ // continuous
    if (Color_type==_palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE){
      Color_map.compute_tones_interpolations(Color);
    }
    else{
      if (Color_assigning==_palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_MUTABLE){
        Color_map.compute_colors_interpolations(Color);
      }
      else{ //use a fixed palette
        Color_map.compute_colors_interpolations_fixed_palette(Colors_fixed_palette);
      }
    }
  }
}

/*************************************************************************/

/*************************************************************************/

void _palette_data::color_type(_palette_color_type Color_type1)
{
  Color_type=Color_type1;

  update();
}

/*************************************************************************/

void _palette_data::type(_palette_data_ns::_palette_type Type1)
{
  Type=Type1;
  update();
}

/*************************************************************************/

void _palette_data::num_stops(int Num_stops1)
{
  Num_stops=Num_stops1;
  Color_map.compute_regular_values(Num_stops);
  update();
}

/*************************************************************************/

void _palette_data::color(QColor Color1)
{
  Color=Color1;
  update();
}
