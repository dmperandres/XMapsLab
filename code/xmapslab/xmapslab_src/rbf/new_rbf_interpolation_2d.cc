#include "new_rbf_interpolation_2d.h"

//HEA
// Load the input data
// Computes the largest distance and computes the mean for Epsilon
// It should be changed by the user

void _new_rbf_interpolation_2d::set_input_data(std::vector<float> &Input_coordinates_x1, std::vector<float> &Input_coordinates_y1, std::vector<float>& Input_intensities1,float Epsilon1)
{
  Input_coordinates_x=Input_coordinates_x1;
  Input_coordinates_y=Input_coordinates_y1;
  Input_intensities=Input_intensities1;
  Epsilon=Epsilon1;

//  // compute the max distance for each coordinate
//  float Max_x=1e-10;
//  float Min_x=1e10;
//  float Max_y=1e-10;
//  float Min_y=1e10;
//  float Area;

//  for (unsigned int i=0;i<Input_coordinates_x.size();i++){
//    if (Input_coordinates_x[i]>Max_x) Max_x=Input_coordinates_x[i];
//    if (Input_coordinates_x[i]<Min_x) Min_x=Input_coordinates_x[i];
//    if (Input_coordinates_y[i]>Max_y) Max_y=Input_coordinates_y[i];
//    if (Input_coordinates_y[i]<Min_y) Min_y=Input_coordinates_y[i];
//  }

////  Area=(Max_x-Min_x)*(Max_y-Min_y);
//  Area=sqrtf(powf(Max_x-Min_x,2)+powf(Max_y-Min_y,2));

//  Epsilon=Area/float(Input_coordinates_x.size());
}


//HEA
// Compute the positions where the new values must be computed
// They are the positions in a grid (the output image)
// The values are normalized

void _new_rbf_interpolation_2d::set_output_positions(int Num_cols1, int Num_rows1)
{
  Output_coordinates_x.resize(Num_cols1*Num_rows1);
  Output_coordinates_y.resize(Num_cols1*Num_rows1);

  int Pos = 0;
  for (int Row=0;Row<Num_rows1;Row++){
    for (int Col=0;Col<Num_cols1;Col++){
      Output_coordinates_x[Pos] = float(Col)/ float(Num_cols1 - 1);
      Output_coordinates_y[Pos] = float(Row)/ float(Num_rows1 - 1);
      Pos = Pos + 1	;
    }
  }
}


//HEA
// The RBF function

float _new_rbf_interpolation_2d::function(float Distance)
{
  float Result=0;

  switch (Function_type) {
  case _new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_LINEAR:
    Result=Distance;
    break;
  case _new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_CUBIC:
    Result=powf(Distance,3);
    break;
  case _new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_QUINTIC:
    Result=powf(Distance,5);
    break;
  case _new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_GAUSSIAN:
    Result=exp(-powf(Distance/Epsilon,2));
    break;
  case _new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_MULTIQUADRIC:
    Result=sqrtf(powf(Distance/Epsilon,2)+1.0f);
    break;
  case _new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_INVERSE_MULTIQUADRIC:
    Result=1.0f/sqrtf(powf(Distance/Epsilon,2)+1.0f);
    break;
  case _new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_THIN_PLATE:
    Result=Distance*Distance*log(Distance);
    break;
  default:
    break;
  }

  return Result;
}

//HEA
// Compute the new intensity values given the weights and the input and output positions

std::vector<float>_new_rbf_interpolation_2d::compute_new_interpolated_values(std::vector<float>& Weights)
{
  std::vector<float> Output_intensities(Output_coordinates_x.size(),0.0f);

  float x;
  float y;
  float Value;
  for (unsigned int i=0;i<Output_coordinates_x.size();i++){
    Value=0;
    for (unsigned int j=0;j<Input_coordinates_x.size();j++){
      // compute the distance between the new point and the input one
      x=Output_coordinates_x[i]-Input_coordinates_x[j];
      y=Output_coordinates_y[i]-Input_coordinates_y[j];
      //
      Value=Value+Weights[j]*function(sqrtf((x*x)+(y*y)));
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

std::vector<float> _new_rbf_interpolation_2d::compute_weights()
{
  Eigen::MatrixXf A(Input_coordinates_x.size(),Input_coordinates_x.size());
  Eigen::VectorXf b(Input_coordinates_x.size());
  std::vector<float> Vec_result(Input_coordinates_x.size(),0.0f);
  float x;
  float y;

  for (unsigned int Row=0;Row<Input_coordinates_x.size();Row++){
      for (unsigned int Col=0;Col<Input_coordinates_x.size();Col++){
        x=Input_coordinates_x[Row]-Input_coordinates_x[Col];
        y=Input_coordinates_y[Row]-Input_coordinates_y[Col];
        A(Row,Col)=function(sqrtf((x*x)+(y*y)));
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

bool _new_rbf_interpolation_2d::compute_interpolation(std::vector<float>& Results,std::string& Error)
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
