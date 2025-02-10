#include "new_rbf_interpolation_2d_plus.h"

//HEA
// Load the input data
// Computes the largest distance and computes the mean for Epsilon
// It should be changed by the user

void _new_rbf_interpolation_2d_plus::set_input_data(std::vector<float> &Input_coordinates_x1, std::vector<float> &Input_coordinates_y1, std::vector<float>& Input_intensities1, float Epsilon1, std::vector<cv::Vec4f> &Input_colors1, std::shared_ptr<cv::Mat> Image_normalized1)
{
  Input_coordinates_x=Input_coordinates_x1;
  Input_coordinates_y=Input_coordinates_y1;
  Input_colors=Input_colors1;
  Input_intensities=Input_intensities1;
  Epsilon=Epsilon1;
  Image_normalized=Image_normalized1;
}

//HEA
// Compute the positions where the new values must be computed
// They are the positions in a grid (the output image)
// The values are normalized

void _new_rbf_interpolation_2d_plus::set_output_positions(int Num_cols1, int Num_rows1)
{
  Output_coordinates_x.resize(Num_cols1*Num_rows1);
  Output_coordinates_y.resize(Num_cols1*Num_rows1);

  int Pos = 0;
  for (int Row=0;Row<Num_rows1;Row++){
    for (int Col=0;Col<Num_cols1;Col++){
      Output_coordinates_x[Pos] = float(Col)/ float(Num_cols1 - 1);
      Output_coordinates_y[Pos] = float(Row)/ double(Num_rows1 - 1);
      Pos = Pos + 1	;
    }
  }
}

//HEA
// Compute the new intensity values given the weights and the input and output positions

std::vector<float>_new_rbf_interpolation_2d_plus::compute_new_interpolated_values(std::vector<float>& Weights)
{
  std::vector<float> Output_intensities(Output_coordinates_x.size(),0.0f);

  float x;
  float y;
  float r;
  float g;
  float b;
  float Value;
  cv::Vec4f Color_input;
  cv::Vec4f Color_output;
  for (unsigned int i=0;i<Output_coordinates_x.size();i++){
    Value=0;
    Color_output=Image_normalized->at<cv::Vec4f>(i);
    for (unsigned int j=0;j<Input_coordinates_x.size();j++){
      Color_input=Input_colors[j];
      // compute the distance between the new point and the input one
      x=Output_coordinates_x[i]-Input_coordinates_x[j];
      y=Output_coordinates_y[i]-Input_coordinates_y[j];
      r=Color_output[0]-Color_input[0];
      g=Color_output[1]-Color_input[1];
      b=Color_output[2]-Color_input[2];
      //
      Value=Value+Weights[j]*function(sqrtf((x*x)+(y*y)+(r*r)+(g*g)+(b*b)));
    }
    if (Value<0) Value=0;

    Output_intensities[i]=Value;
  }

  return Output_intensities;
}


//HEA
// This is the important part. There is a Radial function centered in each input position, as the extension is infinite, each
// function contributes to all the other ones. But we want that the total contribution of all the radial functions in each point
// must match the measure value. Than implies that the weight of each radial function must be compute to comply with all the conditions.
// That produces an equation system that must be resolved. In the previous version I used an old code. No I have implemented it using
// Eigen library.
// It is important to note that even if the imput positions are in a 2D grid, for example, 4x4, what we have to comply are 16 conditions,
// so the A matrix must be of 16x16 and we have 16 input intensities.
// | 1 2 |
// | 3 4 |
//
// A=
// | RBF(1-1) RBF(1-2) RBF(1-3) RBF(1-4) | | W1 |  | I1 |
// | RBF(2-1) RBF(2-2) RBF(2-3) RBF(2-4) | | W2 |  | I2 |
// | RBF(3-1) RBF(3-2) RBF(3-3) RBF(3-4) |x| W3 |= | I3 |
// | RBF(4-1) RBF(4-2) RBF(4-3) RBF(4-4) | | W4 |  | I4 |
//
// Once the weights are computed, the new intensities are computed for any new position NP
// Inp=(NP-P1)*W1+(NP-P2)*W2+(NP-P3)*W3+(NP-P4)*W4

std::vector<float> _new_rbf_interpolation_2d_plus::compute_weights()
{
  Eigen::MatrixXf A(Input_coordinates_x.size(),Input_coordinates_x.size());
  Eigen::VectorXf b(Input_coordinates_x.size());
  std::vector<float> Vec_result(Input_coordinates_x.size(),0.0f);
  float x;
  float y;
  float R;
  float G;
  float B;

  for (unsigned int Row=0;Row<Input_coordinates_x.size();Row++){
      for (unsigned int Col=0;Col<Input_coordinates_x.size();Col++){
        x=Input_coordinates_x[Row]-Input_coordinates_x[Col];
        y=Input_coordinates_y[Row]-Input_coordinates_y[Col];
        R=Input_colors[Row][0]-Input_colors[Col][0];
        G=Input_colors[Row][1]-Input_colors[Col][1];
        B=Input_colors[Row][2]-Input_colors[Col][2];

        A(Row,Col)=function(sqrtf((x*x)+(y*y)+(R*R)+(G*G)+(B*B)));
      }
    }

  for (unsigned int Row=0;Row<Input_coordinates_x.size();Row++) b(Row)=Input_intensities[Row];

  // resolve the system
  Eigen::VectorXf x_vec = A.colPivHouseholderQr().solve(b);

  for (unsigned int Row=0;Row<Input_coordinates_x.size();Row++) Vec_result[Row]=x_vec[Row];

  return Vec_result;
}

//HEA
// General function

bool _new_rbf_interpolation_2d_plus::compute_interpolation(std::vector<float>& Results,std::string& Error)
{
  if ((Function_type==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_GAUSSIAN || Function_type==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_MULTIQUADRIC || Function_type==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_INVERSE_MULTIQUADRIC) && Epsilon==0){
      Error="Error: The mean distance between positions is 0";
      return false;
  }

  // computes the weights of the radial functions
  std::vector<float> Weights=compute_weights();

  // computes the interpolation values
  Results=compute_new_interpolated_values(Weights);

  return true;
}
