#include "file_xrd_obs_uxd.h"

//HEA

bool _file_xrd_obs_uxd::read(std::vector<float> &Vec_data, std::string &Error)
{
  std::string Text;
  std::string Token;
  std::vector<std::string>Tokens;
//  float Max=-1;
  float Step_size=1.0f/_data_xrd_ns::STEPS_2THETA;
  float Start_position;

  setlocale(LC_ALL, "C");

  // head
  try{
    for (int i=0;i<6;i++)
      get_new_line(File,Token);

    // stepsize
    get_new_line(File,Token);
    get_tokens(Token,'=',Tokens);
    Text=Tokens[1];
    replace(Text.begin(),Text.end(),',','.');
    Step_size=stof(Text);

    // start position
    get_new_line(File,Token);
    get_tokens(Token,'=',Tokens);
    Text=Tokens[1];
    replace(Text.begin(),Text.end(),',','.');
    Start_position=stof(Text);

    // COUNTS
    get_new_line(File,Token);

    // remove the data until reach the position 22
    Vec_data.resize((_data_xrd_ns::END_2THETA-_data_xrd_ns::START_2THETA)*_data_xrd_ns::STEPS_2THETA,0);
    int Position=0;
    float Position_2theta=Start_position;
    while (get_new_line(File,Token)){
      Position=int(roundf((Position_2theta-_data_xrd_ns::START_2THETA)*_data_xrd_ns::STEPS_2THETA));
      if (Position>=0 && Position<int(Vec_data.size())){
          Text=Token;
          replace(Text.begin(),Text.end(),',','.');
//          Value=stof(Text);
//          if (Value>Max) Max=Value;
//          Vec_data[Position]=Value;
          Vec_data[Position]=stof(Text);
      }

      Position_2theta=Position_2theta+Step_size;
    }
  }
  catch(std::exception const& Exception){
    Error="There was an error: "+std::string(Exception.what())+"in file "+File_name+'\n';
    return false;
  }

  return true;
}

//HEA

//void _file_xrd_obs_uxd::write(std::vector<float> &Vec_data)
//{
//  int Num_samples=Vec_data.Num_samples;

//  setlocale(LC_ALL, "C");


//  std::string Text=QString("%1").arg(Vec_data.Version).toStdString();
//  File << "MAPLAB;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  if (Vec_data.File_format==_project_data_ns::_file_format::FILE_FORMAT_TXT) Text="TXT";
//  if (Vec_data.File_format==_project_data_ns::_file_format::FILE_FORMAT_BIN) Text="BIN";
//  File << "FILE_FORMAT;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  File << "AUTHOR;" << Vec_data.Author;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  File << "PROJECT_NAME;" << Vec_data.Project_name;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  File << "DATE;" << Vec_data.Date;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  if (Vec_data.Size_units==_project_data_ns::_units::UNITS_CM) Text="CM";
//  if (Vec_data.Size_units==_project_data_ns::_units::UNITS_MM) Text="MM";
//  if (Vec_data.Size_units==_project_data_ns::_units::UNITS_PX) Text="PX";
//  if (Vec_data.Size_units==_project_data_ns::_units::UNITS_N) Text="-";
//  File << "FILE_FORMAT;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  Text=QString("%1").arg(Vec_data.Width,6,'f').toStdString();
//  File << "WIDTH;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  Text=QString("%1").arg(Vec_data.Height,6,'f').toStdString();
//  File << "HEIGHT;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  if (Vec_data.Normalization==_project_data_ns::_normalization::NORMALIZATION_YES) Text="YES";
//  if (Vec_data.Normalization==_project_data_ns::_normalization::NORMALIZATION_NO) Text="NO";
//  File << "NORMALIZATION;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  if (Vec_data.CS_origin==_project_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT) Text="TOP_LEFT";
//  if (Vec_data.CS_origin==_project_data_ns::_cs_origin::CS_ORIGIN_BOTTOM_LEFT) Text="BOTTOM_LEFT";
//  File << "CS_ORIGIN;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  Text=QString("%1").arg(Vec_data.Num_samples).toStdString();
//  File << "NUM_SAMPLES;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  // coordinates
//  File << "X;-";
//  for (unsigned int i=0;i<Vec_data.Vec_coordinate_x.size();i++){
//    Text=QString("%1").arg(Vec_data.Vec_coordinate_x[i],6,'f').toStdString();
//    File << "; " << Text;
//  }
//  File << "\n";

//  File << "Y;-";
//  for (unsigned int i=0;i<Vec_data.Vec_coordinate_y.size();i++){
//    Text=QString("%1").arg(Vec_data.Vec_coordinate_y[i],6,'f').toStdString();
//    File << "; " << Text;
//  }
//  File << "\n";

//  // elements
//  for (unsigned int i=0;i<Vec_element_data.size();i++){
//    if (Vec_element_data[i].Data_type==_project_data_ns::_data_type::DATA_TYPE_XRF) Text="XRF";
//    if (Vec_element_data[i].Data_type==_project_data_ns::_data_type::DATA_TYPE_XRD) Text="XRD";
//    File << Text << "; ";

//    File << Vec_element_data[i].Name;
//    for (unsigned int j=0;j<Vec_element_data[i].Vec_samples.size();j++){
//      Text=QString("%1").arg(Vec_element_data[i].Vec_samples[j].Value,6,'f').toStdString();
//      File << "; " << Text;
//    }
//    File << "\n";
//  }
//}
