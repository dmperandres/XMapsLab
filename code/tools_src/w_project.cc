/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "w_project.h"
#include "window_tools.h"

_w_project::_w_project(_window_tools *Window1):QDialog((QWidget*)Window1)
{
  Window=Window1;

  setFixedWidth(500);

  // Type input. Default type of input file (DAT or CSV
  QFrame *Frame_main=new QFrame;

  QGridLayout *Grid=new QGridLayout;

  QLabel *Label1=new QLabel("Project folder: ");
  QLabel *Label2=new QLabel("Project name: ");
  QLabel *Label3=new QLabel("Author: ");
  QLabel *Label4=new QLabel("Date: ");
  QLabel *Label5=new QLabel("Device: ");
  QLabel *Label6=new QLabel("Tube: ");
  QLabel *Label7=new QLabel("Width (cm): ");
  QLabel *Label8=new QLabel("Height (cm): ");

  Lineedit_project_folder_name=new QLineEdit;
  Lineedit_project_folder_name->setFixedWidth(400);
  Lineedit_project_folder_name->setPlaceholderText("Folder name");

  Lineedit_project_name=new QLineEdit;
  Lineedit_project_name->setFixedWidth(400);
  Lineedit_project_name->setPlaceholderText("Project name");

  Lineedit_author=new QLineEdit;
  Lineedit_author->setFixedWidth(400);
  Lineedit_author->setPlaceholderText("Author name");

  Lineedit_date=new QLineEdit;
  Lineedit_date->setText(QDateTime::currentDateTime().toString(QStringView(QString("dd/MM/yyyy"))));
  Lineedit_device=new QLineEdit;
  Lineedit_device->setPlaceholderText("Used device");

  Combobox_tube=new QComboBox;
  for (unsigned int i=0;i<_data_xrd_ns::Vec_tube_name.size();i++){
    Combobox_tube->addItem(_data_xrd_ns::Vec_tube_name[i]);
  }

  Lineedit_width_cm=new QLineEdit;
  Lineedit_width_cm->setValidator(new QDoubleValidator(0,10000.0, 2,Lineedit_width_cm));
  Lineedit_width_cm->setText("0");

  Lineedit_height_cm=new QLineEdit;
  Lineedit_height_cm->setValidator(new QDoubleValidator(0,10000.0, 2,Lineedit_height_cm));
  Lineedit_height_cm->setText("0");

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
  Grid->addWidget(Lineedit_width_cm,6,1,Qt::AlignLeft);
  Grid->addWidget(Label8,7,0,Qt::AlignRight);
  Grid->addWidget(Lineedit_height_cm,7,1,Qt::AlignLeft);

  //
  Frame_main->setLayout(Grid);

  //
  QHBoxLayout *Horizontal1=new QHBoxLayout;

  Horizontal1->addWidget(Frame_main);

  QWidget *Widged_p=new QWidget;

  Widged_p->setLayout(Horizontal1);

  // control buttons
  QPushButton *Button_ok = new QPushButton(tr("Accept"));
  connect(Button_ok,SIGNAL(clicked(bool)),this,SLOT(accept_slot(bool)));

  QPushButton *Button_cancel = new QPushButton(tr("Cancel"));
  connect(Button_cancel,SIGNAL(clicked(bool)),this,SLOT(cancel_slot(bool)));

  QWidget *Widget_b=new QWidget;
  QHBoxLayout *Horizontal_layout=new QHBoxLayout;

  Horizontal_layout->addStretch();
  Horizontal_layout->addWidget(Button_ok);
  Horizontal_layout->addWidget(Button_cancel);

  Widget_b->setLayout(Horizontal_layout);

  // main
  QVBoxLayout *Vertical_layout=new QVBoxLayout;

  Vertical_layout->addWidget(Widged_p);
  Vertical_layout->addWidget(Widget_b);

  setLayout(Vertical_layout);

  setWindowTitle("Options");
}

/*************************************************************************/

void _w_project::accept_slot(bool State)
{
  Q_UNUSED(State)
  if (Lineedit_project_folder_name->text()!=""){
    if (Lineedit_project_name->text()!=""){
      if (Lineedit_author->text()!=""){
        if (Lineedit_date->text()!=""){
          if (Lineedit_device->text()!=""){
            Window->project_parameters(Lineedit_project_folder_name->text(),Lineedit_project_name->text(),Lineedit_author->text(),Lineedit_date->text(),Lineedit_device->text(), _data_xrd_ns::Vec_tube_name[Combobox_tube->currentIndex()], Lineedit_width_cm->text(),Lineedit_height_cm->text());
            accept();
          }
          else{
            QMessageBox::warning(this, tr("Warning"),tr("Please, insert a device name"));
          }
        }
        else{
          QMessageBox::warning(this, tr("Warning"),tr("Please, insert a date"));
        }
      }
      else{
        QMessageBox::warning(this, tr("Warning"),tr("Please, insert an author name"));
      }
    }
    else{
      QMessageBox::warning(this, tr("Warning"),tr("Please, insert a name for the project"));
    }
  }
  else{
    QMessageBox::warning(this, tr("Warning"),tr("Please, insert a name for the project folder"));
  }
}

/*************************************************************************/

void _w_project::cancel_slot(bool State)
{
  Q_UNUSED(State)
  reject();
}

/*************************************************************************/

//void _w_project::apply_slot()
//{
//  Window->project_parameters(Lineedit_project_folder_name->text(),Lineedit_project_name->text(),Lineedit_author->text(),Lineedit_date->text(),Lineedit_device->text(), _data_xrd_ns::Vec_tube_name[Combobox_tube->currentIndex()], Lineedit_width_cm->text(),Lineedit_height_cm->text());

////  Window->options_parameters(Radiobutton_type_input1->isChecked(),Spinbox_positions_display_font_size->value(), Spinbox_positions_display_out_circle_size->value(), Button_positions_display_font_color->color(), Button_positions_display_out_circle_color->color(), Button_positions_display_in_circle_color->color());
//}

