/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <GL/glew.h>
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

#include <opencv2/core.hpp>

#include <vector>
#include <string>
#include <map>
#include <algorithm>

#include "w_color_bar.h"
#include "w_tab.h"
#include "w_options.h"

#include "splitter.h"
#include "splitter_handle.h"

#include "atomic_data.h"

#include "file_positions_txt.h"
#include "file_info_txt.h"
#include "file_interpreted_txt.h"
#include "file_elements_csv.h"
#include "file_project_data_csv.h"

#include "layer.h"
#include "layer_basic.h"
#include "layer_map_distance.h"
#include "layer_map_triangulation.h"
#include "layer_map_rbf_interpolation.h"
#include "layer_positions.h"
//#include "layer_triangulation.h"
//#include "layer_mask.h"

#include "layer_compound_combination.h"

#include "glwidget.h"

#include "images_tab.h"

#include "common.h"

#include "pigment_data.h"

#include "data_io.h"

#include "w_directory.h"

#include "data_xrd.h"

class _gl_widget;
class _gl_widget_pos;
class _gl_widget_ge;

namespace _window_ns {

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

  const int BGR_ERROR_DEFAULT=25; // 25% of signal

  // window parameters
  const int WINDOW_X_POS_DEFAULT=50;
  const int WINDOW_Y_POS_DEFAULT=50;
  const int WINDOW_WIDTH_DEFAULT=1000;
  const int WINDOW_HEIGHT_DEFAULT=800;

  // short name, name, atomic number, atomic weight, color
  const std::vector<_atomic_data> Vec_atomic_data={
    {"Ag","silver",47,QColor(255,0,0)},
    {"Al","aluminium",13,QColor(255,149,0)},
    {"Ar","argon",18,QColor(213,255,0)},
    {"As","arsenic",33,QColor(240,50,230)},
    {"Au","gold",79,QColor(0,255,85)},
    {"B","boron",5,QColor(0,255,234)},
    {"Ba","barium",56,QColor(60,180,75)},
    {"Be","beryllium",4,QColor(21,0,255)},
    {"Bi","bismuth",83,QColor(170,0,255)},
    {"Br","bromine",35,QColor(255,0,191)},
    {"C","carbon",6,QColor(255,0,42)},
    {"Ca","calcium",20,QColor(255,255,25)},
    {"Cd","cadmium",48,QColor(0,130,200)},
    {"Ce","cerium",58,QColor(106,255,0)},
    {"Cl","chlorine",17,QColor(0,255,42)},
    {"Co","cobalt",27,QColor(245,130,48)},
    {"Cr","chromium",24,QColor(145,30,180)},
    {"Cs","caesium",55,QColor(0,21,255)},
    {"Cu","copper",29,QColor(70,240,240)},
    {"Dy","dysprosium",66,QColor(255,0,234)},
    {"Er","erbium",68,QColor(255,0,85)},
    {"Eu","europium",63,QColor(255,64,0)},
    {"F","fluorine",9,QColor(255,213,0)},
    {"Fe","iron",26,QColor(230,25,75)},
    {"Ga","gallium",31,QColor(0,255,0)},
    {"Gd","gadolinium",64,QColor(0,255,149)},
    {"Ge","germanium",32,QColor(0,213,255)},
    {"H","hydrogen",1,QColor(0,64,255)},
    {"He","helium",2,QColor(85,0,255)},
    {"Hf","hafnium",72,QColor(234,0,255)},
    {"Hg","mercury",80,QColor(210,245,60)},
    {"Ho","holmium",67,QColor(255,21,0)},
    {"I","iodine",53,QColor(255,170,0)},
    {"In","indium",49,QColor(191,255,0)},
    {"Ir","iridium",77,QColor(42,255,0)},
    {"K","potassium",19,QColor(0,128,128)},
    {"Kr","krypton",36,QColor(0,255,255)},
    {"La","lanthanum",57,QColor(0,106,255)},
    {"Li","lithium",3,QColor(42,0,255)},
    {"Lu","lutetium",71,QColor(191,0,255)},
    {"Mg","magnesium",12,QColor(255,0,170)},
    {"Mn","manganese",25,QColor(220,190,255)},
    {"Mo","molybdenum",42,QColor(255,128,0)},
    {"N","nitrogen",7,QColor(234,255,0)},
    {"Na","sodium",11,QColor(85,255,0)},
    {"Nb","niobium",41,QColor(0,255,64)},
    {"Nd","neodymium",60,QColor(0,255,213)},
    {"Ne","neon",10,QColor(0,149,255)},
    {"Ni","nickel",28,QColor(170,110,40)},
    {"O","oxygen",8,QColor(149,0,255)},
    {"Os","osmium",76,QColor(255,0,213)},
    {"P","phosphorus",15,QColor(0,178,255)},
    {"Pb","lead",82,QColor(128,0,0)},
    {"Pd","palladium",46,QColor(255,234,0)},
    {"Pm","promethium",61,QColor(128,255,0)},
    {"Pr","praseodymium",59,QColor(0,255,21)},
    {"Pt","platinum",78,QColor(0,255,170)},
    {"Rb","rubidium",37,QColor(0,191,255)},
    {"Re","rhenium",75,QColor(0,42,255)},
    {"Rh","rhodium",45,QColor(106,0,255)},
    {"Ru","ruthenium",44,QColor(255,0,255)},
    {"S","sulfur",16,QColor(255,0,106)},
    {"Sb","antimony",51,QColor(170,255,195)},
    {"Sc","scandium",21,QColor(255,135,0)},
    {"Se","selenium",34,QColor(128,128,0)},
    {"Si","silicon",14,QColor(21,255,0)},
    {"Sm","samarium",62,QColor(0,255,128)},
    {"Sn","tin",50,QColor(0,0,128)},
    {"Sr","strontium",38,QColor(0,85,255)},
    {"Ta","tantalum",73,QColor(64,0,255)},
    {"Tb","terbium",65,QColor(213,0,255)},
    {"Tc","technetium",43,QColor(255,0,149)},
    {"Te","tellurium",52,QColor(255,0,0)},
    {"Th","thorium",90,QColor(255,110,0)},
    {"Ti","titanium",22,QColor(255,215,180)},
    {"Tl","thallium",81,QColor(130,0,255)},
    {"Tm","thulium",69,QColor(64,255,0)},
    {"V","vanadium",23,QColor(0,255,85)},
    {"W","tungsten",74,QColor(0,255,234)},
    {"Xe","xenon",54,QColor(0,128,255)},
    {"Y","yttrium",39,QColor(21,0,255)},
    {"Yb","ytterbium",70,QColor(170,0,255)},
    {"Zn","zinc",30,QColor(60,180,75)},
    {"Zr","zirconium",40,QColor(155,0,255)}
  };

