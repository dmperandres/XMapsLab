#include "file_ka_txt.h"

using namespace std;

/*************************************************************************/

int _file_ka_txt::open(const string &File_name,_mode Mode)
{

  if (Mode==_mode::MODE_READ) File.open(File_name.c_str(),ios::in);
  if (Mode==_mode::MODE_WRITE) File.open(File_name.c_str(),ios::out);

  if (File.good()) return 1;
  else return 0;
}

/*************************************************************************/

void _file_ka_txt::close()
{
  File.close();
}

/*************************************************************************/

void _file_ka_txt::get_token(istringstream &Line_stream1,string &Token1,char Separator)
{
//  cout << "str= " << Line_stream1.str() << " leng=" << Line_stream1.tellg() << endl;

  if (int(Line_stream1.tellg())<int(Line_stream1.str().length())){
    getline(Line_stream1,Token1,Separator);
    if (Token1[Token1.size()-1]=='\r') Token1.erase(Token1.size() - 1);
  }
  else{
    Token1="";
  }
}

/*************************************************************************/

bool _file_ka_txt::get_new_line(fstream &File,istringstream &Line_stream)
{
  bool Line_empty=true;

  string Line;
  do{
    if (getline(File,Line)){
      // remove carriage return
      Line.erase(remove(Line.begin(),Line.end(),'\r'), Line.end());
      // remove black spaces at the beginning
      Line.erase(remove(Line.begin(),Line.end(),' '), Line.end());
			// remove tabs
//      Line.erase(remove(Line.begin(),Line.end(),'\t'), Line.end());
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

bool _file_ka_txt::read(vector<float> &Vec_data, string &Error, string &Line, int &Position)
{
  float Value;
  string Text;

  string Token;
  istringstream Line_stream;
  setlocale(LC_ALL, "C");

  // head
  for (int i=0;i<7;i++)
    get_new_line(File,Line_stream);

  // data
  Vec_data.resize(586,0);
  Position=6;
  while (get_new_line(File,Line_stream)){    
    Line=Line_stream.str()+'\n';
    get_token(Line_stream,Token,'\t');
    get_token(Line_stream,Token,'\t');
    Text=Token;
    replace(Text.begin(),Text.end(),',','.');
    Value=stof(Text);
    Vec_data[Position]=Value;
    Position++;

//    cout << "Value=" << Value << endl;
  }
//  cout << "Position=" << Position << endl;
  return(true);
}

/*************************************************************************/

void _file_ka_txt::write(vector<float> &Vec_data)
{
//  int Num_samples=Vec_data.Num_samples;

//  setlocale(LC_ALL, "C");

//  string Text=QString("%1").arg(Vec_data.Version).toStdString();
//  File << "MAPLAB;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  if (Vec_data.File_format==_project_data_ns::_file_format::FILE_FORMAT_TXT) Text="TXT";
//  if (Vec_data.File_format==_project_data_ns::_file_format::FILE_FORMAT_BIN) Text="BIN";
//  File << "FILE_FORMAT;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  File << "AUTHOR;" << Vec_data.Author;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  File << "PROJECT_NAME;" << Vec_data.Project_name;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  File << "DATE;" << Vec_data.Date;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  if (Vec_data.Size_units==_project_data_ns::_units::UNITS_CM) Text="CM";
//  if (Vec_data.Size_units==_project_data_ns::_units::UNITS_MM) Text="MM";
//  if (Vec_data.Size_units==_project_data_ns::_units::UNITS_PX) Text="PX";
//  if (Vec_data.Size_units==_project_data_ns::_units::UNITS_N) Text="-";
//  File << "FILE_FORMAT;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  Text=QString("%1").arg(Vec_data.Width,6,'f').toStdString();
//  File << "WIDTH;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  Text=QString("%1").arg(Vec_data.Height,6,'f').toStdString();
//  File << "HEIGHT;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  if (Vec_data.Normalization==_project_data_ns::_normalization::NORMALIZATION_YES) Text="YES";
//  if (Vec_data.Normalization==_project_data_ns::_normalization::NORMALIZATION_NO) Text="NO";
//  File << "NORMALIZATION;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  if (Vec_data.CS_origin==_project_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT) Text="TOP_LEFT";
//  if (Vec_data.CS_origin==_project_data_ns::_cs_origin::CS_ORIGIN_BOTTOM_LEFT) Text="BOTTOM_LEFT";
//  File << "CS_ORIGIN;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  Text=QString("%1").arg(Vec_data.Num_samples).toStdString();
//  File << "NUM_SAMPLES;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  // coordinates
//  File << "X;-";
//  for (unsigned int i=0;i<Vec_data.Vec_coordinate_x.size();i++){
//    Text=QString("%1").arg(Vec_data.Vec_coordinate_x[i],6,'f').toStdString();
//    File << "; " << Text;
//  }
//  File << "\n";

//  File << "Y;-";
//  for (unsigned int i=0;i<Vec_data.Vec_coordinate_y.size();i++){
//    Text=QString("%1").arg(Vec_data.Vec_coordinate_y[i],6,'f').toStdString();
//    File << "; " << Text;
//  }
//  File << "\n";

//  // elements
//  for (unsigned int i=0;i<Vec_element_data.size();i++){
//    if (Vec_element_data[i].Data_type==_project_data_ns::_data_type::DATA_TYPE_XRF) Text="XRF";
//    if (Vec_element_data[i].Data_type==_project_data_ns::_data_type::DATA_TYPE_XRD) Text="XRD";
//    File << Text << "; ";

//    File << Vec_element_data[i].Name;
//    for (unsigned int j=0;j<Vec_element_data[i].Vec_samples.size();j++){
//      Text=QString("%1").arg(Vec_element_data[i].Vec_samples[j].Value,6,'f').toStdString();
//      File << "; " << Text;
//    }
//    File << "\n";
//  }
}
