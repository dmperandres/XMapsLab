/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef DIALOG_CREATE_PALETTE_H
#define DIALOG_CREATE_PALETTE_H

#include <QDialog>
#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QIntValidator>
#include <iostream>

class _palette_data;

class _w_tab_xmapslab;

class _dialog_create_palette: public QDialog
{
Q_OBJECT

public:
  _dialog_create_palette(_palette_data *Data1,_w_tab_xmapslab *W_tab1);

public slots:
  void accept_slot();

protected:
  QRadioButton *Radiobutton_type1=nullptr;
  QRadioButton *Radiobutton_color_type1=nullptr;
  QSpinBox *Spinbox_num_steps=nullptr;
  QLineEdit *Lineedit_palette_name1=nullptr;
  _w_tab_xmapslab *W_tab=nullptr;
  _palette_data *Vec_palette_data=nullptr;
};
#endif
