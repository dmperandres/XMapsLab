#include "file_info_txt.h"
//#include "window_xmapslab.h"

//HEA

bool _file_info_txt::read(_project_data_ns::_project_data &Project_data, std::string &Error)
{
  std::string Text;
  std::string Name;
  std::string Token;
  std::vector<std::string> Tokens;
  bool Result=true;

  setlocale(LC_ALL, "C");

  try{
    while (get_new_line(File,Token)){
      get_tokens(Token,';',Tokens);
      Token=Tokens[0];
      // convert to uppercase
      for (auto& c: Token) c = toupper(c);

      auto It=std::find(_file_info_txt_ns::Vec_allowed_words.begin(),_file_info_txt_ns::Vec_allowed_words.end(),Token);
      if (It!=_file_info_txt_ns::Vec_allowed_words.end()){
        switch(It-_file_info_txt_ns::Vec_allowed_words.begin()){
          case int(_file_info_txt_ns::_allowed_tokens::TOKEN_PROJECT_NAME):
            if (Tokens.size()>1 && Tokens[1]!=""){
              Project_data.Project_name=Tokens[1];
            }
            break;
          case int(_file_info_txt_ns::_allowed_tokens::TOKEN_AUTHOR):
            if (Tokens.size()>1 && Tokens[1]!=""){
              Project_data.Author=Tokens[1];
            }
            break;
          case int(_file_info_txt_ns::_allowed_tokens::TOKEN_DATE):
            if (Tokens.size()>1 && Tokens[1]!=""){
              Project_data.Date=Tokens[1];
            }
            break;
          case int(_file_info_txt_ns::_allowed_tokens::TOKEN_DEVICE):
            if (Tokens.size()>1 && Tokens[1]!=""){
              Project_data.Device=Tokens[1];
            }
            break;
          case int(_file_info_txt_ns::_allowed_tokens::TOKEN_TUBE):
            if (Tokens.size()>1 && Tokens[1]!=""){
              Project_data.Tube_type=_data_xrd_ns::_tube_type(stoi(Tokens[1]));
            }
            break;
          case int(_file_info_txt_ns::_allowed_tokens::TOKEN_XRF_DATA_ADJUSTMENT):
            if (Tokens.size()>1 && Tokens[1]!=""){
              Project_data.XRF_data_adjustment=_data_xrf_ns::_xrf_data_adjustment(stoi(Tokens[1]));
            }
            break;
          case int(_file_info_txt_ns::_allowed_tokens::TOKEN_WIDTH):
            if (Tokens.size()>1 && Tokens[1]!=""){
              Text=Tokens[1];
              replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
              Project_data.Width_original=stof(Text);
            }
            break;
          case int(_file_info_txt_ns::_allowed_tokens::TOKEN_HEIGHT):
            if (Tokens.size()>1 && Tokens[1]!=""){
              Text=Tokens[1];
              replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
              Project_data.Height_original=stof(Text);
            }
            break;
          default:
            break;
        }
      }
    }
  }
  catch(std::exception const& Exception){
    Error="There was an error: "+std::string(Exception.what())+"in file "+File_name+'\n';
    return false;
  }

  return Result;
}

//HEA

void _file_info_txt::write(_project_data_ns::_project_data &Project_data)
{
  std::string Text;

  setlocale(LC_ALL, "C");

  File << "PROJECT_NAME;" << Project_data.Project_name << std::endl;
  File << "AUTHOR;" << Project_data.Author << std::endl;
  File << "DATE;" << Project_data.Date << std::endl;
  File << "DEVICE;" << Project_data.Device << std::endl;
  File << "TUBE;" << _data_xrd_ns::Vec_tube_name[int(Project_data.Tube_type)].toStdString() << std::endl;
  File << "XRF_DATA_ADJUSTMENT;" << _data_xrf_ns::Vec_xrf_data_adjustment_name[int(Project_data.XRF_data_adjustment)].toStdString() << std::endl;

  Text=std::to_string(Project_data.Width);
  replace(Text.begin(),Text.end(),'.',',');
  File << "WIDTH;" << Text << std::endl;

  Text=std::to_string(Project_data.Height);
  replace(Text.begin(),Text.end(),'.',',');
  File << "HEIGHT;" << Text << std::endl;
}
