/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef FILE_XRF_PROCESS_INFO_CSV_H
#define FILE_XRF_PROCESS_INFO_CSV_H

#include <QString>

#include "file_io.h"

class _file_xrf_process_info_csv: public _file_io
{
public:
//  bool read(std::vector<float> &Vec_data, std::string &Error);
  void write(int Num_smooth_steps, int Num_subtract_noise_steps, float Start_kev, float Seps_kev, std::vector<float> &Vec_orig_data, std::vector<float> &Vec_smooth_data, std::vector<float> &Vec_subtract_noise_data, std::vector<float> &Vec_normalized_data);
};

#endif
