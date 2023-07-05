//LIC

#include "data_io.h"
#include "window.h"
#include "project_data.h"

//HEA

bool _data_io::load_info_txt(_window *Window, QString Project_dir,_project_data_ns::_project_data &Project_data)
{
  QFileInfo Check_file(Project_dir+"/"+QString::fromStdString(_common_window_ns::FILE_INFO));
  // check if file exists and if yes: Is it really a file and no directory?
  if (Check_file.exists() && Check_file.isFile()){
    // read the positions
    std::string Error;

    _file_info_txt File;

    File.open(Project_dir.toStdString()+"/"+_common_window_ns::FILE_INFO,_file_info_txt::_mode::MODE_READ);
    if (File.read(Project_data,Error)==true){
      File.close();
    }
    else{
      QMessageBox::critical(Window,Window->tr("Error"),QString::fromStdString(Error));
      QApplication::quit();
      exit(-1);
    }
  }
  else{
    QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString("There is not a '"+_common_window_ns::FILE_INFO+"' file"));
    QApplication::quit();
    exit(-1);
  }
  return true;
}

//HEA

bool _data_io::load_positions_txt(_window *Window, QString Project_dir,_project_data_ns::_project_data &Project_data)
{
  QFileInfo Check_file(Project_dir+"/"+QString::fromStdString(_common_window_ns::FILE_POSITIONS));
  // check if file exists and if yes: Is it really a file and no directory?
  if (Check_file.exists() && Check_file.isFile()){
    // read the positions
    std::string Error;

    // load the positions
    _file_positions_txt File;

    File.open(Project_dir.toStdString()+"/"+_common_window_ns::FILE_POSITIONS,_file_positions_txt::_mode::MODE_READ);
    if (File.read(Project_data,Error)==true){
      File.close();
    }
    else{
      QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString(Error));
      QApplication::quit();
      exit(-1);
    }
  }
  else{
    QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString("There is not a '"+_common_window_ns::FILE_POSITIONS+"' file"));
    QApplication::quit();
    exit(-1);
  }
  return true;
}

//HEAD

bool _data_io::load_project_data_csv(_window *Window, QString Project_dir, _project_data_ns::_project_data &Project_data, std::vector<std::string> &Vec_xrf_pdb_names, std::vector<std::string> &Vec_xrd_pdb_names)
{
  QFileInfo Check_file(Project_dir+"/"+QString::fromStdString(_common_window_ns::FILE_PROJECT_DATA));
  // check if file exists and if yes: Is it really a file and no directory?
  if (Check_file.exists() && Check_file.isFile()){
    // read the positions
    std::string Error;

    _file_project_data_csv File;

    File.open(Project_dir.toStdString()+"/"+_common_window_ns::FILE_PROJECT_DATA,_file_positions_txt::_mode::MODE_READ);
    if (File.read(Project_data,Vec_xrf_pdb_names,Vec_xrd_pdb_names,Error)==true){
      File.close();
    }
    else{
      QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString(Error));
      QApplication::quit();
      exit(-1);
    }
  }
  else{
    QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString("There is not a '"+_common_window_ns::FILE_PROJECT_DATA+"' file"));
    QApplication::quit();
    exit(-1);
  }
  return true;
}

//HEA

bool _data_io::xrf_load_pdb(_window *Window, std::vector<_data_xrf_ns::_data_xrf_pdb> &Vec_xrf_pdb_data, std::vector<std::string> &Vec_xrf_pdb_names)
{
  QFileInfo Check_file(QString::fromStdString(_common_window_ns::FILE_ELEMENTS));
  // check if file exists and if yes: Is it really a file and no directory?
  if (Check_file.exists() && Check_file.isFile()){
    std::string Error;

    _file_elements_csv File_elements_csv;

    File_elements_csv.open(_common_window_ns::FILE_ELEMENTS,_file_elements_csv::_mode::MODE_READ);
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
    QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString("There is not a '"+_common_window_ns::FILE_ELEMENTS+"' file"));
    QApplication::quit();
    exit(-1);
  }
  return true;
}

