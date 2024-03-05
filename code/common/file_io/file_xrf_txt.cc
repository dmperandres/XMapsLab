#include "file_xrf_txt.h"

/*************************************************************************/

bool _file_xrf_txt::read(std::vector<_element_data_ns::_name_value> &Vec_data, std::string &Error)
{
  float Value;
  std::string Name;
  std::string Text;
  std::string Token;
  std::vector<std::string> Tokens;

  setlocale(LC_ALL, "C");

  try{
    while (get_new_line(File,Token)){
      get_tokens(Token,';',Tokens);
      Name=Tokens[0];

      Text=Tokens[1];
      replace(Text.begin(),Text.end(),',','.');
      Value=stof(Text);

      Vec_data.push_back({Name,Value});
    }
  }
  catch(std::exception const& Exception){
    Error="There was an error: "+std::string(Exception.what())+"in file "+File_name+'\n';
    return false;
  }

  return true;
}
