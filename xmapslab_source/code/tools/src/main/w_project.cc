/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#include "w_project.h"
#include "window.h"

_w_project::_w_project(_window *Window1):QDialog((QWidget*)Window1)
{
  Window=Window1;

  // check what model to use
  QFileInfo Check_file(QString::fromStdString(_common_window_ns::FILE_MODE));
  // check if file exists and if yes: Is it really a file and no directory?
  if (Check_file.exists() && Check_file.isFile()) Mode_normal=false;
  else Mode_normal=true;

  // Type input. Default type of input file (DAT or CSV
  QFrame *Frame_main=new QFrame;

  QGridLayout *Grid=new QGridLayout;

  QLabel *Label1=new QLabel("Project folder: ");
  QLabel *Label2=new QLabel("Project name: ");
  QLabel *Label3=new QLabel("Author: ");
  QLabel *Label4=new QLabel("Date: ");
  QLabel *Label5=new QLabel("Device: ");
  QLabel *Label6=new QLabel("Tube: ");
  QLabel *Label7=new QLabel("XRF data adjusment: ");

  Lineedit_project_folder_name=new QLineEdit;
  Lineedit_project_name=new QLineEdit;
  Lineedit_author=new QLineEdit;
  Lineedit_date=new QLineEdit;
  Lineedit_width=new QLineEdit;
  Lineedit_width->setValidator(new QDoubleValidator(0,10000.0, 2,Lineedit_width));
  Lineedit_height=new QLineEdit;
  Lineedit_width->setValidator(new QDoubleValidator(0,10000.0, 2,Lineedit_height));

  Lineedit_date->setText(QDateTime::currentDateTime().toString(QStringView(QString("dd/MM/yyyy"))));

  Lineedit_device=new QLineEdit;

  Combobox_tube=new QComboBox;
  for (unsigned int i=0;i<_data_xrd_ns::Vec_tube_name.size();i++){
    Combobox_tube->addItem(_data_xrd_ns::Vec_tube_name[i]);
  }

  Combobox_xrf_data_adjusment=new QComboBox;
  for (unsigned int i=0;i<_data_xrf_ns::Vec_xrf_data_adjustment_name.size();i++){
    Combobox_xrf_data_adjusment->addItem(_data_xrf_ns::Vec_xrf_data_adjustment_name[i]);
  }

  Grid->addWidget(Label1,0,0,Qt::AlignRight);
  Grid->addWidget(Lineedit_project_folder_name,0,1,Qt::AlignLeft);
  Grid->addWidget(Label2,1,0,Qt::AlignRight);
  Grid->addWidget(Lineedit_project_name,1,1,Qt::AlignLeft);
  Grid->addWidget(Label3,2,0,Qt::AlignRight);
  Grid->addWidget(Lineedit_author,2,1,Qt::AlignLeft);
  Grid->addWidget(Label4,3,0,Qt::AlignRight);
  Grid->addWidget(Lineedit_date,3,1,Qt::AlignLeft);
  Grid->addWidget(Label5,4,0,Qt::AlignRight);
  Grid->addWidget(Lineedit_device,4,1,Qt::AlignLeft);
  Grid->addWidget(Label6,5,0,Qt::AlignRight);
  Grid->addWidget(Combobox_tube,5,1,Qt::AlignLeft);
  Grid->addWidget(Label7,6,0,Qt::AlignRight);
  Grid->addWidget(Combobox_xrf_data_adjusment,6,1,Qt::AlignLeft);

  if (Mode_normal==false){
    QLabel *Label8=new QLabel("Width: ");
    QLabel *Label9=new QLabel("Height: ");

    Grid->addWidget(Label8,7,0,Qt::AlignRight);
    Grid->addWidget(Lineedit_width,7,1,Qt::AlignLeft);
    Grid->addWidget(Label9,8,0,Qt::AlignRight);
    Grid->addWidget(Lineedit_height,8,1,Qt::AlignLeft);
  }

  Frame_main->setLayout(Grid);

  //
  QHBoxLayout *Horizontal1=new QHBoxLayout;

  Horizontal1->addWidget(Frame_main);

  QWidget *Widged_p=new QWidget;

  Widged_p->setLayout(Horizontal1);

  // control buttons
  QPushButton *Button_ok = new QPushButton(tr("Accept"));
  connect(Button_ok,SIGNAL(clicked(bool)),this,SLOT(accept_slot()));

  QWidget *Widget_b=new QWidget;
  QHBoxLayout *Horizontal_layout=new QHBoxLayout;

  Horizontal_layout->addStretch();
  Horizontal_layout->addWidget(Button_ok);

  Widget_b->setLayout(Horizontal_layout);

  // main
  QVBoxLayout *Vertical_layout=new QVBoxLayout;

  Vertical_layout->addWidget(Widged_p);
  Vertical_layout->addWidget(Widget_b);

  setLayout(Vertical_layout);

  setWindowTitle("Options");
}

/*************************************************************************/

void _w_project::accept_slot()
{
  if (Mode_normal==false){
    Window->project_parameters(Lineedit_project_folder_name->text(),Lineedit_project_name->text(),Lineedit_author->text(),Lineedit_date->text(),Lineedit_device->text(), _data_xrd_ns::Vec_tube_name[Combobox_tube->currentIndex()], _data_xrf_ns::Vec_xrf_data_adjustment_name[Combobox_xrf_data_adjusment->currentIndex()], Lineedit_width->text(),Lineedit_height->text());
  }
  else{
    Window->project_parameters(Lineedit_project_folder_name->text(),Lineedit_project_name->text(),Lineedit_author->text(),Lineedit_date->text(),Lineedit_device->text(), _data_xrd_ns::Vec_tube_name[Combobox_tube->currentIndex()], _data_xrf_ns::Vec_xrf_data_adjustment_name[Combobox_xrf_data_adjusment->currentIndex()],"","");
  }

  accept();
}

/*************************************************************************/

void _w_project::apply_slot()
{
//  Window->options_parameters(Radiobutton_type_input1->isChecked(),Spinbox_positions_display_font_size->value(), Spinbox_positions_display_out_circle_size->value(), Button_positions_display_font_color->color(), Button_positions_display_out_circle_color->color(), Button_positions_display_in_circle_color->color());
}

