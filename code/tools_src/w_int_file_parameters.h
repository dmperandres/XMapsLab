/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef _W_INT_FILE_PARAMETERS_H
#define _W_INT_FILE_PARAMETERS_H

//#include <QRadioButton>
#include <QLineEdit>
//#include <QDoubleValidator>
//#include <QIntValidator>
#include <QDialog>
#include <iostream>

class _window_tools;

/*************************************************************************/

class _w_int_file_parameters: public QDialog
{
Q_OBJECT

public:
  _w_int_file_parameters(_window_tools *Window1);

public slots:
  void close_slot();

protected:
  // display
  QLineEdit *Lineedit_name=nullptr;
  QLineEdit *Lineedit_formula=nullptr;
  QLineEdit *Lineedit_XRF=nullptr;
  QLineEdit *Lineedit_RGB_color=nullptr;

  _window_tools *Window=nullptr;
};

#endif
