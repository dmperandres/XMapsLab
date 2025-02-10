//LIC

#include "file_project_data_csv.h"


std::string _file_project_data_csv::trim(const std::string& String)
{
  // Encontrar el primer carácter que no es un espacio en blanco
  size_t start = String.find_first_not_of(" \t\n\r\f\v");
  // Encontrar el último carácter que no es un espacio en blanco
  size_t end = String.find_last_not_of(" \t\n\r\f\v");

  // Si la cadena está vacía o solo contiene espacios, devolver una cadena vacía
  if (start == std::string::npos) {
    return "";
  }

  // Devolver la subcadena sin espacios al principio y al final
  return String.substr(start, end - start + 1);
}

// std::string _file_project_data_csv::replace_soft_hyphen(const std::string& String)
// {
//   std::string Result = String;
//   // const std::string Soft_hyphen = "\xC2\xAD"; // UTF-8 encoding for soft hyphen
//   const std::string Soft_hyphen = "-"; // UTF-8 encoding for soft hyphen
//   // const std::string Hard_hyphen = ">";
//   const std::string Hard_hyphen = "\xC2\xAD";

//   size_t Pos = 0;
//   while ((Pos = Result.find(Soft_hyphen, Pos)) != std::string::npos) {
//     Result.replace(Pos, Soft_hyphen.length(), Hard_hyphen);
//     Pos += Hard_hyphen.length(); // Avanzar para evitar bucles infinitos
//   }
//   return Result;
// }

//HEA
// read in the original values

