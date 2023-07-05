/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#include "window.h"
#include "glwidget.h"

/*************************************************************************/

_window::_window()
{
//  read_settings();
  QSizePolicy Q(QSizePolicy::Expanding,QSizePolicy::Expanding);

  QRect Screen_size = QApplication::primaryScreen()->geometry();
  Screen_width=Screen_size.width();
  Screen_height=Screen_size.height();

//  QGLFormat Format;
//  Format.setAlpha(true);
//  Format.setAccum(true);
//  Format.setRgba(true);
//  Format.setDoubleBuffer(true);
//  QGLFormat::setDefaultFormat(Format);

  Table_positions=new _table_positions(this);
  Table_positions->setMaximumWidth(250);

  QGroupBox *Groupbox_positions=new QGroupBox("Positions");
  Groupbox_positions->setAlignment(Qt::AlignCenter);
  Groupbox_positions->setMaximumWidth(250);
  QVBoxLayout *Vboxlayout_positions=new QVBoxLayout;

  Vboxlayout_positions->addWidget(Table_positions);
  Groupbox_positions->setLayout(Vboxlayout_positions);

  GL_widget[1] = new _gl_widget(this,1);
  GL_widget[1]->setSizePolicy(Q);
  GL_widget[1]->setMinimumSize(300,300);

  Splitter=new _splitter(Qt::Horizontal);

  Splitter->addWidget(GL_widget[1]);
  Splitter->addWidget(Groupbox_positions);

  setCentralWidget(Splitter);

  // actions for file menu
  Load_project = new QAction(QIcon(":/common/icons/fileopen.png"), tr("Open project"), this);
  Load_project->setShortcuts(QKeySequence::Open);
  Load_project->setToolTip(tr("Select the project folder"));
  connect(Load_project, SIGNAL(triggered()), this, SLOT(load_project_slot()));

  Load_image = new QAction(QIcon(":/common/icons/fileopen.png"), tr("Load image"), this);
  Load_image->setEnabled(false);
  Load_image->setToolTip(tr("Load an image selecting the file"));
  connect(Load_image, SIGNAL(triggered()), this, SLOT(load_image_slot()));

//  Load_positions = new QAction(QIcon(":/common/icons/fileopen.png"), tr("Load positions"), this);
//  Load_positions->setEnabled(false);
//  Load_positions->setToolTip(tr("Load the positions data selecting the file"));
//  connect(Load_positions, SIGNAL(triggered()), this, SLOT(load_positions_slot()));

//  Save_project = new QAction(QIcon(":/common/icons/fileopen.png"), tr("Save project data"), this);
//  Save_project->setEnabled(false);
//  Save_project->setToolTip(tr("Save the 'vis' image and the positions data"));
//  connect(Save_project, SIGNAL(triggered()), this, SLOT(save_project_slot()));

  Save_image = new QAction(QIcon(":/common/icons/filesave.png"), tr("Save image"), this);
  Save_image->setEnabled(false);
  Save_image->setToolTip(tr("Save the image with the positions"));
  connect(Save_image, SIGNAL(triggered()), this, SLOT(save_image_slot()));

  Save_positions = new QAction(QIcon(":/common/icons/filesave.png"), tr("Save positions"), this);
  Save_positions->setShortcuts(QKeySequence::Save);
  Save_positions->setEnabled(false);
  Save_positions->setToolTip(tr("Save the positions"));
  connect(Save_positions, SIGNAL(triggered()), this, SLOT(save_positions_slot()));

  Options = new QAction(tr("&Options"), this);
  Options->setEnabled(false);
  Options->setToolTip(tr("Set the options"));
  connect(Options, SIGNAL(triggered()), this, SLOT(options_slot()));

  QAction *Exit = new QAction(QIcon(":/common/icons/exit.png"), tr("&Exit..."), this);
  Exit->setShortcut(tr("Ctrl+Q"));
  Exit->setToolTip(tr("Exit the application"));
  connect(Exit, SIGNAL(triggered()), this, SLOT(close()));

  // actions for programs
//  QAction *Distiller = new QAction(tr("Interpreter"), this);
//  connect(Distiller,SIGNAL(triggered()),this,SLOT(program_interpreter_slot()));

//  QAction *Maplab = new QAction(tr("MapLab"), this);
//  connect(Maplab,SIGNAL(triggered()),this,SLOT(program_maplab_slot()));

  // actions for file menu
  QAction *Help_info = new QAction(tr("&Info"), this);
  connect(Help_info, SIGNAL(triggered()), this, SLOT(info_slot()));

  // menus
  QMenu *File_menu=menuBar()->addMenu(tr("&File"));
  File_menu->addAction(Load_project);
  File_menu->addAction(Load_image);
//  File_menu->addAction(Load_positions);
  File_menu->addSeparator();
//  File_menu->addAction(Save_project);
  File_menu->addAction(Save_image);
  File_menu->addAction(Save_positions);
  File_menu->addSeparator();
  File_menu->addAction(Options);
  File_menu->addSeparator();
  File_menu->addAction(Exit);
  File_menu->setAttribute(Qt::WA_AlwaysShowToolTips);

//  QMenu *Menu_programs=menuBar()->addMenu(tr("Programs"));
//  Menu_programs->addAction(Distiller);
//  Menu_programs->addAction(Maplab);

  QMenu *Menu_help=menuBar()->addMenu(tr("&Help"));
  Menu_help->addAction(Help_info);

  Menu_help->setAttribute(Qt::WA_AlwaysShowToolTips);

//  resize(_window_ne::WIWNDOW_WIDTH,_window_ne::WIWNDOW_HEIGHT);

  // TOOL BAR
  Vec_actions.resize(int(_window_ns::_action_type::ACTION_LAST));

  // load the icons
  Icons[0][0]=QIcon(":/common/icons/move.png");
  Icons[0][1]=QIcon(":/common/icons/move_un.png");
  Icons[1][0]=QIcon(":/common/icons/add_points.png");
  Icons[1][1]=QIcon(":/common/icons/add_points_un.png");
  Icons[2][0]=QIcon(":/common/icons/delete_points.png");
  Icons[2][1]=QIcon(":/common/icons/delete_points_un.png");
  Icons[3][0]=QIcon(":/common/icons/move_points.png");
  Icons[3][1]=QIcon(":/common/icons/move_points_un.png");
  Icons[4][0]=QIcon(":/common/icons/add_point_number.png");

//  Vec_actions[int(_window_ns::_action_type::ACTION_DEFAULT)] = new QAction(QIcon(":/common/icons/move.png"), tr("Camera"), this);
  Vec_actions[int(_window_ns::_action_type::ACTION_DEFAULT)] = new QAction(Icons[0][1], tr("Camera"), this);
  Vec_actions[int(_window_ns::_action_type::ACTION_DEFAULT)]->setStatusTip(tr("Selects things"));
  Vec_actions[int(_window_ns::_action_type::ACTION_DEFAULT)]->setCheckable(true);
  Vec_actions[int(_window_ns::_action_type::ACTION_DEFAULT)]->setChecked(true);
  Vec_actions[int(_window_ns::_action_type::ACTION_DEFAULT)]->setObjectName("move");

  connect(Vec_actions[int(_window_ns::_action_type::ACTION_DEFAULT)], SIGNAL(triggered()), this, SLOT(action_default_slot()));

  Vec_actions[int(_window_ns::_action_type::ACTION_ADD_POINTS)]= new QAction(Icons[1][0], tr("Add points"), this);
  Vec_actions[int(_window_ns::_action_type::ACTION_ADD_POINTS)]->setToolTip(tr("Add points by pointing and clicking the right button of the mouse"));
  Vec_actions[int(_window_ns::_action_type::ACTION_ADD_POINTS)]->setCheckable(true);
  Vec_actions[int(_window_ns::_action_type::ACTION_ADD_POINTS)]->setObjectName("add_points");
  connect(Vec_actions[int(_window_ns::_action_type::ACTION_ADD_POINTS)], SIGNAL(triggered()), this, SLOT(action_add_points_slot()));

  Vec_actions[int(_window_ns::_action_type::ACTION_REMOVE_POINTS)]= new QAction(Icons[2][0], tr("Remove points"), this);
  Vec_actions[int(_window_ns::_action_type::ACTION_REMOVE_POINTS)]->setToolTip(tr("Remove points by pointing clicking the right button of the mouse"));
  Vec_actions[int(_window_ns::_action_type::ACTION_REMOVE_POINTS)]->setCheckable(true);
  Vec_actions[int(_window_ns::_action_type::ACTION_REMOVE_POINTS)]->setObjectName("remove_points");
//  Vec_actions[int(_window_ns::_action_type::ACTION_CHANGE_CAMERA)]->setChecked(true);
  connect(Vec_actions[int(_window_ns::_action_type::ACTION_REMOVE_POINTS)], SIGNAL(triggered()), this, SLOT(action_remove_points_slot()));

  Vec_actions[int(_window_ns::_action_type::ACTION_MOVE_POINTS)]= new QAction(Icons[3][0], tr("Move points"), this);
  Vec_actions[int(_window_ns::_action_type::ACTION_MOVE_POINTS)]->setToolTip(tr("Move points by pointing clicking the right button of the mouse. Then move the cursor to the new position and click the right button of the mouse"));
  Vec_actions[int(_window_ns::_action_type::ACTION_MOVE_POINTS)]->setCheckable(true);
  Vec_actions[int(_window_ns::_action_type::ACTION_MOVE_POINTS)]->setObjectName("move_points");
  connect(Vec_actions[int(_window_ns::_action_type::ACTION_MOVE_POINTS)], SIGNAL(triggered()), this, SLOT(action_move_points_slot()));

  Action_group = new QActionGroup(this);
  Action_group->addAction(Vec_actions[int(_window_ns::_action_type::ACTION_DEFAULT)]);
  Action_group->addAction(Vec_actions[int(_window_ns::_action_type::ACTION_ADD_POINTS)]);
  Action_group->addAction(Vec_actions[int(_window_ns::_action_type::ACTION_REMOVE_POINTS)]);
  Action_group->addAction(Vec_actions[int(_window_ns::_action_type::ACTION_MOVE_POINTS)]);

  ToolBar = addToolBar(tr("Tools"));
  ToolBar->addActions(Action_group->actions());
  ToolBar->setMovable(false);
  ToolBar->setEnabled(false);

//  addToolBar(Qt::LeftToolBarArea,ToolBar);
  addToolBar(Qt::LeftToolBarArea,ToolBar);

  setWindowTitle(_window_ns::Program_name);

  resize(Screen_width/2,Screen_height/2);

//  resize(Screen_size.width()*_window_ns::SCREEN_WIDTH_FACTOR,Screen_size.height()*_window_ns::SCREEN_HEIGHT_FACTOR);

//  check_project();
}

