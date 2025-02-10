//LIC

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

#include "measurement_data.h"

class _file_interpreted_txt: public _file_io
{
public:
  _measurement_data_ns::_pair_name_value Val;
  bool read(std::vector<_measurement_data_ns::_pair_name_value> &Vec_data,std::string &Error);
//  void write(vector<float> &Vec_data);
};

#endif
