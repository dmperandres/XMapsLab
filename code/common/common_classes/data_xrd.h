#ifndef DATA_XRD_H
#define DATA_XRD_H

#include <string>
#include <vector>
#include <iostream>

#include "vertex.h"

#include <QColor>

//#include "common_interpreter.h"
#include "common.h"

namespace _data_xrd_ns {
  const float XRD_THRESHOLD_GOOD_CORRELATION=85;
  const float XRD_THRESHOLD_MEDIUM_CORRELATION=70;
  const float XRD_THRESHOLD_BAD_CORRELATION=30;

  const unsigned int MAX_NUM_STEPS_SMOOTH_XRD=25;
  const unsigned int NUM_STEPS_SMOOTH_XRD=2;

  const unsigned int XRD_MAX_NUM_STEPS_SUBTRACT_BACKGROUND=25;
  const unsigned int XRD_NUM_STEPS_SUBTRACT_BACKGROUND=1;

  const unsigned int MAX_NUM_STEPS_SHIFT_XRD=12;
  const unsigned int NUM_STEPS_SHIFT_XRD=0;

  enum class _smooth_type:unsigned char{SMOOTH_TYPE_MEAN,SMOOTH_TYPE_GS};
  const _smooth_type SMOOTH_TYPE=_smooth_type::SMOOTH_TYPE_GS;

  enum class _normalization_type:unsigned char{NORMALIZATION_TYPE_MEAN,NORMALIZATION_TYPE_PERCENTAGE};
  const _normalization_type NORMALIZATION_TYPE=_normalization_type::NORMALIZATION_TYPE_PERCENTAGE;
  const float NORMALIZATION_FACTOR=100.0f;

  enum class _computation_type:unsigned char{COMPUTATION_TYPE_SQRT,COMPUTATION_TYPE_NOT_ZERO};
  const _computation_type COMPUTATION_TYPE=_computation_type::COMPUTATION_TYPE_NOT_ZERO;

  const float START_2THETA=20;
  const float END_2THETA=50;
  const float STEPS_2THETA=20;

  const float INTENSITY_THRESHOLD=20.0f;

  const int XRD_GAUSSIAN_WIDTH_DEFAULT=9;
  const int XRD_GAUSSIAN_SD_DEFAULT=5;

  const bool XRD_CHART_TYPE_SPECTRA=true;
  const bool XRD_CHART_TYPE_CORRELATION=false;

  enum class _xrd_scale_type:unsigned char{XRD_SCALE_TYPE_LINEAR,XRD_SCALE_TYPE_LOGARITHMIC};
  const _xrd_scale_type XRD_CHART_SCALE_DEFAULT=_xrd_scale_type::XRD_SCALE_TYPE_LINEAR;

  const bool SHOW_GRAPH_RAW_OBS_XRD=false;
  const bool SHOW_GRAPH_OBS_XRD=true;
  const bool SHOW_GRAPH_OBS_SHIFTED_XRD=true;
  const bool SHOW_GRAPH_PDB_XRD=true;
  const bool SHOW_GRAPH_SQRT_XRD=true;

  enum class _pdb_type:unsigned char{PDB_TYPE_SPECTRAL,PDB_TYPE_PEAKS};
  const std::vector<QString> Vec_type_name={"SPECTRAL","PEAKS"};
  const std::string PDB_type_spectral="SPECTRAL";
  const std::string PDB_type_peaks="PEAKS";

  enum class _tube_type:unsigned char{TUBE_TYPE_CU,TUBE_TYPE_CO};
  const std::vector<QString> Vec_tube_name={"CU","CO"};
  const std::string PDB_tube_type_Co="CO";
  const std::string PDB_tube_type_Cu="CU";

  enum class _normalized_type:unsigned char{NORMALIZED_NO,NORMALIZED_YES};
  const std::vector<QString> Vec_normalized_name={"NO","YES"};

  const bool USE_XRD_PDB_SPECTRAL_CU_DEFAULT=true;
  const bool USE_XRD_PDB_SPECTRAL_CO_DEFAULT=false;
  const bool USE_XRD_PDB_ASTM_CU_DEFAULT=false;
  const _tube_type TUBE_TYPE_DEDAULT=_tube_type::TUBE_TYPE_CU;

  const QColor XRD_COLOR_OBS_RAW=QColor(Qt::black);
  const QColor XRD_COLOR_OBS_PROCESSED=QColor(Qt::magenta);
  const QColor XRD_COLOR_OBS_PROCESSED_SHIFTED=QColor(Qt::green);
  const QColor XRD_COLOR_PDB=QColor(Qt::blue);
  const QColor XRD_COLOR_SQRT=QColor(Qt::red);

