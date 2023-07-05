//LIC

#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>
#include <QString>

#include "vertex.h"

namespace _common_ns
{
  enum class _color_model:unsigned char {COLOR_MODEL_RGB,COLOR_MODEL_HLS,COLOR_MODEL_HSV,COLOR_MODEL_LAB,COLOR_MODEL_LUV,COLOR_MODEL_LAST};
  const std::vector<QString> Vec_names_color_model={"RGB","HLS","HSV","LAB","LUB"};
  const _color_model COLOR_MODEL_DEFAULT=_color_model::COLOR_MODEL_RGB;

  // read
  const char FROM_DECIMAL_SEPARATOR=',';
  const char TO_DECIMAL_SEPARATOR='.';
  // write
  const char GOAL_DECIMAL_SEPARATOR=',';

  // num max decimals for color bar
  const int NUM_MAX_DECIMALS=10;

  // UI font size
  const int UI_FONT_SIZE_DEFAULT=12;

  struct _result_linear_regresion{
    float Slope=0;
    float Intercept=0;
    float Correlation_coefficient=0;
  };

  struct _value_position{
    float Value=0;
    int Position=-1;
    float Position_kev=-1;
  };

  struct _peak_data{
    int Position=-1;
    int Start_pos=-1;
    int End_pos=-1;
    float Height=-1;
    int Width=0;
    float Area=0;
    float Relative_area=0;
  };

  struct _position_data{
    int Position_index=-1;
    _vertex2i Coordinates;
    bool Active=false;
  };
}

#endif


