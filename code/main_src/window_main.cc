/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#include "window_main.h"
#include "window_positions.h"
#include "window_xmapslab.h"

#ifdef INTERPRETER
#include "window_interpreter.h"
#endif

/*************************************************************************/

_window_main::_window_main()
{
#ifdef DEBUG_XML
  std::cout << "en _window_main::window_main " << __LINE__ << std::endl;
#endif

  // the dimensions of the main window
  QRect Screen_size = QApplication::primaryScreen()->geometry();
  Screen_width=Screen_size.width();
  Screen_height=Screen_size.height();

#ifdef INTERPETER
  Window_interpreter=new _window_interpreter(this);
#endif
  Window_xmapslab=new _window_xmapslab(this);
  Window_positions=new _window_positions(this);
  Window_tools= new _window_tools(this);

  Main_tab=new QTabWidget;
  // name for using it with styles
  Main_tab->setObjectName("Main_tab");

//  Main_tab->setTabPosition(QTabWidget::West);
  int Pos=0;
  Main_tab->addTab(Window_tools, tr("Tools"));
  Map_tab_name_to_index["tools"]=Pos++;

  Main_tab->addTab(Window_positions, tr("Positions"));
  Map_tab_name_to_index["positions"]=Pos++;

#ifdef INTERPETER
  Main_tab->addTab(Window_interpreter, tr("Interpreter"));
  Map_tab_name_to_index["interpreter"]=Pos++;
#endif
  Main_tab->addTab(Window_xmapslab, tr("MapsLab"));
  Map_tab_name_to_index["mapslab"]=Pos++;

  // stylesheet
//  QString Tab_style = "QTabWidget::pane#Main_tab { \
//                        border-top: 2px solid #C2C7CB; \
//                        position: absolute; \
//                      } \
//                      QTabWidget::tab-bar#Main_tab { \
//                        alignment: center; \
//                      }";

  QString Tab_style = "QTabWidget::tab-bar#Main_tab { \
                        alignment: center; \
                      }";

  Main_tab->setStyleSheet(Tab_style);

  Main_tab->setTabEnabled(Map_tab_name_to_index["positions"],false);
#ifdef INTERPETER
  Main_tab->setTabEnabled(Map_tab_name_to_index["interpreter"],false);
#endif
  Main_tab->setTabEnabled(Map_tab_name_to_index["mapslab"],false);

  connect(Main_tab,SIGNAL(tabBarClicked(int)),this,SLOT(tabbar_clicked(int)));

  setCentralWidget(Main_tab);

  setWindowTitle("XMapsLab");
}

/*************************************************************************/

void _window_main::change_font_size(int Font_size,QWidget* Widget1)
{
  QList<QWidget *> Descendants = Widget1->findChildren<QWidget*>();
  for (QWidget *Descendant : Descendants) {
    if (Descendant!=nullptr) {
      QFont Font = Descendant->font();
      Font.setPointSize(Font_size);
      Descendant->setFont(Font);
    }
  }
}

/*************************************************************************/

void _window_main::project_dir(QString Project_dir1)
{
  Project_dir=Project_dir1;

  read_settings();

  QFont Font=QApplication::font();
  Font.setPointSize(UI_font_size);
  QApplication::setFont(Font);

  resize(Window_size);
  move(Window_position);

  Window_positions->project_dir(Project_dir);
#ifdef INTERPRETER
  Window_interpreter->project_dir(Project_dir);
#endif
  Window_xmapslab->project_dir(Project_dir);

  ui_font_size(UI_font_size);

  check_project_state();
}

