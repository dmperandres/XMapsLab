/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef FILE_XRD_PDB_CSV
#define FILE_XRD_PDB_CSV

#include "file_io.h"
#include "data_xrd.h"
#include "vertex.h"

namespace _file_xrd_pdb_csv_ns {
  const int MINIMUM_NUMBER_OF_VALUES=560;
}

#ifdef GC
class _file_xrd_pdb_csv: public _file_io
{
  public:
  bool read(_data_xrd_ns::_tube_type &XRD_pdb_tube_type, std::vector<std::string> &Vec_names, std::vector<std::string> &Vec_formulas, std::vector<std::string> &Vec_elements, std::vector<float> &Vec_data, std::string &Error);
  void write(std::string Name, std::string Formula, std::string XRF, float Start_value, std::vector<float> &Vec_data);
};
#else
class _file_xrd_pdb_csv: public _file_io
{
public:
  bool read(std::string &Type, std::string &Tube, std::string &Normalized, std::vector<std::string> &Vec_names, std::vector<std::string> &Vec_formulas, std::vector<std::string> &Vec_elements, _vertex3f &Color, std::vector<float> &Vec_data,  std::vector<float> &Vec_2theta, std::vector<float> &Vec_intensity, std::vector<float> &Vec_d_spacing, std::string &Error);
  void write(std::string Type, std::string Tube, std::string Normalized, std::string Name, std::string Formula, std::string XRF, std::string Color, float Start_value, std::vector<float> &Vec_data);
};
#endif

#endif
