/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef FILE_INTERPRETED_CSV
#define FILE_INTERPRETED_CSV

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

//#include "data_xrf.h"

namespace _file_interpreted_csv_ns {
  enum class _mode:unsigned char{MODE_READ,MODE_WRITE};
}

class _file_interpreted_csv:public _file_io
{
public:
  bool read(std::vector<_project_data_ns::_interpreted_data> &Vec_data,std::vector<std::string> &Vec_names_pdb, std::string &Error);
  void write(std::vector<_project_data_ns::_interpreted_data> &Vec_data);
};

#endif
