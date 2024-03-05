#include "file_xrf_artax.h"

/*************************************************************************/

//bool _file_xrf_artax::read(std::vector<float> &Vec_data,float &Step,std::string &Error)
//{
//  float Value,Value1;
//  std::string Text;
//  std::string Token;
//  std::vector<std::string>Tokens;

//  setlocale(LC_ALL, "C");

//  try{
//    //head
//    get_new_line(File,Token);

//    get_new_line(File,Token);
//    get_tokens(Token,' ',Tokens);
//    Token=Tokens[0];
//    get_tokens(Token,'=',Tokens);
//    Text=Tokens[1];
//    replace(Text.begin(),Text.end(),',','.');
//    Step=stof(Text);

//    get_new_line(File,Token);
//    get_new_line(File,Token);

//    int Additional_steps=int(roundf(Step/0.015f));
//    // data
////    Step=0.0148913;

//    int Lim_inf=int(roundf(3/Step));
//    int Lim_sup=int(roundf(13/Step));

//    int Position=-1;
//    while (get_new_line(File,Token)){
//      Position++;
//      if (Position>=Lim_inf && Position<Lim_sup){
//        get_tokens(Token,';',Tokens);
//        Text=Tokens[0];
//        replace(Text.begin(),Text.end(),',','.');
//        Value=stof(Text);

//        Vec_data.push_back(Value);
//      }
//    }
//  }
//  catch(std::exception const& Exception){
//    Error="There was an error: "+std::string(Exception.what())+"in file "+File_name+'\n';
//    return false;
//  }

//  return(true);
//}

//bool _file_xrf_artax::read(std::vector<float> &Vec_data,float &Step,std::string &Error)
//{
//  float Value,Value1;
//  std::string Text;
//  std::string Token;
//  std::vector<std::string>Tokens;
//  float t;

//  setlocale(LC_ALL, "C");

//  try{
//    //head
//    get_new_line(File,Token);

//    get_new_line(File,Token);
//    get_tokens(Token,' ',Tokens);
//    Token=Tokens[0];
//    get_tokens(Token,'=',Tokens);
//    Text=Tokens[1];
//    replace(Text.begin(),Text.end(),',','.');
//    Step=stof(Text);

//    get_new_line(File,Token);
//    get_new_line(File,Token);

//    int Additional_steps=int(roundf(Step/0.015f));
//    if (Additional_steps<0){
//      Error="The step is less than 0";
//      return false;
//    }
//    // data
//    //    Step=0.0148913;

//    int Lim_inf=int(roundf(3/Step));
//    int Lim_sup=int(roundf(13/Step));

//    int Position=-1;
//    // first position
//    get_new_line(File,Token);
//    get_tokens(Token,';',Tokens);
//    Text=Tokens[0];
//    replace(Text.begin(),Text.end(),',','.');
//    Value=stof(Text);
//    while (get_new_line(File,Token)){
//      Position++;
//      get_tokens(Token,';',Tokens);
//      Text=Tokens[0];
//      replace(Text.begin(),Text.end(),',','.');
//      Value1=stof(Text);
//      if (Position>=Lim_inf && Position<Lim_sup){

//        // the data is saved
//        Vec_data.push_back(Value);

//        for (int Pos=1;Pos<=Additional_steps-1;Pos++){
//          t=float(Pos)/Additional_steps;
//          Vec_data.push_back((1.0f-t)*Value+t*Value1);
//        }
//      }
//      Value=Value1;
//    }
//    // the last value must be saved
//    Vec_data.push_back(Value1);
//  }
//  catch(std::exception const& Exception){
//    Error="There was an error: "+std::string(Exception.what())+"in file "+File_name+'\n';
//    return false;
//  }

//  return(true);
//}

bool _file_xrf_artax::read(std::vector<float> &Vec_data,float &Step,std::string &Error)
{
  float Value,Value1;
  std::string Text;
  std::string Token;
  std::vector<std::string>Tokens;
  float t;
  float Previous_pos_kev;
  float Pos_kev;

  setlocale(LC_ALL, "C");

  try{
    //head
    get_new_line(File,Token);

    get_new_line(File,Token);
    get_tokens(Token,' ',Tokens);
    Token=Tokens[0];
    get_tokens(Token,'=',Tokens);
    Text=Tokens[1];
    replace(Text.begin(),Text.end(),',','.');
    Step=stof(Text);

    get_new_line(File,Token);
    get_new_line(File,Token);

    int Additional_steps=int(roundf(Step/0.015f));
    if (Additional_steps<0){
      Error="The step is less than 0";
      return false;
    }
    // data
    //    Step=0.0148913;

//    int Lim_inf=int(roundf(3/Step));
//    int Lim_sup=int(roundf(13/Step));

    Vec_data.resize(1000,0.0f);

    // search for the first KeV position >=3.0
    bool Found=false;
    int Position=-1;
    int Pos_vector=0;
    while (Found==false && get_new_line(File,Token)){
      Position++;
      Previous_pos_kev=Step*Position;
      if (Previous_pos_kev>=3.0f) Found=true;
    }

    // save the first value
    get_tokens(Token,';',Tokens);
    Text=Tokens[0];
    replace(Text.begin(),Text.end(),',','.');
    float Previous_value=stof(Text);
    Vec_data[0]=Previous_value;
    Pos_vector++;
    // this is the start position
    Previous_pos_kev=3.0f;

    float Inv_step;
    while (get_new_line(File,Token)){
      Position++;
      Pos_kev=Step*Position;
      if (Pos_kev>=3.0f && Pos_kev<=13.0f){
        get_tokens(Token,';',Tokens);
        Text=Tokens[0];
        replace(Text.begin(),Text.end(),',','.');
        Value1=stof(Text);

        Additional_steps=int((Pos_kev-Previous_pos_kev)/0.01f);
        Inv_step=0.01f/(Pos_kev-Previous_pos_kev);
        for (int Pos=1;Pos<=Additional_steps-1;Pos++){
          t=float(Pos)*Inv_step;
          Vec_data[Pos_vector++]=(1.0f-t)*Previous_value+t*Value1;
        }
      }
      //
      Previous_pos_kev=(Pos_vector-1)*0.01f+3.0f;
      Previous_value=Vec_data[Pos_vector-1];
    }

    // the last value must be saved
    Vec_data[Pos_vector++]=Value1;

    // adjust the step
    Step=0.01f;
  }
  catch(std::exception const& Exception){
    Error="There was an error: "+std::string(Exception.what())+"in file "+File_name+'\n';
    return false;
  }

  return(true);
}

/*************************************************************************/

//void _file_xrf_artax::write(std::vector<float> &Vec_data)
//{
//  int Num_samples=Vec_data.Num_samples;

//  setlocale(LC_ALL, "C");

//  std::string Text=QString("%1").arg(Vec_data.Version).toStdString();
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
//}
