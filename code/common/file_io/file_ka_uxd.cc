#include "file_ka_uxd.h"
#include "file_xrd_pdb_txt.h"

//HEA

bool _file_ka_uxd::read(std::vector<float> &Vec_data, float& Step_size, float& Start_position, std::string &Error)
{

  float Value;
  std::string Text;
  std::string Token;
  std::vector<std::string>Tokens;

  setlocale(LC_ALL, "C");

  try{
    // the line with names of columns
    // head
    for (int i=0;i<6;i++)
      get_new_line(File,Token);

    // stepsize
    get_new_line(File,Token);
    get_tokens(Token,'=',Tokens);
    Text=Tokens[1];
    replace(Text.begin(),Text.end(),',','.');
    Step_size=stof(Text);

    // start position
    get_new_line(File,Token);
    get_tokens(Token,'=',Tokens);
    Text=Tokens[1];
    replace(Text.begin(),Text.end(),',','.');
    Start_position=stof(Text);

    // COUNTS
    get_new_line(File,Token);

    // data
    Vec_data.resize(560,0);
    int Position1=0;
    float Position_2theta=Start_position;
    while (get_new_line(File,Token)){
      if (Position_2theta>=22.0f){
        if (Position1<560){
          Text=Token;
          replace(Text.begin(),Text.end(),',','.');
          Value=stof(Text);
          Vec_data[Position1]=Value;
          Position1++;
        }
      }
      else{
        Position_2theta=Position_2theta+Step_size;
      }
    }
  }
  catch(std::exception const& Exception){
    Error="There was an error: "+std::string(Exception.what())+"in file "+File_name+'\n';
    return false;
  }

  return true;
}
