/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#include "window.h"

/*************************************************************************/

std::vector<std::string> split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}

/*************************************************************************/

_window::_window()
{
  // the dimensions of the main window
  QRect Screen_size = QApplication::primaryScreen()->geometry();
  Screen_width=Screen_size.width();
  Screen_height=Screen_size.height();

  // the default font size
  QFont Font=QApplication::font();
  UI_font_size=Font.pointSize();

  // structure
  // Splitter --> Splitter_edit ----> Color + Splitter_view + Tab
  //          |-> Splitter_ge                      |-> GL + GL_3D

  Splitter_view=new _splitter(Qt::Vertical);
//  Splitter_view->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

  connect(Splitter_view,SIGNAL(splitterMoved(int,int)),this,SLOT(splitter_moved_slot(int,int)));

  Splitter_view_2D_3D=new _splitter(Qt::Horizontal);

  Splitter_edit=new _splitter(Qt::Horizontal);
  Splitter_edit->setContentsMargins(0, 0, 0, 0);

  Splitter=new _splitter(Qt::Horizontal);

//  QSizePolicy Q(QSizePolicy::Expanding,QSizePolicy::Expanding);

  initialize_palettes_data();

  //

  GL_widget = new _gl_widget(this);

  Color_bar_widget=new _w_color_bar(this);

  Tab_widget=new _w_tab(this);

  Splitter_view_2D_3D->addWidget(GL_widget);

  // add the widgets
//    Splitter_view->addWidget(GL_widget);
  Splitter_view->addWidget(Splitter_view_2D_3D);

  Splitter_edit->addWidget(Color_bar_widget);
  Splitter_edit->addWidget(Splitter_view);
  Splitter_edit->addWidget(Tab_widget);

  connect(static_cast<_splitter_handle *>(Splitter_edit->handle(1)),SIGNAL(double_click()),this,SLOT(left_handle_slot()));
  connect(static_cast<_splitter_handle *>(Splitter_edit->handle(2)),SIGNAL(double_click()),this,SLOT(right_handle_slot()));

  Splitter->addWidget(Splitter_edit);

  setCentralWidget(Splitter);

  // menu
  Load_project = new QAction(QIcon(":/common/icons/fileopen.png"), tr("Load project data"), this);
  Load_project->setShortcuts(QKeySequence::Open);
  Load_project->setToolTip(tr("Load project"));
  connect(Load_project, SIGNAL(triggered()), this, SLOT(load_project_data_slot()));

  Close_project = new QAction(tr("Close project"), this);
  Close_project->setShortcuts(QKeySequence::Close);
  Close_project->setToolTip(tr("Close project"));
  Close_project->setEnabled(false);
  connect(Close_project, SIGNAL(triggered()), this, SLOT(close_project_slot()));

  // for single layer
  Save_single_layer = new QAction(tr("Without color bar"), this);
//  Save_single_map->setToolTip(tr("Load al the elements of a folder"));
  Save_single_layer->setEnabled(false);
  connect(Save_single_layer, SIGNAL(triggered()), this, SLOT(save_single_layer_slot()));

  Save_single_layer_with_color_bar = new QAction(tr("With color bar"), this);
//  Save_single_map_with_color_bar->setToolTip(tr("Load al the elements of a folder"));
  Save_single_layer_with_color_bar->setEnabled(false);
  connect(Save_single_layer_with_color_bar, SIGNAL(triggered()), this, SLOT(save_single_layer_with_color_bar_slot()));

  // for all layer
  Save_all_layers = new QAction(tr("Without color bar"), this);
  //  Save_single_map->setToolTip(tr("Load al the elements of a folder"));
  Save_all_layers->setEnabled(false);
  connect(Save_all_layers, SIGNAL(triggered()), this, SLOT(save_all_layers_slot()));

  Save_all_layers_with_color_bar = new QAction(tr("With color bar"), this);
  //  Save_single_map_with_color_bar->setToolTip(tr("Load al the elements of a folder"));
  Save_all_layers_with_color_bar->setEnabled(false);
  connect(Save_all_layers_with_color_bar, SIGNAL(triggered()), this, SLOT(save_all_layers_with_color_bar_slot()));

  Save_composed_image = new QAction(QIcon(":/common/icons/filesave.png"), tr("Save composed image"), this);
  Save_composed_image->setToolTip(tr("Save composed image"));
  Save_composed_image->setEnabled(false);
  connect(Save_composed_image, SIGNAL(triggered()), this, SLOT(save_composed_image_slot()));

  Options = new QAction(tr("&Options"), this);
  Options->setToolTip(tr("Set the options"));
  Options->setEnabled(false);
  connect(Options, SIGNAL(triggered()), this, SLOT(options_slot()));

  QAction *Exit = new QAction(QIcon(":/common/icons/exit.png"), tr("&Exit..."), this);
  Exit->setShortcut(tr("Ctrl+Q"));
  Exit->setToolTip(tr("Exit the application"));
  connect(Exit, SIGNAL(triggered()), this, SLOT(close()));

  // adjustment

  // show positions
  View_show_positions = new QAction(tr("&Show positions"), this);
  View_show_positions->setCheckable(true);
  View_show_positions->setChecked(false);
  connect(View_show_positions, SIGNAL(triggered()), this, SLOT(show_positions_slot()));

  // show triangles normal
  View_show_triangulation_normal = new QAction(tr("Show triangulation normal"), this);
  View_show_triangulation_normal->setCheckable(true);
  View_show_triangulation_normal->setChecked(false);
  connect(View_show_triangulation_normal, SIGNAL(triggered()), this, SLOT(show_triangulation_normal_slot()));

  // show triangles with corners
  View_show_triangulation_with_corners = new QAction(tr("Show triangulation with corners"), this);
  View_show_triangulation_with_corners->setCheckable(true);
  View_show_triangulation_with_corners->setChecked(false);
  connect(View_show_triangulation_with_corners, SIGNAL(triggered()), this, SLOT(show_triangulation_with_corners_slot()));

  // actions for file menu
  QAction *Help_info = new QAction(tr("&Info"), this);
  connect(Help_info, SIGNAL(triggered()), this, SLOT(info_slot()));

  // menus
  QMenu *File_menu=menuBar()->addMenu(tr("&File"));
  File_menu->addAction(Load_project);
//  File_menu->addAction(Reload_project);
  File_menu->addAction(Close_project);
  File_menu->addSeparator();

  Submenu_save_single_layer=File_menu->addMenu(QIcon(":/common/icons/filesave.png"),"Save selected layer");
  Submenu_save_single_layer->addAction(Save_single_layer);
  Submenu_save_single_layer->addAction(Save_single_layer_with_color_bar);
  Submenu_save_single_layer->setEnabled(false);

  Submenu_save_all_layers=File_menu->addMenu(QIcon(":/common/icons/filesave.png"),"Save all layers");
  Submenu_save_all_layers->addAction(Save_all_layers);
  Submenu_save_all_layers->addAction(Save_all_layers_with_color_bar);
  Submenu_save_all_layers->setEnabled(false);

  File_menu->addSeparator();
  File_menu->addAction(Save_composed_image);
  File_menu->addSeparator();
  File_menu->addAction(Options);
  File_menu->addSeparator();
  File_menu->addAction(Exit);
  File_menu->setAttribute(Qt::WA_AlwaysShowToolTips);

  Menu_view=menuBar()->addMenu(tr("&View"));
  Menu_view->addAction(View_show_positions);

  Submenu_add_show_triangulation=Menu_view->addMenu("Show triangulation");
//  Submenu_add_show_triangulation->setEnabled(false);
  Submenu_add_show_triangulation->addAction(View_show_triangulation_normal);
  Submenu_add_show_triangulation->addAction(View_show_triangulation_with_corners);

  Menu_view->setEnabled(false);

  QMenu *Menu_help=menuBar()->addMenu(tr("&Help"));
  Menu_help->addAction(Help_info);

  Menu_help->setAttribute(Qt::WA_AlwaysShowToolTips);

  setWindowTitle(_window_ns::Program_name);

  resize(Screen_width/2,Screen_height/2);
}

/*************************************************************************/

void _window::ui_set_font_size(int Size)
{
  UI_font_size=Size;

  QFont Font=QApplication::font();
  Font.setPointSize(Size);
  QApplication::setFont(Font);

  // change the width of the color bar
  Color_bar_widget->adjust_width(Project_data.Max_value);

  update_color_bar();
}

/*************************************************************************/

void _window::read_settings()
{
//  QSettings settings("./settings_"+_window_ns::Program_name.toLower()+".ini",QSettings::IniFormat);
  QSettings settings(Project_dir+"/settings.ini",QSettings::IniFormat);

  QStringList Allq=settings.allKeys();

  settings.beginGroup("XMapsLab");
    settings.beginGroup("MainWindow");
      Window_size=settings.value("size", QSize(_window_ns::WINDOW_WIDTH_DEFAULT,_window_ns::WINDOW_HEIGHT_DEFAULT)).toSize();
      Window_position=settings.value("pos", QPoint(_window_ns::WINDOW_X_POS_DEFAULT,_window_ns::WINDOW_Y_POS_DEFAULT)).toPoint();
    settings.endGroup();

    settings.beginGroup("Layer");
      Data_type_print=_palette_data_ns::_data_type_print(settings.value("DataTypePrint",int(_window_ns::DATA_TYPE_PRINT_DEFAULT)).toInt());
    settings.endGroup();

    settings.beginGroup("Maps");
      Interpolation_type=_layer_map_ns::_map_interpolation_methods(settings.value("MapInterpolationType",_window_ns::MAP_INTERPOLATION_TYPE_DEFAULT).toInt());
      Color_model=_common_ns::_color_model(settings.value("ColorModel",_window_ns::COLOR_MODEL_DEFAULT).toInt());
      Use_colors[0]=settings.value("UseColor1",_window_ns::USE_COLOR1_DEFAULT).toBool();
      Use_colors[1]=settings.value("UseColor2",_window_ns::USE_COLOR2_DEFAULT).toBool();
      Use_colors[2]=settings.value("UseColor3",_window_ns::USE_COLOR3_DEFAULT).toBool();
      Use_positions[0]=settings.value("UsePosition1",_window_ns::USE_POSITION1_DEFAULT).toBool();
      Use_positions[1]=settings.value("UsePosition2",_window_ns::USE_POSITION2_DEFAULT).toBool();
      Distance_normalization=settings.value("Normalization",_window_ns::NORMALIZATION_DEFAULT).toBool();
      Position_normalization_type=_layer_map_distance_ns::_position_normalization_type(settings.value("PositionNormalizationType",_window_ns::POSITION_NORMALIZATION_TYPE_DEFAULT).toInt());
      Probe=settings.value("Probe",_window_ns::PROBE_DEFAULT).toInt();
      Palette=settings.value("Palette",_window_ns::PALETTE_DEFAULT).toInt();
      RBF_function=_new_rbf_interpolation_2d_ns::_function_type(settings.value("RBFFunction",int(_new_rbf_interpolation_2d_ns::FUNCTION_TYPE_DEFAULT)).toInt());
      Triangulation_add_corners=settings.value("TriangulationAddCorners",_window_ns::TRIANGULATION_ADD_CORNERS_DEFAULT).toBool();
    settings.endGroup();

    settings.beginGroup("Printing");
      Positions_print_font_factor=settings.value("FontScaleFactor",_w_options_ns::POSITIONS_PRINT_FONT_FACTOR_DEFAULT).toFloat();
    settings.endGroup();

    settings.beginGroup("Palette");
      Color_for_zero_value=_color_map_ns::_color_for_zero_value(settings.value("ColorZeroValue",int(_window_ns::COLOR_FOR_ZERO_VALUE_DEFAULT)).toInt());
    settings.endGroup();

  settings.endGroup();

  settings.beginGroup("DisplayParameters");
    Positions_display_font_size=settings.value("DisplayFontSize",_w_options_ns::POSITIONS_DISPLAY_FONT_SIZE_DEFAULT).toInt();
    Positions_display_out_circle_size=settings.value("DisplayOutCircleSize",_w_options_ns::POSITIONS_DISPLAY_OUT_CIRCLE_SIZE_DEFAULT).toInt();
    Positions_display_font_color=settings.value("DisplayFontColor",_w_options_ns::POSITIONS_DISPLAY_FONT_COLOR_DEFAULT).value<QColor>();
    Positions_display_out_circle_color=settings.value("DisplayOutCircleColor",_w_options_ns::POSITIONS_DISPLAY_OUT_CIRCLE_COLOR_DEFAULT).value<QColor>();
    Positions_display_in_circle_color=settings.value("DisplayInCircleColor",_w_options_ns::POSITIONS_DISPLAY_IN_CIRCLE_COLOR_DEFAULT).value<QColor>();
    Positions_display_selection_out_circle_color=settings.value("DisplaySelectionOutCircleColor",_w_options_ns::POSITIONS_DISPLAY_SELECTION_OUT_CIRCLE_COLOR_DEFAULT).value<QColor>();
    Positions_display_selection_in_circle_color=settings.value("DisplaySelectionInCircleColor",_w_options_ns::POSITIONS_DISPLAY_SELECTION_IN_CIRCLE_COLOR_DEFAULT).value<QColor>();
  settings.endGroup();

  settings.beginGroup("General");
    UI_font_size=settings.value("UIFontSize",_common_ns::UI_FONT_SIZE_DEFAULT).toInt();
  settings.endGroup();
}

/*************************************************************************/