/*************************************************************************/
void _window_main::check_project_state()
{
  // check that there is one image at least
  QDir Directory_images(Project_dir+"/images");
  std::string Dir_images=Directory_images.absolutePath().toStdString();

  QStringList Files_images = Directory_images.entryList(QStringList() << "*.png" << "*.jpg", QDir::Files);

  if (Files_images.size()==0) Image_exists=false;
  else Image_exists=true;

  // Check and load project_data.csv
  QFileInfo Check_file(Project_dir+"/"+QString::fromStdString(_common_window_ns::FILE_PROJECT_DATA));
  if (Check_file.exists()==true){
    // the names of the PDB elements and compounds are not necessary
    if (_data_io::load_project_data_csv(this,Project_dir.toStdString(),Project_data,Vec_xrf_pdb_names,Vec_xrd_pdb_names)==true){
      // first check that the positions have been introduced
      if (Project_data.Vec_coordinate_x_original.size()==0) Positions_exists=false;
      else Positions_exists=true;;

      // check that there are XRF and/or XRD data in project_data.csv -> to use XMapsLab OR

      if (Project_data.Vec_xrf_interpreted_data.size()==0) XRF_data_exist=false;
      else XRF_data_exist=true;

      if (Project_data.Vec_xrd_interpreted_data.size()==0) XRD_data_exist=false;
      else XRD_data_exist=true;

      if(check_xrf_files_exist()==true) XRF_artax_files_exist=true;
      else XRF_artax_files_exist=false;

      if(check_xrd_files_exist()==true) XRD_files_exist=true;
      else XRD_files_exist=false;

      QMessageBox msgBox(this);

      if (Image_exists==false){
        msgBox.setText(_window_main_ns::MESSAGE_NO_IMAGE_TITLE);
        msgBox.setInformativeText(_window_main_ns::MESSAGE_NO_IMAGE_INFO);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();

        return;
      }

      if (Positions_exists==false){
        msgBox.setText(_window_main_ns::MESSAGE_NO_POSITIONS_TITLE);
        msgBox.setInformativeText(_window_main_ns::MESSAGE_NO_POSITIONS_INFO);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();

        Window_tools->show_positions();
        Main_tab->setTabEnabled(Map_tab_name_to_index["positions"],true);

        return;
      }

#ifdef INTERPRETER
      if (XRF_data_exist==false && XRD_data_exist==false){
        if (XRF_artax_files_exist==false && XRD_files_exist==false){
          msgBox.setText("<big>There are not XRF and/or XRD data in project_data.csv file nor artax (XRF) and/or uxd (XRD) files into the corresponding project folders</big>");
          msgBox.setInformativeText("Please, add the XRF and/or XRD data to the project using<br><ul><li>Copying the artax (XRF) and/or uxd (XRD) files into the corresponding project folders. Then you can use <b>Interpreter</b> to get the values.</li><li>Using the utility in <b>Tools</b> to be able to copy the interpreted values that must have been saved in the <b>xrf_data.csv</b> and/or <b>xrd_data.csv</b> files following the rules established in their format (see manual)</li><li>Directly copying the interpreted values from a spreadsheet to the <b>project_data.csv</b> file following the rules established in its format (see manual)</li></ul>");
          msgBox.setDefaultButton(QMessageBox::Ok);
          msgBox.exec();

          Window_tools->show_all();
          Main_tab->setTabEnabled(Map_tab_name_to_index["positions"],true);

          return;
        }
        else{
          msgBox.setText("<big>There are not XRF and/or XRD data in project_data.csv file</big>");
          msgBox.setInformativeText("Please, add the XRF and/or XRD data to the project using<br><ul><li>Using <b>Interpreter</b> to get the values.</li><li>Using the utility in <b>Tools</b> to be able to copy the interpreted values that must have been saved in the <b>xrf_data.csv</b> and/or <b>xrd_data.csv</b> files following the rules established in their format (see manual)</li><li>Directly copying the interpreted values from a spreadsheet to the <b>project_data.csv</b> file following the rules established in its format (see manual)</li></ul>");
          msgBox.setDefaultButton(QMessageBox::Ok);
          msgBox.exec();

          Window_tools->show_all();
          Main_tab->setTabEnabled(Map_tab_name_to_index["positions"],true);
          Main_tab->setTabEnabled(Map_tab_name_to_index["interpreter"],true);
          return;
        }
      }
      else{
        if (XRF_artax_files_exist==false && XRD_files_exist==false){
          msgBox.setText("<big>There are not XRF files nor XRD files, but there are XRF and/or XRD data in project_data.csv file</big>");
          msgBox.setInformativeText("It is possible to use any program except <b>Interpreter</b>");
          msgBox.setDefaultButton(QMessageBox::Ok);
          msgBox.exec();

          Main_tab->setTabEnabled(Map_tab_name_to_index["positions"],true);
          Main_tab->setTabEnabled(Map_tab_name_to_index["interpreter"],false);
          Main_tab->setTabEnabled(Map_tab_name_to_index["mapslab"],true);
        }
        else{
          msgBox.setText("<big>All the data is in project_data.csv file</big>");
          msgBox.setInformativeText("It is possible to use any program");
          msgBox.setDefaultButton(QMessageBox::Ok);
          msgBox.exec();

          Main_tab->setTabEnabled(Map_tab_name_to_index["positions"],true);
#ifdef INTERPRETER
          Main_tab->setTabEnabled(Map_tab_name_to_index["interpreter"],true);
#endif
          Main_tab->setTabEnabled(Map_tab_name_to_index["mapslab"],true);
        }
      }
#else
      if (XRF_data_exist==false && XRD_data_exist==false){
        msgBox.setText("<big>There are not XRF and/or XRD data in project_data.csv file</big>");
        msgBox.setInformativeText("Please, add the XRF and/or XRD data to the project using<br><ul><li>Using the utility in <b>Tools</b> to be able to copy the interpreted values that must have been saved in the <b>xrf_data.csv</b> and/or <b>xrd_data.csv</b> files following the rules established in their format (see manual)</li><li>Directly copying the interpreted values from a spreadsheet to the <b>project_data.csv</b> file following the rules established in its format (see manual)</li></ul>");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();

        Window_tools->show_all();
        Main_tab->setTabEnabled(Map_tab_name_to_index["positions"],true);
        return;
      }
      else{
        msgBox.setText("<big>All the data is in project_data.csv file</big>");
        msgBox.setInformativeText("It is possible to use any program");
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();

        Main_tab->setTabEnabled(Map_tab_name_to_index["positions"],true);
        Main_tab->setTabEnabled(Map_tab_name_to_index["mapslab"],true);
      }
#endif

    }
    else{
      // error reading project_data.csv
//      QMessageBox::critical(this, tr("Error"),tr("The 'project_data.csv' file has an error. It cannot be opened. Please, check it."));
      QApplication::quit();
      exit(-1);
    }
  }
  else{
    QMessageBox::critical(this, tr("Error"),tr("There is not 'project_data.csv' file"));
    QApplication::quit();
    exit(-1);
  }
}

