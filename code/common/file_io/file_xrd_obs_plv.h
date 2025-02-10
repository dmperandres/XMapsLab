//LIC

#ifndef FILE_XRD_OBS_PLV
#define FILE_XRD_OBS_PLV

#include "data_xrd.h"
#include "file_io.h"

class _file_xrd_obs_plv: public _file_io
{
public:
  bool read(std::vector<float> &Vec_data,std::string &Error);
  void write(std::vector<float> &Vec_data);
};

#endif
