/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef _W_DIRECTORY_H
#define _W_DIRECTORY_H

#include <QDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <iostream>
#include <QDir>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

/*************************************************************************/

class _w_directory: public QDialog
{
Q_OBJECT

public:
enum _mode {MODE_DIR,MODE_FILE};

_w_directory(QWidget *Window1, QString Title1, QString Path1, QString *Directory1, _mode Mode1=MODE_DIR, QStringList Filters1=QStringList("*"));

public slots:
  void home_slot();
  void up_slot();
  void select_slot();  
  void cancel_slot();
  void item_clicked_slot(QListWidgetItem *Item);
  void item_double_clicked_slot(QListWidgetItem *Item);

protected:
  void update_list();

  QWidget *Window=nullptr;

  QString Home;
  QString Path;
  QString* Directory;
  QListWidget *List_folders=nullptr;
  _mode Mode;
  QStringList Filters;
};

#endif
