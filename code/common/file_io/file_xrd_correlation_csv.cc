//LIC

#include "file_xrd_correlation_csv.h"

//HEA
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

//HEA
// write the correlation values

void _file_xrd_correlation_csv::write(std::vector<std::string> &Vec_obs_names, std::vector<std::string> &Vec_pdb_names, std::vector<std::vector<_data_xrd_ns::_data_xrd_obs_pdb> > &Mat_xrd_obs_vs_pdb_data, std::vector<std::vector<_data_xrd_ns::_selection>> &Mat_xrd_obs_vs_pdb_data_selected)
{
  std::string Text;
  int R2;

  setlocale(LC_ALL, "C");

//  // now save the name of the visible PDB
//  File << "File name";
//  for (unsigned int Col=0;Col<Vec_xrd_visible_columns_in_table.size();Col++){
//    File << ";" << Vec_pdb_names[Vec_xrd_visible_columns_in_table[Col]];
//  }
//  File << "\n";

//  // now process all the OBS
//  for (unsigned int Row=0;Row<Vec_obs_names.size();Row++){
//    // first the obs name
//    File << Vec_obs_names[Row];
//    for (unsigned int Col=0;Col<Vec_xrd_visible_columns_in_table.size();Col++){
//      // the correlations
//      R2=int(roundf(powf(Mat_xrd_obs_vs_pdb_data[Row][Vec_xrd_visible_columns_in_table[Col]].Correlation_coefficient,2)*100.0f));
//      Text=QString("%1").arg(R2,2,10,QChar('0')).toStdString();
//      File << ";" << Text;
//    }
//    File << "\n";
//  }
}
