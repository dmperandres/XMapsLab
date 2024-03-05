/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "file_positions.h"

using namespace std;

/*************************************************************************/

int _file_positions::open(const string &File_name, _mode Mode)
{
  if (Mode==_mode::MODE_READ) File.open(File_name.c_str(),ios::in);
  if (Mode==_mode::MODE_WRITE) File.open(File_name.c_str(),ios::out);

  if (File.good()) return 1;
  else {
    cout << "Error: the file " << File_name << " cannot be opened" << endl;
    return 0;
  }
}

/*************************************************************************/

void _file_positions::get_token(istringstream &Line_stream1,string &Token1,char Separator)
{
  if (int(Line_stream1.tellg())<int(Line_stream1.str().length())){
    getline(Line_stream1,Token1,Separator);
    if (Token1[Token1.size()-1]=='\r') Token1.erase(Token1.size() - 1);
  }
  else{
    Token1="";
  }
}

/*************************************************************************/

bool _file_positions::get_new_line(fstream &File, istringstream &Line_stream)
{
  bool Line_empty=true;

  string Line;
  do{
    if (getline(File,Line)){
      // remove carriage return
      Line.erase(remove(Line.begin(),Line.end(),'\r'), Line.end());
      // remove tabs
      Line.erase(remove(Line.begin(),Line.end(),'\t'), Line.end());
      // remove black spaces at the beginning
//      Line.erase(remove(Line.begin(),Line.end(),' '), Line.end());
      if (Line.length()>0){
        Line_stream.str(Line);
        Line_stream.seekg(0);
        return true;
      }
    }
    else return false;
  } while (Line_empty==true);
  return false;
}

/*************************************************************************/

bool _file_positions::read(_pigment_data_ns::_positions_data &Positions_data, string &Error, string &Line, int &Position)
{
  string Text;

  string Token;
  istringstream Line_stream;
  setlocale(LC_ALL, "C");

  get_new_line(File,Line_stream);
  Position=1;
  Line=Line_stream.str()+'\n';
  get_token(Line_stream,Token,';');
  if (Token=="WIDTH"){
    get_token(Line_stream,Token,';');
    Positions_data.Width=stof(Token);

    get_new_line(File,Line_stream);
    Position++;
    Line=Line_stream.str()+'\n';

    get_token(Line_stream,Token,';');
    if (Token=="HEIGHT"){
      get_token(Line_stream,Token,';');
      Positions_data.Height=stof(Token);

      get_new_line(File,Line_stream);
      Position++;
      Line=Line_stream.str()+'\n';

      get_token(Line_stream,Token,';');
      if (Token=="NUM_SAMPLES"){
        get_token(Line_stream,Token,';');
        int Num_samples=stoi(Token);

        // read the X coordinates
        get_new_line(File,Line_stream);
        Position++;
        Line=Line_stream.str()+'\n';

        get_token(Line_stream,Token,';');
        if (Token=="X"){

          Positions_data.Vec_coordinate_x.resize(Num_samples);
          for (int i=0;i<Num_samples;i++){
            get_token(Line_stream,Token,';');
            Text=Token;
            replace(Text.begin(),Text.end(),',','.');
            Positions_data.Vec_coordinate_x[i]=stof(Text);
            if (Positions_data.Vec_coordinate_x[i]<0 || Positions_data.Vec_coordinate_x[i]>Positions_data.Width){
              Error="Error: the coordinate X is not in the range";
              return(false);
            }
          }

          get_new_line(File,Line_stream);
          Position++;
          Line=Line_stream.str()+'\n';

          get_token(Line_stream,Token,';');
          if (Token=="Y"){

            Positions_data.Vec_coordinate_y.resize(Num_samples);
            for (int i=0;i<Num_samples;i++){
              get_token(Line_stream,Token,';');
              Text=Token;
              replace(Text.begin(),Text.end(),',','.');
              Positions_data.Vec_coordinate_y[i]=stof(Text);
              if (Positions_data.Vec_coordinate_y[i]<0 || Positions_data.Vec_coordinate_y[i]>Positions_data.Height){
                Error="Error: the coordinate Y is not in the range";
                return(false);
              }
            }
          }
          else{
            Error="Error: No Y";
            return(false);
          }
        }
        else{
          Error="Error: No X";
          return(false);
        }
      }
      else{
        Error="Error: No NUM_SAMPLES";
        return(false);
      }
    }
    else{
      Error="Error: No HEIGHT";
      return(false);
    }
  }
  else{
    Error="Error: No WIDTH";
    return(false);
  }

  return(true);
}

