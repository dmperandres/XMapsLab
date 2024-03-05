/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef _W_READ_INT_H
#define _W_READ_INT_H

#include <QRadioButton>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QDialog>
#include <QSpinBox>
#include <QTabWidget>

#include <iostream>

class _window_tools;

/*************************************************************************/

class _w_read_int: public QDialog
{
Q_OBJECT

public:
  _w_read_int(_window_tools *Window1,int* Number1);

public slots:
  void ok_slot();
//  void cancel_slot();

protected:
  QSpinBox* Spinbox_int_number=nullptr;

  int *Number=nullptr;

  _window_tools *Window=nullptr;
};

#endif
