/*
* Prácticas de IG
* Copyright Domingo Martín Perandrés 2014-218
* dmartin@ugr.es
*
* GPL 3
*/

#include "file_elements_weight.h"

using namespace std;

//******************************************************************************
//
//******************************************************************************

int _file_elements_weight::open(const string &File_name)
{
  File.open(File_name.c_str(),ios::in);

  if (File.good()) return 1;
  else {
    cout << "Error: the file " << File_name << " cannot be opened" << endl;
    return 0;
  }
}

//******************************************************************************
//
//******************************************************************************

void _file_elements_weight::get_token(istringstream &Line_stream1,string &Token1,char Delim)
{
  getline(Line_stream1,Token1,Delim);
  if (Token1[Token1.size()-1]=='\r') Token1.erase(Token1.size() - 1);
}

//******************************************************************************
//
//******************************************************************************

bool _file_elements_weight::get_new_line(ifstream &File,istringstream &Line_stream)
{
  bool Line_empty=true;

  string Line;
  do{
    if (getline(File,Line)){
      if (Line.length()>0){
        Line_stream.str(Line);
        Line_stream.seekg(0);
        return true;
      }
    }
    else return false;
  } while (Line_empty==true);
}


//******************************************************************************
//
//******************************************************************************

//void _file_elements_weight::read(std::vector<_element_data_ns::_data_element_weight> &Vec_elements_weight)
//{

//  string Token;
//  istringstream Line_stream;
////  unsigned int Pos;
//  setlocale(LC_ALL, "C");
//  _element_data_ns::_data_element_weight Data_elements_weight;

//  while(get_new_line(File,Line_stream)){
//    get_token(Line_stream,Token,':');
//    Data_elements_weight.Short_name=Token;
//    get_token(Line_stream,Token,':');
//    Data_elements_weight.Name=Token;
//    get_token(Line_stream,Token,' ');
//    Data_elements_weight.Atomical_weight=stof(Token);
//  }
//}

//******************************************************************************
//
//******************************************************************************

void _file_elements_weight::close()
{
  File.close();
}

