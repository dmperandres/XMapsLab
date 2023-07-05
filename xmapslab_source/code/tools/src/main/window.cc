#include "window.h"

_window::_window()
{
//  read_settings();
  QFrame *Frame=new QFrame;

  QVBoxLayout *Vboxlayout=new QVBoxLayout;

  QFont Font(font());
  Font.setPointSize(20);

  QFont Font1(font());
  Font1.setPointSize(20);

  QLabel *Label1=new QLabel("Opened project:");
  Label1->setFont(Font1);

  Opened_project=new QLineEdit;
  Opened_project->setReadOnly(true);
  Opened_project->setFont(Font1);

//  QPalette Palette = Opened_project->palette();
//  Palette.setColor(QPalette::Base,Qt::gray);
//  Palette.setColor(QPalette::Text,Qt::darkGray);
//  Opened_project->setPalette(Palette);

  QGridLayout *Gridlayout1=new QGridLayout;

  Gridlayout1->addWidget(Label1,0,0,Qt::AlignRight);
  Gridlayout1->addWidget(Opened_project,0,1,Qt::AlignLeft);

  QWidget *Widget_aux=new QWidget;

  Widget_aux->setLayout(Gridlayout1);
  QAction* Action_create_project = new QAction;
  Action_create_project->setText("Create project");
  Action_create_project->setToolTip(_window_ns::Help_text_open_project);
  connect(Action_create_project, SIGNAL(triggered()), this, SLOT(create_project_slot()));

  QAction* Action_open_project = new QAction;
  Action_open_project->setText("Open project");
  connect(Action_open_project, SIGNAL(triggered()), this, SLOT(open_project_slot()));

  Action_add_image = new QAction;
  Action_add_image->setText("Add image");
  Action_add_image->setEnabled(false);
  connect(Action_add_image, SIGNAL(triggered()), this, SLOT(add_image_slot()));

  Action_add_all_xrf_files = new QAction;
  Action_add_all_xrf_files->setText("All files");
  Action_add_all_xrf_files->setEnabled(false);
  connect(Action_add_all_xrf_files, SIGNAL(triggered()), this, SLOT(xrf_add_all_files_slot()));

//  Action_spreadsheet_to_project = new QAction;
//  Action_spreadsheet_to_project->setText("Spreadsheet to project");
//  Action_spreadsheet_to_project->setEnabled(false);
//  connect(Action_spreadsheet_to_project, SIGNAL(triggered()), this, SLOT(spreadsheet_to_project_slot()));

//  Action_project_to_spreadsheet = new QAction;
//  Action_project_to_spreadsheet->setText("Project to spreadsheet");
//  Action_project_to_spreadsheet->setEnabled(false);
//  connect(Action_project_to_spreadsheet, SIGNAL(triggered()), this, SLOT(project_to_spreadsheet_slot()));

  Action_add_xrf_data_csv_to_project_data_csv = new QAction;
  Action_add_xrf_data_csv_to_project_data_csv->setText("csv");
  Action_add_xrf_data_csv_to_project_data_csv->setEnabled(false);
  connect(Action_add_xrf_data_csv_to_project_data_csv, SIGNAL(triggered()), this, SLOT(xrf_data_csv_to_project_data_slot()));

  // XRD

  QMenu *Menu=new QMenu();
//  Menu->setFixedWidth(width());

  connect(Menu,SIGNAL(aboutToHide()),Menu,SLOT(show()));

  Font = Menu->font();
  Font.setPointSize(25);
  Menu->setFont(Font);

  Menu->addAction(Action_create_project);
  Menu->addAction(Action_open_project);
  Menu->addAction(Action_add_image);

  Menu->addSeparator();
  Submenu_add_xrf_data=Menu->addMenu("Add XRF data to project");
  Submenu_add_xrf_data->setEnabled(false);
//  Submenu_add_xrf->setFixedWidth(width());
  Submenu_add_xrf_data->setFont(Font);

  Submenu_add_xrf_data->addAction(Action_add_xrf_data_csv_to_project_data_csv);

  QFrame *Line=new QFrame;
  Line->setFrameStyle(QFrame::HLine);

  Vboxlayout->addWidget(Widget_aux);
  Vboxlayout->addWidget(Line);
  Vboxlayout->addWidget(Menu);

  Frame->setLayout(Vboxlayout);

  setCentralWidget(Frame);

  //
  QAction *Exit = new QAction(QIcon(":/icons/exit.png"), tr("&Exit..."), this);
  Exit->setShortcut(tr("Ctrl+Q"));
  Exit->setToolTip(tr("Exit the application"));
  connect(Exit, SIGNAL(triggered()), this, SLOT(close()));

  // actions for file menu
  QAction *Help_info = new QAction(tr("&Info"), this);
  connect(Help_info, SIGNAL(triggered()), this, SLOT(info_slot()));

  // menus
  QMenu *File_menu=menuBar()->addMenu(tr("&File"));
  File_menu->addAction(Exit);
  File_menu->setAttribute(Qt::WA_AlwaysShowToolTips);

  QMenu *Menu_help=menuBar()->addMenu(tr("&Info"));
  Menu_help->addAction(Help_info);

  Menu_help->setAttribute(Qt::WA_AlwaysShowToolTips);

  //
  setWindowTitle(_window_ns::Program_name);

  // check what model to use
  QFileInfo Check_file(QString::fromStdString(_common_window_ns::FILE_MODE));
  // check if file exists and if yes: Is it really a file and no directory?
  if (Check_file.exists() && Check_file.isFile()) Mode_normal=false;
  else Mode_normal=true;
}

