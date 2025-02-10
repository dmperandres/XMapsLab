//LIC

#ifndef WINDOW_XMAPSLAB_H
#define WINDOW_XMAPSLAB_H

#include <GL/glew.h>
#include <QMainWindow>
#include <QMenuBar>

//#include <QGLFormat> Not for Qt 6.xx
#include <QSurfaceFormat> // For  Qt 6

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

#include "palette_data.h"

//#include "window_xmapslab.h"

#ifdef STATISTIC_GRAPHS_ACTIVE
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLogValueAxis>
#include <QtCharts/QPieLegendMarker>
#include <QtCharts/QChartView>
#endif

#include "w_color_bar.h"
#include "w_tab_xmapslab.h"
#include "w_options_xmapslab.h"
#include "w_options_image_section.h"

#include "splitter.h"
#include "splitter_handle.h"

#include "atomic_data.h"

#include "file_positions_txt.h"
#include "file_info_txt.h"
#include "file_interpreted_txt.h"
#include "file_elements_csv.h"
#include "file_project_data_csv.h"

#include "tokenizer.h"

#ifdef MEASURE_RUN_TIME
#include <chrono>
#endif

#include "layer_xmapslab.h"
#include "layer_basic_xmapslab.h"
#include "layer_map_distance.h"
#include "layer_map_triangulation.h"
#include "layer_map_rbf_interpolation.h"
#include "layer_map_rbf_interpolation_plus.h"
#include "layer_positions_xmapslab.h"
#include "layer_triangulation.h"
#include "layer_map_lab.h"
#include "layer_map_mhd_segmentation.h"
#include "layer_map_value_segmentation.h"
//#include "layer_mask.h"

#ifdef YES_LAYERS_EDGES_CANNY
#include "layer_canny.h"
#endif

#ifdef YES_LAYERS_EDGES_DOG
#include "layer_dog.h"
#endif

#ifdef YES_LAYERS_EDGES_KANG
#include "layer_kang.h"
#endif

#ifdef YES_LAYERS_EDGES_kmeans
#include "layer_kmeans.h"
#endif


#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
#include "layer_compound_from_elements.h"
#endif

#include "glwidget_xmapslab.h"

#ifdef MODE_3D_ACTIVE
#include "glwidget_xmapslab_3D.h"
#endif


#ifdef NODE_EDITOR_ACTIVE
#include "glwidget_xmapslab_ge.h"
#include "graphics_scene.h"
#include "nodes_editor.h"
#include "graphics_view.h"

#include "filter.h"

#ifdef DEFINE_FILTER_IMAGE
#include "filter_image.h"
#endif
#ifdef DEFINE_FILTER_ELEMENT
#include "filter_element.h"
#endif
#ifdef DEFINE_FILTER_LOGIC_AND
#include "filter_logic_and.h"
#endif
#ifdef DEFINE_FILTER_LOGIC_OR
#include "filter_logic_or.h"
#endif
#ifdef DEFINE_FILTER_LOGIC_XOR
#include "filter_logic_xor.h"
#endif
#ifdef DEFINE_FILTER_LOGIC_NOT
#include "filter_logic_not.h"
#endif
#ifdef DEFINE_FILTER_CONVERSION_BIN
#include "filter_conversion_bin.h"
#endif
#ifdef DEFINE_FILTER_CONVERSION_COLOR_BIN
#include "filter_conversion_color_bin.h"
#endif
// #ifdef DEFINE_FILTER_ARITHMETIC_PRODUCT
// #include "filter_arithmetic_product.h"
// #endif
// #ifdef DEFINE_FILTER_ARITHMETIC_ADDITION
// #include "filter_arithmetic_addition.h"
// #endif
#ifdef DEFINE_FILTER_COMBINATION_ELEMENT
#include "filter_combination_element.h"
#endif
#ifdef DEFINE_FILTER_COMBINATION_ELEMENT_REMOVE
#include "filter_combination_element_remove.h"
#endif
#ifdef DEFINE_FILTER_COMBINATION_PRODUCT
#include "filter_combination_product.h"
#endif
#ifdef DEFINE_FILTER_COMBINATION_ADDITION
#include "filter_combination_addition.h"
#endif
#ifdef DEFINE_FILTER_COMBINATION_DIFFERENCE
#include "filter_combination_difference.h"
#endif
#ifdef DEFINE_FILTER_COMBINATION_ADDITION_PERCENTAGE
#include "filter_combination_addition_percentage.h"
#endif

#ifdef DEFINE_FILTER_COMBINATION_ADDITION_REMOVE
#include "filter_combination_addition_remove.h"
#endif
#ifdef DEFINE_FILTER_COLORMAP
#include "filter_colormap.h"
#endif

#endif

#ifdef XRD_ACTIVE
#include "table_xrd_xmapslab.h"
#endif

#include "tree_widget.h"

#include "nodes_editor_maps_tab.h"
#include "filters_tab.h"

#include "common.h"

#include "measurement_data.h"

#include "data_io.h"

#include "w_directory.h"

#include "data_xrd.h"

#include "common_window.h"

class _gl_widget_xmapslab;
class _gl_widget_xmapslab_ge;

namespace _window_xmapslab_ns {

  const QString Program_name="XMapsLab";
  const QString Program_version="v1.0.0";
  const QDateTime Program_date_time=QDateTime::currentDateTime();
  const QString Program_date=Program_date_time.toString("dd.MM.yy");

