#ifndef RBF_INTERPOLATION_2D
#define RBF_INTERPOLATION_2D

#include <vector>
#include <math.h>
#include "rbf_interp_2d.h"

class _rbf_interpolation_2d
{
public:

  _rbf_interpolation_2d(){};
  ~_rbf_interpolation_2d();

  void set_input_data(std::vector<float> Coordinates_x1, std::vector<float> Coordinates_y1, std::vector<float> Intensities1);
  void set_output_positions(int Num_cols1,int Num_rows1);
  std::vector<float> compute_interpolation();


private:
  int Num_input_positions=0;
  int Num_output_positions=0;
  double *Intensities=nullptr;

  int Num_rows;
  int Num_cols;
  double *Input_XY_interlaced=nullptr;
  double *Output_XY_interlaced=nullptr;

  double R0;
};


#endif