//

_window::~_window()
{
}

/*************************************************************************/

void _window::read_settings()
{
//  QSettings settings(Project_dir+"/settings_"+_window_ns::Program_name.toLower()+".ini",QSettings::IniFormat);
  QSettings settings(Project_dir+"/settings.ini",QSettings::IniFormat);

  settings.beginGroup("Interpreter");
    settings.beginGroup("MainWindow");
//    resize(settings.value("size", QSize(800, 800)).toSize());
    move(settings.value("pos", QPoint(50,50)).toPoint());
    settings.endGroup();
  settings.endGroup();
}

/*************************************************************************/

void _window::save_settings()
{
//  QSettings settings(Project_dir+"/settings_"+_window_ns::Program_name.toLower()+".ini",QSettings::IniFormat);
  QSettings settings(Project_dir+"/settings.ini",QSettings::IniFormat);

  settings.beginGroup("Interpreter");
  settings.beginGroup("MainWindow");
//    settings.setValue("size", size());
  settings.setValue("pos", pos());
  settings.endGroup();
  settings.endGroup();
}

/*************************************************************************/

void _window::project_parameters(QString Project_folder_name1, QString Project_name1, QString Author1, QString Date1, QString Device1,QString Tube1, QString XRF_data_adjustment1,QString Widht1,QString Height1)
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
  Project_data.Tube_type=_data_xrd_ns::_tube_type(i);

  for (i=0;i<int(_data_xrf_ns::Vec_xrf_data_adjustment_name.size());i++){
    if (XRF_data_adjustment1.toStdString()==_data_xrf_ns::Vec_xrf_data_adjustment_name[i].toStdString()) break;
  }
  Project_data.XRF_data_adjustment=_data_xrf_ns::_xrf_data_adjustment(i);

  if (Mode_normal==false){
    Project_data.Width=Widht1.toFloat();
    Project_data.Height=Height1.toFloat();
  }
}

/*************************************************************************/

void _window::create_project_slot()
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

      Opened_project->setText(Project_name);

      QDir().mkdir("projects/"+Project_name);
      QDir().mkdir("projects/"+Project_name+"/images");
      QDir().mkdir("projects/"+Project_name+"/positions");
      QDir().mkdir("projects/"+Project_name+"/xrf");
      QDir().mkdir("projects/"+Project_name+"/xrf/raw");
      QDir().mkdir("projects/"+Project_name+"/xrf/maps");
      QDir().mkdir("projects/"+Project_name+"/xrf/graphs");

      //      // save project name for other programs
      //      std::ofstream File;

      //      File.open(_window_ns::Project_name.toStdString(),ios::out);
      //      File << Project_name.toStdString() << endl;
      //      File.close();

      //
      if (Mode_normal==false){
        _data_io::save_info_txt(this,Project_dir,Project_data);
        _data_io::save_positions_txt(this,Project_dir,Project_data);
      }
      else{
       _data_io::save_project_data_csv(this,Project_dir,Project_data);
      }

      QMessageBox::information(this, tr("Information"),tr("The project has been correctly created"));

      Action_add_image->setEnabled(true);

