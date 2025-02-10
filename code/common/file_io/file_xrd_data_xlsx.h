//LIC

#ifndef FILE_XRD_DATA_XLSX_H
#define FILE_XRD_DATA_XLSX_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include <tuple>
#include <QVariant>
#include "vertex.h"
#include "element_data.h"

#include "file_io_xlsx.h"
#include "project_data.h"

#include "header/xlsxdocument.h"
#include "header/xlsxchartsheet.h"
#include "header/xlsxcellrange.h"
#include "header/xlsxchart.h"
#include "header/xlsxrichstring.h"
#include "header/xlsxworkbook.h"


class _file_xrd_data_xlsx:public _file_io_xlsx
{
public:

// bool read(std::vector<_project_data_ns::_xrd_data_data> &Vec_xrd_data_data, std::vector<std::string> &Vec_element_namess, std::string &Error);
 void write(std::vector<float> Vec_coordinates_obs, std::vector<float> Vec_coordinates_obs_normalized,std::vector<float> Vec_coordinates_pdb_normalized, std::vector<float> Vec_coordinates_sqrt);
};

#endif
