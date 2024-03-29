/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef FILE_XRD_CORRELATION_XLSX
#define FILE_XRD_CORRELATION_XLSX

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include <tuple>

#include <QString>

#include "file_io_xlsx.h"

#include "project_data.h"

class _file_xrd_correlation_xlsx:public _file_io_xlsx
{
public:
//  bool read(std::vector<std::string> &Vec_obs_names,std::vector<std::string> &Vec_pdb_names,std::vector<std::vector<int>> &Mat_correlations, std::string &Error);
  void write(std::vector<std::string> &Vec_obs_names,std::vector<std::string> &Vec_pdb_names,vector<bool> &Vec_xrd_visible_columns_in_table,vector<vector<_data_xrd_ns::_data_xrd_obs_pdb>> &Mat_xrd_obs_vs_pdb_data);
};

#endif
