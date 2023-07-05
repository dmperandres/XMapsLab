//LIC

#ifndef FILE_XRD_PROCESS_INFO_XLSX_H
#define FILE_XRD_PROCESS_INFO_XLSX_H

#include "data_xrd.h"
#include "file_io_xlsx.h"

class _file_xrd_process_info_xlsx: public _file_io_xlsx
{
public:
//  bool read(std::vector<float> &Vec_data, std::string &Error);
  void write(int Num_smooth_steps, int Num_subtract_noise_steps, float Start_2theta, float Steps_2theta, std::vector<float> &Vec_orig_data_obs, std::vector<float> &Vec_smooth_data_obs, std::vector<float> &Vec_subtract_noise_data_obs, std::vector<float> &Vec_normalized_data_obs, std::vector<float> &Vec_orig_data_pdb, std::vector<float> &Vec_smooth_data_pdb, std::vector<float> &Vec_subtract_noise_data_pdb, std::vector<float> &Vec_normalized_data_pdb, std::vector<float> Vec_sqrt_data);
};

#endif
