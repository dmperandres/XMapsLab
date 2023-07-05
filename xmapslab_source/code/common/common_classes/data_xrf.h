#ifndef DATA_XRF_H
#define DATA_XRF_H

#include <string>
#include <vector>
#include <iostream>
#include <map>

#include <QString>

//#include "vertex.h"

namespace _data_xrf_ns
{
  const int BGR_ERROR_DEFAULT=25; // 25% of signal
  const int SCAN_WINDOW_SIZE=15;

  // factor to reduce elements with small intensities
  const int THRESHOLD_PERCENTAGE_XRF=5;

  const unsigned int MAX_NUM_STEPS_SMOOTH_XRF=25;
  const unsigned int NUM_STEPS_SMOOTH_XRF=5;

  const unsigned int NUM_STEPS_SUBTRACT_NOISE_XRF=20;

  const float START_KEV=3.0f;

  const bool XRF_CHAR_SCALE_LINEAR=true;
  const bool XRF_CHAR_SCALE_LOG=false;

  // additional space for the charts
  const float ADDITIONAL_SPACE=1.05f; // 5%

  const bool SHOW_GRAPH_OBS_XRF=true;
  const bool SHOW_GRAPH_SMOOTH_XRF=true;
  const bool SHOW_GRAPH_GAUSSIANS_XRF=true;

  enum class _xrf_data_adjustment:unsigned char{XRF_DATA_ADJUSTMENT_NONE,XRF_DATA_ADJUSTMENT_ATOMIC_NUMBER};
  const _xrf_data_adjustment XRF_DATA_ADJUSTMENT_DEFAULT=_xrf_data_adjustment::XRF_DATA_ADJUSTMENT_NONE;
  const std::vector<QString> Vec_xrf_data_adjustment_name={"NONE","ATOMIC_NUMBER"};

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
    std::string Element_name;
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
    unsigned int Element_position_in_pdb;
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
    std::string Element_name;
    int Element_position_in_pdb=-1; // the position in Elements data (PDB)
    _value_position Ka;
    _value_position Kb;
    bool Selected_found=true;
    bool Selected_valid=true;
    bool Selected_orig=true;
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

  struct _data_xrf_obs{
    std::string File_name;
    int Position=-1;
    float Step;
    std::vector<float> Vec_values;
    std::vector<float> Vec_smooth_values;
    std::vector<float> Vec_subtract_noise_values;
    // these are for the results
    float Area;
    float Mean;
    std::vector<_data_xrf_ka_kb> Vec_elements_ka_kb;
    std::vector<_data_xrf_gaussian> Vec_gaussians_data;
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

#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE

  struct _data_element_num_atoms{
    std::string Element_name;
    int Num_atoms;
  };

  struct _data_compound_from_elements_pdb{
    std::string Name;
    std::vector<_data_element_num_atoms> Vec_elements_combination;
  };
#endif

};

#endif


