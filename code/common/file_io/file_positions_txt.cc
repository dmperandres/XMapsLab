#include "file_positions_txt.h"
//#include "window_xmapslab.h"

//HEA

//bool _file_positions_txt::read(_project_data_ns::_project_data &Project_data,string &Error)
//{
//  std::string Text;
//  std::vector<string> Tokens;
//  std::string Token;

//  setlocale(LC_ALL, "C");

//  try{
//    // CS_origin
//    get_new_line(File,Token);
//    get_tokens(Token,';',Tokens);

//    if (Tokens[0]=="CS_ORIGIN"){
//      if (Tokens[1]!=""){
//        Text=Tokens[1];

//        if (Text==_project_data_ns::Vec_names_cs_origin[0] || Text==_project_data_ns::Vec_names_cs_origin[1]){
//          if (Text==_project_data_ns::Vec_names_cs_origin[0]) Project_data.CS_origin=_project_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT;
//          else Project_data.CS_origin=_project_data_ns::_cs_origin::CS_ORIGIN_BOTTOM_LEFT;
//          get_new_line(File,Token);
//          get_tokens(Token,';',Tokens);
//          Token=Tokens[0];

//          if (Token=="NUM_SAMPLES"){
//            if (Tokens[1]!=""){
//              Text=Tokens[1];
//              replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
//              Project_data.Num_samples=stoi(Text);

//              get_new_line(File,Token);
//              get_tokens(Token,';',Tokens);
//              Token=Tokens[0];

//              if (Token=="X"){
//                Project_data.Vec_coordinate_x_original.resize(Project_data.Num_samples,0.0f);
//                for (int i=0;i<Project_data.Num_samples;i++){
//                  Text=Tokens[i+1];
//                  if (Text!=""){
//                    replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
//                    Project_data.Vec_coordinate_x_original[i]=stof(Text);
//                  }
//                }

//                get_new_line(File,Token);
//                get_tokens(Token,';',Tokens);
//                Token=Tokens[0];

//                if (Token=="Y"){
//                  Project_data.Vec_coordinate_y_original.resize(Project_data.Num_samples,0.0);
//                  for (int i=0;i<Project_data.Num_samples;i++){
//                    Text=Tokens[i+1];
//                    if (Text!=""){
//                      replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
//                      Project_data.Vec_coordinate_y_original[i]=stof(Text);
//                    }
//                  }
//                }
//                else{ // NO Y
//                  Error="There is not 'Y' field in positions file";
//                  return false;
//                }
//              }
//              else{ // NO X
//                Error="There is not 'X' field in positions file";
//                return false;
//              }
//            }
//          }
//          else{ // NO NUM_SAMPLES
//            Error="There is not 'NUM_SAMPLES' field in positions file";
//            return false;
//          }
//        }
//        else{
//          Error="The value for 'CS_ORIGIN' is not 'TOP_LEFT' or 'BOTTOM_LEFT'";
//          return false;
//        }
//      }
//    }
//    else{
//      Error="There is not 'CS_ORIGIN' field in positions file";
//      return false;
//    }
//  }
//  catch(std::exception const& Exception){
//    Error="There was an error: "+string(Exception.what())+"in file "+File_name+'\n';
//    return false;
//  }

//  return true;
//}

