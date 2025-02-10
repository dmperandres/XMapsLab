#include "file_xrd_process_info_csv.h"

//HEA

//bool _file_xrd_process_info_csv::read(std::vector<float> &Vec_data, std::string &Error)
//{

//  float Value;
//  string Text;
//  string Token;
//  std::vector<string>Tokens;
//  float Max=-1;

//  setlocale(LC_ALL, "C");

//  // head
//  try{
//    for (int i=0;i<7;i++) get_new_line(File,Token);

//    // remove the data until reach the position 22
//    Vec_data.resize((_data_xrd_ns::END_2THETA-_data_xrd_ns::START_2THETA)*_data_xrd_ns::STEPS_2THETA,0);
//    int Position1;
//    float Position_2theta;
//    // get the first position
//    get_new_line(File,Token);
//    get_tokens(Token,' ',Tokens);
//    Position_2theta=stof(Tokens[0]);
//    while(Position_2theta<22.0f){
//      get_new_line(File,Token);
//      get_tokens(Token,' ',Tokens);
//      Position_2theta=stof(Tokens[0]);
//    }

//    Position1=int((Position_2theta-22.0)*20.0f);
//    Text=Tokens[1];
//    replace(Text.begin(),Text.end(),',','.');
//    Value=stof(Text);
//    if (Value>Max) Max=Value;
//    Vec_data[Position1]=Value;
//    Position1++;

//    while(get_new_line(File,Token)){
//      get_tokens(Token,' ',Tokens);
//      if (Position1<560){
//        Text=Tokens[1];
//        replace(Text.begin(),Text.end(),',','.');
//        Value=stof(Text);
//        if (Value>Max) Max=Value;
//        Vec_data[Position1]=Value;
//        Position1++;
//      }
//    }
//  }
//  catch(std::exception const& Exception){
//    Error="There was an error: "+string(Exception.what())+"in file "+File_name+'\n';
//    return false;
//  }

//  return true;
//}

//HEA

void _file_xrd_process_info_csv::write(int Num_smooth_steps,int Num_subtract_noise_steps,float Start_2theta, float Steps_2theta, std::vector<float> &Vec_orig_data_obs,std::vector<float> &Vec_smooth_data_obs, std::vector<float> &Vec_subtract_noise_data_obs, std::vector<float> &Vec_normalized_data_obs,std::vector<float> &Vec_orig_data_pdb,std::vector<float> &Vec_smooth_data_pdb, std::vector<float> &Vec_subtract_noise_data_pdb, std::vector<float> &Vec_normalized_data_pdb,std::vector<float> Vec_sqrt_data)
{
  setlocale(LC_ALL, "C");

  File << "NUM_SMOOTH_STEPS;" << QString("%1").arg(Num_smooth_steps).toStdString() << "\n";
  File << "NUM_SUBTRACT_NOISE_STEPS;" << QString("%1").arg(Num_subtract_noise_steps).toStdString() << "\n";
  File << "2Theta;OBS_ORIG;OBS_SMOOTH;OBS_SUBTRACT_NOISE;OBS_NORMALIZED;PDB_ORIG;PDB_SMOOTH;PDB_SUBTRACT_NOISE;PDB_NORMALIZED;SQRT(PDB_OBS)\n";

  float Two_theta;
  for (size_t i=0;i<Vec_orig_data_obs.size();i++){
    Two_theta=Start_2theta+float(i)/Steps_2theta;
    File << QString("%1").arg(Two_theta,6,'f').toStdString();
    File << ";" << QString("%1").arg(Vec_orig_data_obs[i],6,'f').toStdString();
    File << ";" << QString("%1").arg(Vec_smooth_data_obs[i],6,'f').toStdString();
    File << ";" << QString("%1").arg(Vec_subtract_noise_data_obs[i],6,'f').toStdString();
    File << ";" << QString("%1").arg(Vec_normalized_data_obs[i],6,'f').toStdString();
    File << ";" << QString("%1").arg(Vec_orig_data_pdb[i],6,'f').toStdString();
    File << ";" << QString("%1").arg(Vec_smooth_data_pdb[i],6,'f').toStdString();
    File << ";" << QString("%1").arg(Vec_subtract_noise_data_pdb[i],6,'f').toStdString();
    File << ";" << QString("%1").arg(Vec_normalized_data_pdb[i],6,'f').toStdString();
    File << ";" << QString("%1").arg(Vec_sqrt_data[i],6,'f').toStdString();
    File << "\n";
  }
}
