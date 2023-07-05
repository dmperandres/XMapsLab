//LIC

#ifndef _W_DIRECTORY_H
#define _W_DIRECTORY_H

#include <QDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <iostream>

class _window;

//HEA

class _w_directory: public QDialog
{
Q_OBJECT

public:
  _w_directory(_window *Window1, QString Path1, QString *Directory1);

public slots:
  void home_slot();
  void up_slot();
  void select_slot();  
  void cancel_slot();
  void item_clicked_slot(QListWidgetItem *Item);
  void item_double_clicked_slot(QListWidgetItem *Item);

protected:
  void update_list();

  _window *Window=nullptr;

  QString Home;
  QString Path;
  QString* Directory;
  QListWidget *List_folders=nullptr;
};

#endif