//      Action_spreadsheet_to_project->setEnabled(true);
//      Action_project_to_spreadsheet->setEnabled(true);
//      Action_uxd_to_interpreter->setEnabled(true);
//      Action_data_plus_positions->setEnabled(true);

      Submenu_add_xrf_data->setEnabled(true);
      Action_add_xrf_data_csv_to_project_data_csv->setEnabled(true);

    }
    else{
      QMessageBox::critical(this, tr("Error"),"The folder with name "+Project_name+" already exists");
    }
  }
}

/*************************************************************************/

void _window::open_project_slot()
{
  _w_directory Dialog(this,"projects",&Project_folder_name);

  if (Dialog.exec()==QDialog::Accepted && Project_folder_name!=""){
    QDir Dir(Project_folder_name);
    Project_dir=Dir.absolutePath();

    QStringList Parts = Project_folder_name.split("/");
    QString Project_name=Parts[Parts.size()-1];
    Opened_project->setText(Project_name);

    // save project name for other programs
//    std::ofstream File;
//    File.open(_window_ns::Project_name.toStdString(),ios::out);
//    File << Project_name.toStdString() << endl;
//    File.close();

    Action_add_image->setEnabled(true);

//    Action_spreadsheet_to_project->setEnabled(true);
//    Action_project_to_spreadsheet->setEnabled(true);
//    Action_uxd_to_interpreter->setEnabled(true);
//    Action_data_plus_positions->setEnabled(true);
    Submenu_add_xrf_data->setEnabled(true);
    Action_add_xrf_data_csv_to_project_data_csv->setEnabled(true);

    read_settings();
  }
}

/*************************************************************************/