bool _file_project_data_csv::read(_project_data_ns::_project_data &Project_data, std::string &Error)
{
  float Value;
  std::string Text;
  std::string Name;
  std::vector<std::string> Tokens;
  bool Result=true;
  std::string Token,Type,Element;
  float Real_value;
  float Max_value;
  float Type_max_value;

  setlocale(LC_ALL, "C");

  try{
    // first line must have XML for being valid
    get_new_line(File,Token);
    Token=trim(Token);
    get_tokens(Token,';',Tokens);
    Token=Tokens[0];
    // Token.erase(std::remove(Token.begin(), Token.end(), ' '), Token.end());
    for (auto & c: Token) c = toupper(c);
    if (Tokens.size()>1 && Token=="XML"){
      Project_data.Version=Tokens[1];

      while (get_new_line(File,Token)==true){
        //
        Token=trim(Token);
        get_tokens(Token,';',Tokens);
        Token=Tokens[0];
        // Token.erase(std::remove(Token.begin(), Token.end(), ' '), Token.end());
        // convert to uppercase
        for (auto & c: Token) c = toupper(c);

        auto It=std::find(_file_project_data_csv_ns::Vec_allowed_words.begin(),_file_project_data_csv_ns::Vec_allowed_words.end(),Token);
        if (It!=_file_project_data_csv_ns::Vec_allowed_words.end()){
          switch(It-_file_project_data_csv_ns::Vec_allowed_words.begin()){
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_PROJECT_NAME):
              if (Tokens.size()>1 && Tokens[1]!=""){
                Project_data.Project_name=Tokens[1];
              }
              break;
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_AUTHOR):
              if (Tokens.size()>1 && Tokens[1]!=""){
                Project_data.Author=Tokens[1];
              }
              break;
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_DATE):
              if (Tokens.size()>1 && Tokens[1]!=""){
                Project_data.Date=Tokens[1];
              }
              break;
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_DEVICE):
              if (Tokens.size()>1 && Tokens[1]!=""){
                // check if there is a correct method string
                Type=Tokens[1];
                Type=trim(Type);
                auto it = std::find(_file_project_data_csv_ns::Vec_names_methods.begin(), _file_project_data_csv_ns::Vec_names_methods.end(), Type);

                if (it != _file_project_data_csv_ns::Vec_names_methods.end()){
                  Text=Tokens[2];
                  Project_data.Map_device[Type]=Text;
                }
                else{
                  Error="There is not a valid mesurement type";
                  return false;
                }
              }
              else{
                Error="There is not DEVICE value";
                return false;
              }
              break;
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_TUBE):
              if (Tokens.size()>1 && Tokens[1]!=""){
                // check if there is a correct method string
                Type=Tokens[1];
                Type=trim(Type);
                auto it = std::find(_file_project_data_csv_ns::Vec_names_methods.begin(), _file_project_data_csv_ns::Vec_names_methods.end(), Type);

                if (it != _file_project_data_csv_ns::Vec_names_methods.end()){
                  Text=Tokens[2];

                  auto it = std::find(_data_xrd_ns::Vec_tube_name.begin(), _data_xrd_ns::Vec_tube_name.end(), Text);

                  if (it != _data_xrd_ns::Vec_tube_name.end()){
                    Project_data.Map_tube_type[Type]=Text;
                  }
                  else{
                    Error="There is not a valid tube type";
                    return false;
                  }
                }
                else{
                  Error="There is not a valid mesurement type";
                  return false;
                }
              }
              else{
                Error="There is not TUBE value";
                return false;
              }
              break;
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_WIDTH_CM):
              if (Tokens.size()>1 && Tokens[1]!=""){
                Text=Tokens[1];
                replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
                Value=stof(Text);
                if (Value>=0) Project_data.Width_cm=Value;
                else{
                  Error="The WIDTH_CM is less than 0";
                  return false;
                }
              }
              else{
                Error="There is not WIDTH_CM value";
                return false;
              }
              break;
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_HEIGHT_CM):
              if (Tokens.size()>1 && Tokens[1]!=""){
                Text=Tokens[1];
                replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
                Value=stof(Text);
                if (Value>=0) Project_data.Height_cm=Value;
                else{
                  Error="The HEIGHT_CM is less than 0";
                  return false;
                }
              }
              else{
                Error="There is not HEIGHT_CM value";
                return false;
              }
              break;
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_CS_ORIGIN):
              if (Tokens.size()>1 && Tokens[1]!=""){
                Text=Tokens[1];

                if (Text==_project_data_ns::Vec_names_cs_origin[0] || Text==_project_data_ns::Vec_names_cs_origin[1]){
                  if (Text==_project_data_ns::Vec_names_cs_origin[0]) Project_data.CS_origin=_project_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT;
                  else Project_data.CS_origin=_project_data_ns::_cs_origin::CS_ORIGIN_BOTTOM_LEFT;
                }
                else{
                  Error="The CS_ORIGIN value must be TOP_LEFT or BOTTOM_LEFT";
                  return false;
                }
              }
              else{
                Error="There is not CS_ORIGIN value";
                return false;
              }
              break;
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_WIDTH_PIXEL):
              if (Tokens.size()>1 && Tokens[1]!=""){
                Text=Tokens[1];
                replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
                Value=stof(Text);
                if (Value>=0) Project_data.Width_pixel=Value;
                else{
                  Error="The WIDTH_PIXEL is less than 0";
                  return false;
                }
              }
              else{
                Error="There is not WIDTH_PIXEL value";
                return false;
              }
              break;
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_HEIGHT_PIXEL):
              if (Tokens.size()>1 && Tokens[1]!=""){
                Text=Tokens[1];
                replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
                Value=stof(Text);
                if (Value>=0) Project_data.Height_pixel=Value;
                else{
                  Error="The HEIGHT_PIXEL is less than 0";
                  return false;
                }
              }
              else{
                Error="There is not HEIGHT_PIXEL value";
                return false;
              }
              break;
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_SPOT_SIZE):
              if (Tokens.size()>1 && Tokens[1]!=""){
                // check if there is a correct method string
                Type=Tokens[1];
                Type=trim(Type);
                auto it = std::find(_file_project_data_csv_ns::Vec_names_methods.begin(), _file_project_data_csv_ns::Vec_names_methods.end(), Type);

                if (it != _file_project_data_csv_ns::Vec_names_methods.end()){
                  Text=Tokens[2];
                  replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
                  Value=stof(Text);
                  if (Value>=0) Project_data.Map_spot_size[Type]=Value;
                  else{
                    Error="The SPOT_SIZE is less than 0";
                    return false;
                  }
                }
              }
              else{
                Error="There is not HEIGHT_PIXEL value";
                return false;
              }
              break;
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_X):
              Project_data.Vec_coordinates_x.resize(Tokens.size()-2,0.0f);

              for (unsigned int i=0;i<Project_data.Vec_coordinates_x.size();i++){
                if (Tokens[i+2]!=""){
                  Text=Tokens[i+2];
                  replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
                  Value=stof(Text);
                  if (Value>=0.0f && Value<=1.0f) Project_data.Vec_coordinates_x[i]=Value;
                  else{
                    Error="The coordinate X of position "+QString("%1").arg(i+1).toStdString()+" is not in the valid range";
                    return false;
                  }
                }
                else{
                  Error="There is not a valid X_coordinate value in position "+QString("%1").arg(i+1).toStdString();
                  return false;
                }
              }
              break;
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_Y):
              if (Tokens.size()-2>=Project_data.Vec_coordinates_x.size()){
                Project_data.Vec_coordinates_y.resize(Project_data.Vec_coordinates_x.size(),0.0f);
                for (unsigned int i=0;i<Project_data.Vec_coordinates_y.size();i++){
                  if (Tokens[i+2]!=""){
                    Text=Tokens[i+2];
                    replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
                    Value=stof(Text);
                    if (Value>=0.0f && Value<1.0f) Project_data.Vec_coordinates_y[i]=Value;
                    else{
                      Error="The coordinate Y of position "+QString("%1").arg(i+1).toStdString()+" is not in the valid range";
                      return false;
                    }
                  }
                  else{
                    Error="There is not a valid Y_coordinate value in position "+QString("%1").arg(i+1).toStdString();
                    return false;
                  }
                }
              }
              else{// error
                Error="There number of Y coordinates is different of X coordinates";
                return false;
              }
              break;
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_XRF):
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_XRD):
            case int(_file_project_data_csv_ns::_allowed_tokens::TOKEN_RAMAN):
              {
                Type=Tokens[0];
                Type=trim(Type);
                Element=Tokens[1];
                Element=trim(Element);
                // Element=replace_soft_hyphen(Element);

                // if Type is new it is added
                if (Project_data.Map_max_value.count(Type)==0) Project_data.Map_max_value[Type]=0;

                // get the max value for the type
                Type_max_value=Project_data.Map_max_value[Type];

                _project_data_ns::_measured_data Measured_data;

                Measured_data.Name=Element;
                Max_value=0;
                for (unsigned int i=0;i<Tokens.size()-2;i++){
                  Text=Tokens[i+2];
                  replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
                  Real_value=stof(Text);
                  if (Real_value<0) Real_value=0;
                  if (Real_value>Max_value) Max_value=Real_value;
                  Measured_data.Vec_values.push_back(Real_value);
                }

                // fill with 0 up to the number of positions
                for (unsigned int i=Tokens.size()-2;i<Project_data.Vec_coordinates_x.size();i++) Measured_data.Vec_values.push_back(0.0f);

                // normalize all the values
                for (unsigned int i=0;i<Measured_data.Vec_values.size();i++){
                  Measured_data.Vec_values[i]/=Max_value;
                }

                Measured_data.Max_value=Max_value;
                if (Max_value>Type_max_value) Project_data.Map_max_value[Type]=Max_value;
                if (Max_value>Project_data.Maximum_value) Project_data.Maximum_value=Max_value;

                Project_data.Map_data[Type][Element]=Measured_data;
              }
              break;
            default:break;
          }
        }
      }
    }
    else{
      Error="The project file must have the XML version in the first line";
      return false;
    }
  }
  catch(std::exception const& Exception){
    Error="There was an error: "+std::string(Exception.what())+" in file "+File_name+'\n';
    return false;
  }

  return Result;
}

