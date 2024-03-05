/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "w_options_positions.h"
#include "window_positions.h"
#include "window_main.h"

_w_options_positions::_w_options_positions(_window_positions *Window1):QDialog((QWidget*)Window1)
{
  Window=Window1;

  // ui options
//  QWidget *W_general=new QWidget;

//  QGridLayout *Grid_general=new QGridLayout;

//  QLabel *Label_general_font_size=new QLabel("Font size");

//  Spinbox_general_font_size=new QSpinBox;
//  Spinbox_general_font_size->setValue(Window->ui_font_size());

//  Grid_general->addWidget(Label_general_font_size,0,0,Qt::AlignRight);
//  Grid_general->addWidget(Spinbox_general_font_size,0,1,Qt::AlignLeft);

//  W_general->setLayout(Grid_general);

  // Display
  QWidget *W_positions_display=new QWidget;
  QGridLayout *Grid_positions_display=new QGridLayout;

  QLabel *Label_positions_display1=new QLabel("Font size");
  QLabel *Label_positions_display2=new QLabel("Out circle size");
  QLabel *Label_positions_display3=new QLabel("Font color");
  QLabel *Label_positions_display4=new QLabel("Out circle color");
  QLabel *Label_positions_display5=new QLabel("In circle color");
  QLabel *Label_positions_display6=new QLabel("Selection out circle color");
  QLabel *Label_positions_display7=new QLabel("Selection In circle color");

  Spinbox_positions_font_size_display=new QSpinBox;
  Spinbox_positions_font_size_display->setValue(Window->Window_main->display_font_size());

  Spinbox_positions_out_circle_size_display=new QSpinBox;
  Spinbox_positions_out_circle_size_display->setValue(Window->Window_main->display_out_circle_size());

  Button_positions_font_color_display=new _button_color_simple(Window->Window_main->display_font_color(),false);
  Button_positions_out_circle_color_display=new _button_color_simple(Window->Window_main->display_out_circle_color(),false);
  Button_positions_in_circle_color_display=new _button_color_simple(Window->Window_main->display_in_circle_color(),false);
  Button_positions_selection_out_circle_color_display=new _button_color_simple(Window->Window_main->display_selection_out_circle_color(),false);
  Button_positions_selection_in_circle_color_display=new _button_color_simple(Window->Window_main->display_selection_in_circle_color(),false);

  Grid_positions_display->addWidget(Label_positions_display1,0,0,Qt::AlignRight);
  Grid_positions_display->addWidget(Spinbox_positions_font_size_display,0,1,Qt::AlignLeft);
  Grid_positions_display->addWidget(Label_positions_display2,1,0,Qt::AlignRight);
  Grid_positions_display->addWidget(Spinbox_positions_out_circle_size_display,1,1,Qt::AlignLeft);
  Grid_positions_display->addWidget(Label_positions_display3,2,0,Qt::AlignRight);
  Grid_positions_display->addWidget(Button_positions_font_color_display,2,1,Qt::AlignLeft);
  Grid_positions_display->addWidget(Label_positions_display4,3,0,Qt::AlignRight);
  Grid_positions_display->addWidget(Button_positions_out_circle_color_display,3,1,Qt::AlignLeft);
  Grid_positions_display->addWidget(Label_positions_display5,4,0,Qt::AlignRight);
  Grid_positions_display->addWidget(Button_positions_in_circle_color_display,4,1,Qt::AlignLeft);

  Grid_positions_display->addWidget(Label_positions_display6,5,0,Qt::AlignRight);
  Grid_positions_display->addWidget(Button_positions_selection_out_circle_color_display,5,1,Qt::AlignLeft);
  Grid_positions_display->addWidget(Label_positions_display7,6,0,Qt::AlignRight);
  Grid_positions_display->addWidget(Button_positions_selection_in_circle_color_display,6,1,Qt::AlignLeft);

  W_positions_display->setLayout(Grid_positions_display);

  // type of interpolation
  QFrame *Frame_copy_to_print=new QFrame;
  Frame_copy_to_print->setFrameStyle(QFrame::Panel);

  QLabel *Label_copy_to_print=new QLabel("Copy values for printing");

  Checkbox_copy_to_print=new QCheckBox;
  if (Window->copy_display_values()) Checkbox_copy_to_print->setChecked(true);
  else Checkbox_copy_to_print->setChecked(false);
  connect(Checkbox_copy_to_print,SIGNAL(stateChanged(int)),this,SLOT(copy_to_print_slot(int)));

  QGridLayout *Grid_copy_to_print=new QGridLayout;
  Grid_copy_to_print->addWidget(Label_copy_to_print,0,0,Qt::AlignRight);
  Grid_copy_to_print->addWidget(Checkbox_copy_to_print,0,1,Qt::AlignLeft);

  Frame_copy_to_print->setLayout(Grid_copy_to_print);

  QWidget *Widged_d=new QWidget;
  QVBoxLayout *Vboxlayout_d=new QVBoxLayout;

  Vboxlayout_d->addWidget(W_positions_display);
  Vboxlayout_d->addWidget(Frame_copy_to_print);

  Widged_d->setLayout(Vboxlayout_d);

  // Print
  QWidget *Widged_p=new QWidget;
  QGridLayout *Grid_positions_print=new QGridLayout;

  QLabel *Label_positions_print1=new QLabel("Font size");
  QLabel *Label_positions_print2=new QLabel("Out circle size");
  QLabel *Label_positions_print3=new QLabel("Font color");
  QLabel *Label_positions_print4=new QLabel("Out circle color");
  QLabel *Label_positions_print5=new QLabel("In circle color");

  Spinbox_positions_font_size_print=new QSpinBox;
  Spinbox_positions_font_size_print->setValue(Window->Window_main->print_font_size());

  Spinbox_positions_out_circle_size_print=new QSpinBox;
  Spinbox_positions_out_circle_size_print->setValue(Window->Window_main->print_out_circle_size());

  Button_positions_font_color_print=new _button_color_simple(Window->Window_main->print_font_color(),false);
  Button_positions_out_circle_color_print=new _button_color_simple(Window->Window_main->print_out_circle_color(),false);
  Button_positions_in_circle_color_print=new _button_color_simple(Window->Window_main->print_in_circle_color(),false);

  Grid_positions_print->addWidget(Label_positions_print1,0,0,Qt::AlignRight);
  Grid_positions_print->addWidget(Spinbox_positions_font_size_print,0,1,Qt::AlignLeft);
  Grid_positions_print->addWidget(Label_positions_print2,1,0,Qt::AlignRight);
  Grid_positions_print->addWidget(Spinbox_positions_out_circle_size_print,1,1,Qt::AlignLeft);
  Grid_positions_print->addWidget(Label_positions_print3,2,0,Qt::AlignRight);
  Grid_positions_print->addWidget(Button_positions_font_color_print,2,1,Qt::AlignLeft);
  Grid_positions_print->addWidget(Label_positions_print4,3,0,Qt::AlignRight);
  Grid_positions_print->addWidget(Button_positions_out_circle_color_print,3,1,Qt::AlignLeft);
  Grid_positions_print->addWidget(Label_positions_print5,4,0,Qt::AlignRight);
  Grid_positions_print->addWidget(Button_positions_in_circle_color_print,4,1,Qt::AlignLeft);

  Widged_p->setLayout(Grid_positions_print);

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
//  Tab->addTab(W_general,"General");
  Tab->addTab(Widged_d,"Display");
  Tab->addTab(Widged_p,"Print");

  if (Window->copy_display_values()) Tab->setTabEnabled(1,false);

  // main
  QVBoxLayout *Vertical_layout=new QVBoxLayout;

  Vertical_layout->addWidget(Tab);
  Vertical_layout->addWidget(Widget_b);

  setLayout(Vertical_layout);

  setWindowTitle("Options");
}

