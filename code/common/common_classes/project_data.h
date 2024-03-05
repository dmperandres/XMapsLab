/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef PROJECT_DATA
#define PROJECT_DATA

#include <string>
#include <vector>
#include <iostream>
#include <QString>

#include "data_xrf.h"
#include "data_xrd.h"

namespace _project_data_ns
{
  enum class _cs_origin: unsigned char {CS_ORIGIN_TOP_LEFT,CS_ORIGIN_BOTTOM_LEFT};
  const std::string Vec_names_cs_origin[]={"TOP_LEFT","BOTTOM_LEFT"};

  enum class _data_type: unsigned char {DATA_TYPE_XRF,DATA_TYPE_XRD};

//  enum class _device:unsigned char{DEVICE_DUETTO1,DEVICE_DUETTO2,DEVICE_TRACER};
//  const std::vector<QString> Vec_device_name={"DUETTO_1","DUETTO_2","TRACER"};

  struct _interpreted_data {
    std::string Name;
    std::vector<float> Vec_values;
  };

  const std::string VERSION_DEFAULT="1.0.0";
  const std::string AUTHOR_DEFAULT="AUTHOR";
  const std::string PROJECT_NAME_DEFAULT="PROJECT_NAME";
  const std::string DATE_DEFAULT="DATE";
  const std::string DEVICE_DEFAULT="DEVICE";

  struct _project_data {
    std::string Version=VERSION_DEFAULT;
    std::string Author=AUTHOR_DEFAULT;
    std::string Project_name=PROJECT_NAME_DEFAULT;
    std::string Date=DATE_DEFAULT;
    std::string Device=DEVICE_DEFAULT;
    _data_xrd_ns::_tube_type XRD_tube_type=_data_xrd_ns::TUBE_TYPE_DEDAULT;
//    _data_xrf_ns::_xrf_data_adjustment XRF_data_adjustment=_data_xrf_ns::XRF_DATA_ADJUSTMENT_DEFAULT;
    float Width_cm=0;
    float Height_cm=0;
    _cs_origin CS_origin=_cs_origin::CS_ORIGIN_TOP_LEFT;
    float Width_original_pixel=0;
    float Height_original_pixel=0;
    float Width_pixel=0;
    float Height_pixel=0;
    float Max_value=0;
    std::vector<float> Vec_coordinate_x_original;
    std::vector<float> Vec_coordinate_y_original;
    std::vector<float> Vec_coordinate_x;
    std::vector<float> Vec_coordinate_y;
    std::vector<_interpreted_data> Vec_xrf_interpreted_data;
    std::vector<_interpreted_data> Vec_xrd_interpreted_data;

    void adjust_coordinates(float Initial_width, float Initial_height);
    void reset();
  };
};

#endif