  const QString Help_string=Program_name+" "+Program_version+" "+Program_date+"\n\nCreated by Domingo Martín (dmartin@ugr.es)\n\nThis program is part of a research project.\nAll the information is at: https://calipso.ugr.es/xmapslab.org\n\n";


  enum class _chart_mode:unsigned char {CHART_MODE_BAR,CHART_MODE_LINE,CHART_MODE_PIE};

  const _chart_mode CHART_MODE_DEFAULT=_chart_mode::CHART_MODE_BAR;

  const int ICON_SIZE_1080=75;

  enum class _update_positions:unsigned char {UPDATE_POSITIONS_IMAGE_TO_TABLE,UPDATE_POSITIONS_TABLE_TO_IMAGE};

  const int WIDTH_TAB_CHARS=20;

  const int XRF_BGR_ERROR_DEFAULT=25; // 25% of signal

  const int WINDOW_X_POS_DEFAULT=50;
  const int WINDOW_Y_POS_DEFAULT=50;
  const int WINDOW_WIDTH_DEFAULT=1000;
  const int WINDOW_HEIGHT_DEFAULT=800;

  // short name, name, atomic number, atomic weight, color
  const std::map<std::string,_atomic_data> Map_atomic_data={
    {"Ag",{"Ag","silver",47,107.87f,QColor(255,0,0)}},
    {"Al",{"Al","aluminium",13,26.982f,QColor(255,149,0)}},
    {"Ar",{"Ar","argon",18,39.95f,QColor(213,255,0)}},
    {"As",{"As","arsenic",33,74.922f,QColor(240,50,230)}},
    {"Au",{"Au","gold",79,196.97f,QColor(0,255,85)}},
    {"B",{"B","boron",5,10.81f,QColor(0,255,234)}},
    {"Ba",{"Ba","barium",56,137.33f,QColor(60,180,75)}},
    {"Be",{"Be","beryllium",4,9.0122f,QColor(21,0,255)}},
    {"Bi",{"Bi","bismuth",83,208.98f,QColor(170,0,255)}},
    {"Br",{"Br","bromine",35,79.904f,QColor(255,0,191)}},
    {"C",{"C","carbon",6,12.011f,QColor(255,0,42)}},
    {"Ca",{"Ca","calcium",20,40.078f,QColor(255,255,25)}},
    {"Cd",{"Cd","cadmium",48,112.41f,QColor(0,130,200)}},
    {"Ce",{"Ce","cerium",58,140.12f,QColor(106,255,0)}},
    {"Cl",{"Cl","chlorine",17,35.45f,QColor(0,255,42)}},
    {"Co",{"Co","cobalt",27,58.933f,QColor(245,130,48)}},
    {"Cr",{"Cr","chromium",24,51.996f,QColor(145,30,180)}},
    {"Cs",{"Cs","caesium",55,132.91f,QColor(0,21,255)}},
    {"Cu",{"Cu","copper",29,63.546f,QColor(70,240,240)}},
    {"Dy",{"Dy","dysprosium",66,162.50f,QColor(255,0,234)}},
    {"Er",{"Er","erbium",68,167.26f,QColor(255,0,85)}},
    {"Eu",{"Eu","europium",63,151.96f,QColor(255,64,0)}},
    {"F",{"F","fluorine",9,18.998f,QColor(255,213,0)}},
    {"Fe",{"Fe","iron",26,55.845f,QColor(230,25,75)}},
    {"Ga",{"Ga","gallium",31,69.723f,QColor(0,255,0)}},
    {"Gd",{"Gd","gadolinium",64,157.25f,QColor(0,255,149)}},
    {"Ge",{"Ge","germanium",32,72.630f,QColor(0,213,255)}},
    {"H",{"H","hydrogen",1,1.008f,QColor(0,64,255)}},
    {"He",{"He","helium",2,4.0026f,QColor(85,0,255)}},
    {"Hf",{"Hf","hafnium",72,178.49f,QColor(234,0,255)}},
    {"Hg",{"Hg","mercury",80,200.59f,QColor(210,245,60)}},
    {"Ho",{"Ho","holmium",67,164.93f,QColor(255,21,0)}},
    {"I",{"I","iodine",53,126.90f, QColor(255,170,0)}},
    {"In",{"In","indium",49,114.82f,QColor(191,255,0)}},
    {"Ir",{"Ir","iridium",77,192.22f,QColor(42,255,0)}},
    {"K",{"K","potassium",19,39.098f,QColor(0,128,128)}},
    {"Kr",{"Kr","krypton",36,83.798f,QColor(0,255,255)}},
    {"La",{"La","lanthanum",57,138.91f,QColor(0,106,255)}},
    {"Li",{"Li","lithium",3,6.94f,QColor(42,0,255)}},
    {"Lu",{"Lu","lutetium",71,174.97f,QColor(191,0,255)}},
    {"Mg",{"Mg","magnesium",12,24.305f,QColor(255,0,170)}},
    {"Mn",{"Mn","manganese",25,54.938f,QColor(220,190,255)}},
    {"Mo",{"Mo","molybdenum",42,95.95f,QColor(255,128,0)}},
    {"N",{"N","nitrogen",7,14.007f,QColor(234,255,0)}},
    {"Na",{"Na","sodium",11,22.990f,QColor(85,255,0)}},
    {"Nb",{"Nb","niobium",41,92.906f,QColor(0,255,64)}},
    {"Nd",{"Nd","neodymium",60,144.24f,QColor(0,255,213)}},
    {"Ne",{"Ne","neon",10,20.180f,QColor(0,149,255)}},
    {"Ni",{"Ni","nickel",28,58.693f,QColor(170,110,40)}},
    {"O",{"O","oxygen",8,15.999f,QColor(149,0,255)}},
    {"Os",{"Os","osmium",76,190.23f,QColor(255,0,213)}},
    {"P",{"P","phosphorus",15,30.974f,QColor(0,178,255)}},
    {"Pb",{"Pb","lead",82,207.2f,QColor(128,0,0)}},
    {"Pd",{"Pd","palladium",46,106.42f,QColor(255,234,0)}},
    {"Pm",{"Pm","promethium",61,0,QColor(128,255,0)}},
    {"Pr",{"Pr","praseodymium",59,140.91f,QColor(0,255,21)}},
    {"Pt",{"Pt","platinum",78,195.08f,QColor(0,255,170)}},
    {"Rb",{"Rb","rubidium",37,85.468f,QColor(0,191,255)}},
    {"Re",{"Re","rhenium",75,186.21f,QColor(0,42,255)}},
    {"Rh",{"Rh","rhodium",45,102.91f,QColor(106,0,255)}},
    {"Ru",{"Ru","ruthenium",44,101.07f,QColor(255,0,255)}},
    {"S",{"S","sulfur",16,32.06f,QColor(255,0,106)}},
    {"Sb",{"Sb","antimony",51,121.76f,QColor(170,255,195)}},
    {"Sc",{"Sc","scandium",21,44.956f,QColor(255,135,0)}},
    {"Se",{"Se","selenium",34,78.971f,QColor(128,128,0)}},
    {"Si",{"Si","silicon",14,28.085f,QColor(21,255,0)}},
    {"Sm",{"Sm","samarium",62,150.36f,QColor(0,255,128)}},
    {"Sn",{"Sn","tin",50,118.71f,QColor(0,0,128)}},
    {"Sr",{"Sr","strontium",38,87.62f,QColor(0,85,255)}},
    {"Ta",{"Ta","tantalum",73,180.95f,QColor(64,0,255)}},
    {"Tb",{"Tb","terbium",65,158.93f,QColor(213,0,255)}},
    {"Tc",{"Tc","technetium",43,0.0f,QColor(255,0,149)}},
    {"Te",{"Te","tellurium",52,127.60f,QColor(255,0,0)}},
    {"Th",{"Th","thorium",90,232.04f,QColor(255,110,0)}},
    {"Ti",{"Ti","titanium",22,47.867f,QColor(255,215,180)}},
    {"Tl",{"Tl","thallium",81,204.38f,QColor(130,0,255)}},
    {"Tm",{"Tm","thulium",69,168.93f,QColor(64,255,0)}},
    {"V",{"V","vanadium",23,50.942f,QColor(0,255,85)}},
    {"W",{"W","tungsten",74,183.84f,QColor(0,255,234)}},
    {"Xe",{"Xe","xenon",54,131.29f,QColor(0,128,255)}},
    {"Y",{"Y","yttrium",39,88.906f,QColor(21,0,255)}},
    {"Yb",{"Yb","ytterbium",70,173.05f,QColor(170,0,255)}},
    {"Zn",{"Zn","zinc",30,65.38f,QColor(60,180,75)}},
    {"Zr",{"Zr","zirconium",40,91.224f,QColor(155,0,255)}}
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
  const std::vector<bool> VEC_MHD_PARAMETERS={true, true, true, true, true};

  const bool MHD_DISTANCE_NORMALIZATION_DEFAULT=false;
  const bool MHD_POSITION_NORMALIZATION_DEFAULT=false;

  const int PROBE_DEFAULT=_layer_map_ns::PROBE_DEFAULT;
  const int PALETTE_DEFAULT=3;
  const bool TRIANGULATION_ADD_CORNERS_DEFAULT=false;

  // palettes
  const _common_ns::_zero_color ZERO_COLOR_DEFAULT=_common_ns::_zero_color::ZERO_COLOR_BLACK;

  // const float MOUSE_SCALING_FACTOR=1.05;

  const int NUM_TESTS=10;

  enum class _mode_chart:unsigned char {MODE_CHART_VALID,MODE_CHART_INVALID,MODE_CHART_ALL};
}

// class _window_main;

class _window_xmapslab : public QMainWindow
{
    Q_OBJECT

public:
    //
    // _window_main *Window_main=nullptr;

