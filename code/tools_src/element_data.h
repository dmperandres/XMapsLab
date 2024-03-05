/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef ELEMENT_DATA
#define ELEMENT_DATA

#include <string>
#include <vector>
#include <iostream>

namespace _element_data_ns
{
  const std::string Text_file_not_exists="File not exists";

  //HEA

  struct _data_element_weight{
    _data_element_weight(std::string Short_name1,std::string Name1,float Atomical_weight1):Short_name(Short_name1),Name(Name1),Atomical_weight(Atomical_weight1){}
    std::string Short_name;
    std::string Name;
    float Atomical_weight=0;
  };

  //HEA

  class _data_sample{
  public:
    float x=-1;
    float y=-1;
    float Value=-1;

    _data_sample(){}
    _data_sample(float x1,float y1,float Value1):x(x1),y(y1),Value(Value1){}

    _data_sample &operator=(const _data_sample &Data_sample1)
    {
      x=Data_sample1.x;
      y=Data_sample1.y;
      Value=Data_sample1.Value;
      return *this;
    };

  };

  //HEA
  // This class contains the sampled data for single elements, XRF, and compounds, XRD

//  class _element_data{
//  public:
//    _element_data_ns::_data_type Data_type=_element_data_ns::_data_type::DATA_TYPE_XRF;
//    std::string Name;
//    float Min_value=MAX_VALUE;
//    float Max_value=-MAX_VALUE;
//    float Atomic_number=0;
//    float Max_value_adjusted=-1;
//    std::vector<_data_sample> Vec_samples;
////    std::vector<_data_sample> Vec_samples_normalized;

//    _element_data(){}
//    _element_data(const _element_data &Data1);

////    void process();
//  };

  //HEA
  // This class contains the information about the coordinates of samples

//  class _data_positions{
//  public:
//    float Width=0;
//    float Height=0;
//    _units Size_units=_units::UNITS_PX;
//    _cs_origin CS_origin=_cs_origin::CS_ORIGIN_TOP_LEFT;
//    std::vector<int> Vec_coordinate_x;
//    std::vector<int> Vec_coordinate_y;
//    std::vector<bool> Vec_valid_coordinates;
////    std::vector<float> Vec_coordinate_x_normalized;
////    std::vector<float> Vec_coordinate_y_normalized;

//    int num_positions(){return Vec_coordinate_x.size();}
////    void normalize_positions();
//    void adjust_y_coordinates();
//  };

  //HEA
  // Basic struct to contain a name and the corresponding value

  struct _name_value{
    _name_value(std::string Name1,float Value1):Name(Name1),Value(Value1){}
    std::string Name;
    float Value=0;
  };

  struct _name_vec_values{
    std::string Name;
    std::vector<float> Values;
  };
};

#endif