/*************************************************************************/

void _window_main::load_image(std::string File_name)
{
  // read the image
  _image_IO Image_io;
  Image_vis=std::make_shared<cv::Mat>();

  Image_io.read_image(File_name,*Image_vis.get());

  int Width_aux=Image_vis->cols;
  int Height_aux=Image_vis->rows;

  adjust_image_sizes(Width_aux,Height_aux);
  if (Width_aux!=Image_vis->cols || Height_aux!=Image_vis->rows){
    cv::resize(*Image_vis.get(),*Image_vis.get(),cv::Size(Width_aux,Height_aux),0,0,cv::INTER_CUBIC);
  }

  // flip the original image to adapt it to OpenGL
  cv::flip(*Image_vis.get(),*Image_vis.get(),0);
  cv::cvtColor(*Image_vis.get(),*Image_vis.get(),cv::COLOR_BGR2BGRA,4);

  // compute the distance threshold
  Distance_threshold=float(Image_vis->cols)*_window_positions_ns::PERCENTAGE_THRESHOLD_DISTANCE;
  if (Distance_threshold<_window_positions_ns::MINIMUM_THRESHOLD_DISTANCE)  Distance_threshold=_window_positions_ns::MINIMUM_THRESHOLD_DISTANCE;

}

/*************************************************************************/

void _window_main::adjust_image_sizes(int& Width1, int& Height1)
{
  float Rest;

  if (Width1%4!=0){
    Rest=roundf(float(Width1)/4.0f);
    Width1=int(Rest)*4;

  }
  if (Height1%4!=0){
    Rest=roundf(float(Height1)/4.0f);
    Height1=int(Rest)*4;
  }
}

