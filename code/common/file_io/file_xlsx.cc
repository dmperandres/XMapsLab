//LIC

#include "file_xlsx.h"

using namespace std;
using namespace QXlsx;

//HEA

int _file_xlsx::open(const string &File_name,_mode Mode)
{

  if (Mode==_mode::MODE_READ){
    Table=new QXlsx::Document(QString::fromStdString(File_name));
  }
//  if (Mode==_mode::MODE_WRITE) File.open(File_name.c_str(),ios::out);

  if (Table->load()) return 1;
  else return 0;
}

//HEA

string _file_xlsx::read_cell(int Row, int Col)
{
  QVariant Var;
  string Token;
  Cell* Cell;

  Cell=Table->cellAt(Row,Col);
  if (Cell!=nullptr){
    Var=Cell->readValue();
    Token=Var.toString().toStdString();
    Token.erase(std::remove(Token.begin(), Token.end(), ' '), Token.end());
  }
  return Token;
}

//HEA

bool _file_xlsx::read(_project_data_ns::_project_data &Project_data,std::vector<std::string> &Vec_element_names,std::string &Error)
{
  string Token;
  string Text;
  string Name;
  float Value;

  CellRange Dimension=Table->dimension();

  int Num_elements=Dimension.lastColumn();
  int Num_positions=Dimension.rowCount()-1;


  // read the name of the elemens
  vector<bool> Vec_valid(Num_elements,false);

  setlocale(LC_ALL, "C");

  try{
    for (int Col=1;Col<=Num_elements;Col++){
      Name=read_cell(1,Col);

      if (Name!=""){
        auto It=std::find(Vec_element_names.begin(),Vec_element_names.end(),Name);
        if (It!=Vec_element_names.end()){
          Project_data.Vec_interpreted_data_xrf.push_back({Name,vector<float>(Num_positions,0.0f)});
          Vec_valid[Col]=true;
        }
        else{
          cout << "Warning: The element " << Name << " does not exists in the PDB" << endl;
        }
      }
    }

    int Row = 2;
    int Pos_position=0;
    while (Row<=Dimension.rowCount()){
      int Pos_element=0;
      for (int Col=1;Col<=Num_elements;Col++){
        if (Vec_valid[Col]==true){
          Token=read_cell(Row,Col);

          if (Token!=""){
            Token.erase(std::remove(Token.begin(), Token.end(), ' '), Token.end());
            replace(Token.begin(),Token.end(),',','.');
            Project_data.Vec_interpreted_data_xrf[Pos_element].Vec_values[Pos_position]=stof(Token);
            Pos_element++;
          }
        }
      }
      Pos_position++;
      Row++;
    }
  }
  catch(std::exception const& Exception){
    Error="There was an error: "+string(Exception.what())+"in file "+File_name+'\n';
    return false;
  }

  return true;
}

//HEA

//void _file_xlsx::write(_project_data_ns::_project_data &Project_data)
//{
//  string Text;

//  int Num_samples=Project_data.Num_samples;

//  setlocale(LC_ALL, "C");

//  File << "PROJECT_NAME;" << Project_data.Project_name << ";";
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  File << "AUTHOR;" << Project_data.Author << ";";
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  File << "DATE;" << Project_data.Date;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  File << "DEVICE;" << Project_data.Device;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";


//  Text=QString("%1").arg(int(Project_data.Width)).toStdString();
//  File << "WIDTH;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  Text=QString("%1").arg(int(Project_data.Height)).toStdString();
//  File << "HEIGHT;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  Text=QString("%1").arg(int(Project_data.Num_samples)).toStdString();
//  File << "NUM_SAMPLES;" << Text;
//  for (int i=0;i<Num_samples;i++) File << ";";
//  File << "\n";

//  // coordinates
//  File << "X;-";
//  for (unsigned int i=0;i<Project_data.Vec_coordinate_x.size();i++){
//    Text=QString("%1").arg(Project_data.Vec_coordinate_x[i],6,'f').toStdString();
//    replace(Text.begin(),Text.end(),'.',',');
//    File << "; " << Text;
//  }
//  File << "\n";

//  File << "Y;-";
//  for (unsigned int i=0;i<Project_data.Vec_coordinate_y.size();i++){
//    Text=QString("%1").arg(Project_data.Vec_coordinate_y[i],6,'f').toStdString();
//    replace(Text.begin(),Text.end(),'.',',');
//    File << "; " << Text;
//  }
//  File << "\n";

//  // elements
//  for (unsigned int i=0;i<Project_data.Vec_interpreted_data_xrf.size();i++){
//    File << "XRF" << "; ";

//    File << Project_data.Vec_interpreted_data_xrf[i].Name;
//    for (int j=0;j<Project_data.Num_samples;j++){
//      Text=QString("%1").arg(Project_data.Vec_interpreted_data_xrf[i].Vec_values[j],6,'f').toStdString();
//      replace(Text.begin(),Text.end(),'.',',');
//      File << "; " << Text;
//    }
//    File << "\n";
//  }
//}
