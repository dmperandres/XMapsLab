#ifndef DATA_IO_H
#define DATA_IO_H

#include <string>
#include <vector>
#include <iostream>

#include <QMessageBox>
#include <QApplication>

#include "file_info_txt.h"
#include "file_positions_txt.h"
#include "file_project_data_csv.h"
#include "file_interpreted_csv.h"

#ifdef XRD_ACTIVE
#include "data_xrd.h"

#ifdef XLSX_ACTIVE
#include "file_xrd_data_xlsx.h"
#include "file_interpreted_xlsx.h"
#include "file_xrd_process_info_xlsx.h"
#include "file_xrd_correlation_xlsx.h"
#else
#include "file_xrd_pdb_txt.h"
#include "file_xrd_pdb_astm_txt.h"
#include "file_xrd_correlation_csv.h"
#endif
#endif

#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
#include "file_compound_combination_csv.h"
#endif


#include "data_xrf.h"

#include "file_xrf_process_info_csv.h"

#include "file_xrd_process_info_csv.h"

#include "common_window.h"

class _data_io
{
public:
  // INFO_TXT
  static bool load_info_txt(_window* Window, QString Project_dir, _project_data_ns::_project_data &Project_data);
  static bool save_info_txt(_window *Window, QString Project_dir,_project_data_ns::_project_data &Project_data);

  // POSITIONS_TXT
  static bool load_positions_txt(_window *Window, QString Project_dir, _project_data_ns::_project_data &Project_data);
  static bool save_positions_txt(_window *Window, QString Project_dir,_project_data_ns::_project_data &Project_data);

  // PROJECT_DATA_CSV
  static bool load_project_data_csv(_window *Window, QString Project_dir, _project_data_ns::_project_data &Project_data, std::vector<std::string> &Vec_xrf_pdb_names,std::vector<std::string> &Vec_xrd_pdb_names);
  static bool save_project_data_csv(_window *Window, QString Project_dir,_project_data_ns::_project_data &Project_data);

  // XRF_DATA_CSV
  static bool load_xrf_interpreted_csv(_window *Window, QString Project_dir, std::vector<_project_data_ns::_interpreted_data> &Vec_sampled_data, std::vector<std::string> &Vec_names_pdb);

  // XRD_DATA_CSV
#ifdef XRD_ACTIVE
  static bool load_xrd_interpreted_csv(_window *Window, QString Project_dir, std::vector<_project_data_ns::_interpreted_data> &Vec_sampled_data, std::vector<std::string> &Vec_names_pdb);
#endif

  // XRF_DATA_XLSX
#ifdef XLSX_ACTIVE
  static bool load_xrf_interpreted_xlsx(_window *Window, QString Project_dir, std::vector<_project_data_ns::_interpreted_data>&Vec_interpreted_data, std::vector<std::string> &Vec_xrf_pdb_names);
  static bool save_xrf_interpreted_xlsx(_window *Window, QString Project_dir, std::vector<_project_data_ns::_interpreted_data> &Vec_interpreted_data);
  static bool save_xrf_interpreted_plus_positions_xlsx(_window *Window, QString Project_dir, std::vector<float> Vec_coordinates_x, std::vector<float> Vec_coordinates_y,std::vector<_project_data_ns::_interpreted_data> &Vec_interpreted_data); 
#endif

  // XRF_PDB
  static bool xrf_load_pdb(_window *Window, std::vector<_data_xrf_ns::_data_xrf_pdb> &Vec_xrf_pdb_data,std::vector<std::string> &Vec_xrf_pdb_names);

  static bool xrf_load_pdb_names(_window *Window,std::vector<std::string> &Vec_xrf_pdb_names);

#ifdef INTERPRETER
  static bool xrf_save_process_info_csv(_window *Window, std::string File_name,int Num_smooth_steps,int Num_subtract_noise_steps, float Start_kev, float Steps_kev, std::vector<float> &Vec_orig_data,std::vector<float> &Vec_smooth_data, std::vector<float> &Vec_subtract_noise_data, std::vector<float> &Vec_normalized_data);
#endif

  //XRD_PDB
#ifdef XRD_ACTIVE

#ifdef SPECTRAL_MODE_ACTIVE
  static bool xrd_load_pdb_spectral(_window *Window, std::string Dir, std::vector<_data_xrd_ns::_data_xrd_pdb> &Vec_xrd_pdb_data, std::vector<std::string> &Vec_xrd_pdb_names);

  static bool xrd_load_pdb_spectral_names(_window *Window, std::string Dir,std::vector<std::string> &Vec_xrd_pdb_names);
#endif

#ifdef ASTM_MODE_ACTIVE
  static bool xrd_load_pdb_astm(_window *Window, std::string &Short_name,std::vector<std::string> &Vec_names,std::vector<std::string> &Vec_formulas, std::vector<std::string> Vec_elements,_vertex3f &Color,std::vector<float> &Vec_2theta,std::vector<float> &Vec_intensity, std::vector<float> &Vec_d_spacing);

