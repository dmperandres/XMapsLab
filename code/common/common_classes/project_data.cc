/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "project_data.h"

using namespace _project_data_ns;

/*************************************************************************/

void _project_data::adjust_coordinates(float Initial_width,float Initial_height)
{
  // normalize the positions. The units can be any one
  float Width_aux=Width_original_pixel;
  float Height_aux=Height_original_pixel;

  Width_pixel=Initial_width;
  Height_pixel=Initial_height;

  Vec_coordinate_x.resize(Vec_coordinate_x_original.size());
  Vec_coordinate_y.resize(Vec_coordinate_y_original.size());

  for (unsigned int i=0;i<Vec_coordinate_x_original.size();i++){
    Vec_coordinate_x[i]=Initial_width*Vec_coordinate_x_original[i]/Width_aux;
    if (CS_origin==_project_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT){
      // convert to OpenGL
      Vec_coordinate_y[i]=Initial_height*(1.0f-Vec_coordinate_y_original[i]/Height_aux);
    }
    else{
      Vec_coordinate_y[i]=Initial_height*Vec_coordinate_y_original[i]/Height_aux;
    }
  }
}

/*************************************************************************/

void _project_data::reset()
{
  Version=VERSION_DEFAULT;
  Author=AUTHOR_DEFAULT;
  Project_name=PROJECT_NAME_DEFAULT;
  Date=DATE_DEFAULT;
  Device=DEVICE_DEFAULT;
  XRD_tube_type=_data_xrd_ns::TUBE_TYPE_DEDAULT;
  CS_origin=_cs_origin::CS_ORIGIN_TOP_LEFT;
  Width_cm=0;
  Height_cm=0;
  Width_original_pixel=0;
  Height_original_pixel=0;
  Width_pixel=0;
  Height_pixel=0;
  Max_value=0;
  Vec_coordinate_x_original.clear();
  Vec_coordinate_y_original.clear();
  Vec_coordinate_x.clear();
  Vec_coordinate_y.clear();
  Vec_xrf_interpreted_data.clear();
  Vec_xrd_interpreted_data.clear();
}
