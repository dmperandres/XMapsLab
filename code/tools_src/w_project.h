/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef _W_PROJECT_H
#define _W_PROJECT_H

#include <QRadioButton>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QIntValidator>
#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QDateTime>
#include <QStringView>
#include <QCalendarWidget>

#include <iostream>

class _window_tools;

/*************************************************************************/

class _w_project: public QDialog
{
Q_OBJECT

public:
  _w_project(_window_tools *Window1);

public slots:

  void accept_slot(bool State);
  void cancel_slot(bool State);

//  void apply_slot();

protected:
  QLineEdit *Lineedit_project_folder_name=nullptr;
  QLineEdit *Lineedit_project_name=nullptr;
  QLineEdit *Lineedit_author=nullptr;
  QLineEdit *Lineedit_date=nullptr;
  QLineEdit *Lineedit_width_cm=nullptr;
  QLineEdit *Lineedit_height_cm=nullptr;
  QLineEdit *Lineedit_width_pixel=nullptr;
  QLineEdit *Lineedit_height_pixel=nullptr;
  QLineEdit *Lineedit_device=nullptr;
  QComboBox *Combobox_tube=nullptr;
  QComboBox *Combobox_xrf_data_adjusment=nullptr;
  QCalendarWidget *Calendar_widget=nullptr;

  _window_tools *Window=nullptr;
};

#endif
