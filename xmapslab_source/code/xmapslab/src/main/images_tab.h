/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#ifndef IMAGES_TAB_H
#define IMAGES_TAB_H

#include <QDialog>
#include <QListWidget>
#include <QGroupBox>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QComboBox>
#include <QFrame>
#include <string>

#include "line_edit.h"

class _window;

/*************************************************************************/
// class for the tab that includes the images in the XRF and XRD widgets

class _images_tab: public QWidget
{
  Q_OBJECT

public:
        _images_tab(_window *Window1, QWidget *Parent = nullptr);
  void  set_item(std::string Name);
  void  set_selected_item(int Pos);
  void  clear(){Images_list->clear();}

  QString selected_item();

  void insert_images();
  void remove_images();

protected slots:
  void item_clicked(QListWidgetItem *);
  void create_single_element_slot();

private:
  QListWidget *Images_list=nullptr;

  QPushButton *Button_create_element=nullptr;
  QComboBox *Combobox_palette=nullptr;
  _window *Window=nullptr;
};

#endif