  // 20 distinct colors: https://sashamaps.net/docs/resources/20-colors/
  // '(230, 25, 75)', '(60, 180, 75)', '(255, 225, 25)', '(0, 130, 200)', '(245, 130, 48)', '(145, 30, 180)', '(70, 240, 240)', '(240, 50, 230)', '(210, 245, 60)', '(250, 190, 212)', '(0, 128, 128)', '(220, 190, 255)', '(170, 110, 40)', '(255, 250, 200)', '(128, 0, 0)', '(170, 255, 195)', '(128, 128, 0)', '(255, 215, 180)', '(0, 0, 128)', '(128, 128, 128)', '(255, 255, 255)', '(0, 0, 0)'
  // red, green, yellow, blue, orange, purple, cyan, magenta, lime, pink, teal, lavende, bronw, beige, marron, mint, olive, apricot, navy, grey, white, black

  // positions
  enum class _update_mode: unsigned char {UPDATE_MODE_ADD,UPDATE_MODE_REPLACE,UPDATE_MODE_REMOVE,UPDATE_MODE_NOTHING};

  // machine states
  enum class _state: unsigned char {STATE_NORMAL,STATE_STATISTICS,STATE_HISTOGRAM,STATE_LABORATORY,STATE_3D};

  const QString Project_name="./project_name.ini";

  // layers
  const _palette_data_ns::_data_type_print DATA_TYPE_PRINT_DEFAULT=_palette_data_ns::_data_type_print::DATA_TYPE_PRINT_INT;