/*************************************************************************/

void _w_options_positions::apply_slot()
{
  if (Tab->currentIndex()==0){
//    Window->ui_font_size(Spinbox_general_font_size->value());

    Window->options_parameters_display(Spinbox_positions_font_size_display->value(), Spinbox_positions_out_circle_size_display->value(), Button_positions_font_color_display->color(), Button_positions_out_circle_color_display->color(), Button_positions_in_circle_color_display->color(),Button_positions_selection_out_circle_color_display->color(), Button_positions_selection_in_circle_color_display->color(),Checkbox_copy_to_print->checkState());

    if (Checkbox_copy_to_print->checkState()==Qt::Checked){
      Spinbox_positions_font_size_print->blockSignals(true);
      Spinbox_positions_font_size_print->setValue(Spinbox_positions_font_size_display->value());
      Spinbox_positions_font_size_print->blockSignals(false);

      Spinbox_positions_out_circle_size_print->blockSignals(true);
      Spinbox_positions_out_circle_size_print->setValue(Window->Window_main->print_out_circle_size());
      Spinbox_positions_out_circle_size_print->blockSignals(false);

      Button_positions_font_color_print->color(Button_positions_font_color_display->color());
      Button_positions_out_circle_color_print->color(Button_positions_out_circle_color_display->color());
      Button_positions_in_circle_color_print->color(Button_positions_in_circle_color_display->color());
    }
  }
  else{
    Window->options_parameters_print(Spinbox_positions_font_size_print->value(), Spinbox_positions_out_circle_size_print->value(), Button_positions_font_color_print->color(), Button_positions_out_circle_color_print->color(), Button_positions_in_circle_color_print->color());
  }
}

/*************************************************************************/

void _w_options_positions::close_slot()
{
//  Window->ui_font_size(Spinbox_general_font_size->value());

  Window->options_parameters_display(Spinbox_positions_font_size_display->value(), Spinbox_positions_out_circle_size_display->value(), Button_positions_font_color_display->color(), Button_positions_out_circle_color_display->color(), Button_positions_in_circle_color_display->color(),Button_positions_selection_out_circle_color_display->color(), Button_positions_selection_in_circle_color_display->color(),Checkbox_copy_to_print->checkState());

  if (Checkbox_copy_to_print->checkState()==Qt::Checked){
    Window->options_parameters_print(Spinbox_positions_font_size_display->value(), Spinbox_positions_out_circle_size_display->value(), Button_positions_font_color_display->color(), Button_positions_out_circle_color_display->color(), Button_positions_in_circle_color_display->color());
  }
  else{
    Window->options_parameters_print(Spinbox_positions_font_size_print->value(), Spinbox_positions_out_circle_size_print->value(), Button_positions_font_color_print->color(), Button_positions_out_circle_color_print->color(), Button_positions_in_circle_color_print->color());
  }

  close();
}

/*************************************************************************/

void _w_options_positions::copy_to_print_slot(int Value)
{
  if (Value==Qt::Unchecked) Tab->setTabEnabled(1,true);
  else Tab->setTabEnabled(1,false);
}