  // the widget that renders OpenGL
  _gl_widget_xmapslab *GL_widget=nullptr;

#ifdef NODE_EDITOR_ACTIVE
  _gl_widget_xmapslab_ge *GL_widget_ge=nullptr;
#endif

#ifdef MODE_3D_ACTIVE
  _gl_widget_xmapslab_3D *GL_widget_3D=nullptr;
#endif

  // the widget for the color bar
  _w_color_bar *Color_bar_widget=nullptr;

  // the widget for the tabs
  _w_tab_xmapslab *Tab_widget=nullptr;

  //
  QWidget *Mapping_widget=nullptr;

  // Is this for node editor ?
  _nodes_editor_maps_tab *Mapping_nodes_editor_maps_tab=nullptr;

  // the widgets for the node editor
#ifdef NODE_EDITOR_ACTIVE
  _filters_tab *Mapping_filters_tab=nullptr;
#endif

  // map a name with the layer data
  std::map<std::string,_measurement_data_ns::_layer_data> Map_name_to_layer;

  // map a name with the corresponding normalized input image
  // (check for saving space: do the normalization when needed) ???
  std::map<std::string,std::vector<shared_ptr<cv::Mat>>> Map_normalized_images;

  // vector with the names of the ordered layers
  std::vector<std::string> Vec_order_of_layers_by_name;

