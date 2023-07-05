/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#include "layer.h"

_layer::_layer()
{
  Image=nullptr;
  State[0]=true;
  State[1]=true;
  Transparency=0.0f;
  Inversion=false;
  Icon=nullptr;
}

/*************************************************************************/

std::shared_ptr<cv::Mat> _layer::input_image(int Pos)
{
  if (Pos>=0 && Pos<int(Vec_input_images.size())){
    return Vec_input_images[Pos];
  }
  else return nullptr;
}

/*************************************************************************/

std::vector<int> _layer::vec_values_histogram()
{
  if (Histogram_computed==false){
    Histogram_computed=true;
    compute_histogram();
  }

  return Vec_values_histogram;
}

/*************************************************************************/

void _layer::compute_histogram()
{
  Vec_values_histogram.resize(256,0);

  cv::Mat Image_aux;
  Image_aux=Result_floats_image->clone();
  Image_aux=Image_aux*255.0F;

  cv::Mat Result_gray_image;
  Image_aux.convertTo(Result_gray_image,CV_8U);

  for (int Row=0;Row<Result_gray_image.rows;Row++){
    for (int Col=0;Col<Result_gray_image.cols;Col++){
      Vec_values_histogram[Result_gray_image.at<unsigned char>(Row,Col)]++;
    }
  }
}

