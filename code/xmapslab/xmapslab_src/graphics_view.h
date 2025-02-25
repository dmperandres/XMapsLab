//LIC

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

//HEA

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