  // maps the type to a map of measurement_data
  // std::map<std::string, std::map<std::string,_measurement_data_ns::_measurement_data>> Map_type_to_map_to_measurement_data;

  // maps the name of an element with its data
#ifdef XRD_ACTIVE
  std::map<std::string,_measurement_data_ns::_measurement_data> Map_name_to_compound;
#endif

  // vector with the names of the compounds
#ifdef XRD_ACTIVE
  std::vector<std::string> Vec_compound_names;
#endif

  std::vector<_palette_data_ns::_palette_data> Vec_palette_data;

  // map the name of a layer with the name of an element
  // for example Fe_cp_1 -> Fe
  std::map<std::string,std::pair<std::string, std::string>> Map_name_of_layer_to_name_of_element;

  int Initial_width;
  int Initial_height;

  int Statistics_x=-1;
  int Statistics_y=-1;

  _window_xmapslab_ns::_mode_chart Mode_chart=_window_xmapslab_ns::_mode_chart::MODE_CHART_ALL;

  // positions
  _vertex2i ZOI={_vertex2i(0,0)};
  std::vector<float> Vec_scaling={1,1};

  // vector with the active positions
  std::vector<bool> Vec_active_positions;
  int Num_active_positions;

  // for the images ?
  std::vector<std::string> *Vec_order_mapping=nullptr;

  // for the fixed palettes
  std::map<std::string,std::vector<_vertex3f>> Map_fixed_palettes;

  // nodes
#ifdef NODE_EDITOR_ACTIVE
  map<std::string,_nodes_editor_ns::_block> *Map_data_blocks=nullptr;
  map<std::string,map<std::string,std::string>> *Map_filters_parameters=nullptr;

  map<std::string,shared_ptr<_filter>> Map_filters;
  map<std::string,_palette_data_ns::_palette_data> Map_filters_palette_data;

  // output images
  map<std::string,shared_ptr<cv::Mat>> Map_mapping_data;
  map<std::string,shared_ptr<cv::Mat>> Map_mapping_images;
  // Pipeline (maintains the order of Map_filters)
  std::vector<shared_ptr<_filter>> Mapping_pipeline;
  map<std::string,std::vector<std::string>> Map_graph;
#endif

  // bug
  int Num_days;

  _window_xmapslab();
  ~_window_xmapslab(){};

//  int ui_font_size(){return UI_font_size;}
//  void ui_font_size(int Size);
//  void pass_ui_font_size(int UI_font_size1);


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

  void remove_element_layer(int Row);
  void remove_element_layer();
  void remove_all_pigment_layers();
  void clear_lab();

  void remove_layer(int Row);
  void remove_all_layers();
//  void recompute_all_layers();

  void update_order_images(std::string Name);
  void show_layer_parameters(int Row,int Col);

  void add_layer_image(std::string Name1,shared_ptr<cv::Mat> Image1);
  void add_layer_color_masks_image(std::string Name1,shared_ptr<cv::Mat> Image1);
  void add_layer_filter(_layer_xmapslab_ns::_subtype Subtype);

  void add_layer_map_minimum_hypercube_distance(std::string Name_image1, std::string Type1, std::string Element1, std::string View_name1, _common_ns::_color_model Color_model1, std::vector<bool> MHD_parameters1, bool MHD_distance_normalization1, bool MHD_position_normalization1, int Probe1, _palette_data_ns::_palette Palette1, _palette_data_ns::_data_type_print Data_type_print1, _common_ns::_zero_color Zero_color1);

  void add_layer_map_rbf_interpolation(std::string Name_image1, std::string Type1, std::string Element1, std::string View_name1, _common_ns::_color_model Color_model1, _palette_data_ns::_palette Palette1, _palette_data_ns::_data_type_print Data_type_print1, _common_ns::_zero_color Zero_color1);

  void add_layer_map_triangulation(std::string Name_image1, std::string Type1, std::string Element1, std::string View_name1, _common_ns::_color_model Color_model1, _palette_data_ns::_palette Palette1, bool Triangulation_add_corners1, _palette_data_ns::_data_type_print Data_type_print1, _common_ns::_zero_color Zero_color1);

  void add_layer_map_lab(std::string Name_image1, std::shared_ptr<cv::Mat> Image1, _palette_data_ns::_palette Palette1, _palette_data_ns::_data_type_print Data_type_print1, float Max_value, _common_ns::_zero_color Zero_color1);

  void add_layer_map_mhd_segmentation(std::string Name_image1, std::string Type1, std::string Element1, std::string View_name1, _common_ns::_color_model Color_model1, std::vector<bool> MHD_parameters1, bool MHD_distance_normalization1, bool MHD_position_normalization1, int Probe1, _palette_data_ns::_palette Palette1, _palette_data_ns::_data_type_print Data_type_print1, _common_ns::_zero_color Zero_color1);

