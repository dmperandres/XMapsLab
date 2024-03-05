/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "data_io.h"
#include "project_data.h"
#ifdef INTERPRETER
#include "window_interpreter.h"
#endif

/*************************************************************************/

bool _data_io::load_project_data_csv(QWidget *Window, std::string Project_dir, _project_data_ns::_project_data &Project_data, std::vector<std::string> &Vec_xrf_pdb_names, std::vector<std::string> &Vec_xrd_pdb_names)
{
  QFileInfo Check_file(QString::fromStdString(Project_dir+"/"+_common_window_ns::FILE_PROJECT_DATA));
  // check if file exists and if yes: Is it really a file and no directory?
  if (Check_file.exists() && Check_file.isFile()){
    // read the positions
    std::string Error;

    _file_project_data_csv File;

    if (File.open(Project_dir+"/"+_common_window_ns::FILE_PROJECT_DATA,_file_project_data_csv::_mode::MODE_READ)){
      if (File.read(Project_data,Vec_xrf_pdb_names,Vec_xrd_pdb_names,Error)==true){
        File.close();

        return true;
      }
      else{
        QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString(Error));
        return false;
      }
    }
    else{
      QMessageBox::warning(Window, Window->tr("Warning"),"The file "+QString::fromStdString(_common_window_ns::FILE_PROJECT_DATA)+" cannot be opened");
      return false;
    }
  }
  else{
    QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString("There is not a '"+_common_window_ns::FILE_PROJECT_DATA+"' file"));
    return false;
  }
}

/*************************************************************************/

bool _data_io::xrf_load_pdb(QWidget *Window, std::vector<_data_xrf_ns::_data_xrf_pdb> &Vec_xrf_pdb_data, std::vector<std::string> &Vec_xrf_pdb_names)
{
  QFileInfo Check_file(QString::fromStdString(_common_window_ns::FILE_ELEMENTS));
  // check if file exists and if yes: Is it really a file and no directory?
  if (Check_file.exists() && Check_file.isFile()){
    std::string Error;

    _file_elements_csv File_elements_csv;

    if (File_elements_csv.open(_common_window_ns::FILE_ELEMENTS,_file_elements_csv::_mode::MODE_READ)){
      if (File_elements_csv.read(Vec_xrf_pdb_data,Error)==true){
        File_elements_csv.close();

        Vec_xrf_pdb_names.resize(Vec_xrf_pdb_data.size());
        for (unsigned int i=0;i<Vec_xrf_pdb_data.size();i++){
          Vec_xrf_pdb_names[i]=Vec_xrf_pdb_data[i].Name;
        }
      }
      else{
        QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString(Error));
        QApplication::quit();
        exit(-1);
      }
    }
    else{
      QMessageBox::warning(Window, Window->tr("Warning"),"The file "+QString::fromStdString(_common_window_ns::FILE_ELEMENTS)+" cannot be opened");
      return false;
    }
  }
  else{
    QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString("There is not a '"+_common_window_ns::FILE_ELEMENTS+"' file"));
    QApplication::quit();
    exit(-1);
  }
  return true;
}

/*************************************************************************/

bool _data_io::xrf_load_pdb_names(QWidget *Window, std::vector<std::string> &Vec_xrf_pdb_names)
{
  QFileInfo Check_file(QString::fromStdString(_common_window_ns::FILE_ELEMENTS));
  // check if file exists and if yes: Is it really a file and no directory?
  if (Check_file.exists() && Check_file.isFile()){
    std::string Error;

    _file_elements_csv File_elements_csv;
    std::vector<_data_xrf_ns::_data_xrf_pdb> Vec_xrf_pdb_data;

    if (File_elements_csv.open(_common_window_ns::FILE_ELEMENTS,_file_elements_csv::_mode::MODE_READ)){
      if (File_elements_csv.read(Vec_xrf_pdb_data,Error)==true){
        File_elements_csv.close();

        Vec_xrf_pdb_names.resize(Vec_xrf_pdb_data.size());
        for (unsigned int i=0;i<Vec_xrf_pdb_data.size();i++){
          Vec_xrf_pdb_names[i]=Vec_xrf_pdb_data[i].Name;
        }
      }
      else{
        QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString(Error));
        QApplication::quit();
        exit(-1);
      }
    }
    else{
      QMessageBox::warning(Window, Window->tr("Warning"),"The file "+QString::fromStdString(_common_window_ns::FILE_ELEMENTS)+" cannot be opened");
      return false;
    }
  }
  else{
    QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString("There is not a '"+_common_window_ns::FILE_ELEMENTS+"' file"));
    QApplication::quit();
    exit(-1);
  }
  return true;
}

/*************************************************************************/