/*************************************************************************/

_window::~_window()
{
}

/*************************************************************************/

void _window::ui_set_font_size(int Size)
{
  UI_font_size=Size;

  QFont Font=QApplication::font();
  Font.setPointSize(Size);
  QApplication::setFont(Font);

  update();
}

/*************************************************************************/

void _window::read_settings()
{
//  QSettings settings(Project_dir+"/settings_"+_window_ns::Program_name.toLower()+".ini",QSettings::IniFormat);
  QSettings settings(Project_dir+"/settings.ini",QSettings::IniFormat);

  // window
  settings.beginGroup("Positions");
    settings.beginGroup("MainWindow");
    resize(settings.value("size", QSize(800, 800)).toSize());
    move(settings.value("pos", QPoint(50,50)).toPoint());
    settings.endGroup();
  settings.endGroup();

  // display
  settings.beginGroup("DisplayParameters");
    Positions_font_size_display=settings.value("DisplayFontSize",_window_ns::POSITIONS_DISPLAY_FONT_SIZE).toInt();
    Positions_out_circle_size_display=settings.value("DisplayOutCircleSize",_window_ns::POSITIONS_DISPLAY_OUT_CIRCLE_SIZE).toInt();
    Positions_font_color_display=settings.value("DisplayFontColor",_window_ns::POSITIONS_DISPLAY_FONT_COLOR).value<QColor>();
    Positions_out_circle_color_display=settings.value("DisplayOutCircleColor",_window_ns::POSITIONS_DISPLAY_OUT_CIRCLE_COLOR).value<QColor>();
    Positions_in_circle_color_display=settings.value("DisplayInCircleColor",_window_ns::POSITIONS_DISPLAY_IN_CIRCLE_COLOR).value<QColor>();
    Positions_selection_out_circle_color_display=settings.value("DisplaySelectionOutCircleColor",_window_ns::POSITIONS_DISPLAY_SELECTION_OUT_CIRCLE_COLOR).value<QColor>();
    Positions_selection_in_circle_color_display=settings.value("DisplaySelectionInCircleColor",_window_ns::POSITIONS_DISPLAY_SELECTION_IN_CIRCLE_COLOR).value<QColor>();
  settings.endGroup();

  // print
  settings.beginGroup("PrintParameters");
  Positions_font_size_print=settings.value("PrintFontSize",_window_ns::POSITIONS_DISPLAY_FONT_SIZE).toInt();
  Positions_out_circle_size_print=settings.value("PrintOutCircleSize",_window_ns::POSITIONS_DISPLAY_OUT_CIRCLE_SIZE).toInt();
  Positions_font_color_print=settings.value("PrintFontColor",_window_ns::POSITIONS_DISPLAY_FONT_COLOR).value<QColor>();
  Positions_out_circle_color_print=settings.value("PrintOutCircleColor",_window_ns::POSITIONS_DISPLAY_OUT_CIRCLE_COLOR).value<QColor>();
  Positions_in_circle_color_print=settings.value("PrintInCircleColor",_window_ns::POSITIONS_DISPLAY_IN_CIRCLE_COLOR).value<QColor>();
  settings.endGroup();

  settings.beginGroup("General");
    UI_font_size=settings.value("UIFontSize",_common_ns::UI_FONT_SIZE_DEFAULT).toInt();
  settings.endGroup();
}