  void add_layer_map_value_segmentation(string Name_image1, std::string Type1, std::string Element1, std::string View_name1, _common_ns::_color_model Color_model1, _layer_map_ns::_map_interpolation_methods Interpolation_type, _palette_data_ns::_palette Palette1, _palette_data_ns::_data_type_print Data_type_print1, _common_ns::_zero_color Zero_color1);


#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
  void add_layer_compound_from_elements(std::string Name_image1, std::string Name_pigment1, std::string View_name1, std::vector<_data_xrf_ns::_data_element_num_atoms> Vec_elements1, std::vector<std::string> Vec_names_in_map1, std::vector<float> Vec_global_percentages1, _palette_data_ns::_palette Palette1, _palette_data_ns::_data_type_print Data_type_print1, _common_ns::_zero_color Zero_color1);
#endif


  void update_layer(std::string Name);
  void update_layer(int Pos);

  void update_color_bar();
  void update_color_bar_data_type_print(int Type1);

  // auxiliar function to get the correct width and heigh (divisible by 4)
  void adjust_image_sizes(int &Width1, int &Height1);

  bool show_positions(){return Show_positions;}
  _layer_map_triangulation_ns::_triangulation_mode show_triangulation(){return Triangulation_mode;}

#ifdef STATISTIC_GRAPHS_ACTIVE
  void create_chart_bar(float Maximum_value,std::vector<float> &Values, std::vector<QColor> &Colors, std::vector<std::string> &Vec_element_names_aux);
  void create_chart_line(float Maximum_value,std::vector<float> &Values, std::vector<QColor> &Colors, std::vector<std::string> &Vec_element_names_aux);
  void create_chart_pie(std::vector<float> &Values, std::vector<QColor> &Colors, std::vector<std::string> &Vec_element_names_aux);

  void update_chart(_window_xmapslab_ns::_mode_chart Mode_chart, int Pos_x,int Pos_y);

  void create_chart_bar_histogram(std::vector<int> &Values, std::vector<QColor> &Colors);
  void update_histogram();
  void compute_histogram_colors();
#endif

  void adjust_by_atomic_number(bool Adjust_by_atomic_number1){Adjust_by_atomic_number=Adjust_by_atomic_number1;}
  bool adjust_by_atomic_number(){return Adjust_by_atomic_number;}

  void adjust_by_atomic_weight(bool Adjust_by_atomic_weight1){Adjust_by_atomic_weight=Adjust_by_atomic_weight1;}
  bool adjust_by_atomic_weight(){return Adjust_by_atomic_weight;}

  int elements_computed(){return Num_elements_computed;}

  void reverse_col(int Col);

  bool loaded_image(){return Loaded_image;}

  void set_save_single_layer_enable(bool Value){Submenu_save_single_layer->setEnabled(Value);}
  void set_save_all_layers_enable(bool Value){Submenu_save_all_layers->setEnabled(Value);}

  // positions
  void draw_positions(QPainter &Painter, float Widht1, float Height1);
  void save_positions_image(string Layer);

  // to select the image that is used for the interpolation in MHD
  void selected_image(string Image_name);
  int mapping_selected_image_index(){return Mapping_selected_image_index;}

  std::string mapping_selected_image_name(){return Mapping_selected_image_name;}

  void save_image_section(std::string File_name, std::string Name, float Value, bool Add_original_image, bool Add_colorbar);

  // nodes
#ifdef NODE_EDITOR_ACTIVE
  void create_nodes_editor_widget();
  void create_mapping();
  void new_effect_slot();

  void add_filter(int Filter_pos,std::string Element,float Col,float Row);

  void create_filters_from_blocks();
  void create_filters_from_blocks(map<std::string,_nodes_editor_ns::_block> *Map_data_blocks1, std::vector<std::string> *Vec_order_mapping1, map<std::string, map<std::string, std::string> > *Map_filters_parameters1);

  void update_all_filters();

  void update_mapping_nodes_editor_maps_tab();
  void update_mapping_filters_tab();

  void selected_filter(std::string Filter_name);

  int mapping_selected_filter_index(){return Mapping_selected_filter_index;}
  std::string mapping_selected_filter_name(){return Mapping_selected_filter_name;}

  void update_filter_aux(std::string Name);
  void update_filter(std::string Name);

  void update_filters_parameters();
#endif

  // palette data
  QColor compute_color(string Name_element);

  // Delaunay triangulation
  std::vector<_delaunay_triangulator_ns::_triangle> &triangles(){return Triangles;}

  //
  _window_xmapslab_ns::_state state(){return State;}

  // for checking if there is a open project
  bool check_project();

  // options
  // positions display
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

  // for selection
  // QColor display_selection_out_circle_color(){}; // not used here
  // QColor display_selection_in_circle_color(){}; // not used here

  // positions print
  void print_font_factor(float Positions_print_font_factor1){Print_font_factor=Positions_print_font_factor1;}
  float print_font_factor(){return Print_font_factor;}


  // layers
  void data_type_print(_palette_data_ns::_data_type_print Data_type_print1){Data_type_print=Data_type_print1;}
  _palette_data_ns::_data_type_print data_type_print(){return Data_type_print;}

