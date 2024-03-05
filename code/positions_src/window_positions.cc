/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "window_positions.h"
#include "glwidget_positions.h"
#include "window_main.h"

/*************************************************************************/

_window_positions::_window_positions(_window_main *Window_main1)
{
#ifdef DEBUG_XML
  std::cout << "en _window_positions " << __LINE__ << std::endl;
#endif

  Window_main=Window_main1;

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

  Main_gl_widget =std::make_shared<_gl_widget_positions>(this,_window_positions_ns::MAIN_IMAGE);
  Main_gl_widget->setSizePolicy(Q);
  Main_gl_widget->setMinimumSize(300,300);

  Splitter=new _splitter(Qt::Horizontal);

  //
  Splitter->addWidget(Main_gl_widget.get());
  Splitter->addWidget(Groupbox_positions);

  setCentralWidget(Splitter);

  // actions for file menu
  Load_project = new QAction(QIcon(":/common/icons/fileopen.png"), tr("Load project data"), this);
  Load_project->setShortcuts(QKeySequence::Open);
  Load_project->setToolTip(tr("Select the project folder"));
  connect(Load_project, SIGNAL(triggered()), this, SLOT(load_project_slot()));

  Load_auxiliary_image = new QAction(QIcon(":/common/icons/fileopen.png"), tr("Load auxiliary image"), this);
  Load_auxiliary_image->setEnabled(false);
  Load_auxiliary_image->setToolTip(tr("Load an image selecting the file"));
  connect(Load_auxiliary_image, SIGNAL(triggered()), this, SLOT(load_auxiliary_image_slot()));

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
  connect(Exit, SIGNAL(triggered()), Window_main, SLOT(close()));

  // actions for programs
//  QAction *Distiller = new QAction(tr("Interpreter"), this);
//  connect(Distiller,SIGNAL(triggered()),this,SLOT(program_interpreter_slot()));

//  QAction *Maplab = new QAction(tr("MapLab"), this);
//  connect(Maplab,SIGNAL(triggered()),this,SLOT(program_maplab_slot()));

#ifndef UNIFIED
  // actions for file menu
  QAction *Help_info = new QAction(tr("&Info"), this);
  connect(Help_info, SIGNAL(triggered()), this, SLOT(info_slot()));
#endif

  // menus
  QMenu* File_menu=menuBar()->addMenu(tr("&File"));
  File_menu->addAction(Load_project);
  File_menu->addAction(Load_auxiliary_image);
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

#ifndef UNIFIED
  QMenu *Menu_help=menuBar()->addMenu(tr("&Help"));
  Menu_help->addAction(Help_info);
  Menu_help->setAttribute(Qt::WA_AlwaysShowToolTips);
#endif

//  resize(_window_positions_ne::WIWNDOW_WIDTH,_window_positions_ne::WIWNDOW_HEIGHT);

  // TOOL BAR
  Vec_actions.resize(int(_window_positions_ns::_action_type::ACTION_LAST));

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

//  Vec_actions[int(_window_positions_ns::_action_type::ACTION_DEFAULT)] = new QAction(QIcon(":/common/icons/move.png"), tr("Camera"), this);
  Vec_actions[int(_window_positions_ns::_action_type::ACTION_DEFAULT)] = new QAction(Icons[0][1], tr("Camera"), this);
  Vec_actions[int(_window_positions_ns::_action_type::ACTION_DEFAULT)]->setStatusTip(tr("Selects things"));
  Vec_actions[int(_window_positions_ns::_action_type::ACTION_DEFAULT)]->setCheckable(true);
  Vec_actions[int(_window_positions_ns::_action_type::ACTION_DEFAULT)]->setChecked(true);
  Vec_actions[int(_window_positions_ns::_action_type::ACTION_DEFAULT)]->setObjectName("move");

  connect(Vec_actions[int(_window_positions_ns::_action_type::ACTION_DEFAULT)], SIGNAL(triggered()), this, SLOT(action_default_slot()));

  Vec_actions[int(_window_positions_ns::_action_type::ACTION_ADD_POINTS)]= new QAction(Icons[1][0], tr("Add points"), this);
  Vec_actions[int(_window_positions_ns::_action_type::ACTION_ADD_POINTS)]->setToolTip(tr("Add points by pointing and clicking the right button of the mouse"));
  Vec_actions[int(_window_positions_ns::_action_type::ACTION_ADD_POINTS)]->setCheckable(true);
  Vec_actions[int(_window_positions_ns::_action_type::ACTION_ADD_POINTS)]->setObjectName("add_points");
  connect(Vec_actions[int(_window_positions_ns::_action_type::ACTION_ADD_POINTS)], SIGNAL(triggered()), this, SLOT(action_add_points_slot()));

  Vec_actions[int(_window_positions_ns::_action_type::ACTION_REMOVE_POINTS)]= new QAction(Icons[2][0], tr("Remove points"), this);
  Vec_actions[int(_window_positions_ns::_action_type::ACTION_REMOVE_POINTS)]->setToolTip(tr("Remove points by pointing clicking the right button of the mouse"));
  Vec_actions[int(_window_positions_ns::_action_type::ACTION_REMOVE_POINTS)]->setCheckable(true);
  Vec_actions[int(_window_positions_ns::_action_type::ACTION_REMOVE_POINTS)]->setObjectName("remove_points");
//  Vec_actions[int(_window_positions_ns::_action_type::ACTION_CHANGE_CAMERA)]->setChecked(true);
  connect(Vec_actions[int(_window_positions_ns::_action_type::ACTION_REMOVE_POINTS)], SIGNAL(triggered()), this, SLOT(action_remove_points_slot()));

  Vec_actions[int(_window_positions_ns::_action_type::ACTION_MOVE_POINTS)]= new QAction(Icons[3][0], tr("Move points"), this);
  Vec_actions[int(_window_positions_ns::_action_type::ACTION_MOVE_POINTS)]->setToolTip(tr("Move points by pointing clicking the right button of the mouse. Then move the cursor to the new position and click the right button of the mouse"));
  Vec_actions[int(_window_positions_ns::_action_type::ACTION_MOVE_POINTS)]->setCheckable(true);
  Vec_actions[int(_window_positions_ns::_action_type::ACTION_MOVE_POINTS)]->setObjectName("move_points");
  connect(Vec_actions[int(_window_positions_ns::_action_type::ACTION_MOVE_POINTS)], SIGNAL(triggered()), this, SLOT(action_move_points_slot()));

  Action_group = new QActionGroup(this);
  Action_group->addAction(Vec_actions[int(_window_positions_ns::_action_type::ACTION_DEFAULT)]);
  Action_group->addAction(Vec_actions[int(_window_positions_ns::_action_type::ACTION_ADD_POINTS)]);
  Action_group->addAction(Vec_actions[int(_window_positions_ns::_action_type::ACTION_REMOVE_POINTS)]);
  Action_group->addAction(Vec_actions[int(_window_positions_ns::_action_type::ACTION_MOVE_POINTS)]);

  ToolBar = addToolBar(tr("Tools"));
  ToolBar->addActions(Action_group->actions());
  ToolBar->setMovable(false);
  ToolBar->setEnabled(false);

//  addToolBar(Qt::LeftToolBarArea,ToolBar);
  addToolBar(Qt::LeftToolBarArea,ToolBar);

#ifndef UNIFIED
  setWindowTitle(_window_positions_ns::Program_name);

  resize(Screen_width/2,Screen_height/2);
#endif

//  resize(Screen_size.width()*_window_positions_ns::SCREEN_WIDTH_FACTOR,Screen_size.height()*_window_positions_ns::SCREEN_HEIGHT_FACTOR);

//  check_project();
}

