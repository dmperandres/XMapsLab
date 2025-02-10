//LIC

#include "w_number.h"
#include "window_positions.h"


_w_number::_w_number(int Position, _window_positions *Window1):QDialog((QWidget*)Window1)
{
  Window=Window1;

  QWidget *Widged_d=new QWidget;
  QGridLayout *Grid_positions_display=new QGridLayout;

  QLabel *Label_positions_display1=new QLabel("Position");

  Spinbox_number=new QSpinBox;
  Spinbox_number->setValue(Position);

  Grid_positions_display->addWidget(Label_positions_display1,0,0,Qt::AlignRight);
  Grid_positions_display->addWidget(Spinbox_number,0,1,Qt::AlignLeft);

  Widged_d->setLayout(Grid_positions_display);


  // control buttons
//  QPushButton *Button_apply = new QPushButton(tr("Apply"));
//  connect(Button_apply,SIGNAL(clicked(bool)),this,SLOT(apply_slot()));

  // separator
  QFrame *Separator=new QFrame();
  Separator->setFrameStyle(QFrame::HLine);

  QPushButton *Button_ok = new QPushButton(tr("OK"));
  connect(Button_ok,SIGNAL(clicked(bool)),this,SLOT(accept()));

  QWidget *Widget_b=new QWidget;
  QVBoxLayout *Vertical_layout_w_b=new QVBoxLayout;

  Vertical_layout_w_b->addStretch();
  Vertical_layout_w_b->addWidget(Separator);
//  Horizontal_layout->addWidget(Button_apply);
  Vertical_layout_w_b->addWidget(Button_ok);

  Widget_b->setLayout(Vertical_layout_w_b);

//  Tab=new QTabWidget(this);
//  Tab->addTab(Widged_d,"Display");
//  Tab->addTab(Widged_p,"Print");

  // main
  QVBoxLayout *Vertical_layout=new QVBoxLayout;

  Vertical_layout->addWidget(Widged_d);
  Vertical_layout->addWidget(Widget_b);

  setLayout(Vertical_layout);

  setWindowTitle("Position");
}


//HEA

//void _w_number::apply_slot()
//{
//  Window->add_position_number(Spinbox_number->value());
//}

//HEA

//void _w_number::close_slot()
//{
//  Window->add_position_number(Spinbox_number->value());
//  close();
//}


