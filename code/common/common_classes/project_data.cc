//LIC

#include "project_data.h"

using namespace _project_data_ns;

//HEA

void _project_data::reset()
{
  Version=VERSION_DEFAULT;
  Author=AUTHOR_DEFAULT;
  Project_name=PROJECT_NAME_DEFAULT;
  Date=DATE_DEFAULT;
  Map_device.clear();
  Map_tube_type.clear();
  Map_spot_size.clear();
  CS_origin=_cs_origin::CS_ORIGIN_TOP_LEFT;
  Width_cm=0;
  Height_cm=0;
  Width_pixel=0;
  Height_pixel=0;  
  Vec_coordinates_x.clear();
  Vec_coordinates_y.clear();
  Map_data.clear();

  Maximum_value=0;
  Map_max_value.clear();
}