//bool _data_io::xrd_load_pdb_spectral(QWidget *Window, std::string Dir, std::vector<_data_xrd_ns::_data_xrd_pdb> &Vec_xrd_pdb_data,std::vector<std::string> &Vec_xrd_pdb_names)
//{
//  std::string File_name;
//  std::string Error;

//  QDir Directory(QString::fromStdString(Dir+"/"));
//  std::string Dir_images=Directory.absolutePath().toStdString();

//  QStringList Files_txt = Directory.entryList(QStringList() << "*.pgm.csv",QDir::Files,QDir::Name);

////  Files_txt.sort();

//  if (Files_txt.size()>0){
//    std::vector<float> Vec_values;
//    std::vector<_common_ns::_peak_data> Vec_peaks;

//    foreach(QString File_name, Files_txt) {
//      QFileInfo File_info(File_name);
//      std::string Short_name=File_info.baseName().toStdString();
//      std::string Long_name=Dir_images+"/"+File_info.fileName().toStdString();

//      std::string Type;
//      std::string Tube;
//      std::string Normalized;
//      std::vector<std::string> Vec_names;
//      std::vector<std::string> Vec_formulas;
//      std::vector<std::string> Vec_elements;
//      _vertex3f Color;

//      _file_xrd_pdb_csv File;
//      if(File.open(Long_name,_file_xrd_pdb_csv::_mode::MODE_READ)){
//        if (File.read(Type, Tube, Normalized, Vec_names, Vec_formulas, Vec_elements, Color, Vec_values, Error)==true){
//          File.close();

////          std::string File_name;
////          _pdb_type Type;
////          _tube_type Tube;
////          bool Normalized=false;
////          std::vector<std::string> Vec_names;
////          std::vector<std::string> Vec_formulas;
////          std::vector<std::string> Vec_elements;
////          _vertex3f Color;
////          std::vector<float> Vec_values;
////          std::vector<float> Vec_smooth_values;
////          std::vector<float> Vec_filtered_values;
////          std::vector<float> Vec_normalized_values;
////          int Area=0;
////          std::vector<_common_ns::_peak_data> Vec_peaks;
//          _data_xrd_ns::_pdb_type PDB_type;
//          if (Type==_data_xrd_ns::PDB_type_peaks) PDB_type=_data_xrd_ns::_pdb_type::PDB_TYPE_PEAKS;
//          else if (Type==_data_xrd_ns::PDB_type_spectral) PDB_type=_data_xrd_ns::_pdb_type::PDB_TYPE_SPECTRAL;
//          else{ // error
//            QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString("TYPE of file "+Long_name+" is wrong"));
//            QApplication::quit();
//            exit(-1);
//          }

//          _data_xrd_ns::_tube_type PDB_tube_type;
//          if (Tube==_data_xrd_ns::PDB_tube_type_Co) PDB_tube_type=_data_xrd_ns::_tube_type::TUBE_TYPE_CO;
//          else if (Tube==_data_xrd_ns::PDB_tube_type_Cu) PDB_tube_type=_data_xrd_ns::_tube_type::TUBE_TYPE_CU;
//          else{ // error
//            QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString("TUBE of file "+Long_name+" is wrong"));
//            QApplication::quit();
//            exit(-1);
//          }

//          bool PDB_normalized;
//          if (Normalized=="YES") PDB_normalized=true;
//          else PDB_normalized=false;

//          Vec_xrd_pdb_data.push_back(_data_xrd_ns::_data_xrd_pdb{Short_name,PDB_type, PDB_tube_type, PDB_normalized, Vec_names, Vec_formulas, Vec_elements, Color, Vec_values, Vec_values, Vec_values, Vec_values, 0, Vec_peaks});
//          Vec_xrd_pdb_names.push_back(Short_name);
//        }
//        else{
//          File.close();

//          QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString(Error));
//          QApplication::quit();
//          exit(-1);
//        }
//      }
//      else{
//        QMessageBox::warning(Window, Window->tr("Warning"),"The file "+File_name+" cannot be opened");
//        return false;
//      }
//    }
//  }
//  else{
//    QMessageBox::critical(Window, Window->tr("Error"),Window->tr("there are not '.txt' (xrd) files in pdb folder"));
//    QApplication::quit();
//    exit(-1);
//  }
//  return true;
//}

#ifdef INTERPRETER
/*************************************************************************/