//HEA
// write the final values

void _file_project_data_csv::write(_project_data_ns::_project_data &Project_data)
{
  std::string Text;

  setlocale(LC_ALL, "C");

  File << "XML;" << Project_data.Version << std::endl;
  File << "PROJECT_NAME;" << Project_data.Project_name << std::endl;
  File << "AUTHOR;" << Project_data.Author << std::endl;
  File << "DATE;" << Project_data.Date << std::endl;
  for (auto &Data : Project_data.Map_device){
    File << "DEVICE;" << Data.first << ";" << Data.second << std::endl;
  }

  for (auto &Data : Project_data.Map_tube_type){
    File << "TUBE;" << Data.first << ";" << Data.second << std::endl;
  }

  Text=QString("%1").arg(int(Project_data.Width_cm)).toStdString();
  File << "WIDTH_CM;" << Text << "\n";
  Text=QString("%1").arg(int(Project_data.Height_cm)).toStdString();
  File << "HEIGHT_CM;" << Text << "\n";

  Text=QString("%1").arg(int(Project_data.Width_pixel)).toStdString();
  File << "WIDTH_PIXEL;" << Text << "\n";
  Text=QString("%1").arg(int(Project_data.Height_pixel)).toStdString();
  File << "HEIGHT_PIXEL;" << Text << "\n";

  if (Project_data.CS_origin==_project_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT){
    Text=_project_data_ns::Vec_names_cs_origin[int(_project_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT)];
  }
  else{
    Text=_project_data_ns::Vec_names_cs_origin[int(_project_data_ns::_cs_origin::CS_ORIGIN_BOTTOM_LEFT)];
  }
  File << "CS_ORIGIN;" << Text << "\n";

  // an auxilar field to show the positions
  File << "POSITION;-";
  for (unsigned int i=0;i<Project_data.Vec_coordinates_x.size();i++){
    Text=QString("%1").arg(i+1).toStdString();
    File << ";" << Text;
  }
  File << "\n";

//  Text=QString("%1").arg(int(Project_data.Num_samples)).toStdString();
//  File << "NUM_SAMPLES;" << Text << "\n";

  // coordinates
  File << "X;-";
  for (unsigned int i=0;i<Project_data.Vec_coordinates_x.size();i++){
    // QString("%1").arg(Project_data.Vec_coordinate_x[i]).toStdString();
    Text=QString::number(Project_data.Vec_coordinates_x[i], 'f', 8).toStdString();
    File << ";" << Text;
  }
  File << "\n";

  File << "Y;-";
  for (unsigned int i=0;i<Project_data.Vec_coordinates_y.size();i++){
    // Text=QString("%1").arg(Project_data.Vec_coordinate_y[i]).toStdString();
    Text=QString::number(Project_data.Vec_coordinates_y[i], 'f', 8).toStdString();
    File << ";" << Text;
  }
  File << "\n";

  // elements
  // Recorrer el diccionario
  std::string Type;
  std::string Element;
  for (const auto& Pair_type : Project_data.Map_data){
    Type=Pair_type.first;
    File << Type << ";";
    for (const auto& Pair_element : Project_data.Map_data[Pair_type.first]){
      Element=Pair_element.first;
      File << Element << ";";
      for (unsigned int j=0;j<Project_data.Map_data[Type][Element].Vec_values.size();j++){
        Text=QString("%1").arg(Project_data.Map_data[Type][Element].Vec_values[j],8,'f',6).toStdString();
        replace(Text.begin(),Text.end(),'.',_common_ns::GOAL_DECIMAL_SEPARATOR);
        File << ";" << Text;
      }

      // fill up to the number of positions
      for (unsigned int j=Project_data.Map_data[Type][Element].Vec_values.size();j<Project_data.Vec_coordinates_x.size();j++){
        File << ";0" ;
      }
      File << "\n";
    }
  }
}
