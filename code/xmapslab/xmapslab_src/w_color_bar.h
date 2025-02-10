#ifndef WIDGET_COLOR_BAR
#define WIDGET_COLOR_BAR

#include <QWidget>
#include <QVBoxLayout>

#include <vector>
#include <math.h>

#include "w_tab_xmapslab.h"

#include "measurement_data.h"

#include "color_bar_abstract.h"
#include "color_bar_interpolation.h"
#include "color_bar_sections.h"

#include "layer_map_distance.h"

class _window_xmapslab;

//HEA

class _w_color_bar: public QWidget
{
Q_OBJECT

public:
  std::vector<_color_bar_abstract *> Palettes;

  std::vector<QColor> Colors_mask;
//  std::vector<QColor> Color_element;

  _w_color_bar(_window_xmapslab *Window1);
  ~_w_color_bar();

  QSize sizeHint() const override;
  QSize minimumSizeHint() const override;

  static int total_width(float Value, QFont Font);
  void adjust_width(float Value);

  void initialize();

  void create_palettes();

  void add_palette_layer(std::string Name);

  void add_palette(_color_bar_abstract *Palette_aux);

  void remove_color_bar(std::string Name);

  void update_color_bar(_w_tab_xmapslab_ns::_tabs Selected_tab);

//  void compute_regular_values(int Num_values,std::vector<float> &Vec_values);
  void compute_regular_values_noise(int Num_values,std::vector<float> &Vec_values,float Noise=0.05);

//  void compute_tones_sections(std::vector<float> &Vec_values, std::vector<QColor> &Vec_colors,string Name_element="");
//  void compute_tones_interpolations(std::vector<float> &Vec_values, std::vector<QColor> &Vec_colors,string Name_element="");
//  void compute_colors(std::vector<float> &Vec_values,std::vector<QColor> &Vec_colors,string Name_element="");

//  std::vector<QColor> compute_palette_colors(int Pos_palette, _project_data_ns::_data_type Data_type1, std::string Name_element1);

  _color_bar_abstract *create_color_bar(_palette_data_ns::_palette_data Palette1, std::string Name_element1, float Max_value, std::vector<QColor> &Colors, _palette_data_ns::_data_type_print Data_type_print1, _common_ns::_zero_color Zero_color1);

protected slots:
  void color_bar_changed_slot(std::vector<float> &Vec_values1, std::vector<QColor> &Vec_colors1, int Type);

protected:
  _window_xmapslab *Window=nullptr;

  QWidget *Widget_color_bar_layers=nullptr;
  QVBoxLayout *Verticalbox_color_bar=nullptr;
  QVBoxLayout *Verticalbox_color_bar_layers=nullptr;

  // for using with Palettes tab
  //  QWidget *Widget_color_bar_palettes=nullptr;
  //  QVBoxLayout *Verticalbox_color_bar_palettes=nullptr;

  QLabel *Label_name=nullptr;

  float Hue_offset=0;
};

#endif