//HEA

bool _data_io::xrf_load_pdb_names(_window *Window, std::vector<std::string> &Vec_xrf_pdb_names)
{
  QFileInfo Check_file(QString::fromStdString(_common_window_ns::FILE_ELEMENTS));
  // check if file exists and if yes: Is it really a file and no directory?
  if (Check_file.exists() && Check_file.isFile()){
    std::string Error;

    _file_elements_csv File_elements_csv;
    std::vector<_data_xrf_ns::_data_xrf_pdb> Vec_xrf_pdb_data;

    File_elements_csv.open(_common_window_ns::FILE_ELEMENTS,_file_elements_csv::_mode::MODE_READ);
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
    QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString("There is not a '"+_common_window_ns::FILE_ELEMENTS+"' file"));
    QApplication::quit();
    exit(-1);
  }
  return true;
}

//HEA

#ifdef XRD_ACTIVE

#ifdef SPECTRAL_MODE_ACTIVE
bool _data_io::xrd_load_pdb_spectral(_window *Window, std::string Dir, std::vector<_data_xrd_ns::_data_xrd_pdb> &Vec_xrd_pdb_data,std::vector<std::string> &Vec_xrd_pdb_names)
{
  std::string File_name;
  std::string Error;

  QDir Directory(QString::fromStdString(Dir+"/"));
  std::string Dir_images=Directory.absolutePath().toStdString();

  QStringList Files_txt = Directory.entryList(QStringList() << "*.pgm.txt",QDir::Files,QDir::Name);

//  Files_txt.sort();

  if (Files_txt.size()>0){
    std::vector<float> Vec_values;
    std::vector<_common_ns::_peak_data> Vec_peaks;

    foreach(QString File_name, Files_txt) {
      QFileInfo File_info(File_name);
      std::string Short_name=File_info.baseName().toStdString();
      std::string Long_name=Dir_images+"/"+File_info.fileName().toStdString();

      std::vector<std::string> Vec_names;
      std::vector<std::string> Vec_formulas;
      std::vector<std::string> Vec_elements;
      _vertex3f Color;

      _file_xrd_pdb_txt File;
      File.open(Long_name,_file_xrd_pdb_txt::_mode::MODE_READ);

      if (File.read(Vec_names,Vec_formulas,Vec_elements,Color,Vec_values,Error)==true){
        File.close();

        Vec_xrd_pdb_data.push_back(_data_xrd_ns::_data_xrd_pdb{Short_name,Vec_names,Vec_formulas,Vec_elements,Color,Vec_values,Vec_values,Vec_values,Vec_values,0,Vec_peaks,true});
        Vec_xrd_pdb_names.push_back(Short_name);
      }
      else{
        File.close();

        QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString(Error));
        QApplication::quit();
        exit(-1);
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

//HEA

bool _data_io::xrd_load_pdb_spectral_names(_window *Window, std::string Dir,std::vector<std::string> &Vec_xrd_pdb_names)
{
  std::string File_name;
  std::string Error;

  QDir Directory(QString::fromStdString(Dir+"/"));
  std::string Dir_images=Directory.absolutePath().toStdString();

  QStringList Files_txt = Directory.entryList(QStringList() << "*.pgm.txt",QDir::Files,QDir::Name);

//  Files_txt.sort();

  if (Files_txt.size()>0){
    std::vector<float> Vec_values;
    std::vector<_common_ns::_peak_data> Vec_peaks;

    foreach(QString File_name, Files_txt) {
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

#endif

#ifdef XRD_ACTIVE
//HEA

#ifdef ASTM_MODE_ACTIVE
//bool _data_io::xrd_load_pdb_astm(_window *Window, std::string &Short_name,std::vector<std::string> &Vec_names,std::vector<std::string> &Vec_formulas, std::vector<string> Vec_elements,_vertex3f &Color,vector<float> &Vec_2theta,vector<float> &Vec_intensity, std::vector<float> &Vec_d_spacing)
//{
//  std::string File_name;
//  std::string Error;

//  QDir Directory(QString::fromStdString(_common_window_ns::FOLDER_PDB)+"/");
//  std::string Dir_images=Directory.absolutePath().toStdString();

//  QStringList Files_txt = Directory.entryList(QStringList() << "*amcsd.pgm.txt",QDir::Files);

//  Files_txt.sort();

//  if (Files_txt.size()>0){
//    std::vector<float> Vec_values;
//    std::vector<_common_ns::_peak_data> Vec_peaks;

//    foreach(QString File_name, Files_txt) {
//      QFileInfo File_info(File_name);
//      Short_name=File_info.baseName().toStdString();
//      std::string Long_name=Dir_images+"/"+File_info.fileName().toStdString();

////      std::vector<std::string> Vec_names;
////      std::vector<std::string> Vec_formulas;
////      std::vector<std::string> Vec_elements;
////      _vertex3f Color;
////      std::vector<float> Vec_2theta;
////      std::vector<float> Vec_intensity;
////      std::vector<float> Vec_d_spacing;

//     file_xrd_pdb_astm_txtxt File;
//      File.open(Long_name,_file_xrd_pdb_txt::_mode::MODE_READ);

//      if (File.read(Vec_names,Vec_formulas,Vec_elements,Color,Vec_2theta,Vec_intensity,Vec_d_spacing,Error)==true){
//        File.close();

////        // create the data of the PDB
////        _data_io::xrf_create_pdb(Vec_2theta,Vec_intensity,Vec_values);

////        Vec_xrd_pdb_data.push_back(_data_xrd_ns::_data_xrd_pdb{Short_name,Vec_names,Vec_formulas,Vec_elements,Color,Vec_values,Vec_values,0,Vec_peaks,false});
////        Vec_xrd_pdb_names.push_back(Short_name);
//      }
//      else{
//        File.close();

//        QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString(Error));
//        QApplication::quit();
//        exit(-1);
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

//HEA

bool _data_io::xrd_load_pdb_astm_names(_window *Window, std::vector<std::string> &Vec_xrd_pdb_names)
{
  std::string File_name;
  std::string Error;
  std::string Short_name;

  std::vector<_data_xrd_ns::_data_xrd_pdb> Vec_xrd_pdb_data_astm_Cu;
  std::vector<std::string> Vec_names_xrd_pdb_astm_Cu;

  QDir Directory(QString::fromStdString(_common_window_ns::FOLDER_PDB_XRD_ASTM_CU)+"/");
  std::string Dir_images=Directory.absolutePath().toStdString();

  QStringList Files_txt = Directory.entryList(QStringList() << "*astm.pgm.txt",QDir::Files);

  Files_txt.sort();

  if (Files_txt.size()>0){
    foreach(QString File_name, Files_txt) {
      QFileInfo File_info(File_name);
      Short_name=File_info.baseName().toStdString();
      std::string Long_name=Dir_images+"/"+File_info.fileName().toStdString();

      Vec_xrd_pdb_names.push_back(Short_name);
    }
  }
  else{
    QMessageBox::critical(Window,Window->tr("Error"),Window->tr("there are not 'astm.pgm.txt' files in pdb folder"));
    QApplication::quit();
    exit(-1);
  }
  return true;
}

#endif

#endif

//HEA

bool _data_io::load_xrf_interpreted_csv(_window *Window, QString Project_dir, std::vector<_project_data_ns::_interpreted_data> &Vec_sampled_data, std::vector<std::string> &Vec_names_pdb)
{
  std::string Error;
  _file_interpreted_csv File;

  QFileInfo Check_file(Project_dir+"/"+QString::fromStdString(_common_window_ns::FILE_XRF_CSV));
  // check if file exists and if yes: Is it really a file and no directory?
  if (Check_file.exists() && Check_file.isFile()){
    File.open(Project_dir.toStdString()+"/"+_common_window_ns::FILE_XRF_CSV,_file_positions_txt::_mode::MODE_READ);
    if (File.read(Vec_sampled_data,Vec_names_pdb,Error)==false){
      QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString(Error));
      QApplication::quit();
      exit(-1);
    }
  }
  else{
    QMessageBox::warning(Window, Window->tr("Warning"),QString::fromStdString("There is not a '"+_common_window_ns::FILE_XRF_CSV+"' file"));
    return false;
  }
  return true;
}


//HEA
#ifdef XRD_ACTIVE
bool _data_io::load_xrd_interpreted_csv(_window *Window, QString Project_dir,std::vector<_project_data_ns::_interpreted_data> &Vec_sampled_data,std::vector<std::string> &Vec_names_pdb)
{
  std::string Error;
  _file_interpreted_csv File;

  QFileInfo Check_file(Project_dir+"/"+QString::fromStdString(_common_window_ns::FILE_XRD_CSV));
  // check if file exists and if yes: Is it really a file and no directory?
  if (Check_file.exists() && Check_file.isFile()){
    File.open(Project_dir.toStdString()+"/"+_common_window_ns::FILE_XRD_CSV,_file_positions_txt::_mode::MODE_READ);
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

//HEA

bool _data_io::save_info_txt(_window *Window, QString Project_dir, _project_data_ns::_project_data &Project_data)
{
  _file_info_txt File;
  File.open(Project_dir.toStdString()+"/"+_common_window_ns::FILE_INFO,_file_io::_mode::MODE_WRITE);
  File.write(Project_data);
  File.close();
  QMessageBox::information(Window, Window->tr("Information"),QString::fromStdString("The file "+_common_window_ns::FILE_INFO+" has been correctly saved"));
  return true;
}

//HEA

bool _data_io::save_positions_txt(_window *Window, QString Project_dir, _project_data_ns::_project_data &Project_data)
{
  _file_positions_txt File;
  File.open(Project_dir.toStdString()+"/"+_common_window_ns::FILE_POSITIONS,_file_io::_mode::MODE_WRITE);
  File.write(Project_data);
  File.close();
  QMessageBox::information(Window, Window->tr("Information"),QString::fromStdString("The file "+_common_window_ns::FILE_POSITIONS+" file has been correctly saved"));
  return true;
}

//HEA

bool _data_io::save_project_data_csv(_window *Window, QString Project_dir, _project_data_ns::_project_data &Project_data)
{
  _file_project_data_csv File;
  File.open(Project_dir.toStdString()+"/"+_common_window_ns::FILE_PROJECT_DATA,_file_io::_mode::MODE_WRITE);
  File.write(Project_data);
  File.close();
  QMessageBox::information(Window, Window->tr("Information"),QString::fromStdString("The file "+_common_window_ns::FILE_PROJECT_DATA+" file has been correctly saved"));
  return true;
}

//HEA
#ifdef XLSX_ACTIVE

bool _data_io::load_xrf_interpreted_xlsx(_window *Window, QString Project_dir, std::vector<_project_data_ns::_interpreted_data>&Vec_interpreted_data, std::vector<std::string> &Vec_xrf_pdb_names)
{
  QFileInfo Check_file(Project_dir+"/"+QString::fromStdString(_common_window_ns::FILE_XRF_XLSX));
  // check if file exists and if yes: Is it really a file and no directory?
  if (Check_file.exists() && Check_file.isFile()){
    load_interpreted_xlsx(Window,Vec_interpreted_data,Vec_xrf_pdb_names,Project_dir.toStdString()+"/"+_common_window_ns::FILE_XRF_XLSX);
    return true;
  }
  else{
    QMessageBox::warning(Window, Window->tr("Warning"),QString::fromStdString("There is not a '"+_common_window_ns::FILE_XRF_XLSX+"' file"));
    return false;
  }
}

//HEA

bool _data_io::save_xrf_interpreted_xlsx(_window *Window, QString Project_dir, std::vector<_project_data_ns::_interpreted_data> &Vec_interpreted_data)
{
  save_interpreted_xlsx(Window,Vec_interpreted_data,Project_dir.toStdString()+"/"+_common_window_ns::FILE_XRF_XLSX);
  return true;
}

//HEA

bool _data_io::save_xrf_interpreted_plus_positions_xlsx(_window *Window, QString Project_dir, std::vector<float> Vec_coordinates_x, std::vector<float> Vec_coordinates_y,std::vector<_project_data_ns::_interpreted_data> &Vec_interpreted_data)
{
  save_interpreted_plus_positions_xlsx(Window,Vec_coordinates_x,Vec_coordinates_y,Vec_interpreted_data,Project_dir.toStdString()+"/"+_common_window_ns::FILE_XRF_PP_XLSX);
  return true;
}

//HEA

bool _data_io::load_xrd_interpreted_xlsx(_window *Window, QString Project_dir, std::vector<_project_data_ns::_interpreted_data>&Vec_interpreted_data, std::vector<std::string> &Vec_xrf_pdb_names)
{
  QFileInfo Check_file(Project_dir+"/"+QString::fromStdString(_common_window_ns::FILE_XRD_XLSX));
  // check if file exists and if yes: Is it really a file and no directory?
  if (Check_file.exists() && Check_file.isFile()){
    load_interpreted_xlsx(Window,Vec_interpreted_data,Vec_xrf_pdb_names,Project_dir.toStdString()+"/"+_common_window_ns::FILE_XRD_XLSX);
    return true;
  }
  else{
    QMessageBox::warning(Window, Window->tr("Warning"),QString::fromStdString("There is not a '"+_common_window_ns::FILE_XRD_XLSX+"' file"));
    return false;
  }
}

//HEA

bool _data_io::save_xrd_interpreted_xlsx(_window *Window, QString Project_dir, std::vector<_project_data_ns::_interpreted_data> &Vec_interpreted_data)
{
  save_interpreted_xlsx(Window,Vec_interpreted_data,Project_dir.toStdString()+"/"+_common_window_ns::FILE_XRD_XLSX);
  return true;
}

//HEA

bool _data_io::save_xrd_interpreted_plus_positions_xlsx(_window *Window, QString Project_dir, std::vector<float> Vec_coordinates_x, std::vector<float> Vec_coordinates_y,std::vector<_project_data_ns::_interpreted_data> &Vec_interpreted_data)
{
  save_interpreted_plus_positions_xlsx(Window,Vec_coordinates_x,Vec_coordinates_y,Vec_interpreted_data,Project_dir.toStdString()+"/"+_common_window_ns::FILE_XRD_PP_XLSX);
  return true;
}

//HEA

bool _data_io::save_xrd_data_xlsx(_window *Window, std::string File_name, std::vector<float> Vec_coordinates_obs, std::vector<float> Vec_coordinates_obs_normalized,std::vector<float> Vec_coordinates_pdb_normalized, std::vector<float> Vec_coordinates_sqrt)
{
  _file_xrd_data_xlsx File;

  File.open(File_name,_file_io_xlsx::_mode::MODE_WRITE);
  File.write(Vec_coordinates_obs,Vec_coordinates_obs_normalized,Vec_coordinates_pdb_normalized,Vec_coordinates_sqrt);
//  File.close();

  QMessageBox::information(Window, Window->tr("Information"),QString::fromStdString("The file "+File_name+" file has been correctly saved"));
  return true;
}


//HEA

bool _data_io::load_interpreted_xlsx(_window *Window, std::vector<_project_data_ns::_interpreted_data> &Vec_interpreted_data, std::vector<string> &Vec_element_namess, std::string File_name)
{
  // read the positions
  std::string Error;

  _file_interpreted_xlsx File;

  File.open(File_name,_file_io_xlsx::_mode::MODE_READ);
  if (File.read(Vec_interpreted_data,Vec_element_namess,Error)==false){
    QMessageBox::critical(Window, Window->tr("Error"),QString::fromStdString(Error));
    QApplication::quit();
    exit(-1);
  }
  return true;
}

//HEA

bool _data_io::save_interpreted_xlsx(_window *Window, std::vector<_project_data_ns::_interpreted_data> &Vec_interpreted_data, std::string File_name)
{
  _file_interpreted_xlsx File;
  File.open(File_name,_file_io_xlsx::_mode::MODE_WRITE);
  File.write(Vec_interpreted_data);
//  File.close();

  QMessageBox::information(Window, Window->tr("Information"),QString::fromStdString("The file "+File_name+" file has been correctly saved"));
  return true;
}

//HEA

bool _data_io::save_interpreted_plus_positions_xlsx(_window *Window, std::vector<float> Vec_coordinates_x, std::vector<float> Vec_coordinates_y, std::vector<_project_data_ns::_interpreted_data> &Vec_interpreted_data, std::string File_name)
{
  _file_interpreted_xlsx File;
  File.open(File_name,_file_io_xlsx::_mode::MODE_WRITE);
  File.write(Vec_coordinates_x,Vec_coordinates_y,Vec_interpreted_data);
//  File.close();

  QMessageBox::information(Window, Window->tr("Information"),QString::fromStdString("The file "+File_name+" file has been correctly saved"));
  return true;
}
#endif

//HEA

//bool _data_io::save_interpreted_csv(_window *Window, QString Project_dir,_project_data_ns::_project_data &Project_data)
//{
//  _file_project_data_csv File;
//  File.open(Project_dir.toStdString()+"/"+_common_window_ns::FILE_DATA,_file_io::_mode::MODE_WRITE);
//  File.write(Project_data);
////  File.close();
//  QMessageBox::information(Window, Window->tr("Information"),QString::fromStdString("The file "+_common_window_ns::FILE_DATA+" file has been correctly saved"));
//}


//HEA
#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
bool _data_io::load_compounds_combination_pdb(_window *Window, std::vector<_data_xrf_ns::_data_compound_from_elements_pdb> &Vec_data_compounds_combination_pdb)
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
#endif

#ifdef INTERPRETER
#ifdef XRD_ACTIVE
#ifdef XLSX_ACTIVE
//HEA

bool _data_io::xrd_save_correlation_table_xlsx(_window *Window, std::string Project_dir,vector<string> &Vec_obs_names,vector<string> &Vec_pdb_names, std::vector<bool> &Vec_xrd_visible_columns_in_table,vector<vector<_data_xrd_ns::_data_xrd_obs_pdb>> &Mat_xrd_obs_vs_pdb_data)
{
  _file_xrd_correlation_xlsx File;
  File.open(Project_dir+"/"+_common_window_ns::FILE_XRD_CORRELATION_DATA_XLSX,_file_io_xlsx::_mode::MODE_WRITE);
  File.write(Vec_obs_names,Vec_pdb_names,Vec_xrd_visible_columns_in_table,Mat_xrd_obs_vs_pdb_data);
  File.close();
  QMessageBox::information(Window, Window->tr("Information"),QString::fromStdString("The file "+_common_window_ns::FILE_XRD_CORRELATION_DATA_XLSX+" file has been correctly saved"));
  return true;
}

//HEA

bool _data_io::xrd_save_process_info_xlsx(_window *Window, std::string File_name, int Num_smooth_steps, int Num_subtract_noise_steps, float Start_2theta, float Steps_2theta, std::vector<float> &Vec_orig_data_obs, std::vector<float> &Vec_smooth_data_obs, std::vector<float> &Vec_subtract_noise_data_obs, std::vector<float> &Vec_normalized_data_obs, std::vector<float> &Vec_orig_data_pdb, std::vector<float> &Vec_smooth_data_pdb, std::vector<float> &Vec_subtract_noise_data_pdb, std::vector<float> &Vec_normalized_data_pdb, std::vector<float> Vec_sqrt_data)
{
  _file_xrd_process_info_xlsx File;
  File.open(File_name,_file_io_xlsx::_mode::MODE_WRITE);
  File.write(Num_smooth_steps,Num_subtract_noise_steps, Start_2theta, Steps_2theta, Vec_orig_data_obs,Vec_smooth_data_obs,Vec_subtract_noise_data_obs,Vec_normalized_data_obs, Vec_orig_data_pdb,Vec_smooth_data_pdb,Vec_subtract_noise_data_pdb,Vec_normalized_data_pdb,Vec_sqrt_data);
  File.close();
  QMessageBox::information(Window, Window->tr("Information"),QString::fromStdString("The file "+File_name+" file has been correctly saved"));
  return true;
}

#else
//HEA

bool _data_io::xrd_save_correlation_table_csv(_window *Window, std::string Project_dir,vector<string> &Vec_obs_names,vector<string> &Vec_pdb_names, std::vector<bool> &Vec_xrd_visible_columns_in_table,vector<vector<_data_xrd_ns::_data_xrd_obs_pdb>> &Mat_xrd_obs_vs_pdb_data)
{
  _file_xrd_correlation_csv File;
  File.open(Project_dir+"/"+_common_window_ns::FILE_XRD_CORRELATION_DATA_CSV,_file_io::_mode::MODE_WRITE);
  File.write(Vec_obs_names,Vec_pdb_names,Vec_xrd_visible_columns_in_table,Mat_xrd_obs_vs_pdb_data);
  File.close();
  QMessageBox::information(Window, Window->tr("Information"),QString::fromStdString("The file "+_common_window_ns::FILE_XRD_CORRELATION_DATA_CSV+" file has been correctly saved"));
  return true;
}

//HEA

bool _data_io::xrd_save_process_info_csv(_window *Window, std::string File_name, int Num_smooth_steps, int Num_subtract_noise_steps, float Start_2theta, float Steps_2theta, std::vector<float> &Vec_orig_data_obs, std::vector<float> &Vec_smooth_data_obs, std::vector<float> &Vec_subtract_noise_data_obs, std::vector<float> &Vec_normalized_data_obs, std::vector<float> &Vec_orig_data_pdb, std::vector<float> &Vec_smooth_data_pdb, std::vector<float> &Vec_subtract_noise_data_pdb, std::vector<float> &Vec_normalized_data_pdb, std::vector<float> Vec_sqrt_data)
{
  _file_xrd_process_info_csv File;
  File.open(File_name,_file_io::_mode::MODE_WRITE);
  File.write(Num_smooth_steps,Num_subtract_noise_steps, Start_2theta, Steps_2theta, Vec_orig_data_obs,Vec_smooth_data_obs,Vec_subtract_noise_data_obs,Vec_normalized_data_obs, Vec_orig_data_pdb,Vec_smooth_data_pdb,Vec_subtract_noise_data_pdb,Vec_normalized_data_pdb,Vec_sqrt_data);
  File.close();
  QMessageBox::information(Window, Window->tr("Information"),QString::fromStdString("The file "+File_name+" file has been correctly saved"));
  return true;
}
#endif
#endif
#endif

//HEA

#ifdef INTERPRETER
bool _data_io::xrf_save_process_info_csv(_window *Window, std::string File_name, int Num_smooth_steps, int Num_subtract_noise_steps, float Start_kev, float Steps_kev, std::vector<float> &Vec_orig_data, std::vector<float> &Vec_smooth_data, std::vector<float> &Vec_subtract_noise_data, std::vector<float> &Vec_normalized_data)
{
  _file_xrf_process_info_csv File;
  File.open(File_name,_file_io::_mode::MODE_WRITE);
  File.write(Start_kev, Steps_kev, Num_smooth_steps, Num_subtract_noise_steps, Vec_orig_data, Vec_smooth_data, Vec_subtract_noise_data, Vec_normalized_data);
  File.close();
  QMessageBox::information(Window, Window->tr("Information"),QString::fromStdString("The file "+File_name+" file has been correctly saved"));
  return true;
}
#endif