  // elements*********
  // view name
  void view_name(std::string View_name1){View_name=View_name1;}
  std::string view_name(){return View_name;}

  // interpolation method
  void map_interpolation_type(_layer_map_ns::_map_interpolation_methods Interpolation_type1){Interpolation_type=Interpolation_type1;}
  _layer_map_ns::_map_interpolation_methods map_interpolation_type(){return Interpolation_type;}

  void color_model(_common_ns::_color_model Color_model1){Color_model=Color_model1;}
  _common_ns::_color_model color_model(){return Color_model;}

  // parameters for MHD function
  void mhd_parameter(int Pos,bool Value);
  bool mhd_parameter(int Pos);

  void mhd_distance_normalization(bool MHD_distance_normalization1){MHD_distance_normalization=MHD_distance_normalization1;}
  bool mhd_distance_normalization(){return MHD_distance_normalization;}

  void mhd_position_normalization(bool MHD_position_normalization1){MHD_position_normalization=MHD_position_normalization1;}
  bool mhd_position_normalization(){return MHD_position_normalization;}

  void palette(_palette_data_ns::_palette Palette1){Palette=Palette1;}
  _palette_data_ns::_palette palette(){return Palette;}

  void probe(int Probe1){Probe=Probe1;}
  int probe(){return Probe;}

  void triangulation_add_corners(bool Triangulation_add_corners1){Triangulation_add_corners=Triangulation_add_corners1;}
  bool triangulation_add_corners(){return Triangulation_add_corners;}

  void rbf_radius(float Radius1){RBF_radius=Radius1;}
  float rbf_radius(){return RBF_radius;}

  void rbf_function(_new_rbf_interpolation_2d_ns::_function_type RBF_function1){RBF_function=RBF_function1;};
  _new_rbf_interpolation_2d_ns::_function_type rbf_function(){return RBF_function;}

  // palette
  void zero_color(_common_ns::_zero_color Zero_color1){Zero_color=Zero_color1;}
  _common_ns::_zero_color zero_color(){return Zero_color;}

  // update when the parameter have been changed
  void parameters_changed();

  // active positions
  void change_active_position(int Position);
  bool active_position(int Position){return Vec_active_positions[Position];}
  std::vector<bool>& vec_active_positions(){return Vec_active_positions;}

  // for the list of xrf files
  void recompute_data();
  // std::vector<_measurement_data_ns::_file_state_data>& vec_file_state(){return  Vec_file_state;}

    // images
  void name_selected_image(std::string Name_selected_image1){Name_selected_image=Name_selected_image1;}
  std::string name_selected_image(){return Name_selected_image;}

  // elements
  void selected_names(std::vector<std::string> Vec_elements_selected_names1){Vec_elements_selected_names=Vec_elements_selected_names1;}
  std::vector<std::string> selected_names(){return Vec_elements_selected_names;}

  void create_map(std::string Type1, std::string Element1);
  void create_some_maps();
  void create_all_maps();

  // compounds from combinations
#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
  void compounds_from_elements_selected_names(std::vector<std::string> Vec_compounds_from_elements_selected_names1){Vec_compounds_from_elements_selected_names=Vec_compounds_from_elements_selected_names1;}
  void compounds_from_elements_create_some_maps();
  void compounds_from_elements_create_all_maps();
#endif

  //
  void selected_layer(int Selected_layer1){Selected_layer=Selected_layer1;}
  int selected_layer(){return Selected_layer;}

  void selected_palette(int Selected_palette1){Selected_palette=Selected_palette1;}
  int selected_palette(){return Selected_palette;}

  void selected_tab(_w_tab_xmapslab_ns::_tabs Selected_tab1){Selected_tab=Selected_tab1;}
  _w_tab_xmapslab_ns::_tabs selected_tab(){return Selected_tab;}

  //
  int initial_width(){return Initial_width;}
  int initial_height(){return Initial_height;}
  float image_diagonal_size(){
    return sqrtf(float(Initial_width*Initial_width+Initial_height*Initial_height));
  }

  //
  int num_valid_positions(){return Num_active_positions;}
  //
  float mean_distance_between_positions(){return Mean_distance_between_positions;}
  float mean_distance_between_neighbors_positions(){return Mean_distance_between_neighbors_positions;}

  //
  int selected_row(){return Selected_row;}
  int selected_col(){return Selected_col;}

  //
  void project_dir(QString Project_dir1){Project_dir=Project_dir1;}

  // image layer name
  std::string image_layer_name(){return Image_layer_name;}

#ifdef NODE_EDITOR_ACTIVE
  void lab_palette(_palette_data_ns::_palette Palette1){LAB_palette=Palette1;}
  _palette_data_ns::_palette lab_palette(){return LAB_palette;}
#endif

  std::vector<float> adjust_coordinates(std::vector<float> &Vec_coordinates1, float Max_value,bool Inversion=false);
  std::vector<std::string> get_tokens(const std::string& String, char Separator);


public slots:
  void load_project_slot();
  void close_project_slot();
  void save_single_layer_slot();
  void save_single_layer_with_color_bar_slot();
  void save_all_layers_slot();
  void save_all_layers_with_color_bar_slot();
//  void save_positions_image_slot();
  void save_composed_image_slot();
  void save_image_section_slot();

