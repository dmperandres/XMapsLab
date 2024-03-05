/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "graphics_view.h"

/*************************************************************************/

_graphics_view::_graphics_view(QWidget *Parent):QGraphicsView(Parent)
{
  Factor=1.0;
}

/*************************************************************************/

void _graphics_view::scaling_factor(float Factor1)
{
  Factor=Factor1;
  resetTransform();
  scale(Factor,Factor);
  horizontalScrollBar()->setValue(-1000);
  verticalScrollBar()->setValue(-1000);
}

/*************************************************************************/

void _graphics_view::wheelEvent(QWheelEvent *Event)
{
  // See QWheelEvent documentation
//  QPoint Num_degrees = Event->angleDelta()/8;
//  float Num_steps = Num_degrees.y() / 15;

  if (Event->angleDelta().y()<0) Factor*=_graphics_view_ns::Zoom_step;
  else Factor/=_graphics_view_ns::Zoom_step;

  resetTransform();
  scale(Factor,Factor);
  horizontalScrollBar()->setValue(-1000);
  verticalScrollBar()->setValue(-1000);
}