/*************************************************************************/

_window_positions::~_window_positions()
{
#ifdef DEBUG_XML
  std::cout << "terminando window" <<endl;
#endif
}

/*************************************************************************/

//void _window_positions::ui_font_size(int Size)
//{
//  UI_font_size=Size;

//  QFont Font=QApplication::font();
//  Font.setPointSize(Size);
////  QApplication::setFont(Font);
//  setFont(Font);

//  menuBar()->setFont(Font);

//  update();
//}

/*************************************************************************/

//void _window_positions::pass_ui_font_size(int UI_font_size1)
//{
//  Window_main->ui_font_size(UI_font_size1);
//}

/*************************************************************************/

void _window_positions::read_settings()
{
//  QSettings settings(Project_dir+"/settings_"+_window_positions_ns::Program_name.toLower()+".ini",QSettings::IniFormat);
//  QSettings settings(Project_dir+"/settings.ini",QSettings::IniFormat);

  // display
//  settings.beginGroup("DisplayParameters");
//    Positions_font_size_display=settings.value("DisplayFontSize",_window_positions_ns::POSITIONS_DISPLAY_FONT_SIZE).toInt();
//    Positions_out_circle_size_display=settings.value("DisplayOutCircleSize",_window_positions_ns::POSITIONS_DISPLAY_OUT_CIRCLE_SIZE).toInt();
//    Positions_font_color_display=settings.value("DisplayFontColor",_window_positions_ns::POSITIONS_DISPLAY_FONT_COLOR).value<QColor>();
//    Positions_out_circle_color_display=settings.value("DisplayOutCircleColor",_window_positions_ns::POSITIONS_DISPLAY_OUT_CIRCLE_COLOR).value<QColor>();
//    Positions_in_circle_color_display=settings.value("DisplayInCircleColor",_window_positions_ns::POSITIONS_DISPLAY_IN_CIRCLE_COLOR).value<QColor>();
//    Positions_selection_out_circle_color_display=settings.value("DisplaySelectionOutCircleColor",_window_positions_ns::POSITIONS_DISPLAY_SELECTION_OUT_CIRCLE_COLOR).value<QColor>();
//    Positions_selection_in_circle_color_display=settings.value("DisplaySelectionInCircleColor",_window_positions_ns::POSITIONS_DISPLAY_SELECTION_IN_CIRCLE_COLOR).value<QColor>();
//  settings.endGroup();

//  // print
//  settings.beginGroup("PrintParameters");
//  Positions_font_size_print=settings.value("PrintFontSize",_window_positions_ns::POSITIONS_DISPLAY_FONT_SIZE).toInt();
//  Positions_out_circle_size_print=settings.value("PrintOutCircleSize",_window_positions_ns::POSITIONS_DISPLAY_OUT_CIRCLE_SIZE).toInt();
//  Positions_font_color_print=settings.value("PrintFontColor",_window_positions_ns::POSITIONS_DISPLAY_FONT_COLOR).value<QColor>();
//  Positions_out_circle_color_print=settings.value("PrintOutCircleColor",_window_positions_ns::POSITIONS_DISPLAY_OUT_CIRCLE_COLOR).value<QColor>();
//  Positions_in_circle_color_print=settings.value("PrintInCircleColor",_window_positions_ns::POSITIONS_DISPLAY_IN_CIRCLE_COLOR).value<QColor>();
//  settings.endGroup();

//  settings.beginGroup("General");
//    UI_font_size=settings.value("UIFontSize",_common_ns::UI_FONT_SIZE_DEFAULT).toInt();
//  settings.endGroup();
}

