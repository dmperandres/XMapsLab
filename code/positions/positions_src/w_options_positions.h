//LIC

#ifndef _W_OPTIONS_POSITIONS_H
#define _W_OPTIONS_POSITIONS_H

#include <QRadioButton>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QIntValidator>
#include <iostream>

#include "button_color_simple.h"

#include "glwidget_positions.h"

namespace _w_options_positions_ns {
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

class _window_positions;

//HEA

class _w_options_positions: public QDialog
{
Q_OBJECT

public:
  _w_options_positions(_window_positions *Window1);

public slots:
  void apply_slot();
  void close_slot();
  // void copy_to_print_slot(int);

protected:
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

  QDoubleSpinBox *Spinbox_print_font_factor=nullptr;

  QTabWidget *Tab=nullptr;

  _window_positions *Window=nullptr;
};

#endif