bool _data_io::xrd_load_pdb_names(QWidget *Window, std::string Dir, std::vector<std::string> &Vec_xrd_pdb_names)
{
  std::string File_name;
  std::string Error;

  QDir Directory(QString::fromStdString(Dir+"/"));
  std::string Dir_images=Directory.absolutePath().toStdString();

  QStringList Files = Directory.entryList(QStringList() << "*.pgm.csv",QDir::Files,QDir::Name);

  Files.sort();

  if (Files.size()>0){
    std::vector<float> Vec_values;
    std::vector<_common_ns::_peak_data> Vec_peaks;

    foreach(QString File_name, Files) {
      QFileInfo File_info(File_name);
      std::string Short_name=File_info.baseName().toStdString();
      std::string Long_name=Dir_images+"/"+File_info.fileName().toStdString();

      Vec_xrd_pdb_names.push_back(Short_name);
    }
  }
  else{
    QMessageBox::critical(Window, Window->tr("Error"),Window->tr("there are not '.txt' (xrd) files in pdb folder"));
    QApplication::quit();
    exit(-1);
  }
  return true;
}
#endif

/*************************************************************************/

//bool _data_io::xrd_load_pdb_astm(QWidget *Window, std::string &Short_name,std::string &Type, std::string &Tube, std::string &Normalized, std::vector<std::string> &Vec_names,std::vector<std::string> &Vec_formulas, std::vector<std::string> Vec_elements,_vertex3f &Color,std::vector<float> &Vec_2theta,std::vector<float> &Vec_intensity, std::vector<float> &Vec_d_spacing)
//{
//  std::string File_name;
//  std::string Error;

//  QDir Directory(QString::fromStdString(_common_window_ns::FOLDER_PDB)+"/");
//  std::string Dir_images=Directory.absolutePath().toStdString();

//  QStringList Files_txt = Directory.entryList(QStringList() << "*astm.pgm.csv",QDir::Files);

//  Files_txt.sort();

//  if (Files_txt.size()>0){
//    std::vector<float> Vec_values;
//    std::vector<_common_ns::_peak_data> Vec_peaks;

//    foreach(QString File_name, Files_txt) {
//      QFileInfo File_info(File_name);
//      Short_name=File_info.baseName().toStdString();
//      std::string Long_name=Dir_images+"/"+File_info.fileName().toStdString();

//     _file_xrd_pdb_astm_csv File;

//      if(File.open(Long_name,_file_xrd_pdb_csv::_mode::MODE_READ)){
//        if (File.read(Type, Tube, Normalized, Vec_names, Vec_formulas, Vec_elements, Color, Vec_2theta, Vec_intensity, Vec_d_spacing, Error)==true){
//          File.close();

//        }
//        else{
//          File.close();

//          QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString(Error));
//          QApplication::quit();
//          exit(-1);
//        }
//      }
//      else{
//        QMessageBox::warning(Window, Window->tr("Warning"),"The file "+File_name+" cannot be opened");
//        return false;
//      }
//    }
//  }
//  else{
//    QMessageBox::critical(Window, Window->tr("Error"),Window->tr("there are not '.txt' (xrd) files in pdb folder"));
//    QApplication::quit();
//    exit(-1);
//  }
//  return true;
//}

/*************************************************************************/

//bool _data_io::xrd_load_pdb_astm_names(QWidget *Window, std::vector<std::string> &Vec_xrd_pdb_names)
//{
//  std::string File_name;
//  std::string Error;
//  std::string Short_name;

//  std::vector<_data_xrd_ns::_data_xrd_pdb> Vec_xrd_pdb_data_astm_Cu;
//  std::vector<std::string> Vec_names_xrd_pdb_astm_Cu;

//  QDir Directory(QString::fromStdString(_common_window_ns::FOLDER_PDB_XRD_ASTM_CU)+"/");
//  std::string Dir_images=Directory.absolutePath().toStdString();

//  QStringList Files_txt = Directory.entryList(QStringList() << "*astm.pgm.txt",QDir::Files);

//  Files_txt.sort();

//  if (Files_txt.size()>0){
//    foreach(QString File_name, Files_txt) {
//      QFileInfo File_info(File_name);
//      Short_name=File_info.baseName().toStdString();
//      std::string Long_name=Dir_images+"/"+File_info.fileName().toStdString();

//      Vec_xrd_pdb_names.push_back(Short_name);
//    }
//  }
//  else{
//    QMessageBox::critical(Window,Window->tr("Error"),Window->tr("there are not 'astm.pgm.txt' files in pdb folder"));
//    QApplication::quit();
//    exit(-1);
//  }
//  return true;
//}

#ifdef INTERPRETER
/*************************************************************************/

