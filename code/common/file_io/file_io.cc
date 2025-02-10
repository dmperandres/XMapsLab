#include "file_io.h"

//HEA

bool _file_io::open(const std::string &File_name1, _mode Mode)
{
  if (Mode==_mode::MODE_READ) File.open(File_name1.c_str(),std::ios::in);
  if (Mode==_mode::MODE_WRITE) File.open(File_name1.c_str(),std::ios::out);

  if (File.good()){
    File_name=File_name1;
    return true;
  }
  else{
//    std::perror("");
//    if (File.fail()) {
//      // La operación falló debido a un error específico.
//      std::cerr << "Error al abrir el archivo debido a un fallo." << std::endl;
//      std::cerr << "Error al abrir el archivo: " << std::strerror(errno) << std::endl;
//    } else if (File.bad()) {
//      // Hay un estado de error en el flujo.
//      std::cerr << "Error en el flujo del archivo." << std::endl;
//    } else if (File.eof()) {
//      // Se alcanzó el final del archivo inesperadamente.
//      std::cerr << "Se alcanzó el final del archivo inesperadamente." << std::endl;
//    } else {
//      // Otra razón desconocida.
//      std::cerr << "Error desconocido al abrir el archivo." << std::endl;
//    }
    return false;
  }
}

//HEA

void _file_io::close()
{
  File.close();
}

//HEA

void _file_io::get_token(std::istringstream &Line_stream1,std::string &Token1,char Separator)
{
//  cout << "str= " << Line_stream1.str() << " leng=" << Line_stream1.tellg() << endl;

  if (int(Line_stream1.tellg())<int(Line_stream1.str().length())){
    do{
      getline(Line_stream1,Token1,Separator);
    } while (Token1=="" && int(Line_stream1.tellg())<int(Line_stream1.str().length()));
    if (Token1.size()>0){
      if (Token1[Token1.size()-1]=='\r') Token1.erase(Token1.size() - 1);
    }
  }
  else{
    Token1="";
  }
}

//HEA

bool _file_io::get_new_line(std::fstream &File,std::string &Line)
{
  bool Line_empty=true;
  std::string Aux;
  char Text[8192];
  int Pos;

  do{
    if (getline(File,Aux)){
      if (Aux.size()>8192){
        std::cout << "There is a file line with size greather than 8192 (file_io::get_new_line)";
        exit(-1);
      }

      Pos=0;
      for (unsigned int i=0;i<Aux.size();i++){
        if (Aux[i]=='\r' || Aux[i]=='\t') Aux[i]=' ';

        if (Aux[i]!=' '){
          Text[Pos]=Aux[i];
          Pos++;
        }
        else{
          if (i<(Aux.size()-1) && Aux[i]==' ' && Aux[i+1]!=' '){
            Text[Pos]=Aux[i];
            Pos++;
          }
        }
      }

      Text[Pos]='\0';
      Line=Text;

      // remove carriage return
//      Aux.erase(remove(Aux.begin(),Aux.end(),'\r'), Aux.end());
//      // remove tabs
////      Aux.erase(remove(Aux.begin(),Aux.end(),'\t'), Aux.end());
//      replace(Aux.begin(),Aux.end(),'\t',' ');
//      Line=Aux;
//      Line=std::regex_replace(Aux, std::regex("\\s+")," ");

      if (Line.length()>0){
        return true;
      }
    }
    else return false;
  } while (Line_empty==true);
  return false;
}


//HEA

//bool _file_io::get_new_line(fstream &File,istringstream &Line_stream)
//{
//  bool Line_empty=true;

//  std::string Line;
//  do{
//    if (getline(File,Line)){
//      // remove carriage return
//      Line.erase(remove(Line.begin(),Line.end(),'\r'), Line.end());
//      // remove blank spaces at the beginning
////      Line.erase(remove(Line.begin(),Line.end(),' '), Line.end());
//			// remove tabs
//      Line.erase(remove(Line.begin(),Line.end(),'\t'), Line.end());
//      if (Line.length()>0){
//        Line_stream.str(Line);
//        Line_stream.seekg(0);
//        return true;
//      }
//    }
//    else return false;
//  } while (Line_empty==true);
//  return false;
//}

//HEA

//void _file_io::get_token(string &Token,char Separator)
//{
//  std::size_t Pos = Token.find(Separator);
//  while ((Pos+1)<string::npos && Token[Pos+1]==Separator) Pos++;
//  if (Pos!=string::npos) Token=Token.substr(Pos+1);
//}

//HEA

void _file_io::get_tokens(std::string &String, char Separator, std::vector<std::string> &Tokens)
{
  std::size_t Pos;
  std::string Token;
  Tokens.clear();

  do{
    Pos = String.find(Separator);
    if (Pos!=std::string::npos){
      Token=String.substr(0,Pos);
      Tokens.push_back(Token);
      while ((Pos+1)<std::string::npos && String[Pos+1]==Separator) Pos++;
      String=String.substr(Pos+1);
    }
  }while (Pos!=std::string::npos);
  if (String.size()>0) Tokens.push_back(String);
}

//HEA

std::string _file_io::clean_token(std::string Token)
{
  Token.erase(std::remove(Token.begin(), Token.end(), ' '), Token.end());
  replace(Token.begin(),Token.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);

  return Token;
}