/*************************************************************************/

void _window::save_settings()
{
//  QSettings settings(Project_dir+"/settings_"+_window_ns::Program_name.toLower()+".ini",QSettings::IniFormat);
  QSettings settings(Project_dir+"/settings.ini",QSettings::IniFormat);

  // window
  settings.beginGroup("Positions");
    settings.beginGroup("MainWindow");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();
  settings.endGroup();

  // display
  settings.beginGroup("DisplayParameters");
    settings.setValue("DisplayFontSize",Positions_font_size_display);
    settings.setValue("DisplayOutCircleSize",Positions_out_circle_size_display);
    settings.setValue("DisplayFontColor",Positions_font_color_display);
    settings.setValue("DisplayOutCircleColor",Positions_out_circle_color_display);
    settings.setValue("DisplayInCircleColor",Positions_in_circle_color_display);
    settings.setValue("DisplaySelectionOutCircleColor",Positions_selection_out_circle_color_display);
    settings.setValue("DisplaySelectionInCircleColor",Positions_selection_in_circle_color_display);
  settings.endGroup();

  // print
  settings.beginGroup("PrintParameters");
    settings.setValue("PrintFontSize",Positions_font_size_print);
    settings.setValue("PrintOutCircleSize",Positions_out_circle_size_print);
    settings.setValue("PrintFontColor",Positions_font_color_print);
    settings.setValue("PrintOutCircleColor",Positions_out_circle_color_print);
    settings.setValue("PrintInCircleColor",Positions_in_circle_color_print);
  settings.endGroup();

  settings.beginGroup("General");
    settings.setValue("UIFontSize",UI_font_size);
  settings.endGroup();
}

