#ifndef DATA_IO_H
#define DATA_IO_H

#include <string>
#include <vector>
#include <iostream>

#include <QMessageBox>
#include <QApplication>
#include <QFileInfo>
#include <QDir>

#include "data_xrf.h"
#include "data_xrd.h"

#include "file_elements_csv.h"
#include "file_project_data_csv.h"
// #include "file_xrd_pdb_csv.h"
// //#include "file_xrd_pdb_astm_csv.h"
// #include "file_xrd_correlation_csv.h"
// #include "file_compound_combination_csv.h"
// #include "file_xrf_process_info_csv.h"
// #include "file_xrd_process_info_csv.h"
// #include "file_interpreted_csv.h"
// #include "file_interpreter_user_selections_csv.h"
// #include "file_positions_csv.h"
#include "file_color_map_csv.h"

#include "common_window.h"

class _window;

class _data_io
{
public:
    // PROJECT_DATA_CSV
static bool load_project_data_csv(QWidget *Window, std::string Project_dir, _project_data_ns::_project_data &Project_data);
  static bool save_project_data_csv(QWidget *Window, std::string Project_dir, _project_data_ns::_project_data &Project_data);

  // XRF_DATA_CSV
  // static bool xrf_load_interpreted_csv(QWidget *Window, std::string File_name, std::vector<_project_data_ns::_measured_data> &Vec_sampled_data, std::vector<std::string> &Vec_names_pdb);

#ifdef INTERPRETER
  // XRD_DATA_CSV
  static bool xrd_load_interpreted_csv(QWidget *Window, std::string Project_dir, std::vector<_project_data_ns::_interpreted_data> &Vec_sampled_data, std::vector<std::string> &Vec_names_pdb);
#endif

  // XRF_PDB
  // static bool xrf_load_pdb(QWidget *Window, std::vector<_data_xrf_ns::_data_xrf_pdb> &Vec_xrf_pdb_data,std::vector<std::string> &Vec_xrf_pdb_names);

  // static bool xrf_load_pdb_names(QWidget *Window,std::vector<std::string> &Vec_xrf_pdb_names);

  // static bool xrf_save_process_info_csv(QWidget *Window, std::string File_name,int Num_smooth_steps,int Num_subtract_noise_steps, float Start_kev, float Steps_kev, std::vector<float> &Vec_orig_data,std::vector<float> &Vec_smooth_data, std::vector<float> &Vec_subtract_noise_data, std::vector<float> &Vec_normalized_data);

#ifdef INTERPRETER
  // XRD_PDB
  static bool xrd_load_pdb(QWidget *Window, std::string Dir, std::vector<_data_xrd_ns::_data_xrd_pdb> &Vec_xrd_pdb_data, std::vector<std::string> &Vec_xrd_pdb_names);
#ifdef GC
  static bool xrd_save_pdb_spectral(QWidget *Window, std::string File_name, std::string Name, std::string Formula, std::string XRF, float Start_value, std::vector<float> &Vec_data);
#else
  static bool xrd_save_pdb_spectral(QWidget *Window, std::string File_name, std::string Type, std::string Tube, std::string Normalized, std::string Name, std::string Formula, std::string XRF, std::string Color, float Start_value, std::vector<float> &Vec_data);
#endif

  //
  static bool xrd_save_correlation_table_csv(QWidget *Window, std::string File_name,std::vector<std::string> &Vec_obs_names,std::vector<std::string> &Vec_pdb_names,  std::vector<std::vector<_data_xrd_ns::_data_xrd_obs_pdb>> &Mat_xrd_obs_vs_pdb_data, std::vector<std::vector<_data_xrd_ns::_selection>> &Mat_xrd_obs_vs_pdb_data_selected);

  static bool xrd_save_process_info_csv(QWidget *Window, std::string File_name,int Num_smooth_steps,int Num_subtract_noise_steps, float Start_2theta, float Steps_2theta, std::vector<float> &Vec_orig_data_obs,std::vector<float> &Vec_smooth_data_obs, std::vector<float> &Vec_subtract_noise_data_obs, std::vector<float> &Vec_normalized_data_obs,std::vector<float> &Vec_orig_data_pdb,std::vector<float> &Vec_smooth_data_pdb, std::vector<float> &Vec_subtract_noise_data_pdb, std::vector<float> &Vec_normalized_data_pdb,std::vector<float> Vec_sqrt_data);
#endif

