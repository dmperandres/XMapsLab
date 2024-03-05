/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#ifndef WINDOW_MAIN_H
#define WINDOW_MAIN_H

#include <QMainWindow>
#include <QMenuBar>

#include <QSurfaceFormat>
#include <QAction>
#include <QActionGroup>
#include <QToolBar>
#include <QRect>
#include <QApplication>
#include <QScreen>
#include <QWizardPage>
#include <QSettings>
#include <QDateTime>
#include <QActionGroup>
#include <QSize>
#include <QPoint>
#include <QMessageBox>
#include <QSplitter>

#include <vector>
#include <string>
#include <map>
#include <algorithm>

#include "window_xmapslab.h"
#include "window_positions.h"
#include "window_tools.h"

#ifdef INTERPRETER
#include "window_interpreter.h"
#endif


#include "data_io.h"

namespace _window_main_ns {

  const QString Program_name="XMapsLab";
  const QString Program_version="v1.0.0";
  const QDateTime Program_date_time=QDateTime::currentDateTime();
  const QString Program_date=Program_date_time.toString("dd.MM.yy");

  const QString Help_string=Program_name+" "+Program_version+" "+Program_date+"\n\nCreated by Domingo Martín (dmartin@ugr.es)\n\nThis program is part of a research project.\nAll the information is at: https://calipso.ugr.es/xmapslab.org\n\n";

  const float SCREEN_WIDTH_FACTOR=0.5f;
  const float SCREEN_HEIGHT_FACTOR=0.9f;

  enum class _chart_mode:unsigned char {CHART_MODE_BAR,CHART_MODE_LINE,CHART_MODE_PIE};

  const _chart_mode CHART_MODE_DEFAULT=_chart_mode::CHART_MODE_BAR;

  const int ICON_SIZE_1080=75;

  enum class _update_positions:unsigned char {UPDATE_POSITIONS_IMAGE_TO_TABLE,UPDATE_POSITIONS_TABLE_TO_IMAGE};

  const int WIDTH_TAB_CHARS=20;

  const int XRF_BGR_ERROR_DEFAULT=25; // 25% of signal

  // window parameters
  const int WINDOW_X_POS_DEFAULT=50;
  const int WINDOW_Y_POS_DEFAULT=50;
  const int WINDOW_WIDTH_DEFAULT=1000;
  const int WINDOW_HEIGHT_DEFAULT=800;

  // message strings
  const QString MESSAGE_NO_IMAGE_TITLE="<big>There is not image in the project</big>";
#ifdef INTERPRETER
  const QString MESSAGE_NO_IMAGE_INFO="Please,<ul><li>add an image for a <b>STANDARD</b> project</li><li>add random positions for a <b>TEST</b> project</li></ul>";
#else
  const QString MESSAGE_NO_IMAGE_INFO="Please, add an image for the project";
#endif

  const QString MESSAGE_NO_POSITIONS_TITLE="<big>There are not defined positions in project_data.csv file</big>";
#ifdef INTERPRETER
  const QString MESSAGE_NO_POSITIONS_INFO="Please, add the positions to the project using:<ul><li>A CSV file using <b>Tools</b> tab</li><li>Interactively using <b>Positions</b> tab</li></ul>";
#else
  const QString MESSAGE_NO_POSITIONS_INFO="Please, add the positions to the project using <b>Positions</b> tab";
#endif

  // if (Positions_exists==false){
  //   msgBox.setText();
  //   msgBox.setInformativeText();

}

class _window_main : public QMainWindow
{
    Q_OBJECT

public:
    // class for data of a project project
    _project_data_ns::_project_data Project_data;

  _window_main();
  ~_window_main(){};

  void project_dir(QString Project_dir1);
  QString project_dir(){return Project_dir;}

  void check_project_state();

  void ui_font_size(int UI_font_size1);
  int ui_font_size(){return UI_font_size;}

  void change_font_size(int Font_size,QWidget* Widget);

  void read_settings();
  void save_settings();

  // options display
  void display_font_size(int Value){Display_font_size=Value;}
  int display_font_size(){return Display_font_size;}

  void display_out_circle_size(int Value){Display_out_circle_size=Value;}
  int display_out_circle_size(){return Display_out_circle_size;}

  void display_font_color(QColor Color1){Display_font_color=Color1;}
  QColor display_font_color(){return Display_font_color;}

  void display_out_circle_color(QColor Color1){Display_out_circle_color=Color1;}
  QColor display_out_circle_color(){return Display_out_circle_color;}

  void display_in_circle_color(QColor Color1){Display_in_circle_color=Color1;}
  QColor display_in_circle_color(){return Display_in_circle_color;}

  void display_selection_out_circle_color(QColor Color1){Display_selection_out_circle_color=Color1;}
  QColor display_selection_out_circle_color(){return Display_selection_out_circle_color;}

