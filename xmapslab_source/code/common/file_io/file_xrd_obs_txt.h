//LIC

#ifndef FILE_XRD_OBS_TXT_H
#define FILE_XRD_OBS_TXT_H

#include "data_xrd.h"
#include "file_io.h"

class _file_xrd_obs_txt: public _file_io
{
public:
  bool read(std::vector<float> &Vec_data, std::string &Error);
  void write(std::vector<float> &Vec_data);
};

#endif
