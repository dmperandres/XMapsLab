//LIC

#include "file_interpreted_csv.h"

//HEA
// read in the original values

bool _file_interpreted_csv::read(std::vector<_project_data_ns::_interpreted_data> &Vec_data,std::vector<std::string> &Vec_names_pdb, std::string &Error)
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
        Token.erase(std::remove(Token.begin(), Token.end(), ' '), Token.end());
        replace(Token.begin(),Token.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
        Vec_data[i].Vec_values.push_back(stof(Token));
      }
    }
  }
  catch(std::exception const& Exception){
    Error="There was an error: "+std::string(Exception.what())+"in file "+File_name+'\n';
    return false;
  }

  return Result;
}
