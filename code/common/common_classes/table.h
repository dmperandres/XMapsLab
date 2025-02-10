//LIC

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

//HEA

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
