#include "file_xrd_pdb_csv.h"

//HEA
#ifdef GC
bool _file_xrd_pdb_csv::read(_data_xrd_ns::_tube_type &XRD_pdb_tube_type, std::vector<std::string> &Vec_names, std::vector<std::string> &Vec_formulas, std::vector<std::string> &Vec_elements, std::vector<float> &Vec_data, std::string &Error)
{
  float Position_2theta;
  std::string Text;
  std::vector<std::string>Tokens;

  std::string Token;
  //  istringstream Line_stream;
  setlocale(LC_ALL, "C");

  try{
    // TUBE
    get_new_line(File,Token);
    Token=clean_string(Token,_file_io_ns::SEPARATOR);
    get_tokens(Token,_file_io_ns::SEPARATOR,Tokens);
    if (Tokens.size()==2){
      Token=Tokens[1];
      if (Token=="CU") XRD_pdb_tube_type=_data_xrd_ns::_tube_type::TUBE_TYPE_CU;
      else if (Token=="CO") XRD_pdb_tube_type=_data_xrd_ns::_tube_type::TUBE_TYPE_CO;
      else{
        Error="There was an error: No correct TUBE (CO or CU) in file "+File_name+'\n';
        return false;
      }
    }
    else{
      Error="There was an error: No correct TUBE (CO or CU) in file "+File_name+'\n';
      return false;
    }

    // name
    get_new_line(File,Token);
    Token=clean_string(Token,_file_io_ns::SEPARATOR);
    get_tokens(Token,_file_io_ns::SEPARATOR,Tokens);
    if (Tokens.size()==2){
      Token=Tokens[1];
      get_tokens(Token,',',Tokens);
      Vec_names=Tokens;
    }
    else{
      Error="There was an error: No Name value in file "+File_name+'\n';
      return false;
    }


    // formula
    get_new_line(File,Token);
    Token=clean_string(Token,_file_io_ns::SEPARATOR);
    get_tokens(Token,_file_io_ns::SEPARATOR,Tokens);
    if (Tokens.size()==2){
      Token=Tokens[1];
      get_tokens(Token,',',Tokens);
      Vec_formulas=Tokens;
    }

    // Elements
    get_new_line(File,Token);
    Token=clean_string(Token,_file_io_ns::SEPARATOR);
    get_tokens(Token,_file_io_ns::SEPARATOR,Tokens);
    if (Tokens.size()==2){
      Token=Tokens[1];
      get_tokens(Token,',',Tokens);
      Vec_elements=Tokens;
    }

    Vec_data.resize((_data_xrd_ns::END_2THETA-_data_xrd_ns::START_2THETA)*_data_xrd_ns::STEPS_2THETA,0);
    int Position=0;
    while (get_new_line(File,Token)){
      Token=clean_string(Token,_file_io_ns::SEPARATOR);
      get_tokens(Token,_file_io_ns::SEPARATOR,Tokens);
      if (Tokens.size()==2){
        Text=Tokens[0];
        replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
        Position_2theta=stof(Text);
        Position=int(roundf((Position_2theta-_data_xrd_ns::START_2THETA)*_data_xrd_ns::STEPS_2THETA));
        if (Position>=0 && Position<int(Vec_data.size())){
          // value
          Text=Tokens[1];
          replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
          Vec_data[Position]=stof(Text);
        }
      }
      else{
        Error="There was an error: No correct position or value for position "+std::to_string(Position)+" in file "+File_name+'\n';
        return false;
      }
    }
    Position=1000;

  }
  catch(std::exception const& Exception){
    Error="There was an error: "+std::string(Exception.what())+" in file "+File_name+'\n';
    return false;
  }

  return true;
}


//HEA

