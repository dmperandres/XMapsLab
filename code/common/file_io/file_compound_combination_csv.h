//LIC

#ifndef FILE_COMPOUND_COMBINATION_CSV
#define FILE_COMPOUND_COMBINATION_CSV

#include "file_io.h"
#include "data_xrf.h"

class _file_compound_combination_csv: public _file_io
{
public:
  bool read(std::vector<_data_xrf_ns::_data_compound_from_elements_pdb> &Vec_data_compounds_combination_pdb, std::string &Error);
//  void write(_project_data_ns::_project_data &Project_data, std::vector<_common_ns::_element_data> &Vec_element_data);
};

#endif
