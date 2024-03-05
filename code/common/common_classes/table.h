/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef TABLE_H
#define TABLE_H

#include <QTableWidget>
#include <QPushButton>
#include <QPixmap>
#include <QIcon>
#include <QSize>
#include <QHeaderView>
#include <QDropEvent>
#include <iostream>
#include <vector>

#include "button_icon.h"

class _window;

/*************************************************************************/

class _table: public QTableWidget
{
Q_OBJECT

public:

  _table(std::string Name1,QWidget *Parent1);
  std::string name(){return Name;}

protected:
  std::string Name;
  QWidget *Parent=nullptr;
};

#endif
