//LIC

#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>
#include <QString>
#include <QColor>

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

  // window parameters
  const int WINDOW_X_POS_DEFAULT=50;
  const int WINDOW_Y_POS_DEFAULT=50;
  const int WINDOW_WIDTH_DEFAULT=1000;
  const int WINDOW_HEIGHT_DEFAULT=800;

  const float SCREEN_WIDTH_FACTOR=0.5f;
  const float SCREEN_HEIGHT_FACTOR=0.9f;

  const QColor SELECTED_COLOR(61,174,233);

  const _vertex3f COLORS[]={{0,0,0},{1,0,0},{0,1,0},{0,0,1},{0,1,1},{1,0,1},{1,1,0},{1,1,1},{0.5,0.5,0.5}};

  const int DEFAULT_COLOR=0;
  const unsigned char DEFAULT_TONE=240;

  const int BLACK=0;
  const int WHITE=7;

  const float MOUSE_SCALING_FACTOR=1.05f;

  const int DISPLAY_FONT_SIZE=0;
  const int DISPLAY_OUT_CIRCLE_SIZE=0;
  const QColor DISPLAY_FONT_COLOR=QColor(Qt::blue);
  const QColor DISPLAY_OUT_CIRCLE_COLOR=QColor(Qt::blue);
  const QColor DISPLAY_IN_CIRCLE_COLOR=QColor(Qt::yellow);
  const QColor DISPLAY_SELECTION_OUT_CIRCLE_COLOR=QColor(Qt::magenta);
  const QColor DISPLAY_SELECTION_IN_CIRCLE_COLOR=QColor(Qt::yellow);

  const std::vector<QString> Vec_names_zero_color={"Black","White"};
  const std::vector<QColor> Vec_zero_colors={QColor(Qt::black),QColor(Qt::white)};
  enum class _zero_color:unsigned char {ZERO_COLOR_BLACK, ZERO_COLOR_WHITE};
  const _zero_color ZERO_COLOR_DEFAULT=_zero_color::ZERO_COLOR_BLACK;

  enum class _units: unsigned char {UNITS_M,UNITS_CM,UNITS_MM,UNITS_PX,UNITS_N};
  enum class _xray_data_type: unsigned char {XRAY_DATA_TYPE_XRF,XRAY_DATA_TYPE_XRD};
  enum class _cs_origin: unsigned char {CS_ORIGIN_TOP_LEFT,CS_ORIGIN_BOTTOM_LEFT};

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


