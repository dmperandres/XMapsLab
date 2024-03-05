/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef _W_NUMBER_H
#define _W_NUMBER_H

#include <QRadioButton>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QSpinBox>

#include <iostream>

#include "glwidget_positions.h"

class _window_positions;

/*************************************************************************/

class _w_number: public QDialog
{
Q_OBJECT

public:
  _w_number(int Position, _window_positions *Window1);

public slots:
//  void apply_slot();
//  void close_slot();

protected:
  QSpinBox *Spinbox_number=nullptr;

//  QTabWidget *Tab=nullptr;

  _window_positions *Window=nullptr;
};

#endif
