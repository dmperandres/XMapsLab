/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "w_table.h"
#include "window_tools.h"

_w_table::_w_table(_window *Window1,_project_data_ns::_project_data &Project_data):QDialog((QWidget*)Window1)
{
  int Pos=0;

  Window=Window1;
  QTableWidgetItem *Item;

  Tablewidget=new QTableWidget;
  Tablewidget->setColumnCount(Project_data.Vec_coordinate_x_original.size()+2);

  Tablewidget->insertRow(Pos);
  //
  Item = new QTableWidgetItem("PROJECT_NAME");
  Item->setFlags(Qt::ItemIsEnabled);
  Tablewidget->setItem(Pos,0,Item);
  Item = new QTableWidgetItem(QString::fromStdString(Project_data.Project_name));
  Item->setFlags(Qt::ItemIsEnabled);
  Tablewidget->setItem(Pos,1,Item);
  Pos++;
  //
  Tablewidget->insertRow(Pos);
  Item = new QTableWidgetItem("AUTHOR");
  Item->setFlags(Qt::ItemIsEnabled);
  Tablewidget->setItem(Pos,0,Item);
  Item = new QTableWidgetItem(QString::fromStdString(Project_data.Author));
  Item->setFlags(Qt::ItemIsEnabled);
  Tablewidget->setItem(Pos,1,Item);
  Pos++;
  //
  Tablewidget->insertRow(Pos);
  Item = new QTableWidgetItem("DATE");
  Item->setFlags(Qt::ItemIsEnabled);
  Tablewidget->setItem(Pos,0,Item);
  Item = new QTableWidgetItem(QString::fromStdString(Project_data.Date));
  Item->setFlags(Qt::ItemIsEnabled);
  Tablewidget->setItem(Pos,1,Item);
  Pos++;
  //
  Tablewidget->insertRow(Pos);
  Item = new QTableWidgetItem("DEVICE");
  Item->setFlags(Qt::ItemIsEnabled);
  Tablewidget->setItem(Pos,0,Item);
  Item = new QTableWidgetItem(QString::fromStdString(Project_data.Device));
  Item->setFlags(Qt::ItemIsEnabled);
  Tablewidget->setItem(Pos,1,Item);
  Pos++;
  //
  Tablewidget->insertRow(Pos);
  Item = new QTableWidgetItem("TUBE");
  Item->setFlags(Qt::ItemIsEnabled);
  Tablewidget->setItem(Pos,0,Item);
  Item = new QTableWidgetItem(_data_xrd_ns::Vec_tube_name[int(Project_data.XRD_tube_type)]);
  Item->setFlags(Qt::ItemIsEnabled);
  Tablewidget->setItem(Pos,1,Item);
  Pos++;
  //
//  Tablewidget->insertRow(Pos);
//  Item = new QTableWidgetItem("XRF_DATA_ADJUSTMENT");
//  Item->setFlags(Qt::ItemIsEnabled);
//  Tablewidget->setItem(Pos,0,Item);
//  Item = new QTableWidgetItem(_data_xrf_ns::Vec_xrf_data_adjustment_name[int(Project_data.XRF_data_adjustment)]);
//  Item->setFlags(Qt::ItemIsEnabled);
//  Tablewidget->setItem(Pos,1,Item);
//  Pos++;
  //
  Tablewidget->insertRow(Pos);
  Item = new QTableWidgetItem("WIDTH");
  Item->setFlags(Qt::ItemIsEnabled);
  Tablewidget->setItem(Pos,0,Item);
  Item = new QTableWidgetItem(QString("%1").arg(Project_data.Width_pixel));
  Item->setFlags(Qt::ItemIsEnabled);
  Tablewidget->setItem(Pos,1,Item);
  Pos++;
  //
  Tablewidget->insertRow(Pos);
  Item = new QTableWidgetItem("HEIGHT");
  Item->setFlags(Qt::ItemIsEnabled);
  Tablewidget->setItem(Pos,0,Item);
  Item = new QTableWidgetItem(QString("%1").arg(Project_data.Height_pixel));
  Item->setFlags(Qt::ItemIsEnabled);
  Tablewidget->setItem(Pos,1,Item);
  Pos++;
  //
//  Tablewidget->insertRow(Pos);
//  Item = new QTableWidgetItem("NUM_SAMPLES");
//  Item->setFlags(Qt::ItemIsEnabled);
//  Tablewidget->setItem(Pos,0,Item);
//  Item = new QTableWidgetItem(QString("%1").arg(Project_data.Num_samples));
//  Item->setFlags(Qt::ItemIsEnabled);
//  Tablewidget->setItem(Pos,1,Item);
//  Pos++;
  //
  Tablewidget->insertRow(Pos);
  Item = new QTableWidgetItem("X");
  Item->setFlags(Qt::ItemIsEnabled);
  Tablewidget->setItem(Pos,0,Item);
  Item = new QTableWidgetItem("-");
  Item->setFlags(Qt::ItemIsEnabled);
  Tablewidget->setItem(Pos,1,Item);
  for (unsigned int i=0;i<Project_data.Vec_coordinate_x.size();i++){
    Item = new QTableWidgetItem(QString("%1").arg(Project_data.Vec_coordinate_x[i]));
    Item->setFlags(Qt::ItemIsEnabled);
    Tablewidget->setItem(Pos,2+i,Item);
  }
  Pos++;
  //
  Tablewidget->insertRow(Pos);
  Item = new QTableWidgetItem("Y");
  Item->setFlags(Qt::ItemIsEnabled);
  Tablewidget->setItem(Pos,0,Item);
  Item = new QTableWidgetItem("-");
  Item->setFlags(Qt::ItemIsEnabled);
  Tablewidget->setItem(Pos,1,Item);
  for (unsigned int i=0;i<Project_data.Vec_coordinate_y.size();i++){
    Item = new QTableWidgetItem(QString("%1").arg(Project_data.Vec_coordinate_y[i]));
    Item->setFlags(Qt::ItemIsEnabled);
    Tablewidget->setItem(Pos,2+i,Item);
  }
  Pos++;
  //
  for (unsigned int i=0;i<Project_data.Vec_xrf_interpreted_data.size();i++){
    Tablewidget->insertRow(Pos);
    Item = new QTableWidgetItem("XRF");
    Item->setFlags(Qt::ItemIsEnabled);
    Tablewidget->setItem(Pos,0,Item);
    Item = new QTableWidgetItem(QString::fromStdString(Project_data.Vec_xrf_interpreted_data[i].Name));
    Item->setFlags(Qt::ItemIsEnabled);
    Tablewidget->setItem(Pos,1,Item);
    for (unsigned int j=0;j<Project_data.Vec_xrf_interpreted_data[i].Vec_values.size();j++){
      Item = new QTableWidgetItem(QString("%1").arg(Project_data.Vec_xrf_interpreted_data[i].Vec_values[j]));
      Item->setFlags(Qt::ItemIsEnabled);
      Tablewidget->setItem(Pos,2+j,Item);
    }
    Pos++;
  }

  Tablewidget->setMinimumSize(500,500);

  QDialogButtonBox *Dialogbuttonbox=new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel);

  connect(Dialogbuttonbox, &QDialogButtonBox::accepted, this, &QDialog::accept);
  connect(Dialogbuttonbox, &QDialogButtonBox::rejected, this, &QDialog::reject);

  // main
  QVBoxLayout *Vertical_layout=new QVBoxLayout;

  Vertical_layout->addWidget(Tablewidget);
  Vertical_layout->addWidget(Dialogbuttonbox);

  setLayout(Vertical_layout);

  setWindowTitle("Spreadsheet");
}

/*************************************************************************/

//void _w_table::accept_slot()
//{
////  Window->options_parameters(Spinbox_positions_display_font_size->value(), Spinbox_positions_display_out_circle_size->value(), Button_positions_display_font_color->color(), Button_positions_display_out_circle_color->color(), Button_positions_display_in_circle_color->color());
//}

/*************************************************************************/

//void _w_table::cancel_slot()
//{
////  Window->options_parameters(Spinbox_positions_display_font_size->value(), Spinbox_positions_display_out_circle_size->value(), Button_positions_display_font_color->color(), Button_positions_display_out_circle_color->color(), Button_positions_display_in_circle_color->color());

//  close();
//}