  // elements
  const int MAP_INTERPOLATION_TYPE_DEFAULT=int(_layer_map_ns::MAP_INTERPOLATION_TYPE_DEFAULT);
  const int COLOR_MODEL_DEFAULT=int(_common_ns::COLOR_MODEL_DEFAULT);
  const bool USE_COLOR1_DEFAULT=true;
  const bool USE_COLOR2_DEFAULT=true;
  const bool USE_COLOR3_DEFAULT=true;
  const bool USE_POSITION1_DEFAULT=true;
  const bool USE_POSITION2_DEFAULT=true;
  const bool NORMALIZATION_DEFAULT=true;
  const int POSITION_NORMALIZATION_TYPE_DEFAULT=int(_layer_map_distance_ns::NORMALIZATION_TYPE_DEFAULT);
  const int PROBE_DEFAULT=_layer_map_ns::PROBE_DEFAULT;
  const int PALETTE_DEFAULT=3;
  const bool TRIANGULATION_ADD_CORNERS_DEFAULT=false;

  // palettes
  const _color_map_ns::_color_for_zero_value COLOR_FOR_ZERO_VALUE_DEFAULT=_color_map_ns::_color_for_zero_value::COLOR_ZERO_VALUE_BLACK;

  const float MOUSE_SCALING_FACTOR=1.05;

  const int NUM_TESTS=10;

#include "common_window.h"
}

class _window : public QMainWindow
{
    Q_OBJECT

public:
  // the widget that renders OpenGL
  _gl_widget *GL_widget=nullptr;

  // the widget for the color bar
  _w_color_bar *Color_bar_widget=nullptr;

  // the widget for the tabs
  _w_tab *Tab_widget=nullptr;  

  //
  QWidget *Mapping_widget=nullptr;

  // Is this for node editor ?
  _images_tab *Mapping_images_tab=nullptr;

  // the widgets for the node editor

  // map a name with the layer data
  std::map<std::string,_pigment_data_ns::_layer_data> Map_name_to_layer;

  // map a name with the corresponding normalized input image
  // (check for saving space: do the normalization when needed) ???
  std::map<std::string,std::vector<std::shared_ptr<cv::Mat>>> Map_normalized_images;

  // vector with the names of the ordered layers
  std::vector<std::string> Vec_order_of_layers_by_name;

  // maps the name of an element with its data
  std::map<std::string,_pigment_data_ns::_pigment_data> Map_name_to_element;

  // maps the name of an element with its data

  // vector with the names of the elements
  std::vector<std::string> Vec_element_names;

  // vector with the names of the compounds

  std::vector<_palette_data> Vec_palette_data;

  // map the name of a layer with the name of an element
  // for example Fe_cp_1 -> Fe
  std::map<std::string,std::string> Map_name_of_layer_to_name_of_element;

  int Initial_width;
  int Initial_height;

  int Statistics_x=-1;
  int Statistics_y=-1;

  // positions
  _vertex2i ZOI={_vertex2i(0,0)};
  std::vector<float> Scaling={1,1};

  // vector with the active positions
  std::vector<bool> Vec_active_positions;
  int Num_active_positions;

  // for the images ?
  std::vector<std::string> *Vec_order_mapping=nullptr;

  // nodes

  // bug
  int Num_days;

  _window();
  ~_window(){};

  int ui_font_size(){return UI_font_size;}
  void ui_set_font_size(int Size);

  void read_settings();
  void save_settings();

  void initialize_palettes_data();

  int screen_width(){return Screen_width;}
  int screen_height(){return Screen_height;}

  void change_button_state(int Row,int Col);

//  void restart();

  void compute_normalized_images(std::string Name,std::shared_ptr<cv::Mat> Original);

  void move_layers_backward(int Initial_pos, int Destination_pos);
  void move_layers_forward(int Initial_pos, int Destination_pos);

  void remove_pigment_layer(int Row);
  void remove_pigment_layer();
  void remove_all_pigment_layers();

  void remove_layer(int Row);
  void remove_all_layers();
//  void recompute_all_layers();

  void update_order_images(std::string Name);
  void show_layer_parameters(int Row,int Col);

  void add_layer_image(std::string Name1,std::shared_ptr<cv::Mat> Image1);
  void add_layer_filter(_layer_ns::_layer_type Layer_type);

