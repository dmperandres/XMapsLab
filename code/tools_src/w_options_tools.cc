/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "w_options_tools.h"
#include "window_tools.h"

_w_options_tools::_w_options_tools(_window_tools *Window1):QDialog((QWidget*)Window1)
{
  Window=Window1;

  // ui options
  QWidget *W_general=new QWidget;

  QGridLayout *Grid_general=new QGridLayout;

  QLabel *Label_general_font_size=new QLabel("Font size");

  Spinbox_general_font_size=new QSpinBox;
  Spinbox_general_font_size->setValue(Window->ui_font_size());

  Grid_general->addWidget(Label_general_font_size,0,0,Qt::AlignRight);
  Grid_general->addWidget(Spinbox_general_font_size,0,1,Qt::AlignLeft);

  W_general->setLayout(Grid_general);

  // control buttons
  QPushButton *Button_apply = new QPushButton(tr("Apply"));
  connect(Button_apply,SIGNAL(clicked(bool)),this,SLOT(apply_slot()));

  QPushButton *Button_ok = new QPushButton(tr("Close window"));
  connect(Button_ok,SIGNAL(clicked(bool)),this,SLOT(accept()));

  QWidget *Widget_b=new QWidget;
  QHBoxLayout *Horizontal_layout=new QHBoxLayout;

  Horizontal_layout->addStretch();
  Horizontal_layout->addWidget(Button_apply);
  Horizontal_layout->addWidget(Button_ok);

  Widget_b->setLayout(Horizontal_layout);

  Tab=new QTabWidget(this);
  Tab->addTab(W_general,"General");

  // main
  QVBoxLayout *Vertical_layout=new QVBoxLayout;

  Vertical_layout->addWidget(Tab);
  Vertical_layout->addWidget(Widget_b);

  setLayout(Vertical_layout);

  setWindowTitle("Options");
}

/*************************************************************************/

void _w_options_tools::apply_slot()
{
  Window->pass_ui_font_size(Spinbox_general_font_size->value());
}

/*************************************************************************/

void _w_options_tools::close_slot()
{
  Window->ui_font_size(Spinbox_general_font_size->value());

  close();
}

