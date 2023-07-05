//LIC

#ifndef FILE_POSITIONS_TXT
#define FILE_POSITIONS_TXT

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

class _file_positions_txt:public _file_io
{
public:
  bool read(_project_data_ns::_project_data &Project_data, std::string &Error);
  void write(_project_data_ns::_project_data &Project_data);
};

#endif
