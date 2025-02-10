//LIC

#include "measurement_data.h"

using namespace _measurement_data_ns;

//HEA

// _measurement_data::_measurement_data(const _measurement_data &Data1)
// {
//   Xray_data_type=Data1.Xray_data_type;
//   Name=Data1.Name;
//   Min_value=Data1.Min_value;
//   Max_value=Data1.Max_value;
//   Max_value_adjusted=Data1.Max_value_adjusted;
//   Atomic_number=Data1.Atomic_number;
//   Vec_values=Data1.Vec_values;
// }



//HEA

void _positions_data::adjust_y_coordinates()
{
  for (unsigned int i=0;i<Vec_coordinate_y.size();i++){
    Vec_coordinate_y[i]=Height-1.0f-Vec_coordinate_y[i];
  }
}

//HEA

//_history_data::_history_data(std::string Name_layer1, std::string Name_element1, std::string View_name1, int Palette1, _layer_map_ns::_interpolation_type Interpolation_type1, int Probe1, std::vector<bool> Use_colors1, std::vector<bool> Use_positions1, _common_ns::_color_model Color_model1, bool Normalization1):
//Name_layer(Name_layer1),Name_element(Name_element1), View_name(View_name1), Palette(Palette1),
//Interpolation_type(Interpolation_type1), Probe(Probe1), Use_colors(Use_colors1), Use_positions(Use_positions1),  Color_model(Color_model1),Normalization(Normalization1)
//{

//}

////HEA

//_history_data::_history_data(const _history_data &Data1)
//{
//  Name_layer=Data1.Name_layer;
//  Name_element=Data1.Name_element;
//  View_name=Data1.View_name;
//  Palette=Data1.Palette;
//  Interpolation_type=Data1.Interpolation_type;
//  Probe=Data1.Probe;
//  Use_colors=Data1.Use_colors;
//  Use_positions=Data1.Use_positions;
//  Color_model=Data1.Color_model;
//}

