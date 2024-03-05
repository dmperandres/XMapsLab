/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef FILE_INFO_TXT
#define FILE_INFO_TXT

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include <tuple>
#include <fstream>

#include "file_io.h"

#include "project_data.h"

class _window;

namespace _file_info_txt_ns {
  const std::vector<std::string> Vec_allowed_words={"PROJECT_NAME","AUTHOR","DATE","DEVICE","TUBE","XRF_DATA_ADJUSTMENT","WIDTH","HEIGHT"};
  enum class _allowed_tokens:unsigned char{TOKEN_PROJECT_NAME,TOKEN_AUTHOR,TOKEN_DATE,TOKEN_DEVICE,TOKEN_TUBE,TOKEN_XRF_DATA_ADJUSTMENT,TOKEN_WIDTH,TOKEN_HEIGHT};
}

class _file_info_txt: public _file_io
{
public:
  bool read(_project_data_ns::_project_data &Project_data, std::string &Error);
  void write(_project_data_ns::_project_data &Project_data);
};

#endif