  // XRF_INTERPRETED_CSV
  // static bool save_xrf_interpreted_csv(QWidget *Window, std::string Project_dir, std::vector<_project_data_ns::_measured_data> &Vec_interpreted_data);

#ifdef INTERPRETER
  // XRD_INTERPRETED_CSV
  static bool save_xrd_interpreted_csv(QWidget *Window, std::string Project_dir, std::vector<_project_data_ns::_interpreted_data> &Vec_interpreted_data);
#endif

  // COMPOUNDS_COMBINATION PDB
  // static bool load_compounds_combination_pdb(QWidget *Window, std::vector<_data_xrf_ns::_data_compound_from_elements_pdb> &Vec_data_compounds_combination_pdb);

  // USER SELECTIONS
  // static bool load_interpreter_user_selections_csv(QWidget *Window, std::string Project_dir, int &Selected_file_position, unsigned int& XRF_num_steps_smooth, unsigned int& XRF_num_steps_subtract_background, unsigned int& XRF_num_steps_search_window, _data_xrf_ns::_smooth_type& XRF_smooth_type, int &XRF_threshold_percentage, std::vector<_data_xrf_ns::_data_xrf_obs> &Vec_xrf_obs_data, std::vector<std::string> &Vec_xrd_selected_pdb_folders, unsigned int& XRD_num_steps_smooth, unsigned int& XRD_num_steps_subtract_background, unsigned int& XRD_num_steps_shift, _data_xrd_ns::_smooth_type& XRD_smooth_type, _data_xrd_ns::_normalization_type& XRD_normalization_type, float& XRD_correlation_good_threshold, float& XRD_correlation_medium_threshold, float& XRD_correlation_bad_threshold, std::vector<std::vector<_data_xrd_ns::_selection> > &Mat_xrd_obs_vs_pdb_data_selected);

  // static bool save_interpreter_user_selections_csv(QWidget *Window, std::string Project_dir, int Selected_file_position, int XRF_num_steps_smooth, int XRF_num_steps_subtract_background, int XRF_num_steps_search_window,_data_xrf_ns::_smooth_type XRF_smooth_type, int XRF_threshold_percentage, std::vector<_data_xrf_ns::_data_xrf_obs> &Vec_xrf_obs_data, std::vector<std::string> &Vec_xrd_selected_pdb_folders, int XRD_num_steps_smooth, int XRD_num_steps_subtract_background, int XRD_num_steps_shift,  _data_xrd_ns::_smooth_type XRD_smooth_type, _data_xrd_ns::_normalization_type XRD_normalization_type, float XRD_correlation_good_threshold, float XRD_correlation_medium_threshold, float XRD_correlation_bad_threshold, std::vector<std::vector<_data_xrd_ns::_selection> > &Mat_xrd_obs_vs_pdb_data_selected);

  // static bool load_interpreter_user_selections_csv(QWidget *Window, std::string Project_dir, std::vector<std::string> &Vec_xrd_selected_pdb_folders);

  // static bool save_interpreter_user_selections_csv(QWidget *Window, std::string Project_dir,  std::vector<std::string> &Vec_xrd_selected_pdb_folders);

  // POSITIONS FROM CSV
// static bool load_positions_data_csv(QWidget *Window, std::string File_name, _project_data_ns::_project_data &Project_data);

  // COLORMAP CSV
static bool load_colormaps_csv(QWidget *Window, std::string Project_dir, std::map<std::string, std::vector<_vertex3f> > &Map_fixed_palettes);

protected:
#ifdef INTERPRETER
  //XRD_PDB
  bool xrd_load_pdb_data(QWidget *Window, std::string File_name, std::string &Type, std::string &Tube, std::string &Normalized, std::vector<std::string> &Vec_names, std::vector<std::string> &Vec_formulas, std::vector<std::string> Vec_elements, _vertex3f &Color, std::vector<float> &Vec_values, std::vector<float> &Vec_2theta, std::vector<float> &Vec_intensity, std::vector<float> &Vec_d_spacing);
  bool xrd_load_pdb_names(QWidget *Window, std::string Dir,std::vector<std::string> &Vec_xrd_pdb_names);
#endif

  _data_xrd_ns::_pdb_type pdb_check_type(std::string File_name);
};

#endif