/*************************************************************************/

bool _window_main::check_xrf_files_exist()
{
  // check that there are a xrf folder
  if (QDir(Project_dir+"/xrf").exists()){
    // check that there are a xrf/raw folder
    if (QDir(Project_dir+"/xrf/raw").exists()){
      // check if there are files
      QDir Directory(Project_dir+"/xrf/raw/");
      //      std::string Dir_xrf=Directory.absolutePath().toStdString();

      QStringList Files_artax = Directory.entryList(QStringList() << "*.txt",QDir::Files);

      if (Files_artax.size()>0) return true;
    }
  }
  return false;
}

/*************************************************************************/

bool _window_main::check_xrd_files_exist()
{
  // check that there are a xrd folder
  if (QDir(Project_dir+"/xrd").exists()){
    // check that there are a xrd/raw folder
    if (QDir(Project_dir+"/xrd/raw").exists()){
      // check if there are files
      QDir Directory(Project_dir+"/xrd/raw/");

      QStringList Files_uxd = Directory.entryList(QStringList() << "*.uxd",QDir::Files);

      if (Files_uxd.size()>0) return true;

      QStringList Files_plv = Directory.entryList(QStringList() << "*.plv",QDir::Files);

      if (Files_plv.size()>0) return true;
    }
  }
  return false;
}

/*************************************************************************/
void _window_main::tabbar_clicked(int Index)
{
  Main_tab->blockSignals(true);
  Main_tab->setCurrentIndex(Index);
  Main_tab->blockSignals(false);

  Previous_tab=Current_tab;
  Current_tab=Index;

//  switch (Index){
//  case 1:
//    if (Previous_tab==0 && Image_exists==true){
////      QWidget* Current_widget = Main_tab->widget(Index);
////      Current_widget->setFocus();

////      Window_positions->load_project();

//      Previous_tab=Current_tab;
//      Current_tab=Index;
//    }
//    break;
//  case 2:
//    break;
//  case 3:
//    break;
//  }
}

/*************************************************************************/

void _window_main::read_settings()
{
  //  QSettings settings("./settings_"+_window_xmapslab_ns::Program_name.toLower()+".ini",QSettings::IniFormat);
  QSettings settings(Project_dir+"/settings.ini",QSettings::IniFormat);
  QStringList Allq=settings.allKeys();

  QRect Screen_size = QApplication::primaryScreen()->geometry();
  int Screen_width=Screen_size.width();
  int Screen_height=Screen_size.height();

  settings.beginGroup("General");
    Window_size=settings.value("size", size()).toSize();
    Window_position=settings.value("pos", QPoint((Screen_width-width())/2,(Screen_height-height())/2)).toPoint();
    UI_font_size=settings.value("UIFontSize",_common_ns::UI_FONT_SIZE_DEFAULT).toInt();
  settings.endGroup();

  settings.beginGroup("DisplayParameters");
    Display_font_size=settings.value("DisplayFontSize",_window_positions_ns::POSITIONS_DISPLAY_FONT_SIZE).toInt();
    Display_out_circle_size=settings.value("DisplayOutCircleSize",_window_positions_ns::POSITIONS_DISPLAY_OUT_CIRCLE_SIZE).toInt();
    Display_font_color=settings.value("DisplayFontColor",_window_positions_ns::POSITIONS_DISPLAY_FONT_COLOR).value<QColor>();
    Display_out_circle_color=settings.value("DisplayOutCircleColor",_window_positions_ns::POSITIONS_DISPLAY_OUT_CIRCLE_COLOR).value<QColor>();
    Display_in_circle_color=settings.value("DisplayInCircleColor",_window_positions_ns::POSITIONS_DISPLAY_IN_CIRCLE_COLOR).value<QColor>();
    Display_selection_out_circle_color=settings.value("DisplaySelectionOutCircleColor",_window_positions_ns::POSITIONS_DISPLAY_SELECTION_OUT_CIRCLE_COLOR).value<QColor>();
    Display_selection_in_circle_color=settings.value("DisplaySelectionInCircleColor",_window_positions_ns::POSITIONS_DISPLAY_SELECTION_IN_CIRCLE_COLOR).value<QColor>();
  settings.endGroup();

  // print
  settings.beginGroup("PrintParameters");
    Print_font_size=settings.value("PrintFontSize",_window_positions_ns::POSITIONS_DISPLAY_FONT_SIZE).toInt();
    Print_out_circle_size=settings.value("PrintOutCircleSize",_window_positions_ns::POSITIONS_DISPLAY_OUT_CIRCLE_SIZE).toInt();
    Print_font_color=settings.value("PrintFontColor",_window_positions_ns::POSITIONS_DISPLAY_FONT_COLOR).value<QColor>();
    Print_out_circle_color=settings.value("PrintOutCircleColor",_window_positions_ns::POSITIONS_DISPLAY_OUT_CIRCLE_COLOR).value<QColor>();
    Print_in_circle_color=settings.value("PrintInCircleColor",_window_positions_ns::POSITIONS_DISPLAY_IN_CIRCLE_COLOR).value<QColor>();
  settings.endGroup();

  Window_positions->read_settings();
#ifdef INTERPRETER
  Window_interpreter->read_settings();
#endif
  Window_xmapslab->read_settings();

  change_font_size(UI_font_size,Main_tab);
//  Window_tools->ui_font_size(UI_font_size);
//  Window_positions->ui_font_size(UI_font_size);
//  Window_interpreter->ui_font_size(UI_font_size);
//  Window_xmapslab->ui_font_size(UI_font_size);
}

