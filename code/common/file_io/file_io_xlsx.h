/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef FILE_IO_XLSX_H
#define FILE_IO_XLSX_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include <tuple>
#include <stdexcept>
//#include <regex>

#include "header/xlsxdocument.h"
#include "header/xlsxchartsheet.h"
#include "header/xlsxcellrange.h"
#include "header/xlsxchart.h"
#include "header/xlsxrichstring.h"
#include "header/xlsxworkbook.h"

class _file_io_xlsx
{
public:
  enum class _mode:unsigned char{MODE_READ,MODE_WRITE};

  _file_io_xlsx(){}
  int open(const std::string &File_name1,_mode Mode);
  void close(){};

  bool read(){return false;}
  void write(){};

protected:
  std::string File_name;
  QXlsx::Document* Table=nullptr;

  std::string read_cell(int Row, int Col);
};

#endif