  void add_layer_map_minimum_hypercube_distance(std::string Name_image1, std::string Name_pigment1, std::string View_name1, _common_ns::_color_model Color_model1, std::vector<bool> Use_colors1, std::vector<bool> Use_positions1, bool Distance_normalization1, _layer_map_distance_ns::_position_normalization_type Position_normalization_type1, int Probe1, int Palette1, _palette_data_ns::_data_type_print Data_type_print1, _color_map_ns::_color_for_zero_value Color_for_zero_value1,std::map<std::string,_pigment_data_ns::_pigment_data> &Map_pigment_data);

  void add_layer_map_rbf_interpolation(std::string Name_image1, std::string Name_pigment1, std::string View_name1, _common_ns::_color_model Color_model1, int Palette1, _palette_data_ns::_data_type_print Data_type_print1, _color_map_ns::_color_for_zero_value Color_for_zero_value1, std::map<std::string,_pigment_data_ns::_pigment_data> &Map_pigment_data);

  void add_layer_map_triangulation(std::string Name_image1, std::string Name_pigment1, std::string View_name1, _common_ns::_color_model Color_model1, int Palette1, bool Triangulation_add_corners1, _palette_data_ns::_data_type_print Data_type_print1, _color_map_ns::_color_for_zero_value Color_for_zero_value1, std::map<std::string,_pigment_data_ns::_pigment_data> &Map_pigment_data);

  void add_layer_compound_combination(std::string Name_image1, std::string Name_pigment1, std::string View_name1, std::vector<_data_xrf_ns::_data_element_num_atoms> Vec_elements1, std::vector<std::string> Vec_names_in_map1, std::vector<float> Vec_global_percentages1,int Palette1, _palette_data_ns::_data_type_print Data_type_print1, _color_map_ns::_color_for_zero_value Color_for_zero_value1);

  void update_layer(std::string Name);
  void update_layer(int Pos);

  void update_color_bar();
  void update_color_bar_data_type_print(int Type1);

  // auxiliar function to get the correct width and heigh (divisible by 4)
  void adjust_image_sizes(int &Width1, int &Height1);

  bool show_positions(){return Show_positions;}
  _layer_map_triangulation_ns::_triangulation_mode show_triangulation(){return Triangulation_mode;}

  void adjust_by_atomic_number(bool XRF_adjust_by_atomic_number1){XRF_adjust_by_atomic_number=XRF_adjust_by_atomic_number1;}
  bool adjust_by_atomic_number(){return XRF_adjust_by_atomic_number;}

  void adjust_by_atomic_weight(bool XRF_adjust_by_atomic_weight1){XRF_adjust_by_atomic_weight=XRF_adjust_by_atomic_weight1;}
  bool adjust_by_atomic_weight(){return XRF_adjust_by_atomic_weight;}

  int elements_computed(){return Num_elements_computed;}

  void reverse_col(int Col);

  bool loaded_image(){return Loaded_image;}

  void set_save_single_layer_enable(bool Value){Submenu_save_single_layer->setEnabled(Value);}
  void set_save_all_layers_enable(bool Value){Submenu_save_all_layers->setEnabled(Value);}

  // positions
  void draw_positions(QPainter &Painter, float Widht1, float Height1);
  void save_positions_image(std::string Layer);

  // to select the image that is used for the interpolation in MHD
  void selected_image(std::string Image_name);
  int mapping_selected_image_index(){return Mapping_selected_image_index;}

  std::string mapping_selected_image_name(){return Mapping_selected_image_name;}

  // nodes

  // palette data
  QColor compute_color(std::string Name_element);

  // Delaunay triangulation
  std::vector<_delaunay_triangulator_ns::_triangle> &triangles(){return Triangles;}

  //
  _window_ns::_state state(){return State;}

  // for checking if there is a open project
  bool check_project();

  // options
  // positions display
  void positions_display_font_size(int Value){Positions_display_font_size=Value;}
  int positions_display_font_size(){return Positions_display_font_size;}

  void positions_display_out_circle_size(int Value){Positions_display_out_circle_size=Value;}
  int positions_display_out_circle_size(){return Positions_display_out_circle_size;}

  void positions_display_font_color(QColor Color1){Positions_display_font_color=Color1;}
  QColor positions_display_font_color(){return Positions_display_font_color;}

