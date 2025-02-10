//LIC

#ifndef COMMON_WINDOW_H
#define COMMON_WINDOW_H

#include <string>

namespace _common_window_ns{

  const std::string FOLDER_PDB="./pdb";
  const std::string FOLDER_PDB_XRD_SPECTRAL_CU="./pdb/xrd_pdb_spectral_Cu";
  const std::string FOLDER_PDB_XRD_SPECTRAL_CO="./pdb/xrd_pdb_spectral_Co";
  const std::string FOLDER_PDB_XRD_ASTM_CU="./pdb/xrd_pdb_astm_Cu";

  const std::string FILE_ELEMENTS="pdb/xrf_elements.csv";
  const std::string FILE_COMPOUNDS_COMBINATION="pdb/compounds_combination.csv";
  const std::string FILE_POSITIONS="positions/positions.txt";
	const std::string FILE_IMAGE_POSITIONS="positions/positions.png";
	const std::string FILE_INFO="info.txt";
  const std::string FILE_PROJECT_DATA="project_data.csv";
	const std::string FILE_XRF_XLSX="xrf_data.xlsx";
	const std::string FILE_XRD_XLSX="xrd_data.xlsx";
  const std::string FILE_XRF_CSV="xrf_data.csv";
  const std::string FILE_XRD_CSV="xrd_data.csv";
  const std::string FILE_XRF_PP_XLSX="xrf_data_plus_positions.xlsx";
  const std::string FILE_XRD_PP_XLSX="xrd_data_plus_positions.xlsx";
  const std::string FILE_XRD_CORRELATION_DATA_CSV="xrd_correlation_data.csv";
  const std::string FILE_XRD_CORRELATION_DATA_XLSX="xrd_correlation_data.xlsx";

  const std::string FILE_INTERPRETER_USER_SELECTIONS="interpreter_user_selections.csv";

  const std::string FILE_MODE=".mode_g";
}

#endif
