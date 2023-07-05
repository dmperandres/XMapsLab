#ifndef DATA_XRD_H
#define DATA_XRD_H

#include <string>
#include <vector>
#include <iostream>

#include "vertex.h"

#include <QColor>

//#include "common_interpreter.h"
#include "common.h"

namespace _data_xrd_ns
{
  const float THRESHOLD_XRD_GOOD_CORRELATION=85;
  const float THRESHOLD_XRD_MEDIUM_CORRELATION=70;
  const int HALF_SHIFT_DEFAULT=12; // 20 steps for one 2Theta degree  12

  const unsigned int MAX_NUM_STEPS_SMOOTH_XRD=25;
  const unsigned int NUM_STEPS_SMOOTH_XRD=2;

  const unsigned int MAX_NUM_STEPS_SUBTRACT_MEAN_XRD=25;
  const unsigned int NUM_STEPS_SUBTRACT_MEAN_XRD=1;

  const bool SMOOTH_TYPE_MEAN_XRD=true;
  const bool SMOOTH_TYPE_GS_XRD=false;

  const bool NORMALIZATION_TYPE_MEAN_XRD=true;
  const bool NORMALIZATION_TYPE_UNITY_XRD=false;
  const float NORMALIZATION_FACTOR=100.0f;

  const float START_2THETA=20;
  const float END_2THETA=50;
  const float STEPS_2THETA=20;

  const float INTENSITY_THRESHOLD=20.0f;

  const int XRD_GAUSSIAN_WIDTH_DEFAULT=3;
  const int XRD_GAUSSIAN_SD_DEFAULT=3;

  const bool XRD_CHART_TYPE_SPECTRA=true;
  const bool XRD_CHART_TYPE_CORRELATION=false;

  const bool SHOW_GRAPH_OBS_XRD=true;
  const bool SHOW_GRAPH_OBS_SHIFTED_XRD=true;
  const bool SHOW_GRAPH_PDB_XRD=true;
  const bool SHOW_GRAPH_SQRT_XRD=true;

  enum class _tube_type:unsigned char{TUBE_TYPE_CU,TUBE_TYPE_CO,ACTION_LAST};
  const std::vector<QString> Vec_tube_name={"CU","CO"};

  const bool USE_XRD_PDB_SPECTRAL_CU_DEFAULT=true;
  const bool USE_XRD_PDB_SPECTRAL_CO_DEFAULT=false;
  const bool USE_XRD_PDB_ASTM_CU_DEFAULT=false;
  const _tube_type TUBE_TYPE_DEDAULT=_tube_type::TUBE_TYPE_CU;

  const QColor COLOR_FILE_NOT_EXISTS_DEFAULT=QColor(Qt::gray);
  const QColor COLOR_ELEMENT_NOT_EXISTS_DEFAULT=QColor(Qt::red);
  const QColor COLOR_VALID_GOOD_DEFAULT=QColor(Qt::green);
  const QColor COLOR_VALID_MEDIUM_DEFAULT=QColor(Qt::yellow);
  const QColor COLOR_VALID_BAD_DEFAULT=QColor(Qt::magenta);
  const QColor COLOR_FONT_DEFAULT=QColor(Qt::black);

  const bool SHOW_VALID_GOOD_DEFAULT=true;
  const bool SHOW_VALID_MEDIUM_DEFAULT=false;
  const bool SHOW_VALID_BAD_DEFAULT=false;

  const bool SHOW_VALID_DEFAULT=true;
  const bool SHOW_ELEMENT_NOT_EXISTS_DEFAULT=false;
  const bool SHOW_FILE_NOT_EXISTS_DEFAULT=false;

  const std::vector<std::string> Vec_tube_type_names={"Cu","Co"};


  enum class _tube_conversion_mode:unsigned char{TUBE_CONVERSION_CU_TO_CO,TUBE_CONVERSION_CO_TO_CU,ACTION_LAST};

  enum class _chart_type:unsigned char{CHART_TYPE_SPECTRAL,CHART_TYPE_CORRELATION};

  struct _data_xrd_pdb{
    std::string File_name;
    std::vector<std::string> Vec_names;
    std::vector<std::string> Vec_formulas;
    std::vector<std::string> Vec_elements;
    _vertex3f Color;
    std::vector<float> Vec_values;
    std::vector<float> Vec_smooth_values;
    std::vector<float> Vec_filtered_values;
    std::vector<float> Vec_normalized_values;
    int Area=0;
    std::vector<_common_ns::_peak_data> Vec_peaks;
    bool Do_preprocess=true;
  };

  struct _data_xrd_obs{
    std::string File_name;
    int Position=-1;
    std::vector<float> Vec_values;
    std::vector<float> Vec_smooth_values;
    std::vector<float> Vec_filtered_values;
    std::vector<float> Vec_normalized_values;
    int Area=0;
    std::vector<_common_ns::_peak_data> Vec_peaks;
  };

  struct _data_xrd_obs_pdb{
    float Slope=0;
    float Intercept=0;
    float Correlation_coefficient=0;
    float Shift=0;
    unsigned int Num_peaks=0;
    unsigned int Num_counted_peaks;
    bool XRF_used=false;    
    int Pos_data_xrf=-1;
    bool Show=true;
    std::vector<std::string> Vec_elements_not_found;
    std::vector<float> Vec_sqrt_values;
    std::vector<float> Vec_obs_values_shifted;
  };

  struct _data_maximum{
    int Position_vec_data=-1;
    float Value=0;
  };
};

#endif