bool _file_positions_txt::read(_project_data_ns::_project_data &Project_data,std::string &Error)
{
  std::string Text;
  std::vector<std::string> Tokens;
  std::string Token;
  std::vector<float> Vec_x_aux;
  std::vector<float> Vec_y_aux;

  setlocale(LC_ALL, "C");

  try{
    // CS_origin
    get_new_line(File,Token);
    get_tokens(Token,';',Tokens);

    if (Tokens[0]=="CS_ORIGIN"){
      if (Tokens[1]!=""){
        Text=Tokens[1];

        if (Text==_project_data_ns::Vec_names_cs_origin[0] || Text==_project_data_ns::Vec_names_cs_origin[1]){
          if (Text==_project_data_ns::Vec_names_cs_origin[0]) Project_data.CS_origin=_project_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT;
          else Project_data.CS_origin=_project_data_ns::_cs_origin::CS_ORIGIN_BOTTOM_LEFT;

          get_new_line(File,Token);
          get_tokens(Token,';',Tokens);
          Token=Tokens[0];

          if (Tokens[0]=="POS" && Tokens[1]=="X" && Tokens[2]=="Y"){


            while (get_new_line(File,Token)){
              get_tokens(Token,';',Tokens);

              Text=Tokens[1];
              if (Text!=""){
                replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
                Vec_x_aux.push_back(stof(Text));
              }

              Text=Tokens[2];
              if (Text!=""){
                replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
                Vec_y_aux.push_back(stof(Text));
              }
            }

            Project_data.Vec_coordinate_x_original=Vec_x_aux;
            Project_data.Vec_coordinate_y_original=Vec_y_aux;
          }
          else{ // NO POS,X,Y
            Error="There is not valid format. It must be 'POS;X;Y'";
            return false;
          }
        }
        else{
          Error="The value for 'CS_ORIGIN' is not 'TOP_LEFT' or 'BOTTOM_LEFT'";
          return false;
        }
      }
    }
    else{
      Error="There is not 'CS_ORIGIN' field in positions file";
      return false;
    }
  }
  catch(std::exception const& Exception){
    Error="There was an error: "+std::string(Exception.what())+"in file "+File_name+'\n';
    return false;
  }

  return true;
}


//HEA

//void _file_positions_txt::write(_project_data_ns::_project_data &Project_data)
//{
//  std::string Text;

//  setlocale(LC_ALL, "C");

//  std::string Origin;
//  if (Project_data.CS_origin==_project_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT) Origin=_project_data_ns::Vec_names_cs_origin[int(_project_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT)];
//  else Origin=_project_data_ns::Vec_names_cs_origin[int(_project_data_ns::_cs_origin::CS_ORIGIN_BOTTOM_LEFT)];
//  File << "CS_ORIGIN;" << Origin << endl;

//  File << "NUM_SAMPLES;" << std::to_string(int(Project_data.Num_samples)) << endl;
//  File << "X";
//  for (unsigned int i=0;i<Project_data.Vec_coordinate_x.size();i++){
//    Text=std::to_string(int(Project_data.Vec_coordinate_x[i]));
//    replace(Text.begin(),Text.end(),'.',',');
//    File << ";" << Text;
//  }
//  File << endl;

//  File << "Y";
//  for (unsigned int i=0;i<Project_data.Vec_coordinate_y.size();i++){
//    File << ";" << std::to_string(int(Project_data.Vec_coordinate_y[i]));
//  }
//  File << endl;
//}

void _file_positions_txt::write(_project_data_ns::_project_data &Project_data)
{
  std::string Text;

  setlocale(LC_ALL, "C");

  std::string Origin;
  if (Project_data.CS_origin==_project_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT) Origin=_project_data_ns::Vec_names_cs_origin[int(_project_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT)];
  else Origin=_project_data_ns::Vec_names_cs_origin[int(_project_data_ns::_cs_origin::CS_ORIGIN_BOTTOM_LEFT)];
  File << "CS_ORIGIN;" << Origin << std::endl;

  File << "POS;X;Y" << std::endl;

  for (unsigned int i=0;i<Project_data.Vec_coordinate_x.size();i++){
    File << std::to_string(i+1);

    Text=std::to_string(int(Project_data.Vec_coordinate_x[i]));
    replace(Text.begin(),Text.end(),'.',',');
    File << ";" << Text;

    Text=std::to_string(int(Project_data.Vec_coordinate_y[i]));
    replace(Text.begin(),Text.end(),'.',',');
    File << ";" << Text << std::endl;
  }
}

