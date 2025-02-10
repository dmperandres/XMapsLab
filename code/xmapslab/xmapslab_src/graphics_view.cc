//LIC

#include "graphics_view.h"

//HEA

_graphics_view::_graphics_view(QWidget *Parent):QGraphicsView(Parent)
{
  Factor=1.0;
}


//HEA

void _graphics_view::scaling_factor(float Factor1)
{
  Factor=Factor1;
  resetTransform();
  scale(Factor,Factor);
  horizontalScrollBar()->setValue(-1000);
  verticalScrollBar()->setValue(-1000);
}

//HEA

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
