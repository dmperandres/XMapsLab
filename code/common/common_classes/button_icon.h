/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef _BUTTON_ICON_H
#define _BUTTON_ICON_H

#include <QPushButton>
#include <QColor>
#include <QColorDialog>
#include <iostream>

//#include "glwidget.h"

class _table;

class _button_icon: public QPushButton
{
Q_OBJECT

public:
  _button_icon(int Row1, int Col1);

signals:
  void change_state(int,int);

protected:
  void mousePressEvent(QMouseEvent *Event);

  int Row;
  int Col;
  bool State;
  _table *Table=nullptr;
};

#endif
