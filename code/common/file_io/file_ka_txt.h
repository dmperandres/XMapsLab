/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef FILE_KA_TXT
#define FILE_KA_TXT

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include <tuple>
#include <QCryptographicHash>
#include "vertex.h"
//#include "element_data.h"

class _file_ka_txt
{
public:
  enum class _mode:unsigned char{MODE_READ,MODE_WRITE};

  _file_ka_txt(){}
  int open(const string &File_name,_mode Mode);
  void close();

  bool read(vector<float> &Vec_data,string &Error,string &Line, int &Position);
  void write(vector<float> &Vec_data);

private:
  void get_token(std::istringstream &Line_stream1, std::string &Token1, char Separator);
  bool get_new_line(fstream &File, std::istringstream &Line_stream);

  std::fstream File;
};

#endif
