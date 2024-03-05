/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef FILE_INTERPRETER_USER_SELECTIONS_CSV
#define FILE_INTERPRETER_USER_SELECTIONS_CSV

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

namespace _file_interpreter_user_selections_ns {
  enum class _mode:unsigned char{MODE_READ,MODE_WRITE};
}

class _file_interpreter_user_selections:public _file_io
{
public:
  bool read(int &Selected_file_position, unsigned int& XRF_num_steps_smooth, unsigned int& XRF_num_steps_subtract_background, unsigned int& XRF_num_steps_search_window, _data_xrf_ns::_smooth_type& XRF_smooth_type, int &XRF_threshold_percentage, std::vector<_data_xrf_ns::_data_xrf_obs> &Vec_xrf_obs_data, std::vector<std::string> &Vec_xrd_selected_pdb_folders, unsigned int& XRD_num_steps_smooth, unsigned int& XRD_num_steps_subtract_background, unsigned int& XRD_num_steps_shift, _data_xrd_ns::_smooth_type& XRD_smooth_type, _data_xrd_ns::_normalization_type& XRD_normalization_type, float& XRD_correlation_good_threshold, float& XRD_correlation_medium_threshold, float& XRD_correlation_bad_threshold, std::vector<std::vector<_data_xrd_ns::_selection> > &Mat_xrd_obs_vs_pdb_data_selected, std::string &Error);

  bool read(std::vector<std::string> &Vec_xrd_selected_pdb_folders, std::string &Error);

  //
  void write(int Selected_file_position, int XRF_num_steps_smooth, int XRF_num_steps_subtract_background, int XRF_num_steps_search_window, _data_xrf_ns::_smooth_type XRF_smooth_type, int XRF_threshold_percentage, std::vector<_data_xrf_ns::_data_xrf_obs> Vec_xrf_obs_data, std::vector<std::string> &Vec_xrd_selected_pdb_folders, int XRD_num_steps_smooth, int XRD_num_steps_subtract_background, int XRD_num_steps_shift, _data_xrd_ns::_smooth_type XRD_smooth_type, _data_xrd_ns::_normalization_type XRD_normalization_type, float XRD_correlation_good_threshold, float XRD_correlation_medium_threshold, float XRD_correlation_bad_threshold, std::vector<std::vector<_data_xrd_ns::_selection> > &Mat_xrd_obs_vs_pdb_data_selected);

  void write(std::vector<std::string> &Vec_xrd_selected_pdb_folders);
};

#endif