void _window::save_settings()
{
//  QSettings settings("./settings_"+_window_ns::Program_name.toLower()+".ini",QSettings::IniFormat);
  QSettings settings(Project_dir+"/settings.ini",QSettings::IniFormat);

  settings.beginGroup("XMapsLab");
    settings.beginGroup("MainWindow");
      settings.setValue("size", size());
      settings.setValue("pos", pos());
    settings.endGroup();

    settings.beginGroup("Layer");
      settings.setValue("DataTypePrint",int(Data_type_print));
    settings.endGroup();

    settings.beginGroup("Maps");
      settings.setValue("MapInterpolationType",int(Interpolation_type));
      settings.setValue("ColorModel", int(Color_model));
      settings.setValue("UseColor1", bool(Use_colors[0]));
      settings.setValue("UseColor2", bool(Use_colors[1]));
      settings.setValue("UseColor3", bool(Use_colors[2]));
      settings.setValue("UsePosition1", bool(Use_positions[0]));
      settings.setValue("UsePosition2", bool(Use_positions[1]));
      settings.setValue("Normalization", Distance_normalization);
      settings.setValue("PositionNormalizationType", int(Position_normalization_type));
      settings.setValue("Probe", Probe);
      settings.setValue("Palette", Palette);
      settings.setValue("TriangulationAddCorners",Triangulation_add_corners);
      settings.setValue("RBFFunction",int(RBF_function));
    settings.endGroup();

    settings.beginGroup("Printing");
      settings.setValue("FontScaleFactor",Positions_print_font_factor);
    settings.endGroup();

    settings.beginGroup("Palette");
      settings.setValue("ColorZeroValue",int(Color_for_zero_value));
    settings.endGroup();

  settings.endGroup();

  settings.beginGroup("DisplayParameters");
    settings.setValue("DisplayFontSize",Positions_display_font_size);
    settings.setValue("DisplayOutCircleSize",Positions_display_out_circle_size);
    settings.setValue("DisplayFontColor",Positions_display_font_color);
    settings.setValue("DisplayOutCircleColor",Positions_display_out_circle_color);
    settings.setValue("DisplayInCircleColor",Positions_display_in_circle_color);
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

void _window::initialize_palettes_data()
{
  for (unsigned int i=0;i<_palette_data_ns::Vec_palette_data_aux.size();i++){
    Vec_palette_data.push_back(_palette_data(_palette_data_ns::Vec_palette_data_aux[i].Name,_palette_data_ns::Vec_palette_data_aux[i].Data_type,_palette_data_ns::Vec_palette_data_aux[i].Color_type,_palette_data_ns::Vec_palette_data_aux[i].Num_steps,compute_color(""),color_for_zero_value()));
  }
}

/*************************************************************************/
// Load the images

void _window::load_images()
{
  QString File_name;

  QDir Directory_images(Project_dir+"/images");
  std::string Dir_images=Directory_images.absolutePath().toStdString();

  QStringList Files_images = Directory_images.entryList(QStringList() << "*.png" << "*.jpg", QDir::Files);

  // there are more than one image, select one
  if (Files_images.size()>0){
    if (Files_images.size()==1){
      File_name=Files_images[0];
    }
    else{
      QFileDialog Dialog(this,tr("Select the image"),Project_dir+"/images");
      Dialog.setFileMode(QFileDialog::ExistingFile);
      Dialog.setNameFilter(tr("Images (*.png *.jpg)"));
      if (Dialog.exec()){
        QStringList List=Dialog.selectedFiles();
        File_name=List[0];
      }
    }

    QFileInfo File_info(File_name);
    std::string Short_name=File_info.baseName().toStdString();
    std::string Long_name=Dir_images+"/"+File_info.fileName().toStdString();

    _image_IO Image_io;
    std::shared_ptr<cv::Mat> Image=std::make_shared<cv::Mat>();

    // a fast access
    Original_image=Image;

    // BGR
    Image_io.read_image(Long_name,*Image.get());

    int Width_aux=Image->cols;
    int Height_aux=Image->rows;

    adjust_image_sizes(Width_aux,Height_aux);
    if (Width_aux!=Image->cols || Height_aux!=Image->rows){
      cv::resize(*Image.get(),*Image.get(),cv::Size(Width_aux,Height_aux),0,0,cv::INTER_CUBIC);
    }

    // flip the original image to adapt it to OpenGL
    cv::flip(*Image.get(),*Image.get(),0);
    // convert to BGRA. Add the alpha channel in case the original image has not it
    cv::cvtColor(*Image.get(),*Image.get(),cv::COLOR_BGR2BGRA,4);

    if (Loaded_image==false){
      Loaded_image=true;

//        Layers.clear();
//        Textures.clear();
      Map_name_to_layer.clear();
      Vec_order_of_layers_by_name.clear();
      Map_name_to_element.clear();

      Initial_image=File_info.baseName().toStdString();
      Initial_image=Initial_image+"_"+std::to_string(Vec_order_of_layers_by_name.size());
      Initial_width=Image->cols;
      Initial_height=Image->rows;
    }

    add_layer_image(Short_name,Image);

    //
    Num_images++;

  }
  else{
    Files_images = Directory_images.entryList(QStringList() << "*.jpg",QDir::Files);

    if (Files_images.size()>0){
      foreach(QString File_name, Files_images) {
        QFileInfo File_info(File_name);

        QImage Image;
        QString File_name1=Directory_images.absolutePath()+"/"+File_name;
        Image.load(File_name1);

        QString New_file_name=Directory_images.absolutePath()+"/"+File_info.baseName()+".png";
        Image.save(New_file_name,"PNG");
      }

      load_images();
    }
    else{
      QMessageBox::critical(this,tr("Error"),tr("There is not a 'vis' file in images folder"));
      QApplication::quit();
      exit(-1);
    }
  }
}

/*************************************************************************/

 void _window::load_compounds_combination()
 {
   _data_io::load_compounds_combination_pdb(this,Vec_compounds_from_elements_pdb);
 }

/*************************************************************************/
// Normalizes the data

void _window::xrf_process_data(_pigment_data_ns::_pigment_data &Element_data)
{
  float Max_aux=*max_element(Element_data.Vec_values.begin(),Element_data.Vec_values.end());

  Element_data.Max_value=Max_aux;

  float Divisor=Max_aux;
  if (Max_aux==0) Divisor=1;

  // adjust the max value
  if (Project_data.XRF_data_adjustment!=_data_xrf_ns::_xrf_data_adjustment::XRF_DATA_ADJUSTMENT_NONE){
    // adjust
    if (Project_data.XRF_data_adjustment==_data_xrf_ns::_xrf_data_adjustment::XRF_DATA_ADJUSTMENT_ATOMIC_NUMBER){
      Element_data.Max_value_adjusted=Element_data.Max_value/Element_data.Atomic_number;
    }
  }
  else{
    Element_data.Max_value_adjusted=Element_data.Max_value;
  }

  for (unsigned int i=0;i<Element_data.Vec_values.size();i++){
    Element_data.Vec_values[i]=Element_data.Vec_values[i]/Divisor;
  }
}

/*************************************************************************/

void _window::process_xrf_map_data()
{
  for (auto &Element : Map_name_to_element){
    float Atomic_number=-1.0f;

    std::string Element_name=Element.first;

    for (auto &Data: _window_ns::Vec_atomic_data){
      if (Data.Short_name==Element_name){
        Atomic_number=Data.Atomic_number;
        break;
      }
    }

    if (Atomic_number==-1){
      QMessageBox::critical(this, tr("Error"),"The element "+QString::fromStdString(Element.first)+" does not exist");
      QApplication::quit();
      exit(-1);
    }

    Element.second.Atomic_number=Atomic_number;

    // adjust the values of the samples dividing by the atomic number
    xrf_process_data(Element.second);

    // insert in the map pair (name of the element or pigment data)
    Map_name_to_element.insert(std::pair<std::string,_pigment_data_ns::_pigment_data>(Element_name,_pigment_data_ns::_pigment_data(Element.second)));

    // add the element
    Tab_widget->add_element(Element_name);

    // save the name
    Vec_element_names.push_back(Element_name);
  }

  // add the information of compounds combination
  for (unsigned int i=0;i<Vec_compounds_from_elements_pdb.size();i++){
    Tab_widget->add_compound_combination(Vec_compounds_from_elements_pdb[i].Name);
  }
}

/*************************************************************************/
// Load the the data in MapLab format

void _window::load_data_csv_format(bool &XRF_data_loaded, bool &XRD_data_loaded)
{
  std::string Material;
  std::vector<std::vector<float>> Values;
  std::string Error;
  std::string File_name;

  // maybe that the data is loaded for for firts time or reloaded
  // if it is reloaded, I have to save the previous state for positions
  std::vector<bool> Vec_active_positions_previous_state=Vec_active_positions;

  // first read the elements
  _data_io::xrf_load_pdb(this,Vec_xrf_pdb_data,Vec_xrf_pdb_names);

  // the names of the PDB elements and compounds are not necessary
  _data_io::load_project_data_csv(this,Project_dir,Project_data,Vec_xrf_pdb_names,Vec_xrd_pdb_names);

  // Num of valid positions is equal to the number of read positions
  Num_active_positions=Project_data.Vec_coordinate_x_original.size();

  // convert to pixels
  Project_data.adjust_coordinates(Initial_width,Initial_height);

  // initialize the vector of valid positions
  Vec_active_positions.resize(Project_data.Vec_coordinate_x.size(),true);

  // if there was a previous state, now is used
  if (Vec_active_positions_previous_state.size()!=0){
    for (unsigned int i=0;i<Vec_active_positions.size();i++){
      if (i<Vec_active_positions_previous_state.size()){
        Vec_active_positions[i]=Vec_active_positions_previous_state[i];
      }
    }
  }

  // convert the XRF data
  int Num_positions=Project_data.Vec_coordinate_x_original.size();

  if (Project_data.Vec_xrf_interpreted_data.size()>0){
    XRF_data_loaded=true;
    std::string Element_name;

    for (unsigned int i=0;i<Project_data.Vec_xrf_interpreted_data.size();i++){
      Element_name=Project_data.Vec_xrf_interpreted_data[i].Name;

      Map_name_to_element[Element_name].Vec_values=std::vector<float>(Num_positions,0);

      for (int j=0;j<Num_positions;j++){
         Map_name_to_element[Element_name].Vec_values[j]=Project_data.Vec_xrf_interpreted_data[i].Vec_values[j];
      }
    }

    process_xrf_map_data();
  }

  // compute the image with the positions of the samples
  add_layer_positions_image();

  // compute mean distance between positions
//  compute_mean_distance_between_positions();
  compute_mean_distance_between_neighbors_positions();

  // the max epsilon are 5 mean_distances
  int Value=255;
  Tab_widget->set_rbf_epsilon(Value);

  rbf_radius(Mean_distance_between_neighbors_positions/float(max_dimension()));
}

/*************************************************************************/
// Load the the data in XLSX format

/*************************************************************************/

void _window::add_layer_positions_image()
{
  std::vector<_delaunay_triangulator_ns::_point> Points;
  _delaunay_triangulator_ns::_point Point;

  unsigned int Pos;
  for (Pos=0;Pos<Project_data.Vec_coordinate_x.size();Pos++){
    if (Vec_active_positions[Pos]==true){
      Point.x=Project_data.Vec_coordinate_x[Pos];
      Point.y=Project_data.Vec_coordinate_y[Pos];
      Point.Position=Pos;
      Points.push_back(Point);
    }
  }

  _delaunay_triangulator_ns::_delaunay_triangulator Triangulator;

  Triangles=Triangulator.triangulate(Points);

  // create the vector for the coordinates with the corners
  std::vector<float> Vec_coordinate_x_corners=Project_data.Vec_coordinate_x;
  std::vector<float> Vec_coordinate_y_corners=Project_data.Vec_coordinate_y;

  // add the triangulation with corners. Add the four corners to Points
  Point.x=0;
  Point.y=0;
  Point.Position=Pos;
  Points.push_back(Point);
  Vec_coordinate_x_corners.push_back(0);
  Vec_coordinate_y_corners.push_back(0);
  Pos++;

  Point.x=Project_data.Width-1;
  Point.y=0;
  Point.Position=Pos;
  Points.push_back(Point);
  Vec_coordinate_x_corners.push_back(Project_data.Width-1);
  Vec_coordinate_y_corners.push_back(0);
  Pos++;

  Point.x=0;
  Point.y=Project_data.Height-1;
  Point.Position=Pos;
  Points.push_back(Point);
  Vec_coordinate_x_corners.push_back(0);
  Vec_coordinate_y_corners.push_back(Project_data.Height-1);
  Pos++;

  Point.x=Project_data.Width-1;
  Point.y=Project_data.Height-1;
  Point.Position=Pos;
  Points.push_back(Point);
  Vec_coordinate_x_corners.push_back(Project_data.Width-1);
  Vec_coordinate_y_corners.push_back(Project_data.Height-1);
  Pos++;

   _delaunay_triangulator_ns::_delaunay_triangulator Triangulator1;

  Triangles_with_corners=Triangulator1.triangulate(Points);

  // add
//  cout << "Num_triangles en window=" << Triangles.size() << endl;

  // check if the layer exists
  std::shared_ptr<_layer_positions_ui> Layer_positions=nullptr;
  if (Map_name_to_layer.find("Positions")==Map_name_to_layer.end()){
    Layer_positions=std::make_shared<_layer_positions_ui>(this,"Positions");
  }
  else{
    Layer_positions=std::static_pointer_cast<_layer_positions_ui>(Map_name_to_layer["Positions"].Layer);
  }

  // the data of the element. ALWAYS THE FIRST ONE
  Layer_positions->add_valid_coordinates(Vec_active_positions);
  Layer_positions->add_coordinates(Project_data.Vec_coordinate_x,Project_data.Vec_coordinate_y);
  Layer_positions->add_coordinates_with_corners(Vec_coordinate_x_corners,Vec_coordinate_y_corners);

  Layer_positions->cs_origin(Project_data.CS_origin);
  Layer_positions->size(Project_data.Width,Project_data.Height);
  Layer_positions->triangles(Triangles);
  Layer_positions->triangles_with_corners(Triangles_with_corners);

  Layer_positions->parameters(Positions_display_font_size,Positions_display_out_circle_size, Positions_display_font_color, Positions_display_out_circle_color, Positions_display_in_circle_color);

  Layer_positions->update();
  Map_name_to_layer["Positions"].Layer=Layer_positions;
  Map_name_to_layer["Positions"].Texture=GL_widget->set_texture(Layer_positions->image());
}

/*************************************************************************/

void _window::load_project()
{
  int Pos=Project_dir.lastIndexOf('/');
  Project_name=Project_dir.right(Project_dir.size()-Pos-1);

  if (First_load==true){
    read_settings();

    // initialize the widgets with correct data
    Color_bar_widget->initialize();
    Tab_widget->initialize();

    //
    QFont Font=QApplication::font();
    Font.setPointSize(UI_font_size);
    QApplication::setFont(Font);
  }

  // load the images in the folder
  load_images();

  // load the compounds_combination PDB
  load_compounds_combination();

  if (Mode_normal==false){
  }
  else{
    QFileInfo Check_file(Project_dir+"/"+QString::fromStdString(_common_window_ns::FILE_PROJECT_DATA));
    if (Check_file.exists()==true){
      load_data_csv_format(XRF_data_loaded,XRD_data_loaded);
    }
    else{
      QMessageBox::critical(this, tr("Error"),tr("There is not 'data.csv' file"));
      QApplication::quit();
      exit(-1);
    }
  }

  // update the positions
  Tab_widget->add_active_positions(Vec_active_positions);

  if (XRF_data_loaded==true || XRD_data_loaded==true){
    // enable tabs
    Tab_widget->setTabEnabled(Tab_widget->pos_of_tab(_w_tab_ns::_tabs::POSITIONS_TAB),true);
    Tab_widget->setTabEnabled(Tab_widget->pos_of_tab(_w_tab_ns::_tabs::LAYERS_TAB),true);

    if (XRF_data_loaded==true){
      Tab_widget->setTabEnabled(int(_w_tab_ns::_tabs::ELEMENTS_TAB),true);
      Tab_widget->setTabEnabled(Tab_widget->pos_of_tab(_w_tab_ns::_tabs::COMPOUNDS_FROM_XRF_TAB),true);
    }
    else{
      Tab_widget->setTabEnabled(Tab_widget->pos_of_tab(_w_tab_ns::_tabs::ELEMENTS_TAB),false);
      Tab_widget->setTabEnabled(Tab_widget->pos_of_tab(_w_tab_ns::_tabs::COMPOUNDS_FROM_XRF_TAB),false);
    }

    if (XRD_data_loaded==true){
      Tab_widget->setTabEnabled(Tab_widget->pos_of_tab(_w_tab_ns::_tabs::COMPOUNDS_XRD_TAB),true);
    }
    else{
      Tab_widget->setTabEnabled(Tab_widget->pos_of_tab(_w_tab_ns::_tabs::COMPOUNDS_XRD_TAB),false);
    }

    // change widgets
    Tab_widget->changed_interpolation_type_slot(int(Interpolation_type));

    // change states
    Tab_widget->elements_change_buttons_state(true);

    // show the loaded xrf files
    Selected_tab=_w_tab_ns::_tabs::POSITIONS_TAB;
    Tab_widget->setCurrentIndex(int(Selected_tab));

    Menu_view->setEnabled(true);

    GL_widget->setEnabled(true);
    Load_project->setEnabled(false);
//    Reload_project->setEnabled(true);
    Close_project->setEnabled(true);

    Options->setEnabled(true);

    // change the size of the color bar depending on the max value to show
    Color_bar_widget->adjust_width(Project_data.Max_value);

  }
  else{
    QMessageBox::critical(this, tr("Error"),"There is not XRF nor XRD data. The project is empty");
    QApplication::quit();
    exit(-1);
  }
}

/*************************************************************************/
// load the data

void _window::load_project_data_slot()
{
  _w_directory Dialog(this,"projects",&Project_name);

  if (Dialog.exec()==QDialog::Accepted && Project_name!=""){
    QDir Dir(Project_name);
    Project_dir=Dir.absolutePath();

    // save project name for other programs
//    std::ofstream File;
//    File.open(_window_ns::Project_name.toStdString(),ios::out);
//    File << Project_name.toStdString() << endl;
//    File.close();

    // check what model to use
    if (First_load==true){
      QFileInfo Check_file(QString::fromStdString(_common_window_ns::FILE_MODE));
      // check if file exists and if yes: Is it really a file and no directory?
      if (Check_file.exists() && Check_file.isFile()) Mode_normal=false;
      else Mode_normal=true;
    }

    load_project();

    if (First_load==true){
      resize(Window_size);
      move(Window_position);
    }

    First_load=false;
  }
}

/*************************************************************************/
// load the data

void _window::close_project_slot()
{
  // clear ???
//  Map_name_to_layer.clear();

  // remove all the layers
  remove_all_layers();

  // remove all the elements
  Tab_widget->remove_all_elements();
  Tab_widget->remove_all_images();
  Tab_widget->remove_all_xrf_files();

  Map_name_to_element.clear();
  Vec_element_names.clear();
  Map_name_to_layer.clear();
  Map_normalized_images.clear();
  Vec_element_names.clear();
  Map_name_of_layer_to_name_of_element.clear();
  Vec_active_positions.clear();
  Vec_xrf_data.clear();
//  Vec_data_pigments.clear();

  ZOI=_vertex2i(0,0);
  Scaling={1,1};

  GL_widget->setEnabled(false);

  // change states
  Tab_widget->elements_change_buttons_state(false);

  // dienable tabs
  Tab_widget->setTabEnabled(Tab_widget->pos_of_tab(_w_tab_ns::_tabs::LAYERS_TAB),false);
  Tab_widget->setTabEnabled(Tab_widget->pos_of_tab(_w_tab_ns::_tabs::ELEMENTS_TAB),false);
  Tab_widget->setTabEnabled(Tab_widget->pos_of_tab(_w_tab_ns::_tabs::POSITIONS_TAB),false);
//  Tab_widget->setTabEnabled(int(_w_tab_ns::_tabs::TAB_XRD_FILES),false);

//  Tab_widget->setTabEnabled(int(_w_tab_ns::_tabs::TAB_PALETTES),false);

  Selected_tab=_w_tab_ns::_tabs::LAYERS_TAB;
  Tab_widget->setCurrentIndex(Tab_widget->pos_of_tab(_w_tab_ns::_tabs::LAYERS_TAB));

  Load_project->setEnabled(true);
//  Reload_project->setEnabled(false);
  Close_project->setEnabled(false);
}

/*************************************************************************/

void _window::draw_positions(QPainter &Painter,float Widht1,float Height1)
{
  std::static_pointer_cast<_layer_positions_ui>(Map_name_to_layer["Positions"].Layer)->draw(Painter,Widht1,Height1);
}

/*************************************************************************/

void _window::save_single_layer(std::string Name)
{
  // The image of the selected layer
  cv::Mat Image_opencv=Map_name_to_layer[Name].Layer->image()->clone();
  cv::flip(Image_opencv,Image_opencv,0);

  float Width1=float(Image_opencv.cols-1);
  float Height1=float(Image_opencv.rows-1);

  // change form OpenCV to Qt format
  QImage Image_qt(Image_opencv.data,Image_opencv.cols,Image_opencv.rows,static_cast<int>(Image_opencv.step),QImage::Format_ARGB32);
  //Image_qt.rgbSwapped();

  //
  QPainter Painter(&Image_qt);
  // Draw the image of the layer
  Painter.drawImage(0,0,Image_qt);

  // Draw the positions
  if (Show_positions==true){
    draw_positions(Painter,Width1,Height1);
  }
  Painter.end();

  QString File_name(Project_dir+"/xrf/maps/"+QString::fromStdString(Name));
  if (Show_positions==true) File_name=File_name+"_positions";
  File_name=File_name+"_single.png";

  Image_qt.save(File_name,"PNG");
}

/*************************************************************************/

void _window::save_single_layer_slot()
{
  save_single_layer(Vec_order_of_layers_by_name[Selected_layer]);

  QMessageBox::information(this,tr("Information"),tr("The image of the selected element/pigment has been correctly saved"));
}

/*************************************************************************/

void _window::save_all_layers_slot()
{
  int Num_total_layers=int(Vec_order_of_layers_by_name.size());
  int Num_element_layers=0;

  for (int i=0;i<Num_total_layers;i++){
    std::string Name=Vec_order_of_layers_by_name[i];
    if (Map_name_to_layer[Name].Layer->layer_type()>=_layer_ns::_layer_type::LAYER_TYPE_MAP_DISTANCE || Map_name_to_layer[Name].Layer->layer_type()>=_layer_ns::_layer_type::LAYER_TYPE_MAP_TRIANGULATION) Num_element_layers++;
  }

  int Count_progress=0;
  QProgressDialog Progress("Working...", "Abort",0,Num_element_layers,this);
  Progress.setWindowModality(Qt::WindowModal);
  Progress.setMinimumDuration(0);
  Progress.setCancelButton(0);

  for (int i=0;i<Num_total_layers;i++){
    std::string Name=Vec_order_of_layers_by_name[i];
    if (Map_name_to_layer[Name].Layer->layer_type()>=_layer_ns::_layer_type::LAYER_TYPE_MAP_DISTANCE || Map_name_to_layer[Name].Layer->layer_type()>=_layer_ns::_layer_type::LAYER_TYPE_MAP_TRIANGULATION){
      Progress.setValue(Count_progress++);
      if (Progress.wasCanceled()) break;
      save_single_layer(Name);
    }
  }

  Progress.setValue(Num_element_layers);

  QMessageBox::information(this,tr("Information"),tr("All the elements/pigments have been correctly saved"));
}

/*************************************************************************/

void _window::save_single_layer_with_color_bar(std::string Name, float Value)
{
  QFont Normal_font=QApplication::font();
  int Normal_font_size=int(float(Normal_font.pointSize())*Positions_print_font_factor);
  Normal_font.setPointSize(Normal_font_size);

  // compute the space of a '0'
  QFontMetrics Font_metric(Normal_font);
  QRect Rect_char=Font_metric.boundingRect('0');
  int Normal_font_pixels_width=Rect_char.width();
//  int Normal_font_pixels_height=Rect_char.height();

  // color box. It must be odd
  int Color_box_width=int(roundf(float(Normal_font_pixels_width)*_color_bar_abstract_ns::COLOR_BOX_FACTOR));
  if (Color_box_width<_color_bar_abstract_ns::COLOR_BOX_MIN) Color_box_width=_color_bar_abstract_ns::COLOR_BOX_MIN;
  if (Color_box_width%2!=0) Color_box_width++;

  // The image of the selected layer
  cv::Mat Image_opencv=Map_name_to_layer[Name].Layer->image()->clone();
  cv::flip(Image_opencv,Image_opencv,0);

  //
  int Width1=Image_opencv.cols-1;
  int Height1=Image_opencv.rows-1;

  // change form OpenCV to Qt format
  QImage Image_original(Image_opencv.data,Image_opencv.cols,Image_opencv.rows,static_cast<int>(Image_opencv.step),QImage::Format_ARGB32);
//  Image_original.rgbSwapped();

  QString Text=QString::fromStdString(Map_name_to_layer[Name].Color_bar_name);

  // the font size must depend on the image height
  // 1 point=1/72 of 1 inch=
  // 12 points=12/72 of 1 inch= 25.4*12/72=4.23 mm

  // height at 300ppi
//  float Height_inches=float(Height1)/300.0f;
//  // we define n rows that must be draw in the Height
//  int N_rows=20;
//  float Font_highness=float(Height_inches)/float(N_rows);
//  int Font_size=int(roundf(Font_highness/(1.0f/72.0f)));

  int Color_bar_width=_w_color_bar::total_width(Value,Normal_font);

  // if the image height is less than Color_bar_width, the width og the final image will be Color_bar_width
  int Image_width=Image_original.width();
  int Image_height=Image_original.height();
  if (Image_height<Color_bar_width) Image_height=Color_bar_width;

  // parameters
  int White_space=5;
  int Line_width=3;

  // WS=white space  LW=line width IW=image width WC=width_color_bar
  // horizontal : WS+LW+WS+IW+WS+LW+WS+WS+WC+WS
  // vertical: WS+LW+WS+IH+WS+LW+WS
  int Image_total_width=Image_width+Color_bar_width+4*White_space+2*Line_width+Color_box_width;
  int Image_total_height=Image_height+4*White_space+2*Line_width;

  QImage Image_result(Image_total_width,Image_total_height,QImage::Format_ARGB32);
  Image_result.fill(Qt::white);

  //
  QPainter Painter(&Image_result);
  // Draw the image of the layer
  Painter.drawImage(2*White_space+Line_width,2*White_space+Line_width,Image_original);

  QPen Previous_pen=Painter.pen();

  QPen Pen;
  Pen.setWidth(Line_width);
  Painter.setPen(Pen);

  // Draw the black border
  QRect Rect2(White_space,White_space,Image_width+2*White_space+2*Line_width,Image_height+2*White_space+2*Line_width);
  Painter.drawRect(Rect2);

  Painter.setPen(Previous_pen);

  // Draw the name of the element/pigment in the center of the char zone
  // check the font size that allows to show the text
  int Text_width;
  int Label_font_size=2*Normal_font_size+1;
  do{
    Label_font_size--;
    QFont Font2(QApplication::font());
    Font2.setBold(true);
    Font2.setPointSize(Label_font_size);
    QFontMetrics Font_metric2(Font2);
    Text_width=Font_metric2.horizontalAdvance(Text);
  } while (Label_font_size>10 && Text_width>(Color_bar_width-2));

  QFont Label_font(Normal_font);
  Label_font.setBold(true);
  Label_font.setPointSize(Label_font_size);
  QFontMetrics Font_metric_label(Label_font);
  QString Clipped_text = Font_metric_label.elidedText(Text, Qt::ElideMiddle, Color_bar_width-2);

  int Width_title=Font_metric_label.horizontalAdvance(Text);

  // for the Height of the label box
  QFont Font_aux(Normal_font);
  Font_aux.setPointSize(Normal_font_size*2);
  QFontMetrics Font_aux_metric(Font_aux);
  QRect Rect_char2=Font_aux_metric.boundingRect('M');
  int Font_aux_pixels_height=Rect_char2.height();

  // draw label
  Painter.setFont(Label_font);
  Painter.drawText(QPointF(Image_result.width()-Color_bar_width/2-Width_title/2-Color_box_width/2,1.5*Font_aux_pixels_height),Clipped_text); // 1+1/2

  QRect Rect3(Image_result.width()-Color_bar_width, White_space+2*Font_aux_pixels_height, Color_bar_width,Image_original.height()-2*White_space-2*Line_width-2*Font_aux_pixels_height);

  Painter.setFont(Normal_font);
  // Draw the color bar
  if (Map_name_to_layer[Name].Color_bar->type()==_palette_data_ns::_data_type::DATA_TYPE_DISCRETE){
    Painter.translate(Rect3.x(),Rect3.y());
    static_cast<_color_bar_sections *>(Map_name_to_layer[Name].Color_bar)->draw(Painter,Rect3,Normal_font_size);
    Painter.translate(-Rect3.x(),-Rect3.y());
  }
  else{
    Painter.translate(Rect3.x(),Rect3.y());
    static_cast<_color_bar_interpolation *>(Map_name_to_layer[Name].Color_bar)->draw(Painter,Rect3,Normal_font_size);
    Painter.translate(-Rect3.x(),-Rect3.y());
  }

  // Draw the positions
  if (Show_positions==true){
    // Translate to the origin of the image
    Painter.translate(QPointF(2*White_space+Line_width,2*White_space+Line_width));
    draw_positions(Painter,Width1,Height1);
//    Painter.translate(QPointF(-2.5*White_space,-(3.5*White_space+Rect_name.height())));
  }
  Painter.end();

  QString File_name(Project_dir+"/xrf/maps/"+QString::fromStdString(Name));
  if (Show_positions==true) File_name=File_name+"_positions";
  File_name=File_name+"_colorbar.png";

  Image_result.save(File_name,"PNG");
}

/*************************************************************************/

void _window::save_single_layer_with_color_bar_slot()
{
  save_single_layer_with_color_bar(Vec_order_of_layers_by_name[Selected_layer],Project_data.Max_value);

  QMessageBox::information(this,tr("Information"),tr("The image of the selected element/pigment has been correctly saved"));
}

/*************************************************************************/

void _window::save_all_layers_with_color_bar_slot()
{
  int Num_total_layers=int(Vec_order_of_layers_by_name.size());
  int Num_element_layers=0;

  for (int i=0;i<Num_total_layers;i++){
    std::string Name=Vec_order_of_layers_by_name[i];
    if (Map_name_to_layer[Name].Layer->layer_type()>=_layer_ns::_layer_type::LAYER_TYPE_MAP_DISTANCE || Map_name_to_layer[Name].Layer->layer_type()>=_layer_ns::_layer_type::LAYER_TYPE_MAP_TRIANGULATION) Num_element_layers++;
  }

  int Count_progress=0;
  QProgressDialog Progress("Working...", "Abort",0,Num_element_layers,this);
  Progress.setWindowModality(Qt::WindowModal);
  Progress.setMinimumDuration(0);
  Progress.setCancelButton(0);

  for (int i=0;i<Num_total_layers;i++){
    std::string Name=Vec_order_of_layers_by_name[i];
    if (Map_name_to_layer[Name].Layer->layer_type()>=_layer_ns::_layer_type::LAYER_TYPE_MAP_DISTANCE || Map_name_to_layer[Name].Layer->layer_type()>=_layer_ns::_layer_type::LAYER_TYPE_MAP_TRIANGULATION){
      Progress.setValue(Count_progress++);
      if (Progress.wasCanceled()) break;
      save_single_layer_with_color_bar(Name,Project_data.Max_value);
    }
  }

  Progress.setValue(Num_element_layers);

  QMessageBox::information(this,tr("Information"),tr("All the elements/pigments have been correctly saved"));
}

/*************************************************************************/

void _window::options_slot()
{
  if (!W_options){
    W_options=new _w_options(this);
    connect(W_options,SIGNAL(accepted()),W_options,SLOT(close()));
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

void _window::show_positions_slot()
{
  if (Show_positions) Show_positions=false;
  else Show_positions=true;

  std::static_pointer_cast<_layer_positions_ui>(Map_name_to_layer["Positions"].Layer)->draw_positions(Show_positions);
  std::static_pointer_cast<_layer_positions_ui>(Map_name_to_layer["Positions"].Layer)->update();
  GL_widget->update_texture("Positions");

  GL_widget->update();
}

/*************************************************************************/

void _window::show_triangulation_normal_slot()
{
  switch (Triangulation_mode){
    case _layer_map_triangulation_ns::_triangulation_mode::TRIANGULATION_MODE_NONE:
      Triangulation_mode=_layer_map_triangulation_ns::_triangulation_mode::TRIANGULATION_MODE_NORMAL;
      break;
    case _layer_map_triangulation_ns::_triangulation_mode::TRIANGULATION_MODE_NORMAL:
      Triangulation_mode=_layer_map_triangulation_ns::_triangulation_mode::TRIANGULATION_MODE_NONE;
      break;
    case _layer_map_triangulation_ns::_triangulation_mode::TRIANGULATION_MODE_WITH_CORNERS:
      Triangulation_mode=_layer_map_triangulation_ns::_triangulation_mode::TRIANGULATION_MODE_NORMAL;
      View_show_triangulation_with_corners->blockSignals(true);
      View_show_triangulation_with_corners->setChecked(false);
      View_show_triangulation_with_corners->blockSignals(false);
      break;
  }

  std::static_pointer_cast<_layer_positions_ui>(Map_name_to_layer["Positions"].Layer)->draw_triangulation_mode(Triangulation_mode);
  std::static_pointer_cast<_layer_positions_ui>(Map_name_to_layer["Positions"].Layer)->update();
  GL_widget->update_texture("Positions");

  GL_widget->update();
}

/*************************************************************************/

void _window::show_triangulation_with_corners_slot()
{
  switch (Triangulation_mode){
    case _layer_map_triangulation_ns::_triangulation_mode::TRIANGULATION_MODE_NONE:
      Triangulation_mode=_layer_map_triangulation_ns::_triangulation_mode::TRIANGULATION_MODE_WITH_CORNERS;
      break;
    case _layer_map_triangulation_ns::_triangulation_mode::TRIANGULATION_MODE_NORMAL:
      Triangulation_mode=_layer_map_triangulation_ns::_triangulation_mode::TRIANGULATION_MODE_WITH_CORNERS;
      View_show_triangulation_normal->blockSignals(true);
      View_show_triangulation_normal->setChecked(false);
      View_show_triangulation_normal->blockSignals(false);
      break;
    case _layer_map_triangulation_ns::_triangulation_mode::TRIANGULATION_MODE_WITH_CORNERS:
      Triangulation_mode=_layer_map_triangulation_ns::_triangulation_mode::TRIANGULATION_MODE_NONE;
      break;
  }

  std::static_pointer_cast<_layer_positions_ui>(Map_name_to_layer["Positions"].Layer)->draw_triangulation_mode(Triangulation_mode);
  std::static_pointer_cast<_layer_positions_ui>(Map_name_to_layer["Positions"].Layer)->update();
  GL_widget->update_texture("Positions");

  GL_widget->update();
}

/*************************************************************************/

void _window::normal_slot()
{
  switch(State){
    case _window_ns::_state::STATE_NORMAL:
      break;
    case _window_ns::_state::STATE_STATISTICS:
    case _window_ns::_state::STATE_HISTOGRAM:
      {
      // remove the widget
      QWidget *Widget=Splitter_view->widget(0);
      delete Widget;
      }
      break;
    case _window_ns::_state::STATE_LABORATORY:
      Splitter_edit->show();

      break;
    case _window_ns::_state::STATE_3D:

      Splitter_edit->show();
      break;
  }

  GL_widget->setCursor(Qt::ArrowCursor);

  State=_window_ns::_state::STATE_NORMAL;
}

/*************************************************************************/

void _window::compute_normalized_images(std::string Name, std::shared_ptr<cv::Mat> Original)
{
  // convert first the RGBA image. It is used with the other conversions
  std::shared_ptr<cv::Mat> Image_normalized=std::make_shared<cv::Mat>();
  // BGRA -> RGBA  (interchange R and B channels)
  cv::cvtColor(*Original.get(),*Image_normalized.get(),cv::COLOR_BGRA2RGBA,4);
  // convert to 4 float
  Image_normalized->convertTo(*Image_normalized, CV_32FC4);

  cv::Vec4f Data;
  // RGBA
  // This is compulsory: the other color models convert from RGB to XXX. The values must be normalized
  for (size_t i=0;i<Image_normalized->total();i++){
    Data=Image_normalized->at<cv::Vec4f>(i);
    Data/=255.0f;
    Image_normalized->at<cv::Vec4f>(i)=Data;
  }

  Map_normalized_images[Name].push_back(Image_normalized);

  // now the other formats
  for (int Color_model=int(_common_ns::_color_model::COLOR_MODEL_HLS);Color_model<int(_common_ns::_color_model::COLOR_MODEL_LAST);Color_model++){
    // copy the color image
    Image_normalized=std::make_shared<cv::Mat>();

   *Image_normalized=Map_normalized_images[Name][0]->clone();

    cv::Mat Color_channels(Original->rows,Original->cols, CV_32FC3);
    cv::Mat Alpha_channel(Original->rows,Original->cols, CV_32FC1);
    cv::Mat Out[]={Color_channels,Alpha_channel};
    int from_to[] = { 0,0, 1,1, 2,2, 3,3 };
    // split the channels in the color part and the transparency part
    // source, num_sources, destiny, num_destinies, from_to, num_pairs
    cv::mixChannels(Image_normalized.get(),1,Out,2,from_to,4);

    switch (Color_model) {
      case int(_common_ns::_color_model::COLOR_MODEL_HLS):
        //  0<=H<=360, 0<=S<=1, 0<=V<=1
        cv::cvtColor(Color_channels,Color_channels,cv::COLOR_RGB2HLS,3);
        break;
      case int(_common_ns::_color_model::COLOR_MODEL_HSV):
        //  0<=H<=360, 0<=S<=1, 0<=V<=1
        cv::cvtColor(Color_channels,Color_channels,cv::COLOR_RGB2HSV,3);
        break;
      case int(_common_ns::_color_model::COLOR_MODEL_LAB):
        //  0<=L<=100, -127<=a<=127, -127<=b<=127
        cv::cvtColor(Color_channels,Color_channels,cv::COLOR_RGB2Lab,3);
        break;
      case int(_common_ns::_color_model::COLOR_MODEL_LUV):
        //  0<=L<=100, -134<=u<=220, -140<=v<=122
        cv::cvtColor(Color_channels,Color_channels,cv::COLOR_RGB2Luv,3);
        break;
      default:break;
    }

    // add the Alpha_channel channel
    cv::mixChannels(Out,2,Image_normalized.get(),1,from_to,4);

//    cv::Vec4f Data;
//    // RGBA
//    for (size_t i=0;i<Image_normalized->total();i++){
//      Data=Image_normalized->at<cv::Vec4f>(i);
//    }

    Map_normalized_images[Name].push_back(Image_normalized);
  }
}

/*************************************************************************/

void _window::update_order_images(std::string Name)
{
  if (Selected_layer==-1 || Selected_layer==int(Vec_order_of_layers_by_name.size())){
    // it is the first time or the selecte layer is the last element
    Vec_order_of_layers_by_name.push_back(Name);
  }
  else{
    // the selected layer is not the last one. The order is changed. The new layer is placed after the current selected layer
    Vec_order_of_layers_by_name.push_back(Vec_order_of_layers_by_name.back());
    for (int i=int(Vec_order_of_layers_by_name.size())-1;i>Selected_layer;i--){
      Vec_order_of_layers_by_name[i]=Vec_order_of_layers_by_name[i-1];
    }
    Vec_order_of_layers_by_name[Selected_layer+1]=Name;
  }
}

/*************************************************************************/
// the destination is at the end

void _window::move_layers_backward(int Initial_pos, int Destination_pos)
{
  std::string Aux_string=Vec_order_of_layers_by_name[Initial_pos];

  for (int i=Initial_pos;i<Destination_pos;i++){
    Vec_order_of_layers_by_name[i]=Vec_order_of_layers_by_name[i+1];
  }
  Vec_order_of_layers_by_name[Destination_pos]=Aux_string;

  show_layer_parameters(Destination_pos,0);
}

/*************************************************************************/
// the destination is at the begin

void _window::move_layers_forward(int Initial_pos, int Destination_pos)
{
  std::string Aux_string=Vec_order_of_layers_by_name[Initial_pos];

  for (int i=Initial_pos;i>Destination_pos;i--){
    Vec_order_of_layers_by_name[i]=Vec_order_of_layers_by_name[i-1];
  }
  Vec_order_of_layers_by_name[Destination_pos]=Aux_string;

  show_layer_parameters(Destination_pos,0);
}

/*************************************************************************/

void _window::remove_pigment_layer(int Row)
{
  std::string Name=Vec_order_of_layers_by_name[Row];

  if (Map_name_to_layer[Name].Layer->layer_type()!=_layer_ns::_layer_type::LAYER_TYPE_BASIC){

    Tab_widget->Table_layers->remove_row(Row);

    Color_bar_widget->remove_color_bar(Name);

    Tab_widget->remove_layer_from_layout(Name);

    Map_name_to_layer.erase(Name);

    for (unsigned int i=Row;i<Vec_order_of_layers_by_name.size()-1;i++){
      Vec_order_of_layers_by_name[i]=Vec_order_of_layers_by_name[i+1];
    }
    Vec_order_of_layers_by_name.pop_back();

    Selected_layer=Row-1;
    if (Selected_layer>=0){
      Tab_widget->Table_layers->selectRow(Selected_layer);

      for(unsigned int i=0; i<Vec_order_of_layers_by_name.size();i++){
        Map_name_to_layer[Vec_order_of_layers_by_name[i]].Layer->hide();
      }

      Map_name_to_layer[Vec_order_of_layers_by_name[Selected_layer]].Layer->show();

      show_layer_parameters(Selected_layer,0);
    }

    // check if all the elements layers have been removed. Only the images are maintained
    if (Vec_order_of_layers_by_name.size()-Num_images==0){
//      View_save_positions->setEnabled(false);
      View_show_positions->setEnabled(true);
//      View_show_triangulation->setEnabled(false);
//      View_compose_colors->setEnabled(false);
      for (unsigned int i=1;i<View.size();i++) View[i]->setEnabled(false);
    }

    //    update();
    GL_widget->update();

    // remove 1 to the numeber of elements
    Num_elements_computed--;
    // change the visibilty of some options that are for elements
    if (Num_elements_computed==0){
      for (unsigned int i=1;i<View.size();i++){
        View[i]->setEnabled(false);
      }
    }
  }
}

/*************************************************************************/

void _window::remove_pigment_layer()
{
  remove_pigment_layer(Selected_layer);
}

/*************************************************************************/

void _window::remove_all_pigment_layers()
{
  int Num_layers=int(Vec_order_of_layers_by_name.size());

  for (int i=Num_layers-1;i>=0;i--){
    remove_pigment_layer(i);
  }
}

/*************************************************************************/

void _window::remove_layer(int Row)
{
  std::string Name=Vec_order_of_layers_by_name[Row];

  Tab_widget->Table_layers->remove_row(Row);

  Color_bar_widget->remove_color_bar(Name);

  Tab_widget->remove_layer_from_layout(Name);

  Map_name_to_layer.erase(Name);

  for (unsigned int i=Row;i<Vec_order_of_layers_by_name.size()-1;i++){
    Vec_order_of_layers_by_name[i]=Vec_order_of_layers_by_name[i+1];
  }
  Vec_order_of_layers_by_name.pop_back();

  Selected_layer=Row-1;
  if (Selected_layer>=0){
    Tab_widget->Table_layers->selectRow(Selected_layer);

    for(unsigned int i=0; i<Vec_order_of_layers_by_name.size();i++){
      Map_name_to_layer[Vec_order_of_layers_by_name[i]].Layer->hide();
    }

    Map_name_to_layer[Vec_order_of_layers_by_name[Selected_layer]].Layer->show();

    show_layer_parameters(Selected_layer,0);
  }

  // check if all the elements layers have been removed.
  if (Vec_order_of_layers_by_name.size()==0){

//      View_save_positions->setEnabled(false);
    View_show_positions->setEnabled(true);
//    View_show_triangulation->setEnabled(false);
//    View_compose_colors->setEnabled(false);
    for (unsigned int i=1;i<View.size();i++) View[i]->setEnabled(false);
  }

  //    update();
  GL_widget->update();

  // remove 1 to the numeber of elements
  Num_elements_computed--;
  // change the visibilty of some options that are for elements
  if (Num_elements_computed==0){
    for (unsigned int i=1;i<View.size();i++){
      View[i]->setEnabled(false);
    }
  }
}

/*************************************************************************/

void _window::remove_all_layers()
{
  int Num_layers=int(Vec_order_of_layers_by_name.size());

  for (int i=Num_layers-1;i>=0;i--){
    remove_layer(i);
  }

   Map_name_to_layer.erase("Positions");
}

/*************************************************************************/

void _window::show_layer_parameters(int Row,int Col)
{
  Q_UNUSED(Col)
  Selected_layer=Row;
  for(unsigned int i=0; i<Vec_order_of_layers_by_name.size();i++){
    Map_name_to_layer[Vec_order_of_layers_by_name[i]].Layer->hide();
  }

  Map_name_to_layer[Vec_order_of_layers_by_name[Selected_layer]].Layer->show();

  Color_bar_widget->update_color_bar(Selected_tab);
  if (state()==_window_ns::_state::STATE_STATISTICS){
  }
  else{
    if (state()==_window_ns::_state::STATE_HISTOGRAM){
    }
  }
}

/*************************************************************************/

void _window::add_layer_image(std::string Name1, std::shared_ptr<cv::Mat> Image1)
{
  // Image1 is the color image
  std::string Name;

//  cv::Vec4b Data;
//  // RGBA
//  for (size_t i=0;i<Image1->total();i++){
//    Data=Image1->at<cv::Vec4b>(i);
//    Data[0]=Data[0] & 0xc0;
//    Data[1]=Data[1] & 0xc0;
//    Data[2]=Data[2] & 0xc0;
//    Image1->at<cv::Vec4b>(i)=Data;
//  }

  Name=Name1+"_"+std::to_string(Vec_order_of_layers_by_name.size());
  // create a image layer with its associated name
  Map_name_to_layer[Name].Layer=std::make_shared<_layer_basic_ui>(this,Name);
  // assign the image
  Map_name_to_layer[Name].Layer->image(Image1);

  // compute the normalized images
  compute_normalized_images(Name,Image1);

  // add the name to the laye list in the elements tab
  cv::Mat Small_image;
  int Size1;
  int Width1;
  int Height1;

  if (screen_height()<=1080) Size1=_window_ns::ICON_SIZE_1080;
  else Size1=_window_ns::ICON_SIZE_1080*Screen_height/1080;

  if (Image1->cols>Image1->rows){
    Width1=Size1;
    Height1=int(float(Image1->rows)*Size1/float(Image1->cols));
  }
  else{
    Height1=Size1;
    Width1=int(float(Image1->cols)*Size1/float(Image1->rows));
  }

  // For the Icon
  adjust_image_sizes(Width1,Height1);
  cv::resize(*Image1.get(),Small_image,cv::Size(Width1,Height1),0,0,cv::INTER_CUBIC);
  cv::cvtColor(Small_image,Small_image,cv::COLOR_BGRA2RGB,3);
  cv::flip(Small_image,Small_image,0);

  QPixmap Pixmap;
  Pixmap=QPixmap::fromImage(QImage((unsigned char*) Small_image.data, Small_image.cols, Small_image.rows,QImage::Format_RGB888));

  QIcon *Icon=new QIcon; // VALGRIND
  Icon->addPixmap(Pixmap);

  Map_name_to_layer[Name].Layer->icon(Icon);

  // get the id for the texture
  Map_name_to_layer[Name].Texture=GL_widget->set_texture(Map_name_to_layer[Name].Layer->image());

  // orders the images
  std::vector<float> Values;
  std::vector<QColor> Colors;
  Values.resize(3);
  Colors.resize(3);

  update_order_images(Name);

  Map_name_to_layer[Name].Color_bar=new _color_bar_abstract(_palette_data_ns::_color_type::COLOR_TYPE_TONE,3,Values,Colors,this);
  Map_name_to_layer[Name].Color_bar_name="";

  Color_bar_widget->add_palette_layer(Name);

  // the first time the texture must be refreshed
  if (Vec_order_of_layers_by_name.size()==1){
    GL_widget->refresh_texture(Map_name_to_layer[Initial_image].Layer->image()->cols,Map_name_to_layer[Initial_image].Layer->image()->rows);
  }

  // show only the control parameter of the new layer
  _table_layers_ns::_info Info;
  Info.Name=QString::fromStdString(Name);

  // add the image to the lists
  Tab_widget->add_image(Info,Icon);

  // the layer with the image
  Tab_widget->add_layer(Info);

  Selected_tab=_w_tab_ns::_tabs::LAYERS_TAB;
  Tab_widget->setCurrentIndex(int(Selected_tab));

  show_layer_parameters(Selected_layer+1,0);

  GL_widget->update();
}

/*************************************************************************/

void _window::add_layer_filter(_layer_ns::_layer_type Layer_type)
{
  std::shared_ptr<cv::Mat> Image=std::make_shared<cv::Mat>();
  std::string Name;

  *Image=Map_name_to_layer[Vec_order_of_layers_by_name[Selected_layer]].Layer->image()->clone();

  switch(Layer_type){
  default:break;
  }

  Map_name_to_layer[Name].Texture=GL_widget->set_texture(Map_name_to_layer[Name].Layer->image());

  // orders the images
  std::vector<float> Values;
  std::vector<QColor> Colors;
  Values.resize(3);
  Colors.resize(3);

  update_order_images(Name);

  Map_name_to_layer[Name].Color_bar=new _color_bar_abstract(_palette_data_ns::_color_type::COLOR_TYPE_TONE,3,Values,Colors,this);
  Map_name_to_layer[Name].Color_bar_name="";

  Color_bar_widget->add_palette_layer(Name);

  _table_layers_ns::_info Info;
  Info.Name=QString::fromStdString(Name);

  Tab_widget->add_layer(Info);

  Selected_tab=_w_tab_ns::_tabs::LAYERS_TAB;
  Tab_widget->setCurrentIndex(int(Selected_tab));

  show_layer_parameters(Selected_layer+1,0);

  Tab_widget->select_layers_row(Selected_layer);

  GL_widget->update();
}

/*************************************************************************/
// Adds a layer corresponding to an element (single or compound)
// It is importat to note that it is possible to have several layers obtained from
// a single element (XRF or XRD). For example, it is possible to compute the distance
// only using the color or the position
// So, it is neccesary to obtain the new values but also to link to the original data

void _window::add_layer_map_minimum_hypercube_distance(std::string Name_image1, std::string Name_pigment1, std::string View_name1, _common_ns::_color_model Color_model1, std::vector<bool> Use_colors1, std::vector<bool> Use_positions1, bool Distance_normalization1, _layer_map_distance_ns::_position_normalization_type Position_normalization_type1, int Probe1, int Palette1, _palette_data_ns::_data_type_print Data_type_print1, _color_map_ns::_color_for_zero_value Color_for_zero_value1, std::map<std::string, _pigment_data_ns::_pigment_data> &Map_pigment_data)
{
  std::shared_ptr<cv::Mat> Image_normalized=std::make_shared<cv::Mat>();

  // get the normalized image that will be used for computing the minimum distance
  // currently only one image is used ???
  Image_normalized=Map_normalized_images[Name_image1][int(Color_model1)];//->clone();

  std::string Name_layer;
  std::string Name_pigment_aux=View_name1+"_"+Name_pigment1+"_";

  // text to know the type of computation that was made: c -> color, p -> position
  Name_pigment_aux=Name_pigment_aux+_common_ns::Vec_names_color_model[int(Color_model1)].toStdString()+"_";
  if (Use_colors1[0]==true || Use_colors1[1]==true || Use_colors1[2]==true) Name_pigment_aux=Name_pigment_aux+"c";
  if (Use_colors1[0]==true) Name_pigment_aux=Name_pigment_aux+"1";
  if (Use_colors1[1]==true) Name_pigment_aux=Name_pigment_aux+"2";
  if (Use_colors1[2]==true) Name_pigment_aux=Name_pigment_aux+"3";
  if (Use_positions1[0]==true || Use_positions1[1]==true) Name_pigment_aux=Name_pigment_aux+"p";
  if (Use_positions1[0]==true) Name_pigment_aux=Name_pigment_aux+"1";
  if (Use_positions1[1]==true) Name_pigment_aux=Name_pigment_aux+"2";

  if (Distance_normalization1==true) Name_pigment_aux=Name_pigment_aux+"_NY";
  else Name_pigment_aux=Name_pigment_aux+"_NN";

  if (Position_normalization_type1==_layer_map_distance_ns::_position_normalization_type::POSITION_NORMALIZATION_HOMOGENEOUS) Name_pigment_aux=Name_pigment_aux+"_HO";
  else Name_pigment_aux=Name_pigment_aux+"_HE";

  // the name add the position of the current layer. There are not two layers that are equal in name
  Name_layer=Name_pigment_aux+"_"+std::to_string(Vec_order_of_layers_by_name.size());
  // add the map between the original element and the layer (to get information)
//  Map_element_layer.insert(std::pair<string,string>(Name_pigment_aux,Name_layer));
  // add the map between the name of the layer and the original element (to get information)
  Map_name_of_layer_to_name_of_element.insert(std::pair<std::string,std::string>(Name_layer,Name_pigment1));

  // create the new layer
  std::shared_ptr<_layer_map_distance_ui> Layer=std::make_shared<_layer_map_distance_ui>(this,Name_layer);
  // add to the map
  Map_name_to_layer[Name_layer].Layer=Layer;
  // add the name
  Map_name_to_layer[Name_layer].Pigment_name=Name_pigment1;
  // the result image
  std::shared_ptr<cv::Mat> Image_r=std::make_shared<cv::Mat>();
  Image_r->create(Initial_height,Initial_width,CV_8UC4);
  Layer->image(Image_r);
  // the data of the element
  Layer->add_input_data(Project_data.Vec_coordinate_x,Project_data.Vec_coordinate_y,Map_pigment_data[Name_pigment1].Vec_values);
  // the valid positions
  Layer->add_valid_positions(Vec_active_positions);
  // the color image
  Layer->add_input_image(Image_normalized);
//  Layer->add_image_alpha_channel(Image_alpha_channel);
  Layer->size(Initial_width,Initial_height);
  Layer->color_model(Color_model1);
  Layer->probe(Probe1);
  Layer->use_colors(Use_colors1);
  Layer->use_positions(Use_positions1);
  Layer->normalization(Distance_normalization1);
  Layer->position_normalization_type(Position_normalization_type1);
  Layer->data_type_print(Data_type_print1);

  bool Invisible=true;
  if (Invisible){
    Layer->state(0,false);
    Layer->state(1,true);
  }

  // create color_bar
  std::vector<QColor> Colors;
  Map_name_to_layer[Name_layer].Color_bar=Color_bar_widget->create_color_bar(Palette1,Map_pigment_data[Name_pigment1].Data_type,Name_pigment1,Map_pigment_data[Name_pigment1].Max_value_adjusted,Colors,Data_type_print1,Color_for_zero_value1);

  // assign the name of the element/pigment that produces the map
  Map_name_to_layer[Name_layer].Color_bar_name=Name_pigment1;

  Color_bar_widget->add_palette_layer(Name_layer);
  // pass the palette to the layer
  Layer->set_colormap(Color_bar_widget->Palettes[Palette1]->vec_proportions(),Colors,int(Color_bar_widget->Palettes[Palette1]->type()));

  Layer->update();

  Map_name_to_layer[Name_layer].Texture=GL_widget->set_texture(Map_name_to_layer[Name_layer].Layer->image());

  // update the vector with the order of images
  update_order_images(Name_layer);

  // add the new element of the story. The key is the name of the layer.
//  Element_history[Name_layer]=_pigment_data_ns::_history_data(Name_layer1,Name_element1,View_name1, Palette1,Interpolation_type,Probe1,Use_colors1,Use_positions1,Color_model1,Distance_normalization1);

  // add 1 to the counter
  Num_elements_computed++;
  // change the visibility of some options
  if (Num_elements_computed==1){
    for (unsigned int i=1;i<View.size();i++){
      View[i]->setEnabled(true);
    }
  }

  _table_layers_ns::_info Info;
  Info.Name=QString::fromStdString(Name_layer);

  // check
  Info.States[0]=false;

  Tab_widget->add_layer(Info);
  Selected_tab=_w_tab_ns::_tabs::LAYERS_TAB;
  Tab_widget->setCurrentIndex(int(Selected_tab));

  show_layer_parameters(Selected_layer+1,0);

  Tab_widget->select_layers_row(Selected_layer);

  //
  Submenu_save_single_layer->setEnabled(true);
  Save_single_layer->setEnabled(true);
  Save_single_layer_with_color_bar->setEnabled(true);

  Submenu_save_all_layers->setEnabled(true);
  Save_all_layers->setEnabled(true);
  Save_all_layers_with_color_bar->setEnabled(true);

  Save_composed_image->setEnabled(true);
//  View_save_positions->setEnabled(true);
  View_show_positions->setEnabled(true);

  for (unsigned int i=1;i<View.size();i++) View[i]->setEnabled(true);

  GL_widget->update();
}

/*************************************************************************/
// Adds a layer corresponding to an element (single or compound)
// It is importat to note that it is possible to have several layers obtained from
// a single element (XRF or XRD). For example, it is possible to compute the distance
// only using the color or the position
// So, it is neccesary to obtain the new values but also to link to the original data

void _window::add_layer_map_triangulation(std::string Name_image1, std::string Name_pigment1, std::string View_name1, _common_ns::_color_model Color_model1, int Palette1, bool Triangulation_add_corners1, _palette_data_ns::_data_type_print Data_type_print1, _color_map_ns::_color_for_zero_value Color_for_zero_value1, std::map<std::string,_pigment_data_ns::_pigment_data> &Map_pigment_data)
{
  std::shared_ptr<cv::Mat> Image_normalized=std::make_shared<cv::Mat>();
  std::vector<float> Vec_coordinate_x_corners;
  std::vector<float> Vec_coordinate_y_corners;
  std::vector<float> Vec_values_corners;

  // get the normalized image that will be used for computing the minimum distance
  // currently only one image is used ???
  Image_normalized=Map_normalized_images[Name_image1][int(Color_model1)];//->clone();

  std::string Name_layer;
  std::string Name_element_aux=View_name1+"_"+Name_pigment1+"_";

  Name_element_aux=Name_element_aux+"TRI";

  // the name add the position of the current layer. There are not two layers that are equal in name
  Name_layer=Name_element_aux+"_"+std::to_string(Vec_order_of_layers_by_name.size());
  // add the map between the original element and the layer (to get information)
//  Map_element_layer.insert(std::pair<string,string>(Name_element_aux,Name_layer));
  // add the map between the name of the layer and the original element (to get information)
  Map_name_of_layer_to_name_of_element.insert(std::pair<std::string,std::string>(Name_layer,Name_pigment1));

  // create the new layer
  std::shared_ptr<_layer_map_triangulation_ui> Layer=std::make_shared<_layer_map_triangulation_ui>(this,Name_layer);
  // add to the map
  Map_name_to_layer[Name_layer].Layer=Layer;
  // add the name
  Map_name_to_layer[Name_layer].Pigment_name=Name_pigment1;
  // the result image
  std::shared_ptr<cv::Mat> Image_r=std::make_shared<cv::Mat>();
  Image_r->create(Initial_height,Initial_width,CV_8UC4);
  Layer->image(Image_r);
  // the data of the element
  Layer->size(Initial_width,Initial_height);
  Layer->data_type_print(Data_type_print1);
  // the normalized color image (here is used to check if there are transparent zones
  Layer->add_input_image(Image_normalized);

  if (Triangulation_add_corners1==false){ // send the normal data
    Layer->add_input_data(Project_data.Vec_coordinate_x,Project_data.Vec_coordinate_y,Map_pigment_data[Name_pigment1].Vec_values);
    Layer->add_triangles_data(Triangles);
  }
  else{ // initialize the vector
    Vec_coordinate_x_corners=Project_data.Vec_coordinate_x;
    Vec_coordinate_y_corners=Project_data.Vec_coordinate_y;
    Vec_values_corners=Map_name_to_element[Name_pigment1].Vec_values;

    // add the corners
    Vec_coordinate_x_corners.push_back(0);
    Vec_coordinate_y_corners.push_back(0);
    Vec_values_corners.push_back(0);

    Vec_coordinate_x_corners.push_back(Project_data.Width-1);
    Vec_coordinate_y_corners.push_back(0);
    Vec_values_corners.push_back(0);

    Vec_coordinate_x_corners.push_back(0);
    Vec_coordinate_y_corners.push_back(Project_data.Height-1);
    Vec_values_corners.push_back(0);

    Vec_coordinate_x_corners.push_back(Project_data.Width-1);
    Vec_coordinate_y_corners.push_back(Project_data.Height-1);
    Vec_values_corners.push_back(0);

    Layer->add_input_data(Vec_coordinate_x_corners,Vec_coordinate_y_corners,Vec_values_corners);
    Layer->add_triangles_data(Triangles_with_corners);
  }

  bool Invisible=true;
  if (Invisible){
    Layer->state(0,false);
    Layer->state(1,true);
  }

  // create color_bar
  std::vector<QColor> Colors;
  Map_name_to_layer[Name_layer].Color_bar=Color_bar_widget->create_color_bar(Palette1,Map_pigment_data[Name_pigment1].Data_type,Name_pigment1,Map_pigment_data[Name_pigment1].Max_value_adjusted,Colors,Data_type_print1,Color_for_zero_value1);
  Map_name_to_layer[Name_layer].Color_bar_name=Name_pigment1;
  Color_bar_widget->add_palette_layer(Name_layer);
  // pass the palette to the layer
  Layer->set_colormap(Color_bar_widget->Palettes[Palette1]->vec_proportions(),Colors,int(Color_bar_widget->Palettes[Palette1]->type()));

  Layer->update();

  Map_name_to_layer[Name_layer].Texture=GL_widget->set_texture(Map_name_to_layer[Name_layer].Layer->image());

  // update the vector with the order of images
  update_order_images(Name_layer);

  // add the new element of the story. The key is the name of the layer.
//  Element_history[Name_layer]=_pigment_data_ns::_history_data(Name_layer1,Name_element1,View_name1, Palette1,Interpolation_type,Probe1,Use_colors1,Use_positions1,Color_model1,Distance_normalization1);

  // add 1 to the counter
  Num_elements_computed++;
  // change the visibility of some options
  if (Num_elements_computed==1){
    for (unsigned int i=1;i<View.size();i++){
      View[i]->setEnabled(true);
    }
  }

  _table_layers_ns::_info Info;
  Info.Name=QString::fromStdString(Name_layer);

  // check
  Info.States[0]=false;

  Tab_widget->add_layer(Info);
  Selected_tab=_w_tab_ns::_tabs::LAYERS_TAB;
  Tab_widget->setCurrentIndex(int(Selected_tab));

  show_layer_parameters(Selected_layer+1,0);

  Tab_widget->select_layers_row(Selected_layer);

  //
  Submenu_save_single_layer->setEnabled(true);
  Save_single_layer->setEnabled(true);
  Save_single_layer_with_color_bar->setEnabled(true);

  Submenu_save_all_layers->setEnabled(true);
  Save_all_layers->setEnabled(true);
  Save_all_layers_with_color_bar->setEnabled(true);

  Save_composed_image->setEnabled(true);
//  View_save_positions->setEnabled(true);
  View_show_positions->setEnabled(true);

  for (unsigned int i=1;i<View.size();i++) View[i]->setEnabled(true);

  GL_widget->update();
}

/*************************************************************************/
// Adds a layer corresponding to an element (single or compound)
// It is importat to note that it is possible to have several layers obtained from
// a single element (XRF or XRD). For example, it is possible to compute the distance
// only using the color or the position
// So, it is neccesary to obtain the new values but also to link to the original data

void _window::add_layer_map_rbf_interpolation(std::string Name_image1, std::string Name_pigment1, std::string View_name1,   _common_ns::_color_model Color_model1, int Palette1, _palette_data_ns::_data_type_print Data_type_print1, _color_map_ns::_color_for_zero_value Color_for_zero_value1, std::map<std::string,_pigment_data_ns::_pigment_data> &Map_pigment_data)
{
  std::shared_ptr<cv::Mat> Image_normalized=std::make_shared<cv::Mat>();

  // get the normalized image that will be used for computing the minimum distance
  // currently only one image is used ???
  Image_normalized=Map_normalized_images[Name_image1][int(Color_model1)];

  std::string Name_layer;
  std::string Name_element_aux=View_name1+"_"+Name_pigment1+"_";

  Name_element_aux=Name_element_aux+"RBF";

  // the name add the position of the current layer. There are not two layers that are equal in name
  Name_layer=Name_element_aux+"_"+std::to_string(Vec_order_of_layers_by_name.size());
  // add the map between the original element and the layer (to get information)
//  Map_element_layer.insert(std::pair<string,string>(Name_element_aux,Name_layer));
  // add the map between the name of the layer and the original element (to get information)
  Map_name_of_layer_to_name_of_element.insert(std::pair<std::string,std::string>(Name_layer,Name_pigment1));

  // create the new layer
  std::shared_ptr<_layer_map_rbf_interpolation_ui> Layer=std::make_shared<_layer_map_rbf_interpolation_ui>(this,Name_layer);
  // add to the map
  Map_name_to_layer[Name_layer].Layer=Layer;
  // add the name
  Map_name_to_layer[Name_layer].Pigment_name=Name_pigment1;

  // the result image
  std::shared_ptr<cv::Mat> Image_r=std::make_shared<cv::Mat>();
  Image_r->create(Initial_height,Initial_width,CV_8UC4);
  Layer->image(Image_r);
  // the data of the element
  Layer->size(Initial_width,Initial_height);
  Layer->data_type_print(Data_type_print1);

  // the valid positions
  Layer->add_valid_positions(Vec_active_positions);
  // the input data
  Layer->add_input_data(Project_data.Vec_coordinate_x,Project_data.Vec_coordinate_y,Map_pigment_data[Name_pigment1].Vec_values,RBF_radius);
  // the normalized color image (here is used to check if there are transparent zones
  Layer->add_input_image(Image_normalized);
  // function type
  Layer->set_function_type(RBF_function);

  bool Invisible=true;
  if (Invisible){
    Layer->state(0,false);
    Layer->state(1,true);
  }

  // create color_bar
  std::vector<QColor> Colors;
  Map_name_to_layer[Name_layer].Color_bar=Color_bar_widget->create_color_bar(Palette1,Map_pigment_data[Name_pigment1].Data_type,Name_pigment1,Map_pigment_data[Name_pigment1].Max_value_adjusted,Colors,Data_type_print1,Color_for_zero_value1);
  Map_name_to_layer[Name_layer].Color_bar_name=Name_pigment1;
  Color_bar_widget->add_palette_layer(Name_layer);
  // pass the palette to the layer
  Layer->set_colormap(Color_bar_widget->Palettes[Palette1]->vec_proportions(),Colors,int(Color_bar_widget->Palettes[Palette1]->type()));

  Layer->update();

  Map_name_to_layer[Name_layer].Texture=GL_widget->set_texture(Map_name_to_layer[Name_layer].Layer->image());

  // update the vector with the order of images
  update_order_images(Name_layer);

  // add the new element of the story. The key is the name of the layer.
//  Element_history[Name_layer]=_pigment_data_ns::_history_data(Name_layer1,Name_element1,View_name1, Palette1,Interpolation_type,Probe1,Use_colors1,Use_positions1,Color_model1,Distance_normalization1);

  // add 1 to the counter
  Num_elements_computed++;
  // change the visibility of some options
  if (Num_elements_computed==1){
    for (unsigned int i=1;i<View.size();i++){
      View[i]->setEnabled(true);
    }
#ifdef YES_STATISTICS_GRAPHS
    View_linear_adjust->setEnabled(true);
    View_log_adjust->setEnabled(true);
#endif
  }

  _table_layers_ns::_info Info;
  Info.Name=QString::fromStdString(Name_layer);

  // check
  Info.States[0]=false;

  Tab_widget->add_layer(Info);
  Selected_tab=_w_tab_ns::_tabs::LAYERS_TAB;
  Tab_widget->setCurrentIndex(int(Selected_tab));

  show_layer_parameters(Selected_layer+1,0);

  Tab_widget->select_layers_row(Selected_layer);

  //
  Submenu_save_single_layer->setEnabled(true);
  Save_single_layer->setEnabled(true);
  Save_single_layer_with_color_bar->setEnabled(true);

  Submenu_save_all_layers->setEnabled(true);
  Save_all_layers->setEnabled(true);
  Save_all_layers_with_color_bar->setEnabled(true);

  Save_composed_image->setEnabled(true);
#ifdef YES_STATISTICS_GRAPHS
  View_linear_adjust->setEnabled(true);
  View_log_adjust->setEnabled(true);
#endif
//  View_save_positions->setEnabled(true);
  View_show_positions->setEnabled(true);

#ifndef BASIC
//  View_show_triangulation->setEnabled(true);
//  View_compose_colors->setEnabled(true);
#endif

  for (unsigned int i=1;i<View.size();i++) View[i]->setEnabled(true);

  GL_widget->update();
}


/*************************************************************************/
// Adds a layer corresponding to an element (single or compound)
// It is importat to note that it is possible to have several layers obtained from
// a single element (XRF or XRD). For example, it is possible to compute the distance
// only using the color or the position
// So, it is neccesary to obtain the new values but also to link to the original data

void _window::add_layer_compound_combination(std::string Name_image1, std::string Name_pigment1, std::string View_name1, std::vector<_data_xrf_ns::_data_element_num_atoms> Vec_elements1, std::vector<std::string> Vec_names_in_map1, std::vector<float> Vec_global_percentages1, int Palette1, _palette_data_ns::_data_type_print Data_type_print1, _color_map_ns::_color_for_zero_value Color_for_zero_value1)
{
  std::shared_ptr<cv::Mat> Image_normalized=std::make_shared<cv::Mat>();

  // get the normalized image that will be used for computing the minimum distance
  // currently only one image is used ???
  Image_normalized=Map_normalized_images[Name_image1][int(_common_ns::_color_model::COLOR_MODEL_RGB)];//->clone();

  std::string Name_layer;
  std::string Name_pigment_aux=View_name1+"_"+Name_pigment1;

  // the name add the position of the current layer. There are not two layers that are equal in name
  Name_layer=Name_pigment_aux+"_"+std::to_string(Vec_order_of_layers_by_name.size());

  // add the map between the original element and the layer (to get information)
//  Map_element_layer.insert(std::pair<string,string>(Name_pigment_aux,Name_layer));
  // add the map between the name of the layer and the original element (to get information)
  Map_name_of_layer_to_name_of_element.insert(std::pair<std::string,std::string>(Name_layer,Name_pigment1));

  // create the new layer
  std::shared_ptr<_layer_compound_combination_ui> Layer=std::make_shared<_layer_compound_combination_ui>(this,Name_layer);
  // add to the map
  Map_name_to_layer[Name_layer].Layer=Layer;
  // add the name
  Map_name_to_layer[Name_layer].Pigment_name=Name_pigment1;

  // the result image
  std::shared_ptr<cv::Mat> Image_r=std::make_shared<cv::Mat>();
  Image_r->create(Initial_height,Initial_width,CV_8UC4);
  Layer->image(Image_r);
  // the inputa data
  std::vector<std::shared_ptr<cv::Mat> > Vec_maps_intensities(Vec_elements1.size());
  std::vector<float> Vec_max_intensities(Vec_elements1.size());
  std::vector<float> Vec_percentages(Vec_elements1.size());

  // compute the total number of atoms
  int Num_total_atoms=0;
  for (unsigned int i=0;i<Vec_elements1.size();i++) Num_total_atoms=Num_total_atoms+Vec_elements1[i].Num_atoms;
  // compute the percentages
  for (unsigned int i=0;i<Vec_elements1.size();i++){
    Vec_percentages[i]=float(Vec_elements1[i].Num_atoms)/float(Num_total_atoms);
  }
  // get the maps and max values
  for (unsigned int i=0;i<Vec_names_in_map1.size();i++){
    Vec_maps_intensities[i]=Map_name_to_layer[Vec_names_in_map1[i]].Layer->result_floats_image();
    Vec_max_intensities[i]=Map_name_to_element[Vec_elements1[i].Element_name].Max_value_adjusted;
  }

  Layer->add_input_data(Vec_maps_intensities,Vec_max_intensities,Vec_percentages,Vec_global_percentages1);

  // the color image
  Layer->add_input_image(Image_normalized);
//  Layer->add_image_alpha_channel(Image_alpha_channel);
  Layer->size(Initial_width,Initial_height);
  Layer->data_type_print(Data_type_print1);

  Layer->update();

  float Max_intensity=Layer->max_intensity();

  bool Invisible=true;
  if (Invisible){
    Layer->state(0,false);
    Layer->state(1,true);
  }

  // create color_bar
  std::vector<QColor> Colors;
  Map_name_to_layer[Name_layer].Color_bar=Color_bar_widget->create_color_bar(Palette1, _pigment_data_ns::_data_type::DATA_TYPE_XRF,Name_pigment1,Max_intensity,Colors,Data_type_print1,Color_for_zero_value1);

  Map_name_to_layer[Name_layer].Color_bar_name=Name_pigment1;
  Color_bar_widget->add_palette_layer(Name_layer);
  // pass the palette to the layer
  Layer->set_colormap(Color_bar_widget->Palettes[Palette1]->vec_proportions(),Colors,int(Color_bar_widget->Palettes[Palette1]->type()));

  // it is necessary a second update once the max_intensity is computed and the colormap created. It only updates the colors
  Layer->update();

  Map_name_to_layer[Name_layer].Texture=GL_widget->set_texture(Map_name_to_layer[Name_layer].Layer->image());

  // update the vector with the order of images
  update_order_images(Name_layer);

  // add the new element of the story. The key is the name of the layer.
//  Element_history[Name_layer]=_pigment_data_ns::_history_data(Name_layer1,Name_element1,View_name1, Palette1,Interpolation_type,Probe1,Use_colors1,Use_positions1,Color_model1,Distance_normalization1);

  // add 1 to the counter
  Num_elements_computed++;
  // change the visibility of some options
  if (Num_elements_computed==1){
    for (unsigned int i=1;i<View.size();i++){
      View[i]->setEnabled(true);
    }
//    View_linear_adjust->setEnabled(true);???
//    View_log_adjust->setEnabled(true);
  }

  _table_layers_ns::_info Info;
  Info.Name=QString::fromStdString(Name_layer);

  // check
  Info.States[0]=false;

  Tab_widget->add_layer(Info);
  Selected_tab=_w_tab_ns::_tabs::LAYERS_TAB;
  Tab_widget->setCurrentIndex(int(Selected_tab));

  show_layer_parameters(Selected_layer+1,0);

  Tab_widget->select_layers_row(Selected_layer);

  //
  Submenu_save_single_layer->setEnabled(true);
  Save_single_layer->setEnabled(true);
  Save_single_layer_with_color_bar->setEnabled(true);

  Submenu_save_all_layers->setEnabled(true);
  Save_all_layers->setEnabled(true);
  Save_all_layers_with_color_bar->setEnabled(true);

  Save_composed_image->setEnabled(true);
//  View_linear_adjust->setEnabled(true);???
//  View_log_adjust->setEnabled(true);
//  View_save_positions->setEnabled(true);
  View_show_positions->setEnabled(true);

  for (unsigned int i=1;i<View.size();i++) View[i]->setEnabled(true);

  GL_widget->update();
}

/*************************************************************************/

void _window::update_layer(std::string Name)
{
  Map_name_to_layer[Name].Layer->update();
  GL_widget->update_texture(Name);

  GL_widget->update();
}

/*************************************************************************/

void _window::update_layer(int Pos)
{
  Selected_layer=Pos;
  update_layer(Vec_order_of_layers_by_name[Selected_layer]);
}

/*************************************************************************/

void _window::update_color_bar()
{
  Color_bar_widget->update_color_bar(Selected_tab);
}

/*************************************************************************/

void _window::update_color_bar_data_type_print(int Type1)
{
  Map_name_to_layer[Vec_order_of_layers_by_name[Selected_layer]].Color_bar->data_type_print(_palette_data_ns::_data_type_print(Type1));
  Map_name_to_layer[Vec_order_of_layers_by_name[Selected_layer]].Color_bar->update();

  Color_bar_widget->adjust_width(Project_data.Max_value);
}

/*************************************************************************/
// Visibility

void _window::change_button_state(int Row,int Col)
{
  bool Value=Map_name_to_layer[Vec_order_of_layers_by_name[Row]].Layer->state(Col);
  Map_name_to_layer[Vec_order_of_layers_by_name[Row]].Layer->state(Col,!Value);

  if (state()==_window_ns::_state::STATE_3D){
    // search for the nearest that is visible
    int Pos=-1;;
    for (Pos=Vec_order_of_layers_by_name.size()-1;Pos>=0;Pos--){
      if (Map_name_to_layer[Vec_order_of_layers_by_name[Pos]].Layer->state(0)==true) break;
    }

    if (Pos!=-1){
    }
    else{
    }
  }
  else GL_widget->update();
}

/*************************************************************************/
// Adjust the values to be multiple of 4, which is necessary for OpenCV

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

void _window::reverse_col(int Col)
{
  bool Value;

  for (unsigned int Row=0;Row<Vec_order_of_layers_by_name.size();Row++){
    Value=Map_name_to_layer[Vec_order_of_layers_by_name[Row]].Layer->state(Col);
    Map_name_to_layer[Vec_order_of_layers_by_name[Row]].Layer->state(Col,!Value);
  }

  GL_widget->update();
}

/*************************************************************************/

void _window::save_positions_image(std::string Layer)
{
  int White_space=10;
//  int Pos_x;
//  int Pos_y;

  cv::Mat Image=Map_name_to_layer[Layer].Layer->image()->clone();
  float Width1=float(Image.cols-1);
  float Height1=float(Image.rows-1);

  cv::flip(Image,Image,0);

  QImage image(Image.data,Image.cols,Image.rows,static_cast<int>(Image.step),QImage::Format_ARGB32);
//  image.rgbSwapped();

  QImage Image1(Image.cols+White_space*5,Image.rows+White_space*5,QImage::Format_ARGB32);
  Image1.fill(Qt::white);

//  float Width1=float(Image1.width())-1;

  QPainter Painter(&Image1);
  Painter.drawImage(2.5*White_space,2.5*White_space,image);

  Painter.translate(QPointF(2.5*White_space,2.5*White_space));
  draw_positions(Painter,Width1,Height1);
  Painter.end();

//  QString Dir(Project_dir.absolutePath());
  QString Dir(Project_dir);

//  if (!QDir(Dir+"/results").exists()) QDir().mkdir(Dir+"/results");
//  if (!QDir(Dir+"/results/images").exists()) QDir().mkdir(Dir+"/results/images");

  Image1.save(Dir+QString::fromStdString("/positions/positions.png"),"PNG");

  QMessageBox::information(this,tr("Information"),tr("The image with the positions has been correctly saved"));
}

void _window::save_composed_image_slot()
{
  int Line_width=5;

  cv::Mat Image;
  GL_widget->get_composed_image(&Image);

//  float Width1=float(Image.cols-1);
//  float Height1=float(Image.rows-1);

  cv::flip(Image,Image,0);

  QImage image(Image.data,Image.cols,Image.rows,static_cast<int>(Image.step),QImage::Format_ARGB32);
//  image.rgbSwapped();

  QImage Image1(Image.cols+Line_width*2,Image.rows+Line_width*2,QImage::Format_ARGB32);
  Image1.fill(Qt::black);

//  float Width1=float(Image1.width())-1;

  QPainter Painter(&Image1);
  Painter.drawImage(Line_width,Line_width,image);

  Painter.translate(QPointF(Line_width,Line_width));
  draw_positions(Painter,Initial_width,Initial_height);
  Painter.end();

//  QString Dir(Project_dir.absolutePath());
  QString Dir(Project_dir);

//  if (!QDir(Dir+"/results").exists()) QDir().mkdir(Dir+"/results");
//  if (!QDir(Dir+"/results/images").exists()) QDir().mkdir(Dir+"/results/images");

  Image1.save(Dir+QString::fromStdString("/xrf/maps/composed_image.png"),"PNG");

  QMessageBox::information(this,tr("Information"),tr("The composed image has been correctly saved"));
}

/*************************************************************************/

void _window::selected_image(std::string Image_name)
{
  Mapping_selected_image_name=Image_name;

  for (unsigned int i=0;i<Vec_order_mapping->size();i++){
    if ((*Vec_order_mapping)[i]==Image_name){
      Mapping_selected_image_index=i;
      break;
    }
  }
  Mapping_images_tab->set_selected_item(Mapping_selected_image_index);

}

/*************************************************************************/

QColor _window::compute_color(std::string Name_element)
{
  QColor Color;
  bool Found=false;
  float Hue=0;

  if (Name_element=="") Found=false;
  else{
    for (auto &Data: _window_ns::Vec_atomic_data){
      if (Name_element==Data.Short_name){
        Color=Data.Color;
        Found=true;
        break;
      }
    }
  }

  if (Found==false){
    std::random_device Random_device;   // non-deterministic generator
    std::mt19937 Generator(Random_device());  // to seed mersenne twister.
    std::uniform_int_distribution<> Random(0,359);
    Hue=Random(Generator);
    Color.setHsv(Hue,255,255);
    Color.toRgb();
  }

  return(Color);
}

/*************************************************************************/

void _window::parameters_changed()
{
  save_settings();

  if (Loaded_image==true){
    std::static_pointer_cast<_layer_positions_ui>(Map_name_to_layer["Positions"].Layer)->parameters(Positions_display_font_size,Positions_display_out_circle_size, Positions_display_font_color, Positions_display_out_circle_color,Positions_display_in_circle_color);

    std::static_pointer_cast<_layer_positions_ui>(Map_name_to_layer["Positions"].Layer)->update();
    GL_widget->update_texture("Positions");
    GL_widget->update();
  }
}

/*************************************************************************/

void _window::splitter_moved_slot(int Pos,int Index)
{
  Q_UNUSED(Index)
  Size_chart=Pos;
}

/*************************************************************************/

bool _window::check_project()
{
  if (QFile::exists(_window_ns::Project_name)){
    std::fstream File;
    std::string Line;
    File.open(_window_ns::Project_name.toStdString(),std::ios::in);
    if (getline(File,Line)){
      Project_name=QString::fromStdString(Line);
      // remove carriage return
      Project_name.remove('\r');
      // remove blank spaces at the beginning
      Project_name.remove(' ');
      // remove tabs
      Project_name.remove('\t');
      if (Project_name.length()>0){

        QDir Dir("./projects/"+Project_name);
        if (Dir.exists()){
          Project_dir=Dir.canonicalPath();

          QMessageBox::information(this,tr("Information"),"The project <font color='#ff0000'><b>"+Project_name+"</b></font> is going to be loaded");

          load_project();

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

void _window::change_active_position(int Position)
{
  Vec_active_positions[Position]=!Vec_active_positions[Position];

  if (Vec_active_positions[Position]==true) Num_active_positions++;
  else Num_active_positions--;
}

/*************************************************************************/

void _window::xrf_recompute_data()
{
  // updates the positions image
  add_layer_positions_image();

  GL_widget->update();
}

/*************************************************************************/
// for the creation of layers

void _window::use_colors(int Pos,bool Value)
{
  if (Pos>=0 && Pos<=2){
    Use_colors[Pos]=Value;
  }
}

/*************************************************************************/

bool _window::use_colors(int Pos)
{
  if (Pos>=0 && Pos<=2){
    return Use_colors[Pos];
  }

  return false;
}

/*************************************************************************/

void _window::use_positions(int Pos,bool Value)
{
  if (Pos>=0 && Pos<=1){
    Use_positions[Pos]=Value;
  }
}

/*************************************************************************/

bool _window::use_positions(int Pos)
{
  if (Pos>=0 && Pos<=1){
    return Use_positions[Pos];
  }

  return false;
}

/*************************************************************************/

void _window::elements_create_some_maps()
{
  if (Num_active_positions>0){
    if (Vec_names_of_selected_elements.size()>0){
      int Count_progress=0;
      QProgressDialog Progress("Computing...", "Abort",0,Vec_names_of_selected_elements.size(),this);
      Progress.setWindowModality(Qt::WindowModal);
      Progress.setMinimumDuration(0);
      Progress.setCancelButton(0);

      for (unsigned int i=0;i<Vec_names_of_selected_elements.size();i++){
        Progress.setValue(Count_progress++);
        if (Progress.wasCanceled()) break;

        switch(Interpolation_type){
          case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_HYPERCUBE_DISTANCE:
          case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_2D_CARTESIAN_DISTANCE:
            add_layer_map_minimum_hypercube_distance(Name_selected_image,Vec_names_of_selected_elements[i],View_name,Color_model,Use_colors,Use_positions,Distance_normalization, Position_normalization_type,Probe,Palette,Data_type_print,Color_for_zero_value,Map_name_to_element);
          break;
          case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_RBF:
            add_layer_map_rbf_interpolation(Name_selected_image,Vec_names_of_selected_elements[i],View_name,Color_model,Palette,Data_type_print,Color_for_zero_value, Map_name_to_element);
          break;
          case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_TRIANGULATION:
            add_layer_map_triangulation(Name_selected_image,Vec_names_of_selected_elements[i],View_name,Color_model,Palette,Triangulation_add_corners,Data_type_print,Color_for_zero_value, Map_name_to_element);
          break;
          default:break;
        }
      }

      Progress.setValue(Vec_names_of_selected_elements.size());
    }
    else{
       QMessageBox::warning(this,tr("Warning"),tr("There are not elements"));
    }
  }
  else{
    QMessageBox::warning(this,tr("Warning"),"There must be at least one valid position");
  }
}

/*************************************************************************/

void _window::elements_create_all_maps()
{
  if (Num_active_positions>0){
    if (Vec_element_names.size()>0){
      int Count_progress=0;
      QProgressDialog Progress("Computing...", "Abort",0,Vec_element_names.size(),this);
      Progress.setWindowModality(Qt::WindowModal);
      Progress.setMinimumDuration(0);
      Progress.setCancelButton(0);

      for (unsigned int i=0;i<Vec_element_names.size();i++){
        Progress.setValue(Count_progress++);
        if (Progress.wasCanceled()) break;

        switch(Interpolation_type){
          case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_HYPERCUBE_DISTANCE:
          case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_2D_CARTESIAN_DISTANCE:
            add_layer_map_minimum_hypercube_distance(Name_selected_image,Vec_element_names[i],View_name,Color_model,Use_colors,Use_positions,Distance_normalization, Position_normalization_type,Probe,Palette,Data_type_print,Color_for_zero_value,Map_name_to_element);
          break;
          case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_RBF:
            add_layer_map_rbf_interpolation(Name_selected_image, Vec_element_names[i],View_name,Color_model,Palette,Data_type_print,Color_for_zero_value, Map_name_to_element);
          break;
          case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_TRIANGULATION:
            add_layer_map_triangulation(Name_selected_image,Vec_element_names[i],View_name,Color_model,Palette,Triangulation_add_corners,Data_type_print,Color_for_zero_value, Map_name_to_element);
          break;
          default:break;
        }
      }

      Progress.setValue(Vec_element_names.size());

    }
    else{
       QMessageBox::warning(this,tr("Warning"),tr("There are not elements"));
    }
  }
  else{
    QMessageBox::warning(this,tr("Warning"),"There must be at least one valid position");
  }
}

/*************************************************************************/

void _window::compounds_from_elements_create_some_maps()
{
  bool Found=false;
  std::map<std::string,int> Map_found_elements;
  std::string Element;
  int Num_atoms;

  // get the all the elements and num of atoms
  for (unsigned int i=0;i<Vec_compounds_from_elements_selected_names.size();i++){
    for (unsigned int j=0;j<Vec_compounds_from_elements_pdb.size();j++){
      if (Vec_compounds_from_elements_selected_names[i]==Vec_compounds_from_elements_pdb[j].Name){
        // add the elements
        for (unsigned int k=0;k<Vec_compounds_from_elements_pdb[j].Vec_elements_combination.size();k++){
          Element=Vec_compounds_from_elements_pdb[j].Vec_elements_combination[k].Element_name;
          Num_atoms=Vec_compounds_from_elements_pdb[j].Vec_elements_combination[k].Num_atoms;

          if (Map_found_elements.find(Element)==Map_found_elements.end()){
            Map_found_elements[Element]=Num_atoms;
          }
          else{
            Map_found_elements[Element]=Map_found_elements[Element]+Num_atoms;
          }
        }
      }
    }
  }

  QProgressDialog Progress("Computing...", "Abort",0,Vec_compounds_from_elements_selected_names.size(),this);
  Progress.setWindowModality(Qt::WindowModal);
  Progress.setMinimumDuration(0);
  Progress.setCancelButton(0);

  for (unsigned int i=0;i<Vec_compounds_from_elements_selected_names.size();i++){
    Progress.setValue(i);
    if (Progress.wasCanceled()) break;

    std::vector<float> Vec_global_percentages;

    // get the elements of the compound
    // a compound is valid if all the elements have a corresponding map
    // the name of the layer is saved to access its data
    std::vector<std::string> Vec_names_in_map;
    int Num_atoms_global;
    for (unsigned int j=0;j<Vec_compounds_from_elements_pdb.size();j++){
      // find the selected Compound in the PDB
      if (Vec_compounds_from_elements_selected_names[i]==Vec_compounds_from_elements_pdb[j].Name){
      // check that all the elements are present as maps by looking the name of the element of the map
        for (unsigned int k=0;k<Vec_compounds_from_elements_pdb[j].Vec_elements_combination.size();k++){
          Found=false;
          for (auto It=Map_name_to_layer.begin();It!=Map_name_to_layer.end();It++){
            // if the Element is found pass to the next one
            if (It->second.Pigment_name==Vec_compounds_from_elements_pdb[j].Vec_elements_combination[k].Element_name){
              Found=true;
              Vec_names_in_map.push_back(It->first);
              Num_atoms_global=Map_found_elements[Vec_compounds_from_elements_pdb[j].Vec_elements_combination[k].Element_name];
              Num_atoms=Vec_compounds_from_elements_pdb[j].Vec_elements_combination[k].Num_atoms;
              Vec_global_percentages.push_back(float(Num_atoms)/float(Num_atoms_global));
              break;
            }
          }
          if (Found==false) break;
        }
        if (Found==true){
          add_layer_compound_combination(Name_selected_image,Vec_compounds_from_elements_pdb[j].Name,View_name,Vec_compounds_from_elements_pdb[j].Vec_elements_combination,Vec_names_in_map, Vec_global_percentages, Palette, Data_type_print,Color_for_zero_value);
        }

        break;
      }
    }
  }

  Progress.setValue(Vec_compounds_from_elements_pdb.size());
}

/*************************************************************************/

void _window::compounds_from_elements_create_all_maps()
{
  bool Found=false;

  QProgressDialog Progress("Computing...", "Abort",0,Vec_compounds_from_elements_pdb.size(),this);
  Progress.setWindowModality(Qt::WindowModal);
  Progress.setMinimumDuration(0);
  Progress.setCancelButton(0);

  // check for all the PDB compounds
  for (unsigned int i=0;i<Vec_compounds_from_elements_pdb.size();i++){
    Progress.setValue(i);
    if (Progress.wasCanceled()) break;

    // get the elements of the compound
    // a compound is valid if all the elements have a corresponding map
    // the name of the layer is saved to access its data
    std::vector<std::string> Vec_names_in_map;
    for (unsigned int j=0;j<Vec_compounds_from_elements_pdb[i].Vec_elements_combination.size();j++){
      // check that all the elements are present as maps by looking the name of the element of the map
      Found=false;
      for (auto It=Map_name_to_layer.begin();It!=Map_name_to_layer.end();It++){
        // if the Element is found pass to the next one
        if (It->second.Pigment_name==Vec_compounds_from_elements_pdb[i].Vec_elements_combination[j].Element_name){
          Found=true;
          Vec_names_in_map.push_back(It->first);
          break;
        }
      }
      if (Found==false) break;
    }

    if (Found==true){
      // All the elements of the compound have map

      std::vector<float> Vec_global_percentages(Vec_names_in_map.size(),1.0f);

      add_layer_compound_combination(Name_selected_image,Vec_compounds_from_elements_pdb[i].Name,View_name,Vec_compounds_from_elements_pdb[i].Vec_elements_combination,Vec_names_in_map, Vec_global_percentages, Palette, Data_type_print,Color_for_zero_value);
    }
  }

  Progress.setValue(Vec_compounds_from_elements_pdb.size());
}

/*************************************************************************/

void _window::compute_mean_distance_between_positions()
{
  float Max_distance=-1;
  float Distance_aux;
  int Num_pos=0;

  for (unsigned int i=0;i<Project_data.Vec_coordinate_x_original.size()-1;i++){
    if (Vec_active_positions[i]==true){
      for (unsigned int j=i+1;j<Project_data.Vec_coordinate_x_original.size();j++){
        if (Vec_active_positions[j]==true){
          Distance_aux=sqrtf(powf((Project_data.Vec_coordinate_x_original[i]-Project_data.Vec_coordinate_x_original[j]),2)+powf((Project_data.Vec_coordinate_y_original[i]-Project_data.Vec_coordinate_y_original[j]),2));
          if (Distance_aux>Max_distance){
            Max_distance=Distance_aux;
            Num_pos++;
          }
        }
      }
    }
  }

  Mean_distance_between_positions=Max_distance/float(Num_pos);
}

/*************************************************************************/

void _window::compute_mean_distance_between_neighbors_positions()
{
  float Max_distance=-1;
  int P1=0,P2=0,P3=0;

  if (Triangles.size()>0){
    for (unsigned int Triangle=0;Triangle<Triangles.size();Triangle++){
      P1=Triangles[Triangle].P1;
      P2=Triangles[Triangle].P2;
      P3=Triangles[Triangle].P3;

      Max_distance+=sqrtf(powf((Project_data.Vec_coordinate_x_original[P1]-Project_data.Vec_coordinate_x_original[P2]),2)+powf((Project_data.Vec_coordinate_y_original[P1]-Project_data.Vec_coordinate_y_original[P2]),2));

      Max_distance+=sqrtf(powf((Project_data.Vec_coordinate_x_original[P2]-Project_data.Vec_coordinate_x_original[P3]),2)+powf((Project_data.Vec_coordinate_y_original[P2]-Project_data.Vec_coordinate_y_original[P3]),2));

      Max_distance+=sqrtf(powf((Project_data.Vec_coordinate_x_original[P3]-Project_data.Vec_coordinate_x_original[P1]),2)+powf((Project_data.Vec_coordinate_y_original[P3]-Project_data.Vec_coordinate_y_original[P1]),2));
    }

    Mean_distance_between_neighbors_positions=Max_distance/float(Triangles.size()*3*2);
  }
  else{
    // There are 1 or 2 valid points.
    if (Num_active_positions==1){
      Mean_distance_between_neighbors_positions=float(max_dimension());
    }
    else{
      // search for the first valid position
      unsigned int i;
      for (i=0;i<Vec_active_positions.size();i++){
        if (Vec_active_positions[i]==true){
          P1=i;
          break;
        }
      }

      // now the second one
      for (i=i+1;i<Vec_active_positions.size();i++){
        if (Vec_active_positions[i]==true){
          P2=i;
          break;
        }
      }

      // half of the distance between points
      Mean_distance_between_neighbors_positions=sqrtf(powf((Project_data.Vec_coordinate_x_original[P1]-Project_data.Vec_coordinate_x_original[P2]),2)+powf((Project_data.Vec_coordinate_y_original[P1]-Project_data.Vec_coordinate_y_original[P2]),2))/2.0f;
    }
  }
}