/*************************************************************************/

void _window_positions::save_settings()
{
//  QSettings settings(Project_dir+"/settings_"+_window_positions_ns::Program_name.toLower()+".ini",QSettings::IniFormat);
//  QSettings settings(Project_dir+"/settings.ini",QSettings::IniFormat);

//  // display
//  settings.beginGroup("DisplayParameters");
//  settings.setValue("DisplayFontSize", Window_main->display_font_size());
//  settings.setValue("DisplayOutCircleSize", Window_main->display_out_circle_size());
//  settings.setValue("DisplayFontColor", Window_main->display_font_color());
//  settings.setValue("DisplayOutCircleColor", Window_main->display_out_circle_color());
//  settings.setValue("DisplayInCircleColor", Window_main->display_in_circle_color());
//  settings.setValue("DisplaySelectionOutCircleColor", Window_main->display_selection_out_circle_color());
//  settings.setValue("DisplaySelectionInCircleColor", Window_main->display_selection_in_circle_color());
//  settings.endGroup();

//  // print
//  settings.beginGroup("PrintParameters");
//  settings.setValue("PrintFontSize", Window_main->print_font_size());
//  settings.setValue("PrintOutCircleSize", Window_main->print_out_circle_size());
//  settings.setValue("PrintFontColor", Window_main->print_font_color());
//  settings.setValue("PrintOutCircleColor", Window_main->print_out_circle_color());
//  settings.setValue("PrintInCircleColor", Window_main->print_in_circle_color());
//  settings.endGroup();

//  settings.beginGroup("General");
//    settings.setValue("UIFontSize",UI_font_size);
//  settings.endGroup();
}

/*************************************************************************/

//void _window_positions::closeEvent(QCloseEvent *Event)
//{
//  save_settings();
//  Event->accept();
//}

/*************************************************************************/

void _window_positions::compute_display_values()
{
  // set the parameters depending on the size of the image

  if (Window_main->display_font_size()==_window_positions_ns::POSITIONS_DISPLAY_FONT_SIZE){ // 0
    // it is the first time, compute a font size that depends on the size of the image
//    int Font_size=int(sqrtf(Main_image->cols*Main_image->rows)*_window_positions_ns::FONT_FACTOR);
    int Font_size=int(Main_image->rows/_window_positions_ns::NUMBER_OF_ROWS);
    Window_main->display_font_size(Font_size);
    Window_main->print_font_size(Font_size);
  }

  if (Window_main->display_out_circle_size()==_window_positions_ns::POSITIONS_DISPLAY_OUT_CIRCLE_SIZE){ // 0
//    int Out_circle_size=int(sqrtf(Main_image->cols*Main_image->rows)*_window_positions_ns::OUT_CIRCLE_FACTOR);
    int Out_circle_size=int(Main_image->rows/_window_positions_ns::NUMBER_OF_ROWS);
    Window_main->display_out_circle_size(Out_circle_size);
    Window_main->print_out_circle_size(Out_circle_size);
  }
}

