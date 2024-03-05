/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef BUTTON_COLOR_SIMPLE
#define BUTTON_COLOR_SIMPLE

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

class _window;

namespace _button_color_simple_ns {
  const int BUTTON_WIDTH=12;
  const int BUTTON_HEIGHT=12;

  const int BORDER_SPACE=1;
}

/*************************************************************************/
// this class is to show a square with a color that can run a dialog for changing the color
 
class _button_color_simple : public QWidget
{
Q_OBJECT

public:
  _button_color_simple(QColor Color1, bool Solid_black1=true,float Factor1=1);
  ~_button_color_simple() {}

  QSize sizeHint() const override;
  QSize minimumSizeHint() const override;

  void color(QColor Color1);
  QColor color(){return Color;}

//  int row_at(QPoint Pos1);

signals:
  void colorChanged(QColor);

protected:
  void mouseDoubleClickEvent(QMouseEvent *Event) override;
  void paintEvent(QPaintEvent *Event) override;

protected:
  QColor Color;
  _palette_data_ns::_palette_color_type Color_type=_palette_data_ns::PALETTE_COLOR_TYPE_DEFAULT;
  int Button_width=0;
  int Button_height=0;

  // this is for making that the color bar to show a sloid black or a grayscale
  bool Solid_black=true;
};

#endif
