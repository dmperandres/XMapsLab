#ifndef SPLITTER_HANDLE
#define SPLITTER_HANDLE

#include <QSplitter>
#include <QSplitterHandle>
#include <QPainter>
#include <QPaintEvent>

#include <iostream>

namespace _splitter_handle_ns {
  const int WIDTH_BUTTON=5;
  const int HEIGHT_BUTTON=40;
}

class _splitter_handle: public QSplitterHandle
{
Q_OBJECT

public:
  _splitter_handle(Qt::Orientation orientation, QSplitter *parent =nullptr);

signals:
  void double_click();

protected:
  void paintEvent(QPaintEvent *Event) override;
  void mouseDoubleClickEvent(QMouseEvent *Event) override;

  QRect Rect;
};

#endif

