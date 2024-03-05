#include "file_info_csv.h"
#include "window.h"

using namespace std;

/*************************************************************************/

bool _file_info_csv::read(_project_data_ns::_project_data &Project_data, string &Error)
{
  string Text;
  string Name;
  string Token;
  vector<string> Tokens;
  bool Result=true;

  setlocale(LC_ALL, "C");

  try{
    while (get_new_line(File,Token)){
      get_tokens(Token,';',Tokens);
      Token=Tokens[0];
      // convert to uppercase
      for (auto& c: Token) c = toupper(c);

      auto It=std::find(_file_info_csv_ns::Vec_allowed_words.begin(),_file_info_csv_ns::Vec_allowed_words.end(),Token);
      if (It!=_file_info_csv_ns::Vec_allowed_words.end()){
        switch(It-_file_info_csv_ns::Vec_allowed_words.begin()){
          case int(_file_info_csv_ns::_allowed_tokens::TOKEN_PROJECT_NAME):
            if (Tokens.size()>1 && Tokens[1]!=""){
              Project_data.Project_name=Tokens[1];
            }
            break;
          case int(_file_info_csv_ns::_allowed_tokens::TOKEN_AUTHOR):
            if (Tokens.size()>1 && Tokens[1]!=""){
              Project_data.Author=Tokens[1];
            }
            break;
          case int(_file_info_csv_ns::_allowed_tokens::TOKEN_DATE):
            if (Tokens.size()>1 && Tokens[1]!=""){
              Project_data.Date=Tokens[1];
            }
            break;
          case int(_file_info_csv_ns::_allowed_tokens::TOKEN_DEVICE):
            if (Tokens.size()>1 && Tokens[1]!=""){
              Project_data.Device=Tokens[1];
            }
            break;
          default:
            break;
        }
      }
    }
  }
  catch(std::exception const& Exception){
    Error="There was an error: "+string(Exception.what())+"in file "+File_name+'\n';
    return false;
  }

  return Result;
}

/*************************************************************************/

void _file_info_csv::write(_project_data_ns::_project_data &Project_data)
{
  setlocale(LC_ALL, "C");

  File << "PROJECT_NAME;" << Project_data.Project_name << endl;
  File << "AUTHOR;" << Project_data.Author << endl;
  File << "DATE;" << Project_data.Date << endl;
  File << "DEVICE;" << Project_data.Device << endl;
}