/*************************************************************************/

void _window_positions::load_project()
{
//  ui_font_size(UI_font_size);

  // check the number of images
  QDir Directory_images(Project_dir+"/images");
  std::string Dir_images=Directory_images.absolutePath().toStdString();

  QStringList Files_images = Directory_images.entryList(QStringList() << "*.png" << "*.jpg", QDir::Files);

  // there are more than one image, select one
  QString File_name;

  if (Files_images.size()>0){
    if (Files_images.size()==1){
      File_name=Files_images[0];
      File_name=Project_dir+"/images/"+File_name;
    }
    else{
      QFileDialog Dialog(this,tr("Select the image"),Project_dir+"/images");
      Dialog.setFileMode(QFileDialog::ExistingFile);
      Dialog.setNameFilter(tr("Images (*.png *.jpg)"));
      if (Dialog.exec()){
        File_name=Dialog.selectedFiles()[0];
      }
    }
  }

  Vec_layers.clear();
  Vec_textures.clear();
  Vec_transparency.clear();

  // load the selected image
  Main_image=load_image(File_name.toStdString());

  Loaded_image=true;

  // compute the display values depending on the image size
  compute_display_values();

  // save the values
  Window_main->save_settings();

  // add a layer with the image
  add_layer_image(Main_image);

  // add a layer to show the information
  add_layer_positions();

  // load the numerical values of the positions
  load_positions();

  ToolBar->setEnabled(true);
  Options->setEnabled(true);
  Load_auxiliary_image->setEnabled(true);
  Save_image->setEnabled(true);
  Save_positions->setEnabled(true);

  Main_gl_widget->setCursor(Qt::CrossCursor);
  Main_gl_widget->update();
}

#ifndef UNIFIED
/*************************************************************************/

void _window_positions::load_project_slot()
{
  _w_directory Dialog(this,"projects",&Project_name);

  if (Dialog.exec()==QDialog::Accepted && Project_name!=""){
    QDir Dir(Project_name);
    Project_dir=Dir.absolutePath();

    load_project();
  }
}
#else
void _window_positions::load_project_slot()
{
  load_project();
}
#endif

/*************************************************************************/

std::shared_ptr<cv::Mat> _window_positions::load_image(std::string File_name)
{
  // read the image
  _image_IO Image_io;
  std::shared_ptr<cv::Mat> Image=std::make_shared<cv::Mat>();

  Image_io.read_image(File_name,*Image.get());

  int Width_aux=Image->cols;
  int Height_aux=Image->rows;

  adjust_image_sizes(Width_aux,Height_aux);
  if (Width_aux!=Image->cols || Height_aux!=Image->rows){
    cv::resize(*Image.get(),*Image.get(),cv::Size(Width_aux,Height_aux),0,0,cv::INTER_CUBIC);
  }

  // flip the original image to adapt it to OpenGL
  cv::flip(*Image.get(),*Image.get(),0);
  cv::cvtColor(*Image.get(),*Image.get(),cv::COLOR_BGR2BGRA,4);

  return Image;

//  // compute the distance threshold
//  Distance_threshold=float(Image->cols)*_window_positions_ns::PERCENTAGE_THRESHOLD_DISTANCE;
//  if (Distance_threshold<_window_positions_ns::MINIMUM_THRESHOLD_DISTANCE)  Distance_threshold=_window_positions_ns::MINIMUM_THRESHOLD_DISTANCE;

}

/*************************************************************************/
// in case that there more than one image the user must select one

