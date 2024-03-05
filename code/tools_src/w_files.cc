/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "w_files.h"
#include "window_tools.h"

_w_files::_w_files(_window_tools *Window1, QStringList File_names):QDialog((QWidget*)Window1)
{
  Window=Window1;

  QListWidget *Listwidget=new QListWidget();
  Listwidget->addItems(File_names);
  Listwidget->setMinimumSize(500,500);

  // Positions rendering
//  QGroupBox *Groupbox_image=new QGroupBox;
//  Groupbox_image->setTitle("Selected image");

//  QVBoxLayout *Vboxlayout_image=new QVBoxLayout;

//  Vboxlayout_image->addWidget(Image_label);

//  Groupbox_image->setLayout(Vboxlayout_image);

  // control buttons
//  QPushButton *Button_apply = new QPushButton(tr("Apply"));
//  connect(Button_apply,SIGNAL(clicked(bool)),this,SLOT(apply_slot()));

//  QPushButton *Button_ok = new QPushButton(tr("Close window"));
//  connect(Button_ok,SIGNAL(clicked(bool)),this,SLOT(accept()));

//  QWidget *Widget_b=new QWidget;
//  QHBoxLayout *Horizontal_layout=new QHBoxLayout;

//  Horizontal_layout->addStretch();
//  Horizontal_layout->addWidget(Button_apply);
//  Horizontal_layout->addWidget(Button_ok);

//  Widget_b->setLayout(Horizontal_layout);
  QDialogButtonBox *Dialogbuttonbox=new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);

  connect(Dialogbuttonbox, &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(Dialogbuttonbox, &QDialogButtonBox::rejected, this, &QDialog::reject);

//  Dialogbuttonbox->addButton(tr("OK"), QDialogButtonBox::AcceptRole);
//  Dialogbuttonbox->addButton(tr("Cancel"),QDialogButtonBox::RejectRole);

  // main
  QVBoxLayout *Vertical_layout=new QVBoxLayout;

  Vertical_layout->addWidget(Listwidget);
  Vertical_layout->addWidget(Dialogbuttonbox);

  setLayout(Vertical_layout);

  setWindowTitle("Selected files");
}

/*************************************************************************/

//void _w_files::accept_slot()
//{
////  Window->options_parameters(Spinbox_positions_display_font_size->value(), Spinbox_positions_display_out_circle_size->value(), Button_positions_display_font_color->color(), Button_positions_display_out_circle_color->color(), Button_positions_display_in_circle_color->color());
//}

/*************************************************************************/

//void _w_files::cancel_slot()
//{
////  Window->options_parameters(Spinbox_positions_display_font_size->value(), Spinbox_positions_display_out_circle_size->value(), Button_positions_display_font_color->color(), Button_positions_display_out_circle_color->color(), Button_positions_display_in_circle_color->color());

//  close();
//}