  void positions_display_out_circle_color(QColor Color1){Positions_display_out_circle_color=Color1;}
  QColor positions_display_out_circle_color(){return Positions_display_out_circle_color;}

  void positions_display_in_circle_color(QColor Color1){Positions_display_in_circle_color=Color1;}
  QColor positions_display_in_circle_color(){return Positions_display_in_circle_color;}

  // positions print
  void positions_print_font_factor(float Positions_print_font_factor1){Positions_print_font_factor=Positions_print_font_factor1;}
  float positions_print_font_factor(){return Positions_print_font_factor;}

  // layers
  void data_type_print(_palette_data_ns::_data_type_print Data_type_print1){Data_type_print=Data_type_print1;}
  _palette_data_ns::_data_type_print data_type_print(){return Data_type_print;}

  // elements
  void view_name(std::string View_name1){View_name=View_name1;}
  std::string view_name(){return View_name;}

  // interpolation method
  void map_interpolation_type(_layer_map_ns::_map_interpolation_methods Interpolation_type1){Interpolation_type=Interpolation_type1;}
  _layer_map_ns::_map_interpolation_methods map_interpolation_type(){return Interpolation_type;}

  void color_model(_common_ns::_color_model Color_model1){Color_model=Color_model1;}
  _common_ns::_color_model color_model(){return Color_model;}

  // parameters for MHD function
  void use_colors(int Pos,bool Value);
  bool use_colors(int Pos);

  void use_positions(int Pos,bool Value);
  bool use_positions(int Pos);

  void distance_normalization(bool Distance_normalization1){Distance_normalization=Distance_normalization1;}
  bool distance_normalization(){return Distance_normalization;}

  void position_normalization_type(_layer_map_distance_ns::_position_normalization_type Position_normalization_type1){Position_normalization_type=Position_normalization_type1;}
  _layer_map_distance_ns::_position_normalization_type position_normalization_type(){return Position_normalization_type;}

  void palette(int Palette1){Palette=Palette1;}
  int palette(){return Palette;}

  void probe(int Probe1){Probe=Probe1;}
  int probe(){return Probe;}

  void triangulation_add_corners(bool Triangulation_add_corners1){Triangulation_add_corners=Triangulation_add_corners1;}
  bool triangulation_add_corners(){return Triangulation_add_corners;}

  void rbf_radius(float Radius1){RBF_radius=Radius1;}
  float rbf_radius(){return RBF_radius;}

  void rbf_function(_new_rbf_interpolation_2d_ns::_function_type RBF_function1){RBF_function=RBF_function1;};
  _new_rbf_interpolation_2d_ns::_function_type rbf_function(){return RBF_function;}

  // palette
  void color_for_zero_value(_color_map_ns::_color_for_zero_value Color_for_zero_value1){Color_for_zero_value=Color_for_zero_value1;}
  _color_map_ns::_color_for_zero_value color_for_zero_value(){return Color_for_zero_value;}

  // update when the parameter have been changed
  void parameters_changed();

  // active positions
  void change_active_position(int Position);
  bool active_position(int Position){return Vec_active_positions[Position];}
  std::vector<bool>& vec_active_positions(){return Vec_active_positions;}

  // for the list of xrf files
//  bool xrf_file_state(int Row){return Vec_xrf_file_state[Row].Selected;}
  void xrf_recompute_data();
  std::vector<_pigment_data_ns::_file_state_data>& vec_xrf_file_state(){return  Vec_xrf_file_state;}

  // for the list of xrd files

  // images
  void name_selected_image(std::string Name_selected_image1){Name_selected_image=Name_selected_image1;}
  std::string name_selected_image(){return Name_selected_image;}

  // elements
  void elements_selected_names(std::vector<std::string> Vec_elements_selected_names1){Vec_names_of_selected_elements=Vec_elements_selected_names1;}
  std::vector<std::string> elements_selected_names(){return Vec_names_of_selected_elements;}
  void elements_create_some_maps();
  void elements_create_all_maps();

  // compounds XRD

  // compounds from combinations
  void compounds_from_elements_selected_names(std::vector<std::string> Vec_compounds_from_elements_selected_names1){Vec_compounds_from_elements_selected_names=Vec_compounds_from_elements_selected_names1;}
  void compounds_from_elements_create_some_maps();
  void compounds_from_elements_create_all_maps();

