/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef IMAGEIO_H
#define IMAGEIO_H

#include <opencv.hpp>
#include <iostream>
#include <string>

/*************************************************************************/

class _image_IO
{
public:
  std::string String;

  void read_image(std::string Name,cv::Mat &Image_in);
  void write_image(std::string Name, cv::Mat &Image_out);
};

#endif