void _window_positions::load_auxiliary_image_slot()
{
  // check if therea are image files
  QStringList Filters;
  Filters << "*.png" << "*.jpg";

  QString File_auxiliary_image;
  _w_directory Dialog(this,"Select the auxiliary image file","projects",&File_auxiliary_image, _w_directory::MODE_FILE,Filters);

  if (Dialog.exec()==QDialog::Accepted && File_auxiliary_image!=""){

    Auxiliary_image=load_image(File_auxiliary_image.toStdString());

    // add the gl_widget
    QSizePolicy Q(QSizePolicy::Expanding,QSizePolicy::Expanding);

    Auxiliary_gl_widget = std::make_shared<_gl_widget_positions>(this,_window_positions_ns::AUXILIARY_IMAGE);
    Auxiliary_gl_widget->setSizePolicy(Q);
    Auxiliary_gl_widget->setMinimumSize(300,300);

    // WARNING: if this instruction is placed after the update (line 479), initilizeGL is not called
    Splitter->insertWidget(0,Auxiliary_gl_widget.get()); // WARNING

    // get the id for the texture
    Auxiliary_texture=Auxiliary_gl_widget->set_texture(Auxiliary_image);
    Auxiliary_transparency=0;

    Auxiliary_gl_widget->refresh_texture(Auxiliary_image->cols,Auxiliary_image->rows);

    Auxiliary_gl_widget->update();
  }
}

/*************************************************************************/

void _window_positions::load_positions()
{
  // now load the positions info
  _data_io::load_project_data_csv(this,Project_dir.toStdString(),Project_data,Vec_names_xrf_pdb,Vec_names_xrd_pdb);

  // add the positions
  Vec_positions.resize(Project_data.Vec_coordinate_x_original.size());
  for (unsigned int i=0;i<Project_data.Vec_coordinate_x_original.size();i++){
    Vec_positions[i]={int(i)+1,_vertex2i(Project_data.Vec_coordinate_x_original[i],Project_data.Vec_coordinate_y_original[i]),false};
  }

  // compute the distance threshold
  Distance_threshold=float(Main_image->cols)*_window_positions_ns::PERCENTAGE_THRESHOLD_DISTANCE;
  if (Distance_threshold<_window_positions_ns::MINIMUM_THRESHOLD_DISTANCE) Distance_threshold=_window_positions_ns::MINIMUM_THRESHOLD_DISTANCE;

  // update and draw
  std::static_pointer_cast<_layer_positions_positions>(Vec_layers[1])->add_input_data(Vec_positions);
  std::static_pointer_cast<_layer_positions_positions>(Vec_layers[1])->update();
  Main_gl_widget->update_texture(1);

  Table_positions->update_table(Vec_positions);
}

/*************************************************************************/

void _window_positions::save_positions_slot()
{
//  Project_data.Num_samples=Vec_positions.size();

  Project_data.Width_pixel=Main_image->cols;
  Project_data.Height_pixel=Main_image->rows;

  Project_data.Vec_coordinate_x.resize(Vec_positions.size());
  Project_data.Vec_coordinate_y.resize(Vec_positions.size());

  for (unsigned int i=0;i<Vec_positions.size();i++){
    Project_data.Vec_coordinate_x[i]=Vec_positions[i].Coordinates.x;
    Project_data.Vec_coordinate_y[i]=Vec_positions[i].Coordinates.y;
  }

  _data_io::save_project_data_csv(this,Project_dir.toStdString(),Project_data);

  Window_main->check_project_state();
}

/*************************************************************************/

void _window_positions::save_image_positions()
{
//  int White_space=10;

//  std::string Name=Order_images[Selected_layer];
  cv::Mat Image=Vec_layers[0]->image()->clone();
  cv::flip(Image,Image,0);

  float Width1=float(Image.cols)-1;
  float Height1=float(Image.rows)-1;

  QImage Composed_image(Image.data,Image.cols,Image.rows,static_cast<int>(Image.step),QImage::Format_ARGB32);
//  Composed_image=Composed_image.rgbSwapped();

//  QImage Image1(Image.cols+White_space*5,Image.rows+White_space*5,QImage::Format_ARGB32);
//  Image1.fill(Qt::white);

  QPainter Painter(&Composed_image);
//  Painter.drawImage(2.5*White_space,2.5*White_space,image);

//  QPen Previous_pen=Painter.pen();

//  QPen Pen;
//  Pen.setWidth(5);
//  Painter.setPen(Pen);

//  QRect Rect(White_space,White_space,Image.cols+3*White_space,Image.rows+3*White_space);
//  Painter.drawRect(Rect);

//  Painter.translate(QPointF(2.5*White_space,2.5*White_space));
  // reuse the draw procedure of the layer
  static_cast<_layer_positions_positions *>(Vec_layers[1].get())->draw(Painter,Width1,Height1, Window_main->print_font_size(), Window_main->print_out_circle_size(), Window_main->print_font_color(), Window_main->print_out_circle_color(), Window_main->print_in_circle_color());

  Painter.end();

  Composed_image.save(Project_dir+"/"+QString::fromStdString(_common_window_ns::FILE_IMAGE_POSITIONS),"PNG");

  QMessageBox::information(this, tr("Information"),QString::fromStdString("The image with the positions has been correctly saved in <b>positions</b> folder"));
}

