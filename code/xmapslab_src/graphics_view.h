/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef GRAPHICS_VIEW_H
#define GRAPHICS_VIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QTimeLine>
#include <QWidget>
#include <QScrollBar>
#include <iostream>

namespace _graphics_view_ns {
const float Zoom_step=1.01;
}

/*************************************************************************/

class _graphics_view : public QGraphicsView
{
Q_OBJECT

public:
  _graphics_view(QWidget *Parent=nullptr);

  void scaling_factor(float Factor1);

protected:
  void wheelEvent(QWheelEvent *Event);

private:
  float Factor;
};
#endif
