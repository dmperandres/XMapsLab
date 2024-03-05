#include "file_interpreted_txt.h"

using namespace std;

/*************************************************************************/

bool _file_interpreted_txt::read(std::vector<_pigment_data_ns::_pair_name_value> &Vec_data, string &Error)
{
  float Value;
  string Name;
  string Text;
  string Token;
  vector<string> Tokens;

  setlocale(LC_ALL, "C");

  try{
    while (get_new_line(File,Token)){
      get_tokens(Token,';',Tokens);
      if (Tokens.size()>1 && Tokens[0]!=""){
        Name=Tokens[0];
      }
      else Name="";

      if (Tokens.size()>1 && Tokens[1]!=""){
        Text=Tokens[1];
        replace(Text.begin(),Text.end(),',','.');
        Value=stof(Text);
      }
      else Value=-1;

      Vec_data.push_back({Name,Value});
    }
  }
  catch(std::exception const& Exception){
    Error="There was an error: "+string(Exception.what())+"in file "+File_name+'\n';
    return false;
  }

  return(true);
}

/*************************************************************************/

//void _file_interpreted_txt::write(vector<float> &Vec_data)
//{
//  int Num_samples=Vec_data.Num_samples;

//  setlocale(LC_ALL, "C");

//  string Text=QString("%1").arg(Vec_data.Version).toStdString();
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
