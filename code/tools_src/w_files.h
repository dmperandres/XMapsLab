/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef _W_FILES_H
#define _W_FILES_H

#include <QDialog>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QPixmap>
#include <QDialogButtonBox>
#include <QStringList>
#include <QListWidget>
#include <QListWidgetItem>
#include <iostream>

class _window_tools;

/*************************************************************************/

class _w_files: public QDialog
{
Q_OBJECT

public:
  _w_files(_window_tools *Window1,QStringList File_names);

//public slots:
//  void accept_slot();
//  void cancel_slot();

protected:

  _window_tools *Window=nullptr;
};

#endif