/*************************************************************************/

void _window::closeEvent(QCloseEvent *Event)
{
  save_settings();
  Event->accept();
}

/*************************************************************************/

void _window::compute_options_parameters()
{
  // set the parameters depending on the size of the image
  int Font_size=int(sqrtf(Image_vis->cols*Image_vis->rows)*_window_ns::FONT_FACTOR);
  if (Font_size<_window_ns::POSITIONS_DISPLAY_FONT_SIZE) Font_size=_window_ns::POSITIONS_DISPLAY_FONT_SIZE;
  Positions_font_size_display=Font_size;
  Positions_font_size_print=Font_size;

  int Out_circle_size=int(sqrtf(Image_vis->cols*Image_vis->rows)*_window_ns::OUT_CIRCLE_FACTOR);
  if (Out_circle_size<_window_ns::POSITIONS_DISPLAY_OUT_CIRCLE_SIZE) Out_circle_size=_window_ns::POSITIONS_DISPLAY_OUT_CIRCLE_SIZE;
  Positions_out_circle_size_display=Out_circle_size;
  Positions_out_circle_size_print=Out_circle_size;
}

/*************************************************************************/

void _window::load_project_slot()
{
  _w_directory Dialog(this,"projects",&Project_name);

  if (Dialog.exec()==QDialog::Accepted && Project_name!=""){
    QDir Dir(Project_name);
    Project_dir=Dir.absolutePath();

    read_settings();

    ui_set_font_size(UI_font_size);

    // save project name for other programs
    std::ofstream File;
    File.open(_window_ns::Project_name.toStdString(),std::ios::out);
    File << Project_name.toStdString() << std::endl;
    File.close();

    Load_image->setEnabled(true);

    // check what model to use
    QFileInfo Check_file(QString::fromStdString(_common_window_ns::FILE_MODE));
    // check if file exists and if yes: Is it really a file and no directory?
    if (Check_file.exists() && Check_file.isFile()) Mode_normal=false;
    else Mode_normal=true;
  }
}

/*************************************************************************/

void _window::load_image(std::string File_name)
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
  Distance_threshold=float(Image_vis->cols)*_window_ns::PERCENTAGE_THRESHOLD_DISTANCE;
  if (Distance_threshold<_window_ns::MINIMUM_THRESHOLD_DISTANCE)  Distance_threshold=_window_ns::MINIMUM_THRESHOLD_DISTANCE;

}

/*************************************************************************/

void _window::load_image_slot()
{
  Layers.clear();
  Textures.clear();
  Transparency.clear();

  QFileDialog Dialog(this,tr("Select the image"),Project_dir+"/images");
  Dialog.setFileMode(QFileDialog::ExistingFile);
  Dialog.setNameFilter(tr("Images (*.png *.jpg)"));
  if (Dialog.exec()){

    QStringList List=Dialog.selectedFiles();
    QString File_name=List[0];

    load_image(File_name.toStdString());
    Loaded_image=true;
    // compute the options parameters depending on the image size
    compute_options_parameters();

    add_layer_image(Image_vis);

    save_settings();

    add_layer_positions();

    load_positions();

    ToolBar->setEnabled(true);
    Options->setEnabled(true);
    Save_image->setEnabled(true);
    Save_positions->setEnabled(true);

    GL_widget[1]->setCursor(Qt::CrossCursor);
    GL_widget[1]->update();
  }
}

/*************************************************************************/