bool _data_io::xrd_load_pdb(QWidget *Window, std::string Dir, std::vector<_data_xrd_ns::_data_xrd_pdb> &Vec_xrd_pdb_data,std::vector<std::string> &Vec_xrd_pdb_names)
{
  std::string File_name;
  std::string Error;

  QDir Directory(QString::fromStdString(Dir+"/"));
  std::string Dir_images=Directory.absolutePath().toStdString();

#ifdef GC
  QStringList Files_txt = Directory.entryList(QStringList() << "*.pgm.txt",QDir::Files,QDir::Name);
#else
  QStringList Files_txt = Directory.entryList(QStringList() << "*.pgm.csv",QDir::Files,QDir::Name);
#endif

  //  Files_txt.sort();

  if (Files_txt.size()>0){
    foreach(QString File_name, Files_txt) {
      QFileInfo File_info(File_name);
      std::string Short_name=File_info.baseName().toStdString();
      std::string Long_name=Dir_images+"/"+File_info.fileName().toStdString();

      std::string Type;
      std::string Tube;
      std::string Normalized;
      std::vector<std::string> Vec_names;
      std::vector<std::string> Vec_formulas;
      std::vector<std::string> Vec_elements;
      std::vector<float> Vec_values;
      std::vector<_common_ns::_peak_data> Vec_peaks;
      std::vector<float> Vec_2theta;
      std::vector<float> Vec_intensity;
      std::vector<float> Vec_d_spacing;
      _vertex3f Color;

#ifdef GC
      _data_xrd_ns::_tube_type Tube_type;

      _file_xrd_pdb_csv File;
      if(File.open(Long_name,_file_xrd_pdb_csv::_mode::MODE_READ)){
        if (File.read(Tube_type, Vec_names, Vec_formulas, Vec_elements, Vec_values, Error)==true){
          File.close();

#else
      _file_xrd_pdb_csv File;
      if(File.open(Long_name,_file_xrd_pdb_csv::_mode::MODE_READ)){
        if (File.read(Type, Tube, Normalized, Vec_names, Vec_formulas, Vec_elements, Color, Vec_values, Vec_2theta, Vec_intensity, Vec_d_spacing, Error)==true){
          File.close();
#endif

          //          std::string File_name;
          //          _pdb_type Type;
          //          _tube_type Tube;
          //          bool Normalized=false;
          //          std::vector<std::string> Vec_names;
          //          std::vector<std::string> Vec_formulas;
          //          std::vector<std::string> Vec_elements;
          //          _vertex3f Color;
          //          std::vector<float> Vec_values;
          //          std::vector<float> Vec_smooth_values;
          //          std::vector<float> Vec_filtered_values;
          //          std::vector<float> Vec_normalized_values;
          //          int Area=0;
          //          std::vector<_common_ns::_peak_data> Vec_peaks;
          _data_xrd_ns::_pdb_type PDB_type;
          if (Type==_data_xrd_ns::PDB_type_peaks) PDB_type=_data_xrd_ns::_pdb_type::PDB_TYPE_PEAKS;
          else if (Type==_data_xrd_ns::PDB_type_spectral) PDB_type=_data_xrd_ns::_pdb_type::PDB_TYPE_SPECTRAL;
          else{ // error
            QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString("TYPE of file "+Long_name+" is wrong"));
            QApplication::quit();
            exit(-1);
          }

          _data_xrd_ns::_tube_type PDB_tube_type;
          if (Tube==_data_xrd_ns::PDB_tube_type_Co) PDB_tube_type=_data_xrd_ns::_tube_type::TUBE_TYPE_CO;
          else if (Tube==_data_xrd_ns::PDB_tube_type_Cu) PDB_tube_type=_data_xrd_ns::_tube_type::TUBE_TYPE_CU;
          else{ // error
            QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString("TUBE of file "+Long_name+" is wrong"));
            QApplication::quit();
            exit(-1);
          }

          bool PDB_normalized;
          if (Normalized=="YES") PDB_normalized=true;
          else PDB_normalized=false;

          // crete the spectral from the peaks
          if (PDB_type==_data_xrd_ns::_pdb_type::PDB_TYPE_PEAKS){
            Vec_values=((_window_interpreter *)Window)->xrd_create_spectral_from_peaks(Vec_2theta, Vec_intensity);
          }

          // get the values for astm

          Vec_xrd_pdb_data.push_back(_data_xrd_ns::_data_xrd_pdb{Short_name,PDB_type, PDB_tube_type, PDB_normalized, Vec_names, Vec_formulas, Vec_elements, Color, Vec_values, Vec_values, Vec_values, Vec_values, 0, Vec_peaks});
          Vec_xrd_pdb_names.push_back(Short_name);
        }
        else{
          File.close();

          QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString(Error));
          QApplication::quit();
          exit(-1);
        }
      }
      else{
        QMessageBox::warning(Window, Window->tr("Warning"),"The file "+File_name+" cannot be opened");
        return false;
      }
    }
  }
  else{
    QMessageBox::critical(Window, Window->tr("Error"),Window->tr("there are not '.txt' (xrd) files in pdb folder"));
    QApplication::quit();
    exit(-1);
  }
  return true;
}

