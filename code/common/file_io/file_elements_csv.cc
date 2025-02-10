#include "file_elements_csv.h"

//HEA

bool compare_function(_data_xrf_ns::_data_xrf_pdb &A,_data_xrf_ns::_data_xrf_pdb &B)
{
  if (A.Name<B.Name) return true;
  else return false;
}


bool _file_elements_csv::read(std::vector<_data_xrf_ns::_data_xrf_pdb> &Vec_xrf_pdb_data, std::string &Error)
{
  std::string Text;
  std::vector<std::string>Tokens;
  std::string Token;
  std::string Name;

  float ka1;
  float kb1;
  std::string Superposition;
  float kb_ka_ratio;

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
      replace(Token.begin(),Token.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
      ka1=stof(Token);

      Token=Tokens[2];
      replace(Token.begin(),Token.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
      kb1=stof(Token);

      Token=Tokens[3];
      replace(Token.begin(),Token.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
      kb_ka_ratio=stof(Token);

      Token=Tokens[4];
      remove(Token.begin(),Token.end(),' ');
      Superposition=Token;

      Vec_xrf_pdb_data.push_back({Name,ka1,kb1,kb_ka_ratio,Superposition});
    }
  }
  catch(std::exception const& Exception){
    Error="There was an error: "+std::string(Exception.what())+"in file "+File_name+'\n';
    return false;
  }

//  sort(Vec_element_data.begin(),Vec_element_data.end(),compare_function);

  return true;
}
