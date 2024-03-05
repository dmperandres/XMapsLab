/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "file_project_data_csv.h"

/*************************************************************************/
// read in the original values

bool _file_project_data_csv::read(_project_data_ns::_project_data &Project_data, std::vector<std::string> &Vec_xrf_pdb_names,std::vector<std::string> &Vec_xrd_pdb_names, std::string &Error)
{
  Q_UNUSED(Vec_xrf_pdb_names)
  Q_UNUSED(Vec_xrd_pdb_names)

  int Value;
  std::string Text;
  std::string Name;
  std::vector<std::string> Tokens;
  bool Result=true;
  std::string Token;
  float Real_value;
  float Max_value=0;

  setlocale(LC_ALL, "C");

  try{
    // first line must have XML for being valid
    get_new_line(File,Token);
    get_tokens(Token,';',Tokens);
    Token=Tokens[0];
    Token.erase(std::remove(Token.begin(), Token.end(), ' '), Token.end());
    for (auto & c: Token) c = toupper(c);
    if (Tokens.size()>1 && Token=="XML"){
      Project_data.Version=Tokens[1];

      while (get_new_line(File,Token)==true){
        //
        get_tokens(Token,';',Tokens);
        Token=Tokens[0];
        Token.erase(std::remove(Token.begin(), Token.end(), ' '), Token.end());
        // convert to uppercase
        for (auto & c: Token) c = toupper(c);

        auto It=std::find(_file_project_data_csv_ns::Vec_allowed_words.begin(),_file_project_data_csv_ns::Vec_allowed_words.end(),Token);
        if (It!=_file_project_data_csv_ns::Vec_allowed_words.end()){
          switch(It-_file_project_data_csv_ns::Vec_allowed_words.begin()){
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_PROJECT_NAME):
              if (Tokens.size()>1 && Tokens[1]!=""){
                Project_data.Project_name=Tokens[1];
              }
              break;
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_AUTHOR):
              if (Tokens.size()>1 && Tokens[1]!=""){
                Project_data.Author=Tokens[1];
              }
              break;
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_DATE):
              if (Tokens.size()>1 && Tokens[1]!=""){
                Project_data.Date=Tokens[1];
              }
              break;
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_DEVICE):
              if (Tokens.size()>1 && Tokens[1]!=""){
                Text=Tokens[1];
                Project_data.Device=Text;
              }
              else{
                Error="There is not DEVICE value";
                return false;
              }
              break;
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_TUBE):
              if (Tokens.size()>1 && Tokens[1]!=""){
                Text=Tokens[1];

                unsigned int i;
                for (i=0;i<_data_xrd_ns::Vec_tube_name.size();i++){
                  if (Text==_data_xrd_ns::Vec_tube_name[i].toStdString()) break;
                }

                if (i<_data_xrd_ns::Vec_tube_name.size()){
                  Project_data.XRD_tube_type=_data_xrd_ns::_tube_type(i);
                }
                else{
                  Error="The TUBE value must be "+_data_xrd_ns::Vec_tube_name[0].toStdString();
                  for (unsigned int i=1;i<_data_xrd_ns::Vec_tube_name.size();i++) Error=Error+" or "+_data_xrd_ns::Vec_tube_name[i].toStdString();
                  return false;
                }
              }
              else{
                Error="There is not TUBE value";
                return false;
              }
              break;
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_WIDTH_CM):
              if (Tokens.size()>1 && Tokens[1]!=""){
                Text=Tokens[1];
                replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
                Value=stof(Text);
                if (Value>=0) Project_data.Width_cm=Value;
                else{
                  Error="The WIDTH_CM is less than 0";
                  return false;
                }
              }
              else{
                Error="There is not WIDTH_CM value";
                return false;
              }
              break;
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_HEIGHT_CM):
              if (Tokens.size()>1 && Tokens[1]!=""){
                Text=Tokens[1];
                replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
                Value=stof(Text);
                if (Value>=0) Project_data.Height_cm=Value;
                else{
                  Error="The HEIGHT_CM is less than 0";
                  return false;
                }
              }
              else{
                Error="There is not HEIGHT_CM value";
                return false;
              }
              break;
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_CS_ORIGIN):
              if (Tokens.size()>1 && Tokens[1]!=""){
                Text=Tokens[1];

                if (Text==_project_data_ns::Vec_names_cs_origin[0] || Text==_project_data_ns::Vec_names_cs_origin[1]){
                  if (Text==_project_data_ns::Vec_names_cs_origin[0]) Project_data.CS_origin=_project_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT;
                  else Project_data.CS_origin=_project_data_ns::_cs_origin::CS_ORIGIN_BOTTOM_LEFT;
                }
                else{
                  Error="The CS_ORIGIN value must be TOP_LEFT or BOTTOM_LEFT";
                  return false;
                }
              }
              else{
                Error="There is not CS_ORIGIN value";
                return false;
              }
              break;
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_WIDTH_PIXEL):
              if (Tokens.size()>1 && Tokens[1]!=""){
                Text=Tokens[1];
                replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
                Value=stof(Text);
                if (Value>=0) Project_data.Width_original_pixel=Value;
                else{
                  Error="The WIDTH_PIXEL is less than 0";
                  return false;
                }
              }
              else{
                Error="There is not WIDTH_PIXEL value";
                return false;
              }
              break;
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_HEIGHT_PIXEL):
              if (Tokens.size()>1 && Tokens[1]!=""){
                Text=Tokens[1];
                replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
                Value=stof(Text);
                if (Value>=0) Project_data.Height_original_pixel=Value;
                else{
                  Error="The HEIGHT_PIXEL is less than 0";
                  return false;
                }
              }
              else{
                Error="There is not HEIGHT_PIXEL value";
                return false;
              }
              break;
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_X):
              Project_data.Vec_coordinate_x_original.resize(Tokens.size()-2,0.0f);
              for (unsigned int i=0;i<Project_data.Vec_coordinate_x_original.size();i++){
                if (Tokens[i+2]!=""){
                  Text=Tokens[i+2];
//                  replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
                  Value=stoi(Text);
                  if (Value>=0 && Value<Project_data.Width_original_pixel) Project_data.Vec_coordinate_x_original[i]=Value;
                  else{
                    Error="The coordinate X of position "+QString("%1").arg(i+1).toStdString()+" is not in the valid range";
                    return false;
                  }
                }
                else{
                  Error="There is not a valid X_coordinate value in position "+QString("%1").arg(i+1).toStdString();
                  return false;
                }
              }
              break;
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_Y):
              if (Tokens.size()-2>=Project_data.Vec_coordinate_x_original.size()){
                Project_data.Vec_coordinate_y_original.resize(Project_data.Vec_coordinate_x_original.size(),0.0f);
                for (unsigned int i=0;i<Project_data.Vec_coordinate_y_original.size();i++){
                  if (Tokens[i+2]!=""){
                    Text=Tokens[i+2];
//                    replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
                    Value=stoi(Text);
                    if (Value>=0 && Value<Project_data.Height_original_pixel) Project_data.Vec_coordinate_y_original[i]=Value;
                    else{
                      Error="The coordinate Y of position "+QString("%1").arg(i+1).toStdString()+" is not in the valid range";
                      return false;
                    }
                  }
                  else{
                    Error="There is not a valid Y_coordinate value in position "+QString("%1").arg(i+1).toStdString();
                    return false;
                  }
                }
              }
              else{// error
                Error="There number of Y coordinates is different of X coordinates";
                return false;
              }
              break;
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_XRF):
              {
                if (Tokens.size()>1 && Tokens[1]!=""){
                  Token=Tokens[1];
                  Token.erase(std::remove(Token.begin(), Token.end(), ' '), Token.end());
                  Name=Token;

                  // check if the name of the element exist in the PDB
//                  bool Found=false;
//                  if (Vec_xrf_pdb_names.size()>0){
//                    for (unsigned int i=0;i<Vec_xrf_pdb_names.size();i++){
//                      if (Vec_xrf_pdb_names[i]==Name){
//                        Found=true;
//                        break;
//                      }
//                    }
//                  }
//                  else Found=true;

//                  if (Found==true){
                    _project_data_ns::_interpreted_data Interpreted_data;

                    Interpreted_data.Name=Name;
                    for (unsigned int i=0;i<Tokens.size()-2;i++){
                      Text=Tokens[i+2];
                      replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
                      Real_value=stof(Text);
                      if (Real_value<0) Real_value=0;
                      if (Real_value>Max_value) Max_value=Real_value;
                      Interpreted_data.Vec_values.push_back(Real_value);
                    }

                    // fill with 0 up to the number of positions
                    for (unsigned int i=Tokens.size()-2;i<Project_data.Vec_coordinate_x_original.size();i++) Interpreted_data.Vec_values.push_back(0.0f);

                    Project_data.Vec_xrf_interpreted_data.push_back(Interpreted_data);
                    if (Project_data.Max_value<Max_value) Project_data.Max_value=Max_value;
//                  }
                }
                else{// error
                  Error="There is not an Element name (XRF)";
                  return false;
                }
              }
              break;
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_XRD):
              {
                if (Tokens.size()>1 && Tokens[1]!=""){
                  Token=Tokens[1];
                  Token.erase(std::remove(Token.begin(), Token.end(), ' '), Token.end());
                  Name=Token;

                  // check if the name of the compound exist in the PDB
//                  bool Found=false;
//                  if (Vec_xrd_pdb_names.size()>0){
//                    for (unsigned int i=0;i<Vec_xrd_pdb_names.size();i++){
//                      if (Vec_xrd_pdb_names[i]==Name){
//                        Found=true;
//                        break;
//                      }
//                    }
//                  }
//                  else Found=true;

//                  if (Found==true){
                    _project_data_ns::_interpreted_data Interpreted_data;

                    Interpreted_data.Name=Name;
                    for (unsigned int i=0;i<Tokens.size()-2;i++){
                      Text=Tokens[i+2];
                      replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
                      Real_value=stof(Text);
                      if (Real_value<0) Real_value=0;
                      if (Real_value>Max_value) Max_value=Real_value;
                      Interpreted_data.Vec_values.push_back(Real_value);
                    }

                    // fill with 0 up to the number of positions
                    for (unsigned int i=Tokens.size()-2;i<Project_data.Vec_coordinate_x_original.size();i++) Interpreted_data.Vec_values.push_back(0.0f);

                    Project_data.Vec_xrd_interpreted_data.push_back(Interpreted_data);
                    if (Project_data.Max_value<Max_value) Project_data.Max_value=Max_value;
//                  }
                }
                else{// error
                 Error="There is not a Compound name (XRD)";
                 return false;
                }
              }
              break;
            default:break;
          }
        }
      }
    }
    else{
      Error="The project file must have the XML version in the first line";
      return false;
    }
  }
  catch(std::exception const& Exception){
    Error="There was an error: "+std::string(Exception.what())+" in file "+File_name+'\n';
    return false;
  }

  return Result;
}

