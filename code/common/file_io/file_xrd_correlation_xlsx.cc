/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "file_xrd_correlation_xlsx.h"

/*************************************************************************/
// read in the original values

//bool _file_xrd_correlation_csv::read(std::vector<std::string> &Vec_obs_names,std::vector<std::string> &Vec_pdb_names,std::vector<std::vector<int>> &Mat_correlations, std::string &Error)
//{
////  int Value;
//  string Text;
//  string Name;
//  std::vector<string> Tokens;
//  bool Result=true;
//  string Token;
//  std::vector<string> Vec_valid_names;
//  std::vector<int> Vec_valid_columns;

//  setlocale(LC_ALL, "C");

//  try{
//    // read the first line with the names of the elements/compounds
//    get_new_line(File,Token);
//    get_tokens(Token,';',Tokens);

//    for (unsigned int i=0;i<Tokens.size();i++){
//      Token=Tokens[i];
//      Token.erase(std::remove(Token.begin(), Token.end(), ' '), Token.end());

//      bool Found=false;
//      if (Vec_names_pdb.size()>0){
//        for (unsigned int i=0;i<Vec_names_pdb.size();i++){
//          if (Vec_names_pdb[i]==Name){
//            Found=true;
//            break;
//          }
//        }
//      }
//      else Found=true;

//      if (Found==true){
//        Vec_valid_names.push_back(Token);
//        Vec_valid_columns.push_back(i);
//      }
//    }

//    // insert the names
//    Vec_data.resize(Vec_valid_names.size());
//    for (unsigned int i=0;i<Vec_valid_names.size();i++){
//      Vec_data[i].Name=Vec_valid_names[i];
//      Vec_data[i].Vec_values.clear();
//    }

//    // get the values;
//    while (get_new_line(File,Token)==true){
//      //
//      get_tokens(Token,';',Tokens);
//      for (unsigned int i=0;i<Vec_valid_columns.size();i++){
//        Token=Tokens[Vec_valid_columns[i]];
//        Token.erase(std::remove(Token.begin(), Token.end(), ' '), Token.end());
//        replace(Token.begin(),Token.end(),',','.');
//        Vec_data[i].Vec_values.push_back(stof(Token));
//      }
//    }
//  }
//  catch(std::exception const& Exception){
//    Error="There was an error: "+string(Exception.what())+"in file "+File_name+'\n';
//    return false;
//  }

//  return Result;
//}

/*************************************************************************/
// write the correlation values

void _file_xrd_correlation_xlsx::write(std::vector<std::string> &Vec_obs_names, std::vector<std::string> &Vec_pdb_names, std::vector<bool> &Vec_xrd_visible_columns_in_table, std::vector<vector<_data_xrd_ns::_data_xrd_obs_pdb> > &Mat_xrd_obs_vs_pdb_data)
{
  string Text;
  int Row=1;
  int Col=1;
  int R2;

  setlocale(LC_ALL, "C");

  // now save the name of the visible PDB

  Table->write(Row,Col++,"File name");
  for (size_t i=0;i<Vec_xrd_visible_columns_in_table.size();i++){
    if (Vec_xrd_visible_columns_in_table[i]==true){
      Table->write(Row,Col++,QVariant(QString::fromStdString(Vec_pdb_names[i])));
    }
  }
  Row++;

  // now process all the OBS
  for (size_t i=0;i<Vec_obs_names.size();i++){
    // first the obs name
    Col=1,
    Table->write(Row,Col++,QVariant(QString::fromStdString(Vec_obs_names[i])));
    for (size_t j=0;j<Vec_xrd_visible_columns_in_table.size();j++){
      if (Vec_xrd_visible_columns_in_table[j]==true){
        // the correlations
        R2=int(roundf(powf(Mat_xrd_obs_vs_pdb_data[i][j].Correlation_coefficient,2)*100.0f));
        Table->write(Row,Col++,QVariant(QString("%1").arg(R2,2,10,QChar('0'))));
      }
    }
    Row++;
  }

  Table->saveAs(QString::fromStdString(File_name));
}
