/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

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