/*************************************************************************/

void _window_main::save_settings()
{
  //  QSettings settings("./settings_"+_window_xmapslab_ns::Program_name.toLower()+".ini",QSettings::IniFormat);
  QSettings settings(Project_dir+"/settings.ini",QSettings::IniFormat);

  settings.beginGroup("General");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.setValue("UIFontSize",UI_font_size);
  settings.endGroup();

  settings.beginGroup("DisplayParameters");
    settings.setValue("DisplayFontSize", Display_font_size);
    settings.setValue("DisplayOutCircleSize", Display_out_circle_size);
    settings.setValue("DisplayFontColor", Display_font_color);
    settings.setValue("DisplayOutCircleColor", Display_out_circle_color);
    settings.setValue("DisplayInCircleColor", Display_in_circle_color);
    settings.setValue("DisplaySelectionOutCircleColor", Display_selection_out_circle_color);
    settings.setValue("DisplaySelectionInCircleColor", Display_selection_in_circle_color);
  settings.endGroup();

  settings.beginGroup("PrintParameters");
    settings.setValue("PrintFontSize", Print_font_size);
    settings.setValue("PrintOutCircleSize", Print_out_circle_size);
    settings.setValue("PrintFontColor", Print_font_color);
    settings.setValue("PrintOutCircleColor", Print_out_circle_color);
    settings.setValue("PrintInCircleColor", Print_in_circle_color);
  settings.endGroup();

}

/*************************************************************************/

void _window_main::closeEvent(QCloseEvent *Event)
{
  Window_positions->save_settings();
#ifdef INTERPRETER
  Window_interpreter->save_settings();
#endif
  Window_xmapslab->save_settings();

  save_settings();
  Event->accept();
}

/*************************************************************************/

void _window_main::ui_font_size(int UI_font_size1)
{
  UI_font_size=UI_font_size1;

  QFont Font(QApplication::font());
  Font.setPointSize(UI_font_size);
  QApplication::setFont(Font);

  change_font_size(UI_font_size,Main_tab);

//  Main_tab->setFont(Font);

//  Window_tools->ui_font_size(UI_font_size);
//  Window_positions->ui_font_size(UI_font_size);
//  Window_interpreter->ui_font_size(UI_font_size);
//  Window_xmapslab->ui_font_size(UI_font_size);

  save_settings();
}

/*************************************************************************/

void _window_main::parameters_changed()
{
  Window_positions->parameters_changed();
  Window_xmapslab->parameters_changed();

  save_settings();
}
