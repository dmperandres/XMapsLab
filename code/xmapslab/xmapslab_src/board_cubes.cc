//LIC

#include "board_cubes.h"

//HEA

void _board_cubes::create(float Width1, float Height1, int Num_divisions1, std::shared_ptr<cv::Mat> Image, std::shared_ptr<cv::Mat> Result_floats_image)
{
  Width=Width1;
  Height=Height1;
  Num_divisions=Num_divisions1;

  // compute the numer of row and columns, as well as the size of the base of the cube.
  // The height depends on the layer data

  if (Width/Height>=1){
    // Height is smaller
    Num_vertical_divisions=Num_divisions;
    float Height_quotient=Height/float(Num_divisions);
    Num_horizontal_divisions=int(roundf(Width/Height_quotient));

  }
  else{
    // Widht is smaller
    Num_horizontal_divisions=Num_divisions;
    float Width_quotient=Width/float(Num_divisions);
    Num_vertical_divisions=int(roundf(Height/Width_quotient));
  }

  Cube_width=Width/Num_horizontal_divisions;
  Cube_height=Height/Num_vertical_divisions;
  Cube_half_width=Cube_width/2;
  Cube_half_height=Cube_height/2;

  Num_cubes=Num_horizontal_divisions*Num_vertical_divisions;

  float Width_result=0;
  float Height_result=0;

  if (Result_floats_image!=nullptr){
    Width_result=float(Result_floats_image->cols-1);
    Height_result=float(Result_floats_image->rows-1);
    if (Width_result>Height_result) Depth_result=Width_result/Height_factor;
    else Depth_result=Height_result/Height_factor;
  }

  // compute the positions
  Vec_positions.resize(Num_cubes);
  Vec_scaling.resize(Num_cubes);
  Vec_colors.resize(Num_cubes);

  float Min_x=-Width/2;
  float Min_y=-Height/2;
  float s,t;
  float Pos_x,Pos_y;
  int Position=0;

//  float Value;

  for (int Row=0;Row<Num_vertical_divisions;Row++){
    s=float(Row)/float(Num_vertical_divisions);
    Pos_y=roundf(s*float(Height-1)+Cube_half_height);
    for (int Col=0;Col<Num_horizontal_divisions;Col++){
      t=float(Col)/float(Num_horizontal_divisions);
      Pos_x=roundf(t*float(Width-1)+Cube_half_width);
      // positions
      // plane Y=0;
//      Value=Width*t+Min_x+Cube_half_width;
//      Value=-(Height*s+Min_y+Cube_half_height);

      Vec_positions[Position].x=Width*t+Min_x+Cube_half_width;
      Vec_positions[Position].z=-(Height*s+Min_y+Cube_half_height);

      // scaling
      Vec_scaling[Position].x=Cube_width;

      if (Result_floats_image!=nullptr){
        Vec_scaling[Position].y=Result_floats_image->at<float>(int(Pos_y),int(Pos_x))*Depth_result;
      }
      else{
        Vec_scaling[Position].y=Cube_width;
      }

      Vec_scaling[Position].z=Cube_height;

      // colors
      cv::Vec4b Vector;
      if (Image!=nullptr){
        Vector=Image->at<cv::Vec4b>(int(Pos_y),int(Pos_x));
        Vec_colors[Position]=_vertex3uc(Vector[2],Vector[1],Vector[0]);
      }

      Position++;
    }
  }
}

//HEA

void _board_cubes::update_data(std::shared_ptr<cv::Mat> Image, std::shared_ptr<cv::Mat> Result_floats_image)
{
//  float Min_x=-Width/2;
//  float Min_y=-Height/2;
  float s,t;
  float Pos_x,Pos_y;
  int Position=0;

  float Width_result=0;
  float Height_result=0;

  if (Result_floats_image!=nullptr){
    Width_result=float(Result_floats_image->cols-1);
    Height_result=float(Result_floats_image->rows-1);
    if (Width_result>Height_result) Depth_result=Width_result/Height_factor;
    else Depth_result=Height_result/Height_factor;
  }

//  float Value;

  for (int Row=0;Row<Num_vertical_divisions;Row++){
    s=float(Row)/float(Num_vertical_divisions);
    Pos_y=roundf(s*float(Height-1)+Cube_half_height);
    for (int Col=0;Col<Num_horizontal_divisions;Col++){
      t=float(Col)/float(Num_horizontal_divisions);
      Pos_x=roundf(t*float(Width-1)+Cube_half_width);

      // scaling
      Vec_scaling[Position].x=Cube_width;

      if (Result_floats_image!=nullptr){
        Vec_scaling[Position].y=Result_floats_image->at<float>(int(Pos_y),int(Pos_x))*Depth_result;
      }
      else{
        Vec_scaling[Position].y=Cube_width;
      }

      Vec_scaling[Position].z=Cube_height;

      // colors
      cv::Vec4b Vector;
      if (Image!=nullptr){
        Vector=Image->at<cv::Vec4b>(int(Pos_y),int(Pos_x));
        Vec_colors[Position]=_vertex3uc(Vector[2],Vector[1],Vector[0]);
      }

      Position++;
    }
  }
}