  const QColor XRD_COLOR_FILE_NOT_EXISTS=QColor(Qt::gray);
  const QColor XRD_COLOR_ELEMENT_NOT_EXISTS=QColor(Qt::red);
  const QColor XRD_COLOR_VALID_GOOD=QColor(Qt::green);
  const QColor XRD_COLOR_VALID_MEDIUM=QColor(Qt::yellow);
  const QColor XRD_COLOR_VALID_BAD=QColor(Qt::magenta);
//  const QColor XRD_COLOR_FONT_DEFAULT=QColor(Qt::black);

//  const bool SHOW_VALID_GOOD_DEFAULT=true;
//  const bool SHOW_VALID_MEDIUM_DEFAULT=true;
//  const bool SHOW_VALID_BAD_DEFAULT=false;

//  const bool SHOW_VALID_DEFAULT=true;
//  const bool SHOW_ELEMENT_NOT_EXISTS_DEFAULT=true;
//  const bool SHOW_FILE_NOT_EXISTS_DEFAULT=true;

  // additional space for the charts
  const float XRF_ADDITIONAL_SPACE=1.15f; // 15%

//  const std::vector<std::string> Vec_tube_type_names={"Cu","Co"};

  enum class _class_type:unsigned char{CLASS_TYPE_NO_XRF_FILE,CLASS_TYPE_NO_ELEMENTS,CLASS_TYPE_VALID};

  enum class _valid_type:unsigned char{VALID_TYPE_GOOD,VALID_TYPE_MEDIUM,VALID_TYPE_BAD};

  enum class _tube_conversion_mode:unsigned char{TUBE_CONVERSION_CU_TO_CO,TUBE_CONVERSION_CO_TO_CU,ACTION_LAST};

  enum class _chart_type:unsigned char{CHART_TYPE_SPECTRAL,CHART_TYPE_CORRELATION};

  const QString SYTLE_FILE_BUTTON_UNSELECTED="text-align: left; padding-left: 3px; padding-right: 3px;";
  const QString SYTLE_FILE_BUTTON_SELECTED="text-align: left; padding-left: 3px; padding-right: 3px;  border-top: 3px solid #0000CC; border-bottom: 3px solid #0000CC;";
  const QString SYTLE_PIGMENT_BUTTON_SELECTED="border-top: 3px solid #0000CC; border-bottom: 3px solid #0000CC;";

#ifdef GC
  struct _data_xrd_pdb{
    std::string File_name;
    //    _pdb_type Type;
    _tube_type Tube;
    //    bool Normalized=false;
    std::vector<std::string> Vec_names;
    std::vector<std::string> Vec_formulas;
    std::vector<std::string> Vec_elements;
    //    _vertex3f Color;
    std::vector<float> Vec_values;
    std::vector<float> Vec_smooth_values;
    std::vector<float> Vec_filtered_values;
    std::vector<float> Vec_normalized_values;
    int Area=0;
    std::vector<_common_ns::_peak_data> Vec_peaks;
  };
#else
  struct _data_xrd_pdb{
    std::string File_name;
    _pdb_type Type;
    _tube_type Tube;
    bool Normalized=false;
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
  };
#endif

  struct _xrd_order_data{
    int Position;
    int Percentage;
    std::string Name;
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
    std::vector<_xrd_order_data> Vec_order;
#ifdef GC
    std::vector<bool> Vec_edition_values;
#endif
  };

  struct _data_xrd_obs_pdb{
    float Slope=0;
    float Intercept=0;
    float Correlation_coefficient_squared=0;
    float Shift=0;
    unsigned int Num_peaks=0;
    unsigned int Num_counted_peaks;
    bool XRF_used=false;
    int Pos_data_xrf=-1;    
    _class_type Class_type;
    _valid_type Valid_type;
    bool Show=false;
    std::vector<std::string> Vec_elements_not_found;
    std::vector<float> Vec_sqrt_values;
    std::vector<float> Vec_obs_values_shifted;
  };

  struct _data_maximum{
    int Position_vec_data=-1;
    float Value=0;
  };

  struct _selection{
    bool Hand_selection=false;
    bool Selected=false;
  };

  //  struct _xrd_table_column_parameters{
  //    bool Visibility=false;
  //    unsigned int Position=0;
  //  };
};

#endif