void _window::load_positions()
{
  // now load the positions info
  if (Mode_normal==false){
    _data_io::load_info_txt(this,Project_dir,Project_data);
    _data_io::load_positions_txt(this,Project_dir,Project_data);
  }
  else{
    _data_io::load_project_data_csv(this,Project_dir,Project_data,Vec_names_xrf_pdb,Vec_names_xrd_pdb);
  }

  // add the positions
  Vec_positions.resize(Project_data.Vec_coordinate_x_original.size());
  for (unsigned int i=0;i<Project_data.Vec_coordinate_x_original.size();i++){
    Vec_positions[i]={int(i)+1,_vertex2i(Project_data.Vec_coordinate_x_original[i],Project_data.Vec_coordinate_y_original[i]),false};
  }

  // compute the distance threshold
  Distance_threshold=float(Image_vis->cols)*_window_ns::PERCENTAGE_THRESHOLD_DISTANCE;
  if (Distance_threshold<_window_ns::MINIMUM_THRESHOLD_DISTANCE) Distance_threshold=_window_ns::MINIMUM_THRESHOLD_DISTANCE;

  // update and draw
  std::static_pointer_cast<_layer_positions_ui>(Layers[1])->add_input_data(Vec_positions);
  std::static_pointer_cast<_layer_positions_ui>(Layers[1])->update();
  GL_widget[1]->update_texture(1);

  Table_positions->update_table(Vec_positions);
}

/*************************************************************************/

void _window::save_positions_slot()
{
//  Project_data.Num_samples=Vec_positions.size();

  Project_data.Width=Image_vis->cols;
  Project_data.Height=Image_vis->rows;

  Project_data.Vec_coordinate_x.resize(Vec_positions.size());
  Project_data.Vec_coordinate_y.resize(Vec_positions.size());

  for (unsigned int i=0;i<Vec_positions.size();i++){
    Project_data.Vec_coordinate_x[i]=Vec_positions[i].Coordinates.x;
    Project_data.Vec_coordinate_y[i]=Vec_positions[i].Coordinates.y;
  }

  if (Mode_normal==false){
    _data_io::save_positions_txt(this,Project_dir,Project_data);
    _data_io::save_info_txt(this,Project_dir,Project_data);
  }
  else{
    _data_io::save_project_data_csv(this,Project_dir,Project_data);
  }
}

/*************************************************************************/

void _window::save_image_positions()
{
  int White_space=10;

//  std::string Name=Order_images[Selected_layer];
  cv::Mat Image=Layers[0]->image()->clone();
  cv::flip(Image,Image,0);

  float Width1=float(Image.cols)-1;
  float Height1=float(Image.rows)-1;

  QImage Composed_image(Image.data,Image.cols,Image.rows,static_cast<int>(Image.step),QImage::Format_ARGB32);
  Composed_image=Composed_image.rgbSwapped();

//  QImage Image1(Image.cols+White_space*5,Image.rows+White_space*5,QImage::Format_ARGB32);
//  Image1.fill(Qt::white);

  QPainter Painter(&Composed_image);
//  Painter.drawImage(2.5*White_space,2.5*White_space,image);

//  QPen Previous_pen=Painter.pen();

  QPen Pen;
  Pen.setWidth(5);
  Painter.setPen(Pen);

  QRect Rect(White_space,White_space,Image.cols+3*White_space,Image.rows+3*White_space);
  Painter.drawRect(Rect);

//  Painter.translate(QPointF(2.5*White_space,2.5*White_space));
  // reuse the draw procedure of the layer
  static_cast<_layer_positions *>(Layers[1].get())->draw(Painter,Width1,Height1,Positions_font_size_print,Positions_out_circle_size_print,Positions_font_color_print,Positions_out_circle_color_print,Positions_in_circle_color_print);
//  Painter.translate(QPointF(-2.5*White_space,-2.5*White_space));

  Painter.end();

  Composed_image.save(Project_dir+QString::fromStdString(_common_window_ns::FILE_IMAGE_POSITIONS),"PNG");

  QMessageBox::information(this, tr("Information"),QString::fromStdString("The file '"+_common_window_ns::FILE_IMAGE_POSITIONS+"' has been correctly saved"));
}

/*************************************************************************/

void _window::save_image_slot()
{
  save_image_positions();
}

/*************************************************************************/

//void _window::program_interpreter_slot()
//{
//#ifdef LINUX
//  QString Program("interpreter");
//#else
//  QString Program("Interpreter.exe");
//#endif

//  QProcess::startDetached(Program,QStringList(""));
//}

/*************************************************************************/

//void _window::program_maplab_slot()
//{
//#ifdef LINUX
//  QString Program("maplab");
//#else
//  QString Program("MapLab.exe");
//#endif

//  QProcess::startDetached(Program,QStringList(""));
//}

/*************************************************************************/

