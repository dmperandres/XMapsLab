#ifndef NEW_RBF_INTERPOLATION_PLUS_2D
#define NEW_RBF_INTERPOLATION_PLUS_2D

#include <vector>
#include <math.h>
#include <string>

#include <Eigen/Dense>

#include <opencv.hpp>

#include "new_rbf_interpolation_2d.h"

class _new_rbf_interpolation_2d_plus: public _new_rbf_interpolation_2d
{
public:

    void set_input_data(std::vector<float>& Input_coordinates_x1, std::vector<float>& Input_coordinates_y1, std::vector<float>& Input_intensities1, float Epsilon1,   std::vector<cv::Vec4f> &Input_colors1, std::shared_ptr<cv::Mat> Image_normalized1);
  void set_output_positions(int Num_cols1,int Num_rows1);

  std::vector<float> compute_weights();
  std::vector<float> compute_new_interpolated_values(std::vector<float> &Weights);

  bool compute_interpolation(std::vector<float>& Results,std::string& Error);

protected:
  std::vector<cv::Vec4f> Input_colors;
  std::shared_ptr<cv::Mat> Image_normalized=nullptr;
};


#endif
