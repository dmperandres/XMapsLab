#include "file_compound_combination_csv.h"

/*************************************************************************/

bool _file_compound_combination_csv::read(std::vector<_data_xrf_ns::_data_compound_from_elements_pdb> &Vec_data_compounds_combination_pdb, std::string &Error)
{
  std::string Text;
  std::vector<std::string>Tokens;
  std::vector<std::string> Tokens_aux;
  std::string Token;
  std::string Name;

  setlocale(LC_ALL, "C");

  try{
    // the line with names of columns
    get_new_line(File,Token);

    while (get_new_line(File,Token)){
      get_tokens(Token,';',Tokens);
      Token=Tokens[0];
      remove(Token.begin(),Token.end(),' ');
      Name=Token;

      Token=Tokens[1];
      get_tokens(Token,',',Tokens);

      std::vector<_data_xrf_ns::_data_element_num_atoms> Vec_elements_combination;
      for (unsigned int i=0;i<Tokens.size();i++){
        Token=Tokens[i];
        // get the name and the number
        get_tokens(Token,':',Tokens_aux);

        Vec_elements_combination.push_back({Tokens_aux[0],stoi(Tokens_aux[1])});
      }

      Vec_data_compounds_combination_pdb.push_back({Name,Vec_elements_combination});
    }
  }
  catch(std::exception const& Exception){
    Error="There was an error: "+std::string(Exception.what())+"in file "+File_name+'\n';
    return false;
  }

//  sort(Vec_element_data.begin(),Vec_element_data.end(),compare_function);

  return true;
}
