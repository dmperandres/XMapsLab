#include "window_tools.h"
#include "window_main.h"

/*************************************************************************/

_window_tools::_window_tools(_window_main *Window_main1)
{
#ifdef DEBUG_XML
  std::cout << "en _window_tools " << __LINE__ << std::endl;
#endif

  Window_main=Window_main1;

//  read_settings();

  QWidget *Widget=new QWidget;
//  Widget->setMinimumWidth(1000);

  QVBoxLayout *Vboxlayout=new QVBoxLayout(Widget);

  Actionbutton_create_project=new QPushButton("Create project");
  Actionbutton_create_project->setStyleSheet(_window_tools_ns::Style_enabled);
  connect(Actionbutton_create_project, SIGNAL(pressed()), this, SLOT(create_project_slot()));
  Vec_pushbuttons.push_back(Actionbutton_create_project);

  Actionbutton_open_project=new QPushButton("Open project");
  Actionbutton_open_project->setStyleSheet(_window_tools_ns::Style_enabled);
  connect(Actionbutton_open_project, SIGNAL(pressed()), this, SLOT(open_project_slot()));
  Vec_pushbuttons.push_back(Actionbutton_open_project);

  Actionbutton_add_image=new QPushButton("Add image to project");
  Actionbutton_add_image->setStyleSheet(_window_tools_ns::Style_enabled);
  connect(Actionbutton_add_image, SIGNAL(pressed()), this, SLOT(add_image_slot()));
  Vec_pushbuttons.push_back(Actionbutton_add_image);

#ifdef INTERPRETER
  Actionbutton_add_random_positions=new QPushButton("Add random positions to project_data.csv");
  //  Actionbutton_add_positions_csv->setEnabled(false);
  Actionbutton_add_random_positions->setStyleSheet(_window_tools_ns::Style_enabled);
  connect(Actionbutton_add_random_positions, SIGNAL(pressed()), this, SLOT(add_random_positions_slot()));
  Vec_pushbuttons.push_back(Actionbutton_add_random_positions);

  Actionbutton_add_positions_csv=new QPushButton("Add positions data (CSV) to project_data.csv");
//  Actionbutton_add_positions_csv->setEnabled(false);
  Actionbutton_add_positions_csv->setStyleSheet(_window_tools_ns::Style_enabled);
  connect(Actionbutton_add_positions_csv, SIGNAL(pressed()), this, SLOT(add_positions_data_csv_slot()));
  Vec_pushbuttons.push_back(Actionbutton_add_positions_csv);

  Actionbutton_add_artax_files_xrf=new QPushButton("Add ARTAX files (XRF) to project");
//  Actionbutton_add_artax_files_xrf->setEnabled(false);
  Actionbutton_add_artax_files_xrf->setStyleSheet(_window_tools_ns::Style_enabled);
  connect(Actionbutton_add_artax_files_xrf, SIGNAL(pressed()), this, SLOT(add_artax_files_slot()));
  Vec_pushbuttons.push_back(Actionbutton_add_artax_files_xrf);

  Actionbutton_add_xy_files_xrf=new QPushButton("Add XY files (XRF) to project");
  //  Actionbutton_add_artax_files_xrf->setEnabled(false);
  Actionbutton_add_xy_files_xrf->setStyleSheet(_window_tools_ns::Style_enabled);
  connect(Actionbutton_add_xy_files_xrf, SIGNAL(pressed()), this, SLOT(add_xy_files_slot()));
  Vec_pushbuttons.push_back(Actionbutton_add_xy_files_xrf);

  Actionbutton_add_uxd_files_xrd=new QPushButton("Add UXD files (XRD) to project");
//  Actionbutton_add_uxd_files_xrd->setEnabled(false);
  Actionbutton_add_uxd_files_xrd->setStyleSheet(_window_tools_ns::Style_enabled);
  connect(Actionbutton_add_uxd_files_xrd, SIGNAL(pressed()), this, SLOT(add_uxd_files_slot()));
  Vec_pushbuttons.push_back(Actionbutton_add_uxd_files_xrd);

  Actionbutton_add_plv_files_xrd=new QPushButton("Add PLV files (XRD) to project");
//  Actionbutton_add_plv_files_xrd->setEnabled(false);
  Actionbutton_add_plv_files_xrd->setStyleSheet(_window_tools_ns::Style_enabled);
  connect(Actionbutton_add_plv_files_xrd, SIGNAL(pressed()), this, SLOT(add_plv_files_slot()));
  Vec_pushbuttons.push_back(Actionbutton_add_plv_files_xrd);
#endif

  Actionbutton_add_xrf_data_csv_to_project_data_csv=new QPushButton("Add XRF data (CSV) to project_data.csv");
//  Actionbutton_add_xrf_data_csv_to_project_data_csv->setEnabled(false);
  Actionbutton_add_xrf_data_csv_to_project_data_csv->setStyleSheet(_window_tools_ns::Style_enabled);
  connect(Actionbutton_add_xrf_data_csv_to_project_data_csv, SIGNAL(pressed()), this, SLOT(xrf_data_csv_to_project_data_slot()));
  Vec_pushbuttons.push_back(Actionbutton_add_xrf_data_csv_to_project_data_csv);

  Actionbutton_add_xrd_data_csv_to_project_data_csv=new QPushButton("Add XRD data (CSV) to project_data.csv");
//  Actionbutton_add_xrd_data_csv_to_project_data_csv->setEnabled(false);
  Actionbutton_add_xrd_data_csv_to_project_data_csv->setStyleSheet(_window_tools_ns::Style_enabled);
  connect(Actionbutton_add_xrd_data_csv_to_project_data_csv, SIGNAL(pressed()), this, SLOT(xrd_data_csv_to_project_data_slot()));
  Vec_pushbuttons.push_back(Actionbutton_add_xrd_data_csv_to_project_data_csv);

  Actionbutton_options=new QPushButton("Options");
//  Actionbutton_options->setEnabled(false);
  Actionbutton_options->setStyleSheet(_window_tools_ns::Style_enabled);
  connect(Actionbutton_options, SIGNAL(pressed()), this, SLOT(options_slot()));
  Vec_pushbuttons.push_back(Actionbutton_options);

  hide_all();

  QPushButton *Actionbutton_exit=new QPushButton("Exit");
  Actionbutton_exit->setStyleSheet(_window_tools_ns::Style_enabled);
  connect(Actionbutton_exit, SIGNAL(pressed()), Window_main, SLOT(close()));
  Vec_pushbuttons.push_back(Actionbutton_exit);

  QFont Font = font();
  Font.setPointSize(Window_main->ui_font_size()*1.5);
  for (unsigned int i=0;i<Vec_pushbuttons.size();i++) Vec_pushbuttons[i]->setFont(Font);

  //
//  Vboxlayout->addWidget(Widget_aux);
//  Vboxlayout->addWidget(Line);
//  Vboxlayout->addWidget(toolButton);
  Vboxlayout->addWidget(Actionbutton_create_project);
  Vboxlayout->addWidget(Actionbutton_open_project);
  Vboxlayout->addWidget(Actionbutton_add_image);
#ifdef INTERPRETER
  Vboxlayout->addWidget(Actionbutton_add_random_positions);
  Vboxlayout->addWidget(Actionbutton_add_positions_csv);
  Vboxlayout->addWidget(Actionbutton_add_artax_files_xrf);
  Vboxlayout->addWidget(Actionbutton_add_xy_files_xrf);
  Vboxlayout->addWidget(Actionbutton_add_uxd_files_xrd);
  Vboxlayout->addWidget(Actionbutton_add_plv_files_xrd);
#endif
  Vboxlayout->addWidget(Actionbutton_add_xrf_data_csv_to_project_data_csv);
  Vboxlayout->addWidget(Actionbutton_add_xrd_data_csv_to_project_data_csv);
  Vboxlayout->addWidget(Actionbutton_options);
  Vboxlayout->addWidget(Actionbutton_exit);
  Vboxlayout->addStretch();
//  Vboxlayout->addWidget(Menu);

  Widget->setLayout(Vboxlayout);

  setCentralWidget(Widget);

  //
//  setWindowTitle(_window_tools_ns::Program_name);
}

