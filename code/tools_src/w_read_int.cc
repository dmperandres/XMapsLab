/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "w_read_int.h"
#include "window_tools.h"

_w_read_int::_w_read_int(_window_tools *Window1, int *Number1):QDialog((QWidget*)Window1)
{
  Window=Window1;
  Number=Number1;

  // ui options
  QWidget *W_general=new QWidget;

  QGridLayout *Grid_general=new QGridLayout;

  QLabel *Label_int_number=new QLabel("Introduce number");

  Spinbox_int_number=new QSpinBox;
  Spinbox_int_number->setValue(1);

  Grid_general->addWidget(Label_int_number,0,0,Qt::AlignRight);
  Grid_general->addWidget(Spinbox_int_number,0,1,Qt::AlignLeft);

  W_general->setLayout(Grid_general);

  // control buttons
  QPushButton *Button_apply = new QPushButton(tr("OK"));
  connect(Button_apply,SIGNAL(clicked(bool)),this,SLOT(ok_slot()));

  QPushButton *Button_ok = new QPushButton(tr("Cancel"));
  connect(Button_ok,SIGNAL(clicked(bool)),this,SLOT(reject()));

  QWidget *Widget_b=new QWidget;
  QHBoxLayout *Horizontal_layout=new QHBoxLayout;

  Horizontal_layout->addStretch();
  Horizontal_layout->addWidget(Button_apply);
  Horizontal_layout->addWidget(Button_ok);

  Widget_b->setLayout(Horizontal_layout);

//  Tab=new QTabWidget(this);
//  Tab->addTab(W_general,"General");

  // main
  QVBoxLayout *Vertical_layout=new QVBoxLayout;

  Vertical_layout->addWidget(W_general);
  Vertical_layout->addWidget(Widget_b);

  setLayout(Vertical_layout);

  setWindowTitle("Insert integer number");
}

/*************************************************************************/

void _w_read_int::ok_slot()
{
  *Number=Spinbox_int_number->value();
  accept();
}

/*************************************************************************/

//void _w_read_int::close_slot()
//{
//  Window->ui_font_size(Spinbox_general_font_size->value());

//  close();
//}

