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

  const int POSITIONS_DISPLAY_FONT_SIZE=0;
  const int POSITIONS_DISPLAY_OUT_CIRCLE_SIZE=0;
  const QColor POSITIONS_DISPLAY_FONT_COLOR=QColor(Qt::blue);
  const QColor POSITIONS_DISPLAY_OUT_CIRCLE_COLOR=QColor(Qt::blue);
  const QColor POSITIONS_DISPLAY_IN_CIRCLE_COLOR=QColor(Qt::yellow);
  const QColor POSITIONS_DISPLAY_SELECTION_OUT_CIRCLE_COLOR=QColor(Qt::magenta);
  const QColor POSITIONS_DISPLAY_SELECTION_IN_CIRCLE_COLOR=QColor(Qt::yellow);

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

  _window_positions(_window_main *Window_main1);
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

//  // options display
//  void positions_font_size_display(int Value){Positions_font_size_display=Value;}
//  int positions_font_size_display(){return Positions_font_size_display;}

//  void positions_out_circle_size_display(int Value){Positions_out_circle_size_display=Value;}
//  int positions_out_circle_size_display(){return Positions_out_circle_size_display;}

//  void positions_font_color_display(QColor Color1){Positions_font_color_display=Color1;}
//  QColor positions_font_color_display(){return Positions_font_color_display;}

//  void positions_out_circle_color_display(QColor Color1){Positions_out_circle_color_display=Color1;}
//  QColor positions_out_circle_color_display(){return Positions_out_circle_color_display;}

//  void positions_in_circle_color_display(QColor Color1){Positions_in_circle_color_display=Color1;}
//  QColor positions_in_circle_color_display(){return Positions_in_circle_color_display;}

//  void positions_selection_out_circle_color_display(QColor Color1){Positions_selection_out_circle_color_display=Color1;}
//  QColor positions_selection_out_circle_color_display(){return Positions_selection_out_circle_color_display;}

//  void positions_selection_in_circle_color_display(QColor Color1){Positions_selection_in_circle_color_display=Color1;}
//  QColor positions_selection_in_circle_color_display(){return Positions_selection_in_circle_color_display;}

  void parameters_changed();

  void options_parameters_display(int Font_size_display1, int Out_circle_size_display1, QColor Font_color_display1, QColor Out_circle_color_display1, QColor In_circle_color_display1,  QColor Selection_out_circle_color_display1, QColor Selection_in_circle_color_display1,bool Copy_display_values1);

//  // options print
//  void positions_font_size_print(int Value){Positions_font_size_print=Value;}
//  int positions_font_size_print(){return Positions_font_size_print;}

//  void positions_out_circle_size_print(int Value){Positions_out_circle_size_print=Value;}
//  int positions_out_circle_size_print(){return Positions_out_circle_size_print;}

//  void positions_font_color_print(QColor Color1){Positions_font_color_print=Color1;}
//  QColor positions_font_color_print(){return Positions_font_color_print;}

//  void positions_out_circle_color_print(QColor Color1){Positions_out_circle_color_print=Color1;}
//  QColor positions_out_circle_color_print(){return Positions_out_circle_color_print;}

//  void positions_in_circle_color_print(QColor Color1){Positions_in_circle_color_print=Color1;}
//  QColor positions_in_circle_color_print(){return Positions_in_circle_color_print;}

  void options_parameters_print(int Font_size_print1, int Out_circle_size_print1, QColor Font_color_print1, QColor Out_circle_color_print1, QColor In_circle_color_print1);

  // for the list of positions
  void add_position_number(int Position);

//  bool check_project();

  bool copy_display_values(){return Copy_display_values;}

  int image_width();
  int image_height();

  void selected_position(int Position1,bool Position_active1);

  void project_dir(QString Project_dir1){Project_dir=Project_dir1;}
  void load_project();

public slots:
  void load_project_slot();
  void load_auxiliary_image_slot();
//  void load_positions_slot();
//  void load_elements();

//  void save_project_slot();
  void save_positions_slot();
  void save_image_slot();

  void options_slot();

//  void program_interpreter_slot();
//  void program_maplab_slot();
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
//  int Positions_font_size_display=_window_positions_ns::POSITIONS_DISPLAY_FONT_SIZE;
//  int Positions_out_circle_size_display=_window_positions_ns::POSITIONS_DISPLAY_OUT_CIRCLE_SIZE;
//  QColor Positions_font_color_display=_window_positions_ns::POSITIONS_DISPLAY_FONT_COLOR;
//  QColor Positions_out_circle_color_display=_window_positions_ns::POSITIONS_DISPLAY_OUT_CIRCLE_COLOR;
//  QColor Positions_in_circle_color_display=_window_positions_ns::POSITIONS_DISPLAY_IN_CIRCLE_COLOR;
//  QColor Positions_selection_out_circle_color_display=_window_positions_ns::POSITIONS_DISPLAY_SELECTION_OUT_CIRCLE_COLOR;
//  QColor Positions_selection_in_circle_color_display=_window_positions_ns::POSITIONS_DISPLAY_SELECTION_IN_CIRCLE_COLOR;
  bool Copy_display_values=true;

  // print
//  int Positions_font_size_print=_window_positions_ns::POSITIONS_DISPLAY_FONT_SIZE;
//  int Positions_out_circle_size_print=_window_positions_ns::POSITIONS_DISPLAY_OUT_CIRCLE_SIZE;
//  QColor Positions_font_color_print=_window_positions_ns::POSITIONS_DISPLAY_FONT_COLOR;
//  QColor Positions_out_circle_color_print=_window_positions_ns::POSITIONS_DISPLAY_OUT_CIRCLE_COLOR;
//  QColor Positions_in_circle_color_print=_window_positions_ns::POSITIONS_DISPLAY_SELECTION_IN_CIRCLE_COLOR;

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
};

#endif