/*************************************************************************/

_window_tools::~_window_tools()
{
#ifdef DEBUG_XML
  std::cout << "terminando window" <<endl;
#endif
}

/*************************************************************************/

void _window_tools::read_settings()
{
//  Window_main->read_settings();

//  ui_font_size();
}

/*************************************************************************/

void _window_tools::save_settings()
{
//  QSettings settings(Project_dir+"/settings_"+_window_tools_ns::Program_name.toLower()+".ini",QSettings::IniFormat);
//  QSettings settings(Project_dir+"/settings.ini",QSettings::IniFormat);

}

/*************************************************************************/

void _window_tools::project_parameters(QString Project_folder_name1, QString Project_name1, QString Author1, QString Date1, QString Device1, QString Tube1, QString Widht_cm1, QString Height_cm1)
{
  Project_folder_name=Project_folder_name1;
  Project_data.Project_name=Project_name1.toStdString();
  Project_data.Author=Author1.toStdString();
  Project_data.Date=Date1.toStdString();
  Project_data.Device=Device1.toStdString();

  int i;
  for (i=0;i<int(_data_xrd_ns::Vec_tube_name.size());i++){
    if (Tube1.toStdString()==_data_xrd_ns::Vec_tube_name[i].toStdString()) break;
  }
  Project_data.XRD_tube_type=_data_xrd_ns::_tube_type(i);

  Project_data.Width_cm=Widht_cm1.toFloat();
  Project_data.Height_cm=Height_cm1.toFloat();
}

/*************************************************************************/

void _window_tools::create_project_slot()
{
  _w_project  *W_project=new _w_project(this);
  connect(W_project,SIGNAL(accepted()),W_project,SLOT(close()));
  W_project->raise();

  if (W_project->exec()==QDialog::Accepted){
    // remove carriage return
//    Project_data.Project_name.erase(remove(Project_data.Project_name.begin(),Project_data.Project_name.end(),'\r'), Project_data.Project_name.end());
    Project_folder_name.remove('\r');
    // remove blank spaces at the beginning
    Project_folder_name.remove(' ');
    // remove tabs
    Project_folder_name.remove('\t');
    Project_folder_name.replace('-','_');

    QString Project_name=Project_folder_name;
    QDir Path_dir("projects/"+Project_name);
    if (!Path_dir.exists()){
      Project_dir=Path_dir.absolutePath();

//      Opened_project->setText(Project_name);

      QDir().mkdir("projects/"+Project_name);
      QDir().mkdir("projects/"+Project_name+"/images");
      QDir().mkdir("projects/"+Project_name+"/positions");
      QDir().mkdir("projects/"+Project_name+"/xrf");
      QDir().mkdir("projects/"+Project_name+"/xrf/raw");
      QDir().mkdir("projects/"+Project_name+"/xrf/maps");
      QDir().mkdir("projects/"+Project_name+"/xrf/graphs");
#ifdef XRD_ACTIVE
      QDir().mkdir("projects/"+Project_name+"/xrd");
      QDir().mkdir("projects/"+Project_name+"/xrd/raw");
      QDir().mkdir("projects/"+Project_name+"/xrd/maps");
      QDir().mkdir("projects/"+Project_name+"/xrd/graphs");
#endif

      //
      _data_io::save_project_data_csv(this,Project_dir.toStdString(),Project_data);

      QMessageBox::information(this, tr("Information"),tr("The project has been correctly created"));

      Actionbutton_add_image->show();
#ifdef INTERPRETER
      Actionbutton_add_random_positions->show();
#endif

      Actionbutton_options->show();

      // pass the name of the project dir to all programs
      Window_main->project_dir(Project_dir);

    }
    else{
      QMessageBox::critical(this, tr("Error"),"The folder with name "+Project_name+" already exists");
    }
  }
}

/*************************************************************************/

void _window_tools::open_project_slot()
{
  bool Accepted=false;
  int Result;
  QString Project_folder_name;

  do{
    _w_directory Dialog(this,"Select project directory","projects",&Project_folder_name);

    Result=Dialog.exec();
    if (Result==QDialog::Accepted){
      if (Project_folder_name!=""){
        // check that is a valid project
        QString File_path = Project_folder_name+"/project_data.csv";
        QFile File(File_path);
        // Verifica si el archivo existe
        if (File.exists()) Accepted=true;
        else{
          QMessageBox::information(this,"Information","Please, select a <b>valid folder</b> or click on 'Cancel' button");
        }
      }
      else QMessageBox::information(this,"Information","Please, select a <b>valid folder</b> or click on 'Cancel' button");
    }
    else Accepted=true;
  } while (Accepted==false);

  if (Result==QDialog::Accepted){
    QDir Dir(Project_folder_name);
    Project_dir=Dir.absolutePath();

    QStringList Parts = Project_folder_name.split("/");

    Actionbutton_add_image->show();
#ifdef INTERPRETER
    Actionbutton_add_random_positions->show();
#endif

    // check if the image has been added to the project
    QDir Directory_images(Project_dir+"/images");
    std::string Dir_images=Directory_images.absolutePath().toStdString();

    // check if therea are image files
    QStringList Files_images = Directory_images.entryList(QStringList() << "*.png" << "*.jpg", QDir::Files);

    if (Files_images.size()>0){
      show_all();
    }

    Actionbutton_options->show();

    // pass the name of the project dir to all programs
    Window_main->project_dir(Project_dir);
  }
}

/*************************************************************************/