  static bool xrd_load_pdb_astm_names(_window *Window, std::vector<std::string> &Vec_xrd_pdb_names);
#endif

#ifdef XLSX_ACTIVE
  static bool load_xrd_interpreted_xlsx(_window *Window, QString Project_dir, std::vector<_project_data_ns::_interpreted_data>&Vec_interpreted_data, std::vector<std::string> &Vec_xrf_pdb_names);

  static bool save_xrd_interpreted_xlsx(_window *Window, QString Project_dir, std::vector<_project_data_ns::_interpreted_data> &Vec_interpreted_data);

  static bool save_xrd_interpreted_plus_positions_xlsx(_window *Window, QString Project_dir, std::vector<float> Vec_coordinates_x, std::vector<float> Vec_coordinates_y,std::vector<_project_data_ns::_interpreted_data> &Vec_interpreted_data);

  // for checking the data
  static bool save_xrd_data_xlsx(_window *Window, std::string File_name, std::vector<float> Vec_coordinates_obs, std::vector<float> Vec_coordinates_obs_normalized,std::vector<float> Vec_coordinates_pdb_normalized, std::vector<float> Vec_coordinates_sqrt);

  static bool xrd_save_correlation_table_xlsx(_window *Window, std::string File_name,std::vector<std::string> &Vec_obs_names,std::vector<std::string> &Vec_pdb_names, std::vector<bool> &Vec_xrd_visible_columns_in_table,std::vector<std::vector<_data_xrd_ns::_data_xrd_obs_pdb>> &Mat_xrd_obs_vs_pdb_data);

  static bool xrd_save_process_info_xlsx(_window *Window, std::string File_name,int Num_smooth_steps,int Num_subtract_noise_steps, float Start_2theta, float Steps_2theta, std::vector<float> &Vec_orig_data_obs,std::vector<float> &Vec_smooth_data_obs, std::vector<float> &Vec_subtract_noise_data_obs, std::vector<float> &Vec_normalized_data_obs,std::vector<float> &Vec_orig_data_pdb,std::vector<float> &Vec_smooth_data_pdb, std::vector<float> &Vec_subtract_noise_data_pdb, std::vector<float> &Vec_normalized_data_pdb,std::vector<float> Vec_sqrt_data);

#else
  static bool xrd_save_correlation_table_csv(_window *Window, std::string File_name,std::vector<std::string> &Vec_obs_names,std::vector<std::string> &Vec_pdb_names, std::vector<bool> &Vec_xrd_visible_columns_in_table,std::vector<std::vector<_data_xrd_ns::_data_xrd_obs_pdb>> &Mat_xrd_obs_vs_pdb_data);

  static bool xrd_save_process_info_csv(_window *Window, std::string File_name,int Num_smooth_steps,int Num_subtract_noise_steps, float Start_2theta, float Steps_2theta, std::vector<float> &Vec_orig_data_obs,std::vector<float> &Vec_smooth_data_obs, std::vector<float> &Vec_subtract_noise_data_obs, std::vector<float> &Vec_normalized_data_obs,std::vector<float> &Vec_orig_data_pdb,std::vector<float> &Vec_smooth_data_pdb, std::vector<float> &Vec_subtract_noise_data_pdb, std::vector<float> &Vec_normalized_data_pdb,std::vector<float> Vec_sqrt_data);

#endif
#endif



//  // XRF_INTERPRETED_CSV
//  static bool save_xrf_interpreted_csv(_window *Window, QString Project_dir, std::vector<_project_data_ns::_interpreted_data> &Vec_interpreted_data);

//  // XRD_INTERPRETED_CSV
//  static bool save_xrd_interpreted_csv(_window *Window, QString Project_dir, std::vector<_project_data_ns::_interpreted_data> &Vec_interpreted_data);

  // COMPOUNDS_COMBINATION PDB
#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
  static bool load_compounds_combination_pdb(_window *Window, std::vector<_data_xrf_ns::_data_compound_from_elements_pdb> &Vec_data_compounds_combination_pdb);
#endif

  protected:
#ifdef XLSX_ACTIVE
  static bool load_interpreted_xlsx(_window *Window,std::vector<_project_data_ns::_interpreted_data>&Vec_interpreted_data, std::vector<std::string> &Vec_element_namess,std::string File_name);
  static bool save_interpreted_xlsx(_window *Window, std::vector<_project_data_ns::_interpreted_data> &Vec_interpreted_data,std::string File_name);
  static bool save_interpreted_plus_positions_xlsx(_window *Window, std::vector<float> Vec_coordinates_x, std::vector<float> Vec_coordinates_y,std::vector<_project_data_ns::_interpreted_data> &Vec_interpreted_data,std::string File_name);
#endif

};

#endif
