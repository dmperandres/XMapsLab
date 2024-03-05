/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef WINDOW_TOOLS_H
#define WINDOW_TOOLS_H

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
#include <QRegularExpression>

#include <vector>
#include <iostream>
#include <fstream>
#include <math.h>

#include "w_project.h"
#include "w_image.h"
#include "w_files.h"
#include "w_table.h"
#include "w_int_file_parameters.h"
#include "w_options_tools.h"

#include <project_data.h>

#include "file_io.h"
#include "file_project_data_csv.h"
#include "file_elements_csv.h"
#include "file_positions_txt.h"
#include "file_info_txt.h"
//#include "file_xrf_txt.h"
//#include "file_ka_uxd.h"

#include "data_io.h"

#include "w_directory.h"
#include "w_read_int.h"

namespace _window_tools_ns {
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

#ifdef XRD_ACTIVE
  const QString Help_text_add_all_xrd_files="This button allows you to copy all the files of the selected folder to the 'xrd' subfolder.\nEach file must star by a number that defines its sampling order.\nFor example, the first file must be '1_rest_of_the_name' or '01_rest_of_the_name'\nThe files must have uxd format";

  const QString Help_text_add_selected_xrd_files="This button allows you to copy the selected file/files to the 'xrd' subfolder.\nEach file must star by a number that defines its sampling order.\nFor example, the first file must be '1_rest_of_the_name' or '01_rest_of_the_name'\nThe files must have uxd format";
#endif

//  const QString Help_text_run_positions="This button allows you to run the program 'Positions' that permits to define the sample positions depending on the 'vis' image.\nIt must be used only when the project has a 'vis' image";

  const QString Project_name="./project_name.ini";

  // file names
#include "common_window.h"

  // num pass for removing BGR
  // WARNING! this value is included in Interpreter, data_xrd.h
  const unsigned int NUM_PASS_DEFAULT=3;

 const QString Style_enabled= R"(
                  QPushButton {
                     border: none;
                     background-color: transparent;
                     padding: 4px 8px;
                     color: #000000;
                     text-align: left;
                  }
                  QPushButton:hover {
                     background-color: #48b3eb;
                  }
                  QPushButton:pressed {
                     background-color: #48b3eb;
                  }
)";

  const QString Style_disabled= R"(
                  QPushButton {
                     border: none;
                     background-color: #CCCCCC;
                     padding: 4px 8px;
                     color: #FFFFFF;
                     text-align: left;
                  }
                  QPushButton:hover {
                     background-color: #48b3eb;
                  }
                  QPushButton:pressed {
                     background-color: #48b3eb;
                  }
)";

}

class _window_main;

class _window_tools : public QMainWindow
{
Q_OBJECT

public:
  _window_tools(_window_main *Window_main1);
  ~_window_tools();

  void read_settings();
  void save_settings();

  void project_parameters(QString Project_folder_name1, QString Project_name1, QString Author1, QString Date1, QString Device1, QString Tube1, QString Widht_cm1,QString Height_cm1);
  bool check_project();

  void int_file_parameters(QString Name1,QString Formula1,QString XRF1,QString RGB_color1){Name=Name1;Formula=Formula1;XRF=XRF1;RGB_color=RGB_color1;}

  void ui_font_size(int UI_font_size1);
  int ui_font_size();

  void pass_ui_font_size(int UI_font_size1);

  void show_positions();

  void hide_all();
  void show_all();  

protected slots:
  void create_project_slot();
  void open_project_slot();
  void add_image_slot();

  void add_positions_data_csv_slot();
  void add_random_positions_slot();

  void add_artax_files_slot();
  void add_xy_files_slot();
  void add_uxd_files_slot();
  void add_plv_files_slot();

//  void xrf_add_all_files_slot();
//  void xrf_add_selected_files_slot();
  void options_slot();

//  void spreadsheet_to_project_slot();
//  void project_to_spreadsheet_slot();
#ifndef UNIFIED
  void info_slot();
#endif

  void program_slot();
  void xrf_data_csv_to_project_data_slot();

//  void show_slot();

#ifdef UXD_TO_PDB_ACTIVE
  void uxd_to_interpreter_slot();
#endif

#ifdef XLSX_ACTIVE
  void data_plus_positions_slot();
  void xrf_data_xlsx_to_project_data_slot();
#endif

#ifdef XRD_ACTIVE
//  void xrd_add_all_files_slot();
//  void xrd_add_selected_files_slot();
  void xrd_data_csv_to_project_data_slot();
#ifdef XLSX_ACTIVE
  void xrd_data_xlsx_to_project_data_slot();
#endif
#endif

protected:
  void adjust_image_sizes(int &Width1, int &Height1);

  void add_artax_files(QString Files_dir,QStringList Files_artax);
  void add_xy_files(QString Files_dir,QStringList Files_xy);

  void add_uxd_files(QString Files_dir,QStringList Files_uxd);
  void add_plv_files(QString Files_dir,QStringList Files_plv);

//  void closeEvent(QCloseEvent *Event) override;
  void save_int_file(QString File_name,std::vector<float>& Values);

  std::vector<float> remove_noise_xrd(std::vector<float> &Raw_data, unsigned int Num_pass);

  QWizardPage* createIntroPage();

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

//  QMenu* Submenu_add_xrf_files=nullptr;
//  QMenu* Submenu_add_xrd_files=nullptr;

//  QMenu* Submenu_add_xrf_data=nullptr;
//  QMenu* Submenu_add_xrd_data=nullptr;

  QString Project_dir;
//  QLineEdit *Opened_project=nullptr;

  QString Project_folder_name;
  _project_data_ns::_project_data Project_data;

  std::vector<_data_xrf_ns::_data_xrf_pdb> Vec_data_xrf_pdb;
  std::vector<std::string> Vec_names_xrf_pdb;

  // xrd files
  std::vector<std::string> Vec_names_xrd_pdb; // for removing complexity in loading data

#ifdef XRD_ACTIVE
  std::vector<_data_xrd_ns::_data_xrd_pdb> Vec_data_xrd_pdb;
#endif

  QString Name;
  QString Formula;
  QString XRF;
  QString RGB_color;

  //
  bool Mode_normal;

//  QMenu *Menu=nullptr;

  //
  _window_main *Window_main=nullptr;

  QPushButton *Actionbutton_create_project=nullptr;
  QPushButton *Actionbutton_open_project=nullptr;
  QPushButton *Actionbutton_add_image=nullptr;
  QPushButton *Actionbutton_add_positions_csv=nullptr;
  QPushButton *Actionbutton_add_random_positions=nullptr;
  QPushButton *Actionbutton_add_artax_files_xrf=nullptr;
  QPushButton *Actionbutton_add_xy_files_xrf=nullptr;
  QPushButton *Actionbutton_add_uxd_files_xrd=nullptr;
  QPushButton *Actionbutton_add_plv_files_xrd=nullptr;
  QPushButton *Actionbutton_add_xrf_data_csv_to_project_data_csv=nullptr;
  QPushButton *Actionbutton_add_xrd_data_csv_to_project_data_csv=nullptr;
  QPushButton *Actionbutton_options=nullptr;
  QPushButton *Actionbutton_exit=nullptr;

  std::vector<QPushButton *> Vec_pushbuttons;

  _w_options_tools *W_options=nullptr;
};

#endif
