/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef FILE_XRD_OBS_UXD
#define FILE_XRD_OBS_UXD

#include "data_xrd.h"
#include "file_io.h"

class _file_xrd_obs_uxd: public _file_io
{
public:
  bool read(std::vector<float> &Vec_data,std::string &Error);
  void write(std::vector<float> &Vec_data);
};

#endif
