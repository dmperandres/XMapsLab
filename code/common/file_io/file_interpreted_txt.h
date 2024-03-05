/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef FILE_INTERPRETED_TXT
#define FILE_INTERPRETED_TXT

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include <tuple>

#include "file_io.h"

#include "pigment_data.h"

class _file_interpreted_txt: public _file_io
{
public:
  _pigment_data_ns::_pair_name_value Val;
  bool read(std::vector<_pigment_data_ns::_pair_name_value> &Vec_data,std::string &Error);
//  void write(vector<float> &Vec_data);
};

#endif
