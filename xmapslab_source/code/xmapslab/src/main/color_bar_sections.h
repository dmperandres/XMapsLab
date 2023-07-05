/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#ifndef COLOR_BAR_SECTIONS_H
#define COLOR_BAR_SECTIONS_H

#include "color_bar_abstract.h"
 
class _window;

class _color_bar_sections : public _color_bar_abstract
{
Q_OBJECT

public:
  _color_bar_sections(_palette_data_ns::_color_type Color_type1,int Num_steps1,std::vector<float> &Vec_values1, std::vector<QColor> &Vec_colors1,_window *Window1=nullptr);

  void draw(QPainter &Painter, QRect Rect,int Font_size);

protected:
  void mousePressEvent(QMouseEvent *Event) override;
  void mouseMoveEvent(QMouseEvent *Event) override;
  void mouseReleaseEvent(QMouseEvent*) override;
  void mouseDoubleClickEvent(QMouseEvent *Event) override;
  void paintEvent(QPaintEvent *Event) override;

private:
  void compute_tones();
};

#endif