/*************************************************************************/

void _window_positions::save_image_slot()
{
  save_image_positions();
}

/*************************************************************************/

//void _window_positions::program_interpreter_slot()
//{
//#ifdef LINUX
//  QString Program("interpreter");
//#else
//  QString Program("Interpreter.exe");
//#endif

//  QProcess::startDetached(Program,QStringList(""));
//}

/*************************************************************************/

//void _window_positions::program_maplab_slot()
//{
//#ifdef LINUX
//  QString Program("maplab");
//#else
//  QString Program("MapLab.exe");
//#endif

//  QProcess::startDetached(Program,QStringList(""));
//}

/*************************************************************************/

void _window_positions::options_slot()
{
  if (!W_options){
    W_options=new _w_options_positions(this);
    connect(W_options,SIGNAL(accepted()),W_options,SLOT(close_slot()));
  }

  W_options->show();
  W_options->raise();
  W_options->activateWindow();
}

/*************************************************************************/

void _window_positions::left_handle_slot()
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

void _window_positions::right_handle_slot()
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

void _window_positions::add_layer_image(std::shared_ptr<cv::Mat> Image1)
{
  // Image1 is the color image
  std::string Name;

  // create a image layer with its associated name
  Vec_layers.push_back(std::make_shared<_layer_basic_positions_ui>(this,"Name"));
  // assign the image
  int Position=Vec_layers.size()-1;
  Vec_layers[Position]->image(Image1);

  // get the id for the texture
  Vec_textures.push_back(Main_gl_widget->set_texture(Vec_layers[Position]->image()));
  Vec_transparency.push_back(0);

  Main_gl_widget->refresh_texture(Main_image->cols,Main_image->rows);

  compute_dimensions();
}

/*************************************************************************/

void _window_positions::add_layer_positions()
{
  // create a image layer with its associated name

  std::shared_ptr<_layer_positions_positions> Layer=std::make_shared<_layer_positions_positions_ui>();
  Vec_layers.push_back(Layer);
  // assign the image
  int Position=Vec_layers.size()-1;
  Layer->add_input_data(Vec_positions);
  Layer->size(Main_image->cols,Main_image->rows);
  Layer->parameters( Window_main->display_font_size(), Window_main->display_out_circle_size(), Window_main->display_font_color(), Window_main->display_out_circle_color(), Window_main->display_in_circle_color(), Window_main->display_selection_out_circle_color(), Window_main->display_selection_in_circle_color());
  Layer->update();

  // get the id for the texture
  Vec_textures.push_back(Main_gl_widget->set_texture(Vec_layers[Position]->image()));
  Vec_transparency.push_back(0);
}

/*************************************************************************/

int _window_positions::search_point(int Pos_x, int Pos_y)
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

