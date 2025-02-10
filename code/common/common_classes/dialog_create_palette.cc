//LIC

#include "dialog_create_palette.h"
//#include "glwidget_xmapslab.h"
#include "palette_data.h"

_dialog_create_palette::_dialog_create_palette(_palette_data *Vec_palette_data1, _w_tab *W_tab1)
{
  W_tab=W_tab1;
  Vec_palette_data=Vec_palette_data1;

  // type
  QGroupBox *Groupbox_type=new QGroupBox;
  Groupbox_type->setTitle("Type");

  QGridLayout *Grid_type=new QGridLayout;

  QLabel *Label_type1=new QLabel("Sections");
  QLabel *Label_type2=new QLabel("Continous");

  Radiobutton_type1=new QRadioButton;
  QRadioButton *Radiobutton_type2=new QRadioButton;
  Radiobutton_type1->setChecked(true);

  Grid_type->addWidget(Label_type1,0,0,Qt::AlignLeft);
  Grid_type->addWidget(Radiobutton_type1,0,1,Qt::AlignCenter);
  Grid_type->addWidget(Label_type2,1,0,Qt::AlignLeft);
  Grid_type->addWidget(Radiobutton_type2,1,1,Qt::AlignCenter);

  Groupbox_type->setLayout(Grid_type);

//  connect(Radiobutton_type1,SIGNAL(toggled(bool)),this,SLOT(type_slot(bool)));

  // Color type
  QGroupBox *Groupbox_color_type=new QGroupBox;
  Groupbox_color_type->setTitle("Color type");

  QGridLayout *Grid_color_type=new QGridLayout;

  QLabel *Label_color_type1=new QLabel("Tone");
  QLabel *Label_color_type2=new QLabel("Color");

  Radiobutton_color_type1=new QRadioButton;
  QRadioButton *Radiobutton_color_type2=new QRadioButton;
  Radiobutton_color_type1->setChecked(true);

  Grid_color_type->addWidget(Label_color_type1,0,0,Qt::AlignLeft);
  Grid_color_type->addWidget(Radiobutton_color_type1,0,1,Qt::AlignCenter);
  Grid_color_type->addWidget(Label_color_type2,1,0,Qt::AlignLeft);
  Grid_color_type->addWidget(Radiobutton_color_type2,1,1,Qt::AlignCenter);

  Groupbox_color_type->setLayout(Grid_color_type);

//  connect(Radiobutton_color_type1,SIGNAL(toggled(bool)),this,SLOT(color_type_slot(bool)));

  // Num steps
  QGroupBox *Groupbox_num_steps=new QGroupBox;
  Groupbox_num_steps->setTitle("Number of steps");

  QGridLayout *Grid_num_steps=new QGridLayout;

  QLabel *Label_num_steps1=new QLabel("Num steps");

  Spinbox_num_steps=new QSpinBox;
  Spinbox_num_steps->setRange(2,10);

  Grid_num_steps->addWidget(Label_num_steps1,0,0,Qt::AlignLeft);
  Grid_num_steps->addWidget(Spinbox_num_steps,0,1,Qt::AlignRight);

  Groupbox_num_steps->setLayout(Grid_num_steps);

//  connect(Lineedit_interpolation1,SIGNAL(returnPressed()),this,SLOT(num_steps_slot()));

  // name
  QGroupBox *Groupbox_palette_name=new QGroupBox;
  Groupbox_palette_name->setTitle("Name");

  QGridLayout *Grid_palette_name=new QGridLayout;

  QLabel *Label_palette_name1=new QLabel("Name:");

  Lineedit_palette_name1=new QLineEdit;

  Grid_palette_name->addWidget(Label_palette_name1,0,0,Qt::AlignLeft);
  Grid_palette_name->addWidget(Lineedit_palette_name1,0,1,Qt::AlignRight);

  Groupbox_palette_name->setLayout(Grid_palette_name);

//  connect(Lineedit_palette_name1,SIGNAL(textChanged(QString)),this,SLOT(name_changed_slot(QString)));

  //
  QHBoxLayout *Horizontal1=new QHBoxLayout;

  Horizontal1->addWidget(Groupbox_type);
  Horizontal1->addWidget(Groupbox_color_type);
  Horizontal1->addWidget(Groupbox_num_steps);
  Horizontal1->addWidget(Groupbox_palette_name);

  QWidget *Widged_p=new QWidget;

  Widged_p->setLayout(Horizontal1);

  // control buttons
  QPushButton *Button_ok = new QPushButton(tr("Ok"));
  QPushButton *Button_cancel = new QPushButton(tr("Cancel"));

  connect(Button_ok,SIGNAL(clicked(bool)),this,SLOT(accept_slot()));
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

  setWindowTitle("Create palette");
}

//HEA

void _dialog_create_palette::accept_slot()
{
  // check the results
  if (Radiobutton_type1->isChecked()==true){
   Vec_palette_data->data_type(_palette_data_ns::_data_type::DATA_TYPE_DISCRETE);
  }
  else{
   Vec_palette_data->data_type(_palette_data_ns::_data_type::DATA_TYPE_CONTINUOUS);
  }

  if (Radiobutton_color_type1->isChecked()==true){
   Vec_palette_data->color_type(_palette_data_ns::_color_type::COLOR_TYPE_TONE);
  }
  else{
   Vec_palette_data->color_type(_palette_data_ns::_color_type::COLOR_TYPE_COLOR);
  }

  Vec_palette_data->num_steps(Spinbox_num_steps->value());

  Vec_palette_data->name(Lineedit_palette_name1->text());

  emit accept();
}
