//LIC

#ifndef BOARD_CUBES_H
#define BOARD_CUBES_H

#include <opencv.hpp>

#include <vector>
#include "vertex.h"
#include <random>
#include "object3D.h"

class _board_cubes:public _object3D
{
public:
  std::vector<_vertex3f> Vec_positions;
  std::vector<_vertex3f> Vec_scaling;
  std::vector<_vertex3uc> Vec_colors;

  void create(float Width1, float Height1, int Num_divisions1, std::shared_ptr<cv::Mat> Image,std::shared_ptr<cv::Mat> Result_floats_image);

  void update_data(std::shared_ptr<cv::Mat> Image,std::shared_ptr<cv::Mat> Result_floats_image);

  int num_cubes(){return Num_cubes;}

protected:
  float Width=0;
  float Height=0;
  int Num_divisions=0;
  int Num_vertical_divisions=0;
  int Num_horizontal_divisions=0;
  int Num_cubes=0;
  float Cube_width=0;
  float Cube_height=0;
  float Cube_half_width=0;
  float Cube_half_height=0;
  float Depth_result=0;

  const float Height_factor=25;
};
#endif
