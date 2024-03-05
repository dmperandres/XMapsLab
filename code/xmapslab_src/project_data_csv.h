/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef PROJECT_DATA_CSV
#define PROJECT_DATA_CSV

#include <QMessageBox>

#include <string>
#include <vector>
#include <iostream>

#include <opencv.hpp>

/*************************************************************************/

namespace _project_data_csv_ns
{	
	struct _interpreted_data {
		std::string Name;
    std::vector<float> Vec_values;
	};
	
  struct _project_data_csv {
    std::string Author;
    std::string Project_name;
    std::string Date;
    std::string Device;
    float Width=-1;
    float Height=-1;
    int Num_samples=0;
    std::vector<float> Vec_coordinate_x;
    std::vector<float> Vec_coordinate_y;
    std::vector<_interpreted_data> Vec_xrf_interpreted_data;
    std::vector<_interpreted_data> Vec_xrd_interpreted_data;
  };
};

#endif