void _window::options_slot()
{
  if (!W_options){
    W_options=new _w_options(this);
    connect(W_options,SIGNAL(accepted()),W_options,SLOT(close_slot()));
  }

  W_options->show();
  W_options->raise();
  W_options->activateWindow();
}

/*************************************************************************/

void _window::left_handle_slot()
{
  QList<int> List=Splitter->sizes();
  if (Left_part_full==true){
    Left_part_full=false;
    Left_part_size=List[0];
    List[0]=0;
  }
  else{
    Left_part_full=true;
    List[0]=Left_part_size;
  }
  Splitter->setSizes(List);
}

/*************************************************************************/

void _window::right_handle_slot()
{
  QList<int> List=Splitter->sizes();
  if (Right_part_full==true){
    Right_part_full=false;
    Right_part_size=List[2];
    List[2]=0;
  }
  else{
    Right_part_full=true;
    List[2]=Right_part_size;
  }
  Splitter->setSizes(List);
}

/*************************************************************************/

void _window::add_layer_image(std::shared_ptr<cv::Mat> Image1)
{
  // Image1 is the color image
  std::string Name;

  // create a image layer with its associated name
  Layers.push_back(std::make_shared<_layer_basic_ui>(this,"Name"));
  // assign the image
  int Position=Layers.size()-1;
  Layers[Position]->image(Image1);

  // get the id for the texture
  Textures.push_back(GL_widget[1]->set_texture(Layers[Position]->image()));
  Transparency.push_back(0);

  GL_widget[1]->refresh_texture(Image_vis->cols,Image_vis->rows);

  compute_dimensions();
}

/*************************************************************************/

void _window::add_layer_positions()
{
  // create a image layer with its associated name

  std::shared_ptr<_layer_positions> Layer=std::make_shared<_layer_positions_ui>();
  Layers.push_back(Layer);
  // assign the image
  int Position=Layers.size()-1;
  Layer->add_input_data(Vec_positions);
  Layer->size(Image_vis->cols,Image_vis->rows);
  Layer->parameters(Positions_font_size_display,Positions_out_circle_size_display,Positions_font_color_display, Positions_out_circle_color_display, Positions_in_circle_color_display, Positions_selection_out_circle_color_display, Positions_selection_in_circle_color_display);
  Layer->update();

  // get the id for the texture
  Textures.push_back(GL_widget[0]->set_texture(Layers[Position]->image()));
  Transparency.push_back(0);
}

/*************************************************************************/

int _window::search_point(int Pos_x, int Pos_y)
{
  float Min_distance=1e6;
  float Distance;
  int Pos=-1;
  int x;
  int y;

  for (unsigned int i=0;i<Vec_positions.size();i++){
    x=Vec_positions[i].Coordinates.x-Pos_x;
    y=Vec_positions[i].Coordinates.y-Pos_y;
    Distance=sqrtf(float(x*x+y*y));
    if (Distance<Distance_threshold){
      if (Distance<Min_distance){
        Min_distance=Distance;
        Pos=i;
      }
    }
  }

  return Pos;
}

/*************************************************************************/

void _window::update_positions(int Pos_x, int Pos_y)
{
  int Pos;
  _common_ns::_position_data Position_data;

  switch (Action_type){
  case _window_ns::_action_type::ACTION_ADD_POINTS:
    {
      // check that is not the same of a previous one
      bool Found=false;
      for (unsigned int i=0;i<Vec_positions.size();i++){
        if (Vec_positions[i].Coordinates.x==Pos_x && Vec_positions[i].Coordinates.y==Pos_y){
          Found=true;
          break;
        }
      }

      if (Found==false){
        Position_data.Position_index=Vec_positions.size()+1;
        Position_data.Coordinates=_vertex2i(Pos_x,Pos_y);
        Position_data.Active=false;

        Vec_positions.push_back(Position_data);
      }
      else{
         QMessageBox::information(this,tr("Information"),"The position was previously included, so it is not added");
      }
    }
    break;
  case _window_ns::_action_type::ACTION_MOVE_POINTS:
    {
      if (Replace==false){
        // find if there is a point near the position
        Pos=search_point(Pos_x,Pos_y);

        if (Pos!=-1){
          Vec_positions[Pos].Active=true;
          Replace=true;
          Replace_position=Pos;
        }
      }
      else{
        Vec_positions[Replace_position].Coordinates.x=Pos_x;
        Vec_positions[Replace_position].Coordinates.y=Pos_y;
        Vec_positions[Replace_position].Active=false;
        Replace=false;
      }
    }
    break;
  case _window_ns::_action_type::ACTION_REMOVE_POINTS:
      if (Vec_positions.size()>0){
        Pos=search_point(Pos_x,Pos_y);

        // check that is the last point
        if (Pos==int(Vec_positions.size()-1)){
          for (unsigned int i=Pos;i<Vec_actions.size()-1;i++){
            Vec_positions[i]=Vec_positions[i+1];
          }
          Vec_positions.pop_back();
        }
      }
    break;
  default:break;
  }

  // update and draw
  std::static_pointer_cast<_layer_positions_ui>(Layers[1])->add_input_data(Vec_positions);
  std::static_pointer_cast<_layer_positions_ui>(Layers[1])->update();

  Table_positions->update_table(Vec_positions);

  GL_widget[1]->update_texture(1);

  GL_widget[1]->update();
}

