/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef FILE_XY_ARTAX
#define FILE_XY_ARTAX

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include <tuple>
#include <math.h>

#include "file_io.h"

class _file_xrf_xy:public _file_io
{
public:
  bool read(std::vector<float> &Vec_data, float &Step, std::string &Error);
//  void write(std::vector<float> &Vec_data);
};

#endif