/*************************************************************************/
#ifdef GC
/*************************************************************************/

bool _data_io::xrd_save_pdb_spectral(QWidget *Window, std::string File_name, std::string Name, std::string Formula, std::string XRF, float Start_value, std::vector<float> &Vec_data)
{
  _file_xrd_pdb_csv File;
  if (File.open(File_name,_file_io::_mode::MODE_WRITE)){
    File.write(Name, Formula, XRF, Start_value, Vec_data);
    File.close();
    return true;
  }
  else{
    QMessageBox::warning(Window, Window->tr("Warning"),"The file "+QString::fromStdString(File_name)+" cannot be opened");
    return false;
  }
}
#else

bool _data_io::xrd_save_pdb_spectral(QWidget *Window, std::string File_name, std::string Type, std::string Tube, std::string Normalized, std::string Name, std::string Formula, std::string XRF, std::string Color, float Start_value, std::vector<float> &Vec_data)
{
  _file_xrd_pdb_csv File;
  if (File.open(File_name,_file_io::_mode::MODE_WRITE)){
    File.write(Type, Tube, Normalized, Name, Formula, XRF, Color, Start_value, Vec_data);
    File.close();
    return true;
  }
  else{
    QMessageBox::warning(Window, Window->tr("Warning"),"The file "+QString::fromStdString(File_name)+" cannot be opened");
    return false;
  }
}
#endif
#endif

/*************************************************************************/

bool _data_io::save_project_data_csv(QWidget *Window, std::string Project_dir, _project_data_ns::_project_data &Project_data)
{
  _file_project_data_csv File;
  if (File.open(Project_dir+"/"+_common_window_ns::FILE_PROJECT_DATA,_file_io::_mode::MODE_WRITE)){
    File.write(Project_data);
    File.close();
    return true;
  }
  else{
    QMessageBox::warning(Window, Window->tr("Warning"),"The file "+QString::fromStdString(Project_dir+"/"+_common_window_ns::FILE_PROJECT_DATA)+" cannot be opened");
    return false;
  }
}

/*************************************************************************/

bool _data_io::load_compounds_combination_pdb(QWidget *Window, std::vector<_data_xrf_ns::_data_compound_from_elements_pdb> &Vec_data_compounds_combination_pdb)
{
  QFileInfo Check_file(QString::fromStdString(_common_window_ns::FILE_COMPOUNDS_COMBINATION));
  // check if file exists and if yes: Is it really a file and no directory?
  if (Check_file.exists() && Check_file.isFile()){
    std::string Error;

    _file_compound_combination_csv File_compounds_combination_csv;

    File_compounds_combination_csv.open(_common_window_ns::FILE_COMPOUNDS_COMBINATION,_file_elements_csv::_mode::MODE_READ);
    if (File_compounds_combination_csv.read(Vec_data_compounds_combination_pdb,Error)==true){
      File_compounds_combination_csv.close();
    }
    else{
      QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString(Error));
      QApplication::quit();
      exit(-1);
    }
  }
  else{
    QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString("There is not a '"+_common_window_ns::FILE_ELEMENTS+"' file"));
    QApplication::quit();
    exit(-1);
  }
  return true;
}

#ifdef INTERPRETER
/*************************************************************************/

bool _data_io::xrd_save_correlation_table_csv(QWidget *Window, std::string Project_dir, std::vector<std::string> &Vec_obs_names, std::vector<std::string> &Vec_pdb_names, std::vector<std::vector<_data_xrd_ns::_data_xrd_obs_pdb>> &Mat_xrd_obs_vs_pdb_data, std::vector<std::vector<_data_xrd_ns::_selection> > &Mat_xrd_obs_vs_pdb_data_selected)
{
  _file_xrd_correlation_csv File;
  if (File.open(Project_dir+"/"+_common_window_ns::FILE_XRD_CORRELATION_DATA_CSV,_file_io::_mode::MODE_WRITE)){
    File.write(Vec_obs_names, Vec_pdb_names, Mat_xrd_obs_vs_pdb_data, Mat_xrd_obs_vs_pdb_data_selected);
    File.close();
    QMessageBox::information(Window, Window->tr("Information"),QString::fromStdString("The file "+_common_window_ns::FILE_XRD_CORRELATION_DATA_CSV+" file has been correctly saved"));
    return true;
  }
  else{
    QMessageBox::warning(Window, Window->tr("Warning"),"The file "+QString::fromStdString(Project_dir+"/"+_common_window_ns::FILE_XRD_CORRELATION_DATA_CSV)+" cannot be opened");
    return false;
  }
}

/*************************************************************************/