/*************************************************************************/

void _window::update_layer(std::string Name)
{
  Q_UNUSED(Name)
//  Layers.get_data(Name)->update();
//  GL_widget->update_texture(Name);

  GL_widget[0]->update();
}

/*************************************************************************/

void _window::update_layer(int Pos)
{
  Selected_layer=Pos;
//  update_layer(Order_images[Selected_layer]);
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

QWizardPage *createIntroPage()
{
  QWizardPage *page = new QWizardPage;
  page->setTitle("General information");

//    page->setPixmap(QWizard::WatermarkPixmap, QPixmap("./splash.png"));

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

void _window::restart()
{
//  Tab_widget->restart();

//  Save_project->setEnabled(false);
//  Save_layer->setEnabled(false);
}

/*************************************************************************/

void _window::compute_dimensions()
{
  if (Loaded_image==false) return;

//  int Result[]={-1,-1,-1,-1};

  int W0_width=GL_widget[1]->width();
  int W0_height=GL_widget[1]->height();

  int W1_width=GL_widget[1]->width();
  int W1_height=W0_height;

  float Ratio_w1=float(W1_width)/float(W1_height);

  int Width1=int(roundf(float(Image_vis->cols)*1.05f));
  float Ratio1=float(Width1)/float(W0_width);
  int Height1=0;

  // check width
  if (Ratio1>=1){
    // the original is bigger
    Ratio1=float(W0_width)*0.95f/float(Image_vis->cols);

    Width1=int(roundf(float(Image_vis->cols)*Ratio1));
    Height1=int(roundf(float(Image_vis->rows)*Ratio1));

//    cout << "Ratio1>=1 =" << Ratio1 << " W=" << Width1 << " H1=" << Height1 << endl;
    if (Width1%2!=0) Width1++;
    if (Height1%2!=0) Height1++;

//    if (Width1<=W0_width && Height1<=W0_height){ ?? set not use
//      Result[0]=Width1*Height1;
//    }
  }
  else{
    // the original is samller
    Ratio1=float(Width1)/float(W0_width);

    Width1=int(roundf(float(Image_vis->cols)/Ratio1));
    Height1=int(roundf(float(Image_vis->rows)/Ratio1));
//    cout << "Ratio1<1 =" << Ratio1 << " W=" << Width1 << " H1=" << Height1 << endl;
    if (Width1%2!=0) Width1++;
    if (Height1%2!=0) Height1++;

//    if (Width1<=W0_width && Height1<=W0_height){?? set not used
//      Result[0]=Width1*Height1;
//    }
  }
  int Pos=0;

  switch(Pos){
  case 0:
    Scaling[0]=float(Image_vis->cols)/float(Width1);

//    cout << "case 0=" << Scaling[0] << endl;

    ZOI.x=int(roundf(float(Image_vis->rows)*Ratio_w1/Scaling[0]));
    ZOI.y=int(roundf(float(Image_vis->rows)/Scaling[0]));

    if (ZOI.x%2!=0) ZOI.x++;
    if (ZOI.y%2!=0) ZOI.y++;

    Scaling[1]=float(ZOI.y)*Scaling[0]/float(W1_height);
    break;
  }

  GL_widget[1]->refresh_texture(Image_vis->cols,Image_vis->rows);
  GL_widget[1]->update();
}

/*************************************************************************/

void _window::change_scale_w1(float Scale)
{
  ZOI.x=int(roundf(float(ZOI.x)*Scale));
  ZOI.y=int(roundf(float(ZOI.y)*Scale));

  if (ZOI.x%2!=0) ZOI.x++;
  if (ZOI.y%2!=0) ZOI.y++;

  Scaling[1]*=Scale;
}

/*************************************************************************/

void _window::action_default_slot()
{
  Action_selected=int(_window_ns::_action_type::ACTION_DEFAULT);

  for (unsigned int i=0;i<int(_window_ns::_action_type::ACTION_LAST);i++){
    Vec_actions[i]->setIcon(Icons[i][0]);
  }

  Vec_actions[Action_selected]->setIcon(Icons[Action_selected][1]);

  //

  if (Action_type==_window_ns::_action_type::ACTION_MOVE_POINTS && Replace==true){
    Vec_positions[Replace_position].Active=false;
    Replace=false;
  }

  Action_type=_window_ns::_action_type::ACTION_DEFAULT;

  GL_widget[1]->editing(false);
}

/*************************************************************************/

void _window::action_add_points_slot()
{
  Action_selected=int(_window_ns::_action_type::ACTION_ADD_POINTS);

  for (unsigned int i=0;i<int(_window_ns::_action_type::ACTION_LAST);i++){
    Vec_actions[i]->setIcon(Icons[i][0]);
  }

  Vec_actions[Action_selected]->setIcon(Icons[Action_selected][1]);

  //

  if (Action_type==_window_ns::_action_type::ACTION_MOVE_POINTS && Replace==true){
    Vec_positions[Replace_position].Active=false;
    Replace=false;
  }

  Action_type=_window_ns::_action_type::ACTION_ADD_POINTS;
  GL_widget[1]->editing(true);
}

/*************************************************************************/

void _window::action_remove_points_slot()
{
  Action_selected=int(_window_ns::_action_type::ACTION_REMOVE_POINTS);

  for (unsigned int i=0;i<int(_window_ns::_action_type::ACTION_LAST);i++){
    Vec_actions[i]->setIcon(Icons[i][0]);
  }

  Vec_actions[Action_selected]->setIcon(Icons[Action_selected][1]);

  //

  if (Action_type==_window_ns::_action_type::ACTION_MOVE_POINTS && Replace==true){
    Vec_positions[Replace_position].Active=false;
    Replace=false;
  }

  Action_type=_window_ns::_action_type::ACTION_REMOVE_POINTS;
  GL_widget[1]->editing(true);
}

/*************************************************************************/

void _window::action_move_points_slot()
{
  Action_selected=int(_window_ns::_action_type::ACTION_MOVE_POINTS);

  for (unsigned int i=0;i<int(_window_ns::_action_type::ACTION_LAST);i++){
    Vec_actions[i]->setIcon(Icons[i][0]);
  }

  Vec_actions[Action_selected]->setIcon(Icons[Action_selected][1]);

  //

  Action_type=_window_ns::_action_type::ACTION_MOVE_POINTS;
  GL_widget[1]->editing(true);
}

/*************************************************************************/
// Options display

void _window::options_parameters_display(int Font_size_display1, int Out_circle_size_display1, QColor Font_color_display1, QColor Out_circle_color_display1, QColor In_circle_color_display1, QColor Selection_out_circle_color_display1, QColor Selection_in_circle_color_display1,bool Copy_display_values1)
{
  Positions_font_size_display=Font_size_display1;
  Positions_out_circle_size_display=Out_circle_size_display1;
  Positions_font_color_display=Font_color_display1;
  Positions_out_circle_color_display=Out_circle_color_display1;
  Positions_in_circle_color_display=In_circle_color_display1;
  Positions_selection_out_circle_color_display=Selection_out_circle_color_display1;
  Positions_selection_in_circle_color_display=Selection_in_circle_color_display1;
  Copy_display_values=Copy_display_values1;

  if (Copy_display_values==true){
    Positions_font_size_print=Font_size_display1;
    Positions_out_circle_size_print=Out_circle_size_display1;
    Positions_font_color_print=Font_color_display1;
    Positions_out_circle_color_print=Out_circle_color_display1;
    Positions_in_circle_color_print=In_circle_color_display1;
  }

  save_settings();

  if (Loaded_image==true){
    std::static_pointer_cast<_layer_positions_ui>(Layers[1])->parameters(Font_size_display1,Out_circle_size_display1, Font_color_display1, Out_circle_color_display1, In_circle_color_display1, Selection_out_circle_color_display1, Selection_in_circle_color_display1);
    std::static_pointer_cast<_layer_positions_ui>(Layers[1])->update();

    GL_widget[1]->update_texture(1);

    GL_widget[1]->update();
  }
}

/*************************************************************************/
// Options print

void _window::options_parameters_print(int Font_size_print1, int Out_circle_size_print1, QColor Font_color_print1, QColor Out_circle_color_print1, QColor In_circle_color_print1)
{
  Positions_font_size_print=Font_size_print1;
  Positions_out_circle_size_print=Out_circle_size_print1;
  Positions_font_color_print=Font_color_print1;
  Positions_out_circle_color_print=Out_circle_color_print1;
  Positions_in_circle_color_print=In_circle_color_print1;

  save_settings();
}

/*************************************************************************/

int _window::image_width()
{
  if (Load_image) return Image_vis->cols;
  else return 0;
}

/*************************************************************************/

int _window::image_height()
{
  if (Load_image) return Image_vis->rows;
  else return 0;
}

/*************************************************************************/

void _window::selected_position(int Position1,bool Position_active1)
{
  // update and draw
  std::static_pointer_cast<_layer_positions_ui>(Layers[1])->selected_position(Position1,Position_active1);
  std::static_pointer_cast<_layer_positions_ui>(Layers[1])->update();

  GL_widget[1]->update_texture(1);

  GL_widget[1]->update();
}
