/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef FILE_PROJECT_DATA_CSV
#define FILE_PROJECT_DATA_CSV

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

namespace _file_project_data_csv_ns {
  const std::vector<std::string> Vec_allowed_words={"PROJECT_NAME","AUTHOR","DATE","DEVICE","TUBE","WIDTH_CM","HEIGHT_CM","WIDTH_PIXEL","HEIGHT_PIXEL","CS_ORIGIN","X","Y","XRF","XRD","COMMENT"};

    enum class _allowed_tokens:unsigned char{TOKEN_PROJECT_NAME, TOKEN_AUTHOR, TOKEN_DATE, TOKEN_DEVICE, TOKEN_TUBE, TOKEN_WIDTH_CM, TOKEN_HEIGHT_CM, TOKEN_WIDTH_PIXEL, TOKEN_HEIGHT_PIXEL, TOKEN_CS_ORIGIN, TOKEN_X, TOKEN_Y, TOKEN_XRF, TOKEN_XRD,TOKEN_COMMENT};

  enum class _mode:unsigned char{MODE_READ,MODE_WRITE};
}

class _file_project_data_csv:public _file_io
{
public:
  bool read(_project_data_ns::_project_data &Project_data,std::vector<std::string> &Vec_xrf_pdb_names,std::vector<std::string> &Vec_xrd_pdb_names, std::string &Error);
  void write(_project_data_ns::_project_data &Project_data);
};

#endif
