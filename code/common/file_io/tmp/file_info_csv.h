//LIC

#ifndef FILE_INFO_CSV
#define FILE_INFO_CSV

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "file_io.h"

#include "project_data.h"

namespace _file_info_csv_ns {
  const std::vector<std::string> Vec_allowed_words={"PROJECT_NAME","AUTHOR","DATE","DEVICE","WIDTH","HEIGHT"};
  enum class _allowed_tokens:unsigned char{TOKEN_PROJECT_NAME,TOKEN_AUTHOR,TOKEN_DATE,TOKEN_DEVICE,TOKEN_WIDTH,TOKEN_HEIGHT};
}

class _file_info_csv: public _file_io
{
public:
  bool read(_project_data_ns::_project_data &Project_data, std::string &Error);
  void write(_project_data_ns::_project_data &Project_data);
};

#endif
