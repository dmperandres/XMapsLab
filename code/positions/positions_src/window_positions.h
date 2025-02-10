//**************************************************************************
//
// Domingo Martin Perandres© 2014-2017
// http://calipso.ugr.es/dmartin
// dmartin@ugr.es
//
// GPL
//**************************************************************************

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <GL/glew.h>
#include <QMainWindow>
#include <QMenuBar>
//#include <QGLFormat>
#include <QAction>
#include <QActionGroup>
#include <QToolBar>
#include <QRect>
#include <QApplication>
#include <QScreen>
#include <QWizardPage>
#include <QDir>
#include <QDateTime>
#include <QSettings>
#include <QProcess>

#include <vector>
#include <deque>

#include "common.h"

//#include "w_color_bar.h"
//#include "w_tab.h"
#include "w_options_positions.h"
#include "w_number.h"

#include "splitter.h"
#include "splitter_handle.h"

//#include "atomic_data.h"

#include "layer_positions.h"
#include "layer_basic_positions.h"

#include "vertex.h"

//#include "layer_canny.h"
//#include "layer_dog.h"
//#include "layer_kang.h"
//#include "layer_element.h"
//#include "layer_combination.h"
//#include "layer_element.h"
#include "layer_positions_positions.h"

#include "dialog_num_samples.h"

#include "file_positions_txt.h"
#include "file_info_txt.h"
//#include "file_info_csv.h"
#include "file_project_data_csv.h"
#include "file_elements_csv.h"

#include "table_positions.h"

#include "data_io.h"

#include "w_directory.h"

#include "common_window.h"

class _gl_widget_positions;

namespace _window_positions_ns {

  const QString Program_name="Positions";
  const QString Program_version="v1.0.0";
  const QDateTime Program_date_time=QDateTime::currentDateTime();
  const QString Program_date=Program_date_time.toString("dd.MM.yy");

  const QString Help_string=Program_name+" "+Program_version+" "+Program_date+"\n\nCreated by Domingo Martín (dmartin@ugr.es)\n\nThis program is part of a research project.\nAll the information is at: https://xmapslab.org\n\n";

  const QString Project_name="./project_name.ini";

  const float SCREEN_WIDTH_FACTOR=0.5f;
  const float SCREEN_HEIGHT_FACTOR=0.9f;

  const int ICON_SIZE_1080=75;

  typedef enum {UPDATE_MODE_ADD,UPDATE_MODE_REPLACE,UPDATE_MODE_REMOVE,UPDATE_MODE_NOTHING} _update_mode;

  enum class _color_type:unsigned char {COLOR_TYPE_TONE,COLOR_TYPE_COLOR};

//  enum class _action_type:unsigned char{ACTION_DEFAULT,ACTION_ADD_POINTS,ACTION_REMOVE_POINTS,ACTION_MOVE_POINTS,ACTION_ADD_POINT_NUMBER,ACTION_REMOVE_POINT_NUMBER,ACTION_MOVE_POINTS_NUMBER_INCREASE,ACTION_MOVE_POINTS_NUMBER_DECREASE,ACTION_LAST};
  enum class _action_type:unsigned char{ACTION_DEFAULT,ACTION_ADD_POINTS,ACTION_REMOVE_POINTS,ACTION_MOVE_POINTS,ACTION_LAST};

  const float MINIMUM_THRESHOLD_DISTANCE=5.0f; // 5 pixels
  const float PERCENTAGE_THRESHOLD_DISTANCE=0.1f;

  //
  const float NUMBER_OF_ROWS=40; // number of rows we want to show

  //
  const int MAIN_IMAGE=0;
  const int AUXILIARY_IMAGE=1;
}

class _window_main;

class _window_positions : public QMainWindow
{
    Q_OBJECT

public:
  //
  _window_main *Window_main=nullptr;

  // Main image
  std::shared_ptr<cv::Mat> Main_image=nullptr;
  std::shared_ptr<_gl_widget_positions> Main_gl_widget=nullptr;
  std::vector<std::shared_ptr<_layer_positions>> Vec_layers;
  std::vector<GLuint> Vec_textures;
  std::vector<float> Vec_transparency;
  _vertex2i ZOI={_vertex2i(0,0)};

  // for the auxiliary image
  std::shared_ptr<cv::Mat> Auxiliary_image=nullptr;
  std::shared_ptr<_gl_widget_positions> Auxiliary_gl_widget=nullptr;
  std::shared_ptr<_layer_positions> Auxiliary_layer;
  GLuint Auxiliary_texture;
  float Auxiliary_transparency;


  int Selected_layer=-1;
  int Selected_tab=0;
  int Selected_palette=0;

  _window_positions();
  ~_window_positions();

//  int ui_font_size(){return UI_font_size;}
//  void ui_font_size(int Size);
//  void pass_ui_font_size(int UI_font_size1);

  void read_settings();
  void save_settings();

  void initialize_palettes_data();

  int screen_width(){return Screen_width;}
  int screen_height(){return Screen_height;}

  void change_button_state(int Row,int Col);

  void restart();

  void add_layer_image(std::shared_ptr<cv::Mat> Image1);
  void add_layer_positions();

  void update_layer(std::string Name);
  void update_layer(int Pos);

  int search_point(int Pos_x, int Pos_y);
  void update_positions(int Pos_x, int Pos_y);

