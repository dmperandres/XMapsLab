//LIC

#ifndef FILE_MEASURED_CSV
#define FILE_MEASURED_CSV

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

namespace _file_measured_csv_ns {
  enum class _mode:unsigned char{MODE_READ,MODE_WRITE};
}

class _file_measured_csv:public _file_io
{
public:
  bool read(std::vector<_project_data_ns::_measured_data> &Vec_data,std::vector<std::string> &Vec_names_pdb, std::string &Error);
  void write(std::vector<_project_data_ns::_measured_data> &Vec_data);
};

#endif
