//LIC

#include "project_data.h"

using namespace _project_data_ns;


//HEA

void _project_data::adjust_coordinates(float Initial_width,float Initial_height)
{
  // normalize the positions. The units can be any one
  float Width_aux=Width_original;
  float Height_aux=Height_original;

  Width=Initial_width;
  Height=Initial_height;

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
