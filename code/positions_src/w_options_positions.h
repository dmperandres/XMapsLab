/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef _W_OPTIONS_POSITIONS_H
#define _W_OPTIONS_POSITIONS_H

#include <QRadioButton>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QIntValidator>
#include <iostream>

#include "button_color_simple.h"

#include "glwidget_positions.h"

class _window_positions;

/*************************************************************************/

class _w_options_positions: public QDialog
{
Q_OBJECT

public:
  _w_options_positions(_window_positions *Window1);

public slots:
  void apply_slot();
  void close_slot();
  void copy_to_print_slot(int);

protected:
  QSpinBox * Spinbox_general_font_size=nullptr;
  // display
  QRadioButton *Radiobutton_type_input_display=nullptr;
  QSpinBox *Spinbox_positions_font_size_display=nullptr;
  QSpinBox *Spinbox_positions_out_circle_size_display=nullptr;
  _button_color_simple *Button_positions_font_color_display=nullptr;
  _button_color_simple *Button_positions_out_circle_color_display=nullptr;
  _button_color_simple *Button_positions_in_circle_color_display=nullptr;
  _button_color_simple *Button_positions_selection_out_circle_color_display=nullptr;
  _button_color_simple *Button_positions_selection_in_circle_color_display=nullptr;
  QCheckBox *Checkbox_copy_to_print=nullptr;

  // print
  QRadioButton *Radiobutton_type_input_print=nullptr;
  QSpinBox *Spinbox_positions_font_size_print=nullptr;
  QSpinBox *Spinbox_positions_out_circle_size_print=nullptr;
  _button_color_simple *Button_positions_font_color_print=nullptr;
  _button_color_simple *Button_positions_out_circle_color_print=nullptr;
  _button_color_simple *Button_positions_in_circle_color_print=nullptr;

  QTabWidget *Tab=nullptr;

  _window_positions *Window=nullptr;
};

#endif