  void display_selection_in_circle_color(QColor Color1){Display_selection_in_circle_color=Color1;}
  QColor display_selection_in_circle_color(){return Display_selection_in_circle_color;}

//  void options_parameters_display(int Font_size_display1, int Out_circle_size_display1, QColor Font_color_display1, QColor Out_circle_color_display1, QColor In_circle_color_display1,  QColor Selection_out_circle_color_display1, QColor Selection_in_circle_color_display1,bool Copy_display_values1);

  // options print
  void print_font_size(int Value){Print_font_size=Value;}
  int print_font_size(){return Print_font_size;}

  void print_out_circle_size(int Value){Print_out_circle_size=Value;}
  int print_out_circle_size(){return Print_out_circle_size;}

  void print_font_color(QColor Color1){Print_font_color=Color1;}
  QColor print_font_color(){return Print_font_color;}

  void print_out_circle_color(QColor Color1){Print_out_circle_color=Color1;}
  QColor print_out_circle_color(){return Print_out_circle_color;}

  void print_in_circle_color(QColor Color1){Print_in_circle_color=Color1;}
  QColor print_in_circle_color(){return Print_in_circle_color;}

//  void options_parameters_print(int Font_size_print1, int Out_circle_size_print1, QColor Font_color_print1, QColor Out_circle_color_print1, QColor In_circle_color_print1);

  void parameters_changed();

protected slots:
       void tabbar_clicked(int Index);

protected:
  void closeEvent(QCloseEvent *Event) override;

  void load_image(std::string File_name);
  void adjust_image_sizes(int& Width1, int& Height1);
  bool check_xrf_files_exist();
  bool check_xrd_files_exist();

  //
  int Screen_width=0;
  int Screen_height=0;

  // window parameters
  QSize Window_size=QSize(_common_ns::WINDOW_WIDTH_DEFAULT,_common_ns::WINDOW_HEIGHT_DEFAULT);
  QPoint Window_position=QPoint(_common_ns::WINDOW_X_POS_DEFAULT,_common_ns::WINDOW_Y_POS_DEFAULT);

  //
  int UI_font_size=_common_ns::UI_FONT_SIZE_DEFAULT;

  //
  QTabWidget *Main_tab=nullptr;

#ifdef INTERPRETER
  _window_interpreter* Window_interpreter=nullptr;
#endif

  _window_xmapslab* Window_xmapslab=nullptr;
  _window_positions* Window_positions=nullptr;
  _window_tools* Window_tools=nullptr;

  QString Project_dir="";
//  QString Project_name;

  bool XRF_data_loaded=false;
  bool XRD_data_loaded=false;

  std::vector<std::string> Vec_xrf_pdb_names;
  std::vector<std::string> Vec_xrd_pdb_names; // this is maintained for simplicity with the load function

  QString File_image_name;

  bool Image_exists=false;
  bool Image_loaded=false;
  std::shared_ptr<cv::Mat> Image_vis=nullptr;

  bool Positions_exists=false;

  bool XRF_data_exist=false;
  bool XRD_data_exist=false;

  float Distance_threshold=0;

  bool XRF_artax_files_exist=false;
  bool XRD_files_exist=false;

  //
  int Previous_tab=0;
  int Current_tab=0;

  // options
  // display
  int Display_font_size=_window_positions_ns::POSITIONS_DISPLAY_FONT_SIZE;
  int Display_out_circle_size=_window_positions_ns::POSITIONS_DISPLAY_OUT_CIRCLE_SIZE;
  QColor Display_font_color=_window_positions_ns::POSITIONS_DISPLAY_FONT_COLOR;
  QColor Display_out_circle_color=_window_positions_ns::POSITIONS_DISPLAY_OUT_CIRCLE_COLOR;
  QColor Display_in_circle_color=_window_positions_ns::POSITIONS_DISPLAY_IN_CIRCLE_COLOR;
  QColor Display_selection_out_circle_color=_window_positions_ns::POSITIONS_DISPLAY_SELECTION_OUT_CIRCLE_COLOR;
  QColor Display_selection_in_circle_color=_window_positions_ns::POSITIONS_DISPLAY_SELECTION_IN_CIRCLE_COLOR;

  // print
  int Print_font_size=_window_positions_ns::POSITIONS_DISPLAY_FONT_SIZE;
  int Print_out_circle_size=_window_positions_ns::POSITIONS_DISPLAY_OUT_CIRCLE_SIZE;
  QColor Print_font_color=_window_positions_ns::POSITIONS_DISPLAY_FONT_COLOR;
  QColor Print_out_circle_color=_window_positions_ns::POSITIONS_DISPLAY_OUT_CIRCLE_COLOR;
  QColor Print_in_circle_color=_window_positions_ns::POSITIONS_DISPLAY_SELECTION_IN_CIRCLE_COLOR;

  // map for valid tabs
  std::map<std::string,int> Map_tab_name_to_index;
};

#endif
