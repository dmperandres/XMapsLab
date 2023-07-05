/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#ifndef SPLITTER
#define SPLITTER

#include <QSplitter>
#include <QSplitterHandle>
#include <QPainter>
#include <QPaintEvent>

#include <iostream>

/*************************************************************************/

class _splitter: public QSplitter
{
public:
  _splitter(Qt::Orientation orientation, QWidget *parent =nullptr);

protected:
  QSplitterHandle *createHandle() override;
};

#endif

