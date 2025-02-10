//LIC

#ifndef PROJECT_DATA
#define PROJECT_DATA

#include <string>
#include <vector>
#include <map>

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


  struct _measured_data {
    std::string Name;
    float Max_value=0;
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
    std::map<std::string, std::string, std::greater<std::string>> Map_device;
    std::map<std::string, std::string, std::greater<std::string>> Map_tube_type;
    std::map<std::string, float> Map_spot_size;
    float Width_cm=0;
    float Height_cm=0;
    float Width_pixel=0;
    float Height_pixel=0;
    _cs_origin CS_origin=_cs_origin::CS_ORIGIN_TOP_LEFT;   
    std::vector<float> Vec_coordinates_x;
    std::vector<float> Vec_coordinates_y;
    std::map<std::string, std::map<std::string, _measured_data>, std::greater<std::string>> Map_data; // inverse order
    float Maximum_value=0;
    std::map<std::string, float> Map_max_value;

    void reset();
  };
};


#endif


