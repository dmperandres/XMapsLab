/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "file_color_map_csv.h"

/*************************************************************************/
// read in the original values

bool _file_color_map_csv::read(std::vector<_vertex3f> &Vec_colors, std::string &Error)
{
  int Value;
  std::string Text1,Text2,Text3;
  std::string Name;
  std::vector<std::string> Tokens;
  bool Result=true;
  std::string Token;
  _vertex3f Color;

  setlocale(LC_ALL, "C");

  try{  
    while (get_new_line(File,Token)==true){
      //
      get_tokens(Token,';',Tokens);
      Text1=Tokens[0];
      replace(Text1.begin(),Text1.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
      Text2=Tokens[1];
      replace(Text2.begin(),Text2.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
      Text3=Tokens[2];
      replace(Text3.begin(),Text3.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);

      Vec_colors.push_back(_vertex3f(stof(Text1)*255.0f,stof(Text2)*255.0f,stof(Text3)*255.0f));
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

//void _file_project_data_csv::write(_project_data_ns::_project_data &Project_data)
//{
//  std::string Text;

//  setlocale(LC_ALL, "C");

//  File << "XML;" << Project_data.Version << std::endl;
//  File << "PROJECT_NAME;" << Project_data.Project_name << std::endl;
//  File << "AUTHOR;" << Project_data.Author << std::endl;
//  File << "DATE;" << Project_data.Date << std::endl;
//  File << "DEVICE;" << Project_data.Device << std::endl;
//  File << "TUBE;" << _data_xrd_ns::Vec_tube_name[int(Project_data.XRD_tube_type)].toStdString() << std::endl;

//  Text=QString("%1").arg(int(Project_data.Width_cm)).toStdString();
//  File << "WIDTH_CM;" << Text << "\n";
//  Text=QString("%1").arg(int(Project_data.Height_cm)).toStdString();
//  File << "HEIGHT_CM;" << Text << "\n";

//  Text=QString("%1").arg(int(Project_data.Width_pixel)).toStdString();
//  File << "WIDTH_PIXEL;" << Text << "\n";
//  Text=QString("%1").arg(int(Project_data.Height_pixel)).toStdString();
//  File << "HEIGHT_PIXEL;" << Text << "\n";

//  if (Project_data.CS_origin==_project_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT){
//    Text=_project_data_ns::Vec_names_cs_origin[int(_project_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT)];
//  }
//  else{
//    Text=_project_data_ns::Vec_names_cs_origin[int(_project_data_ns::_cs_origin::CS_ORIGIN_BOTTOM_LEFT)];
//  }
//  File << "CS_ORIGIN;" << Text << "\n";

//  // an auxilar field to show the positions
//  File << "POSITION;-";
//  for (unsigned int i=0;i<Project_data.Vec_coordinate_x.size();i++){
//    Text=QString("%1").arg(i+1).toStdString();
//    File << ";" << Text;
//  }
//  File << "\n";

////  Text=QString("%1").arg(int(Project_data.Num_samples)).toStdString();
////  File << "NUM_SAMPLES;" << Text << "\n";

//  // coordinates
//  File << "X;-";
//  for (unsigned int i=0;i<Project_data.Vec_coordinate_x.size();i++){
//    Text=QString("%1").arg(Project_data.Vec_coordinate_x[i]).toStdString();
//    File << ";" << Text;
//  }
//  File << "\n";

//  File << "Y;-";
//  for (unsigned int i=0;i<Project_data.Vec_coordinate_y.size();i++){
//    Text=QString("%1").arg(Project_data.Vec_coordinate_y[i]).toStdString();
//    File << ";" << Text;
//  }
//  File << "\n";

//  // elements
//  for (unsigned int i=0;i<Project_data.Vec_xrf_interpreted_data.size();i++){
//    File << "XRF;" ;

//    File << Project_data.Vec_xrf_interpreted_data[i].Name;
//    for (unsigned int j=0;j<Project_data.Vec_xrf_interpreted_data[i].Vec_values.size();j++){
//      Text=QString("%1").arg(Project_data.Vec_xrf_interpreted_data[i].Vec_values[j],8,'f',6).toStdString();
//      replace(Text.begin(),Text.end(),'.',_common_ns::GOAL_DECIMAL_SEPARATOR);
//      File << ";" << Text;
//    }

//    // fill up to the number of positions
//    for (unsigned int j=Project_data.Vec_xrf_interpreted_data[i].Vec_values.size();j<Project_data.Vec_coordinate_x.size();j++){
//      File << ";0" ;
//    }
//    File << "\n";
//  }

//  // compounds
//  for (unsigned int i=0;i<Project_data.Vec_xrd_interpreted_data.size();i++){
//    File << "XRD;";

//    File << Project_data.Vec_xrd_interpreted_data[i].Name;
//    for (unsigned int j=0;j<Project_data.Vec_xrd_interpreted_data[i].Vec_values.size();j++){
//      Text=QString("%1").arg(Project_data.Vec_xrd_interpreted_data[i].Vec_values[j],8,'f',6).toStdString();
//      replace(Text.begin(),Text.end(),'.',_common_ns::GOAL_DECIMAL_SEPARATOR);
//      File << ";" << Text;
//    }

//    // fill up to the number of positions
//    for (unsigned int j=Project_data.Vec_xrd_interpreted_data[i].Vec_values.size();j<Project_data.Vec_coordinate_x.size();j++){
//      File << ";0" ;
//    }
//    File << "\n";
//  }
//}
