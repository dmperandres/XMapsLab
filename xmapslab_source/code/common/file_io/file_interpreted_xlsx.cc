//LIC

#include "file_interpreted_xlsx.h"

using namespace QXlsx;

//HEA

bool _file_interpreted_xlsx::read(std::vector<_project_data_ns::_interpreted_data> &Vec_interpreted_data, std::vector<std::string> &Vec_element_namess, std::string &Error)
{
  std::string Token;
  std::string Text;
  std::string Name;

  CellRange Dimension=Table->dimension();

  int Num_elements=Dimension.lastColumn();
  int Num_positions=Dimension.rowCount()-1;


  // read the name of the elemens
  std::vector<bool> Vec_valid(Num_elements,false);

  setlocale(LC_ALL, "C");

  try{
    for (int Col=1;Col<=Num_elements;Col++){
      Name=read_cell(1,Col);

      if (Vec_element_namess.size()>0){
        if (Name!=""){
          auto It=std::find(Vec_element_namess.begin(),Vec_element_namess.end(),Name);
          if (It!=Vec_element_namess.end()){
            Vec_interpreted_data.push_back({Name,vector<float>(Num_positions,0.0f)});
            Vec_valid[Col]=true;
          }
          else{
            cout << "Warning: The element " << Name << " does not exists in the PDB" << endl;
          }
        }
      }
      else{
        if (Name!=""){
          Vec_interpreted_data.push_back({Name,vector<float>(Num_positions,0.0f)});
          Vec_valid[Col]=true;
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
            replace(Token.begin(),Token.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
            Vec_interpreted_data[Pos_element].Vec_values[Pos_position]=stof(Token);
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

void _file_interpreted_xlsx::write(std::vector<_project_data_ns::_interpreted_data> &Vec_interpreted_data)
{
  std::string Text;

  setlocale(LC_ALL, "C");

  for (int Col=1;Col<=int(Vec_interpreted_data.size());Col++){
    Table->write(1,Col,QVariant(QString::fromStdString(Vec_interpreted_data[Col-1].Name)));
  }

  for (int Row=0;Row<int(Vec_interpreted_data[0].Vec_values.size());Row++){
    for (int Col=1;Col<=int(Vec_interpreted_data.size());Col++){
      Table->write(Row+2,Col,QVariant(Vec_interpreted_data[Col-1].Vec_values[Row]));
    }
  }

  Table->saveAs(QString::fromStdString(File_name));
}

//HEA

void _file_interpreted_xlsx::write(std::vector<float> &Vec_coordinates_x,std::vector<float> &Vec_coordinates_y,std::vector<_project_data_ns::_interpreted_data> &Vec_interpreted_data)
{
  std::string Text;

  setlocale(LC_ALL, "C");

  Table->write(1,1,"X");
  Table->write(1,2,"Y");

  for (int Col=1;Col<=int(Vec_interpreted_data.size());Col++){
    Table->write(1,Col+2,QVariant(QString::fromStdString(Vec_interpreted_data[Col-1].Name)));
  }

  for (int Row=0;Row<int(Vec_coordinates_x.size());Row++){
    Table->write(Row+2,1,QVariant(Vec_coordinates_x[Row]));
    Table->write(Row+2,2,QVariant(Vec_coordinates_y[Row]));
    if (int(Vec_interpreted_data[0].Vec_values.size())>Row){
      // only copy up to the number of positions
      for (int Col=1;Col<=int(Vec_interpreted_data.size());Col++){
        Table->write(Row+2,Col+2,QVariant(Vec_interpreted_data[Col-1].Vec_values[Row]));
      }
    }
    else{
      // there are mor positions than intensities
      for (int Col=1;Col<=int(Vec_interpreted_data.size());Col++){
        Table->write(Row+2,Col+2,QVariant(0.0f));
      }
    }
  }

  Table->saveAs(QString::fromStdString(File_name));
}