void _window_tools::add_image_slot()
{
  if (QFile::exists(Project_dir+"/images/")){
    QDir Directory_images(Project_dir+"/images");
    std::string Dir_images=Directory_images.absolutePath().toStdString();

    // check if therea are image files
    QStringList Filters;
    Filters << "*.png" << "*.jpg";

    QStringList Files_images = Directory_images.entryList(Filters, QDir::Files);

    if (Files_images.size()==0){
      // there are not images
      QString File_image;
      _w_directory Dialog(this,"Select the image file","projects",&File_image,_w_directory::MODE_FILE,Filters);

      if (Dialog.exec()==QDialog::Accepted && File_image!=""){
        _w_image W_image(this,File_image);
        if (W_image.exec()==QDialog::Accepted){
          QImage Image;

          Image.load(File_image);
          int Width_aux=Image.width();
          int Height_aux=Image.height();

          adjust_image_sizes(Width_aux,Height_aux);
          if (Width_aux!=Image.width() || Height_aux!=Image.height()){
            Image=Image.scaled(QSize(Width_aux,Height_aux),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
          }

          Project_data.Width_pixel=Width_aux;
          Project_data.Height_pixel=Height_aux;
          // save the image dimensions
          _data_io::save_project_data_csv(this,Project_dir.toStdString(),Project_data);

          //
          QFileInfo File_info(File_image);
          QString Base_name=File_info.baseName();
          QString File_name_out=Project_dir+"/images/"+Base_name+".png";
          Image.save(File_name_out);
          QMessageBox::information(this, tr("Information"),tr("The image has been correctly copied"));

#ifdef INTERPRETER
          Actionbutton_add_positions_csv->setEnabled(true);
          Actionbutton_add_positions_csv->setStyleSheet(_window_tools_ns::Style_enabled);

          Actionbutton_add_random_positions->setEnabled(true);
          Actionbutton_add_random_positions->setStyleSheet(_window_tools_ns::Style_enabled);

          Actionbutton_add_artax_files_xrf->setEnabled(true);
          Actionbutton_add_artax_files_xrf->setStyleSheet(_window_tools_ns::Style_enabled);

          Actionbutton_add_uxd_files_xrd->setEnabled(true);
          Actionbutton_add_uxd_files_xrd->setStyleSheet(_window_tools_ns::Style_enabled);

          Actionbutton_add_plv_files_xrd->setEnabled(true);
          Actionbutton_add_plv_files_xrd->setStyleSheet(_window_tools_ns::Style_enabled);
#endif
          Actionbutton_add_xrf_data_csv_to_project_data_csv->setEnabled(true);
          Actionbutton_add_xrf_data_csv_to_project_data_csv->setStyleSheet(_window_tools_ns::Style_enabled);

          Actionbutton_add_xrd_data_csv_to_project_data_csv->setEnabled(true);
          Actionbutton_add_xrd_data_csv_to_project_data_csv->setStyleSheet(_window_tools_ns::Style_enabled);

          Window_main->check_project_state();
        }
      }
    }
    else{
      // there is at leas one image
      QMessageBox::information(this, tr("Information"),tr("There is at least one image<br>Your are going to add a new image"));

      QString File_image;
      _w_directory Dialog(this,"Select the image file","projects",&File_image,_w_directory::MODE_FILE,Filters);

      if (Dialog.exec()==QDialog::Accepted && File_image!=""){
        // show the selected image
        _w_image W_image(this,File_image);
        if (W_image.exec()==QDialog::Accepted){

          QImage Image;

          Image.load(File_image);
          int Width_aux=Image.width();
          int Height_aux=Image.height();

          if (Window_main->Project_data.Width_original_pixel!=0 && Window_main->Project_data.Height_original_pixel!=0){
            QMessageBox::warning(this, tr("Warning"),tr("The width and height values of the image are different from the respective values stored in the <b>project_data.csv</b> file<br>The image will be resized!"));

            if (Window_main->Project_data.Width_original_pixel!=Width_aux || Window_main->Project_data.Height_original_pixel!=Height_aux){

              Image=Image.scaled(QSize(Window_main->Project_data.Width_original_pixel,Window_main->Project_data.Height_original_pixel),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
            }
          }

          QFileInfo File_info(File_image);
          QString Base_name=File_info.baseName();
          QString File_name_out=Project_dir+"/images/"+Base_name+".png";

          if(QFileInfo::exists(File_name_out)){
            QString Message="The image file <b>"+Base_name+".png</b> exists<br>Please, introduce a new name";
            QMessageBox::information(this, tr("Information"),Message);

            File_image=QFileDialog::getSaveFileName(this, "Save image", Project_dir+"/images", "Images (*.png)");

            if (File_image.isEmpty()){
              QMessageBox::information(this, tr("Information"),tr("The name is empty. The image will not be copied"));
              return;
            }

            File_name_out=File_image;
          }

          Image.save(File_name_out);
          QMessageBox::information(this, tr("Information"),tr("The image has been correctly copied"));

          Project_data.Width_pixel=Project_data.Width_original_pixel;
          Project_data.Height_pixel=Project_data.Height_original_pixel;
          // save the image dimensions
           _data_io::save_project_data_csv(this,Project_dir.toStdString(),Project_data);

#ifdef INTERPRETER
          Actionbutton_add_positions_csv->setEnabled(true);
          Actionbutton_add_positions_csv->setStyleSheet(_window_tools_ns::Style_enabled);

          Actionbutton_add_random_positions->setEnabled(true);
          Actionbutton_add_random_positions->setStyleSheet(_window_tools_ns::Style_enabled);

          Actionbutton_add_artax_files_xrf->setEnabled(true);
          Actionbutton_add_artax_files_xrf->setStyleSheet(_window_tools_ns::Style_enabled);

          Actionbutton_add_uxd_files_xrd->setEnabled(true);
          Actionbutton_add_uxd_files_xrd->setStyleSheet(_window_tools_ns::Style_enabled);

          Actionbutton_add_plv_files_xrd->setEnabled(true);
          Actionbutton_add_plv_files_xrd->setStyleSheet(_window_tools_ns::Style_enabled);
#endif
          Actionbutton_add_xrf_data_csv_to_project_data_csv->setEnabled(true);
          Actionbutton_add_xrf_data_csv_to_project_data_csv->setStyleSheet(_window_tools_ns::Style_enabled);

          Actionbutton_add_xrd_data_csv_to_project_data_csv->setEnabled(true);
          Actionbutton_add_xrd_data_csv_to_project_data_csv->setStyleSheet(_window_tools_ns::Style_enabled);

          Window_main->check_project_state();
        }
      }
    }
  }
  else{
    QMessageBox::critical(this, tr("Error"),"There is not 'images' folder<br>Please create a folder called 'images' in project folder");
    QApplication::quit();
    exit(-1);
  }
}

/*************************************************************************/

void _window_tools::add_positions_data_csv_slot()
{
  if (_data_io::load_project_data_csv(this,Project_dir.toStdString(),Project_data,Vec_names_xrf_pdb,Vec_names_xrd_pdb)){
    QString File_positions_csv;
    _w_directory Dialog(this,"Select the CSV file with the POSITIONS data","projects",&File_positions_csv,_w_directory::MODE_FILE);

    if (Dialog.exec()==QDialog::Accepted && File_positions_csv!=""){
      if (_data_io::load_positions_data_csv(this,File_positions_csv.toStdString(),Project_data)){
        // save data
        Project_data.Width_pixel=Project_data.Width_original_pixel;
        Project_data.Height_pixel=Project_data.Height_original_pixel;
        Project_data.Vec_coordinate_x=Project_data.Vec_coordinate_x_original;
        Project_data.Vec_coordinate_y=Project_data.Vec_coordinate_y_original;

        _data_io::save_project_data_csv(this,Project_dir.toStdString(),Project_data);

        Window_main->check_project_state();
      }
    }
  }
}

/*************************************************************************/

void _window_tools::add_random_positions_slot()
{
  if (_data_io::load_project_data_csv(this,Project_dir.toStdString(),Project_data,Vec_names_xrf_pdb,Vec_names_xrd_pdb)){
    int Number;
    _w_read_int Dialog(this,&Number);

    if (Dialog.exec()==QDialog::Accepted){
      // save data
      if (Number>0){
        // save a fake image
        QImage Imagen(100, 100, QImage::Format_RGB32);
        Imagen.fill(QColor(Qt::red));
        Imagen.save(Project_dir+"/images/fake.png");

        // save fake positions
        std::random_device RD;
        std::mt19937 Generator(RD());
        std::uniform_int_distribution<int> Distribution(0, 99);

        Project_data.Width_pixel=100;
        Project_data.Height_pixel=100;

        Project_data.Vec_coordinate_x.resize(Number);
        Project_data.Vec_coordinate_y.resize(Number);
        for (int i=0;i<Number;i++){
          Project_data.Vec_coordinate_x[i]=Distribution(Generator);
          Project_data.Vec_coordinate_y[i]=Distribution(Generator);
        }

        _data_io::save_project_data_csv(this,Project_dir.toStdString(),Project_data);

        Window_main->check_project_state();
      }
      else{
        QMessageBox::warning(this, tr("Warning"),"Please, introduce a number greater than 0");
      }
    }
  }
}

/*************************************************************************/

void _window_tools::add_artax_files_slot()
{
  if (QFile::exists(Project_dir+"/xrf")){
    if (QFile::exists(Project_dir+"/xrf/raw/")){
      QString Folder_artax_files;
      _w_directory Dialog(this,"Select the directory with ARTAX files","projects",&Folder_artax_files);

      if (Dialog.exec()==QDialog::Accepted && Folder_artax_files!=""){
        QDir Directory(Folder_artax_files);
        QStringList Files_artax = Directory.entryList(QStringList() << "*.txt",QDir::Files);

        _w_files W_files(this,Files_artax);
        if (W_files.exec()==QDialog::Accepted){
          add_artax_files(Folder_artax_files,Files_artax);

          Window_main->check_project_state();
        }
      }
    }
    else{
      QMessageBox::critical(this, tr("Error"),"There is not 'xrf/raw' folder");
      QApplication::quit();
      exit(-1);
    }
  }
  else{
    QMessageBox::critical(this, tr("Error"),"There is not 'xrf' folder");
    QApplication::quit();
    exit(-1);
  }
}

/*************************************************************************/

void _window_tools::add_xy_files_slot()
{
  if (QFile::exists(Project_dir+"/xrf")){
    if (QFile::exists(Project_dir+"/xrf/raw/")){
      QString Folder_xy_files;
      _w_directory Dialog(this,"Select the directory with XY files","projects",&Folder_xy_files);

      if (Dialog.exec()==QDialog::Accepted && Folder_xy_files!=""){
        QDir Directory(Folder_xy_files);
        QStringList Files_xy = Directory.entryList(QStringList() << "*.XY",QDir::Files);

        _w_files W_files(this,Files_xy);
        if (W_files.exec()==QDialog::Accepted){
          add_xy_files(Folder_xy_files,Files_xy);

          Window_main->check_project_state();
        }
      }
    }
    else{
      QMessageBox::critical(this, tr("Error"),"There is not 'xrf/raw' folder");
      QApplication::quit();
      exit(-1);
    }
  }
  else{
    QMessageBox::critical(this, tr("Error"),"There is not 'xrf' folder");
    QApplication::quit();
    exit(-1);
  }
}

/*************************************************************************/

void _window_tools::add_uxd_files_slot()
{
  if (QFile::exists(Project_dir+"/xrd")){
    if (QFile::exists(Project_dir+"/xrd/raw/")){
      QString Folder_uxd_files;
      _w_directory Dialog(this,"Select the directory with UXD files","projects",&Folder_uxd_files);

      if (Dialog.exec()==QDialog::Accepted && Folder_uxd_files!=""){
        QDir Directory(Folder_uxd_files);
        QStringList Files_uxd = Directory.entryList(QStringList() << "*.uxd",QDir::Files);
        _w_files W_files(this,Files_uxd);
        if (W_files.exec()==QDialog::Accepted){
          add_uxd_files(Folder_uxd_files,Files_uxd);

          Window_main->check_project_state();
        }
      }
    }
    else{
      QMessageBox::critical(this, tr("Error"),"There is not 'xrd/raw' folder");
      QApplication::quit();
      exit(-1);
    }
  }
  else{
    QMessageBox::critical(this, tr("Error"),"There is not 'xrd' folder");
    QApplication::quit();
    exit(-1);
  }
}

void _window_tools::add_plv_files_slot()
{
  if (QFile::exists(Project_dir+"/xrd")){
    if (QFile::exists(Project_dir+"/xrd/raw/")){
      QString Folder_plv_files;
      _w_directory Dialog(this,"Select the directory with PLV files","projects",&Folder_plv_files);

      if (Dialog.exec()==QDialog::Accepted && Folder_plv_files!=""){
        QDir Directory(Folder_plv_files);
        QStringList Files_plv = Directory.entryList(QStringList() << "*.plv",QDir::Files);
        _w_files W_files(this,Files_plv);
        if (W_files.exec()==QDialog::Accepted){
          add_plv_files(Folder_plv_files,Files_plv);

          Window_main->check_project_state();
        }
      }
    }
    else{
      QMessageBox::critical(this, tr("Error"),"There is not 'xrd/raw' folder");
      QApplication::quit();
      exit(-1);
    }
  }
  else{
    QMessageBox::critical(this, tr("Error"),"There is not 'xrd' folder");
    QApplication::quit();
    exit(-1);
  }
}

/*************************************************************************/

//void _window_tools::add_plv_files_slot()
//{
//  if (QFile::exists(Project_dir+"/xrd")){
//    if (QFile::exists(Project_dir+"/xrd/raw/")){
//      QFileDialog Dialog(this, tr("Select the directory with PLV files"),"./projects");
//      Dialog.setFileMode(QFileDialog::Directory);
//      Dialog.setOption(QFileDialog::ShowDirsOnly,false);
//      Dialog.setOption(QFileDialog::DontUseNativeDialog,true);
//      if (Dialog.exec()==QDialog::Accepted){
//        QString Files_dir=Dialog.directory().absolutePath();
//        QDir Directory(Files_dir);
//        QStringList Files_plv = Directory.entryList(QStringList() << "*.plv",QDir::Files);

//        _w_files W_files(this,Files_plv);
//        if (W_files.exec()==QDialog::Accepted){
//          add_plv_files(Files_dir,Files_plv);

//          Window_main->check_project_state();
//        }
//      }
//    }
//    else{
//      QMessageBox::critical(this, tr("Error"),"There is not 'xrd/raw' folder");
//      QApplication::quit();
//      exit(-1);
//    }
//  }
//  else{
//    QMessageBox::critical(this, tr("Error"),"There is not 'xrd/raw' folder");
//    QApplication::quit();
//    exit(-1);
//  }
//}

/*************************************************************************/

void _window_tools::add_artax_files(QString Files_dir,QStringList Files_artax)
{
  if (Files_artax.size()>0){
    // check that numbers are not repeated
    std::vector<int> Positions;
    foreach(QString File_name, Files_artax){
      QString File_name1=File_name;
//      File_name1.replace('-','_');
//      QStringList Tokens=File_name1.split('_');

      // get the first 3 characters
      QString Number=File_name1.left(3);

      // check that the first 3 characters are numbers
      bool Is_digit = true;
      for (int i = 0; i < Number.length(); i++) {
        QChar Character = Number.at(i);
        if (Character.isDigit()==false){
          Is_digit = false;
          break;
        }
      }

      if  (Is_digit==true){
        int Result=Number.toInt();
        if (Result>0) Positions.push_back(Result);
        else{
          QMessageBox::critical(this, tr("Error"),"The file "+File_name+" has not a valid value beacuse it is 0 or negative");
          QApplication::quit();
          exit(-1);
        }
      }
      else{
        QMessageBox::critical(this, tr("Error"),"The file <b>"+File_name+"</b> has not a valid number format: 3 numbers indicating the measurement position and starting at 1. For example, 001");
        QApplication::quit();
        exit(-1);
      }
    }

    sort(Positions.begin(),Positions.end());
    auto Result=std::adjacent_find(Positions.begin(),Positions.end());
    if (Result!=Positions.end()){
      QMessageBox::critical(this, tr("Error"),tr("There are 'artax.txt' files with the same number"));
      QApplication::quit();
      exit(-1);
    }

    //
    foreach(QString File_name, Files_artax){
      QString File_name1=File_name;
      File_name1=File_name1.toLower();

      File_name1.replace(' ','_');
      File_name1.replace('-','_');

      // regular expresion
      QRegularExpression Regex("_+");
      File_name1.replace(Regex, "_");

      File_name1.replace("_.",".");

      // remove the .txt
      int Pos=File_name1.lastIndexOf('.');
      File_name1=File_name1.left(Pos);

      // check that the fourth character is an under bar
      int Position;
      if (File_name1[3]=='_'){
        QStringList Tokens=File_name1.split('_');
        // convert to the format
        Position=Tokens[0].toInt();
        File_name1=File_name1.mid(4);
      }
      else{
        QString Number=File_name1.left(3);
        Position=Number.toInt();
        File_name1=File_name1.mid(3);
      }

      // convert the value of the position to the format
      QString Position_string=QStringLiteral("%1").arg(Position,3,10,QChar('0'));

      QString Final_name=Position_string+"_"+File_name1+".txt";

      if (QFile::exists(Project_dir+"/xrf/raw/"+Final_name)){
        QFile::remove(Project_dir+"/xrf/raw/"+Final_name);
      }

      QFile::copy(Files_dir+"/"+File_name,Project_dir+"/xrf/raw/"+Final_name);
    }

    QMessageBox::information(this, tr("Information"),tr("The XRF files have been correctly copied"));
  }
  else{
    QMessageBox::critical(this, tr("Error"),tr("There are not '.txt' files"));
  }
}

/*************************************************************************/

void _window_tools::add_xy_files(QString Files_dir,QStringList Files_xy)
{
  if (Files_xy.size()>0){
    // check that numbers are not repeated
    std::vector<int> Positions;
    foreach(QString File_name, Files_xy){
      QString File_name1=File_name;
      //      File_name1.replace('-','_');
      //      QStringList Tokens=File_name1.split('_');

      // get the first 3 characters
      QString Number=File_name1.left(3);

      // check that the first 3 characters are numbers
      bool Is_digit = true;
      for (int i = 0; i < Number.length(); i++) {
        QChar Character = Number.at(i);
        if (Character.isDigit()==false){
          Is_digit = false;
          break;
        }
      }

      if  (Is_digit==true){
        int Result=Number.toInt();
        if (Result>0) Positions.push_back(Result);
        else{
          QMessageBox::critical(this, tr("Error"),"The file "+File_name+" has not a valid value beacuse it is 0 or negative");
          QApplication::quit();
          exit(-1);
        }
      }
      else{
        QMessageBox::critical(this, tr("Error"),"The file <b>"+File_name+"</b> has not a valid number format: 3 numbers indicating the measurement position and starting at 1. For example, 001");
        QApplication::quit();
        exit(-1);
      }
    }

    sort(Positions.begin(),Positions.end());
    auto Result=std::adjacent_find(Positions.begin(),Positions.end());
    if (Result!=Positions.end()){
      QMessageBox::critical(this, tr("Error"),tr("There are 'artax.txt' files with the same number"));
      QApplication::quit();
      exit(-1);
    }

    //
    foreach(QString File_name, Files_xy){
      QString File_name1=File_name;
      File_name1=File_name1.toLower();

      File_name1.replace(' ','_');
      File_name1.replace('-','_');

      // regular expresion
      QRegularExpression Regex("_+");
      File_name1.replace(Regex, "_");

      File_name1.replace("_.",".");

      // remove the .txt
      int Pos=File_name1.lastIndexOf('.');
      File_name1=File_name1.left(Pos);

      // check that the fourth character is an under bar
      int Position;
      if (File_name1[3]=='_'){
        QStringList Tokens=File_name1.split('_');
        // convert to the format
        Position=Tokens[0].toInt();
        File_name1=File_name1.mid(4);
      }
      else{
        QString Number=File_name1.left(3);
        Position=Number.toInt();
        File_name1=File_name1.mid(3);
      }

      // convert the value of the position to the format
      QString Position_string=QStringLiteral("%1").arg(Position,3,10,QChar('0'));

      QString Final_name=Position_string+"_"+File_name1+".xy";

      if (QFile::exists(Project_dir+"/xrf/raw/"+Final_name)){
        QFile::remove(Project_dir+"/xrf/raw/"+Final_name);
      }

      QFile::copy(Files_dir+"/"+File_name,Project_dir+"/xrf/raw/"+Final_name);
    }

    QMessageBox::information(this, tr("Information"),tr("The XY files have been correctly copied"));
  }
  else{
    QMessageBox::critical(this, tr("Error"),tr("There are not '.XY' files"));
  }
}

/*************************************************************************/

//void _window_tools::xrf_add_all_files_slot()
//{
//  if (QFile::exists(Project_dir+"/xrf/")){
//    if (QFile::exists(Project_dir+"/xrf/raw/")){

//      QString Directory_name;
//      _w_directory Dialog(this,"projects",&Directory_name);

//      if (Dialog.exec()==QDialog::Accepted && Directory_name!=""){
//        QDir Dir(Directory_name);
//        QStringList Files_artax = Dir.entryList(QStringList() << "*.txt",QDir::Files);

//        _w_files W_files(this,Files_artax);
//        if (W_files.exec()==QDialog::Accepted){
//          add_xrf_files(Directory_name,Files_artax);
//        }
//      }
//    }
//    else{
//      QMessageBox::critical(this, tr("Error"),"There is not 'xrf/raw' folder");
//      QApplication::quit();
//      exit(-1);
//    }
//  }
//  else{
//    QMessageBox::critical(this, tr("Error"),"There is not 'xrf' folder");
//    QApplication::quit();
//    exit(-1);
//  }
//}

/*************************************************************************/

//void _window_tools::xrf_add_selected_files_slot()
//{
//  if (QFile::exists(Project_dir+"/xrf/")){
//    if (QFile::exists(Project_dir+"/xrf/raw/")){
//      QFileDialog Dialog(this, tr("Select the directory with XRF files"),"./projects");
//      Dialog.setNameFilter(tr("XRF (*artax.txt)"));
//      Dialog.setFileMode(QFileDialog::ExistingFiles);
//      Dialog.setOption(QFileDialog::DontUseNativeDialog,true);
//      if (Dialog.exec()==QDialog::Accepted){
//        QStringList Files_artax;
//        QString Files_dir=Dialog.directory().absolutePath();
//        Files_artax=Dialog.selectedFiles();

//        // leave only the name of the file
//        for (int i=0;i<Files_artax.size();i++){
//          QString File_name=Files_artax[i];
//          int Pos=File_name.lastIndexOf('/');
//          Files_artax[i]=File_name.right(File_name.size()-Pos-1);
//        }

//        _w_files W_files(this,Files_artax);
//        if (W_files.exec()==QDialog::Accepted){
//          add_xrf_files(Files_dir,Files_artax);
//        }
//      }
//    }
//    else{
//      QMessageBox::critical(this, tr("Error"),"There is not 'xrf/raw' folder");
//      QApplication::quit();
//      exit(-1);
//    }
//  }
//  else{
//    QMessageBox::critical(this, tr("Error"),"There is not 'xrf' folder");
//    QApplication::quit();
//    exit(-1);
//  }
//}

/*************************************************************************/
#ifdef XRD_ACTIVE
void _window_tools::add_uxd_files(QString Files_dir,QStringList Files_uxd)
{
  if (Files_uxd.size()>0){
    // check that numbers are not repeated
    std::vector<int> Positions;
    foreach(QString File_name, Files_uxd){
      QString File_name1=File_name;

      // get the first 3 characters
      QString Number=File_name1.left(3);

      // check that the first 3 characters are numbers
      bool Is_digit = true;
      for (int i = 0; i < Number.length(); i++) {
        QChar Character = Number.at(i);
        if (Character.isDigit()==false){
          Is_digit = false;
          break;
        }
      }

      if  (Is_digit==true){
        int Result=Number.toInt();
        if (Result>0) Positions.push_back(Result);
        else{
          QMessageBox::critical(this, tr("Error"),"The file "+File_name+" has not a valid value beacuse it is 0 or negative");
          QApplication::quit();
          exit(-1);
        }
      }
      else{
        QMessageBox::critical(this, tr("Error"),"The file <b>"+File_name+"</b> has not a valid number format: 3 numbers indicating the measurement position and starting at 1. For example, 001");
        QApplication::quit();
        exit(-1);
      }
    }

    sort(Positions.begin(),Positions.end());
    auto Result=std::adjacent_find(Positions.begin(),Positions.end());
    if (Result!=Positions.end()){
      QMessageBox::critical(this, tr("Error"),tr("there are .uxd files with the same number"));
      QApplication::quit();
      exit(-1);
    }

    //
    foreach(QString File_name, Files_uxd){
      QString File_name1=File_name;
      File_name1=File_name1.toLower();

      File_name1.replace(' ','_');
      File_name1.replace('-','_');

      // regular expresion
      QRegularExpression Regex("_+");
      File_name1.replace(Regex, "_");

      File_name1.replace("_.",".");

      // remove the .uxd
      int Pos=File_name1.lastIndexOf('.');
      File_name1=File_name1.left(Pos);

      // check that the fourth character is an under bar
      int Position;
      if (File_name1[3]=='_'){
        QStringList Tokens=File_name1.split('_');
        // convert to the format
        Position=Tokens[0].toInt();
        File_name1=File_name1.mid(4);
      }
      else{
        QString Number=File_name1.left(3);
        Position=Number.toInt();
        File_name1=File_name1.mid(3);
      }

      // convert the value of the position to the format
      QString Position_string=QStringLiteral("%1").arg(Position,3,10,QChar('0'));

      QString Final_name=Position_string+"_"+File_name1+".uxd";

      if (QFile::exists(Project_dir+"/xrd/raw/"+Final_name)){
        QFile::remove(Project_dir+"/xrd/raw/"+Final_name);
      }

      QFile::copy(Files_dir+"/"+File_name,Project_dir+"/xrd/raw/"+Final_name);
    }

    QMessageBox::information(this, tr("Information"),tr("The XRD files have been correctly copied"));
  }
  else{
    QMessageBox::critical(this, tr("Error"),tr("There are not '.uxd' files"));
  }
}

/*************************************************************************/

void _window_tools::add_plv_files(QString Files_dir,QStringList Files_plv)
{
  if (Files_plv.size()>0){
    // check that numbers are not repeated
    std::vector<int> Positions;
    foreach(QString File_name, Files_plv){
      QString File_name1=File_name;

      // get the first 3 characters
      QString Number=File_name1.left(3);

      // check that the first 3 characters are numbers
      bool Is_digit = true;
      for (int i = 0; i < Number.length(); i++) {
        QChar Character = Number.at(i);
        if (Character.isDigit()==false){
          Is_digit = false;
          break;
        }
      }

      if  (Is_digit==true){
        int Result=Number.toInt();
        if (Result>0) Positions.push_back(Result);
        else{
          QMessageBox::critical(this, tr("Error"),"The file "+File_name+" has not a valid value beacuse it is 0 or negative");
          QApplication::quit();
          exit(-1);
        }
      }
      else{
        QMessageBox::critical(this, tr("Error"),"The file <b>"+File_name+"</b> has not a valid number format: 3 numbers indicating the measurement position and starting at 1. For example, 001");
        QApplication::quit();
        exit(-1);
      }
    }

    sort(Positions.begin(),Positions.end());
    auto Result=std::adjacent_find(Positions.begin(),Positions.end());
    if (Result!=Positions.end()){
      QMessageBox::critical(this, tr("Error"),tr("there are .plv files with the same number"));
      QApplication::quit();
      exit(-1);
    }

    //
    foreach(QString File_name, Files_plv){
      QString File_name1=File_name;
      File_name1=File_name1.toLower();

      File_name1.replace(' ','_');
      File_name1.replace('-','_');

      // regular expresion
      QRegularExpression Regex("_+");
      File_name1.replace(Regex, "_");

      File_name1.replace("_.",".");

      // remove the .uxd
      int Pos=File_name1.lastIndexOf('.');
      File_name1=File_name1.left(Pos);

      // check that the fourth character is an under bar
      int Position;
      if (File_name1[3]=='_'){
        QStringList Tokens=File_name1.split('_');
        // convert to the format
        Position=Tokens[0].toInt();
        File_name1=File_name1.mid(4);
      }
      else{
        QString Number=File_name1.left(3);
        Position=Number.toInt();
        File_name1=File_name1.mid(3);
      }

      // convert the value of the position to the format
      QString Position_string=QStringLiteral("%1").arg(Position,3,10,QChar('0'));

      QString Final_name=Position_string+"_"+File_name1+".plv";

      if (QFile::exists(Project_dir+"/xrd/raw/"+Final_name)){
        QFile::remove(Project_dir+"/xrd/raw/"+Final_name);
      }

      QFile::copy(Files_dir+"/"+File_name,Project_dir+"/xrd/raw/"+Final_name);
    }

    QMessageBox::information(this, tr("Information"),tr("The PLV files have been correctly copied"));
  }
  else{
    QMessageBox::critical(this, tr("Error"),tr("There are not '.plv' files"));
  }
}

/*************************************************************************/

//void _window_tools::xrd_add_all_files_slot()
//{
//  if (QFile::exists(Project_dir+"/xrd/")){
//    if (QFile::exists(Project_dir+"/xrd/raw/")){

//      QString Directory_name;
//      _w_directory Dialog(this,"projects",&Directory_name);

//      if (Dialog.exec()==QDialog::Accepted && Directory_name!=""){
//        QDir Dir(Directory_name);
//        QStringList Files_uxd = Dir.entryList(QStringList() << "*.uxd",QDir::Files);

//        _w_files W_files(this,Files_uxd);
//        if (W_files.exec()==QDialog::Accepted){
//          add_xrd_files(Directory_name,Files_uxd);
//        }
//      }
//    }
//    else{
//      QMessageBox::critical(this, tr("Error"),"There is not 'xrd/raw' folder");
//      QApplication::quit();
//      exit(-1);
//    }
//  }
//  else{
//    QMessageBox::critical(this, tr("Error"),"There is not 'xrd' folder");
//    QApplication::quit();
//    exit(-1);
//  }
//}

/*************************************************************************/

//void _window_tools::xrd_add_selected_files_slot()
//{
//  if (QFile::exists(Project_dir+"/xrd/")){
//    if (QFile::exists(Project_dir+"/xrd/raw/")){
//      QFileDialog Dialog(this, tr("Select the '.uxd' files"),"./projects");
////      Dialog.setFileMode(QFileDialog::DirectoryOnly);
////      Dialog.setOption(QFileDialog::ShowDirsOnly,true);
//      Dialog.setNameFilter(tr("XRD (*.uxd)"));
//      Dialog.setFileMode(QFileDialog::ExistingFiles);
//      Dialog.setOption(QFileDialog::DontUseNativeDialog,true);
//      if (Dialog.exec()==QDialog::Accepted){
//        QString Files_dir=Dialog.directory().absolutePath();
//        QDir Directory(Files_dir);
//        QStringList Files_uxd = Directory.entryList(QStringList() << "*.uxd",QDir::Files);

//        _w_files W_files(this,Files_uxd);
//        if (W_files.exec()==QDialog::Accepted){
//          add_xrd_files(Files_dir,Files_uxd);
//        }
//      }
//    }
//    else{
//      QMessageBox::critical(this, tr("Error"),"There is not 'xrd/raw' folder");
//      QApplication::quit();
//      exit(-1);
//    }
//  }
//  else{
//    QMessageBox::critical(this, tr("Error"),"There is not 'xrd' folder");
//    QApplication::quit();
//    exit(-1);
//  }
//}
#endif

/*************************************************************************/
// Text for the info

QWizardPage *_window_tools::createIntroPage()
{
  QWizardPage *page = new QWizardPage;
  page->setTitle("General information");

  QLabel *label = new QLabel(_window_tools_ns::Help_string);

  label->setWordWrap(true);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(label);
  page->setLayout(layout);

  return page;
}

#ifndef UNIFIED
/*************************************************************************/

void _window_tools::info_slot()
{
  QWizard wizard(this);

  QFont Font=font();
  Font.setPointSize(24);
  wizard.setFont(Font);
  wizard.setOptions(QWizard::NoCancelButton | QWizard::NoBackButtonOnLastPage);
  wizard.addPage(createIntroPage());
  wizard.setWindowTitle("Info");
  wizard.exec();
}
#endif
/*************************************************************************/

void _window_tools::program_slot()
{
#ifdef LINUX
  QString Program("positions");
#else
  QString Program("Positions.exe");
#endif

  QProcess::startDetached(Program,QStringList(""));
}

/*************************************************************************/

void _window_tools::adjust_image_sizes(int &Width1, int &Height1)
{
  float Rest;

  if (Width1%4!=0){
    Rest=roundf(float(Width1+0.5f)/4.0f);
    Width1=int(Rest)*4;

  }
  if (Height1%4!=0){
    Rest=roundf(float(Height1+0.5)/4.0f);
    Height1=int(Rest)*4;
  }
}

/*************************************************************************/

bool _window_tools::check_project()
{
  if (QFile::exists(_window_tools_ns::Project_name)){
    std::fstream File;
    std::string Line;
    File.open(_window_tools_ns::Project_name.toStdString(),std::ios::in);
    if (getline(File,Line)){
      QString Project_name=QString::fromStdString(Line);
      // remove carriage return
      Project_name.remove('\r');
      // remove blank spaces at the beginning
      Project_name.remove(' ');
      // remove tabs
      Project_name.remove('\t');
      if (Project_name.length()>0){
        Project_data.Project_name=Project_name.toStdString();

        QDir Dir("./projects/"+Project_name);
        if (Dir.exists()){
          Project_dir=Dir.canonicalPath();

          read_settings();

          QMessageBox::information(this,tr("Information"),"The project <font color='#ff0000'><b>"+Project_name+"</b></font> is going to be opened");

//          Opened_project->setText(Project_name);

//          Button_add_image->setEnabled(true);
//          Button_program->setEnabled(true);
//          Button_add_all_xrf_files->setEnabled(true);
//          Button_add_selected_xrf_files->setEnabled(true);
//          Button_add_all_xrd_files->setEnabled(true);
//          Button_add_selected_xrd_files->setEnabled(true);
          return true;
        }
        else{
          QMessageBox::warning(this,tr("Warning"),"The name of the saved project <font color='#ff0000'><b>"+Project_name+"</b></font> is not valid");

          QFile::remove(_window_tools_ns::Project_name);

          return false;
        }
      }
    }
  }
  return false;
}

/*************************************************************************/

//void _window_tools::closeEvent(QCloseEvent *Event)
//{

//  save_settings();
//  Event->accept();
//}

/*************************************************************************/

void _window_tools::save_int_file(QString File_name,std::vector<float>& Values)
{
  char Aux[15];

  std::ofstream File;
  File.open(File_name.toStdString());
  File << "Name:" << Name.toStdString() << std::endl;
  File << "Formula:" << Formula.toStdString() << std::endl;
  File << "XRF:" << XRF.toStdString() << std::endl;
  File << "RGB:" << RGB_color.toStdString() << std::endl;

  float Pos=22;
  for (unsigned int i=0;i<Values.size();i++){
    sprintf(Aux,"%5.2f",Pos);
    File << std::string(Aux);
    sprintf(Aux,"%12.6f",Values[i]);
    File << " " << std::string(Aux);
    File << std::endl;
    Pos=Pos+0.05;
  }
  File.close();

  QMessageBox::information(this, tr("Information"),tr("The interpreted PDB file has been correctly saved"));
}

/*************************************************************************/
#ifdef XRD_ACTIVE
std::vector<float> _window_tools::remove_noise_xrd(std::vector<float> &Raw_data, unsigned int Num_pass)
{
  std::vector<float> Vec_result=Raw_data;

  for (unsigned int i=0;i<Num_pass;i++){
    if (Vec_result[0]>=(Vec_result[0]+Vec_result[1])/2){
      Vec_result[0]=(Vec_result[0]+Vec_result[1])/2;
    }

    for (unsigned int j=1;j<Vec_result.size()-1;j++){
      if (Vec_result[j]>=(Vec_result[j-1]+Vec_result[j+1])/2){
          Vec_result[j]=(Vec_result[j-1]+Vec_result[j+1])/2;
      }
    }

    if (Vec_result[Vec_result.size()-1]>=(Vec_result[Vec_result.size()-2]+Vec_result[Vec_result.size()-1])/2){
        Vec_result[Vec_result.size()-1]=(Vec_result[Vec_result.size()-2]+Vec_result[Vec_result.size()-1])/2;
    }
  }

  float Mean=0;
  for (unsigned int i=0;i<Vec_result.size();i++) Mean=Mean+Vec_result[i];
  Mean=Mean/float(Vec_result.size());

  for (unsigned int i=0;i<Vec_result.size();i++){
    Vec_result[i]=Vec_result[i]-Mean;
    if (Vec_result[i]<0) Vec_result[i]=0;
  }

  // normalize
  Mean=0;
  for (unsigned int i=0;i<Vec_result.size();i++){
    Mean=Mean+Vec_result[i];
  }

  Mean=Mean/float(Vec_result.size());

  for (unsigned int i=0;i<Vec_result.size();i++) Vec_result[i]=Vec_result[i]/Mean;

  return Vec_result;
}
#endif

/*************************************************************************/

#ifdef UXD_TO_PDB_ACTIVE
void _window_tools::uxd_to_interpreter_slot()
{
  QFileDialog Dialog(this,tr("Select the uxd file"),"./projects");
  Dialog.setFileMode(QFileDialog::ExistingFile);
  Dialog.setNameFilter(tr("UXD (*.uxd)"));
  if (Dialog.exec()){
    std::string File_name=Dialog.selectedFiles().first().toStdString();

    std::string Error;
    vector<float> Values;
    float Step_size;
    float Start_position;

    _file_ka_uxd File_ka_uxd;
    File_ka_uxd.open(File_name,_file_ka_uxd::_mode::MODE_READ);
    if (File_ka_uxd.read(Values,Step_size,Start_position,Error)==true){
      File_ka_uxd.close();
    }
    else{
      File_ka_uxd.close();

      QMessageBox::critical(this, tr("Error"),QString::fromStdString(Error));
      QApplication::quit();
      exit(-1);
    }

//    vector<float> Vec_result=remove_noise_xrd(Values,_window_tools_ns::NUM_PASS_DEFAULT);
    vector<float> Vec_result=Values;

    // The data is readed. The additional data must be obtained
    _w_int_file_parameters *W_int_file_parameters=new _w_int_file_parameters(this);
    connect(W_int_file_parameters,SIGNAL(accepted()),W_int_file_parameters,SLOT(close_slot()));
    W_int_file_parameters->exec();

    // save the interpreter file
    QFileDialog Dialog(this,"Save compound PDB file","pdb","*.pgm.txt");
    Dialog.setWindowModality(Qt::WindowModal);
    Dialog.setAcceptMode(QFileDialog::AcceptSave);
    Dialog.setDefaultSuffix("txt");
    Dialog.selectFile(Name+".pgm.txt");
    if (Dialog.exec()== QDialog::Accepted){
      save_int_file(Dialog.selectedFiles().at(0),Vec_result);
    }
  }
}
#endif

/*************************************************************************/

#ifdef XLSX_ACTIVE
void _window_tools::data_plus_positions_slot()
{
  _data_io::load_positions_txt(this,Project_dir,Project_data);

  _data_io::load_xrf_interpreted_xlsx(this,Project_dir,Project_data.Vec_xrf_interpreted_data,Vec_names_xrf_pdb);
  _data_io::save_xrf_interpreted_plus_positions_xlsx(this,Project_dir,Project_data.Vec_coordinate_x_original,Project_data.Vec_coordinate_y_original, Project_data.Vec_xrf_interpreted_data);

#ifdef XRD_ACTIVE
  _data_io::load_xrd_interpreted_xlsx(this,Project_dir,Project_data.Vec_xrd_interpreted_data,Vec_names_xrd_pdb);
  _data_io::save_xrd_interpreted_plus_positions_xlsx(this,Project_dir,Project_data.Vec_coordinate_x_original,Project_data.Vec_coordinate_y_original, Project_data.Vec_xrd_interpreted_data);
#endif
}
#endif

/*************************************************************************/

void _window_tools::xrf_data_csv_to_project_data_slot()
{
  if (_data_io::load_project_data_csv(this,Project_dir.toStdString(),Project_data,Vec_names_xrf_pdb,Vec_names_xrd_pdb)){
    Project_data.Width_pixel=Project_data.Width_original_pixel;
    Project_data.Height_pixel=Project_data.Height_original_pixel;
    Project_data.Vec_coordinate_x=Project_data.Vec_coordinate_x_original;
    Project_data.Vec_coordinate_y=Project_data.Vec_coordinate_y_original;

    QString File_xrf_csv;
    _w_directory Dialog(this,"Select the CSV file with the XRF data","projects",&File_xrf_csv,_w_directory::MODE_FILE);

    if (Dialog.exec()==QDialog::Accepted && File_xrf_csv!=""){
       if (_data_io::xrf_load_interpreted_csv(this,File_xrf_csv.toStdString(),Project_data.Vec_xrf_interpreted_data,Vec_names_xrf_pdb)){
         // save data
         _data_io::save_project_data_csv(this,Project_dir.toStdString(),Project_data);

         Window_main->check_project_state();
       }
    }
  }
}

/*************************************************************************/

#ifdef XLSX_ACTIVE
void _window_tools::xrf_data_xlsx_to_project_data_slot()
{
  if (_data_io::load_project_data_csv(this,Project_dir,Project_data,Vec_names_xrf_pdb,Vec_names_xrd_pdb)){
    // load sampled data
    if (_data_io::load_xrf_interpreted_xlsx(this,Project_dir,Project_data.Vec_xrf_interpreted_data,Vec_names_xrf_pdb)){
      Project_data.Width=Project_data.Width_original;
      Project_data.Height=Project_data.Height_original;
      Project_data.Vec_coordinate_x=Project_data.Vec_coordinate_x_original;
      Project_data.Vec_coordinate_y=Project_data.Vec_coordinate_y_original;

       // save data
      _data_io::save_project_data_csv(this,Project_dir,Project_data);
    }
  }
}
#endif

/*************************************************************************/

void _window_tools::xrd_data_csv_to_project_data_slot()
{
  if (_data_io::load_project_data_csv(this,Project_dir.toStdString(),Project_data,Vec_names_xrf_pdb,Vec_names_xrd_pdb)){
    Project_data.Width_pixel=Project_data.Width_original_pixel;
    Project_data.Height_pixel=Project_data.Height_original_pixel;
    Project_data.Vec_coordinate_x=Project_data.Vec_coordinate_x_original;
    Project_data.Vec_coordinate_y=Project_data.Vec_coordinate_y_original;

    QString File_xrd_csv;
    _w_directory Dialog(this,"Select the CSV file with the XRD data","projects",&File_xrd_csv,_w_directory::MODE_FILE);

    if (Dialog.exec()==QDialog::Accepted && File_xrd_csv!=""){
       if (_data_io::xrf_load_interpreted_csv(this,File_xrd_csv.toStdString(),Project_data.Vec_xrf_interpreted_data,Vec_names_xrf_pdb)){
         // save data
         _data_io::save_project_data_csv(this,Project_dir.toStdString(),Project_data);

         Window_main->check_project_state();
       }
    }
  }
}

/*************************************************************************/

#ifdef XLSX_ACTIVE
#ifdef XRD_ACTIVE
void _window_tools::xrd_data_xlsx_to_project_data_slot()
{
  if (_data_io::load_project_data_csv(this,Project_dir,Project_data,Vec_names_xrf_pdb,Vec_names_xrd_pdb)){
    // load sampled data
    if (_data_io::load_xrd_interpreted_xlsx(this,Project_dir,Project_data.Vec_xrf_interpreted_data,Vec_names_xrf_pdb)){
      Project_data.Width=Project_data.Width_original;
      Project_data.Height=Project_data.Height_original;
      Project_data.Vec_coordinate_x=Project_data.Vec_coordinate_x_original;
      Project_data.Vec_coordinate_y=Project_data.Vec_coordinate_y_original;

       // save data
      _data_io::save_project_data_csv(this,Project_dir,Project_data);
    }
  }
}
#endif
#endif

/*************************************************************************/

/*************************************************************************/

void _window_tools::options_slot()
{
  if (!W_options){
    W_options=new _w_options_tools(this);
    connect(W_options,SIGNAL(accepted()),W_options,SLOT(close()));
  }

  W_options->show();
  W_options->raise();
  W_options->activateWindow();
}

/*************************************************************************/

void _window_tools::ui_font_size(int UI_font_size1)
{
  Q_UNUSED(UI_font_size1)

  QFont Font = font();
  Font.setPointSize(Window_main->ui_font_size());
  for (unsigned int i=0;i<Vec_pushbuttons.size();i++) Vec_pushbuttons[i]->setFont(Font);

  update();
}

/*************************************************************************/

int _window_tools::ui_font_size()
{
  return Window_main->ui_font_size();
}

/*************************************************************************/

void _window_tools::pass_ui_font_size(int UI_font_size1)
{
  Window_main->ui_font_size(UI_font_size1);
}

/*************************************************************************/

void _window_tools::show_positions()
{
#ifdef INTERPRETER
  Actionbutton_add_positions_csv->show();
  Actionbutton_add_random_positions->show();
#endif
}

/*************************************************************************/

void _window_tools::hide_all()
{
  Actionbutton_add_image->hide();
#ifdef INTERPRETER
  Actionbutton_add_random_positions->hide();
  Actionbutton_add_positions_csv->hide();
  Actionbutton_add_artax_files_xrf->hide();
  Actionbutton_add_xy_files_xrf->hide();
  Actionbutton_add_uxd_files_xrd->hide();
  Actionbutton_add_plv_files_xrd->hide();
#endif
  Actionbutton_add_xrf_data_csv_to_project_data_csv->hide();
  Actionbutton_add_xrd_data_csv_to_project_data_csv->hide();
  Actionbutton_options->hide();

}

/*************************************************************************/

void _window_tools::show_all()
{
#ifdef INTERPRETER
  Actionbutton_add_positions_csv->show();
  Actionbutton_add_artax_files_xrf->show();
  Actionbutton_add_xy_files_xrf->show();
  Actionbutton_add_uxd_files_xrd->show();
  Actionbutton_add_plv_files_xrd->show();
#endif
  Actionbutton_add_xrf_data_csv_to_project_data_csv->show();
  Actionbutton_add_xrd_data_csv_to_project_data_csv->show();
}

//void _window_tools::show_slot()
//{
//  Menu->exec(mapToGlobal(pos()+QPoint(width()/2,0)));
//}