bool _data_io::xrd_save_process_info_csv(QWidget *Window, std::string File_name, int Num_smooth_steps, int Num_subtract_noise_steps, float Start_2theta, float Steps_2theta, std::vector<float> &Vec_orig_data_obs, std::vector<float> &Vec_smooth_data_obs, std::vector<float> &Vec_subtract_noise_data_obs, std::vector<float> &Vec_normalized_data_obs, std::vector<float> &Vec_orig_data_pdb, std::vector<float> &Vec_smooth_data_pdb, std::vector<float> &Vec_subtract_noise_data_pdb, std::vector<float> &Vec_normalized_data_pdb, std::vector<float> Vec_sqrt_data)
{
  _file_xrd_process_info_csv File;
  if (File.open(File_name,_file_io::_mode::MODE_WRITE)){
    File.write(Num_smooth_steps,Num_subtract_noise_steps, Start_2theta, Steps_2theta, Vec_orig_data_obs,Vec_smooth_data_obs,Vec_subtract_noise_data_obs,Vec_normalized_data_obs, Vec_orig_data_pdb,Vec_smooth_data_pdb,Vec_subtract_noise_data_pdb,Vec_normalized_data_pdb,Vec_sqrt_data);
    File.close();
    QMessageBox::information(Window, Window->tr("Information"),QString::fromStdString("The file "+File_name+" file has been correctly saved"));
    return true;
  }
  else{
    QMessageBox::warning(Window, Window->tr("Warning"),"The file "+QString::fromStdString(File_name)+" cannot be opened");
    return false;
  }
}
#endif

/*************************************************************************/

bool _data_io::xrf_save_process_info_csv(QWidget *Window, std::string File_name, int Num_smooth_steps, int Num_subtract_noise_steps, float Start_kev, float Steps_kev, std::vector<float> &Vec_orig_data, std::vector<float> &Vec_smooth_data, std::vector<float> &Vec_subtract_noise_data, std::vector<float> &Vec_normalized_data)
{
  _file_xrf_process_info_csv File;
  if (File.open(File_name,_file_io::_mode::MODE_WRITE)){
    File.write(Start_kev, Steps_kev, Num_smooth_steps, Num_subtract_noise_steps, Vec_orig_data, Vec_smooth_data, Vec_subtract_noise_data, Vec_normalized_data);
    File.close();
    QMessageBox::information(Window, Window->tr("Information"),QString::fromStdString("The file "+File_name+" file has been correctly saved"));
    return true;
  }
  else{
    QMessageBox::warning(Window, Window->tr("Warning"),"The file "+QString::fromStdString(File_name)+" cannot be opened");
    return false;
  }
}

/*************************************************************************/

bool _data_io::xrf_load_interpreted_csv(QWidget *Window, std::string File_name, std::vector<_project_data_ns::_interpreted_data> &Vec_sampled_data, std::vector<std::string> &Vec_names_pdb)
{
  std::string Error;
  _file_interpreted_csv File;

  if (File.open(File_name,_file_io::_mode::MODE_READ)){
    if (File.read(Vec_sampled_data,Vec_names_pdb,Error)==false){
      QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString(Error));
      QApplication::quit();
      exit(-1);
    }
    return true;
  }
  else{
    QMessageBox::warning(Window, Window->tr("Warning"),"The file "+QString::fromStdString(File_name)+" cannot be opened");
    return false;
  }
}

#ifdef INTERPRETER
/*************************************************************************/

bool _data_io::xrd_load_interpreted_csv(QWidget *Window, std::string Project_dir, std::vector<_project_data_ns::_interpreted_data> &Vec_sampled_data, std::vector<std::string> &Vec_names_pdb)
{
  std::string Error;
  _file_interpreted_csv File;

  QFileInfo Check_file(QString::fromStdString(Project_dir+"/"+_common_window_ns::FILE_XRD_CSV));
  // check if file exists and if yes: Is it really a file and no directory?
  if (Check_file.exists() && Check_file.isFile()){
    File.open(Project_dir+"/"+_common_window_ns::FILE_XRD_CSV,_file_io::_mode::MODE_READ);
      if (File.read(Vec_sampled_data,Vec_names_pdb,Error)==false){
        QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString(Error));
        QApplication::quit();
        exit(-1);
      }
  }
  else{
    QMessageBox::warning(Window, Window->tr("Warning"),QString::fromStdString("There is not a '"+_common_window_ns::FILE_XRD_CSV+"' file"));
    return false;
  }
  return true;
}
#endif

/*************************************************************************/

