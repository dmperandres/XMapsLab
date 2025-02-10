//LIC

#ifndef PALETTE_DATA_H
#define PALETTE_DATA_H

#include <QString>
#include <QColor>
#include <vector>

#include "common.h"

#include "color_map.h"

namespace _palette_data_ns {
  const std::vector<QString> Vec_names_data_type_print={"Float","Scientific","Integer","Per cent"};
  enum class _data_type_print: unsigned char {DATA_TYPE_PRINT_FLOAT,DATA_TYPE_PRINT_SCIENTIFIC,DATA_TYPE_PRINT_INT,DATA_TYPE_PRINT_PERCENT};


  enum class _palette_type:unsigned char {PALETTE_TYPE_DISCRETE, PALETTE_TYPE_CONTINUOUS};
  const _palette_type PALETTE_TYPE_DEFAULT=_palette_type::PALETTE_TYPE_CONTINUOUS;

  enum class _palette_color_type:unsigned char {PALETTE_COLOR_TYPE_SINGLE_TONE, PALETTE_COLOR_TYPE_COLOR};
  const _palette_color_type PALETTE_COLOR_TYPE_DEFAULT=_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE;

  enum class _palette_color_assigning_type:unsigned char {PALETTE_COLOR_ASSIGNING_FIXED, PALETTE_COLOR_ASSIGNING_RANDOM};
  const _palette_color_assigning_type PALETTE_COLOR_ASSIGNING_DEFAULT=_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_FIXED;

  const int PALETTE_DISCRETE_MINIMUM_INTERVALS=2;
  const int PALETTE_DISCRETE_MAXIMUM_INTERVALS=10;
  const int PALETTE_CONTINUOUS_MINIMUM_INTERVALS=1;
  const int PALETTE_CONTINUOUS_MAXIMUM_INTERVALS=10;

  const QColor FIXED_COLOR=Qt::red;

  struct _palette {
    _palette_type Type;
    _palette_color_type Color_type;
    int Num_stops;
    _palette_color_assigning_type Color_assigning;
    QColor Color;
    std::string Name_fixed_palette;
  };

  //  enum class _data_type: unsigned char {DATA_TYPE_DISCRETE,DATA_TYPE_CONTINUOUS};
  //  enum class _color_type: unsigned char {COLOR_TYPE_TONE,COLOR_TYPE_COLOR};

  struct _palette_data_aux{
    QString Name;
    _palette_type Type;
    _palette_color_type Color_type;
    int Num_stops;
    _palette_color_assigning_type Color_assigning;
  };

  class _palette_data
  {
    public:

    _palette_data(){};

    _palette_data(QString Name1, _palette_data_ns::_palette_type Palette_type1, _palette_data_ns::_palette_color_type Palette_color_type1, int Num_stops1, _palette_color_assigning_type Palette_color_assigning1, QColor Color1, std::vector<_vertex3f> Colors_fixed_palette1, _common_ns::_zero_color Zero_color1);

    _palette_data(const _palette_data &Vec_palette_data1);

    _palette_data &operator=(const _palette_data &Vec_palette_data1);

    void update_values();

    void name(QString Name1){Name=Name1;}
    QString name(){return Name;}

    void type(_palette_data_ns::_palette_type Type1);
    _palette_data_ns::_palette_type type(){return Type;};

    void color_type(_palette_data_ns::_palette_color_type Color_type1);
    _palette_data_ns::_palette_color_type color_type(){return Color_type;}

    void num_stops(int Num_stops1);
    int num_stops(){return Num_stops;}

    void color(QColor Color1);
    QColor color(){return Color;}

    void color_assigning(_palette_color_assigning_type Color_assigning1){Color_assigning=Color_assigning1;}
    _palette_color_assigning_type color_assigning(){return Color_assigning;}

    std::vector<QColor> colors(){return Color_map.Vec_colors;}

    void update();

    std::vector<float> &vec_values(){return Color_map.Vec_values;}
    std::vector<QColor> &vec_colors(){return Color_map.Vec_colors;}

    protected:
    QString Name="";
    _palette_type Type;
    _palette_color_type Color_type; // tone or color
    int Num_stops;
    _palette_color_assigning_type Color_assigning;
    QColor Color;
    std::vector<_vertex3f> Colors_fixed_palette;

    _color_map Color_map;
    _common_ns::_zero_color Zero_color;
  };
}

#endif

