#ifndef DATA_XRF_H
#define DATA_XRF_H

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <QColor>

#include <QString>

//#include "vertex.h"

namespace _data_xrf_ns
{
  const int XRF_BGR_ERROR_DEFAULT=25; // 25% of signal

  // factor to reduce elements with small intensities
  const int XRF_THRESHOLD_PERCENTAGE=1; // percentage

  const unsigned int XRF_MAX_NUM_STEPS_SMOOTH=25;
  const unsigned int XRF_NUM_STEPS_SMOOTH=5;

  const unsigned int XRF_MAX_NUM_STEPS_SUBTRACT_BACKGROUND=25;
  const unsigned int XRF_NUM_STEPS_SUBTRACT_BACKGROUND=4;

  const unsigned int MAX_NUM_STEPS_SEARCH_WINDOW_XRF=30;
  const unsigned int NUM_STEPS_SEARCH_WINDOW_XRF=10;

  const float XRF_START_KEV=3.0f;

  enum class _xrf_scale_type:unsigned char{XRF_SCALE_TYPE_LINEAR,XRF_SCALE_TYPE_LOGARITHMIC};
  const _xrf_scale_type XRF_CHART_SCALE_DEFAULT=_xrf_scale_type::XRF_SCALE_TYPE_LINEAR;

  // additional space for the charts
  const float XRF_ADDITIONAL_SPACE=1.15f; // 15%

  const bool XRF_SHOW_GRAPH_OBS=false;
  const bool XRF_SHOW_GRAPH_PROCESSED=true;
  const bool XRF_SHOW_GRAPH_PROCESSED_SHIFTED=true;
  const bool XRF_SHOW_GRAPH_GAUSSIANS=false;

  enum class _smooth_type:unsigned char{SMOOTH_TYPE_MEAN,SMOOTH_TYPE_GS};
  const _smooth_type SMOOTH_TYPE=_smooth_type::SMOOTH_TYPE_GS;

  // Gaussians
  const float XRF_GAUSSIANS_SIGMA=9;// 0.015 Elin in Artax files of Duetto 1
  const int XRF_GAUSSIANS_SIGMAS_TO_COVER=5;

  const unsigned int XRF_MAX_NUM_PEAKS=10;

  const QColor XRF_COLOR_OBS_RAW=QColor(Qt::black);
  const QColor XRF_COLOR_OBS_PROCESSED=QColor(Qt::blue);
  const QColor XRF_COLOR_OBS_PROCESSED_SHIFTED=QColor(Qt::green);
  const QColor XRF_COLOR_GAUSSIANS=QColor(Qt::red);

  enum class _xrf_data_adjustment:unsigned char{XRF_DATA_ADJUSTMENT_NONE,XRF_DATA_ADJUSTMENT_ATOMIC_NUMBER};
  const _xrf_data_adjustment XRF_DATA_ADJUSTMENT_DEFAULT=_xrf_data_adjustment::XRF_DATA_ADJUSTMENT_NONE;
  const std::vector<QString> Vec_xrf_data_adjustment_name={"NONE","ATOMIC_NUMBER"};

//  enum class _xrf_tube_type:unsigned char{XRF_DATA_ADJUSTMENT_NONE,XRF_DATA_ADJUSTMENT_ATOMIC_NUMBER};


  enum class _k_type:unsigned char{K_TYPE_A,K_TYPE_B};

  struct _data_peak{
    int Pos_left;
    int Pos_top;
    int Pos_right;
    float Value_max;
    float Value_min;
    float Width;
    float Height;
    float Area;
  };

  struct _value_position{
    float Value=0;
    int Position=-1;
    float Position_kev=-1;
  };

  struct _data_element{
    std::string Name;
    _k_type K_type;
  };

  struct _data_maximum{
    float Value=0;
    int Position_vec_data=-1;
    std::vector<_data_element> Vec_elements;
  };

  struct _position_k_type{
    int Position=-1;
    _k_type K_type;
  };

  struct _data_k{
    int Distance_vec_data=-1;
    int Position_in_vec_maximums=-1;
    _k_type K_type;
  };

  struct _data_k_element{
    _data_element Data_element;
    _data_k Data_k;
  };

  struct _data_xrf_selected{
    bool Valid=true;
    unsigned int Position_in_pdb;
    _data_k Data_ka;
    _data_k Data_kb;
  };

  struct _result{
    _result(bool Used1,std::vector<_data_xrf_selected> Vec_selected1):
      Used(Used1),Vec_selected(Vec_selected1){}
    bool Used;
    std::vector<_data_xrf_selected> Vec_selected;
  };

  struct _data_element_weight{
    std::string Short_name;
    std::string Name;
    float Atomical_weight=0;
  };

  struct _data_xrf_ka_kb{
    std::string Name;
    int Position_in_pdb=-1; // the position in Elements data (PDB)
    _value_position Ka;
    _value_position Kb;
    bool Selected=true;
    bool Found=true;
    float Gaussian_area_ka=0;
    std::vector<float> Vec_values_gaussian;
  };

  struct _data_xrf_gaussian{
    std::string Name;
    _value_position Ka;
    _value_position Kb;
    std::vector<float> Vec_values;
    float Area_ka;
  };

  struct _data_xrf_pdb{
    std::string Name;
    float Ka=0;
    float Kb=0;
    float Kb_Ka_ratio=-1;
    std::string Superposition;
  };

  struct _manual_selection{
    bool Manual_selection=false;
    bool Selected=false;
  };

  struct _data_xrf_obs{
    std::string File_name;
    int Position=-1;
    float Step;
    std::vector<float> Vec_values;
    std::vector<float> Vec_processed_values;
    std::vector<float> Vec_processed_shifted_values;
    std::map<std::string,_manual_selection> Map_elements_manually_selected;
    // these are for the results
    float Area=0;
    float Mean=0;
//    float Gaussian_sigma;
    std::vector<_data_xrf_ka_kb> Vec_elements_ka_kb;
    // Composition of Gaussians
    std::vector<float> Vec_values_composition_of_gaussians;

  };

  struct _data_sample{
    float x=-1;
    float y=-1;
    float Value=-1;
  };

  struct _data_pos_value{
    int Position=-1;
    float Value=-1;
  };

  // compounds from elements
  struct _data_element_num_atoms{
    std::string Element_name;
    int Num_atoms;
  };

  struct _data_compound_from_elements_pdb{
    std::string Name;
    std::vector<_data_element_num_atoms> Vec_elements_combination;
  };
};

#endif


