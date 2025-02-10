#include "file_xrd_process_info_xlsx.h"

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

void _file_xrd_process_info_xlsx::write(int Num_smooth_steps,int Num_subtract_noise_steps,float Start_2theta, float Steps_2theta, std::vector<float> &Vec_orig_data_obs,std::vector<float> &Vec_smooth_data_obs, std::vector<float> &Vec_subtract_noise_data_obs, std::vector<float> &Vec_normalized_data_obs,std::vector<float> &Vec_orig_data_pdb,std::vector<float> &Vec_smooth_data_pdb, std::vector<float> &Vec_subtract_noise_data_pdb, std::vector<float> &Vec_normalized_data_pdb,std::vector<float> Vec_sqrt_data)
{
  string Text;
  int Row=1;
  setlocale(LC_ALL, "C");

  Table->write(Row,1,"NUM_SMOOTH_STEPS");
  Table->write(Row,2,QVariant(Num_smooth_steps));
  Row++;

  Table->write(Row,1,"NUM_SUBTRACT_NOISE_STEPS");
  Table->write(Row,2,QVariant(Num_subtract_noise_steps));
  Row++;

  Table->write(Row,1,"2THETA");
  Table->write(Row,2,"OBS_ORIG");
  Table->write(Row,3,"OBS_SMOOTH");
  Table->write(Row,4,"OBS_SUBTRACT_NOISE");
  Table->write(Row,5,"OBS_NORMALIZED");
  Table->write(Row,6,"PDB_ORIG");
  Table->write(Row,7,"PDB_SMOOTH");
  Table->write(Row,8,"PDB_SUBTRACT");
  Table->write(Row,9,"PDB_NORMALIZED");
  Table->write(Row,10,"SQRT(PDB_OBS)");
  Row++;

  float Two_theta;
  int Col;
  for (size_t i=0;i<Vec_orig_data_obs.size();i++){
    Col=1;
    Two_theta=Start_2theta+float(i)/Steps_2theta;
    Table->write(Row,Col++,QVariant(Two_theta));
    Table->write(Row,Col++,QVariant(Vec_orig_data_obs[i]));
    Table->write(Row,Col++,QVariant(Vec_smooth_data_obs[i]));
    Table->write(Row,Col++,QVariant(Vec_subtract_noise_data_obs[i]));
    Table->write(Row,Col++,QVariant(Vec_normalized_data_obs[i]));
    Table->write(Row,Col++,QVariant(Vec_orig_data_pdb[i]));
    Table->write(Row,Col++,QVariant(Vec_smooth_data_pdb[i]));
    Table->write(Row,Col++,QVariant(Vec_subtract_noise_data_pdb[i]));
    Table->write(Row,Col++,QVariant(Vec_normalized_data_pdb[i]));
    Table->write(Row,Col++,QVariant(Vec_sqrt_data[i]));
    Row++;
  }

  Table->saveAs(QString::fromStdString(File_name));
}
