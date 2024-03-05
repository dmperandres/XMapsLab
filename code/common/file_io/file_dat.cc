/*
* Prácticas de IG
* Copyright Domingo Martín Perandrés 2014-218
* dmartin@ugr.es
*
* GPL 3
*/

#include "file_dat.h"

using namespace std;

/*************************************************************************/

int _file_dat::open(const string &File_name, _mode Mode)
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

void _file_dat::get_token(istringstream &Line_stream1,string &Token1,char Separator)
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

bool _file_dat::get_new_line(fstream &File, istringstream &Line_stream)
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

bool _file_dat::read(_project_data_ns::_project_data &Project_data, vector<_data_xrf_ns::_element_data> &Vec_element_data, string &Error, string &Line, int &Position)
{
  int Value;
  string Text;

  string Token;
  istringstream Line_stream;
  setlocale(LC_ALL, "C");

  get_new_line(File,Line_stream);
  Position=1;
  Line=Line_stream.str()+'\n';
  get_token(Line_stream,Token,' ');
  if (Token=="MAPLAB"){ // the identifier of the format
    get_token(Line_stream,Token,' ');
    Project_data.Version=stoi(Token);

    get_new_line(File,Line_stream);
    Position++;
    Line=Line_stream.str()+'\n';

    get_token(Line_stream,Token,' ');
    if (Token=="FILE_FORMAT"){
      get_token(Line_stream,Token,' ');

      if (Token=="TXT" || Token=="BIN"){
        if (Token=="TXT") Project_data.File_format=_project_data_ns::_file_format::FILE_FORMAT_TXT;
        if (Token=="BIN") Project_data.File_format=_project_data_ns::_file_format::FILE_FORMAT_BIN;

        get_new_line(File,Line_stream);
        Position++;
        Line=Line_stream.str()+'\n';

        get_token(Line_stream,Token,' ');
        if (Token=="AUTHOR"){
          get_token(Line_stream,Token,' ');
          Project_data.Author=Token;
          get_new_line(File,Line_stream);
          Position++;
          Line=Line_stream.str()+'\n';

          get_token(Line_stream,Token,' ');
          if (Token=="PROJECT_NAME"){
            get_token(Line_stream,Token,' ');
            Project_data.Project_name=Token;

            get_new_line(File,Line_stream);
            Position++;
            Line=Line_stream.str()+'\n';

            get_token(Line_stream,Token,' ');
            if (Token=="DATE"){
              get_token(Line_stream,Token,' ');
              Project_data.Date=Token;

              get_new_line(File,Line_stream);
              Position++;
              Line=Line_stream.str()+'\n';

              get_token(Line_stream,Token,' ');
              if (Token=="SIZE_UNITS"){
                get_token(Line_stream,Token,' ');

                // units
                if (Token=="CM" || Token=="MM" || Token=="PX" || Token=="-"){

                  if (Token=="CM") Project_data.Size_units=_project_data_ns::_units::UNITS_CM;
                  if (Token=="MM") Project_data.Size_units=_project_data_ns::_units::UNITS_MM;
                  if (Token=="PX") Project_data.Size_units=_project_data_ns::_units::UNITS_PX;
                  if (Token=="-") Project_data.Size_units=_project_data_ns::_units::UNITS_N;

                  get_new_line(File,Line_stream);
                  Position++;
                  Line=Line_stream.str()+'\n';

                  get_token(Line_stream,Token,' ');
                  if (Token=="WIDTH"){
                    get_token(Line_stream,Token,' ');
                    Text=Token;
                    replace(Text.begin(),Text.end(),',','.');
                    Project_data.Width=stof(Text);

                    get_new_line(File,Line_stream);
                    Position++;
                    Line=Line_stream.str()+'\n';

                    get_token(Line_stream,Token,' ');
                    if (Token=="HEIGHT"){
                      get_token(Line_stream,Token,' ');
                      Text=Token;
                      replace(Text.begin(),Text.end(),',','.');
                      Project_data.Height=stof(Text);

                      get_new_line(File,Line_stream);
                      Position++;
                      Line=Line_stream.str()+'\n';

                      get_token(Line_stream,Token,' ');
                      if (Token=="NORMALIZATION"){
                        get_token(Line_stream,Token,' ');

                        if (Token=="YES" || Token=="NO"){
                          // type_data
                          if (Token=="YES") Project_data.Normalization=_project_data_ns::_normalization::NORMALIZATION_YES;
                          if (Token=="NO") Project_data.Normalization=_project_data_ns::_normalization::NORMALIZATION_NO;

                          get_new_line(File,Line_stream);
                          Position++;
                          Line=Line_stream.str()+'\n';

                          get_token(Line_stream,Token,' ');
                          if (Token=="CS_ORIGIN"){
                            get_token(Line_stream,Token,' ');

                            if (Token=="TOP_LEFT" || Token=="BOTTOM_LEFT"){
                              // horizontal_data_order
                              if (Token=="TOP_LEFT") Project_data.CS_origin=_project_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT;
                              if (Token=="BOTTOM_LEFT") Project_data.CS_origin=_project_data_ns::_cs_origin::CS_ORIGIN_BOTTOM_LEFT;

                              get_new_line(File,Line_stream);
                              Position++;
                              Line=Line_stream.str()+'\n';

                              get_token(Line_stream,Token,' ');
                              if (Token=="NUM_SAMPLES"){
                                get_token(Line_stream,Token,' ');
                                if (Token=="-") Project_data.Num_samples=-1;
                                else Project_data.Num_samples=stoi(Token);

                                // read the X coordinates
                                get_new_line(File,Line_stream);
                                Position++;
                                Line=Line_stream.str()+'\n';

                                get_token(Line_stream,Token,' ');
                                if (Token=="X"){
                                  // remove the space
                                  get_token(Line_stream,Token,' ');

                                  Project_data.Vec_coordinate_x.resize(Project_data.Num_samples);
                                  for (int i=0;i<Project_data.Num_samples;i++){
                                    get_token(Line_stream,Token,' ');
                                    Text=Token;
                                    replace(Text.begin(),Text.end(),',','.');
                                    Project_data.Vec_coordinate_x[i]=stof(Text);
                                    if (Project_data.Vec_coordinate_x[i]<0 || Project_data.Vec_coordinate_x[i]>Project_data.Width){
                                      Error="Error: the coordinate X is not in the range";
                                      return(false);
                                    }
                                  }

                                  get_new_line(File,Line_stream);
                                  Position++;
                                  Line=Line_stream.str()+'\n';

                                  get_token(Line_stream,Token,' ');
                                  if (Token=="Y"){
                                    get_token(Line_stream,Token,' ');

                                    Project_data.Vec_coordinate_y.resize(Project_data.Num_samples);
                                    for (int i=0;i<Project_data.Num_samples;i++){
                                      get_token(Line_stream,Token,' ');
                                      Text=Token;
                                      replace(Text.begin(),Text.end(),',','.');
                                      Project_data.Vec_coordinate_y[i]=stof(Text);
                                      if (Project_data.Vec_coordinate_y[i]<0 || Project_data.Vec_coordinate_y[i]>Project_data.Height){
                                        Error="Error: the coordinate Y is not in the range";
                                        return(false);
                                      }
                                    }

                                    // read the elements
                                    while (get_new_line(File,Line_stream)){                                      
                                      Position++;
                                      Line=Line_stream.str()+'\n';

                                      _data_xrf_ns::_element_data Element_data;

                                      get_token(Line_stream,Token,' ');
                                      if (Token=="XRF" || Token=="XRD"){

                                        if (Token=="XRF") Element_data.Data_type=_project_data_ns::_data_type::DATA_TYPE_XRF;
                                        else Element_data.Data_type=_project_data_ns::_data_type::DATA_TYPE_XRD;

                                        get_token(Line_stream,Token,' ');
                                        Element_data.Name=Token;

                                        // remove the black speaces before the text
                                        Element_data.Name.erase(remove(Element_data.Name.begin(),Element_data.Name.end(),' '), Element_data.Name.end());

                                        Element_data.Vec_samples.resize(Project_data.Num_samples);

                                        float Min_value=1e12;
                                        float Max_value=-1;

                                        for (int i=0;i<Project_data.Num_samples;i++){
                                          get_token(Line_stream,Token,' ');
                                          Text=Token;
                                          replace(Text.begin(),Text.end(),',','.');
                                          Value=stof(Text);
                                          if (Value<Min_value) Min_value=Value;
                                          if (Value>Max_value) Max_value=Value;
                                          Element_data.Vec_samples[i]=_data_xrf_ns::_data_sample(Project_data.Vec_coordinate_x[i],Project_data.Vec_coordinate_y[i],Value);
                                        }

                                        if (Min_value<Project_data.Min_value) Project_data.Min_value=Min_value;
                                        if (Max_value>Project_data.Max_value) Project_data.Max_value=Max_value;

                                        Element_data.Min_value=Min_value;
                                        Element_data.Max_value=Max_value;
                                        Element_data.Max_value_adjusted=Max_value;

                                        Vec_element_data.push_back(Element_data);
                                      }
                                      else{
                                        Error="Error: No XRF or XRD";
                                        return(false);
                                      }
                                    }

                                    return true;
      //                                      Error="File readed";

      //                                      QCryptographicHash Hash(QCryptographicHash::Keccak_256);
      //                                      Hash.addData(String.c_str(),String.size());
      //                                      cout << String << endl;
      //                                      cout << Hash.result().toHex().toStdString() << endl;
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
                                Error="Error: No NUM_RANDOM_SAMPLES";
                                return(false);
                              }
                            }
                            else{
                              Error="Error: No TOP_LEFT or BOTTOM_LEFT";
                              return(false);
                            }
                          }
                          else{
                            Error="Error: No CS_ORIGIN";
                            return(false);
                          }
                        }
                        else{
                          Error="Error: No YES or NO";
                          return(false);
                        }
                      }
                      else{
                          Error="Error: No NORMALIZATION";
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
                }
                else{
                  Error="Error: No CM or MM or PX or -";
                  return(false);
                }
              }
              else{
                Error="Error: No SIZE_UNITS";
                return(false);
              }
            }
            else{
              Error="Error: No DATE";
              return(false);
            }
          }
          else{
            Error="Error: No PROJECT_NAME";
            return(false);
          }
        }
        else{
          Error="Error: No AUTHOR";
          return(false);
        }
      }
      else{
        Error="Error: No TXT or BIN";
        return(false);
      }
    }
    else{
      Error="Error: No FILE_FORMAT";
      return(false);
    }
  }
  else{
    Error="Error: No MAPLAB";
    return(false);
  }
}

/*************************************************************************/

void _file_dat::write(_project_data_ns::_project_data &Project_data, vector<_data_xrf_ns::_element_data> &Vec_element_data)
{
  int Num_samples=Project_data.Num_samples;

  setlocale(LC_ALL, "C");

  string Text=QString("%1").arg(Project_data.Version).toStdString();
  File << "MAPLAB;" << Text;
  for (int i=0;i<Num_samples;i++) File << ";";
  File << "\n";

  if (Project_data.File_format==_project_data_ns::_file_format::FILE_FORMAT_TXT) Text="TXT";
  if (Project_data.File_format==_project_data_ns::_file_format::FILE_FORMAT_BIN) Text="BIN";
  File << "FILE_FORMAT;" << Text;
  for (int i=0;i<Num_samples;i++) File << ";";
  File << "\n";

  File << "AUTHOR;" << Project_data.Author;
  for (int i=0;i<Num_samples;i++) File << ";";
  File << "\n";

  File << "PROJECT_NAME;" << Project_data.Project_name;
  for (int i=0;i<Num_samples;i++) File << ";";
  File << "\n";

  File << "DATE;" << Project_data.Date;
  for (int i=0;i<Num_samples;i++) File << ";";
  File << "\n";

  if (Project_data.Size_units==_project_data_ns::_units::UNITS_CM) Text="CM";
  if (Project_data.Size_units==_project_data_ns::_units::UNITS_MM) Text="MM";
  if (Project_data.Size_units==_project_data_ns::_units::UNITS_PX) Text="PX";
  if (Project_data.Size_units==_project_data_ns::_units::UNITS_N) Text="-";
  File << "FILE_FORMAT;" << Text;
  for (int i=0;i<Num_samples;i++) File << ";";
  File << "\n";

  Text=QString("%1").arg(Project_data.Width,6,'f').toStdString();
  File << "WIDTH;" << Text;
  for (int i=0;i<Num_samples;i++) File << ";";
  File << "\n";

  Text=QString("%1").arg(Project_data.Height,6,'f').toStdString();
  File << "HEIGHT;" << Text;
  for (int i=0;i<Num_samples;i++) File << ";";
  File << "\n";

  if (Project_data.Normalization==_project_data_ns::_normalization::NORMALIZATION_YES) Text="YES";
  if (Project_data.Normalization==_project_data_ns::_normalization::NORMALIZATION_NO) Text="NO";
  File << "NORMALIZATION;" << Text;
  for (int i=0;i<Num_samples;i++) File << ";";
  File << "\n";

  if (Project_data.CS_origin==_project_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT) Text="TOP_LEFT";
  if (Project_data.CS_origin==_project_data_ns::_cs_origin::CS_ORIGIN_BOTTOM_LEFT) Text="BOTTOM_LEFT";
  File << "CS_ORIGIN;" << Text;
  for (int i=0;i<Num_samples;i++) File << ";";
  File << "\n";

  Text=QString("%1").arg(Project_data.Num_samples).toStdString();
  File << "NUM_SAMPLES;" << Text;
  for (int i=0;i<Num_samples;i++) File << ";";
  File << "\n";

  // coordinates
  File << "X;-";
  for (unsigned int i=0;i<Project_data.Vec_coordinate_x.size();i++){
    Text=QString("%1").arg(Project_data.Vec_coordinate_x[i],6,'f').toStdString();
    File << "; " << Text;
  }
  File << "\n";

  File << "Y;-";
  for (unsigned int i=0;i<Project_data.Vec_coordinate_y.size();i++){
    Text=QString("%1").arg(Project_data.Vec_coordinate_y[i],6,'f').toStdString();
    File << "; " << Text;
  }
  File << "\n";

  // elements
  for (unsigned int i=0;i<Vec_element_data.size();i++){
    if (Vec_element_data[i].Data_type==_project_data_ns::_data_type::DATA_TYPE_XRF) Text="XRF";
    if (Vec_element_data[i].Data_type==_project_data_ns::_data_type::DATA_TYPE_XRD) Text="XRD";
    File << Text << "; ";

    File << Vec_element_data[i].Name;
    for (unsigned int j=0;j<Vec_element_data[i].Vec_samples.size();j++){
      Text=QString("%1").arg(Vec_element_data[i].Vec_samples[j].Value,6,'f').toStdString();
      File << "; " << Text;
    }
    File << "\n";
  }
}
/*************************************************************************/

void _file_dat::close()
{
  File.close();
}

