//LIC

#include "pure_color_bar.h"

//HEA

_pure_color_bar::_pure_color_bar(QColor *Color1,bool Solid_black1)
{
  Color_fill=Color1;
  Solid_black=Solid_black1;

  setFocusPolicy(Qt::StrongFocus);
  setMinimumSize(QSize(400,100));
}

//HEA

QSize _pure_color_bar::sizeHint() const
{
  ensurePolished();
  return QSize(400,100);
}

//HEA

QSize _pure_color_bar::minimumSizeHint() const
{
    ensurePolished();
    return QSize(400,100);
}

//HEA

int _pure_color_bar::row_at(QPoint Pos1)
{
  if (Rect_black.contains(Pos1)) return 0;
  else{
    if (Rect_gradient.contains(Pos1)) return 1;
    else return -1;
  }
}

//HEA

void _pure_color_bar::paintEvent(QPaintEvent *Event)
{
  QRect Rect = Event->rect();

  int Widget_height = Rect.height();
  int Widget_width = Rect.width();

  QPainter Painter(this);
  QColor Color;

  QRect rect_black(0,0,Widget_width-2,Widget_height/3-Widget_height/10);

  Rect_black=rect_black;

  if (Solid_black){
    // the up bar is draw with black color
    Painter.fillRect(rect_black,QBrush(QColor(0,0,0)));
    Painter.drawRect(rect_black);
  }
  else{
    // the up bar is draw with gradient between black a white
    QLinearGradient linearGrad(QPointF(0,0), QPointF(Widget_width-2,0));
    for (int i=0;i<256;i++) {
      Color.setRgb(i,i,i);
      linearGrad.setColorAt(float(i)/float(256),Color);
    }

    Painter.fillRect(rect_black,linearGrad);
    Painter.drawRect(rect_black);
  }

  // gradient
  QLinearGradient linearGrad(QPointF(0,0), QPointF(Widget_width-2,0));
  for (int i=0;i<36;i++) {
    Color.setHsv(i*10,255,255);
    Color.toRgb();
    linearGrad.setColorAt(float(i)/float(36),Color);
  }
  QRect rect_linear(0,0,Widget_width-2,Widget_height/3-Widget_height/10);

  // rect for the gradient
  rect_linear.translate(0,Widget_height/3);
  Rect_gradient=rect_linear;
  Painter.fillRect(rect_linear, linearGrad);
  Painter.drawRect(rect_linear);

  // rect for the selected color
  QRect rect_linear1(0,0,Widget_width/4-2,Widget_height/3-Widget_height/10);
  rect_linear1.translate(1.5*Widget_width/4+1,2*Widget_height/3);
  Painter.fillRect(rect_linear1,*Color_fill);
  Painter.drawRect(rect_linear1);

}

//HEA

void _pure_color_bar::mouseMoveEvent(QMouseEvent *Event)
{
  QPoint Pos=Event->pos();

  switch (row_at(Pos)){
  case 0:
    if (Solid_black) Color_fill->setRgb(0,0,0);
    else{
      float Xmin=Rect_black.x();

      float t=(Pos.x()-Xmin)/(float(Rect_black.width())-1.0f);

      Color_fill->setRgb(t*255,t*255,t*255);
    }

    repaint();
    break;
  case 1:
    {
    // compute the porportion
    float Xmin=Rect_gradient.x();

    float t=(Pos.x()-Xmin)/(float(Rect_gradient.width())-1.0f);

    Color_fill->setHsv(t*360,255,255);
    Color_fill->toRgb();

    repaint();
    }
    break;
  default:break;
  }
}

//HEA

void _pure_color_bar::mouseReleaseEvent(QMouseEvent *Event)
{
  QPoint Pos=Event->pos();
  switch (row_at(Pos)){
  case 0:
    if (Solid_black) Color_fill->setRgb(0,0,0);
    else{
      float Xmin=Rect_black.x();

      float t=(Pos.x()-Xmin)/(float(Rect_black.width())-1.0f);

      Color_fill->setRgb(t*255,t*255,t*255);
    }

    repaint();
    break;
  case 1:
    {
    // compute the porportion
    float Xmin=Rect_gradient.x();

    float t=(Pos.x()-Xmin)/(float(Rect_gradient.width())-1.0f);

    Color_fill->setHsv(t*360,255,255);
    Color_fill->toRgb();

    repaint();
    }
    break;
  default:break;
  }
}
