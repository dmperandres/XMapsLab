/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#include "w_options.h"
#include "window.h"

_w_options::_w_options(_window *Window1):QDialog((QWidget*)Window1)
{
  Window=Window1;

  QTabWidget *Tab=new QTabWidget;

  // ui options
  QWidget *W_general=new QWidget;

  QGridLayout *Grid_general=new QGridLayout;

  QLabel *Label_general_font_size=new QLabel("Font size");

  Spinbox_general_font_size=new QSpinBox;
  Spinbox_general_font_size->setValue(Window->ui_font_size());

  Grid_general->addWidget(Label_general_font_size,0,0,Qt::AlignRight);
  Grid_general->addWidget(Spinbox_general_font_size,0,1,Qt::AlignLeft);

  W_general->setLayout(Grid_general);

  // Positions display
  QWidget *W_positions_display=new QWidget;

  QGridLayout *Grid_positions_display=new QGridLayout;

  QLabel *Label_positions_display_font_size=new QLabel("Font size");
  QLabel *Label_positions_display_out_circle_size=new QLabel("Out circle size");
  QLabel *Label_positions_display_font_color=new QLabel("Font color");
  QLabel *Label_positions_display_out_circle_color=new QLabel("Out circle color");
  QLabel *Label_positions_display_in_circle_color=new QLabel("In circle color");

  Spinbox_positions_display_font_size=new QSpinBox;
  Spinbox_positions_display_font_size->setValue(Window->positions_display_font_size());

  Spinbox_positions_display_out_circle_size=new QSpinBox;
  Spinbox_positions_display_out_circle_size->setValue(Window->positions_display_out_circle_size());

  Button_positions_display_font_color=new _button_color_simple(Window->positions_display_font_color(),false);
  Button_positions_display_out_circle_color=new _button_color_simple(Window->positions_display_out_circle_color(),false);
  Button_positions_display_in_circle_color=new _button_color_simple(Window->positions_display_in_circle_color(),false);

  Grid_positions_display->addWidget(Label_positions_display_font_size,0,0,Qt::AlignRight);
  Grid_positions_display->addWidget(Spinbox_positions_display_font_size,0,1,Qt::AlignLeft);
  Grid_positions_display->addWidget(Label_positions_display_out_circle_size,1,0,Qt::AlignRight);
  Grid_positions_display->addWidget(Spinbox_positions_display_out_circle_size,1,1,Qt::AlignLeft);
  Grid_positions_display->addWidget(Label_positions_display_font_color,2,0,Qt::AlignRight);
  Grid_positions_display->addWidget(Button_positions_display_font_color,2,1,Qt::AlignLeft);
  Grid_positions_display->addWidget(Label_positions_display_out_circle_color,3,0,Qt::AlignRight);
  Grid_positions_display->addWidget(Button_positions_display_out_circle_color,3,1,Qt::AlignLeft);
  Grid_positions_display->addWidget(Label_positions_display_in_circle_color,4,0,Qt::AlignRight);
  Grid_positions_display->addWidget(Button_positions_display_in_circle_color,4,1,Qt::AlignLeft);

  W_positions_display->setLayout(Grid_positions_display);

  // Positions print
  QWidget *W_positions_print=new QWidget;

  QGridLayout *Grid_positions_print=new QGridLayout;

  QLabel *Label_positions_print_font_factor=new QLabel("Font factor");

  Spinbox_positions_print_font_factor=new QDoubleSpinBox;
  Spinbox_positions_print_font_factor->setLocale(QLocale::C);
  Spinbox_positions_print_font_factor->setRange(0.1,8);
  Spinbox_positions_print_font_factor->setSingleStep(0.1);
  Spinbox_positions_print_font_factor->setDecimals(2);
  Spinbox_positions_print_font_factor->setValue(Window->positions_print_font_factor());

  Grid_positions_print->addWidget(Label_positions_print_font_factor,0,0,Qt::AlignRight);
  Grid_positions_print->addWidget(Spinbox_positions_print_font_factor,0,1,Qt::AlignLeft);

  W_positions_print->setLayout(Grid_positions_print);

  // Layers
  QWidget *W_layers=new QWidget;
  QGridLayout *Grid_layers=new QGridLayout;

  QLabel *Label_layers1=new QLabel("Data type");

  Combobox_data_type_print=new QComboBox;
  for (unsigned int i=0; i<_palette_data_ns::Vec_names_data_type_print.size();i++){
    Combobox_data_type_print->addItem(_palette_data_ns::Vec_names_data_type_print[i]);
  }
  Combobox_data_type_print->setCurrentIndex(int(Window->data_type_print()));

  Grid_layers->addWidget(Label_layers1,0,0,Qt::AlignRight);
  Grid_layers->addWidget(Combobox_data_type_print,0,1,Qt::AlignLeft);

  W_layers->setLayout(Grid_layers);

  // Palettes
  QWidget *W_palettes=new QWidget;
  QGridLayout *Grid_palettes=new QGridLayout;

  QLabel *Label_palettes1=new QLabel("0 value color");

  Combobox_color_for_zero_value=new QComboBox;
  for (unsigned int i=0; i<_color_map_ns::Vec_color_names_for_zero_value.size();i++){
    Combobox_color_for_zero_value->addItem(_color_map_ns::Vec_color_names_for_zero_value[i]);
  }
  Combobox_color_for_zero_value->setCurrentIndex(int(Window->color_for_zero_value()));

  Grid_palettes->addWidget(Label_palettes1,0,0,Qt::AlignRight);
  Grid_palettes->addWidget(Combobox_color_for_zero_value,0,1,Qt::AlignLeft);

  W_palettes->setLayout(Grid_palettes);

  // control buttons
  QPushButton *Button_apply = new QPushButton(tr("Apply"));
  connect(Button_apply,SIGNAL(clicked(bool)),this,SLOT(apply_slot()));

  QPushButton *Button_ok = new QPushButton(tr("Close window"));
  connect(Button_ok,SIGNAL(clicked(bool)),this,SLOT(close_slot()));

  QWidget *Widget_b=new QWidget;
  QHBoxLayout *Horizontal_layout=new QHBoxLayout;

  Horizontal_layout->addStretch();
  Horizontal_layout->addWidget(Button_apply);
  Horizontal_layout->addWidget(Button_ok);

  Widget_b->setLayout(Horizontal_layout);

  // Tab
  Tab->addTab(W_general,"General");
  Tab->addTab(W_positions_display,"Pos. display");
  Tab->addTab(W_positions_print,"Pos. print");
  Tab->addTab(W_layers,"Layers");
//  Tab->addTab(W_elements,"Elements");
  Tab->addTab(W_palettes,"Palettes");

  // main
  QVBoxLayout *Vertical_layout=new QVBoxLayout;

  Vertical_layout->addWidget(Tab);
  Vertical_layout->addWidget(Widget_b);

  setLayout(Vertical_layout);

  setWindowTitle("Options");

  setMinimumWidth(500);
}

/*************************************************************************/

void _w_options::apply_slot()
{
  Window->ui_set_font_size(Spinbox_general_font_size->value());
  Window->positions_display_font_size(Spinbox_positions_display_font_size->value());
  Window->positions_display_out_circle_size(Spinbox_positions_display_out_circle_size->value());
  Window->positions_display_font_color(Button_positions_display_font_color->color());
  Window->positions_display_out_circle_color(Button_positions_display_out_circle_color->color());
  Window->positions_display_in_circle_color(Button_positions_display_in_circle_color->color());

  Window->positions_print_font_factor(float(Spinbox_positions_print_font_factor->value()));
  Window->data_type_print(static_cast<_palette_data_ns::_data_type_print>(Combobox_data_type_print->currentIndex()));
  Window->color_for_zero_value(static_cast<_color_map_ns::_color_for_zero_value>(Combobox_color_for_zero_value->currentIndex()));
  Window->parameters_changed();
}

/*************************************************************************/

void _w_options::close_slot()
{
  apply_slot();
  close();
}

