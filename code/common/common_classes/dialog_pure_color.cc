//LIC

#include "dialog_pure_color.h"

//HEA

_dialog_pure_color::_dialog_pure_color(QWidget *Parent, QColor *Color1, bool Solid_black1):QDialog(Parent)
{
  Color=Color1;

  Pure_color_bar=new _pure_color_bar(Color,Solid_black1);
  //
  QHBoxLayout *Horizontal1=new QHBoxLayout;

  Horizontal1->addWidget(Pure_color_bar);

  QWidget *Widged_p=new QWidget;

  Widged_p->setLayout(Horizontal1);

  // control buttons
  QPushButton *Button_ok = new QPushButton(tr("OK"));
  QPushButton *Button_cancel = new QPushButton(tr("Cancel"));

//  connect(Button_ok,SIGNAL(clicked(bool)),this,SLOT(accept_slot()));
  connect(Button_ok,SIGNAL(clicked(bool)),this,SLOT(accept()));
  connect(Button_cancel,SIGNAL(clicked(bool)),this,SLOT(reject()));

  QWidget *Widget_b=new QWidget;
  QHBoxLayout *Horizontal_layout=new QHBoxLayout;

  Horizontal_layout->addStretch();
  Horizontal_layout->addWidget(Button_ok);
  Horizontal_layout->addWidget(Button_cancel);

  Widget_b->setLayout(Horizontal_layout);

//  // main
  QVBoxLayout *Vertical_layout=new QVBoxLayout;

  Vertical_layout->addWidget(Widged_p);
  Vertical_layout->addWidget(Widget_b);

  setLayout(Vertical_layout);

  setWindowTitle("Select color");
}