/*************************************************************************/
// write the final values

void _file_project_data_csv::write(_project_data_ns::_project_data &Project_data)
{
  std::string Text;

  setlocale(LC_ALL, "C");

  File << "XML;" << Project_data.Version << std::endl;
  File << "PROJECT_NAME;" << Project_data.Project_name << std::endl;
  File << "AUTHOR;" << Project_data.Author << std::endl;
  File << "DATE;" << Project_data.Date << std::endl;
  File << "DEVICE;" << Project_data.Device << std::endl;
  File << "TUBE;" << _data_xrd_ns::Vec_tube_name[int(Project_data.XRD_tube_type)].toStdString() << std::endl;

  Text=QString("%1").arg(int(Project_data.Width_cm)).toStdString();
  File << "WIDTH_CM;" << Text << "\n";
  Text=QString("%1").arg(int(Project_data.Height_cm)).toStdString();
  File << "HEIGHT_CM;" << Text << "\n";

  Text=QString("%1").arg(int(Project_data.Width_pixel)).toStdString();
  File << "WIDTH_PIXEL;" << Text << "\n";
  Text=QString("%1").arg(int(Project_data.Height_pixel)).toStdString();
  File << "HEIGHT_PIXEL;" << Text << "\n";

  if (Project_data.CS_origin==_project_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT){
    Text=_project_data_ns::Vec_names_cs_origin[int(_project_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT)];
  }
  else{
    Text=_project_data_ns::Vec_names_cs_origin[int(_project_data_ns::_cs_origin::CS_ORIGIN_BOTTOM_LEFT)];
  }
  File << "CS_ORIGIN;" << Text << "\n";

  // an auxilar field to show the positions
  File << "POSITION;-";
  for (unsigned int i=0;i<Project_data.Vec_coordinate_x.size();i++){
    Text=QString("%1").arg(i+1).toStdString();
    File << ";" << Text;
  }
  File << "\n";

//  Text=QString("%1").arg(int(Project_data.Num_samples)).toStdString();
//  File << "NUM_SAMPLES;" << Text << "\n";

  // coordinates
  File << "X;-";
  for (unsigned int i=0;i<Project_data.Vec_coordinate_x.size();i++){
    Text=QString("%1").arg(Project_data.Vec_coordinate_x[i]).toStdString();
    File << ";" << Text;
  }
  File << "\n";

  File << "Y;-";
  for (unsigned int i=0;i<Project_data.Vec_coordinate_y.size();i++){
    Text=QString("%1").arg(Project_data.Vec_coordinate_y[i]).toStdString();
    File << ";" << Text;
  }
  File << "\n";

  // elements
  for (unsigned int i=0;i<Project_data.Vec_xrf_interpreted_data.size();i++){
    File << "XRF;" ;

    File << Project_data.Vec_xrf_interpreted_data[i].Name;
    for (unsigned int j=0;j<Project_data.Vec_xrf_interpreted_data[i].Vec_values.size();j++){
      Text=QString("%1").arg(Project_data.Vec_xrf_interpreted_data[i].Vec_values[j],8,'f',6).toStdString();
      replace(Text.begin(),Text.end(),'.',_common_ns::GOAL_DECIMAL_SEPARATOR);
      File << ";" << Text;
    }

    // fill up to the number of positions
    for (unsigned int j=Project_data.Vec_xrf_interpreted_data[i].Vec_values.size();j<Project_data.Vec_coordinate_x.size();j++){
      File << ";0" ;
    }
    File << "\n";
  }

  // compounds
  for (unsigned int i=0;i<Project_data.Vec_xrd_interpreted_data.size();i++){
    File << "XRD;";

    File << Project_data.Vec_xrd_interpreted_data[i].Name;
    for (unsigned int j=0;j<Project_data.Vec_xrd_interpreted_data[i].Vec_values.size();j++){
      Text=QString("%1").arg(Project_data.Vec_xrd_interpreted_data[i].Vec_values[j],8,'f',6).toStdString();
      replace(Text.begin(),Text.end(),'.',_common_ns::GOAL_DECIMAL_SEPARATOR);
      File << ";" << Text;
    }

    // fill up to the number of positions
    for (unsigned int j=Project_data.Vec_xrd_interpreted_data[i].Vec_values.size();j<Project_data.Vec_coordinate_x.size();j++){
      File << ";0" ;
    }
    File << "\n";
  }
}