bool _data_io::load_interpreter_user_selections_csv(QWidget *Window, std::string Project_dir, int &Selected_file_position, unsigned int& XRF_num_steps_smooth, unsigned int& XRF_num_steps_subtract_background, unsigned int& XRF_num_steps_search_window, _data_xrf_ns::_smooth_type& XRF_smooth_type, int &XRF_threshold_percentage, std::vector<_data_xrf_ns::_data_xrf_obs> &Vec_xrf_obs_data, std::vector<std::string> &Vec_xrd_selected_pdb_folders, unsigned int& XRD_num_steps_smooth, unsigned int& XRD_num_steps_subtract_background, unsigned int& XRD_num_steps_shift, _data_xrd_ns::_smooth_type& XRD_smooth_type, _data_xrd_ns::_normalization_type& XRD_normalization_type, float& XRD_correlation_good_threshold, float& XRD_correlation_medium_threshold, float& XRD_correlation_bad_threshold, std::vector<std::vector<_data_xrd_ns::_selection> > &Mat_xrd_obs_vs_pdb_data_selected)
{
  std::string Error;
  _file_interpreter_user_selections File;

  QFileInfo Check_file(QString::fromStdString(Project_dir+"/"+_common_window_ns::FILE_INTERPRETER_USER_SELECTIONS));
  // check if file exists and if yes: Is it really a file and no directory?
  if (Check_file.exists() && Check_file.isFile()){

    if (File.open(Project_dir+"/"+_common_window_ns::FILE_INTERPRETER_USER_SELECTIONS,_file_io::_mode::MODE_READ)){
      if (File.read(Selected_file_position, XRF_num_steps_smooth, XRF_num_steps_subtract_background, XRF_num_steps_search_window, XRF_smooth_type, XRF_threshold_percentage, Vec_xrf_obs_data, Vec_xrd_selected_pdb_folders, XRD_num_steps_smooth, XRD_num_steps_subtract_background, XRD_num_steps_shift, XRD_smooth_type, XRD_normalization_type, XRD_correlation_good_threshold, XRD_correlation_medium_threshold, XRD_correlation_bad_threshold, Mat_xrd_obs_vs_pdb_data_selected,Error)==false){
        QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString(Error));
        QApplication::quit();
        exit(-1);
      }
    }
    else{
      QMessageBox::warning(Window, Window->tr("Warning"),"The file "+QString::fromStdString(_common_window_ns::FILE_INTERPRETER_USER_SELECTIONS)+" cannot be opened");
      return false;
    }
  }
  else{
    QMessageBox::warning(Window, Window->tr("Warning"),QString::fromStdString("There is not a '"+_common_window_ns::FILE_INTERPRETER_USER_SELECTIONS+"' file"));
    return false;
  }
  return true;
}

/*************************************************************************/

bool _data_io::save_interpreter_user_selections_csv(QWidget *Window, std::string Project_dir, int Selected_file_position, int XRF_num_steps_smooth, int XRF_num_steps_subtract_background, int XRF_num_steps_search_window, _data_xrf_ns::_smooth_type XRF_smooth_type, int XRF_threshold_percentage, std::vector<_data_xrf_ns::_data_xrf_obs> &Vec_xrf_obs_data, std::vector<std::string> &Vec_xrd_selected_pdb_folders, int XRD_num_steps_smooth, int XRD_num_steps_subtract_background, int XRD_num_steps_shift, _data_xrd_ns::_smooth_type XRD_smooth_type, _data_xrd_ns::_normalization_type XRD_normalization_type, float XRD_correlation_good_threshold, float XRD_correlation_medium_threshold, float XRD_correlation_bad_threshold, std::vector<std::vector<_data_xrd_ns::_selection> > &Mat_xrd_obs_vs_pdb_data_selected)
{
  _file_interpreter_user_selections File;
  if (File.open(Project_dir+"/"+_common_window_ns::FILE_INTERPRETER_USER_SELECTIONS,_file_io::_mode::MODE_WRITE)){
    File.write(Selected_file_position, XRF_num_steps_smooth, XRF_num_steps_subtract_background, XRF_num_steps_search_window, XRF_smooth_type, XRF_threshold_percentage, Vec_xrf_obs_data, Vec_xrd_selected_pdb_folders, XRD_num_steps_smooth, XRD_num_steps_subtract_background, XRD_num_steps_shift, XRD_smooth_type, XRD_normalization_type, XRD_correlation_good_threshold, XRD_correlation_medium_threshold, XRD_correlation_bad_threshold, Mat_xrd_obs_vs_pdb_data_selected);
    File.close();
    QMessageBox::information(Window, Window->tr("Information"),QString::fromStdString("The file "+_common_window_ns::FILE_INTERPRETER_USER_SELECTIONS+" file has been correctly saved"));
    return true;
  }
  else{
    QMessageBox::warning(Window, Window->tr("Warning"),"The file "+QString::fromStdString(_common_window_ns::FILE_INTERPRETER_USER_SELECTIONS)+" cannot be opened");
    return false;
  }
}

/*************************************************************************/

