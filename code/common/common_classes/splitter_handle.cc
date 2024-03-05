#include "splitter_handle.h"

/*************************************************************************/

_splitter_handle::_splitter_handle(Qt::Orientation orientation, QSplitter *parent):QSplitterHandle(orientation,parent)
{

}

/*************************************************************************/

void _splitter_handle::paintEvent(QPaintEvent *Event)
{
  QRect Rect1;

  QPainter Painter(this);
  if (orientation()==Qt::Horizontal){
    int Widget_height = Event->rect().height();
    Rect1.setRect(0,0,_splitter_handle_ns::WIDTH_BUTTON,_splitter_handle_ns::HEIGHT_BUTTON);
    Rect1.translate(0,Widget_height/2-20);
  }
  else{
    int Widget_width = Event->rect().width();
    Rect1.setRect(0,0,_splitter_handle_ns::HEIGHT_BUTTON,_splitter_handle_ns::WIDTH_BUTTON);
    Rect1.translate(Widget_width/2-20,0);
  }
  Rect=Rect1;
  QBrush Brush(QColor(255,0,0));
  Painter.fillRect(Rect1,Brush);
}

/*************************************************************************/

void _splitter_handle::mouseDoubleClickEvent(QMouseEvent *Event)
{
  if (Rect.contains(Event->pos())){
//    cout << "doble" << endl;
    emit double_click();
  }
}

