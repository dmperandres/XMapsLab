/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef FILE_IO_H
#define FILE_IO_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <utility>
#include <tuple>
#include <stdexcept>

#include <QRegularExpression>
//#include <regex>

#include "common.h"

class _file_io
{
public:
  enum class _mode:unsigned char{MODE_READ,MODE_WRITE};

  _file_io(){}
  bool open(const std::string &File_name1,_mode Mode);
  void close();

  bool read(){return false;}
  void write(){};

protected:
  void get_token(std::istringstream &Line_stream1, std::string &Token1, char Separator);
  bool get_new_line(std::fstream &File,std::string &Line);
  void get_tokens(std::string &String,char Separator,std::vector<std::string> &Tokens);
  std::string clean_token(std::string Token);

  std::fstream File;
  std::string File_name;
};

#endif
