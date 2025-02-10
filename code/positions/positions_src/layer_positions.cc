//LIC

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

//HEA

std::shared_ptr<cv::Mat> _layer_positions::input_image(int Pos)
{
  if (Pos>=0 && Pos<int(Vec_input_images.size())){
    return Vec_input_images[Pos];
  }
  else return nullptr;
}

