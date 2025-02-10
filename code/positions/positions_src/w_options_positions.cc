//LIC

#include "w_options_positions.h"
#include "window_positions.h"


_w_options_positions::_w_options_positions(_window_positions *Window1):QDialog((QWidget*)Window1)
{
  Window=Window1;

  QTabWidget *Tab=new QTabWidget;

  // Display
  QWidget *W_display=new QWidget;
  QGridLayout *Grid_display=new QGridLayout;

  QLabel *Label_display1=new QLabel("Font size");
  QLabel *Label_display2=new QLabel("Out circle size");
  QLabel *Label_display3=new QLabel("Font color");
  QLabel *Label_display4=new QLabel("Out circle color");
  QLabel *Label_display5=new QLabel("In circle color");
  QLabel *Label_display6=new QLabel("Selection out circle color");
  QLabel *Label_display7=new QLabel("Selection In circle color");

  Spinbox_display_font_size=new QSpinBox;
  Spinbox_display_font_size->setValue(Window->display_font_size());

  Spinbox_display_out_circle_size=new QSpinBox;
  Spinbox_display_out_circle_size->setValue(Window->display_out_circle_size());

  Button_display_font_color=new _button_color_simple(Window->display_font_color(),false);
  Button_display_out_circle_color=new _button_color_simple(Window->display_out_circle_color(),false);
  Button_display_in_circle_color=new _button_color_simple(Window->display_in_circle_color(),false);

  Button_display_selection_out_circle_color=new _button_color_simple(Window->display_selection_out_circle_color(),false);
  Button_display_selection_in_circle_color=new _button_color_simple(Window->display_selection_in_circle_color(),false);

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

  Grid_display->addWidget(Label_display6,5,0,Qt::AlignRight);
  Grid_display->addWidget(Button_display_selection_out_circle_color,5,1,Qt::AlignLeft);
  Grid_display->addWidget(Label_display7,6,0,Qt::AlignRight);
  Grid_display->addWidget(Button_display_selection_in_circle_color,6,1,Qt::AlignLeft);

  W_display->setLayout(Grid_display);

  //
  // Font factor
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

  //
  Tab->addTab(W_display,"Display");
  Tab->addTab(W_print,"Print");

  // main
  QVBoxLayout *Vertical_layout=new QVBoxLayout;

  Vertical_layout->addWidget(Tab);
  Vertical_layout->addWidget(Widget_b);

  setLayout(Vertical_layout);

  setWindowTitle("Options");
}


//HEA

void _w_options_positions::apply_slot()
{
  //  Window->ui_font_size(Spinbox_general_font_size->value());
  Window->display_font_size(Spinbox_display_font_size->value());
  Window->display_out_circle_size(Spinbox_display_out_circle_size->value());
  Window->display_font_color(Button_display_font_color->color());
  Window->display_out_circle_color(Button_display_out_circle_color->color());
  Window->display_in_circle_color(Button_display_in_circle_color->color());

  Window->print_font_factor(float(Spinbox_print_font_factor->value()));

  Window->parameters_changed();

  Window->save_settings();
}

//HEA

void _w_options_positions::close_slot()
{
  apply_slot();
  close();
}

//HEA

// void _w_options_positions::copy_to_print_slot(int Value)
// {
//   if (Value==Qt::Unchecked) Tab->setTabEnabled(1,true);
//   else Tab->setTabEnabled(1,false);
// }

