/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef _W_TABLE_H
#define _W_TABLE_H

#include <QDialog>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPixmap>
#include <QDialogButtonBox>
#include <QStringList>
#include <QTableWidget>
#include <QTableWidgetItem>

#include <iostream>

#include "project_data.h"

class _window;

/*************************************************************************/

class _w_table: public QDialog
{
Q_OBJECT

public:
  _w_table(_window *Window1,_project_data_ns::_project_data &Project_data);

//public slots:
//  void accept_slot();
//  void cancel_slot();

protected:
  _window *Window=nullptr;

   QTableWidget *Tablewidget=nullptr;
};

#endif
