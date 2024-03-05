#ifndef NEW_RBF_INTERPOLATION_2D
#define NEW_RBF_INTERPOLATION_2D

#include <vector>
#include <math.h>
#include <string>

#include <Eigen/Dense>

namespace _new_rbf_interpolation_2d_ns {

  // formulas from python RBF
  // https://docs.scipy.org/doc/scipy/reference/generated/scipy.interpolate.Rbf.html
  const std::vector<std::string> Vec_names_function={"Linear","Cubic","Quintic","Gaussian","Multiquadrics","Inverse Multiquadrics","Thin-plate"};
  const std::vector<std::string> Vec_short_names_function={"LIN","CUB","QUI","GAU","MQU","IMQ","TPL"};
  enum class _function_type:unsigned char{FUNCTION_TYPE_LINEAR, FUNCTION_TYPE_CUBIC, FUNCTION_TYPE_QUINTIC, FUNCTION_TYPE_GAUSSIAN, FUNCTION_TYPE_MULTIQUADRIC, FUNCTION_TYPE_INVERSE_MULTIQUADRIC, FUNCTION_TYPE_THIN_PLATE};

  const _function_type FUNCTION_TYPE_DEFAULT=_function_type::FUNCTION_TYPE_LINEAR;
}

class _new_rbf_interpolation_2d
{
public:

  _new_rbf_interpolation_2d(){};
  ~_new_rbf_interpolation_2d(){};

  void set_input_data(std::vector<float>& Input_coordinates_x1,std::vector<float>& Input_coordinates_y1, std::vector<float>& Input_intensities1,float Epsilon1);
  void set_output_positions(int Num_cols1,int Num_rows1);
  void set_function_type(_new_rbf_interpolation_2d_ns::_function_type Function_type1){Function_type=Function_type1;}

  float function(float Distance);

  std::vector<float> compute_weights();
  std::vector<float> compute_new_interpolated_values(std::vector<float> &Weights);
  bool compute_interpolation(std::vector<float>& Results,std::string& Error);

protected:
  int Num_input_positions=0;
  int Num_output_positions=0;

  int Num_rows;
  int Num_cols;

  std::vector<float> Input_coordinates_x;
  std::vector<float> Input_coordinates_y;
  std::vector<float> Input_intensities;

  std::vector<float> Output_coordinates_x;
  std::vector<float> Output_coordinates_y;
  std::vector<float> Output_intensities;

  _new_rbf_interpolation_2d_ns::_function_type Function_type=_new_rbf_interpolation_2d_ns::FUNCTION_TYPE_DEFAULT;

  float Epsilon;
};

#endif
