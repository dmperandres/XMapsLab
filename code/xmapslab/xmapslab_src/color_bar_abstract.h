//LIC

#ifndef COLOR_BAR_ABSTRACT_H
#define COLOR_BAR_ABSTRACT_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QStyleOptionFrame>
#include <QMenu>
#include <QApplication>
#include <QVBoxLayout>
#include <QColorDialog>

#include <iostream>
#include <vector>
#include <random>

#include "dialog_pure_color.h"
#include "palette_data.h"

class _window_xmapslab;

namespace _color_bar_abstract_ns {
  const int COLOR_BOX_WIDTH=10;
  const int OFFSET=50;

  const int MIN_NUM_CELLS_WIDTH=6;
  const int FONT_SIZE=14;

  const int HORIZONTAL_SPACE=5;
  const int TEXT_SPACE=2;

  const bool CHANGEABLE_DEFAULT=true;

  const float INITIAL_HUE=112;

  const float BORDER_SPACE_FACTOR=1;
  const float WHITE_SPACE_FACTOR=0.5;
  const float COLOR_BOX_FACTOR=2;
  const int COLOR_BOX_MIN=3;
}

//HEA
 
class _color_bar_abstract : public QWidget
{
Q_OBJECT

public:
  _color_bar_abstract(_palette_data_ns::_palette_color_type Palette_color_type1, int Num_stops1, std::vector<float> &Vec_values1, std::vector<QColor> &Vec_colors1, _window_xmapslab *Window1=nullptr);
  ~_color_bar_abstract() {}

  QSize sizeHint() const override;
  QSize minimumSizeHint() const override;

  int row_at(QPoint Pos1);

  bool pos_in_bar(QPoint Pos1);

  void set_data_values(float Start_value1,float End_value1){Start_value=Start_value1;End_value=End_value1;}

  void data_type_print(_palette_data_ns::_data_type_print Data_type_print1){Data_type_print=Data_type_print1;}
  _palette_data_ns::_data_type_print data_type_print(){return Data_type_print;}

  void changeable(bool Changeable1){Changeable=Changeable1;}
  bool changeable(){return Changeable;}

  std::vector<float> &vec_proportions(){return Vec_proportions;}
  std::vector<QColor> &vec_colors(){return Vec_colors;}

  std::vector<float> &values(){return Vec_original_values;}
  std::vector<QColor> &colors(){return Vec_original_colors;}

  int num_stops(){return  Num_stops;}

  void palette_type(_palette_data_ns::_palette_type Palette_type1){Palette_type=Palette_type1;}
  _palette_data_ns::_palette_type palette_type(){return Palette_type;}

  _palette_data_ns::_palette_color_type palette_color_type(){return Palette_color_type;}

  void show_data(bool Show_data1){Show_data=Show_data1;}

  QColor compute_new_tone(float Value, QColor Color1);
  QColor compute_new_color();

  int color_box_width(){return Color_box_width;}

  static QColor compute_random_color();

signals:
  void colorChanged(std::vector<float> &,std::vector<QColor> &,int);


protected:
  void paintCell(QPainter *Painter, int Pos,const QRect& Rect);
  void draw_text_int(QPainter &Painter);
  void draw_text_float(QPainter &Painter);
  void draw_text_scientific(QPainter &Painter);
  void draw_text_percent(QPainter &Painter);

protected:
  QColor Start_color;
  QColor End_color;

  std::vector<float> Vec_original_values;
  std::vector<QColor> Vec_original_colors;

  std::vector<float> Vec_values;
  std::vector<QColor> Vec_colors;

  float Min_value=0;
  float Max_value=1;

  std::vector<float> Vec_data;

  std::vector<QRect> Vec_rect;
  std::vector<int> Vec_translations;
  std::vector<float> Vec_proportions;

  QRect Rect_bar;

  float Start_value=0;
  float End_value=0;

  int Pos_selected=0;
  bool Color_selected=false;
  QRect Color_selected_rect;

  int Widget_height=0;
  int Widget_width=0;

  _palette_data_ns::_data_type_print Data_type_print;
  int VSpace=0;

  _palette_data_ns::_palette_type Palette_type;
  _palette_data_ns::_palette_color_type Palette_color_type;
  int Num_stops=0;

  bool Changeable;
  bool Show_data;

  QPoint Offset;
  QPoint Initial_position;

  int Color_box_width=0;

  _window_xmapslab *Window=nullptr;

  int Font_size=0;
  int Font_pixels_width=0;
  int Font_pixels_height=0;
};


#endif
