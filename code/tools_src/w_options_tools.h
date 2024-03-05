/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef _W_OPTIONS_TOOLS_H
#define _W_OPTIONS_TOOLS_H

#include <QRadioButton>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QDialog>
#include <QSpinBox>
#include <QTabWidget>

#include <iostream>

//#include "button_color_simple.h"

//#include "glwidget_tools.h"

class _window_tools;

/*************************************************************************/

class _w_options_tools: public QDialog
{
Q_OBJECT

public:
  _w_options_tools(_window_tools *Window1);

public slots:
  void apply_slot();
  void close_slot();

protected:
  QSpinBox* Spinbox_general_font_size=nullptr;

  QTabWidget *Tab=nullptr;

  _window_tools *Window=nullptr;
};

#endif
