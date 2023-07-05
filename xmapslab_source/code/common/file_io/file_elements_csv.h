//LIC

#ifndef FILE_ELEMENTS_CSV
#define FILE_ELEMENTS_CSV

#include "file_io.h"
#include "data_xrf.h"

#include "common.h"

class _file_elements_csv: public _file_io
{
public:
  bool read(std::vector<_data_xrf_ns::_data_xrf_pdb> &Vec_xrf_pdb_data, std::string &Error);
//  void write(_project_data_ns::_project_data &Project_data, std::vector<_common_ns::_element_data> &Vec_element_data);
};

#endif
