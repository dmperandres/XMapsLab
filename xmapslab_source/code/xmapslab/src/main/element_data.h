/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

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
    std::string Short_name;
    std::string Name;
    float Atomic_number=-1.0f;
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