  void options_slot();
#ifndef UNIFIED
  void info_slot();
#endif
  void left_handle_slot();
  void right_handle_slot();

  void show_positions_slot();
  void show_position_numbers_slot();
  void show_triangulation_normal_slot();
  void show_triangulation_with_corners_slot();
  void activate_image_section_slot();

  void normal_slot();

#ifdef STATISTIC_GRAPHS_ACTIVE
  void chart_bar_slot();
  void chart_line_slot();
  void chart_pie_slot();
  void histogram_slot();
  void linear_adjust_slot();
  void logarithmic_adjust_slot();
#endif

  //mapping
#ifdef NODE_EDITOR_ACTIVE
  void save_ge_image_slot();

  void laboratory_slot();
  void tab_ge_clicked_slot(int Index1);
#endif

  void use_spot_size_slot();

  // View 3D
#ifdef MODE_3D_ACTIVE
    void view3D_slot();
#endif

  // splitter
  void splitter_moved_slot(int Pos,int Index);

protected:
//  void closeEvent(QCloseEvent *Event) override;

  //
  void save_single_layer(std::string Folder, std::string Name);
  void save_single_layer_with_color_bar(std::string Folder, std::string Name,float Value);

  void save_all_layers();
  void save_all_layers_with_color_bar();

  // images
  void load_images();

  // masks
  void load_color_masks_image();
  void load_masks_ids_image();


  void process_map_data();
  void load_data_csv_format();

#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
  void load_compounds_combination();
#endif

  void add_layer_positions_image();

  void create_filter_list();

  void load_project();

  // void process_data(_measurement_data_ns::_measurement_data &Element_data,float Divisor);

  // auxilar functions for RBF
  void compute_mean_distance_between_positions();
  void compute_mean_distance_between_neighbors_positions();

  // for spot size computations
  void adjust_image_start(std::shared_ptr<cv::Mat> Normalized_image, std::shared_ptr<cv::Mat> Alpha, float Spot_size1, float Width_cm1, float Height_cm1);
  void adjust_image_end(std::shared_ptr<cv::Mat> Float_image, std::shared_ptr<cv::Mat> RGBA_image, std::shared_ptr<cv::Mat> Alpha, int Width1, int Height1);
  void adjust_image_masks_start(std::shared_ptr<cv::Mat> Masks_image, float Spot_size1, float Width_cm1, float Height_cm1);
  //
  QWizardPage* createIntroPage();


  std::vector<std::string> split(const std::string& s, char delimiter);

  //
  int Screen_width=0;
  int Screen_height=0;

  //
  int UI_font_size=_common_ns::UI_FONT_SIZE_DEFAULT;

  // window parameters
  QSize Window_size=QSize(_common_ns::WINDOW_WIDTH_DEFAULT,_common_ns::WINDOW_HEIGHT_DEFAULT);
  QPoint Window_position=QPoint(_common_ns::WINDOW_X_POS_DEFAULT,_common_ns::WINDOW_Y_POS_DEFAULT);

  bool Loaded_image=false;
  int Num_images=0;
  std::string Initial_image;

  QMenu* Menu_view=nullptr;
  QMenu* Submenu_save_single_layer=nullptr;
  QMenu* Submenu_save_all_layers=nullptr;
  QMenu* Submenu_add_show_triangulation=nullptr;

  QAction *Load_project=nullptr;
#ifndef UNIFIED
  QAction *Close_project=nullptr;
#endif
  QAction *Save_single_layer=nullptr;
  QAction *Save_single_layer_with_color_bar=nullptr;
  QAction *Save_all_layers=nullptr;
  QAction *Save_all_layers_with_color_bar=nullptr;
#ifdef NODE_EDITOR_ACTIVE
  QAction *Save_ge_image=nullptr;
#endif
  QAction *Save_positions_image=nullptr;
  QAction *Save_composed_image=nullptr;
  QAction *Save_image_section=nullptr;
  QAction *Options=nullptr;

  std::vector<QAction *> View;
  // QAction *Action_save_positions=nullptr;
  QAction *Action_show_positions=nullptr;
  QAction *Action_show_position_numbers=nullptr;
  QAction *Action_show_triangulation_normal=nullptr;
  QAction *Action_show_triangulation_with_corners=nullptr;
  QAction *Action_activate_image_section=nullptr;

  QAction *Action_use_spot_size=nullptr;

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
  bool Show_position_numbers=false;
  _layer_map_triangulation_ns::_triangulation_mode Triangulation_mode=_layer_map_triangulation_ns::_triangulation_mode::TRIANGULATION_MODE_NONE;
  bool Activate_image_section=false;
  bool Activate_image_section_first_time=true;

  bool Use_spot_size=false;

  int Selected_view;

  bool Adjust_by_atomic_number=false;
  bool Adjust_by_atomic_weight=false;

  int Num_elements_computed=0;

  // positions
  int Insert_position=0;

  // for the images
  int Mapping_selected_image_index=0;
  std::string Mapping_selected_image_name;

#ifdef STATISTIC_GRAPHS_ACTIVE
  QChartView *Chart_view=nullptr;

  bool Linear_adjust=true;
  QAction *View_linear_adjust=nullptr;
  QAction *View_log_adjust=nullptr;