  //
  void selected_layer(int Selected_layer1){Selected_layer=Selected_layer1;}
  int selected_layer(){return Selected_layer;}

  void selected_palette(int Selected_palette1){Selected_palette=Selected_palette1;}
  int selected_palette(){return Selected_palette;}

  void selected_tab(_w_tab_ns::_tabs Selected_tab1){Selected_tab=Selected_tab1;}
  _w_tab_ns::_tabs selected_tab(){return Selected_tab;}

  //
  int initial_width(){return Initial_width;}
  int initial_height(){return Initial_height;}
  int max_dimension(){
    if (Initial_width>Initial_height) return Initial_width;
    else return Initial_height;
  }

  //
  int num_valid_positions(){return Num_active_positions;}
  //
  float mean_distance_between_positions(){return Mean_distance_between_positions;}
  float mean_distance_between_neighbors_positions(){return Mean_distance_between_neighbors_positions;}

public slots:  
  void load_project_data_slot();
  void close_project_slot();
  void save_single_layer_slot();
  void save_single_layer_with_color_bar_slot();
  void save_all_layers_slot();
  void save_all_layers_with_color_bar_slot();
//  void save_positions_image_slot();
  void save_composed_image_slot();
  void options_slot();
  void info_slot();

  void left_handle_slot();
  void right_handle_slot();

  void show_positions_slot();
  void show_triangulation_normal_slot();
  void show_triangulation_with_corners_slot();

  void normal_slot();

  //mapping

  // View 3D

  // splitter
  void splitter_moved_slot(int Pos,int Index);

protected:
  void closeEvent(QCloseEvent *Event) override;

  //
  void save_single_layer(std::string Name);
  void save_single_layer_with_color_bar(std::string Name,float Value);

  void save_all_layers();
  void save_all_layers_with_color_bar();

  // images
  void load_images();

  void process_xrf_map_data();
//  bool load_xrf_data();
  void load_data_csv_format(bool& XRF_data_loaded,bool& XRD_data_loaded);

  void load_compounds_combination();

  void add_layer_positions_image();

  void create_filter_list();

  void load_project();

  void xrf_process_data(_pigment_data_ns::_pigment_data &Element_data);

  // auxilar functions for RBF
  void compute_mean_distance_between_positions();
  void compute_mean_distance_between_neighbors_positions();

  //
  int Screen_width=0;
  int Screen_height=0;

  //
  int UI_font_size=_common_ns::UI_FONT_SIZE_DEFAULT;

  // window parameters
  QSize Window_size=QSize(_window_ns::WINDOW_WIDTH_DEFAULT,_window_ns::WINDOW_HEIGHT_DEFAULT);
  QPoint Window_position=QPoint(_window_ns::WINDOW_X_POS_DEFAULT,_window_ns::WINDOW_Y_POS_DEFAULT);

  bool Loaded_image=false;
  int Num_images=0;
  std::string Initial_image;

  QMenu* Menu_view=nullptr;
  QMenu* Submenu_save_single_layer=nullptr;
  QMenu* Submenu_save_all_layers=nullptr;
  QMenu* Submenu_add_show_triangulation=nullptr;

  QAction *Load_project=nullptr;
  QAction *Close_project=nullptr;
  QAction *Save_single_layer=nullptr;
  QAction *Save_single_layer_with_color_bar=nullptr;
  QAction *Save_all_layers=nullptr;
  QAction *Save_all_layers_with_color_bar=nullptr;
  QAction *Save_positions_image=nullptr;
  QAction *Save_composed_image=nullptr;
  QAction *Options=nullptr;

  std::vector<QAction *> View;
  QAction *View_save_positions=nullptr;
  QAction *View_show_positions=nullptr;
  QAction *View_show_triangulation_normal=nullptr;
  QAction *View_show_triangulation_with_corners=nullptr;

  QImage Image;

  QActionGroup *Action_group=nullptr;
  std::vector<QAction *> Vec_actions;

  _splitter *Splitter=nullptr;
  QSplitter *Splitter_edit=nullptr;
  QSplitter *Splitter_view=nullptr;
  QSplitter *Splitter_view_2D_3D=nullptr;