/*************************************************************************/

//void _file_positions::write(_pigment_data_ns::_pigment_data &Positions_data, vector<_pigment_data_ns::_pigment_data> &Vec_element_data)
//{
//  int Num_samples=Positions_data.Num_samples;

//  setlocale(LC_ALL, "C");

//  string Text=QString("%1").arg(Positions_data.Version).toStdString();
//  File << "MAPLAB;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  if (Positions_data.File_format==_pigment_data_ns::_file_format::FILE_FORMAT_TXT) Text="TXT";
//  if (Positions_data.File_format==_pigment_data_ns::_file_format::FILE_FORMAT_BIN) Text="BIN";
//  File << "FILE_FORMAT;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  File << "AUTHOR;" << Positions_data.Author;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  File << "PROJECT_NAME;" << Positions_data.Project_name;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  File << "DATE;" << Positions_data.Date;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  if (Positions_data.Size_units==_pigment_data_ns::_units::UNITS_CM) Text="CM";
//  if (Positions_data.Size_units==_pigment_data_ns::_units::UNITS_MM) Text="MM";
//  if (Positions_data.Size_units==_pigment_data_ns::_units::UNITS_PX) Text="PX";
//  if (Positions_data.Size_units==_pigment_data_ns::_units::UNITS_N) Text="-";
//  File << "FILE_FORMAT;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  Text=QString("%1").arg(Positions_data.Width,6,'f').toStdString();
//  File << "WIDTH;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  Text=QString("%1").arg(Positions_data.Height,6,'f').toStdString();
//  File << "HEIGHT;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  if (Positions_data.Normalization==_pigment_data_ns::_normalization::NORMALIZATION_YES) Text="YES";
//  if (Positions_data.Normalization==_pigment_data_ns::_normalization::NORMALIZATION_NO) Text="NO";
//  File << "NORMALIZATION;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  if (Positions_data.CS_origin==_pigment_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT) Text="TOP_LEFT";
//  if (Positions_data.CS_origin==_pigment_data_ns::_cs_origin::CS_ORIGIN_BOTTOM_LEFT) Text="BOTTOM_LEFT";
//  File << "CS_ORIGIN;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  Text=QString("%1").arg(Positions_data.Num_samples).toStdString();
//  File << "NUM_SAMPLES;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  // coordinates
//  File << "X;-";
//  for (unsigned int i=0;i<Positions_data.Vec_coordinate_x.size();i++){
//    Text=QString("%1").arg(Positions_data.Vec_coordinate_x[i],6,'f').toStdString();
//    File << "; " << Text;
//  }
//  File << "\n";

//  File << "Y;-";
//  for (unsigned int i=0;i<Positions_data.Vec_coordinate_y.size();i++){
//    Text=QString("%1").arg(Positions_data.Vec_coordinate_y[i],6,'f').toStdString();
//    File << "; " << Text;
//  }
//  File << "\n";

//  // elements
//  for (unsigned int i=0;i<Vec_element_data.size();i++){
//    if (Vec_element_data[i].Data_type==_pigment_data_ns::_data_type::DATA_TYPE_XRF) Text="XRF";
//    if (Vec_element_data[i].Data_type==_pigment_data_ns::_data_type::DATA_TYPE_XRD) Text="XRD";
//    File << Text << "; ";

//    File << Vec_element_data[i].Name;
//    for (unsigned int j=0;j<Vec_element_data[i].Vec_samples.size();j++){
//      Text=QString("%1").arg(Vec_element_data[i].Vec_samples[j].Value,6,'f').toStdString();
//      File << "; " << Text;
//    }
//    File << "\n";
//  }
//}

/*************************************************************************/

void _file_positions::close()
{
  File.close();
}

