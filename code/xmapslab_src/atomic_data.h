/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef ATOMIC_DATA
#define ATOMIC_DATA

#include <string>
#include <vector>
#include <iostream>
#include <QColor>

//#include <opencv.hpp>

class _atomic_data{
public:
  std::string Short_name;
  std::string Name;
  float Atomic_number=0;
  float Atomic_weight=0;
  QColor Color;

//  _atomic_data(){}
//  _atomic_data(std::string Short_name1,std::string Name1,float Atomic_number1,float Atomic_weight1,QColor Color1);
//  _atomic_data(const _atomic_data &Data1);
};

#endif

