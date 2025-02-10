//LIC

#ifndef FILE_XRD_CORRELATION_CSV
#define FILE_XRD_CORRELATION_CSV

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

namespace _file_xrd_correlation_csv_ns {
  enum class _mode:unsigned char{MODE_READ,MODE_WRITE};
}

class _file_xrd_correlation_csv:public _file_io
{
public:
//  bool read(std::vector<std::string> &Vec_obs_names,std::vector<std::string> &Vec_pdb_names,std::vector<std::vector<int>> &Mat_correlations, std::string &Error);
void write(std::vector<std::string> &Vec_obs_names, std::vector<std::string> &Vec_pdb_names, std::vector<std::vector<_data_xrd_ns::_data_xrd_obs_pdb>> &Mat_xrd_obs_vs_pdb_data, std::vector<std::vector<_data_xrd_ns::_selection> > &Mat_xrd_obs_vs_pdb_data_selected);
};

#endif
