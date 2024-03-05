/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "file_positions_csv.h"

/*************************************************************************/
// read in the original values

bool _file_positions_csv::read(_project_data_ns::_project_data &Project_data, std::string &Error)
{
//  int Value;
  std::string Text;
  std::string Name;
  std::vector<std::string> Tokens;
  bool Result=true;
  std::string Token;
  std::vector<std::string> Vec_valid_names;
  std::vector<int> Vec_valid_columns; 
  float Width1;
  float Height1;
  float Value;
  int Position;

  setlocale(LC_ALL, "C");

  try{
    // read the first line with the names of the elements/compounds
    get_new_line(File,Token);
    get_tokens(Token,';',Tokens);
    Token=Tokens[0];
    Token.erase(std::remove(Token.begin(), Token.end(), ' '), Token.end());
    for (auto & c: Token) c = toupper(c);

    if (Tokens.size()>1 && Token=="WIDTH"){
      Token=Tokens[1];
      Token.erase(std::remove(Token.begin(), Token.end(), ' '), Token.end());
      replace(Token.begin(),Token.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
      Width1=stof(Token);
      if (Width1<=0){
        Error="The 'WIDTH' value is wrong";
        return false;
      }

      get_new_line(File,Token);
      get_tokens(Token,';',Tokens);
      Token=Tokens[0];
      Token.erase(std::remove(Token.begin(), Token.end(), ' '), Token.end());
      for (auto & c: Token) c = toupper(c);
      if (Tokens.size()>1 && Token=="HEIGHT"){
        Token=Tokens[1];
        Token.erase(std::remove(Token.begin(), Token.end(), ' '), Token.end());
        replace(Token.begin(),Token.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
        Height1=stof(Token);
        if (Height1<=0){
          Error="The 'HEIGHT' value is wrong";
          return false;
        }

        // get the auxiliar line
        get_new_line(File,Token);

        // read the data
        Project_data.Vec_coordinate_x_original.clear();
        Project_data.Vec_coordinate_y_original.clear();

        while (get_new_line(File,Token)==true){
          get_tokens(Token,';',Tokens);
          if (Tokens.size()>=3){
            // Position
            Token=Tokens[0];
            Token.erase(std::remove(Token.begin(), Token.end(), ' '), Token.end());
            replace(Token.begin(),Token.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
            Position=stoi(Token);

            // X
            Token=Tokens[1];
            Token.erase(std::remove(Token.begin(), Token.end(), ' '), Token.end());
            replace(Token.begin(),Token.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
            Value=stof(Token);
            if (Value<0 || Value>Width1){
              Error="The 'X' value of position "+std::to_string(Position)+"is wrong";
              return false;
            }
            Project_data.Vec_coordinate_x_original.push_back(Value*Project_data.Width_original_pixel/Width1);

            // Y
            Token=Tokens[2];
            Token.erase(std::remove(Token.begin(), Token.end(), ' '), Token.end());
            replace(Token.begin(),Token.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
            Value=stof(Token);
            if (Value<0 || Value>Height1){
              Error="The 'Y' value of position "+std::to_string(Position)+"is wrong";
              return false;
            }
            Project_data.Vec_coordinate_y_original.push_back(Value*Project_data.Height_original_pixel/Height1);
          }
        }
      }
      else{
        Error="The 'HEIGHT' field must be in the second line";
        return false;
      }
    }
    else{
      Error="The 'WIDTH' field must be in the first line";
      return false;
    }
  }
  catch(std::exception const& Exception){
    Error="There was an error: "+std::string(Exception.what())+"in file "+File_name+'\n';
    return false;
  }

  return Result;
}

/*************************************************************************/
// write the final values

//void _file_positions_csv::write(_project_data_ns::_project_data &Project_data)
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