  void adjust_image_sizes(int &Width1, int &Height1);

  void compute_dimensions();

  void change_translation(int Translation_x1, int Translation_y1);
//  _vertex2f translation(int Position_gl_widget){return Vec_translations[Position_gl_widget];}

  void change_scale(float Scale1);
//  float scaling(int Position_gl_widget){return Vec_scaling[Position_gl_widget];}

//  void save_image(QString File_name);

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

  // positions print
  void print_font_factor(float Positions_print_font_factor1){Print_font_factor=Positions_print_font_factor1;}
  float print_font_factor(){return Print_font_factor;}

  void parameters_changed();

  void options_parameters_display(int Font_size_display1, int Out_circle_size_display1, QColor Font_color_display1, QColor Out_circle_color_display1, QColor In_circle_color_display1,  QColor Selection_out_circle_color_display1, QColor Selection_in_circle_color_display1,bool Copy_display_values1);

  void options_parameters_print(int Font_size_print1, int Out_circle_size_print1, QColor Font_color_print1, QColor Out_circle_color_print1, QColor In_circle_color_print1);

  // for the list of positions
  void add_position_number(int Position);

//  bool check_project();

  // bool copy_display_values(){return Copy_display_values;}

  int image_width();
  int image_height();

  void selected_position(int Position1,bool Position_active1);

  void project_dir(QString Project_dir1){Project_dir=Project_dir1;}
  void load_project();

public slots:
  void load_project_slot();
  void load_auxiliary_image_slot();

  void save_positions_slot();
  void save_image_slot();

  void options_slot();

#ifndef UNIFIED
  void info_slot();
#endif

  void left_handle_slot();
  void right_handle_slot();

  void action_default_slot();
  void action_add_points_slot();
  void action_remove_points_slot();
  void action_move_points_slot();

protected:
//  void load_project();

  std::shared_ptr<cv::Mat> load_image(std::string File_name);

  void save_image(QString File_name);
  void save_image_positions();

  void compute_display_values();

//  void closeEvent(QCloseEvent *Event) override;

  void load_positions();

  QWizardPage* createIntroPage();
  //
  _window_positions_ns::_action_type Action_type=_window_positions_ns::_action_type::ACTION_DEFAULT;

  int Screen_width=0;
  int Screen_height=0;

  //
  int UI_font_size=_common_ns::UI_FONT_SIZE_DEFAULT;

  bool Loaded_image=false;

  std::string Initial_image;

  QAction *Load_project=nullptr;
  QAction *Load_auxiliary_image=nullptr;
//  QAction *Load_positions=nullptr;
//  QAction *Save_project=nullptr;
  QAction *Save_positions=nullptr;
  QAction *Save_image=nullptr;
  QAction *Options=nullptr;

  QImage Image;

  QActionGroup *Action_group=nullptr;
  std::vector<QAction *> Vec_actions;

  _splitter *Splitter=nullptr;
  bool Left_part_full=true;
  int Left_part_size=-1;

  bool Right_part_full=true;
  int Right_part_size=-1;

  bool Replace=false;
  int Replace_position=-1;

  int Insert_position=0;

  QString Project_name;

  QString Project_dir;

  // options
  //
  _w_options_positions *W_options=nullptr;

  // display
  int Display_font_size=_w_options_positions_ns::DISPLAY_FONT_SIZE_DEFAULT;
  int Display_out_circle_size=_w_options_positions_ns::DISPLAY_OUT_CIRCLE_SIZE_DEFAULT;
  QColor Display_font_color=_w_options_positions_ns::DISPLAY_FONT_COLOR_DEFAULT;
  QColor Display_out_circle_color=_w_options_positions_ns::DISPLAY_OUT_CIRCLE_COLOR_DEFAULT;
  QColor Display_in_circle_color=_w_options_positions_ns::DISPLAY_IN_CIRCLE_COLOR_DEFAULT;
  QColor Display_selection_out_circle_color=_w_options_positions_ns::DISPLAY_SELECTION_OUT_CIRCLE_COLOR_DEFAULT;
  QColor Display_selection_in_circle_color=_w_options_positions_ns::DISPLAY_SELECTION_IN_CIRCLE_COLOR_DEFAULT;
  // positions print
  float Print_font_factor=_w_options_positions_ns::PRINT_FONT_FACTOR_DEFAULT;

  //
  int Action_selected=0;

  QToolBar *ToolBar=nullptr;

  QIcon Icons[8][2];

  //
  int Last_position=0;
//  deque<_common_ns::_position_data> Deque_positions;
  std::vector<_common_ns::_position_data> Vec_positions;

  float Distance_threshold;

  // table for positions
  _table_positions *Table_positions=nullptr;

  //
  int Positions_width;
  int Positions_height;

  //
  _project_data_ns::_project_data Project_data;

  //
  std::vector<_data_xrf_ns::_data_xrf_pdb> Vec_data_xrf_pdb;
  std::vector<std::string> Vec_names_xrf_pdb;

#ifdef XRD_ACTIVE
  std::vector<_data_xrd_ns::_data_xrd_pdb> Vec_data_xrd_pdb;
#endif

  std::vector<std::string> Vec_names_xrd_pdb;

  bool Mode_normal=false;

  float Main_image_scaling=1;
  _vertex2f Main_image_translation=_vertex2f(0,0);

  //
  int Initial_width;
  int Initial_height;
};

#endif