void _window::add_image_slot()
{
  if (QFile::exists(Project_dir+"/images/")){
    QFileDialog Dialog(this,tr("Select the image"),"./projects");
    Dialog.setFileMode(QFileDialog::ExistingFile);
    Dialog.setNameFilter(tr("Images (*.png *.jpg)"));
    if (Dialog.exec()){
      QStringList List=Dialog.selectedFiles();
      QString File_name=List[0];

      _w_image W_image(this,File_name);
      if (W_image.exec()==QDialog::Accepted){

        QImage Image;

        Image.load(File_name);
        int Width_aux=Image.width();
        int Height_aux=Image.height();

        adjust_image_sizes(Width_aux,Height_aux);
        if (Width_aux!=Image.width() || Height_aux!=Image.height()){
          Image=Image.scaled(QSize(Width_aux,Height_aux),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
        }

        QFileInfo File_info(File_name);
        QString Base_name=File_info.baseName();
        QString Aux=Base_name;
        QString File_name_out;

        Aux.remove('-');
        Aux.remove('_');

        // check if the name is only "vis"
        if (Aux=="vis") File_name_out="vis_image";
        else{
          // check that there is not 'vis' in the name
          QString File_name1=Base_name;
          File_name1.replace('-','_');
          QStringList Tokens=File_name1.split('_');

          if (Tokens[0]=="vis") File_name_out=Base_name;
          else File_name_out="vis_"+Base_name;
        }

        Image.save(Project_dir+"/images/"+File_name_out+".png");

        QMessageBox::information(this, tr("Information"),tr("The image has been correctly copied"));
      }
    }
  }
  else{
    QMessageBox::critical(this, tr("Error"),"There is not 'images' folder");
    QApplication::quit();
    exit(-1);
  }
}

/*************************************************************************/

void _window::add_xrf_files(QString Files_dir,QStringList Files_artax)
{
  if (Files_artax.size()>0){
    // check that numbers are not repeated
    std::vector<int> Positions;
    foreach(QString File_name, Files_artax){
      QString File_name1=File_name;
      File_name1.replace('-','_');
      QStringList Tokens=File_name1.split('_');
      int Result=Tokens[0].toInt();
      if (Result!=0) Positions.push_back(Result);
      else{
        QMessageBox::critical(this, tr("Error"),"The file "+File_name+" has not number");
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

      File_name1.remove("artax");
      File_name1.remove("xrf");
      File_name1.remove("ka");

      File_name1.replace("____","_");
      File_name1.replace("___","_");
      File_name1.replace("__","_");
      File_name1.replace("_.",".");

      // remove the .txt
      int Pos=File_name1.lastIndexOf('.');
      File_name1=File_name1.left(Pos);

      QStringList Tokens=File_name1.split('_');
      // convert to the format
      int Position=Tokens[0].toInt();
      QString Position_string=QStringLiteral("%1").arg(Position,3,10,QChar('0'));

      QString Final_name=Position_string+"_";
      for (int i=1;i<Tokens.size();i++){
        QString Token=Tokens[i];
        Token=Token.toLower();

        Token[0]=Token[0].toUpper();

        if (i<Tokens.size()-1){
          Final_name=Final_name+Token+'_';
        }
        else{
          Final_name=Final_name+Token;
        }
      }

      Final_name=Final_name+".txt";

      if (QFile::exists(Project_dir+"/xrf/raw/"+Final_name)){
        QFile::remove(Project_dir+"/xrf/raw/"+Final_name);
      }

      QFile::copy(Files_dir+"/"+File_name,Project_dir+"/xrf/raw/"+Final_name);
    }

    QMessageBox::information(this, tr("Information"),tr("The XRD files have been correctly copied"));
  }
  else{
    QMessageBox::critical(this, tr("Error"),tr("There are not '.txt' files"));
  }
}

/*************************************************************************/

void _window::xrf_add_all_files_slot()
{
  if (QFile::exists(Project_dir+"/xrf/")){
    if (QFile::exists(Project_dir+"/xrf/raw/")){

      QString Directory_name;
      _w_directory Dialog(this,"projects",&Directory_name);

      if (Dialog.exec()==QDialog::Accepted && Directory_name!=""){
        QDir Dir(Directory_name);
        QStringList Files_artax = Dir.entryList(QStringList() << "*.txt",QDir::Files);

        _w_files W_files(this,Files_artax);
        if (W_files.exec()==QDialog::Accepted){
          add_xrf_files(Directory_name,Files_artax);
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

//void _window::xrf_add_selected_files_slot()
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

/*************************************************************************/
// Text for the info

QWizardPage *createIntroPage()
{
  QWizardPage *page = new QWizardPage;
  page->setTitle("General information");

  QLabel *label = new QLabel(_window_ns::Help_string);

  label->setWordWrap(true);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(label);
  page->setLayout(layout);

  return page;
}

/*************************************************************************/

void _window::info_slot()
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

/*************************************************************************/

void _window::program_slot()
{
  QString Program("Positions.exe");

  QProcess::startDetached(Program,QStringList(""));
}

/*************************************************************************/

void _window::adjust_image_sizes(int &Width1, int &Height1)
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

bool _window::check_project()
{
  if (QFile::exists(_window_ns::Project_name)){
    std::fstream File;
    std::string Line;
    File.open(_window_ns::Project_name.toStdString(),std::ios::in);
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

          Opened_project->setText(Project_name);

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

          QFile::remove(_window_ns::Project_name);

          return false;
        }
      }
    }
  }
  return false;
}

/*************************************************************************/

void _window::closeEvent(QCloseEvent *Event)
{

  save_settings();
  Event->accept();
}

/*************************************************************************/

void _window::save_int_file(QString File_name,std::vector<float>& Values)
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

/*************************************************************************/

/*************************************************************************/

/*************************************************************************/

void _window::xrf_data_csv_to_project_data_slot()
{
  if (_data_io::load_project_data_csv(this,Project_dir,Project_data,Vec_names_xrf_pdb,Vec_names_xrd_pdb)){
    // load sampled data
    if (_data_io::load_xrf_interpreted_csv(this,Project_dir,Project_data.Vec_xrf_interpreted_data,Vec_names_xrf_pdb)){
      Project_data.Width=Project_data.Width_original;
      Project_data.Height=Project_data.Height_original;
      Project_data.Vec_coordinate_x=Project_data.Vec_coordinate_x_original;
      Project_data.Vec_coordinate_y=Project_data.Vec_coordinate_y_original;

       // save data
      _data_io::save_project_data_csv(this,Project_dir,Project_data);
    }
  }
}

/*************************************************************************/

/*************************************************************************/

/*************************************************************************/

