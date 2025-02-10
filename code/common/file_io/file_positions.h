//LIC

#ifndef FILE_POSITIONS
#define FILE_POSITIONS

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <QCryptographicHash>
#include "vertex.h"
#include "pigment_data.h"

class _file_positions
{
public:
  enum class _mode:unsigned char{MODE_READ,MODE_WRITE};

  _file_positions(){}
  int open(const string &File_name,_mode Mode);
  bool read(_measurement_data_ns::_positions_data &Positions_data, string &Error, string &Line, int &Position);
//  void write(_measurement_data_ns::_project_data &Project_data, vector<_measurement_data_ns::_pigment_data> &Vec_element_data);
  void close();

private:
  void get_token(std::istringstream &Line_stream1, std::string &Token1, char Separator);
  bool get_new_line(std::fstream &File,std::istringstream &Line_stream);

  std::fstream File;
};

#endif
