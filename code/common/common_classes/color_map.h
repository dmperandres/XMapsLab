//LIC

#ifndef COLOR_MAP
#define COLOR_MAP

#include <vector>
#include <string>
#include <QColor>
#include <QMessageBox>
#include <random>

#include "vertex.h"

#include "common.h"

// namespace _color_map_ns {
// // enum class _null_element_color:unsigned char{NULL_ELEMENT_COLOR_WHITE,NULL_ELEMENT_COLOR_BLACK};
// // const _null_element_color NULL_ELEMENT_COLOR_DEFAULT=_null_element_color::NULL_ELEMENT_COLOR_BLACK;

//  const std::vector<QString> Vec_color_names_for_zero_value={"Black","White"};
//  enum class _color_for_zero_value: unsigned char {COLOR_ZERO_VALUE_BLACK,COLOR_ZERO_VALUE_WHITE};

// }


//HEA
// This class computes the colors depending on the proportions. The proportions must be between 0 and 1
// There is the possibility of assign black or white color to the 0 value
// It is possible to use tones (a single color) or colors
// It is more normal to use tones and sections, and colors and interpolation

class _color_map
{
public:

  _color_map(){}

//  _color_map(_color_map &Color_map1);

//  _color_map &operator=(_color_map &Color_map1);
  void color_for_zero_value(_common_ns::_zero_color Zero_color1){Zero_color=Zero_color1;}

  void compute_regular_values(int Num_values1);
  void compute_tones_sections(QColor Color1);
  void compute_tones_interpolations(QColor Color1);
  void compute_colors_sections(QColor Color1);
  void compute_colors_interpolations(QColor Color1);
  void compute_colors_sections_fixed_palette(std::vector<_vertex3f> Vec_colors_fixed_palette);
  void compute_colors_interpolations_fixed_palette(std::vector<_vertex3f> Vec_colors_fixed_palette);

  void compute_tones_sections(int Num_values,std::vector<QColor> &Vec_colors1,QColor Color1);
  void compute_tones_interpolations(int Num_values,std::vector<QColor> &Vec_colors1,QColor Color1);
  void compute_colors_sections(int Num_values,std::vector<QColor> &Vec_colors1,QColor Color1);
  void compute_colors_interpolations(int Num_values,std::vector<QColor> &Vec_colors1,QColor Color1);
  void compute_colors_sections_fixed_palette(int Num_values, std::vector<QColor> &Vec_colors1, std::vector<_vertex3f> Vec_colors_fixed_palette);
  void compute_colors_interpolations_fixed_palette(int Num_values,std::vector<QColor> &Vec_colors1,std::vector<_vertex3f> Vec_colors_fixed_palette);

  std::vector<float> Vec_values;
  std::vector<QColor> Vec_colors;

private:
  QColor Color=QColor(0,0,0);
  int Num_values;
  _common_ns::_zero_color Zero_color;
};

#endif


