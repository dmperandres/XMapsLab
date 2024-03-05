/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef LAYER_POSITIONS_POSITIONS_H
#define LAYER_POSITIONS_POSITIONS_H

#include <QDialog>
#include <QGroupBox>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>
#include <QPainterPath>
#include <string>
//#include <deque>
#include <vector>

#include "layer_positions.h"
#include "vertex.h"
#include "project_data.h"

#include "common.h"

#define DEFINED_LAYER_POSITIONS_POSITIONS

/*************************************************************************/

class _layer_positions_positions : public _layer_positions
{
public:
  _layer_positions_positions();
  void reset_data();
  void add_input_data(std::vector<_common_ns::_position_data> &Vec_positions1);
  void size(int Widht1,int Height1){Width=Widht1;Height=Height1;}
  void selected_position(int Selected_position1,bool Position_active1){Selected_position=Selected_position1;Position_active=Position_active1;}

  void parameters(int Display_font_size1,int Display_out_circle_size1,QColor Display_font_color1, QColor Display_out_circle_color1, QColor Display_in_circle_color1, QColor Display_selection_out_circle_color1, QColor Display_selection_in_circle_color1);

  void draw(QPainter &Painter, float Width1, float Height1, int Display_font_size1, int Display_out_circle_size1, QColor Font_color1,  QColor Out_circle_color1, QColor In_circle_color1);

  void update();

protected:
  std::vector<_common_ns::_position_data> Vec_positions;
  int Width;
  int Height;
  _project_data_ns::_cs_origin CS_origin=_project_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT;

  int Display_font_size;
  int Display_out_circle_size;
  QColor Display_font_color;
  QColor Display_out_circle_color;
  QColor Display_in_circle_color;
  QColor Display_selection_out_circle_color;
  QColor Display_selection_in_circle_color;

  int Selected_position;
  int Position_active=false;
};

/*************************************************************************/

class _layer_positions_positions_ui : public _layer_positions_positions
{
public:
//  _layer_positions_positions_ui(_window *Window1, std::string Name1=_f_basic_ns::BOX_TEXT);
  //_layer_basic_ui(_window Window1,std::map<std::string,std::string> &Parameters,std::string Name1=_f_canny_ns::BOX_TEXT);
  ~_layer_positions_positions_ui(){};
  void reset_data(){};

  void show(){};
  void hide(){};
  void *get_link(){return nullptr;}
};

#endif
