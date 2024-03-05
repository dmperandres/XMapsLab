/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef PURE_COLOR_BAR_H
#define PURE_COLOR_BAR_H

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <iostream>
 
/*************************************************************************/
// class to select a color in a color gradient or the black color if Solid_black=true.
// if Solid_black is false, the a gray scale is added

class _pure_color_bar : public QWidget
{
Q_OBJECT

public:
  _pure_color_bar(QColor *Color1, bool Solid_black1=true);
  ~_pure_color_bar() {}

  QSize sizeHint() const override;
  QSize minimumSizeHint() const override;

  int row_at(QPoint Pos1);

  void solid_black(bool Value){Solid_black=Value;}

protected:
  void mouseMoveEvent(QMouseEvent *Event) override;
  void mouseReleaseEvent(QMouseEvent*) override;
  void paintEvent(QPaintEvent *Event) override;

protected:
  QRect Rect_black;
  QRect Rect_gradient;

  QColor *Color_fill=nullptr;

  // this is for making that the color bar to show a sloid black or a grayscale
  bool Solid_black=true;
};

#endif
