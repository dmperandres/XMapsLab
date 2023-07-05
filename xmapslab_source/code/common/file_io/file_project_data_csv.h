//LIC

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
  const std::vector<std::string> Vec_allowed_words={"PROJECT_NAME","AUTHOR","DATE","DEVICE","TUBE","XRF_DATA_ADJUSTMENT","WIDTH","HEIGHT","CS_ORIGIN","NUM_SAMPLES","X","Y","XRF","XRD"};

    enum class _allowed_tokens:unsigned char{TOKEN_PROJECT_NAME, TOKEN_AUTHOR, TOKEN_DATE, TOKEN_DEVICE, TOKEN_TUBE, TOKEN_XRF_DATA_ADJUSTMENT, TOKEN_WIDTH, TOKEN_HEIGHT, TOKEN_CS_ORIGIN, TOKEN_NUM_SAMPLES, TOKEN_X, TOKEN_Y, TOKEN_XRF, TOKEN_XRD};

  enum class _mode:unsigned char{MODE_READ,MODE_WRITE};
}

class _file_project_data_csv:public _file_io
{
public:
  bool read(_project_data_ns::_project_data &Project_data,std::vector<std::string> &Vec_xrf_pdb_names,std::vector<std::string> &Vec_xrd_pdb_names, std::string &Error);
  void write(_project_data_ns::_project_data &Project_data);
};

#endif