void _window_positions::update_positions(int Pos_x, int Pos_y)
{
  int Pos;
  _common_ns::_position_data Position_data;

  switch (Action_type){
  case _window_positions_ns::_action_type::ACTION_ADD_POINTS:
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
  case _window_positions_ns::_action_type::ACTION_MOVE_POINTS:
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
  case _window_positions_ns::_action_type::ACTION_REMOVE_POINTS:
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
  std::static_pointer_cast<_layer_positions_positions_ui>(Vec_layers[1])->add_input_data(Vec_positions);
  std::static_pointer_cast<_layer_positions_positions_ui>(Vec_layers[1])->update();

  Table_positions->update_table(Vec_positions);

  Main_gl_widget->update_texture(1);

  Main_gl_widget->update();
}

/*************************************************************************/

void _window_positions::update_layer(std::string Name)
{
  Q_UNUSED(Name)
//  Vec_layers.get_data(Name)->update();
//  Vec_gl_widget->update_texture(Name);

  Main_gl_widget->update();
}

/*************************************************************************/

void _window_positions::update_layer(int Pos)
{
  Selected_layer=Pos;
//  update_layer(Order_images[Selected_layer]);
}

/*************************************************************************/

void _window_positions::adjust_image_sizes(int &Width1, int &Height1)
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

QWizardPage *_window_positions::createIntroPage()
{
  QWizardPage *page = new QWizardPage;
  page->setTitle("General information");

//    page->setPixmap(QWizard::WatermarkPixmap, QPixmap("./splash.png"));

  QLabel *label = new QLabel(_window_positions_ns::Help_string);

  label->setWordWrap(true);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(label);
  page->setLayout(layout);

  return page;
}

#ifndef UNIFIED
/*************************************************************************/

void _window_positions::info_slot()
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

void _window_positions::restart()
{
//  Tab_widget->restart();

//  Save_project->setEnabled(false);
//  Save_layer->setEnabled(false);
}

/*************************************************************************/

void _window_positions::compute_dimensions()
{
  if (Loaded_image==false) return;

  int Main_width=Main_gl_widget->width();
  int Main_height=Main_gl_widget->height();

//  int W0_width=Main_gl_widget->width();
//  int W0_height=Main_gl_widget->height();

  float Main_ratio=float(Main_width)/float(Main_height);

  int Width1=int(roundf(float(Main_image->cols)*1.05f));
  float Ratio1=float(Width1)/float(Main_width);
  int Height1=0;

  // check width
  if (Ratio1>=1){
    // the original is bigger
    Ratio1=float(Main_width)*0.95f/float(Main_image->cols);
    Width1=int(roundf(float(Main_image->cols)*Ratio1));
    Height1=int(roundf(float(Main_image->rows)*Ratio1));

//    cout << "Ratio1>=1 =" << Ratio1 << " W=" << Width1 << " H1=" << Height1 << endl;
    if (Width1%2!=0) Width1++;
    if (Height1%2!=0) Height1++;
  }
  else{
    // the original is samller
    Ratio1=float(Width1)/float(Main_width);

    Width1=int(roundf(float(Main_image->cols)/Ratio1));
    Height1=int(roundf(float(Main_image->rows)/Ratio1));
//    cout << "Ratio1<1 =" << Ratio1 << " W=" << Width1 << " H1=" << Height1 << endl;
    if (Width1%2!=0) Width1++;
    if (Height1%2!=0) Height1++;
  }

  int Pos=0;
  switch(Pos){
  case _window_positions_ns::MAIN_IMAGE:
    Main_image_scaling=float(Main_image->cols)/float(Width1);

    ZOI.x=int(roundf(float(Main_image->rows)*Main_ratio/Main_image_scaling));
    ZOI.y=int(roundf(float(Main_image->rows)/Main_image_scaling));

    if (ZOI.x%2!=0) ZOI.x++;
    if (ZOI.y%2!=0) ZOI.y++;

    Main_image_scaling=float(ZOI.y)*Main_image_scaling/float(Main_height);
    break;
  }

  Main_gl_widget->refresh_texture(Main_image->cols,Main_image->rows);
  Main_gl_widget->update();
}

/*************************************************************************/

void _window_positions::change_translation(int Translation_x1,int Translation_y1)
{
  Main_image_translation.x=Translation_x1;
  Main_image_translation.y=Translation_y1;
}

/*************************************************************************/

void _window_positions::change_scale(float Scale)
{
  ZOI.x=int(roundf(float(ZOI.x)*Scale));
  ZOI.y=int(roundf(float(ZOI.y)*Scale));

  if (ZOI.x%2!=0) ZOI.x++;
  if (ZOI.y%2!=0) ZOI.y++;

  Main_image_scaling=Scale;
}

/*************************************************************************/

void _window_positions::action_default_slot()
{
  Action_selected=int(_window_positions_ns::_action_type::ACTION_DEFAULT);

  for (unsigned int i=0;i<int(_window_positions_ns::_action_type::ACTION_LAST);i++){
    Vec_actions[i]->setIcon(Icons[i][0]);
  }

  Vec_actions[Action_selected]->setIcon(Icons[Action_selected][1]);

  //

  if (Action_type==_window_positions_ns::_action_type::ACTION_MOVE_POINTS && Replace==true){
    Vec_positions[Replace_position].Active=false;
    Replace=false;
  }

  Action_type=_window_positions_ns::_action_type::ACTION_DEFAULT;

  Main_gl_widget->editing(false);
}

/*************************************************************************/

void _window_positions::action_add_points_slot()
{
  Action_selected=int(_window_positions_ns::_action_type::ACTION_ADD_POINTS);

  for (unsigned int i=0;i<int(_window_positions_ns::_action_type::ACTION_LAST);i++){
    Vec_actions[i]->setIcon(Icons[i][0]);
  }

  Vec_actions[Action_selected]->setIcon(Icons[Action_selected][1]);

  //

  if (Action_type==_window_positions_ns::_action_type::ACTION_MOVE_POINTS && Replace==true){
    Vec_positions[Replace_position].Active=false;
    Replace=false;
  }

  Action_type=_window_positions_ns::_action_type::ACTION_ADD_POINTS;
  Main_gl_widget->editing(true);
}

/*************************************************************************/

void _window_positions::action_remove_points_slot()
{
  Action_selected=int(_window_positions_ns::_action_type::ACTION_REMOVE_POINTS);

  for (unsigned int i=0;i<int(_window_positions_ns::_action_type::ACTION_LAST);i++){
    Vec_actions[i]->setIcon(Icons[i][0]);
  }

  Vec_actions[Action_selected]->setIcon(Icons[Action_selected][1]);

  //

  if (Action_type==_window_positions_ns::_action_type::ACTION_MOVE_POINTS && Replace==true){
    Vec_positions[Replace_position].Active=false;
    Replace=false;
  }

  Action_type=_window_positions_ns::_action_type::ACTION_REMOVE_POINTS;
  Main_gl_widget->editing(true);
}

/*************************************************************************/

void _window_positions::action_move_points_slot()
{
  Action_selected=int(_window_positions_ns::_action_type::ACTION_MOVE_POINTS);

  for (unsigned int i=0;i<int(_window_positions_ns::_action_type::ACTION_LAST);i++){
    Vec_actions[i]->setIcon(Icons[i][0]);
  }

  Vec_actions[Action_selected]->setIcon(Icons[Action_selected][1]);

  //

  Action_type=_window_positions_ns::_action_type::ACTION_MOVE_POINTS;
  Main_gl_widget->editing(true);
}

/*************************************************************************/

void _window_positions::parameters_changed()
{
  if (Loaded_image==true){
    std::static_pointer_cast<_layer_positions_positions_ui>(Vec_layers[1])->parameters(Window_main->display_font_size(), Window_main->display_out_circle_size(), Window_main->display_font_color(), Window_main->display_out_circle_color(), Window_main->display_in_circle_color(), Window_main->display_selection_out_circle_color(), Window_main->display_selection_in_circle_color());
    std::static_pointer_cast<_layer_positions_positions_ui>(Vec_layers[1])->update();

    Main_gl_widget->update_texture(1);

    Main_gl_widget->update();
  }
}

/*************************************************************************/
// Options display

void _window_positions::options_parameters_display(int Font_size_display1, int Out_circle_size_display1, QColor Font_color_display1, QColor Out_circle_color_display1, QColor In_circle_color_display1, QColor Selection_out_circle_color_display1, QColor Selection_in_circle_color_display1,bool Copy_display_values1)
{
  Window_main->display_font_size(Font_size_display1);
  Window_main->display_out_circle_size(Out_circle_size_display1);
  Window_main->display_font_color(Font_color_display1);
  Window_main->display_out_circle_color(Out_circle_color_display1);
  Window_main->display_in_circle_color(In_circle_color_display1);
  Window_main->display_selection_out_circle_color(Selection_out_circle_color_display1);
  Window_main->display_selection_in_circle_color(Selection_in_circle_color_display1);
  Copy_display_values=Copy_display_values1;

  if (Copy_display_values==true){
    Window_main->print_font_size(Font_size_display1);
    Window_main->print_out_circle_size(Out_circle_size_display1);
    Window_main->print_font_color(Font_color_display1);
    Window_main->print_out_circle_color(Out_circle_color_display1);
    Window_main->print_in_circle_color(In_circle_color_display1);
  }

  Window_main->parameters_changed();
}

/*************************************************************************/
// Options print

void _window_positions::options_parameters_print(int Font_size_print1, int Out_circle_size_print1, QColor Font_color_print1, QColor Out_circle_color_print1, QColor In_circle_color_print1)
{
  Window_main->print_font_size(Font_size_print1);
  Window_main->print_out_circle_size(Out_circle_size_print1);
  Window_main->print_font_color(Font_color_print1);
  Window_main->print_out_circle_color(Out_circle_color_print1);
  Window_main->print_in_circle_color(In_circle_color_print1);

  save_settings();
}

/*************************************************************************/

int _window_positions::image_width()
{
  if (Loaded_image) return Main_image->cols;
  else return 0;
}

/*************************************************************************/

int _window_positions::image_height()
{
  if (Loaded_image) return Main_image->rows;
  else return 0;
}

/*************************************************************************/

void _window_positions::selected_position(int Position1,bool Position_active1)
{
  // update and draw
  std::static_pointer_cast<_layer_positions_positions_ui>(Vec_layers[1])->selected_position(Position1,Position_active1);
  std::static_pointer_cast<_layer_positions_positions_ui>(Vec_layers[1])->update();

  Main_gl_widget->update_texture(1);

  Main_gl_widget->update();
}

