//LIC

#ifndef FILE_XRD_PDB_ASTM_TXT
#define FILE_XRD_PDB_ASTM_TXT

#include "file_io.h"
#include "vertex.h"

#include "common.h"

namespace _file_xrd_pdb_astm_txt_ns {
  const int MINIMUM_NUMBER_OF_VALUES=560;
}

class _file_xrd_pdb_astm_txt: public _file_io
{
public:
  bool read(std::vector<std::string> &Vec_names,std::vector<std::string> &Vec_formulas,std::vector<std::string> &Vec_elements,_vertex3f &Color,std::vector<float> &Vec_2theta,std::vector<float> &Vec_intensity,std::vector<float> &Vec_d_spacing, std::string &Error);
void write(std::vector<float> &Vec_data);
};

#endif
