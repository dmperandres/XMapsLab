//LIC

#include "w_options_image_section.h"
#include "window_xmapslab.h"


_w_options_image_section::_w_options_image_section(_window_xmapslab *Window1, bool *Add_original_image1, bool *Add_colorbar1):QDialog((QWidget*)Window1)
{
  Window=Window1;
  Add_original_image=Add_original_image1;
  Add_colorbar=Add_colorbar1;

//  setMinimumWidth(600);
  // Display
  QWidget *W_options_image_section=new QWidget;
  QGridLayout *Grid_options_image_section=new QGridLayout;
//  Grid_options_image_section->setColumnStretch(1,1);

  QLabel *Label_add_original_image=new QLabel("Add original image");
  QLabel *Label_add_colorbar=new QLabel("Add color bar");
//  QLabel *Label_options_image_section3=new QLabel("XRF");
//  QLabel *Label_options_image_section4=new QLabel("RGB color");

  Checkbox_add_original_image=new QCheckBox(this);
  Checkbox_add_original_image->setCheckState(Qt::Unchecked);
//  connect(Checkbox_add_original_image,SIGNAL(stateChanged(int)),this,SLOT(add_original_image_slot(int)));

  Checkbox_add_colorbar=new QCheckBox(this);
  Checkbox_add_colorbar->setCheckState(Qt::Unchecked);
//  connect(Checkbox_add_original_image,SIGNAL(stateChanged(int)),this,SLOT(add_color_slot(int)));

  Grid_options_image_section->addWidget(Label_add_original_image,0,0,Qt::AlignRight);
  Grid_options_image_section->addWidget(Checkbox_add_original_image,0,1,Qt::AlignLeft);
  Grid_options_image_section->addWidget(Label_add_colorbar,1,0,Qt::AlignRight);
  Grid_options_image_section->addWidget(Checkbox_add_colorbar,1,1,Qt::AlignLeft);

  W_options_image_section->setLayout(Grid_options_image_section);

  // control buttons
//  QPushButton *Button_apply = new QPushButton(tr("Apply"));
//  connect(Button_apply,SIGNAL(clicked(bool)),this,SLOT(apply_slot()));

  QPushButton *Button_ok = new QPushButton(tr("OK"));
  connect(Button_ok,SIGNAL(clicked(bool)),this,SLOT(accept_slot()));

  QWidget *Widget_b=new QWidget;
  QHBoxLayout *Horizontal_layout=new QHBoxLayout;

  Horizontal_layout->addStretch();
//  Horizontal_layout->addWidget(Button_apply);
  Horizontal_layout->addWidget(Button_ok);

  Widget_b->setLayout(Horizontal_layout);


  // main
  QVBoxLayout *Vertical_layout=new QVBoxLayout;

  Vertical_layout->addWidget(W_options_image_section);
  Vertical_layout->addWidget(Widget_b);

  setLayout(Vertical_layout);

  setWindowTitle("Image section parameters");
}

//HEA

void _w_options_image_section::accept_slot()
{
  if (Checkbox_add_original_image->checkState()==Qt::Checked) *Add_original_image=true;
  else *Add_original_image=false;

  if (Checkbox_add_colorbar->checkState()==Qt::Checked) *Add_colorbar=true;
  else *Add_colorbar=false;

  close();
}

