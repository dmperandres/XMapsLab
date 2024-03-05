/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef FILE_INTERPRETED_XLSX_H
#define FILE_INTERPRETED_XLSX_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include <tuple>
#include <QVariant>
#include "vertex.h"

#include "file_io_xlsx.h"
#include "project_data.h"

#include "header/xlsxdocument.h"
#include "header/xlsxchartsheet.h"
#include "header/xlsxcellrange.h"
#include "header/xlsxchart.h"
#include "header/xlsxrichstring.h"
#include "header/xlsxworkbook.h"

namespace _file_interpreted_xlsx_ns {
 const std::vector<std::string> Vec_allowed_words={"PROJECT_NAME","AUTHOR","DATE","DEVICE","WIDTH","HEIGHT","NUM_SAMPLES","X","Y","XRF","XRD"};
 enum class _allowed_tokens:unsigned char{TOKEN_PROJECT_NAME,TOKEN_AUTHOR,TOKEN_DATE,TOKEN_DEVICE,TOKEN_WIDTH,TOKEN_HEIGHT,TOKEN_NUM_SAMPLES, TOKEN_X,TOKEN_Y, TOKEN_XRF,TOKEN_XRD};

  enum class _mode:unsigned char{MODE_READ,MODE_WRITE};
}

class _file_interpreted_xlsx:public _file_io_xlsx
{
public:

 bool read(std::vector<_project_data_ns::_interpreted_data> &Vec_interpreted_data, std::vector<std::string> &Vec_element_namess, std::string &Error);
 void write(std::vector<_project_data_ns::_interpreted_data> &Vec_interpreted_data);
 void write(std::vector<float> &Vec_coordinates_x,std::vector<float> &Vec_coordinates_y,std::vector<_project_data_ns::_interpreted_data> &Vec_interpreted_data);
};

#endif
