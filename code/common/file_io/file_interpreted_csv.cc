//LIC

#include "file_interpreted_csv.h"

//HEA
// read in the original values

bool _file_measured_csv::read(std::vector<_project_data_ns::_measured_data> &Vec_data,std::vector<std::string> &Vec_names_pdb, std::string &Error)
{
//  int Value;
  std::string Text;
  std::string Name;
  std::vector<std::string> Tokens;
  bool Result=true;
  std::string Token;
  std::vector<std::string> Vec_valid_names;
  std::vector<int> Vec_valid_columns;

  setlocale(LC_ALL, "C");

  try{
    // read the first line with the names of the elements/compounds
    get_new_line(File,Token);
    get_tokens(Token,';',Tokens);

    for (unsigned int i=0;i<Tokens.size();i++){
      Token=Tokens[i];
      Token.erase(std::remove(Token.begin(), Token.end(), ' '), Token.end());

      bool Found=false;
      if (Vec_names_pdb.size()>0){
        for (unsigned int i=0;i<Vec_names_pdb.size();i++){
          if (Vec_names_pdb[i]==Name){
            Found=true;
            break;
          }
        }
      }
      else Found=true;

      if (Found==true){
        Vec_valid_names.push_back(Token);
        Vec_valid_columns.push_back(i);
      }
    }

    // insert the names
    Vec_data.resize(Vec_valid_names.size());
    for (unsigned int i=0;i<Vec_valid_names.size();i++){
      Vec_data[i].Name=Vec_valid_names[i];
      Vec_data[i].Vec_values.clear();
    }


    // get the values;
    while (get_new_line(File,Token)==true){
      //
      get_tokens(Token,';',Tokens);
      for (unsigned int i=0;i<Vec_valid_columns.size();i++){
        Token=Tokens[Vec_valid_columns[i]];
        if (Token.size()>0){
          Token.erase(std::remove(Token.begin(), Token.end(), ' '), Token.end());
          replace(Token.begin(),Token.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
          Vec_data[i].Vec_values.push_back(stof(Token));
        }
        else
        Vec_data[i].Vec_values.push_back(0.0f);
      }
    }
  }
  catch(std::exception const& Exception){
    Error="There was an error: "+std::string(Exception.what())+"in file "+File_name+'\n';
    return false;
  }

  return Result;
}

//HEA
// write the final values

//void _file_interpreted_csv::write(_project_data_ns::_project_data &Project_data)
//{
//  std::string Text;

//  setlocale(LC_ALL, "C");

//  File << "PROJECT_NAME;" << Project_data.Project_name << endl;
//  File << "AUTHOR;" << Project_data.Author << endl;
//  File << "DATE;" << Project_data.Date << endl;
//  File << "DEVICE;" << Project_data.Device << endl;

//  Text=QString("%1").arg(int(Project_data.Width)).toStdString();
//  File << "WIDTH;" << Text << "\n";

//  Text=QString("%1").arg(int(Project_data.Height)).toStdString();
//  File << "HEIGHT;" << Text << "\n";

//  if (Project_data.CS_origin==_project_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT){
//    Text=_project_data_ns::Vec_names_cs_origin[int(_project_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT)];
//  }
//  else{
//    Text=_project_data_ns::Vec_names_cs_origin[int(_project_data_ns::_cs_origin::CS_ORIGIN_BOTTOM_LEFT)];
//  }
//  File << "CS_ORIGIN;" << Text << "\n";

//  Text=QString("%1").arg(int(Project_data.Num_samples)).toStdString();
//  File << "NUM_SAMPLES;" << Text << "\n";

//  // coordinates
//  File << "X;-";
//  for (int i=0;i<Project_data.Num_samples;i++){
//    Text=QString("%1").arg(Project_data.Vec_coordinate_x[i],6,'f',2).toStdString();
//    replace(Text.begin(),Text.end(),'.',',');
//    File << ";" << Text;
//  }
//  File << "\n";

//  File << "Y;-";
//  for (int i=0;i<Project_data.Num_samples;i++){
//    Text=QString("%1").arg(Project_data.Vec_coordinate_y[i],6,'f',2).toStdString();
//    replace(Text.begin(),Text.end(),'.',',');
//    File << ";" << Text;
//  }
//  File << "\n";

//  // elements
//  for (unsigned int i=0;i<Project_data.Vec_xrf_interpreted_data.size();i++){
//    File << "XRF;" ;

//    File << Project_data.Vec_xrf_interpreted_data[i].Name;
//    for (int j=0;j<Project_data.Num_samples;j++){
//      Text=QString("%1").arg(Project_data.Vec_xrf_interpreted_data[i].Vec_values[j],8,'f',6).toStdString();
//      replace(Text.begin(),Text.end(),'.',',');
//      File << "; " << Text;
//    }
//    File << "\n";
//  }

//  // elements
//  for (unsigned int i=0;i<Project_data.Vec_xrd_interpreted_data.size();i++){
//    File << "XRD;";

//    File << Project_data.Vec_xrd_interpreted_data[i].Name;
//    for (int j=0;j<Project_data.Num_samples;j++){
//      Text=QString("%1").arg(Project_data.Vec_xrd_interpreted_data[i].Vec_values[j],8,'f',6).toStdString();
//      replace(Text.begin(),Text.end(),'.',',');
//      File << "; " << Text;
//    }
//    File << "\n";
//  }
//}
