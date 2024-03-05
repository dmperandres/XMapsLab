/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "image_IO.h"

/*************************************************************************/

void _image_IO::read_image(std::string Name,cv::Mat &Image_in)
{
  #ifdef WINDOWS
  std::string Aux_string;
  for (int i=0;i<Name.size();i++){
    if (Name[i]=='/'){
      Aux_string.push_back('\\');
    }
    else Aux_string.push_back(Name[i]);
  }
  Name=Aux_string;
  #endif

  Image_in=cv::imread(Name,cv::IMREAD_UNCHANGED);
  if( !Image_in.data ){ // check if the image has been loaded properly
    std::cout << "Error reading the image: " << Name << std::endl;
    exit(-1);
  }
}

/*************************************************************************/

void _image_IO::write_image(std::string Name,cv::Mat &Image_out)
{
	imwrite(Name, Image_out);
}
