//LIC

#include "file_interpreter_user_selections_csv.h"

//HEA
// read in the original values

bool _file_interpreter_user_selections::read(int &Selected_file_position, unsigned int& XRF_num_steps_smooth, unsigned int& XRF_num_steps_subtract_background, unsigned int& XRF_num_steps_search_window, _data_xrf_ns::_smooth_type& XRF_smooth_type, int &XRF_threshold_percentage, std::vector<_data_xrf_ns::_data_xrf_obs> &Vec_xrf_obs_data, std::vector<std::string> &Vec_xrd_selected_pdb_folders, unsigned int& XRD_num_steps_smooth, unsigned int& XRD_num_steps_subtract_background, unsigned int& XRD_num_steps_shift, _data_xrd_ns::_smooth_type& XRD_smooth_type, _data_xrd_ns::_normalization_type& XRD_normalization_type, float& XRD_correlation_good_threshold, float& XRD_correlation_medium_threshold, float& XRD_correlation_bad_threshold, std::vector<std::vector<_data_xrd_ns::_selection> > &Mat_xrd_obs_vs_pdb_data_selected, std::string &Error)
{
  std::string Text;
  std::string Name;
  std::vector<std::string> Tokens;
  bool Result=true;
  std::string Token;

  setlocale(LC_ALL, "C");

  try{
    // PDBs seleted
    get_new_line(File,Token);
    get_tokens(Token,';',Tokens);
    Vec_xrd_selected_pdb_folders.clear();
    for (unsigned int i=0;i<Tokens.size()-1;i++) Vec_xrd_selected_pdb_folders.push_back(Tokens[i+1]);

    //
    get_new_line(File,Token);
    get_tokens(Token,';',Tokens);
    Selected_file_position=std::stoi(clean_token(Tokens[1]));

    get_new_line(File,Token);
    get_tokens(Token,';',Tokens);
    if (Tokens[0]=="XRF" || Tokens[0]=="XRD"){
      if (Tokens[0]=="XRF"){
        // Thresholds
        get_new_line(File,Token);
        get_tokens(Token,';',Tokens);
        XRF_num_steps_smooth=std::stoi(clean_token(Tokens[1]));

        get_new_line(File,Token);
        get_tokens(Token,';',Tokens);
        XRF_num_steps_subtract_background=std::stoi(clean_token(Tokens[1]));

        get_new_line(File,Token);
        get_tokens(Token,';',Tokens);
        XRF_num_steps_search_window=std::stoi(clean_token(Tokens[1]));

        get_new_line(File,Token);
        get_tokens(Token,';',Tokens);
        if (Tokens[1]=="MEAN") XRF_smooth_type=_data_xrf_ns::_smooth_type::SMOOTH_TYPE_MEAN;
        else XRF_smooth_type=_data_xrf_ns::_smooth_type::SMOOTH_TYPE_GS;

        // num files (we know the number yet)
        get_new_line(File,Token);

        // num elements (we know the number yet)
        get_new_line(File,Token);
        get_tokens(Token,';',Tokens);
        int Num_elements=std::stoi(clean_token(Tokens[1]));

        // the threshold
        get_new_line(File,Token);
        get_tokens(Token,';',Tokens);
        XRF_threshold_percentage=std::stoi(Tokens[1]);

        // get the data
        for (unsigned int Pos_file=0;Pos_file<Vec_xrf_obs_data.size();Pos_file++){
          // values
          Vec_xrf_obs_data[Pos_file].Map_elements_manually_selected.clear();

          get_new_line(File,Token);
          get_tokens(Token,';',Tokens);
          for (int Pos_element=0;Pos_element<Num_elements;Pos_element++){
            Text=Tokens[3*Pos_element+1];
            bool Manual=bool(std::stoi(Tokens[3*Pos_element+2]));
            bool Selected=bool(std::stoi(Tokens[3*Pos_element+3]));

            Vec_xrf_obs_data[Pos_file].Map_elements_manually_selected[Text]={Manual,Selected};
          }
        }

        // read the next line
        get_new_line(File,Token);
        get_tokens(Token,';',Tokens);
      }

      if (Tokens[0]=="XRD"){        
        //
        get_new_line(File,Token);
        get_tokens(Token,';',Tokens);
        XRD_num_steps_smooth=std::stoi(clean_token(Tokens[1]));

        get_new_line(File,Token);
        get_tokens(Token,';',Tokens);
        XRD_num_steps_subtract_background=std::stoi(clean_token(Tokens[1]));

        get_new_line(File,Token);
        get_tokens(Token,';',Tokens);
        XRD_num_steps_shift=std::stoi(clean_token(Tokens[1]));

        get_new_line(File,Token);
        get_tokens(Token,';',Tokens);
        if (Tokens[1]=="MEAN") XRD_smooth_type=_data_xrd_ns::_smooth_type::SMOOTH_TYPE_MEAN;
        else XRD_smooth_type=_data_xrd_ns::_smooth_type::SMOOTH_TYPE_GS;

        get_new_line(File,Token);
        get_tokens(Token,';',Tokens);
        if (Tokens[1]=="MEAN") XRD_normalization_type=_data_xrd_ns::_normalization_type::NORMALIZATION_TYPE_MEAN;
        else XRD_normalization_type=_data_xrd_ns::_normalization_type::NORMALIZATION_TYPE_PERCENTAGE;

        // correlation good
        get_new_line(File,Token);
        get_tokens(Token,';',Tokens);
        XRD_correlation_good_threshold=std::stof(clean_token(Tokens[1]));

        // correlation medium
        get_new_line(File,Token);
        get_tokens(Token,';',Tokens);
        XRD_correlation_medium_threshold=std::stof(clean_token(Tokens[1]));

        // correlation bad
        get_new_line(File,Token);
        get_tokens(Token,';',Tokens);
        XRD_correlation_bad_threshold=std::stof(clean_token(Tokens[1]));

        // num files (we know the number yet)
        get_new_line(File,Token);
//        get_tokens(Token,';',Tokens);
//        int Num_files=std::stoi(clean_token(Tokens[1]));

        // num pigments (we know the number yet)
        get_new_line(File,Token);
        get_tokens(Token,';',Tokens);
        int Num_pigments=std::stoi(clean_token(Tokens[1]));

        // get the data HAND_SELECTION
        for (unsigned int Pos_file=0;Pos_file<Mat_xrd_obs_vs_pdb_data_selected.size();Pos_file++){
          Mat_xrd_obs_vs_pdb_data_selected[Pos_file].resize(Num_pigments);

          get_new_line(File,Token);
          get_tokens(Token,';',Tokens);

          for (unsigned Pos_pigment=0;Pos_pigment<Mat_xrd_obs_vs_pdb_data_selected[Pos_file].size();Pos_pigment++){
            if (Tokens[Pos_pigment+1]=="T") Mat_xrd_obs_vs_pdb_data_selected[Pos_file][Pos_pigment].Hand_selection=true;
            else Mat_xrd_obs_vs_pdb_data_selected[Pos_file][Pos_pigment].Hand_selection=false;
          }
        }

        // get the data SELECTED
        for (unsigned int Pos_file=0;Pos_file<Mat_xrd_obs_vs_pdb_data_selected.size();Pos_file++){
          get_new_line(File,Token);
          get_tokens(Token,';',Tokens);

          for (unsigned Pos_pigment=0;Pos_pigment<Mat_xrd_obs_vs_pdb_data_selected[Pos_file].size();Pos_pigment++){
            if (Tokens[Pos_pigment+1]=="T") Mat_xrd_obs_vs_pdb_data_selected[Pos_file][Pos_pigment].Selected=true;
            else Mat_xrd_obs_vs_pdb_data_selected[Pos_file][Pos_pigment].Selected=false;
          }
        }
      }
    }
    else{
      Error="The first field must be 'XRF' or 'XRD'";
      return false;
    }
  }
  catch(std::exception const& Exception){
    Error="There was an error: "+std::string(Exception.what())+"in file "+File_name+'\n';
    return false;
  }

  return Result;
}