void _file_xrd_pdb_csv::write(std::string Name, std::string Formula, std::string XRF, float Start_value, std::vector<float> &Vec_data)
{
  setlocale(LC_ALL, "C");

  std::string Position;
  std::string Value;

  File << "NAME" << _file_io_ns::SEPARATOR << Name << std::endl;
  File << "FORMULA" << _file_io_ns::SEPARATOR << Formula << std::endl;
  File << "XRF" << _file_io_ns::SEPARATOR << XRF << std::endl;

  for (unsigned int i=0;i<Vec_data.size();i++){
    Position=QString("%1").arg(Start_value+0.05*float(i),2,'f').toStdString();
    Value=QString("%1").arg(Vec_data[i],6,'f').toStdString();
    File << Position << _file_io_ns::SEPARATOR << Value << std::endl;
  }
}
#else
bool _file_xrd_pdb_csv::read(std::string &Type, std::string &Tube, std::string &Normalized, std::vector<std::string> &Vec_names, std::vector<std::string> &Vec_formulas, std::vector<std::string> &Vec_elements, _vertex3f &Color, std::vector<float> &Vec_data, std::vector<float> &Vec_2theta, std::vector<float> &Vec_intensity, std::vector<float> &Vec_d_spacing, std::string &Error)
{
  float Position_2theta;
  std::string Text;
  std::vector<std::string>Tokens;

  std::string Token;
//  istringstream Line_stream;
  setlocale(LC_ALL, "C");

  try{
    // type
    get_new_line(File,Token);
    get_tokens(Token,';',Tokens);
    Type=Tokens[1];
    if (!(Type==_data_xrd_ns::PDB_type_peaks || Type==_data_xrd_ns::PDB_type_spectral)){
      Error="There is an error for TYPE in file "+File_name+'\n';
      return false;
    }

    // tube
    get_new_line(File,Token);
    get_tokens(Token,';',Tokens);
    Tube=Tokens[1];
    if (!(Tube==_data_xrd_ns::PDB_tube_type_Co || Tube==_data_xrd_ns::PDB_tube_type_Cu)){
      Error="There is an error for TUBE in file "+File_name+'\n';
      return false;
    }

    // normalized
    get_new_line(File,Token);
    get_tokens(Token,';',Tokens);
    Normalized=Tokens[1];
    if (!(Normalized=="NO" || Normalized=="YES")){
      Error="There is an error for NORMALIZED in file "+File_name+'\n';
      return false;
    }

    // name
    get_new_line(File,Token);
    get_tokens(Token,';',Tokens);
    Token=Tokens[1];
    get_tokens(Token,',',Tokens);
    Vec_names=Tokens;

    // formula
    get_new_line(File,Token);
    get_tokens(Token,';',Tokens);
    Token=Tokens[1];
    get_tokens(Token,',',Tokens);
    Vec_formulas=Tokens;

    // Elements
    get_new_line(File,Token);
    get_tokens(Token,';',Tokens);
    Token=Tokens[1];
    get_tokens(Token,',',Tokens);
    Vec_elements=Tokens;

    // Color
    get_new_line(File,Token);
    get_tokens(Token,';',Tokens);
    Token=Tokens[1];
    get_tokens(Token,',',Tokens);
    if (Tokens.size()==3){
      Color.r=std::stof(Tokens[0]);
      Color.g=std::stof(Tokens[1]);
      Color.b=std::stof(Tokens[2]);
    }

    if (Type==_data_xrd_ns::PDB_type_spectral){ // Spectral
      Vec_data.resize((_data_xrd_ns::END_2THETA-_data_xrd_ns::START_2THETA)*_data_xrd_ns::STEPS_2THETA,0);
      int Position=0;
      while (get_new_line(File,Token)){
        get_tokens(Token,';',Tokens);
        Text=Tokens[0];
        replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
        Position_2theta=stof(Text);
        Position=int(roundf((Position_2theta-_data_xrd_ns::START_2THETA)*_data_xrd_ns::STEPS_2THETA));
        if (Position>=0 && Position<int(Vec_data.size())){
          // value
          Text=Tokens[1];
          replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
          Vec_data[Position]=stof(Text);
        }
      }
      Position=1000;
    }
    else{// peaks
      // remove the info line
      get_new_line(File,Token);

      // data
      while (get_new_line(File,Token)){
        get_tokens(Token,';',Tokens);

        // 2theta
        Text=Tokens[0];
        replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
        Vec_2theta.push_back(stof(Text));

        // intensity
        Text=Tokens[1];
        replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
        Vec_intensity.push_back(stof(Text));

        // d spacing
        Text=Tokens[2];
        replace(Text.begin(),Text.end(),_common_ns::FROM_DECIMAL_SEPARATOR,_common_ns::TO_DECIMAL_SEPARATOR);
        Vec_d_spacing.push_back(stof(Text));
      }
    }

  }
  catch(std::exception const& Exception){
    Error="There was an error: "+std::string(Exception.what())+"in file "+File_name+'\n';
    return false;
  }

  return true;
}


//HEA

void _file_xrd_pdb_csv::write(std::string Type, std::string Tube, std::string Normalized, std::string Name, std::string Formula, std::string XRF, std::string Color, float Start_value, std::vector<float> &Vec_data)
{
  setlocale(LC_ALL, "C");

  std::string Position;
  std::string Value;

  File << "TYPE;" << Type << std::endl;
  File << "TUBE;" << Tube << std::endl;
  File << "NORMALIZED;" << Normalized << std::endl;
  File << "NAME;" << Name << std::endl;
  File << "FORMULA;" << Formula << std::endl;
  File << "XRF;" << XRF << std::endl;
  File << "COLOR;" << Color << std::endl;

  for (unsigned int i=0;i<Vec_data.size();i++){
    Position=QString("%1").arg(Start_value+0.05*float(i),2,'f').toStdString();
    Value=QString("%1").arg(Vec_data[i],6,'f').toStdString();
    File << Position << ';' << Value << std::endl;
  }
}
#endif

