/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRect>
#include <QApplication>
#include <QScreen>
#include <QFrame>
#include <QVBoxLayout>
#include <QPushButton>
#include <QProcess>
#include <QString>
#include <QDir>
#include <QMessageBox>
#include <QApplication>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QWizard>
#include <QSettings>
#include <QCloseEvent>
#include <QToolButton>
#include <QWidgetAction>

#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>

#include "w_project.h"
#include "w_image.h"
#include "w_files.h"
#include "w_table.h"
#include "w_int_file_parameters.h"

#include <project_data.h>

#include "file_io.h"
#include "file_project_data_csv.h"
#include "file_elements_csv.h"
#include "file_positions_txt.h"
#include "file_info_txt.h"
#include "file_xrf_txt.h"
#include "file_ka_uxd.h"

#include "data_io.h"

#include "w_directory.h"

namespace _window_ns {
  const QString Program_name="Tools";
  const QString Program_version="v1.0.0";
  const QDateTime Program_date_time=QDateTime::currentDateTime();
  const QString Program_date=Program_date_time.toString("dd.MM.yy");

  const QString Help_string=Program_name+" "+Program_version+" "+Program_date+"\n\nCreated by Domingo Martín (dmartin@ugr.es)\n\nThis program is part of a research project.\nAll the information is at: https://xmapslab.org\n\n";

  const float SCREEN_WIDTH_FACTOR=0.5f;
  const float SCREEN_HEIGHT_FACTOR=0.9f;

  const QString Help_text_create_project="This button allows you to create a new project folder with the name you prefer\nIt will also create the necessary subfoldersfor the images, positions, XRF and XRD data.\nA file called info.txt will be created with the informations of the project\n\nThe project will be opened to add the images, XRF and XRD files";

  const QString Help_text_open_project="This button allows you to open a project to allow to add the images, XRF and XRD files.";

  const QString Help_text_add_image="This button allows you to add the image that will be the main visible image for the project.\nThe selected image will be copied in the image subfolder.\nThe 'vis_' text will be added to the begin of the name\n It is possible to use JPG or PNG formats";

  const QString Help_text_add_all_xrf_files="This button allows you to copy all the files of the selected folder to the 'xrf' subfolder.\nEach file must star by a number that defines its sampling order.\nFor example, the first file must be '1_rest_of_the_name' or '01_rest_of_the_name'\nThe files must have 'artx.txt' format";

  const QString Help_text_add_selected_xrf_files="This button allows you to copy the selected file/files to the 'xrf' subfolder.\nEach file must star by a number that defines its sampling order.\nFor example, the first file must be '1_rest_of_the_name' or '01_rest_of_the_name'\nThe files must have 'artx.txt' format";

//  const QString Help_text_run_positions="This button allows you to run the program 'Positions' that permits to define the sample positions depending on the 'vis' image.\nIt must be used only when the project has a 'vis' image";

  const QString Project_name="./project_name.ini";

  // file names
#include "common_window.h"

  // num pass for removing BGR
  // WARNING! this value is included in Interpreter, data_xrd.h
  const unsigned int NUM_PASS_DEFAULT=3;
}

class _window : public QMainWindow
{
Q_OBJECT

public:
  _window();
  ~_window();

  void read_settings();
  void save_settings();

  void project_parameters(QString Project_folder_name1, QString Project_name1, QString Author1, QString Date1, QString Device1, QString Tube1, QString XRF_data_adjustment1, QString Widht1, QString Height1);
  bool check_project();

  void int_file_parameters(QString Name1,QString Formula1,QString XRF1,QString RGB_color1){Name=Name1;Formula=Formula1;XRF=XRF1;RGB_color=RGB_color1;}

protected slots:
  void create_project_slot();
  void open_project_slot();
  void add_image_slot();
  void xrf_add_all_files_slot();
//  void xrf_add_selected_files_slot();

//  void spreadsheet_to_project_slot();
//  void project_to_spreadsheet_slot();
  void info_slot();
  void program_slot();
  void xrf_data_csv_to_project_data_slot();

protected:
  void adjust_image_sizes(int &Width1, int &Height1);

  void add_xrf_files(QString Files_dir,QStringList Files_artax);
  void add_xrd_files(QString Files_dir,QStringList Files_uxd);

  void closeEvent(QCloseEvent *Event) override;
  void save_int_file(QString File_name,std::vector<float>& Values);

  std::vector<float> remove_noise_xrd(std::vector<float> &Raw_data, unsigned int Num_pass);

  QAction* Action_add_image=nullptr;
  QAction* Action_add_all_xrf_files=nullptr;
  QAction* Action_add_selected_xrf_files=nullptr;
  QAction* Action_add_all_xrd_files=nullptr;
  QAction* Action_add_selected_xrd_files=nullptr;
  QAction* Action_uxd_to_interpreter=nullptr;
  QAction* Action_data_plus_positions=nullptr;
  QAction* Action_add_xrf_data_xsls_to_project_data_csv=nullptr;
  QAction* Action_add_xrf_data_csv_to_project_data_csv=nullptr;
  QAction* Action_add_xrd_data_xsls_to_project_data_csv=nullptr;
  QAction* Action_add_xrd_data_csv_to_project_data_csv=nullptr;

  QMenu* Submenu_add_xrf_files=nullptr;
  QMenu* Submenu_add_xrd_files=nullptr;

  QMenu* Submenu_add_xrf_data=nullptr;
  QMenu* Submenu_add_xrd_data=nullptr;

  QString Project_dir;
  QLineEdit *Opened_project=nullptr;

  QString Project_folder_name;
  _project_data_ns::_project_data Project_data;

  std::vector<_data_xrf_ns::_data_xrf_pdb> Vec_data_xrf_pdb;
  std::vector<std::string> Vec_names_xrf_pdb;

  // xrd files
  std::vector<std::string> Vec_names_xrd_pdb; // for removing complexity in loading data

  QString Name;
  QString Formula;
  QString XRF;
  QString RGB_color;

  //
  bool Mode_normal;
};

#endif