//

bool _file_interpreter_user_selections::read(std::vector<std::string> &Vec_xrd_selected_pdb_folders, std::string &Error)
{
  std::string Text;
  std::string Name;
  std::vector<std::string> Tokens;
  bool Result=true;
  std::string Token;

  setlocale(LC_ALL, "C");

  try{
    //
    get_new_line(File,Token);
    get_tokens(Token,';',Tokens);
    Vec_xrd_selected_pdb_folders.clear();
    for (unsigned int i=0;i<Tokens.size()-1;i++) Vec_xrd_selected_pdb_folders.push_back(Tokens[i+1]);
  }
  catch(std::exception const& Exception){
    Error="There was an error: "+std::string(Exception.what())+"in file "+File_name+'\n';
    return false;
  }

  return Result;
}


//HEA
// write the final values

void _file_interpreter_user_selections::write(int Selected_file_position, int XRF_num_steps_smooth, int XRF_num_steps_subtract_background, int XRF_num_steps_search_window, _data_xrf_ns::_smooth_type XRF_smooth_type, int XRF_threshold_percentage, std::vector<_data_xrf_ns::_data_xrf_obs> Vec_xrf_obs_data, std::vector<std::string> &Vec_xrd_selected_pdb_folders, int XRD_num_steps_smooth, int XRD_num_steps_subtract_background, int XRD_num_steps_shift, _data_xrd_ns::_smooth_type XRD_smooth_type, _data_xrd_ns::_normalization_type XRD_normalization_type, float XRD_correlation_good_threshold, float XRD_correlation_medium_threshold, float XRD_correlation_bad_threshold, std::vector<std::vector<_data_xrd_ns::_selection> > &Mat_xrd_obs_vs_pdb_data_selected)
{
  std::string Text;

  setlocale(LC_ALL, "C");
  File << "SELECTED_PDBS";

  for (unsigned int i=0;i<Vec_xrd_selected_pdb_folders.size();i++)
    File << ";"+Vec_xrd_selected_pdb_folders[i];
  File << std::endl;

  File << "SELECTED_FILE_POSITION;" << Selected_file_position << std::endl;

  if (Vec_xrf_obs_data.size()>0){
    File << "XRF;" << std::endl;

    File << "NUM_STEPS_SMOOTH;" << XRF_num_steps_smooth << std::endl;
    File << "NUM_STEPS_SUBTRACT_BACKGROUND;" << XRF_num_steps_subtract_background << std::endl;
    File << "NUM_STEPS_SEARCH_WINDOW;" << XRF_num_steps_search_window << std::endl;

    if (XRF_smooth_type==_data_xrf_ns::_smooth_type::SMOOTH_TYPE_MEAN) File << "SMOOTH_TYPE;MEAN" << std::endl;
    else File << "SMOOTH_TYPE;GS" << std::endl;

    File << "NUM_FILES;" << Vec_xrf_obs_data.size() << std::endl;
    File << "NUM_ELEMENTS;" << Vec_xrf_obs_data[0].Map_elements_manually_selected.size() << std::endl;
    File << "THRESHOLD;" << XRF_threshold_percentage << std::endl;
    for (unsigned int Pos_file=0;Pos_file<Vec_xrf_obs_data.size();Pos_file++){
      File << "VALUES;";
      for (const auto &Pair : Vec_xrf_obs_data[Pos_file].Map_elements_manually_selected){
        File << Pair.first << ";" << Pair.second.Manual_selection << ";" << Pair.second.Selected << ";";
      }
      File << std::endl;
    }
  }

  if (Mat_xrd_obs_vs_pdb_data_selected.size()>0){
    File << "XRD;" << std::endl;
    File << "NUM_STEPS_SMOOTH;" << XRD_num_steps_smooth << std::endl;
    File << "NUM_STEPS_SUBTRACT_BACKGROUND;" << XRD_num_steps_subtract_background << std::endl;
    File << "NUM_STEPS_SHIFT;" << XRD_num_steps_shift << std::endl;

    if (XRD_smooth_type==_data_xrd_ns::_smooth_type::SMOOTH_TYPE_MEAN) File << "SMOOTH_TYPE;MEAN" << std::endl;
    else File << "SMOOTH_TYPE;GS" << std::endl;

    if (XRD_normalization_type==_data_xrd_ns::_normalization_type::NORMALIZATION_TYPE_MEAN) File << "NORMALIZATION_TYPE;MEAN" << std::endl;
    else File << "NORMALIZATION_TYPE;PERCENTAGE" << std::endl;

    Text=QString("%1").arg(int(XRD_correlation_good_threshold)).toStdString();
    File << "CORRELATION_GOOD_THRESHOLD;" << Text << "\n";

    Text=QString("%1").arg(int(XRD_correlation_medium_threshold)).toStdString();
    File << "CORRELATION_MEDIUM_THRESHOLD;" << Text << "\n";

    Text=QString("%1").arg(int(XRD_correlation_bad_threshold)).toStdString();
    File << "CORRELATION_BAD_THRESHOLD;" << Text << "\n";

    File << "NUM_FILES;" << Mat_xrd_obs_vs_pdb_data_selected.size() << std::endl;

    File << "NUM_PIGMENTS;" << Mat_xrd_obs_vs_pdb_data_selected[0].size() << std::endl;

    for (unsigned int Pos_file=0;Pos_file<Mat_xrd_obs_vs_pdb_data_selected.size();Pos_file++){
      File << "HAND_SELECTION;";
      for (unsigned Pos_pigment=0;Pos_pigment<Mat_xrd_obs_vs_pdb_data_selected[Pos_file].size();Pos_pigment++){
        if (Mat_xrd_obs_vs_pdb_data_selected[Pos_file][Pos_pigment].Hand_selection==true) File << "T";
        else File << "F";
        if (Pos_pigment<Mat_xrd_obs_vs_pdb_data_selected[Pos_file].size()-1) File << ";";
      }
      File << std::endl;
    }

    for (unsigned int Pos_file=0;Pos_file<Mat_xrd_obs_vs_pdb_data_selected.size();Pos_file++){
      File << "SELECTED;";
      for (unsigned Pos_pigment=0;Pos_pigment<Mat_xrd_obs_vs_pdb_data_selected[Pos_file].size();Pos_pigment++){
        if (Mat_xrd_obs_vs_pdb_data_selected[Pos_file][Pos_pigment].Selected==true) File << "T";
        else File << "F";
        if (Pos_pigment<Mat_xrd_obs_vs_pdb_data_selected[Pos_file].size()-1) File << ";";
      }
      File << std::endl;
    }

  }
}

//HEA

void _file_interpreter_user_selections::write(std::vector<std::string> &Vec_xrd_selected_pdb_folders)
{
  setlocale(LC_ALL, "C");

  File << "SELECTED_PDBS";

  for (unsigned int i=0;i<Vec_xrd_selected_pdb_folders.size();i++)
    File << ";"+Vec_xrd_selected_pdb_folders[i];
  File << std::endl;
}
