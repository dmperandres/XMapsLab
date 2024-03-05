/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef _W_OPTIONS_XMAPSLAB_H
#define _W_OPTIONS_XMAPSLAB_H

#include <QRadioButton>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QIntValidator>
#include <iostream>

#include "button_color_simple.h"
#include "glwidget_xmapslab.h"

namespace _w_options_xmapslab_ns {
  // positions
  const int DISPLAY_FONT_SIZE_DEFAULT=15;
  const int DISPLAY_OUT_CIRCLE_SIZE_DEFAULT=15;
  const QColor DISPLAY_FONT_COLOR_DEFAULT=QColor(Qt::blue);
  const QColor DISPLAY_OUT_CIRCLE_COLOR_DEFAULT=QColor(Qt::blue);
  const QColor DISPLAY_IN_CIRCLE_COLOR_DEFAULT=QColor(Qt::yellow);
  const QColor DISPLAY_SELECTION_OUT_CIRCLE_COLOR_DEFAULT=QColor(Qt::magenta);
  const QColor DISPLAY_SELECTION_IN_CIRCLE_COLOR_DEFAULT=QColor(Qt::yellow);

  const float PRINT_FONT_FACTOR_DEFAULT=1.0f;
}

class _window_xmapslab;

/*************************************************************************/

class _w_options_xmapslab: public QDialog
{
Q_OBJECT

public:
  _w_options_xmapslab(_window_xmapslab *Window1);

public slots:
  void apply_slot();
  void close_slot();

protected:
//  QRadioButton *Radiobutton_type_input1=nullptr;
  QSpinBox * Spinbox_general_font_size=nullptr;

  // display
  QRadioButton *Radiobutton_display_type_input=nullptr;
  QSpinBox *Spinbox_display_font_size=nullptr;
  QSpinBox *Spinbox_display_out_circle_size=nullptr;
  _button_color_simple *Button_display_font_color=nullptr;
  _button_color_simple *Button_display_out_circle_color=nullptr;
  _button_color_simple *Button_display_in_circle_color=nullptr;
  _button_color_simple *Button_display_selection_out_circle_color=nullptr;
  _button_color_simple *Button_display_selection_in_circle_color=nullptr;
  // QCheckBox *Checkbox_copy_to_print=nullptr;

  QDoubleSpinBox *Spinbox_print_font_factor=nullptr;

  QComboBox *Combobox_data_type_print=nullptr;

  QComboBox *Combobox_elements_interpolation_type=nullptr;
  QComboBox *Combobox_elements_color_model=nullptr;
  QCheckBox *Checkbox_elements_color1=nullptr;
  QCheckBox *Checkbox_elements_color2=nullptr;
  QCheckBox *Checkbox_elements_color3=nullptr;
  QCheckBox *Checkbox_elements_position1=nullptr;
  QCheckBox *Checkbox_elements_position2=nullptr;
  QCheckBox *Checkbox_elements_normalization=nullptr;
  QComboBox *Combobox_elements_position_interpolation_type=nullptr;
  QComboBox *Combobox_elements_probe=nullptr;
  QComboBox *Combobox_elements_palette=nullptr;
  QCheckBox *Checkbox_elements_triangulation_add_corners=nullptr;

  QComboBox *Combobox_color_for_zero_value=nullptr;

  _window_xmapslab *Window=nullptr;
};

#endif
