//LIC

#ifndef FILE_COLOR_MAP_CSV
#define FILE_COLOR_MAP_CSV

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include <tuple>

#include <QString>

#include "file_io.h"

#include "project_data.h"


class _file_color_map_csv:public _file_io
{
public:
  bool read(std::vector<_vertex3f> &Vec_colors,std::string &Error);
//  void write(_project_data_ns::_project_data &Project_data);
};

#endif
