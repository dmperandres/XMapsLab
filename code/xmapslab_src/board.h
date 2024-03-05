/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef BOARD_H
#define BOARD_H

#include <opencv.hpp>

#include <vector>
#include "vertex.h"
#include <random>
#include "object3D.h"

class _board:public _object3D
{
public:

  void create(float Width1, float Height1, int Num_divisions1, _vertex3f Color1,std::shared_ptr<cv::Mat> Result_floats_image);

void update_data(std::shared_ptr<cv::Mat> Result_floats_image);

protected:
  _vertex3f Bottom_left1;
  _vertex3f Top_right1;
  int Num_divisions;
  int Num_vertical_divisions;
  int Num_horizontal_divisions;
  _vertex3f Color;

  const float Height_factor=25;

  int linear_position(int Column,int Row){return (Row*Num_horizontal_divisions+Column);};
};
#endif
