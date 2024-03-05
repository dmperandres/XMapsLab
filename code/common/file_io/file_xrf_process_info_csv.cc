#include "file_xrf_process_info_csv.h"

/*************************************************************************/

//bool _file_process_info_csv::read(std::vector<float> &Vec_data, std::string &Error)
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

/*************************************************************************/

void _file_xrf_process_info_csv::write(int Num_smooth_steps, int Num_subtract_noise_steps,float Start_kev, float Steps_kev, std::vector<float> &Vec_orig_data, std::vector<float> &Vec_smooth_data, std::vector<float> &Vec_subtract_noise_data, std::vector<float> &Vec_normalized_data)
{
  setlocale(LC_ALL, "C");

  File << "NUM_SMOOTH_STEPS;" << QString("%1").arg(Num_smooth_steps).toStdString() << "\n";
  File << "NUM_SUBTRACT_NOISE_STEPS;" << QString("%1").arg(Num_subtract_noise_steps).toStdString() << "\n";
  File << "KeV;ORIG_DATA;SMOOTH_DATA;SUBTRACT_NOISE_DATA;NORMALIZED_DATA\n";

  float KeV;
  for (size_t i=0;i<Vec_orig_data.size();i++){
    KeV=Start_kev+float(i)*Steps_kev;
    File << QString("%1").arg(KeV,6,'f').toStdString();
    File << ";" << QString("%1").arg(Vec_orig_data[i],6,'f').toStdString();
    File << ";" << QString("%1").arg(Vec_smooth_data[i],6,'f').toStdString();
    File << ";" << QString("%1").arg(Vec_subtract_noise_data[i],6,'f').toStdString();
    File << ";" << QString("%1").arg(Vec_normalized_data[i],6,'f').toStdString();
    File << "\n";
  }
}
