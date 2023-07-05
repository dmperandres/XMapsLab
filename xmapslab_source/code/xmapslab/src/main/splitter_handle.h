/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#ifndef SPLITTER_HANDLE
#define SPLITTER_HANDLE

#include <QSplitter>
#include <QSplitterHandle>
#include <QPainter>
#include <QPaintEvent>

#include <iostream>

namespace _splitter_handle_ns {
  const int WIDTH_BUTTON=3;
  const int HEIGHT_BUTTON=40;
}

/*************************************************************************/

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

