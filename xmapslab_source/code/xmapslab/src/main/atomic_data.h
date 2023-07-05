/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#ifndef ATOMIC_DATA
#define ATOMIC_DATA

#include <string>
#include <vector>
#include <iostream>
#include <QColor>

struct _atomic_data {
  std::string Short_name;
  std::string Name;
  float Atomic_number=0.0f;
  QColor Color;
};

#endif