bool _data_io::load_interpreter_user_selections_csv(QWidget *Window, std::string Project_dir, std::vector<std::string> &Vec_xrd_selected_pdb_folders)
{
  std::string Error;
  _file_interpreter_user_selections File;

  QFileInfo Check_file(QString::fromStdString(Project_dir+"/"+_common_window_ns::FILE_INTERPRETER_USER_SELECTIONS));
  // check if file exists and if yes: Is it really a file and no directory?
  if (Check_file.exists() && Check_file.isFile()){

    if (File.open(Project_dir+"/"+_common_window_ns::FILE_INTERPRETER_USER_SELECTIONS,_file_io::_mode::MODE_READ)){
      if (File.read(Vec_xrd_selected_pdb_folders,Error)==false){
        QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString(Error));
        QApplication::quit();
        exit(-1);
      }
    }
    else{
      QMessageBox::warning(Window, Window->tr("Warning"),"The file "+QString::fromStdString(_common_window_ns::FILE_INTERPRETER_USER_SELECTIONS)+" cannot be opened");
      return false;
    }
  }
  else{
    QMessageBox::warning(Window, Window->tr("Warning"),QString::fromStdString("There is not a '"+_common_window_ns::FILE_INTERPRETER_USER_SELECTIONS+"' file"));
    return false;
  }
  return true;
}

/*************************************************************************/

bool _data_io::save_interpreter_user_selections_csv(QWidget *Window, std::string Project_dir,  std::vector<std::string> &Vec_xrd_selected_pdb_folders)
{
  _file_interpreter_user_selections File;
  if (File.open(Project_dir+"/"+_common_window_ns::FILE_INTERPRETER_USER_SELECTIONS,_file_io::_mode::MODE_WRITE)){
    File.write(Vec_xrd_selected_pdb_folders);
    File.close();
    QMessageBox::information(Window, Window->tr("Information"),QString::fromStdString("The file "+_common_window_ns::FILE_INTERPRETER_USER_SELECTIONS+" file has been correctly saved"));
    return true;
  }
  else{
    QMessageBox::warning(Window, Window->tr("Warning"),"The file "+QString::fromStdString(_common_window_ns::FILE_INTERPRETER_USER_SELECTIONS)+" cannot be opened");
    return false;
  }
}

/*************************************************************************/

bool _data_io::load_positions_data_csv(QWidget *Window, std::string File_name, _project_data_ns::_project_data &Project_data)
{

  if (Project_data.Width_original_pixel>0 && Project_data.Height_original_pixel>0){
    std::string Error;
    _file_positions_csv File;

    if (File.open(File_name,_file_io::_mode::MODE_READ)){
      if (File.read(Project_data,Error)==false){
        QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString(Error));
        QApplication::quit();
        exit(-1);
      }
      return true;
    }
    else{
      QMessageBox::warning(Window, Window->tr("Warning"),"The file "+QString::fromStdString(File_name)+" cannot be opened");
      return false;
    }
  }
  else{
    QMessageBox::warning(Window, Window->tr("Warning"),"The Width or the Height in project_data.csv must be possitive and different of 0<br>Probably you have forgotten to include the image in the project<br>Use <b>Tools</b> to include the image");
    return false;
  }
}

/*************************************************************************/

bool _data_io::load_colormaps_csv(QWidget *Window, std::string Dir, std::map<std::string,std::vector<_vertex3f>> &Map_fixed_palettes)
{
  std::string File_name;
  std::string Error;

  QDir Directory(QString::fromStdString(Dir+"/"));
  std::string Dir_images=Directory.absolutePath().toStdString();

  QStringList Files_csv = Directory.entryList(QStringList() << "*.csv",QDir::Files,QDir::Name);

  //  Files_txt.sort();

  if (Files_csv.size()>0){
    foreach(QString File_name, Files_csv) {
      QFileInfo File_info(File_name);
      std::string Short_name=File_info.baseName().toStdString();
      std::string Long_name=Dir+"/"+File_info.fileName().toStdString();

      std::vector<_vertex3f> Vec_colors;

      _file_color_map_csv File;
      if(File.open(Long_name,_file_xrd_pdb_csv::_mode::MODE_READ)){
        if (File.read(Vec_colors, Error)==true){
          File.close();

          Map_fixed_palettes[Short_name]=Vec_colors;
        }
        else{
          File.close();

          QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString(Error));
          QApplication::quit();
          exit(-1);
        }
      }
      else{
        QMessageBox::warning(Window, Window->tr("Warning"),"The file "+File_name+" cannot be opened");
        return false;
      }
    }
  }
  else{
    QMessageBox::critical(Window, Window->tr("Error"),Window->tr("there are not '.csv' (fixed palettes) files in the folder"));
    QApplication::quit();
    exit(-1);
  }
  return true;
}