  _window_xmapslab_ns::_chart_mode Chart_mode;
  std::vector<QColor> Histogram_colors;
#endif

#ifdef NODE_EDITOR_ACTIVE
  QSplitter *Splitter_node_editor=nullptr;
  QTabWidget *Tab_widget_ge=nullptr;
  QTabWidget *Tab_widget_mapping_visualization=nullptr;

  _tree_widget *Filters_list=nullptr;
  _nodes_editor *Nodes_editor=nullptr;

  _graphics_view *Graphics_view=nullptr;
  _graphics_scene *Scene=nullptr;

  _filter_ns::_filter_parameters Filter_parameters;
  int Mapping_selected_filter_index=0;
  std::string Mapping_selected_filter_name;
  bool Created_filter_list=false;
#endif

  // the boolean tells us if it is the first time that a project is loaded
  // For the second time, some elements have not to be created again as the widgets
  bool First_load=true;

  //
  std::vector<_measurement_data_ns::_interpreted_data> Vec_data;

  std::vector<int> Match_errors;

  int Selected_row=0;
  int Selected_col=1;

  //*** options
  _w_options_xmapslab *W_options=nullptr;

  // display
  int Display_font_size=_w_options_xmapslab_ns::DISPLAY_FONT_SIZE_DEFAULT;
  int Display_out_circle_size=_w_options_xmapslab_ns::DISPLAY_OUT_CIRCLE_SIZE_DEFAULT;
  QColor Display_font_color=_w_options_xmapslab_ns::DISPLAY_FONT_COLOR_DEFAULT;
  QColor Display_out_circle_color=_w_options_xmapslab_ns::DISPLAY_OUT_CIRCLE_COLOR_DEFAULT;
  QColor Display_in_circle_color=_w_options_xmapslab_ns::DISPLAY_IN_CIRCLE_COLOR_DEFAULT;
  QColor Display_selection_out_circle_color=_w_options_xmapslab_ns::DISPLAY_SELECTION_OUT_CIRCLE_COLOR_DEFAULT;
  QColor Display_selection_in_circle_color=_w_options_xmapslab_ns::DISPLAY_SELECTION_IN_CIRCLE_COLOR_DEFAULT;

  // positions print
  float Print_font_factor=_w_options_xmapslab_ns::PRINT_FONT_FACTOR_DEFAULT;

  // layers
  _palette_data_ns::_data_type_print Data_type_print;

  // selected image
  std::string Name_selected_image;

  // elements
  std::string View_name=_w_tab_xmapslab_ns::VIEW_NAME_DEFAULT.toStdString();
  _layer_map_ns::_map_interpolation_methods Interpolation_type=_layer_map_ns::MAP_INTERPOLATION_TYPE_DEFAULT;
  _common_ns::_color_model Color_model;
  std::vector<bool> MHD_parameters={true,true,true,true,true};
  _palette_data_ns::_palette Palette;
  bool MHD_distance_normalization;
  bool MHD_position_normalization;
  int Probe;
  float RBF_radius;
  _new_rbf_interpolation_2d_ns::_function_type RBF_function=_new_rbf_interpolation_2d_ns::FUNCTION_TYPE_DEFAULT;
  std::vector<std::string> Vec_elements_selected_names;
  bool Triangulation_add_corners;

  // palette
  _common_ns::_zero_color Zero_color;

#ifdef NODE_EDITOR_ACTIVE
  _palette_data_ns::_palette LAB_palette;
#endif

  // 3D
#ifdef MODE_3D_ACTIVE
  bool Show_view3D=false;
  QTabWidget *Tab_widget_view3D=nullptr;
#endif

  // triangulation
  std::vector<_delaunay_triangulator_ns::_triangle> Triangles;
  std::vector<_delaunay_triangulator_ns::_triangle> Triangles_with_corners;

  // element history
//  std::map<std::string,_measurement_data_ns::_history_data> Element_history;

  // state
  _window_xmapslab_ns::_state State=_window_xmapslab_ns::_state::STATE_NORMAL;

  // sizes for chart and image widgets
  bool Size_adjusted=false;
  int Size_chart=-1;

  // xrf files
  // std::vector<_measurement_data_ns::_file_state_data> Vec_file_state;
  // int Selected_file;
  //
  int Selected_layer=-1;
  int Selected_palette=0;

  _w_tab_xmapslab_ns::_tabs Selected_tab=_w_tab_xmapslab_ns::_tabs::POSITIONS_TAB;

  //
  bool Data_loaded=false;

  // class for data of a project project
  _project_data_ns::_project_data Project_data;

  // std::vector<_data_xrf_ns::_data_xrf_pdb> Vec_xrf_pdb_data;
  // std::vector<std::string> Vec_xrf_pdb_names;


  // mean distance between positions
  float Mean_distance_between_positions=1;
  float Mean_distance_between_neighbors_positions=1;

  // ONLY ONE ORIGINAL IMAGE
  shared_ptr<cv::Mat> Original_image=nullptr;

  // the image with the IDs of the masks
  shared_ptr<cv::Mat> Masks_ids_image=nullptr;
  bool Masks_ids_image_loaded=false;

  // compound_combination
#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
  std::vector<std::string> Vec_compounds_from_elements_selected_names;

  std::vector<_data_xrf_ns::_data_compound_from_elements_pdb> Vec_compounds_from_elements_pdb;
#endif

  std::string Image_layer_name;
};

#endif
