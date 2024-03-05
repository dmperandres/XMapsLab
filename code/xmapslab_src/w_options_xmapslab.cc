/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "w_options_xmapslab.h"
#include "window_xmapslab.h"
#include "window_main.h"

_w_options_xmapslab::_w_options_xmapslab(_window_xmapslab *Window1):QDialog((QWidget*)Window1)
{
  Window=Window1;

  QTabWidget *Tab=new QTabWidget;

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
  QWidget *W_display=new QWidget;
  QGridLayout *Grid_display=new QGridLayout;

  QLabel *Label_display1=new QLabel("Font size");
  QLabel *Label_display2=new QLabel("Out circle size");
  QLabel *Label_display3=new QLabel("Font color");
  QLabel *Label_display4=new QLabel("Out circle color");
  QLabel *Label_display5=new QLabel("In circle color");
  // QLabel *Label_display6=new QLabel("Selection out circle color");
  // QLabel *Label_display7=new QLabel("Selection In circle color");

  Spinbox_display_font_size=new QSpinBox;
  Spinbox_display_font_size->setValue(Window->Window_main->display_font_size());

  Spinbox_display_out_circle_size=new QSpinBox;
  Spinbox_display_out_circle_size->setValue(Window->Window_main->display_out_circle_size());

  Button_display_font_color=new _button_color_simple(Window->Window_main->display_font_color(),false);
  Button_display_out_circle_color=new _button_color_simple(Window->Window_main->display_out_circle_color(),false);
  Button_display_in_circle_color=new _button_color_simple(Window->Window_main->display_in_circle_color(),false);
  Button_display_selection_out_circle_color=new _button_color_simple(Window->Window_main->display_selection_out_circle_color(),false);
  Button_display_selection_in_circle_color=new _button_color_simple(Window->Window_main->display_selection_in_circle_color(),false);

  Grid_display->addWidget(Label_display1,0,0,Qt::AlignRight);
  Grid_display->addWidget(Spinbox_display_font_size,0,1,Qt::AlignLeft);
  Grid_display->addWidget(Label_display2,1,0,Qt::AlignRight);
  Grid_display->addWidget(Spinbox_display_out_circle_size,1,1,Qt::AlignLeft);
  Grid_display->addWidget(Label_display3,2,0,Qt::AlignRight);
  Grid_display->addWidget(Button_display_font_color,2,1,Qt::AlignLeft);
  Grid_display->addWidget(Label_display4,3,0,Qt::AlignRight);
  Grid_display->addWidget(Button_display_out_circle_color,3,1,Qt::AlignLeft);
  Grid_display->addWidget(Label_display5,4,0,Qt::AlignRight);
  Grid_display->addWidget(Button_display_in_circle_color,4,1,Qt::AlignLeft);

  W_display->setLayout(Grid_display);

  QWidget *W_print=new QWidget;

  QGridLayout *Grid_print=new QGridLayout;

  QLabel *Label_print_font_factor=new QLabel("Font factor");

  Spinbox_print_font_factor=new QDoubleSpinBox;
  Spinbox_print_font_factor->setLocale(QLocale::C);
  Spinbox_print_font_factor->setRange(0.1,8);
  Spinbox_print_font_factor->setSingleStep(0.1);
  Spinbox_print_font_factor->setDecimals(2);
  Spinbox_print_font_factor->setValue(Window->print_font_factor());

  Grid_print->addWidget(Label_print_font_factor,0,0,Qt::AlignRight);
  Grid_print->addWidget(Spinbox_print_font_factor,0,1,Qt::AlignLeft);

  W_print->setLayout(Grid_print);

  // Vec_layers
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
  //  Tab->addTab(W_general,"General");
  Tab->addTab(W_display,"Display");
  Tab->addTab(W_print,"Print");
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

void _w_options_xmapslab::apply_slot()
{
  //  Window->ui_font_size(Spinbox_general_font_size->value());
  Window->Window_main->display_font_size(Spinbox_display_font_size->value());
  Window->Window_main->display_out_circle_size(Spinbox_display_out_circle_size->value());
  Window->Window_main->display_font_color(Button_display_font_color->color());
  Window->Window_main->display_out_circle_color(Button_display_out_circle_color->color());
  Window->Window_main->display_in_circle_color(Button_display_in_circle_color->color());

  Window->print_font_factor(float(Spinbox_print_font_factor->value()));
  Window->data_type_print(static_cast<_palette_data_ns::_data_type_print>(Combobox_data_type_print->currentIndex()));
  Window->color_for_zero_value(static_cast<_color_map_ns::_color_for_zero_value>(Combobox_color_for_zero_value->currentIndex()));
  Window->parameters_changed();

  Window->Window_main->save_settings();
}

/*************************************************************************/

void _w_options_xmapslab::close_slot()
{
  apply_slot();
  close();
}

