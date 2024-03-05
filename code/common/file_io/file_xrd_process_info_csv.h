/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef FILE_XRD_PROCESS_INFO_CSV_H
#define FILE_XRD_PROCESS_INFO_CSV_H

#include "data_xrd.h"
#include "file_io.h"

class _file_xrd_process_info_csv: public _file_io
{
public:
//  bool read(std::vector<float> &Vec_data, std::string &Error);
  void write(int Num_smooth_steps, int Num_subtract_noise_steps, float Start_2theta, float Steps_2theta, std::vector<float> &Vec_orig_data_obs, std::vector<float> &Vec_smooth_data_obs, std::vector<float> &Vec_subtract_noise_data_obs, std::vector<float> &Vec_normalized_data_obs, std::vector<float> &Vec_orig_data_pdb, std::vector<float> &Vec_smooth_data_pdb, std::vector<float> &Vec_subtract_noise_data_pdb, std::vector<float> &Vec_normalized_data_pdb, std::vector<float> Vec_sqrt_data);
};

#endif
