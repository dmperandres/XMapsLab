/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "file_xrd_data_xlsx.h"

using namespace QXlsx;

/*************************************************************************/

//bool _file_xrd_data_xlsx::read(std::vector<_project_data_ns::_xrd_data_data> &Vec_xrd_data_data, std::vector<std::string> &Vec_element_namess, std::string &Error)
//{
//  std::string Token;
//  std::string Text;
//  std::string Name;

//  CellRange Dimension=Table->dimension();

//  int Num_elements=Dimension.lastColumn();
//  int Num_positions=Dimension.rowCount()-1;

//  // read the name of the elemens
//  std::vector<bool> Vec_valid(Num_elements,false);

//  setlocale(LC_ALL, "C");

//  try{
//    for (int Col=1;Col<=Num_elements;Col++){
//      Name=read_cell(1,Col);

//      if (Vec_element_namess.size()>0){
//        if (Name!=""){
//          auto It=std::find(Vec_element_namess.begin(),Vec_element_namess.end(),Name);
//          if (It!=Vec_element_namess.end()){
//            Vec_xrd_data_data.push_back({Name,vector<float>(Num_positions,0.0f)});
//            Vec_valid[Col]=true;
//          }
//          else{
//            cout << "Warning: The element " << Name << " does not exists in the PDB" << endl;
//          }
//        }
//      }
//      else{
//        if (Name!=""){
//          Vec_xrd_data_data.push_back({Name,vector<float>(Num_positions,0.0f)});
//          Vec_valid[Col]=true;
//        }
//      }
//    }

//    int Row = 2;
//    int Pos_position=0;
//    while (Row<=Dimension.rowCount()){
//      int Pos_element=0;
//      for (int Col=1;Col<=Num_elements;Col++){
//        if (Vec_valid[Col]==true){
//          Token=read_cell(Row,Col);

//          if (Token!=""){
//            Token.erase(std::remove(Token.begin(), Token.end(), ' '), Token.end());
//            replace(Token.begin(),Token.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
//            Vec_xrd_data_data[Pos_element].Vec_values[Pos_position]=stof(Token);
//            Pos_element++;
//          }
//        }
//      }
//      Pos_position++;
//      Row++;
//    }
//  }
//  catch(std::exception const& Exception){
//    Error="There was an error: "+string(Exception.what())+"in file "+File_name+'\n';
//    return false;
//  }

//  return true;
//}

/*************************************************************************/

void _file_xrd_data_xlsx::write(std::vector<float> Vec_coordinates_obs, std::vector<float> Vec_coordinates_obs_normalized, std::vector<float> Vec_coordinates_pdb_normalized, std::vector<float> Vec_coordinates_sqrt)
{
  std::string Text;

  setlocale(LC_ALL, "C");

  Table->write(1,1,"OBS");
  Table->write(1,2,"OBS normalized");
  Table->write(1,3,"PDB normalized");
  Table->write(1,4,"SQRT");

  for (int Row=0;Row<int(Vec_coordinates_obs.size());Row++){
    Table->write(Row+2,1,QVariant(Vec_coordinates_obs[Row]));
    Table->write(Row+2,2,QVariant(Vec_coordinates_obs_normalized[Row]));
    Table->write(Row+2,3,QVariant(Vec_coordinates_pdb_normalized[Row]));
    Table->write(Row+2,4,QVariant(Vec_coordinates_sqrt[Row]));
  }

  Table->saveAs(QString::fromStdString(File_name));
}

