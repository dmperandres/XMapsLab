//LIC

#ifndef MEASUREMENT_DATA_H
#define MEASUREMENT_DATA_H

#include <string>
#include <vector>
#include <iostream>

#include <GL/glew.h>
//#include <opencv.hpp>

#include "common.h"

#include "palette_data.h"

#include "layer_xmapslab.h"
//#include "layer_map.h"
//#include "color_bar_abstract.h"

//#include "project_data.h"

class _color_bar_abstract;

namespace _measurement_data_ns
{
  const float MAX_VALUE=1e20f;
  const std::string Text_file_not_exists="File not exists";

  //HEA

  struct _element_weight_data{
//    _element_weight_data(std::string Short_name1,std::string Name1,float Atomical_weight1):Short_name(Short_name1),Name(Name1),Atomical_weight(Atomical_weight1){}
    std::string Short_name;
    std::string Name;
    float Atomic_number=-1;
    float Atomic_weight=-1;
  };

  //HEA

  class _sample_data{
  public:
    float x=-1;
    float y=-1;
    float Value=-1;

    _sample_data(){}
    _sample_data(float x1,float y1,float Value1):x(x1),y(y1),Value(Value1){}

    _sample_data &operator=(const _sample_data &Data_sample1)
    {
      x=Data_sample1.x;
      y=Data_sample1.y;
      Value=Data_sample1.Value;
      return *this;
    };

  };

  //HEA
  // This class contains the sampled data for single elements, XRF, and compounds, XRD

  class _measurement_data{
  public:
    _common_ns::_xray_data_type Xray_data_type=_common_ns::_xray_data_type::XRAY_DATA_TYPE_XRF;
    std::string Name;
    float Min_value=MAX_VALUE;
    float Max_value=-MAX_VALUE;
    float Atomic_number=-1;
    float Atomic_weight=-1;

    float Max_value_adjusted=-1;
    std::vector<float> Vec_values;

    // _measurement_data(){}
    // _measurement_data(const _measurement_data &Data1);
  };

  //HEA
  // This class contains the information about the coordinates of samples

  class _positions_data{
  public:
    float Width=0;
    float Height=0;
    std::vector<float> Vec_coordinate_x;
    std::vector<float> Vec_coordinate_y;

    int num_positions(){return Vec_coordinate_x.size();}
//    void normalize_positions();
    void adjust_y_coordinates();
  };

  //HEA
  // Basic struct to contain a name and the corresponding value

  struct _pair_name_value{
//    _pair_name_value(std::string Name1,float Value1):Name(Name1),Value(Value1){}
    std::string Name;
    float Value=0;
  };

  class _layer_data{
  public:
    std::shared_ptr<_layer_xmapslab> Layer;
    std::string Pigment_name;
    _color_bar_abstract *Color_bar=nullptr;
    std::shared_ptr<_palette_data_ns::_palette_data> Palette_data;
    GLuint Texture=0;
    std::string Color_bar_name;
    _common_ns::_xray_data_type Xray_data_type;

    _layer_data(){}
    _layer_data(const _layer_data &Layer_data1){
      Layer=Layer_data1.Layer;
      Color_bar=Layer_data1.Color_bar;
      Texture=Layer_data1.Texture;
      Color_bar_name=Layer_data1.Color_bar_name;
    }
    ~_layer_data(){
      glDeleteTextures(1,&Texture);
    }
  };

  struct _interpreted_data{
    std::string Name;
    std::vector<float> Raw_values;
    std::vector<float> Filtered_values;
    std::vector<float> Normalized_values;
  };


  struct _pair_name_vec_values{
    std::string Name;
    std::vector<float> Values;
  };

  //HEA
  // this struct is for knowing what xrf files are actived to do the map computation
  struct _file_state_data{
//    bool Selected=false;
    int Position=-1;
    std::string File_name=Text_file_not_exists;
    std::vector<_pair_name_value> Vec_data_value;
  };

  //HEA
  // This class is for maintaining information of the data that has been interpreted to redo when a file is changed

//  class _history_data{
//  public:
//    std::string Name_layer;
//    std::string Name_element;
//    std::string View_name;
//    int Palette;
//    _layer_map_ns::_interpolation_type Interpolation_type;
////    _layer_map_ns::_interpolation_type Interpolation_type;
//    int Probe;
//    std::vector<bool> Use_colors;
//    std::vector<bool> Use_positions;
//    _common_ns::_color_model Color_model;
//    bool Normalization;

//    _history_data(){} // this is necessary when it is used in an equal. e.g map<string,_history_data> Data["Ba"]=_history_data("dd",..)
//    _history_data(std::string Name_layer1,std::string Name_element1, std::string View_name1,int Palette1,_layer_map_ns::_interpolation_type Interpolation_type1, int Probe1,std::vector<bool> Use_colors1,std::vector<bool> Use_positions1, _common_ns::_color_model Color_model1,bool Normalization1);
//    _history_data(const _history_data &Data1);
//  };


};

#endif


