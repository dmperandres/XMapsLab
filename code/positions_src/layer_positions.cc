/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "layer_positions.h"

_layer_positions::_layer_positions()
{
  Image=nullptr;
  State[0]=true;
  State[1]=true;
  Transparence=0.0f;
  Inversion=false;
  Icon=nullptr;
}

/*************************************************************************/

std::shared_ptr<cv::Mat> _layer_positions::input_image(int Pos)
{
  if (Pos>=0 && Pos<int(Vec_input_images.size())){
    return Vec_input_images[Pos];
  }
  else return nullptr;
}

