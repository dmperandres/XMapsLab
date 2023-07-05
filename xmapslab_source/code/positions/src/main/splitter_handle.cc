#include "splitter_handle.h"

/*************************************************************************/

_splitter_handle::_splitter_handle(Qt::Orientation orientation, QSplitter *parent):QSplitterHandle(orientation,parent)
{

}

/*************************************************************************/

void _splitter_handle::paintEvent(QPaintEvent *Event)
{
  int Widget_height = Event->rect().height();

  QPainter Painter(this);
  QRect Rect1(0,0,_splitter_handle_ns::WIDTH_BUTTON,_splitter_handle_ns::HEIGHT_BUTTON);

  Rect1.translate(0,Widget_height/2-20);
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

