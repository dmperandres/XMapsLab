/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "w_int_file_parameters.h"
#include "window_tools.h"

_w_int_file_parameters::_w_int_file_parameters(_window_tools *Window1):QDialog((QWidget*)Window1)
{
  Window=Window1;

//  setMinimumWidth(600);
  // Display
  QWidget *W_int_file_parameters=new QWidget;
  QGridLayout *Grid_int_file_parameters=new QGridLayout;
//  Grid_int_file_parameters->setColumnStretch(1,1);

  QLabel *Label_int_file_parameters1=new QLabel("Name");
  QLabel *Label_int_file_parameters2=new QLabel("Formula");
  QLabel *Label_int_file_parameters3=new QLabel("XRF");
  QLabel *Label_int_file_parameters4=new QLabel("RGB color");

  Lineedit_name=new QLineEdit("Name1,Name2,...");
  Lineedit_name->setMinimumWidth(400);
  Lineedit_formula=new QLineEdit("Formula1,Formula2,...");;
  Lineedit_formula->setMinimumWidth(400);
  Lineedit_XRF=new QLineEdit("Element1,Element2,...");;
  Lineedit_XRF->setMinimumWidth(400);
  Lineedit_RGB_color=new QLineEdit("255,255,255");
  Lineedit_RGB_color->setMinimumWidth(400);

  Grid_int_file_parameters->addWidget(Label_int_file_parameters1,0,0,Qt::AlignRight);
  Grid_int_file_parameters->addWidget(Lineedit_name,0,1,Qt::AlignLeft);
  Grid_int_file_parameters->addWidget(Label_int_file_parameters2,1,0,Qt::AlignRight);
  Grid_int_file_parameters->addWidget(Lineedit_formula,1,1,Qt::AlignLeft);
  Grid_int_file_parameters->addWidget(Label_int_file_parameters3,2,0,Qt::AlignRight);
  Grid_int_file_parameters->addWidget(Lineedit_XRF,2,1,Qt::AlignLeft);
  Grid_int_file_parameters->addWidget(Label_int_file_parameters4,3,0,Qt::AlignRight);
  Grid_int_file_parameters->addWidget(Lineedit_RGB_color,3,1,Qt::AlignLeft);

  W_int_file_parameters->setLayout(Grid_int_file_parameters);

  // control buttons
//  QPushButton *Button_apply = new QPushButton(tr("Apply"));
//  connect(Button_apply,SIGNAL(clicked(bool)),this,SLOT(apply_slot()));

  QPushButton *Button_ok = new QPushButton(tr("Close window"));
  connect(Button_ok,SIGNAL(clicked(bool)),this,SLOT(accept()));

  QWidget *Widget_b=new QWidget;
  QHBoxLayout *Horizontal_layout=new QHBoxLayout;

  Horizontal_layout->addStretch();
//  Horizontal_layout->addWidget(Button_apply);
  Horizontal_layout->addWidget(Button_ok);

  Widget_b->setLayout(Horizontal_layout);

  // main
  QVBoxLayout *Vertical_layout=new QVBoxLayout;

  Vertical_layout->addWidget(W_int_file_parameters);
  Vertical_layout->addWidget(Widget_b);

  setLayout(Vertical_layout);

  setWindowTitle("Parameters");
}

/*************************************************************************/

void _w_int_file_parameters::close_slot()
{
  Window->int_file_parameters(Lineedit_name->text(),Lineedit_formula->text(),Lineedit_XRF->text(),Lineedit_RGB_color->text());

  close();
}