  // handles
  bool Left_part_full=true;
  int Left_part_size=-1;

  bool Right_part_full=true;
  int Right_part_size=-1;

  QString Project_dir;
  QString Project_name;

  bool Show_positions=false;
  _layer_map_triangulation_ns::_triangulation_mode Triangulation_mode=_layer_map_triangulation_ns::_triangulation_mode::TRIANGULATION_MODE_NONE;

  int Selected_view;

  bool XRF_adjust_by_atomic_number=false;
  bool XRF_adjust_by_atomic_weight=false;

  int Num_elements_computed=0;

  // positions
  int Insert_position=0;

  // for the images
  int Mapping_selected_image_index=0;
  std::string Mapping_selected_image_name;

  // the boolean tells us if it is the first time that a project is loaded
  // For the second time, some elements have not to be created again as the widgets
  bool First_load=true;

  //
  std::vector<_pigment_data_ns::_interpreted_data> Vec_xrf_data;

  std::vector<int> Match_errors;

  int Selected_row=0;
  int Selected_col=1;

  //*** options
  _w_options *W_options=nullptr;

  // positions display
  int Positions_display_font_size;
  int Positions_display_out_circle_size;
  QColor Positions_display_font_color;
  QColor Positions_display_out_circle_color;
  QColor Positions_display_in_circle_color;
  QColor Positions_display_selection_out_circle_color;
  QColor Positions_display_selection_in_circle_color;

  // positions print
  float Positions_print_font_factor;

  // layers
  _palette_data_ns::_data_type_print Data_type_print;

  // elements
  std::string View_name=_w_tab_ns::VIEW_NAME_DEFAULT.toStdString();
  _layer_map_ns::_map_interpolation_methods Interpolation_type;
  _common_ns::_color_model Color_model;
  std::vector<bool> Use_colors={true,true,true};
  std::vector<bool> Use_positions={true,true};
  int Palette;
  bool Distance_normalization;
  _layer_map_distance_ns::_position_normalization_type Position_normalization_type;
  int Probe;
  float RBF_radius;
  _new_rbf_interpolation_2d_ns::_function_type RBF_function=_new_rbf_interpolation_2d_ns::FUNCTION_TYPE_DEFAULT;
  std::string Name_selected_image;

  // vector of the slected names
  std::vector<std::string> Vec_names_of_selected_elements;

  bool Triangulation_add_corners;

  // palette
  _color_map_ns::_color_for_zero_value Color_for_zero_value;

  // 3D

  // triangulation
  std::vector<_delaunay_triangulator_ns::_triangle> Triangles;
  std::vector<_delaunay_triangulator_ns::_triangle> Triangles_with_corners;

  // element history
//  map<std::string,_pigment_data_ns::_history_data> Element_history;

  // state
  _window_ns::_state State=_window_ns::_state::STATE_NORMAL;

  // sizes for chart and image widgets
  bool Size_adjusted=false;
  int Size_chart=-1;

  // xrf files
  std::vector<_pigment_data_ns::_file_state_data> Vec_xrf_file_state;
  int XRF_selected_file;

  // xrd files

  //
  int Selected_layer=-1;
  int Selected_palette=0;

  _w_tab_ns::_tabs Selected_tab=_w_tab_ns::_tabs::POSITIONS_TAB;

  //
  bool XRF_data_loaded=false;
  bool XRD_data_loaded=false; // this is maintained for simplicity with the load function

  // class for data of a project project
  _project_data_ns::_project_data Project_data;

  std::vector<_data_xrf_ns::_data_xrf_pdb> Vec_xrf_pdb_data;
  std::vector<std::string> Vec_xrf_pdb_names;
  std::vector<std::string> Vec_xrd_pdb_names; // this is maintained for simplicity with the load function

  //
  bool Mode_normal=false;

  // mean distance between positions
  float Mean_distance_between_positions=1;
  float Mean_distance_between_neighbors_positions=1;

  // ONLY ONE ORIGINAL IMAGE
  std::shared_ptr<cv::Mat> Original_image=nullptr;

  // compound_combination
  std::vector<std::string> Vec_compounds_from_elements_selected_names;

  std::vector<_data_xrf_ns::_data_compound_from_elements_pdb> Vec_compounds_from_elements_pdb;
};

#endif
