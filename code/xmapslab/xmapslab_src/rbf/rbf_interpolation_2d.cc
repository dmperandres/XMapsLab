 #include "rbf_interpolation_2d.h"


_rbf_interpolation_2d::~_rbf_interpolation_2d()
{
  delete[] Intensities;
  delete[] Input_XY_interlaced;
  delete[] Output_XY_interlaced;
}

//HEA

void _rbf_interpolation_2d::set_input_data(std::vector<float> Coordinates_x1,std::vector<float> Coordinates_y1,std::vector<float> Intensities1)
{
  if (Num_input_positions!=int(Coordinates_x1.size())){
    delete[] Intensities;
    delete[] Input_XY_interlaced;
  }

  Num_input_positions=Coordinates_x1.size();


  Intensities= new double[Num_input_positions];
  Input_XY_interlaced=new double[Num_input_positions*2];

  for (int i=0;i<Num_input_positions;i++){
    Input_XY_interlaced[i*2]=double(Coordinates_x1[i]);
    Input_XY_interlaced[i*2+1]=double(Coordinates_y1[i]);

    Intensities[i]=double(Intensities1[i]);
  }

  double Max_x=1e-10;
  double Min_x=1e10;
  double Max_y=1e-10;
  double Min_y=1e10;
  double Volume=0;
  double e=0;


  for (unsigned int i=0;i<Coordinates_x1.size();i++){
    if (double(Coordinates_x1[i])>Max_x) Max_x=double(Coordinates_x1[i]);
    if (double(Coordinates_x1[i])<Min_x) Min_x=double(Coordinates_x1[i]);

    if (double(Coordinates_y1[i])>Max_y) Max_y=double(Coordinates_y1[i]);
    if (double(Coordinates_y1[i])<Min_y) Min_y=double(Coordinates_y1[i]);


  }

  // compute the Area
  Volume = ( Max_x - Min_x ) * ( Max_y - Min_y );

  // computes r0
  e = 1.0 / double(2);
  R0 = pow (Volume/Num_input_positions,e);

  std::cout << "r0=" << R0 << std::endl;
}

//HEA

void _rbf_interpolation_2d::set_output_positions(int Num_cols1, int Num_rows1)
{
  if (Num_cols!=Num_cols1 || Num_rows!=Num_rows1){
    delete[] Output_XY_interlaced;
  }

  Num_cols=Num_cols1;
  Num_rows=Num_rows1;

  Output_XY_interlaced=new double[Num_cols*Num_rows*2];

  int Pos = 0;
  for (int Row=0;Row<Num_rows;Row++){
    for (int Col=0;Col<Num_cols;Col++){
      Output_XY_interlaced[Pos*2] = double(Col)/ double(Num_cols - 1);
      Output_XY_interlaced[Pos*2+1] = double(Row)/ double(Num_rows - 1);
      Pos = Pos + 1	;
    }
  }
}

//HEA

std::vector<float> _rbf_interpolation_2d::compute_interpolation()
{
  double *Weights;
  double *Results_d;

  // computes the weights of the radial functions
  Weights=rbf_weight(2,Num_input_positions, Input_XY_interlaced,R0, phi5_a, Intensities);

  // computes the interpolation values
  // m=2
  // nd, xyd, w are are the input
  // ni, xyi are the results
  Results_d=rbf_interp(2,Num_input_positions,Input_XY_interlaced,R0,phi5,Weights,Num_cols*Num_rows,Output_XY_interlaced);

  std::vector<float> Results(Num_cols*Num_rows);

  for (int i=0;i<Num_cols*Num_rows;i++){
    Results[i]=float(Results_d[i]);
  }

  return Results;
}
