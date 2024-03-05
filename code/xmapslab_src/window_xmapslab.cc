/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "window_xmapslab.h"
#include "window_main.h"

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

_window_xmapslab::_window_xmapslab(_window_main *Window_main1)
{
#ifdef DEBUG_XML
  std::cout << "en _window_xmaplab " << __LINE__ << std::endl;
#endif

  Window_main=Window_main1;

  // the dimensions of the main window
  QRect Screen_size = QApplication::primaryScreen()->geometry();
  Screen_width=Screen_size.width();
  Screen_height=Screen_size.height();

  // the default font size
  QFont Font=QApplication::font();
  UI_font_size=Font.pointSize();

  // structure
  // Splitter --> Splitter_edit ----> Color + Splitter_view + Tab
  //          |-> Splitter_node_editor                      |-> GL + GL_3D

  Splitter_view=new _splitter(Qt::Vertical);
//  Splitter_view->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

  connect(Splitter_view,SIGNAL(splitterMoved(int,int)),this,SLOT(splitter_moved_slot(int,int)));

  Splitter_view_2D_3D=new _splitter(Qt::Horizontal);

  Splitter_edit=new _splitter(Qt::Horizontal);
  Splitter_edit->setContentsMargins(0, 0, 0, 0);

#ifdef NODE_EDITOR_ACTIVE
  Splitter_node_editor = new QSplitter(Qt::Horizontal);
#endif

  Splitter=new _splitter(Qt::Horizontal);

//  QSizePolicy Q(QSizePolicy::Expanding,QSizePolicy::Expanding);

  initialize_palettes_data();

  //
#ifdef NODE_EDITOR_ACTIVE
  create_nodes_editor_widget();
#endif

  GL_widget = new _gl_widget_xmapslab(this);

  Color_bar_widget=new _w_color_bar(this);

  Tab_widget=new _w_tab_xmapslab(this);

#ifdef MODE_3D_ACTIVE
  GL_widget_3D=new _gl_widget_xmapslab_3D(this);
//  GL_widget_3D->setSizePolicy(Q);
  GL_widget_3D->setMinimumSize(400,400);
  GL_widget_3D->hide();
//    GL_widget_3D->show();
#endif

  Splitter_view_2D_3D->addWidget(GL_widget);
#ifdef MODE_3D_ACTIVE
  Splitter_view_2D_3D->addWidget(GL_widget_3D);
#endif

  // add the widgets
//    Splitter_view->addWidget(GL_widget);
  Splitter_view->addWidget(Splitter_view_2D_3D);

  Splitter_edit->addWidget(Color_bar_widget);
  Splitter_edit->addWidget(Splitter_view);
  Splitter_edit->addWidget(Tab_widget);

  connect(static_cast<_splitter_handle *>(Splitter_edit->handle(1)),SIGNAL(double_click()),this,SLOT(left_handle_slot()));
  connect(static_cast<_splitter_handle *>(Splitter_edit->handle(2)),SIGNAL(double_click()),this,SLOT(right_handle_slot()));

  Splitter->addWidget(Splitter_edit);
#ifdef NODE_EDITOR_ACTIVE
  Splitter->addWidget(Splitter_node_editor);
#endif

  setCentralWidget(Splitter);

  QFont Font1(font());
  Font.setPointSize(40);

  // menu
  Load_project = new QAction(QIcon(":/common/icons/fileopen.png"), tr("Load project data"), this);
  Load_project->setShortcuts(QKeySequence::Open);
  Load_project->setToolTip(tr("Load project"));
  connect(Load_project, SIGNAL(triggered()), this, SLOT(load_project_data_slot()));

#ifndef UNIFIED
  Close_project = new QAction(tr("Close project"), this);
  Close_project->setShortcuts(QKeySequence::Close);
  Close_project->setToolTip(tr("Close project"));
  Close_project->setEnabled(false);
  connect(Close_project, SIGNAL(triggered()), this, SLOT(close_project_slot()));
#endif

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

#ifdef NODE_EDITOR_ACTIVE
  // Save_ge_image = new QAction(QIcon(":/common/icons/filesave.png"), tr("Save G-E image"), this);
  // Save_ge_image->setToolTip(tr("Save G-E image"));
  // Save_ge_image->setEnabled(false);
  // connect(Save_ge_image, SIGNAL(triggered()), this, SLOT(save_ge_image_slot()));
#endif

  Save_composed_image = new QAction(QIcon(":/common/icons/filesave.png"), tr("Save composed image"), this);
  Save_composed_image->setToolTip(tr("Save composed image"));
  Save_composed_image->setEnabled(false);
  connect(Save_composed_image, SIGNAL(triggered()), this, SLOT(save_composed_image_slot()));

  // image section
  Action_activate_image_section = new QAction(tr("Activate image section"), this);
  Action_activate_image_section->setEnabled(false);
  Action_activate_image_section->setCheckable(true);
  Action_activate_image_section->setChecked(false);
  connect(Action_activate_image_section, SIGNAL(triggered()), this, SLOT(activate_image_section_slot()));

  Save_image_section = new QAction(QIcon(":/common/icons/filesave.png"), tr("Save image section"), this);
  Save_image_section->setToolTip(tr("Save image section"));
  Save_image_section->setEnabled(false);
  connect(Save_image_section, SIGNAL(triggered()), this, SLOT(save_image_section_slot()));

  Options = new QAction(tr("&Options"), this);
  Options->setToolTip(tr("Set the options"));
  Options->setEnabled(false);
  connect(Options, SIGNAL(triggered()), this, SLOT(options_slot()));

  QAction *Exit = new QAction(QIcon(":/common/icons/exit.png"), tr("&Exit"), this);
  Exit->setShortcut(tr("Ctrl+Q"));
  Exit->setToolTip(tr("Exit the application"));
  connect(Exit, SIGNAL(triggered()), Window_main, SLOT(close()));

  // actions for view
  QAction *Action=new QAction(tr("&Normal"), this);
  Action->setCheckable(true);
  Action->setChecked(true);
  connect(Action, SIGNAL(triggered()), this, SLOT(normal_slot()));
  View.push_back(Action);

#ifdef STATISTIC_GRAPHS_ACTIVE
  Action=new QAction(tr("&Char bars"), this);
  Action->setCheckable(true);
  Action->setChecked(false);
  connect(Action, SIGNAL(triggered()), this, SLOT(chart_bar_slot()));
  View.push_back(Action);

  Action=new QAction(tr("&Char lines"), this);
  Action->setCheckable(true);
  Action->setChecked(false);
  connect(Action, SIGNAL(triggered()), this, SLOT(chart_line_slot()));
  View.push_back(Action);

  Action=new QAction(tr("&Char pie"), this);
  Action->setCheckable(true);
  Action->setChecked(false);
  connect(Action, SIGNAL(triggered()), this, SLOT(chart_pie_slot()));
  View.push_back(Action);

  Action=new QAction(tr("&Histogram"), this);
  Action->setCheckable(true);
  Action->setChecked(false);
  connect(Action, SIGNAL(triggered()), this, SLOT(histogram_slot()));
  View.push_back(Action);
#endif

#ifdef NODE_EDITOR_ACTIVE
  Action=new QAction(tr("&Laboratory"), this);
  Action->setCheckable(true);
  Action->setChecked(false);
  connect(Action, SIGNAL(triggered()), this, SLOT(laboratory_slot()));
  View.push_back(Action);
#endif

#ifdef MODE_3D_ACTIVE
  Action=new QAction(tr("View 3D"), this);
  Action->setCheckable(true);
  Action->setChecked(false);
  connect(Action, SIGNAL(triggered()), this, SLOT(view3D_slot()));
  View.push_back(Action);
#endif

  for (unsigned int i=1;i<View.size();i++) View[i]->setEnabled(false);

  QActionGroup *View_group = new QActionGroup(this);
  for (unsigned int i=0;i<View.size();i++) View_group->addAction(View[i]);

  // adjustment
#ifdef STATISTIC_GRAPHS_ACTIVE
  View_linear_adjust = new QAction(tr("&Linear adjust"), this);
  View_linear_adjust->setCheckable(true);
  View_linear_adjust->setChecked(true);
  View_linear_adjust->setEnabled(false);
  connect(View_linear_adjust, SIGNAL(triggered()), this, SLOT(linear_adjust_slot()));

  View_log_adjust = new QAction(tr("&Logarithmic adjust"), this);
  View_log_adjust->setCheckable(true);
  View_log_adjust->setChecked(false);
  View_log_adjust->setEnabled(false);
  connect(View_log_adjust, SIGNAL(triggered()), this, SLOT(logarithmic_adjust_slot()));

  QActionGroup *Adjustment_group = new QActionGroup(this);
  Adjustment_group->addAction(View_linear_adjust);
  Adjustment_group->addAction(View_log_adjust);
#endif

  // actions for file menu
#ifndef UNIFIED
  QAction *Help_info = new QAction(tr("&Info"), this);
  connect(Help_info, SIGNAL(triggered()), this, SLOT(info_slot()));
#endif

  // menus
  QMenu *File_menu=menuBar()->addMenu(tr("&File"));

  File_menu->addAction(Load_project);
#ifndef UNIFIED
  File_menu->addAction(Close_project);
#endif
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
#ifdef NODE_EDITOR_ACTIVE
  // File_menu->addAction(Save_ge_image);??
  // File_menu->addSeparator();
#endif
  File_menu->addAction(Save_composed_image);
  File_menu->addSeparator();
  File_menu->addAction(Action_activate_image_section);
  File_menu->addAction(Save_image_section);
  File_menu->addSeparator();
  File_menu->addAction(Options);
  File_menu->addSeparator();
  File_menu->addAction(Exit);

  File_menu->setAttribute(Qt::WA_AlwaysShowToolTips);

  //
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

  // add actions to view_menu
  Menu_view=menuBar()->addMenu(tr("&View"));
  for (unsigned int i=0;i<View.size();i++) Menu_view->addAction(View[i]);
  Menu_view->addSeparator();
  Menu_view->addAction(View_show_positions);

  Submenu_add_show_triangulation=Menu_view->addMenu("Show triangulation");
//  Submenu_add_show_triangulation->setEnabled(false);
  Submenu_add_show_triangulation->addAction(View_show_triangulation_normal);
  Submenu_add_show_triangulation->addAction(View_show_triangulation_with_corners);

  Menu_view->setEnabled(false);

#ifndef UNIFIED
  QMenu *Menu_help=menuBar()->addMenu(tr("&Help"));
  Menu_help->addAction(Help_info);

  Menu_help->setAttribute(Qt::WA_AlwaysShowToolTips);

  setWindowTitle(_window_xmapslab_ns::Program_name);

#ifdef STATISTIC_GRAPHS_ACTIVE
  compute_histogram_colors();
#endif

  resize(Screen_width/2,Screen_height/2);
#endif

}

/*************************************************************************/

//void _window_xmapslab::ui_font_size(int Size)
//{
//  UI_font_size=Size;

//  QFont Font=QApplication::font();
//  Font.setPointSize(Size);
////  QApplication::setFont(Font);
//  setFont(Font);

//  menuBar()->setFont(Font);

//  // change the width of the color bar
//  Color_bar_widget->adjust_width(Project_data.Max_value);

//  update_color_bar();
//}

/*************************************************************************/

//void _window_xmapslab::pass_ui_font_size(int UI_font_size1)
//{
//  Window_main->ui_font_size(UI_font_size1);
//}

/*************************************************************************/

void _window_xmapslab::read_settings()
{
//  QSettings settings("./settings_"+_window_xmapslab_ns::Program_name.toLower()+".ini",QSettings::IniFormat);
  QSettings settings(Project_dir+"/settings.ini",QSettings::IniFormat);

  QStringList Allq=settings.allKeys();

  settings.beginGroup("XMapsLab");
    settings.beginGroup("MainWindow");
      Window_size=settings.value("size", QSize(_window_xmapslab_ns::WINDOW_WIDTH_DEFAULT,_window_xmapslab_ns::WINDOW_HEIGHT_DEFAULT)).toSize();
      Window_position=settings.value("pos", QPoint(_window_xmapslab_ns::WINDOW_X_POS_DEFAULT,_window_xmapslab_ns::WINDOW_Y_POS_DEFAULT)).toPoint();
    settings.endGroup();

    settings.beginGroup("Layer");
      Data_type_print=_palette_data_ns::_data_type_print(settings.value("DataTypePrint",int(_window_xmapslab_ns::DATA_TYPE_PRINT_DEFAULT)).toInt());
    settings.endGroup();

    settings.beginGroup("Maps");
      settings.beginGroup("XRF");
        XRF_interpolation_type=_layer_map_ns::_map_interpolation_methods(settings.value("XRFMapInterpolationType",_window_xmapslab_ns::MAP_INTERPOLATION_TYPE_DEFAULT).toInt());
        XRF_color_model=_common_ns::_color_model(settings.value("XRFColorModel",_window_xmapslab_ns::COLOR_MODEL_DEFAULT).toInt());
        XRF_use_colors[0]=settings.value("XRFUseColor1",_window_xmapslab_ns::USE_COLOR1_DEFAULT).toBool();
        XRF_use_colors[1]=settings.value("XRFUseColor2",_window_xmapslab_ns::USE_COLOR2_DEFAULT).toBool();
        XRF_use_colors[2]=settings.value("XRFUseColor3",_window_xmapslab_ns::USE_COLOR3_DEFAULT).toBool();
        XRF_use_positions[0]=settings.value("XRFUsePosition1",_window_xmapslab_ns::USE_POSITION1_DEFAULT).toBool();
        XRF_use_positions[1]=settings.value("XRFUsePosition2",_window_xmapslab_ns::USE_POSITION2_DEFAULT).toBool();
        XRF_distance_normalization=settings.value("XRFNormalization",_window_xmapslab_ns::NORMALIZATION_DEFAULT).toBool();
        XRF_position_normalization_type=_layer_map_distance_ns::_position_normalization_type(settings.value("XRFPositionNormalizationType",_window_xmapslab_ns::POSITION_NORMALIZATION_TYPE_DEFAULT).toInt());
        XRF_probe=settings.value("XRFProbe",_window_xmapslab_ns::PROBE_DEFAULT).toInt();
        XRF_RBF_function=_new_rbf_interpolation_2d_ns::_function_type(settings.value("XRFRBFFunction",int(_new_rbf_interpolation_2d_ns::FUNCTION_TYPE_DEFAULT)).toInt());
        XRF_triangulation_add_corners=settings.value("XRFTriangulationAddCorners",_window_xmapslab_ns::TRIANGULATION_ADD_CORNERS_DEFAULT).toBool();
      settings.endGroup();
      settings.beginGroup("XRD");
        XRD_interpolation_type=_layer_map_ns::_map_interpolation_methods(settings.value("XRDMapInterpolationType",_window_xmapslab_ns::MAP_INTERPOLATION_TYPE_DEFAULT).toInt());
        XRD_color_model=_common_ns::_color_model(settings.value("XRDColorModel",_window_xmapslab_ns::COLOR_MODEL_DEFAULT).toInt());
        XRD_use_colors[0]=settings.value("XRDUseColor1",_window_xmapslab_ns::USE_COLOR1_DEFAULT).toBool();
        XRD_use_colors[1]=settings.value("XRDUseColor2",_window_xmapslab_ns::USE_COLOR2_DEFAULT).toBool();
        XRD_use_colors[2]=settings.value("XRDUseColor3",_window_xmapslab_ns::USE_COLOR3_DEFAULT).toBool();
        XRD_use_positions[0]=settings.value("XRDUsePosition1",_window_xmapslab_ns::USE_POSITION1_DEFAULT).toBool();
        XRD_use_positions[1]=settings.value("XRDUsePosition2",_window_xmapslab_ns::USE_POSITION2_DEFAULT).toBool();
        XRD_distance_normalization=settings.value("XRDNormalization",_window_xmapslab_ns::NORMALIZATION_DEFAULT).toBool();
        XRD_position_normalization_type=_layer_map_distance_ns::_position_normalization_type(settings.value("XRDPositionNormalizationType",_window_xmapslab_ns::POSITION_NORMALIZATION_TYPE_DEFAULT).toInt());
        XRD_probe=settings.value("XRDProbe",_window_xmapslab_ns::PROBE_DEFAULT).toInt();
        XRD_RBF_function=_new_rbf_interpolation_2d_ns::_function_type(settings.value("XRDRBFFunction",int(_new_rbf_interpolation_2d_ns::FUNCTION_TYPE_DEFAULT)).toInt());
        XRD_triangulation_add_corners=settings.value("XRDTriangulationAddCorners",_window_xmapslab_ns::TRIANGULATION_ADD_CORNERS_DEFAULT).toBool();
      settings.endGroup();
    settings.endGroup();

    settings.beginGroup("Printing");
      Print_font_factor=settings.value("FontScaleFactor",_w_options_xmapslab_ns::PRINT_FONT_FACTOR_DEFAULT).toFloat();
    settings.endGroup();

    settings.beginGroup("Palette");
      Color_for_zero_value=_color_map_ns::_color_for_zero_value(settings.value("ColorZeroValue",int(_window_xmapslab_ns::COLOR_FOR_ZERO_VALUE_DEFAULT)).toInt());
    settings.endGroup();

  settings.endGroup();

//  settings.beginGroup("DisplayParameters");
//    Positions_display_font_size=settings.value("DisplayFontSize",_w_options_xmapslab_ns::POSITIONS_DISPLAY_FONT_SIZE_DEFAULT).toInt();
//    Positions_display_out_circle_size=settings.value("DisplayOutCircleSize",_w_options_xmapslab_ns::POSITIONS_DISPLAY_OUT_CIRCLE_SIZE_DEFAULT).toInt();
//    Positions_display_font_color=settings.value("DisplayFontColor",_w_options_xmapslab_ns::POSITIONS_DISPLAY_FONT_COLOR_DEFAULT).value<QColor>();
//    Positions_display_out_circle_color=settings.value("DisplayOutCircleColor",_w_options_xmapslab_ns::POSITIONS_DISPLAY_OUT_CIRCLE_COLOR_DEFAULT).value<QColor>();
//    Positions_display_in_circle_color=settings.value("DisplayInCircleColor",_w_options_xmapslab_ns::POSITIONS_DISPLAY_IN_CIRCLE_COLOR_DEFAULT).value<QColor>();
//    Positions_display_selection_out_circle_color=settings.value("DisplaySelectionOutCircleColor",_w_options_xmapslab_ns::POSITIONS_DISPLAY_SELECTION_OUT_CIRCLE_COLOR_DEFAULT).value<QColor>();
//    Positions_display_selection_in_circle_color=settings.value("DisplaySelectionInCircleColor",_w_options_xmapslab_ns::POSITIONS_DISPLAY_SELECTION_IN_CIRCLE_COLOR_DEFAULT).value<QColor>();
//  settings.endGroup();

//  settings.beginGroup("General");
//    UI_font_size=settings.value("UIFontSize",_common_ns::UI_FONT_SIZE_DEFAULT).toInt();
//  settings.endGroup();
}

/*************************************************************************/

void _window_xmapslab::save_settings()
{
//  QSettings settings("./settings_"+_window_xmapslab_ns::Program_name.toLower()+".ini",QSettings::IniFormat);
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
      settings.beginGroup("XRF");
        settings.setValue("XRFMapInterpolationType",int(XRF_interpolation_type));
        settings.setValue("XRFColorModel", int(XRF_color_model));
        settings.setValue("XRFUseColor1", bool(XRF_use_colors[0]));
        settings.setValue("XRFUseColor2", bool(XRF_use_colors[1]));
        settings.setValue("XRFUseColor3", bool(XRF_use_colors[2]));
        settings.setValue("XRFUsePosition1", bool(XRF_use_positions[0]));
        settings.setValue("XRFUsePosition2", bool(XRF_use_positions[1]));
        settings.setValue("XRFNormalization", XRF_distance_normalization);
        settings.setValue("XRFPositionNormalizationType", int(XRF_position_normalization_type));
        settings.setValue("XRFProbe", XRF_probe);
        settings.setValue("XRFTriangulationAddCorners",XRF_triangulation_add_corners);
        settings.setValue("XRFRBFFunction",int(XRF_RBF_function));
      settings.endGroup();
      settings.beginGroup("XRD");
        settings.setValue("XRDMapInterpolationType",int(XRD_interpolation_type));
        settings.setValue("XRDColorModel", int(XRD_color_model));
        settings.setValue("XRDUseColor1", bool(XRD_use_colors[0]));
        settings.setValue("XRDUseColor2", bool(XRD_use_colors[1]));
        settings.setValue("XRDUseColor3", bool(XRD_use_colors[2]));
        settings.setValue("XRDUsePosition1", bool(XRD_use_positions[0]));
        settings.setValue("XRDUsePosition2", bool(XRD_use_positions[1]));
        settings.setValue("XRDNormalization", XRD_distance_normalization);
        settings.setValue("XRDPositionNormalizationType", int(XRD_position_normalization_type));
        settings.setValue("XRDProbe", XRD_probe);
        settings.setValue("XRDTriangulationAddCorners",XRD_triangulation_add_corners);
        settings.setValue("XRDRBFFunction",int(XRD_RBF_function));
      settings.endGroup();
    settings.endGroup();

    settings.beginGroup("Printing");
      settings.setValue("FontScaleFactor",Print_font_factor);
    settings.endGroup();

    settings.beginGroup("Palette");
      settings.setValue("ColorZeroValue",int(Color_for_zero_value));
    settings.endGroup();

  settings.endGroup();

//  settings.beginGroup("DisplayParameters");
//  settings.setValue("DisplayFontSize", Window_main->display_font_size());
//  settings.setValue("DisplayOutCircleSize", Window_main->display_out_circle_size());
//  settings.setValue("DisplayFontColor", Window_main->display_font_color());
//  settings.setValue("DisplayOutCircleColor", Window_main->display_out_circle_color());
//  settings.setValue("DisplayInCircleColor", Window_main->display_in_circle_color());
//  settings.endGroup();

//  settings.beginGroup("General");
//    settings.setValue("UIFontSize",UI_font_size);
//  settings.endGroup();
}

/*************************************************************************/

//void _window_xmapslab::closeEvent(QCloseEvent *Event)
//{
//  save_settings();
//  Event->accept();
//}

/*************************************************************************/

void _window_xmapslab::initialize_palettes_data()
{
//  for (unsigned int i=0;i<_palette_data_ns::Vec_palette_data_aux.size();i++){
//    Vec_palette_data.push_back(_palette_data_ns::_palette_data(_palette_data_ns::Vec_palette_data_aux[i].Name,_palette_data_ns::Vec_palette_data_aux[i].Type,_palette_data_ns::Vec_palette_data_aux[i].Color_type,_palette_data_ns::Vec_palette_data_aux[i].Num_stops,_palette_data_ns::Vec_palette_data_aux[i].Color_assigning, compute_color(""),color_for_zero_value()));
//  }
}

/*************************************************************************/
// Load the images

void _window_xmapslab::load_images()
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
    if (Image->channels()<=3) cv::cvtColor(*Image.get(),*Image.get(),cv::COLOR_BGR2BGRA,4);

    if (Loaded_image==false){
      Loaded_image=true;

//        Vec_layers.clear();
//        Vec_textures.clear();
//      Map_name_to_layer.clear();
//      Vec_order_of_layers_by_name.clear();
//      Map_name_to_element.clear();

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

#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
 void _window_xmapslab::load_compounds_combination()
 {
   _data_io::load_compounds_combination_pdb(this,Vec_compounds_from_elements_pdb);
 }
#endif

/*************************************************************************/
// Normalizes the data

void _window_xmapslab::xrf_process_data(_pigment_data_ns::_pigment_data &Element_data)
{
  float Max_aux=*max_element(Element_data.Vec_values.begin(),Element_data.Vec_values.end());

  Element_data.Max_value=Max_aux;

  float Divisor=Max_aux;
  if (Max_aux==0) Divisor=1;

  // adjust the max value
//  if (Project_data.XRF_data_adjustment!=_data_xrf_ns::_xrf_data_adjustment::XRF_DATA_ADJUSTMENT_NONE){
//    // adjust
//    if (Project_data.XRF_data_adjustment==_data_xrf_ns::_xrf_data_adjustment::XRF_DATA_ADJUSTMENT_ATOMIC_NUMBER){
//      Element_data.Max_value_adjusted=Element_data.Max_value/Element_data.Atomic_number;
//    }
//    else{
//      Element_data.Max_value_adjusted=Element_data.Max_value/Element_data.Atomic_weight;
//    }
//  }
//  else{
//    Element_data.Max_value_adjusted=Element_data.Max_value;
//  }

  Element_data.Max_value_adjusted=Element_data.Max_value;

  for (unsigned int i=0;i<Element_data.Vec_values.size();i++){
    Element_data.Vec_values[i]=Element_data.Vec_values[i]/Divisor;
  }
}

/*************************************************************************/
// adjust the sample data dividing by the atomic number

#ifdef XRD_ACTIVE
void _window_xmapslab::xrd_process_data(_pigment_data_ns::_pigment_data &Compound_data)
{
  float Max_aux=*max_element(Compound_data.Vec_values.begin(),Compound_data.Vec_values.end());

  Compound_data.Max_value=Max_aux;
  Compound_data.Max_value_adjusted=Compound_data.Max_value;
  Compound_data.Xray_data_type=_common_ns::_xray_data_type::XRAY_DATA_TYPE_XRD;

  for (unsigned int i=0;i<Compound_data.Vec_values.size();i++){
    Compound_data.Vec_values[i]=Compound_data.Vec_values[i]/Max_aux;
  }
}
#endif

/*************************************************************************/

void _window_xmapslab::xrf_process_map_data()
{
  for (auto &Element : Map_name_to_element){
    float Atomic_number=-1.0f;
    float Atomic_weight=-1.0f;

    std::string Element_name=Element.first;

    auto It = _window_xmapslab_ns::Map_atomic_data.find(Element_name);

    if (It != _window_xmapslab_ns::Map_atomic_data.end()) {
      Atomic_number=It->second.Atomic_number;
      Atomic_weight=It->second.Atomic_weight;
    }

    if (Atomic_number==-1){
      QMessageBox::critical(this, tr("Error"),"The element "+QString::fromStdString(Element.first)+" does not exist");
      QApplication::quit();
      exit(-1);
    }

    Element.second.Atomic_number=Atomic_number;
    Element.second.Atomic_weight=Atomic_weight;
    Element.second.Xray_data_type=_common_ns::_xray_data_type::XRAY_DATA_TYPE_XRF;

    // adjust the values of the samples dividing by the atomic number
    xrf_process_data(Element.second);

    // insert in the map pair (name of the element or pigment data)
    Map_name_to_element.insert(std::pair<std::string,_pigment_data_ns::_pigment_data>(Element_name,_pigment_data_ns::_pigment_data(Element.second)));

    // add the element
    Tab_widget->add_xrf(Element_name);

    // save the name
    Vec_element_names.push_back(Element_name);
  }

  // add the information of compounds combination
#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
  for (unsigned int i=0;i<Vec_compounds_from_elements_pdb.size();i++){
    Tab_widget->add_compound_from_elements(Vec_compounds_from_elements_pdb[i].Name);
  }
#endif
}

/*************************************************************************/

#ifdef XRD_ACTIVE
void _window_xmapslab::xrd_process_map_data()
{
  for (auto &Compound : Map_name_to_compound){
    std::string Compound_name=Compound.first;

    // adjust the values of the samples dividing by the atomic number
    xrd_process_data(Compound.second);

    // insert in the map pair (name of the element or pigment data)
    Map_name_to_element.insert(std::pair<std::string,_pigment_data_ns::_pigment_data>(Compound_name,_pigment_data_ns::_pigment_data(Compound.second)));

    // add the compound or compound
    Tab_widget->add_xrd(Compound_name);

    // save the name
    Vec_compound_names.push_back(Compound_name);
  }
}
#endif

/*************************************************************************/
// Load the the data in MapLab format

void _window_xmapslab::load_data_csv_format(bool &XRF_data_loaded, bool &XRD_data_loaded)
{
  Q_UNUSED(XRD_data_loaded)

  std::string Material;
  std::vector<std::vector<float>> Values;
  std::string Error;
  std::string File_name;

  // maybe that the data is loaded for for firts time or reloaded
  // if it is reloaded, I have to save the previous state for positions
  std::vector<bool> Vec_active_positions_previous_state=Vec_active_positions;

  // first read the elements
  _data_io::xrf_load_pdb(this,Vec_xrf_pdb_data,Vec_xrf_pdb_names);

#ifdef XRD_ACTIVE
#ifdef SPECTRAL_MODE_ACTIVE
//  _data_io::xrd_load_pdb_spectral_names(this,_common_window_xmapslab_ns::FOLDER_PDB_XRD_SPECTRAL_CU,Vec_xrd_pdb_names);
//  _data_io::xrd_load_pdb_spectral_names(this,_common_window_xmapslab_ns::FOLDER_PDB_XRD_SPECTRAL_CO,Vec_xrd_pdb_names);
#endif
#ifdef ASTM_MODE_ACTIVE
//  _data_io::xrd_load_pdb_astm_names(this,Vec_xrd_pdb_names);
#endif
#endif

  // the names of the PDB elements and compounds are not necessary
  _data_io::load_project_data_csv(this,Project_dir.toStdString(),Project_data,Vec_xrf_pdb_names,Vec_xrd_pdb_names);

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

      Map_name_to_element[Element_name].Xray_data_type=_common_ns::_xray_data_type::XRAY_DATA_TYPE_XRF;

      Map_name_to_element[Element_name].Vec_values=vector<float>(Num_positions,0);

      for (int j=0;j<Num_positions;j++){
         Map_name_to_element[Element_name].Vec_values[j]=Project_data.Vec_xrf_interpreted_data[i].Vec_values[j];
      }
    }

    xrf_process_map_data();
  }

#ifdef XRD_ACTIVE
  if (Project_data.Vec_xrd_interpreted_data.size()>0){
    XRD_data_loaded=true;
    std::string Compound_name;

    for (unsigned int i=0;i<Project_data.Vec_xrd_interpreted_data.size();i++){
      Compound_name=Project_data.Vec_xrd_interpreted_data[i].Name;

      Map_name_to_compound[Compound_name].Xray_data_type=_common_ns::_xray_data_type::XRAY_DATA_TYPE_XRD;

      Map_name_to_compound[Compound_name].Vec_values=vector<float>(Num_positions,0);

      for (int j=0;j<Num_positions;j++){
         Map_name_to_compound[Compound_name].Vec_values[j]=Project_data.Vec_xrd_interpreted_data[i].Vec_values[j];
      }
    }

    xrd_process_map_data();
  }
#endif

  // compute the image with the positions of the samples
  add_layer_positions_image();

  // compute mean distance between positions
  compute_mean_distance_between_neighbors_positions();

  xrf_rbf_radius(Mean_distance_between_neighbors_positions/image_diagonal_size());
  xrd_rbf_radius(Mean_distance_between_neighbors_positions/image_diagonal_size());

  Tab_widget->set_rbf_epsilon(255);
}

/*************************************************************************/
// Load the the data in XLSX format

#ifdef XLSX_ACTIVE
void _window_xmapslab::load_data_xlsx_format(bool& XRF_data_loaded,bool& XRD_data_loaded)
{
  _file_xlsx File_xlsx;
  std::string Material;
  std::vector<vector<float>> Values;
  std::string Error;
  std::string File_name;
//  _project_data_csv_ns::_project_data_csv Project_data_csv;

  // maybe that the data is loaded for for firts time or reloaded
  // if it is reloaded, I have to save the previous state for positions
  std::vector<bool> Vec_active_positions_previous_state=Vec_active_positions;

  _data_io::load_info_txt(this,Project_dir,Project_data);

//  _data_io::load_xrf_pdb(this,Vec_xrf_pdb_data,Vec_xrf_pdb_names);
//  _data_io::load_xrd_pdb(this,Vec_xrd_pdb_data,Vec_xrd_pdb_names);

  _data_io::load_positions_txt(this,Project_dir,Project_data);

  // Num of valid positions is equal to the number of read positions
  Num_active_positions=Project_data.Vec_coordinate_x_original.size();

  // XRF
  if (_data_io::load_xrf_interpreted_xlsx(this,Project_dir,Project_data.Vec_xrf_interpreted_data,Vec_xrf_pdb_names)==true){

    // the data is loaded. Check against the number of positions
    if (Project_data.Vec_xrf_interpreted_data.size()>0){
      if (Project_data.Vec_coordinate_x_original.size()<Project_data.Vec_xrf_interpreted_data[0].Vec_values.size()){
        // there are less points than values
        QMessageBox::warning(this, tr("Warning"),"There are less positions than intensities: "+QString("%1").arg(Project_data.Vec_coordinate_x_original.size())+" / "+QString("%1").arg(Project_data.Vec_xrf_interpreted_data[0].Vec_values.size())+"\n The exceding ones have been removed");

  //          msg.setStyleSheet("QLabel{min-width: 700px;}");
        for (unsigned int i=0;i<Project_data.Vec_xrf_interpreted_data.size();i++){
          Project_data.Vec_xrf_interpreted_data[i].Vec_values.resize(Project_data.Vec_coordinate_x_original.size());
        }
      }
      else{
        // there are more points than values
        if (Project_data.Vec_coordinate_x_original.size()>Project_data.Vec_xrf_interpreted_data[0].Vec_values.size()){
          QMessageBox::warning(this, tr("Warning"),"There are more positions than intensities: "+QString("%1").arg(Project_data.Vec_coordinate_x_original.size())+" / "+QString("%1").arg(Project_data.Vec_xrf_interpreted_data[0].Vec_values.size())+"\n The missing values have added (as 0)");

          for (unsigned int i=0;i<Project_data.Vec_xrf_interpreted_data.size();i++){
            Project_data.Vec_xrf_interpreted_data[i].Vec_values.resize(Project_data.Vec_coordinate_x_original.size(),0.0);
          }
        }
      }
    }
  }

  // XRD
  if (_data_io::load_xrd_interpreted_xlsx(this,Project_dir,Project_data.Vec_xrd_interpreted_data,Vec_xrd_pdb_names)==true){

    // the data is loaded. Check against the number of positions
    if (Project_data.Vec_xrd_interpreted_data.size()>0){
      if (Project_data.Vec_coordinate_x_original.size()<Project_data.Vec_xrd_interpreted_data[0].Vec_values.size()){
        // there are less points than values
        QMessageBox::warning(this, tr("Warning"),"There are less positions than intensities: "+QString("%1").arg(Project_data.Vec_coordinate_x_original.size())+" / "+QString("%1").arg(Project_data.Vec_xrd_interpreted_data[0].Vec_values.size())+"\n The exceding ones have been removed");

  //          msg.setStyleSheet("QLabel{min-width: 700px;}");
        for (unsigned int i=0;i<Project_data.Vec_xrd_interpreted_data.size();i++){
          Project_data.Vec_xrd_interpreted_data[i].Vec_values.resize(Project_data.Vec_coordinate_x_original.size());
        }
      }
      else{
        // there are more points than values
        if (Project_data.Vec_coordinate_x_original.size()>Project_data.Vec_xrd_interpreted_data[0].Vec_values.size()){
          QMessageBox::warning(this, tr("Warning"),"There are more positions than intensities: "+QString("%1").arg(Project_data.Vec_coordinate_x_original.size())+" / "+QString("%1").arg(Project_data.Vec_xrd_interpreted_data[0].Vec_values.size())+"\n The missing values have added (as 0)");

          for (unsigned int i=0;i<Project_data.Vec_xrd_interpreted_data.size();i++){
            Project_data.Vec_xrd_interpreted_data[i].Vec_values.resize(Project_data.Vec_coordinate_x_original.size(),0.0);
          }
        }
      }
    }
  }

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
  if (Project_data.Vec_xrf_interpreted_data.size()>0){
    XRF_data_loaded=true;
    int Num_positions=Project_data.Vec_coordinate_x.size();
    std::string Element_name;

    for (unsigned int i=0;i<Project_data.Vec_xrf_interpreted_data.size();i++){
      Element_name=Project_data.Vec_xrf_interpreted_data[i].Name;

      Map_name_to_element[Element_name].Vec_values=vector<float>(Num_positions,0);

      for (int j=0;j<Num_positions;j++){
         Map_name_to_element[Element_name].Vec_values[j]=Project_data.Vec_xrf_interpreted_data[i].Vec_values[j];
      }
    }

    xrf_process_map_data();
  }

#ifdef XRD_ACTIVE
  if (Project_data.Vec_xrd_interpreted_data.size()>0){
    XRD_data_loaded=true;

    int Num_positions=Project_data.Vec_coordinate_x.size();
    std::string Compound_name;

    for (unsigned int i=0;i<Project_data.Vec_xrd_interpreted_data.size();i++){
      Compound_name=Project_data.Vec_xrd_interpreted_data[i].Name;

      Map_name_to_compound[Compound_name].Vec_values=vector<float>(Num_positions,0);

      for (int j=0;j<Num_positions;j++){
         Map_name_to_compound[Compound_name].Vec_values[j]=Project_data.Vec_xrd_interpreted_data[i].Vec_values[j];
      }
    }

    xrd_process_map_data();
  }
#endif

  // compute the image with the positions of the samples
  add_layer_positions_image();

  // compute mean distance between positions
//  compute_mean_distance_between_positions();
  compute_mean_distance_between_neighbors_positions();

  // the max epsilon are 5 mean_distances
  int Value=255;
  Tab_widget->set_rbf_epsilon(Value);

  rbf_radius(Mean_distance_between_neighbors_positions/image_diagonal_size());
}
#endif

/*************************************************************************/

void _window_xmapslab::add_layer_positions_image()
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

  Point.x=Project_data.Width_pixel-1;
  Point.y=0;
  Point.Position=Pos;
  Points.push_back(Point);
  Vec_coordinate_x_corners.push_back(Project_data.Width_pixel-1);
  Vec_coordinate_y_corners.push_back(0);
  Pos++;

  Point.x=0;
  Point.y=Project_data.Height_pixel-1;
  Point.Position=Pos;
  Points.push_back(Point);
  Vec_coordinate_x_corners.push_back(0);
  Vec_coordinate_y_corners.push_back(Project_data.Height_pixel-1);
  Pos++;

  Point.x=Project_data.Width_pixel-1;
  Point.y=Project_data.Height_pixel-1;
  Point.Position=Pos;
  Points.push_back(Point);
  Vec_coordinate_x_corners.push_back(Project_data.Width_pixel-1);
  Vec_coordinate_y_corners.push_back(Project_data.Height_pixel-1);
  Pos++;

   _delaunay_triangulator_ns::_delaunay_triangulator Triangulator1;

  Triangles_with_corners=Triangulator1.triangulate(Points);

  // add
//  cout << "Num_triangles en window=" << Triangles.size() << endl;

  // check if the layer exists
  std::shared_ptr<_layer_positions_xmapslab_ui> Layer_positions=nullptr;
  if (Map_name_to_layer.find("Positions")==Map_name_to_layer.end()){
    Layer_positions=std::make_shared<_layer_positions_xmapslab_ui>(this,"Positions");
  }
  else{
    Layer_positions=std::static_pointer_cast<_layer_positions_xmapslab_ui>(Map_name_to_layer["Positions"].Layer);
    // remove the old texture
    // GL_widget->del_texture(Map_name_to_layer["Positions"].Texture);????
    // Map_name_to_layer["Positions"].Texture=0;
  }

  // the data of the element. ALWAYS THE FIRST ONE
  Layer_positions->add_valid_coordinates(Vec_active_positions);
  Layer_positions->add_coordinates(Project_data.Vec_coordinate_x,Project_data.Vec_coordinate_y);
  Layer_positions->add_coordinates_with_corners(Vec_coordinate_x_corners,Vec_coordinate_y_corners);

  Layer_positions->cs_origin(Project_data.CS_origin);
  Layer_positions->size(Project_data.Width_pixel,Project_data.Height_pixel);
  Layer_positions->triangles(Triangles);
  Layer_positions->triangles_with_corners(Triangles_with_corners);

  Layer_positions->parameters(Window_main->display_font_size(), Window_main->display_out_circle_size(), Window_main->display_font_color(), Window_main->display_out_circle_color(), Window_main->display_in_circle_color());

  Layer_positions->update();
  Map_name_to_layer["Positions"].Layer=Layer_positions;
  Map_name_to_layer["Positions"].Texture=GL_widget->set_texture(Layer_positions->image());
}

/*************************************************************************/

void _window_xmapslab::load_project()
{
  int Pos=Project_dir.lastIndexOf('/');
  Project_name=Project_dir.right(Project_dir.size()-Pos-1);

  if (First_load==true){
    First_load=false;

    read_settings();

    // create_nodes_editor_widget();????

    // load fixed palettes
    _data_io::load_colormaps_csv(this,"common/colormaps", Map_fixed_palettes);

    // initialize the widgets with correct data
    Color_bar_widget->initialize();
    Tab_widget->initialize();

    //
    QFont Font=QApplication::font();
    Font.setPointSize(UI_font_size);
    QApplication::setFont(Font);
  }

  close_project_slot();

  // load the images in the folder
  load_images();

  // load the compounds_combination PDB
#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
  load_compounds_combination();
#endif

  // create the basic layer for 3D view
#ifdef MODE_3D_ACTIVE
  GL_widget_3D->show();
  GL_widget_3D->create_object(Map_name_to_layer[Vec_order_of_layers_by_name[0]].Layer->image()->cols,Map_name_to_layer[Vec_order_of_layers_by_name[0]].Layer->image()->rows,200,Map_name_to_layer[Vec_order_of_layers_by_name[0]].Layer->image(),nullptr);
  GL_widget_3D->hide();
#endif

  // load data
  QFileInfo Check_file(Project_dir+"/"+QString::fromStdString(_common_window_ns::FILE_PROJECT_DATA));
  if (Check_file.exists()==true){
    load_data_csv_format(XRF_data_loaded,XRD_data_loaded);
  }
  else{
    QMessageBox::critical(this, tr("Error"),tr("There is not 'data.csv' file"));
    QApplication::quit();
    exit(-1);
  }

  // update the positions
  Tab_widget->add_active_positions(Vec_active_positions);

  if (XRF_data_loaded==true || XRD_data_loaded==true){
    // enable tabs
    Tab_widget->setTabEnabled(Tab_widget->pos_of_tab(_w_tab_xmapslab_ns::_tabs::POSITIONS_TAB),true);
    Tab_widget->setTabEnabled(Tab_widget->pos_of_tab(_w_tab_xmapslab_ns::_tabs::LAYERS_TAB),true);

    if (XRF_data_loaded==true){
      Tab_widget->setTabEnabled(int(_w_tab_xmapslab_ns::_tabs::ELEMENTS_TAB),true);
#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
      Tab_widget->setTabEnabled(Tab_widget->pos_of_tab(_w_tab_xmapslab_ns::_tabs::COMPOUNDS_FROM_XRF_TAB),true);
#endif
    }
    else{
      Tab_widget->setTabEnabled(Tab_widget->pos_of_tab(_w_tab_xmapslab_ns::_tabs::ELEMENTS_TAB),false);
#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
      Tab_widget->setTabEnabled(Tab_widget->pos_of_tab(_w_tab_xmapslab_ns::_tabs::COMPOUNDS_FROM_XRF_TAB),false);
#endif
    }

    if (XRD_data_loaded==true){
      Tab_widget->setTabEnabled(Tab_widget->pos_of_tab(_w_tab_xmapslab_ns::_tabs::COMPOUNDS_XRD_TAB),true);
    }
    else{
      Tab_widget->setTabEnabled(Tab_widget->pos_of_tab(_w_tab_xmapslab_ns::_tabs::COMPOUNDS_XRD_TAB),false);
    }

    // change widgets
//    Tab_widget->changed_interpolation_type_slot(int(Interpolation_type)); ????

    // change states
    Tab_widget->xrf_change_buttons_state(true);
#ifdef XRD_ACTIVE
    Tab_widget->xrd_change_buttons_state(true);
#endif

    // show the loaded xrf files
    Selected_tab=_w_tab_xmapslab_ns::_tabs::POSITIONS_TAB;
    Tab_widget->setCurrentIndex(int(Selected_tab));

    Menu_view->setEnabled(true);

    GL_widget->setEnabled(true);
//    Load_project->setEnabled(false);
//    Reload_project->setEnabled(true);
//    Close_project->setEnabled(true);

    //
    Submenu_save_single_layer->setEnabled(true);
    Save_single_layer->setEnabled(true);
//    Save_single_layer_with_color_bar->setEnabled(true);

    Submenu_save_all_layers->setEnabled(true);
    Save_all_layers->setEnabled(true);
//    Save_all_layers_with_color_bar->setEnabled(true);

    Save_composed_image->setEnabled(true);

    //Action_activate_image_section->setEnabled(true)
    //Save_image_section->setEnabled(true);

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

#ifndef UNIFIED
/*************************************************************************/
// load the data

void _window_xmapslab::load_project_data_slot()
{
  _w_directory Dialog(this,"projects",&Project_name);

  if (Dialog.exec()==QDialog::Accepted && Project_name!=""){
    QDir Dir(Project_name);
    Project_dir=Dir.absolutePath();

    load_project();

    if (First_load==true){
      resize(Window_size);
      move(Window_position);
    }

    First_load=false;
  }
}
#else
void _window_xmapslab::load_project_data_slot()
{
  load_project();

  if (First_load==true){
    resize(Window_size);
    move(Window_position);
  }

  First_load=false;
}
#endif

/*************************************************************************/
// load the data

void _window_xmapslab::close_project_slot()
{
  // clear ???
  //  Map_name_to_layer.clear();

  // remove all the layers
  remove_all_layers();

  // remove positions
  Tab_widget->remove_all_positions();
  // remove all the elements
  Tab_widget->remove_all_xrf();
#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
  Tab_widget->remove_all_compound_from_elements();
#endif
  Tab_widget->remove_all_xrd();

  //#ifdef XRD_ACTIVE
  //  Tab_widget->remove_all_xrd_files();
  //#endif

  Vec_element_names.clear();
  Vec_active_positions.clear();
  Vec_xrf_data.clear();
  Vec_compound_names.clear();
#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
  Vec_compounds_from_elements_pdb.clear();
#endif
  Vec_order_of_layers_by_name.clear();
  Vec_xrf_pdb_data.clear();
  Vec_xrf_pdb_names.clear();

  Project_data.reset();
  Num_active_positions=0;

  Map_name_to_layer.clear();
  Map_name_to_element.clear();
  Map_name_to_compound.clear();
  Map_name_of_layer_to_name_of_element.clear();
  Map_normalized_images.clear();
  Map_name_to_compound.clear();

  XRF_data_loaded=false;
  XRD_data_loaded=false;
  //
  //  if (Original_image.get()!=nullptr) delete Original_image.get();

  Loaded_image=false;
  Initial_image="";
  Initial_width=0;
  Initial_height=0;
  Num_images=0;

  ZOI=_vertex2i(0,0);
  Vec_scaling={1,1};

  GL_widget->setEnabled(false);

  // change states
  Tab_widget->xrf_change_buttons_state(false);
#ifdef XRD_ACTIVE
  Tab_widget->xrd_change_buttons_state(false);
#endif

  // dienable tabs
  Tab_widget->setTabEnabled(Tab_widget->pos_of_tab(_w_tab_xmapslab_ns::_tabs::LAYERS_TAB),false);
  Tab_widget->setTabEnabled(Tab_widget->pos_of_tab(_w_tab_xmapslab_ns::_tabs::ELEMENTS_TAB),false);
  Tab_widget->setTabEnabled(Tab_widget->pos_of_tab(_w_tab_xmapslab_ns::_tabs::POSITIONS_TAB),false);
#ifdef XRD_ACTIVE
  Tab_widget->setTabEnabled(Tab_widget->pos_of_tab(_w_tab_xmapslab_ns::_tabs::COMPOUNDS_XRD_TAB),false);
#endif
  //  Tab_widget->setTabEnabled(int(_w_tab_xmapslab_ns::_tabs::TAB_XRD_FILES),false);

  //  Tab_widget->setTabEnabled(int(_w_tab_xmapslab_ns::_tabs::TAB_PALETTES),false);

  Selected_tab=_w_tab_xmapslab_ns::_tabs::LAYERS_TAB;
  Tab_widget->setCurrentIndex(Tab_widget->pos_of_tab(_w_tab_xmapslab_ns::_tabs::LAYERS_TAB));

//  Load_project->setEnabled(true);
  //  Reload_project->setEnabled(false);
  //  Close_project->setEnabled(false);
}

/*************************************************************************/

void _window_xmapslab::draw_positions(QPainter &Painter,float Widht1,float Height1)
{
  static_pointer_cast<_layer_positions_xmapslab_ui>(Map_name_to_layer["Positions"].Layer)->draw(Painter,Widht1,Height1);
}

/*************************************************************************/

void _window_xmapslab::save_single_layer(string Name)
{
  // The image of the selected layer
  cv::Mat Image_opencv=Map_name_to_layer[Name].Layer->image()->clone();
  cv::flip(Image_opencv,Image_opencv,0);

  float Width1=float(Image_opencv.cols-1);
  float Height1=float(Image_opencv.rows-1);

  // change form OpenCV to Qt format
  QImage Image_qt(Image_opencv.data,Image_opencv.cols,Image_opencv.rows,static_cast<int>(Image_opencv.step),QImage::Format_ARGB32);
  Image_qt.rgbSwapped();

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

void _window_xmapslab::save_single_layer_slot()
{
  save_single_layer(Vec_order_of_layers_by_name[Selected_layer]);

  QMessageBox::information(this,tr("Information"),tr("The image of the selected element/pigment has been correctly saved"));
}

/*************************************************************************/

void _window_xmapslab::save_all_layers_slot()
{
  int Num_total_layers=int(Vec_order_of_layers_by_name.size());
  int Num_element_layers=0;

  for (int i=0;i<Num_total_layers;i++){
    std::string Name=Vec_order_of_layers_by_name[i];
    if (Map_name_to_layer[Name].Layer->layer_type()>=_layer_xmapslab_ns::_layer_type::LAYER_TYPE_MAP_DISTANCE || Map_name_to_layer[Name].Layer->layer_type()>=_layer_xmapslab_ns::_layer_type::LAYER_TYPE_MAP_TRIANGULATION) Num_element_layers++;
  }

  int Count_progress=0;
  QProgressDialog Progress("Working...", "Abort",0,Num_element_layers,this);
  Progress.setWindowModality(Qt::WindowModal);
  Progress.setMinimumDuration(0);
  Progress.setCancelButton(0);

  for (int i=0;i<Num_total_layers;i++){
    std::string Name=Vec_order_of_layers_by_name[i];
    if (Map_name_to_layer[Name].Layer->layer_type()>=_layer_xmapslab_ns::_layer_type::LAYER_TYPE_MAP_DISTANCE || Map_name_to_layer[Name].Layer->layer_type()>=_layer_xmapslab_ns::_layer_type::LAYER_TYPE_MAP_TRIANGULATION){
      Progress.setValue(Count_progress++);
      if (Progress.wasCanceled()) break;
      save_single_layer(Name);
    }
  }

  Progress.setValue(Num_element_layers);

  QMessageBox::information(this,tr("Information"),tr("All the elements/pigments have been correctly saved"));
}

/*************************************************************************/

void _window_xmapslab::save_single_layer_with_color_bar(std::string Name, float Value)
{
  QFont Normal_font=QApplication::font();
  int Normal_font_size=int(float(Normal_font.pointSize())*Print_font_factor);
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
  Image_original.rgbSwapped();

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
  if (Map_name_to_layer[Name].Color_bar->palette_type()==_palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE){
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

void _window_xmapslab::save_single_layer_with_color_bar_slot()
{
  save_single_layer_with_color_bar(Vec_order_of_layers_by_name[Selected_layer],Project_data.Max_value);

  QMessageBox::information(this,tr("Information"),tr("The image of the selected element/pigment has been correctly saved"));
}

/*************************************************************************/

void _window_xmapslab::save_all_layers_with_color_bar_slot()
{
  int Num_total_layers=int(Vec_order_of_layers_by_name.size());
  int Num_element_layers=0;

  for (int i=0;i<Num_total_layers;i++){
    std::string Name=Vec_order_of_layers_by_name[i];
    if (Map_name_to_layer[Name].Layer->layer_type()>=_layer_xmapslab_ns::_layer_type::LAYER_TYPE_MAP_DISTANCE || Map_name_to_layer[Name].Layer->layer_type()>=_layer_xmapslab_ns::_layer_type::LAYER_TYPE_MAP_TRIANGULATION) Num_element_layers++;
  }

  int Count_progress=0;
  QProgressDialog Progress("Working...", "Abort",0,Num_element_layers,this);
  Progress.setWindowModality(Qt::WindowModal);
  Progress.setMinimumDuration(0);
  Progress.setCancelButton(0);

  for (int i=0;i<Num_total_layers;i++){
    std::string Name=Vec_order_of_layers_by_name[i];
    if (Map_name_to_layer[Name].Layer->layer_type()>=_layer_xmapslab_ns::_layer_type::LAYER_TYPE_MAP_DISTANCE || Map_name_to_layer[Name].Layer->layer_type()>=_layer_xmapslab_ns::_layer_type::LAYER_TYPE_MAP_TRIANGULATION){
      Progress.setValue(Count_progress++);
      if (Progress.wasCanceled()) break;
      save_single_layer_with_color_bar(Name,Project_data.Max_value);
    }
  }

  Progress.setValue(Num_element_layers);

  QMessageBox::information(this,tr("Information"),tr("All the elements/pigments have been correctly saved"));
}

/*************************************************************************/

#ifdef NODE_EDITOR_ACTIVE
void _window_xmapslab::save_ge_image_slot()
{
//  QDir Directory_images(Project_dir.absolutePath()+"/results/images");
//  QDir Directory_images(Project_dir.absolutePath());
//  std::string Dir_images=Directory_images.absolutePath().toStdString();

  if (!QDir(Project_dir+"/results").exists()) QDir().mkdir(Project_dir+"/results");
  if (!QDir(Project_dir+"/results/images").exists()) QDir().mkdir(Project_dir+"/results/images");

  std::string Image_Name=Mapping_nodes_editor_maps_tab->selected_item().toStdString();

  cv::Mat Image=Map_mapping_images[Image_Name]->clone();
  cv::flip(Image,Image,0);

  QImage Image1(Image.data,Image.cols,Image.rows,static_cast<int>(Image.step),QImage::Format_ARGB32);
  Image1.rgbSwapped();

  std::string Dir_images=Project_dir.toStdString()+"/results/images/"+Image_Name+".png";

  Image1.save(QString::fromStdString(Dir_images),"PNG");

  QMessageBox::information(this,tr("Information"),tr("The image has been correctly saved"));
}
#endif

/*************************************************************************/

void _window_xmapslab::options_slot()
{
  if (!W_options){
    W_options=new _w_options_xmapslab(this);
    connect(W_options,SIGNAL(accepted()),W_options,SLOT(close()));
  }

  W_options->show();
  W_options->raise();
  W_options->activateWindow();
}

/*************************************************************************/

void _window_xmapslab::left_handle_slot()
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

void _window_xmapslab::right_handle_slot()
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

void _window_xmapslab::show_positions_slot()
{
  if (Show_positions) Show_positions=false;
  else Show_positions=true;

  static_pointer_cast<_layer_positions_xmapslab_ui>(Map_name_to_layer["Positions"].Layer)->draw_positions(Show_positions);
  static_pointer_cast<_layer_positions_xmapslab_ui>(Map_name_to_layer["Positions"].Layer)->update();
  GL_widget->update_texture("Positions");

  GL_widget->update();
}

/*************************************************************************/

void _window_xmapslab::show_triangulation_normal_slot()
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

  static_pointer_cast<_layer_positions_xmapslab_ui>(Map_name_to_layer["Positions"].Layer)->draw_triangulation_mode(Triangulation_mode);
  static_pointer_cast<_layer_positions_xmapslab_ui>(Map_name_to_layer["Positions"].Layer)->update();
  GL_widget->update_texture("Positions");

  GL_widget->update();
}

/*************************************************************************/

void _window_xmapslab::show_triangulation_with_corners_slot()
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

  static_pointer_cast<_layer_positions_xmapslab_ui>(Map_name_to_layer["Positions"].Layer)->draw_triangulation_mode(Triangulation_mode);
  static_pointer_cast<_layer_positions_xmapslab_ui>(Map_name_to_layer["Positions"].Layer)->update();
  GL_widget->update_texture("Positions");

  GL_widget->update();
}

/*************************************************************************/

void _window_xmapslab::activate_image_section_slot()
{
  if (Activate_image_section_first_time==true){
    Activate_image_section_first_time=false;
    QMessageBox::information(this,tr("Information"),tr("The zone of interest of the image is selected by clicking simoultaneously the <b>left shift key</b> in the keyboard and the <b>left button</b> of the mouse<br>Then move the mouse to create the rectangle<br>The zone of interest can be saved using the corresponding option in <b>File</b> menu"));
  }

  if (Activate_image_section){
    Activate_image_section=false;
    Save_image_section->setEnabled(false);
  }
  else{
    Activate_image_section=true;
    Save_image_section->setEnabled(true);
  }

  GL_widget->activate_image_section(Activate_image_section);

  GL_widget->update();
}

/*************************************************************************/

void _window_xmapslab::normal_slot()
{
  switch(State){
    case _window_xmapslab_ns::_state::STATE_NORMAL:
      break;
    case _window_xmapslab_ns::_state::STATE_STATISTICS:
    case _window_xmapslab_ns::_state::STATE_HISTOGRAM:
      {
      // remove the widget
      QWidget *Widget=Splitter_view->widget(0);
      delete Widget;
      }
      break;
    case _window_xmapslab_ns::_state::STATE_LABORATORY:
#ifdef NODE_EDITOR_ACTIVE
      Splitter_node_editor->hide();
      // Save_ge_image->setEnabled(false);
#endif
      Splitter_edit->show();

      break;
    case _window_xmapslab_ns::_state::STATE_3D:
#ifdef MODE_3D_ACTIVE
      GL_widget->show();
      GL_widget_3D->hide();
#endif

#ifdef NODE_EDITOR_ACTIVE
      Splitter_node_editor->hide();
#endif
      Splitter_edit->show();
      break;
  }

  GL_widget->setCursor(Qt::ArrowCursor);

  State=_window_xmapslab_ns::_state::STATE_NORMAL;
}

/*************************************************************************/
// create the bar chart view

#ifdef STATISTIC_GRAPHS_ACTIVE
void _window_xmapslab::chart_bar_slot()
{
  if (Num_elements_computed>0){
    // initialize the data
    Chart_mode=_window_xmapslab_ns::_chart_mode::CHART_MODE_BAR;
    GL_widget->setCursor(Qt::CrossCursor);

    switch(State){
      case _window_xmapslab_ns::_state::STATE_NORMAL:
      case _window_xmapslab_ns::_state::STATE_STATISTICS:
        break;
      case _window_xmapslab_ns::_state::STATE_HISTOGRAM:
        {
        // remove the widget
        QWidget *Widget=Splitter_view->widget(0);
        delete Widget;
        }
        break;
      case _window_xmapslab_ns::_state::STATE_LABORATORY:
#ifdef NODE_EDITOR_ACTIVE
        Splitter_node_editor->hide();
        Save_ge_image->setEnabled(false);
#endif
        Splitter_edit->show();

        break;
      case _window_xmapslab_ns::_state::STATE_3D:
        GL_widget->show();
#ifdef MODE_3D_ACTIVE
        GL_widget_3D->hide();
#endif

#ifdef NODE_EDITOR_ACTIVE
        Splitter_node_editor->hide();
#endif
        Splitter_edit->show();
        break;
    }

    State=_window_xmapslab_ns::_state::STATE_STATISTICS;

    update_chart(Statistics_x,Statistics_y);
  }
}
#endif

/*************************************************************************/
#ifdef STATISTIC_GRAPHS_ACTIVE
void _window_xmapslab::chart_line_slot()
{
  if (Num_elements_computed>0){
    GL_widget->setCursor(Qt::CrossCursor);
    Chart_mode=_window_xmapslab_ns::_chart_mode::CHART_MODE_LINE;

    switch(State){
      case _window_xmapslab_ns::_state::STATE_NORMAL:
      case _window_xmapslab_ns::_state::STATE_STATISTICS:
        break;
      case _window_xmapslab_ns::_state::STATE_HISTOGRAM:
        {
        // remove the widget
        QWidget *Widget=Splitter_view->widget(0);
        delete Widget;
        }
        break;
      case _window_xmapslab_ns::_state::STATE_LABORATORY:
#ifdef NODE_EDITOR_ACTIVE
        Splitter_node_editor->hide();
        Save_ge_image->setEnabled(false);
#endif
        Splitter_edit->show();

        break;
      case _window_xmapslab_ns::_state::STATE_3D:

        GL_widget->show();
#ifdef MODE_3D_ACTIVE
        GL_widget_3D->hide();
#endif

#ifdef NODE_EDITOR_ACTIVE
        Splitter_node_editor->hide();
#endif
        Splitter_edit->show();
        break;
    }

    State=_window_xmapslab_ns::_state::STATE_STATISTICS;

    update_chart(Statistics_x,Statistics_y);
  }
}
#endif
/*************************************************************************/
#ifdef STATISTIC_GRAPHS_ACTIVE
void _window_xmapslab::chart_pie_slot()
{
  if (Num_elements_computed>0){
    GL_widget->setCursor(Qt::CrossCursor);
    Chart_mode=_window_xmapslab_ns::_chart_mode::CHART_MODE_PIE;

    switch(State){
      case _window_xmapslab_ns::_state::STATE_NORMAL:
      case _window_xmapslab_ns::_state::STATE_STATISTICS:
        break;
      case _window_xmapslab_ns::_state::STATE_HISTOGRAM:
        {
        // remove the widget
        QWidget *Widget=Splitter_view->widget(0);
        delete Widget;
        }
        break;
      case _window_xmapslab_ns::_state::STATE_LABORATORY:
#ifdef NODE_EDITOR_ACTIVE
        Splitter_node_editor->hide();
        Save_ge_image->setEnabled(false);
#endif
        Splitter_edit->show();

        break;
      case _window_xmapslab_ns::_state::STATE_3D:
        GL_widget->show();
#ifdef MODE_3D_ACTIVE
        GL_widget_3D->hide();
#endif

#ifdef NODE_EDITOR_ACTIVE
        Splitter_node_editor->hide();
#endif
        Splitter_edit->show();
        break;
    }

    State=_window_xmapslab_ns::_state::STATE_STATISTICS;

    update_chart(Statistics_x,Statistics_y);
  }
}
#endif

/*************************************************************************/
#ifdef STATISTIC_GRAPHS_ACTIVE
void _window_xmapslab::histogram_slot()
{
  if (Num_elements_computed>0){
    switch(State){
      case _window_xmapslab_ns::_state::STATE_NORMAL:
#ifdef NODE_EDITOR_ACTIVE
        Splitter_node_editor->hide();
#endif
        Splitter_edit->show();
        break;
      case _window_xmapslab_ns::_state::STATE_STATISTICS:
        {
        // remove the widget
        QWidget *Widget=Splitter_view->widget(0);
        delete Widget;

        GL_widget->setCursor(Qt::ArrowCursor);
        }
        break;
      case _window_xmapslab_ns::_state::STATE_HISTOGRAM:
        break;
      case _window_xmapslab_ns::_state::STATE_LABORATORY:
#ifdef NODE_EDITOR_ACTIVE
        Splitter_node_editor->hide();
        Save_ge_image->setEnabled(false);
#endif
        Splitter_edit->show();

        break;
      case _window_xmapslab_ns::_state::STATE_3D:
        GL_widget->show();
#ifdef MODE_3D_ACTIVE
        GL_widget_3D->hide();
#endif

#ifdef NODE_EDITOR_ACTIVE
        Splitter_node_editor->hide();
#endif
        Splitter_edit->show();
        break;
    }

    State=_window_xmapslab_ns::_state::STATE_HISTOGRAM;
#ifdef STATISTIC_GRAPHS_ACTIVE
    update_histogram();
#endif
  }
}
#endif
/*************************************************************************/
#ifdef STATISTIC_GRAPHS_ACTIVE
void _window_xmapslab::linear_adjust_slot()
{
  View_log_adjust->setChecked(false);

  Linear_adjust=true;
#ifdef STATISTIC_GRAPHS_ACTIVE
  update_chart(Statistics_x,Statistics_y);
#endif
}
#endif

/*************************************************************************/

#ifdef STATISTIC_GRAPHS_ACTIVE
void _window_xmapslab::logarithmic_adjust_slot()
{
  View_linear_adjust->setChecked(false);

  Linear_adjust=false;
#ifdef STATISTIC_GRAPHS_ACTIVE
  update_chart(Statistics_x,Statistics_y);
#endif
}
#endif
/*************************************************************************/

#ifdef NODE_EDITOR_ACTIVE
void _window_xmapslab::laboratory_slot()
{
  if (Num_elements_computed>0){
    switch(State){
      case _window_xmapslab_ns::_state::STATE_NORMAL:
        Splitter_edit->hide();

        Splitter_node_editor->show();
        // Save_ge_image->setEnabled(true);
        break;
      case _window_xmapslab_ns::_state::STATE_STATISTICS:
      case _window_xmapslab_ns::_state::STATE_HISTOGRAM:
        {
        // remove the char widget
        QWidget *Widget=Splitter_view->widget(0);
        delete Widget;

        Splitter_edit->hide();
        Splitter_node_editor->show();
        // Save_ge_image->setEnabled(true);
        }
        break;
      case _window_xmapslab_ns::_state::STATE_LABORATORY:
        break;
      case _window_xmapslab_ns::_state::STATE_3D:
        Splitter_edit->hide();
        // Splitter_node_editor->show();
        break;
    }

    create_mapping();

    State=_window_xmapslab_ns::_state::STATE_LABORATORY;
  }
}
#endif

#ifdef MODE_3D_ACTIVE
void _window_xmapslab::view3D_slot()
{
  if (Num_elements_computed>0){
    switch(State){
      case _window_xmapslab_ns::_state::STATE_NORMAL:
        GL_widget->hide();
        GL_widget_3D->show();
#ifdef NODE_EDITOR_ACTIVE
        Splitter_node_editor->hide();
#endif
        Splitter_edit->show();
        break;
      case _window_xmapslab_ns::_state::STATE_STATISTICS:
      case _window_xmapslab_ns::_state::STATE_HISTOGRAM:
        {
        // remove the char widget
        QWidget *Widget=Splitter_view->widget(0);
        delete Widget;

        GL_widget->hide();
        GL_widget_3D->show();
#ifdef NODE_EDITOR_ACTIVE
        Splitter_node_editor->hide();
#endif
        Splitter_edit->show();
        }
        break;
      case _window_xmapslab_ns::_state::STATE_LABORATORY:
        GL_widget->hide();
        GL_widget_3D->show();
#ifdef NODE_EDITOR_ACTIVE
        Splitter_node_editor->hide();
        Save_ge_image->setEnabled(false);
#endif
        Splitter_edit->show();

        break;
      case _window_xmapslab_ns::_state::STATE_3D:
        break;
    }

    State=_window_xmapslab_ns::_state::STATE_3D;
  }
}
#endif

/*************************************************************************/

void _window_xmapslab::compute_normalized_images(std::string Name, std::shared_ptr<cv::Mat> Original)
{
  // convert first the RGBA image. It is used with the other conversions
  shared_ptr<cv::Mat> Image_normalized=make_shared<cv::Mat>();
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
//  for (int Color_model=int(_common_ns::_color_model::COLOR_MODEL_HLS);Color_model<int(_common_ns::_color_model::COLOR_MODEL_LAST);Color_model++){
//    // copy the color image
//    Image_normalized=make_shared<cv::Mat>();

//   *Image_normalized=Map_normalized_images[Name][0]->clone();

//    cv::Mat Color_channels(Original->rows,Original->cols, CV_32FC3);
//    cv::Mat Alpha_channel(Original->rows,Original->cols, CV_32FC1);
//    cv::Mat Out[]={Color_channels,Alpha_channel};
//    int from_to[] = { 0,0, 1,1, 2,2, 3,3 };
//    // split the channels in the color part and the transparency part
//    // source, num_sources, destiny, num_destinies, from_to, num_pairs
//    cv::mixChannels(Image_normalized.get(),1,Out,2,from_to,4);

//    switch (Color_model) {
//      case int(_common_ns::_color_model::COLOR_MODEL_HLS):
//        //  0<=H<=360, 0<=S<=1, 0<=V<=1
//        cv::cvtColor(Color_channels,Color_channels,cv::COLOR_RGB2HLS,3);
//        break;
//      case int(_common_ns::_color_model::COLOR_MODEL_HSV):
//        //  0<=H<=360, 0<=S<=1, 0<=V<=1
//        cv::cvtColor(Color_channels,Color_channels,cv::COLOR_RGB2HSV,3);
//        break;
//      case int(_common_ns::_color_model::COLOR_MODEL_LAB):
//        //  0<=L<=100, -127<=a<=127, -127<=b<=127
//        cv::cvtColor(Color_channels,Color_channels,cv::COLOR_RGB2Lab,3);
//        break;
//      case int(_common_ns::_color_model::COLOR_MODEL_LUV):
//        //  0<=L<=100, -134<=u<=220, -140<=v<=122
//        cv::cvtColor(Color_channels,Color_channels,cv::COLOR_RGB2Luv,3);
//        break;
//      default:break;
//    }

//    // add the Alpha_channel channel
//    cv::mixChannels(Out,2,Image_normalized.get(),1,from_to,4);

////    cv::Vec4f Data;
////    // RGBA
////    for (size_t i=0;i<Image_normalized->total();i++){
////      Data=Image_normalized->at<cv::Vec4f>(i);
////    }

//    Map_normalized_images[Name].push_back(Image_normalized);
//  }
}

/*************************************************************************/

void _window_xmapslab::update_order_images(std::string Name)
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

void _window_xmapslab::move_layers_backward(int Initial_pos, int Destination_pos)
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

void _window_xmapslab::move_layers_forward(int Initial_pos, int Destination_pos)
{
  std::string Aux_string=Vec_order_of_layers_by_name[Initial_pos];

  for (int i=Initial_pos;i>Destination_pos;i--){
    Vec_order_of_layers_by_name[i]=Vec_order_of_layers_by_name[i-1];
  }
  Vec_order_of_layers_by_name[Destination_pos]=Aux_string;

  show_layer_parameters(Destination_pos,0);
}

/*************************************************************************/

void _window_xmapslab::remove_pigment_layer(int Row)
{
  std::string Name=Vec_order_of_layers_by_name[Row];

  if (Map_name_to_layer[Name].Layer->layer_type()!=_layer_xmapslab_ns::_layer_type::LAYER_TYPE_BASIC){

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
#ifdef YES_STATISTICS_GRAPHS
      View_linear_adjust->setEnabled(false);
      View_log_adjust->setEnabled(false);
#endif
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
#ifdef YES_STATISTICS_GRAPHS
      View_linear_adjust->setEnabled(false);
      View_log_adjust->setEnabled(false);
#endif
    }
  }
}

/*************************************************************************/

void _window_xmapslab::remove_pigment_layer()
{
  remove_pigment_layer(Selected_layer);
  // clear laboratory
  clear_lab();
}

/*************************************************************************/

void _window_xmapslab::remove_all_pigment_layers()
{
  int Num_layers=int(Vec_order_of_layers_by_name.size());

  for (int i=Num_layers-1;i>=0;i--){
    remove_pigment_layer(i);
  }

  // clear laboratory
  clear_lab();
}

/*************************************************************************/

void _window_xmapslab::clear_lab()
{
  Nodes_editor->clear();
  // this has the images of applying filters
  Mapping_nodes_editor_maps_tab->remove_maps();  // _nodes_editor_maps_tab(this);
  Mapping_filters_tab->remove_filters();  // _filters_tab(this);
  Created_filter_list=false;
  // this is to show the list of usable filters. It depens on the computed layers
  Filters_list->initialize();

  Tab_widget_ge->setCurrentIndex(0);

  //  Map_mapping_images.clear();
  Mapping_selected_image_index=0;
  Mapping_selected_filter_index=0;

  GL_widget_ge->initialize_object();
}

/*************************************************************************/

void _window_xmapslab::remove_layer(int Row)
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
#ifdef YES_STATISTICS_GRAPHS
    View_linear_adjust->setEnabled(false);
    View_log_adjust->setEnabled(false);
#endif

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
#ifdef YES_STATISTICS_GRAPHS
    View_linear_adjust->setEnabled(false);
    View_log_adjust->setEnabled(false);
#endif
  }
}

/*************************************************************************/

void _window_xmapslab::remove_all_layers()
{
  int Num_layers=int(Vec_order_of_layers_by_name.size());

  for (int i=Num_layers-1;i>=0;i--){
    remove_layer(i);
  }

   Map_name_to_layer.erase("Positions");
}

/*************************************************************************/

void _window_xmapslab::show_layer_parameters(int Row,int Col)
{
  Q_UNUSED(Col)
  Selected_layer=Row;
  for(unsigned int i=0; i<Vec_order_of_layers_by_name.size();i++){
    Map_name_to_layer[Vec_order_of_layers_by_name[i]].Layer->hide();
  }

  Map_name_to_layer[Vec_order_of_layers_by_name[Selected_layer]].Layer->show();

  Color_bar_widget->update_color_bar(Selected_tab);
  if (state()==_window_xmapslab_ns::_state::STATE_STATISTICS){
#ifdef STATISTIC_GRAPHS_ACTIVE
    update_chart(Statistics_x,Statistics_y);
#endif
  }
  else{
    if (state()==_window_xmapslab_ns::_state::STATE_HISTOGRAM){
#ifdef STATISTIC_GRAPHS_ACTIVE
      update_histogram();
#endif
    }
  }
}

/*************************************************************************/

void _window_xmapslab::add_layer_image(std::string Name1,shared_ptr<cv::Mat> Image1)
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

  // only one image
  Image_layer_name=Name;

  // create a image layer with its associated name
  Map_name_to_layer[Name].Layer=make_shared<_layer_basic_xmapslab_ui>(this,Name);
  // assign the image
  Map_name_to_layer[Name].Layer->image(Image1);

  // compute the normalized images
  compute_normalized_images(Name,Image1);

  // add the name to the layer list in the elements tab
  cv::Mat Small_image;
  int Size1;
  int Width1;
  int Height1;

  if (screen_height()<=1080) Size1=_window_xmapslab_ns::ICON_SIZE_1080;
  else Size1=_window_xmapslab_ns::ICON_SIZE_1080*Screen_height/1080;

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

  Map_name_to_layer[Name].Color_bar=new _color_bar_abstract(_palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE,3,Values,Colors,this);
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
//  Tab_widget->add_image(Info,Icon);

  // the layer with the image
  Tab_widget->add_layer(Info);

  Selected_tab=_w_tab_xmapslab_ns::_tabs::LAYERS_TAB;
  Tab_widget->setCurrentIndex(int(Selected_tab));

  show_layer_parameters(Selected_layer+1,0);

  GL_widget->update();
}

/*************************************************************************/

void _window_xmapslab::add_layer_filter(_layer_xmapslab_ns::_layer_type Layer_type)
{
  shared_ptr<cv::Mat> Image=make_shared<cv::Mat>();
  std::string Name;

  *Image=Map_name_to_layer[Vec_order_of_layers_by_name[Selected_layer]].Layer->image()->clone();

  switch(Layer_type){
#ifdef YES_LAYERS_EDGES_CANNY
  case _layer_xmapslab_ns::_layer_type::LAYER_TYPE_CANNY:
    Name="Canny_"+std::to_string(Vec_order_of_layers_by_name.size());
    Map_name_to_layer[Name].Layer=make_shared<_layer_canny_ui>(this,Name);
    Map_name_to_layer[Name].Layer->add_input_image(Image);
    Map_name_to_layer[Name].Layer->update();
    break;
#endif
#ifdef YES_LAYERS_EDGES_DOG
  case _layer_xmapslab_ns::_layer_type::LAYER_TYPE_DOG:
    Name="DOG_"+std::to_string(Vec_order_of_layers_by_name.size());
    Map_name_to_layer[Name].Layer=make_shared<_layer_dog_ui>(this,Name);
    Map_name_to_layer[Name].Layer->add_input_image(Image);
    Map_name_to_layer[Name].Layer->update();
    break;
#endif
#ifdef YES_LAYERS_EDGES_KANG
  case _layer_xmapslab_ns::_layer_type::LAYER_TYPE_KANG:
    Name="Kang_"+std::to_string(Vec_order_of_layers_by_name.size());
    Map_name_to_layer[Name].Layer=make_shared<_layer_kang_ui>(this,Name);
    Map_name_to_layer[Name].Layer->add_input_image(Image);
    Map_name_to_layer[Name].Layer->update();
    break;
#endif
#ifdef YES_LAYERS_EDGES_KMEANS
  case _layer_xmapslab_ns::_layer_type::LAYER_TYPE_KMEANS:
    Name="Kmeans_"+std::to_string(Vec_order_of_layers_by_name.size());
    Map_name_to_layer[Name].Layer=make_shared<_layer_kmeans_ui>(this,Name);
    Map_name_to_layer[Name].Layer->add_input_image(Image);
    Map_name_to_layer[Name].Layer->update();
    break;
#endif
  default:break;
  }

  Map_name_to_layer[Name].Texture=GL_widget->set_texture(Map_name_to_layer[Name].Layer->image());

  // orders the images
  std::vector<float> Values;
  std::vector<QColor> Colors;
  Values.resize(3);
  Colors.resize(3);

  update_order_images(Name);

  Map_name_to_layer[Name].Color_bar=new _color_bar_abstract(_palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE,3,Values,Colors,this);
  Map_name_to_layer[Name].Color_bar_name="";

  Color_bar_widget->add_palette_layer(Name);

  _table_layers_ns::_info Info;
  Info.Name=QString::fromStdString(Name);

  Tab_widget->add_layer(Info);

  Selected_tab=_w_tab_xmapslab_ns::_tabs::LAYERS_TAB;
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

void _window_xmapslab::add_layer_map_minimum_hypercube_distance(string Name_image1, std::string Name_pigment1, std::string View_name1, _common_ns::_color_model Color_model1, std::vector<bool> Use_colors1, std::vector<bool> Use_positions1, bool Distance_normalization1, _layer_map_distance_ns::_position_normalization_type Position_normalization_type1, int Probe1, _palette_data_ns::_palette Palette1, _palette_data_ns::_data_type_print Data_type_print1, _color_map_ns::_color_for_zero_value Color_for_zero_value1, std::map<std::string, _pigment_data_ns::_pigment_data> &Map_pigment_data, _common_ns::_xray_data_type Xray_data_type1)
{
 shared_ptr<cv::Mat> Image_normalized=make_shared<cv::Mat>();

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
//  Map_element_layer.insert(std::pair<std::string,std::string>(Name_pigment_aux,Name_layer));
 // add the map between the name of the layer and the original element (to get information)
 Map_name_of_layer_to_name_of_element.insert(std::pair<std::string,std::string>(Name_layer,Name_pigment1));

 // create the new layer
 shared_ptr<_layer_map_distance_ui> Layer=make_shared<_layer_map_distance_ui>(this,Name_layer);
 // add to the map
 Map_name_to_layer[Name_layer].Layer=Layer;
 // add the name
 Map_name_to_layer[Name_layer].Pigment_name=Name_pigment1;
 // the result image
 shared_ptr<cv::Mat> Image_r=make_shared<cv::Mat>();
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
 Layer->xray_data_type(Map_pigment_data[Name_pigment1].Xray_data_type);

 bool Invisible=true;
 if (Invisible){
   Layer->state(0,false);
   Layer->state(1,true);
 }

 // create the palette data
 // if the name is mutable and is XRF, each one has a color assigned
 QColor Color1=Palette1.Color;
 if (Map_pigment_data[Name_pigment1].Xray_data_type==_common_ns::_xray_data_type::XRAY_DATA_TYPE_XRF){
   if (Palette1.Color_assigning==_palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_MUTABLE){
     auto It = _window_xmapslab_ns::Map_atomic_data.find(Name_pigment1);

     if (It != _window_xmapslab_ns::Map_atomic_data.end()) Color1=It->second.Color;
   }
 }
 else{
   if (Palette1.Color_assigning==_palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_MUTABLE){
     Color1=_color_bar_abstract::compute_random_color();
   }
 }

 _palette_data_ns::_palette_data Palette_layer("",Palette1.Type,Palette1.Color_type,Palette1.Num_stops, Palette1.Color_assigning, Color1, Map_fixed_palettes[Palette1.Name_fixed_palette], Color_for_zero_value1);

 // create color_bar
 std::vector<QColor> Colors=Palette_layer.colors();
 Map_name_to_layer[Name_layer].Color_bar=Color_bar_widget->create_color_bar(Palette_layer, Map_pigment_data[Name_pigment1].Xray_data_type, Name_pigment1, Map_pigment_data[Name_pigment1].Max_value_adjusted, Colors, Data_type_print1, Color_for_zero_value1);

 // assign the name of the element/pigment that produces the map
 Map_name_to_layer[Name_layer].Color_bar_name=Name_pigment1;

 Color_bar_widget->add_palette_layer(Name_layer);
 // pass the palette to the layer
 Layer->set_colormap(Palette_layer.vec_values(),Colors,Palette_layer.type());

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
 Selected_tab=_w_tab_xmapslab_ns::_tabs::LAYERS_TAB;
 Tab_widget->setCurrentIndex(int(Selected_tab));

 show_layer_parameters(Selected_layer+1,0);

 Tab_widget->select_layers_row(Selected_layer);

 //
 Action_activate_image_section->setEnabled(true);

//  //
//  Submenu_save_single_layer->setEnabled(true);
//  Save_single_layer->setEnabled(true);
 Save_single_layer_with_color_bar->setEnabled(true);

//  Submenu_save_all_layers->setEnabled(true);
//  Save_all_layers->setEnabled(true);
 Save_all_layers_with_color_bar->setEnabled(true);

//  Save_composed_image->setEnabled(true);
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

void _window_xmapslab::add_layer_map_triangulation(std::string Name_image1, std::string Name_pigment1, std::string View_name1, _common_ns::_color_model Color_model1, _palette_data_ns::_palette Palette1, bool Triangulation_add_corners1, _palette_data_ns::_data_type_print Data_type_print1, _color_map_ns::_color_for_zero_value Color_for_zero_value1, std::map<std::string,_pigment_data_ns::_pigment_data> &Map_pigment_data, _common_ns::_xray_data_type Xray_data_type1)
{
//  shared_ptr<cv::Mat> Image_normalized=make_shared<cv::Mat>();
//  std::vector<float> Vec_coordinate_x_corners;
//  std::vector<float> Vec_coordinate_y_corners;
//  std::vector<float> Vec_values_corners;

//  // get the normalized image that will be used for computing the minimum distance
//  // currently only one image is used ???
//  Image_normalized=Map_normalized_images[Name_image1][int(Color_model1)];//->clone();

//  std::string Name_layer;
//  std::string Name_element_aux=View_name1+"_"+Name_pigment1+"_";

//  Name_element_aux=Name_element_aux+"TRI";

//  // the name add the position of the current layer. There are not two layers that are equal in name
//  Name_layer=Name_element_aux+"_"+std::to_string(Vec_order_of_layers_by_name.size());
//  // add the map between the original element and the layer (to get information)
////  Map_element_layer.insert(std::pair<std::string,std::string>(Name_element_aux,Name_layer));
//  // add the map between the name of the layer and the original element (to get information)
//  Map_name_of_layer_to_name_of_element.insert(std::pair<std::string,std::string>(Name_layer,Name_pigment1));

//  // create the new layer
//  shared_ptr<_layer_map_triangulation_ui> Layer=make_shared<_layer_map_triangulation_ui>(this,Name_layer);
//  // add to the map
//  Map_name_to_layer[Name_layer].Layer=Layer;
//  // add the name
//  Map_name_to_layer[Name_layer].Pigment_name=Name_pigment1;
//  // the result image
//  shared_ptr<cv::Mat> Image_r=make_shared<cv::Mat>();
//  Image_r->create(Initial_height,Initial_width,CV_8UC4);
//  Layer->image(Image_r);
//  // the data of the element
//  Layer->size(Initial_width,Initial_height);
//  Layer->data_type_print(Data_type_print1);
//  // the normalized color image (here is used to check if there are transparent zones
//  Layer->add_input_image(Image_normalized);
//  Layer->xray_data_type(Map_pigment_data[Name_pigment1].Xray_data_type);

//  if (Triangulation_add_corners1==false){ // send the normal data
//    Layer->add_input_data(Project_data.Vec_coordinate_x,Project_data.Vec_coordinate_y,Map_pigment_data[Name_pigment1].Vec_values);
//    Layer->add_triangles_data(Triangles);
//  }
//  else{ // initialize the vector
//    Vec_coordinate_x_corners=Project_data.Vec_coordinate_x;
//    Vec_coordinate_y_corners=Project_data.Vec_coordinate_y;
//    Vec_values_corners=Map_name_to_element[Name_pigment1].Vec_values;

//    // add the corners
//    Vec_coordinate_x_corners.push_back(0);
//    Vec_coordinate_y_corners.push_back(0);
//    Vec_values_corners.push_back(0);

//    Vec_coordinate_x_corners.push_back(Project_data.Width_pixel-1);
//    Vec_coordinate_y_corners.push_back(0);
//    Vec_values_corners.push_back(0);

//    Vec_coordinate_x_corners.push_back(0);
//    Vec_coordinate_y_corners.push_back(Project_data.Height_pixel-1);
//    Vec_values_corners.push_back(0);

//    Vec_coordinate_x_corners.push_back(Project_data.Width_pixel-1);
//    Vec_coordinate_y_corners.push_back(Project_data.Height_pixel-1);
//    Vec_values_corners.push_back(0);

//    Layer->add_input_data(Vec_coordinate_x_corners,Vec_coordinate_y_corners,Vec_values_corners);
//    Layer->add_triangles_data(Triangles_with_corners);
//  }

//  bool Invisible=true;
//  if (Invisible){
//    Layer->state(0,false);
//    Layer->state(1,true);
//  }

//  // create color_bar
//  std::vector<QColor> Colors;
//  Map_name_to_layer[Name_layer].Color_bar=Color_bar_widget->create_color_bar(Palette1,Map_pigment_data[Name_pigment1].Xray_data_type, Name_pigment1,Map_pigment_data[Name_pigment1].Max_value_adjusted,Colors,Data_type_print1,Color_for_zero_value1);
//  Map_name_to_layer[Name_layer].Color_bar_name=Name_pigment1;
//  Color_bar_widget->add_palette_layer(Name_layer);
//  // pass the palette to the layer
//  Layer->set_colormap(Color_bar_widget->Palettes[Palette1]->vec_proportions(),Colors,Color_bar_widget->Palettes[Palette1]->type());

//  Layer->update();

//  Map_name_to_layer[Name_layer].Texture=GL_widget->set_texture(Map_name_to_layer[Name_layer].Layer->image());

//  // update the vector with the order of images
//  update_order_images(Name_layer);

//  // add the new element of the story. The key is the name of the layer.
////  Element_history[Name_layer]=_pigment_data_ns::_history_data(Name_layer1,Name_element1,View_name1, Palette1,Interpolation_type,Probe1,Use_colors1,Use_positions1,Color_model1,Distance_normalization1);

//  // add 1 to the counter
//  Num_elements_computed++;
//  // change the visibility of some options
//  if (Num_elements_computed==1){
//    for (unsigned int i=1;i<View.size();i++){
//      View[i]->setEnabled(true);
//    }
//#ifdef YES_STATISTICS_GRAPHS
//    View_linear_adjust->setEnabled(true);
//    View_log_adjust->setEnabled(true);
//#endif
//  }

//  _table_layers_ns::_info Info;
//  Info.Name=QString::fromStdString(Name_layer);

//  // check
//  Info.States[0]=false;

//  Tab_widget->add_layer(Info);
//  Selected_tab=_w_tab_xmapslab_ns::_tabs::LAYERS_TAB;
//  Tab_widget->setCurrentIndex(int(Selected_tab));

//  show_layer_parameters(Selected_layer+1,0);

//  Tab_widget->select_layers_row(Selected_layer);

//  //
//  Action_activate_image_section->setEnabled(true);

////  Submenu_save_single_layer->setEnabled(true);
////  Save_single_layer->setEnabled(true);
//  Save_single_layer_with_color_bar->setEnabled(true);

////  Submenu_save_all_layers->setEnabled(true);
////  Save_all_layers->setEnabled(true);
//  Save_all_layers_with_color_bar->setEnabled(true);

////  Save_composed_image->setEnabled(true);
//#ifdef YES_STATISTICS_GRAPHS
//  View_linear_adjust->setEnabled(true);
//  View_log_adjust->setEnabled(true);
//#endif
////  View_save_positions->setEnabled(true);
//  View_show_positions->setEnabled(true);

//#ifndef BASIC
////  View_show_triangulation->setEnabled(true);
////  View_compose_colors->setEnabled(true);
//#endif

//  for (unsigned int i=1;i<View.size();i++) View[i]->setEnabled(true);

//  GL_widget->update();
}

/*************************************************************************/
// Adds a layer corresponding to an element (single or compound)
// It is importat to note that it is possible to have several layers obtained from
// a single element (XRF or XRD). For example, it is possible to compute the distance
// only using the color or the position
// So, it is neccesary to obtain the new values but also to link to the original data

void _window_xmapslab::add_layer_map_rbf_interpolation(string Name_image1, std::string Name_pigment1, std::string View_name1,   _common_ns::_color_model Color_model1, _palette_data_ns::_palette Palette1, _palette_data_ns::_data_type_print Data_type_print1, _color_map_ns::_color_for_zero_value Color_for_zero_value1, std::map<std::string,_pigment_data_ns::_pigment_data> &Map_pigment_data, _common_ns::_xray_data_type Xray_data_type1)
{
 shared_ptr<cv::Mat> Image_normalized=make_shared<cv::Mat>();

 // get the normalized image that will be used for computing the minimum distance
 // currently only one image is used ???
 Image_normalized=Map_normalized_images[Name_image1][int(Color_model1)];

 std::string Name_layer;
 std::string Name_element_aux=View_name1+"_"+Name_pigment1+"_";

 Name_element_aux=Name_element_aux+"RBF";

 // the name add the position of the current layer. There are not two layers that are equal in name
 Name_layer=Name_element_aux+"_"+std::to_string(Vec_order_of_layers_by_name.size());
 // add the map between the original element and the layer (to get information)
//  Map_element_layer.insert(std::pair<std::string,std::string>(Name_element_aux,Name_layer));
 // add the map between the name of the layer and the original element (to get information)
 Map_name_of_layer_to_name_of_element.insert(std::pair<string,string>(Name_layer,Name_pigment1));

 // create the new layer
 shared_ptr<_layer_map_rbf_interpolation_ui> Layer=make_shared<_layer_map_rbf_interpolation_ui>(this,Name_layer);
 // add to the map
 Map_name_to_layer[Name_layer].Layer=Layer;
 // add the name
 Map_name_to_layer[Name_layer].Pigment_name=Name_pigment1;

 // the result image
 shared_ptr<cv::Mat> Image_r=make_shared<cv::Mat>();
 Image_r->create(Initial_height,Initial_width,CV_8UC4);
 Layer->image(Image_r);
 // the data of the element
 Layer->size(Initial_width,Initial_height);
 Layer->data_type_print(Data_type_print1);

 // the valid positions
 Layer->add_valid_positions(Vec_active_positions);
 // the input data
 Layer->add_input_data(Project_data.Vec_coordinate_x,Project_data.Vec_coordinate_y,Map_pigment_data[Name_pigment1].Vec_values,XRF_RBF_radius); // ???? checl
 // the normalized color image (here is used to check if there are transparent zones
 Layer->add_input_image(Image_normalized);
 // function type
 Layer->set_function_type(XRF_RBF_function); //????
 //
 Layer->xray_data_type(Xray_data_type1);

 bool Invisible=true;
 if (Invisible){
   Layer->state(0,false);
   Layer->state(1,true);
 }

 // create color_bar
 // std::vector<QColor> Colors;
 // Map_name_to_layer[Name_layer].Color_bar=Color_bar_widget->create_color_bar(Palette1,Map_pigment_data[Name_pigment1].Xray_data_type, Name_pigment1,Map_pigment_data[Name_pigment1].Max_value_adjusted,Colors,Data_type_print1,Color_for_zero_value1);
 // Map_name_to_layer[Name_layer].Color_bar_name=Name_pigment1;
 // Color_bar_widget->add_palette_layer(Name_layer);

 // create the palette data
 // if the name is mutable and is XRF, each one has a color assigned
 QColor Color1=Palette1.Color;
 if (Xray_data_type1==_common_ns::_xray_data_type::XRAY_DATA_TYPE_XRF){
   if (Palette1.Color_assigning==_palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_MUTABLE){
     auto It = _window_xmapslab_ns::Map_atomic_data.find(Name_pigment1);

     if (It != _window_xmapslab_ns::Map_atomic_data.end()) Color1=It->second.Color;
   }
 }
 else{
   if (Palette1.Color_assigning==_palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_MUTABLE){
     Color1=_color_bar_abstract::compute_random_color();
   }
 }

 _palette_data_ns::_palette_data Palette_layer("",Palette1.Type,Palette1.Color_type,Palette1.Num_stops, Palette1.Color_assigning, Color1, Map_fixed_palettes[Palette1.Name_fixed_palette], Color_for_zero_value1);

 // create color_bar
 std::vector<QColor> Colors=Palette_layer.colors();
 Map_name_to_layer[Name_layer].Color_bar=Color_bar_widget->create_color_bar(Palette_layer, Map_pigment_data[Name_pigment1].Xray_data_type, Name_pigment1, Map_pigment_data[Name_pigment1].Max_value_adjusted, Colors, Data_type_print1, Color_for_zero_value1);

 // assign the name of the element/pigment that produces the map
 Map_name_to_layer[Name_layer].Color_bar_name=Name_pigment1;

 Color_bar_widget->add_palette_layer(Name_layer);

 // pass the palette to the layer
 Layer->set_colormap(Palette_layer.vec_values(),Colors,Palette_layer.type());

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
 Selected_tab=_w_tab_xmapslab_ns::_tabs::LAYERS_TAB;
 Tab_widget->setCurrentIndex(int(Selected_tab));

 show_layer_parameters(Selected_layer+1,0);

 Tab_widget->select_layers_row(Selected_layer);

 //
 Action_activate_image_section->setEnabled(true);

//  //
//  Submenu_save_single_layer->setEnabled(true);
//  Save_single_layer->setEnabled(true);
 Save_single_layer_with_color_bar->setEnabled(true);

//  Submenu_save_all_layers->setEnabled(true);
//  Save_all_layers->setEnabled(true);
 Save_all_layers_with_color_bar->setEnabled(true);

//  Save_composed_image->setEnabled(true);
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
// This is the new method

//void _window_xmapslab::add_layer_map_rbf_interpolation(std::string Name_image1, std::string Name_pigment1, std::string View_name1,   _common_ns::_color_model Color_model1, int Palette1, _palette_data_ns::_data_type_print Data_type_print1, _color_map_ns::_color_for_zero_value Color_for_zero_value1, std::map<std::string,_pigment_data_ns::_pigment_data> &Map_pigment_data)
//{
//  shared_ptr<cv::Mat> Image_normalized=make_shared<cv::Mat>();

//  // get the normalized image that will be used for computing the minimum distance
//  // currently only one image is used ???
//  Image_normalized=Map_normalized_images[Name_image1][int(Color_model1)];

//  std::string Name_layer;
//  std::string Name_element_aux=View_name1+"_"+Name_pigment1+"_";

//  Name_element_aux=Name_element_aux+"RBF";

//  // the name add the position of the current layer. There are not two layers that are equal in name
//  Name_layer=Name_element_aux+"_"+std::to_string(Vec_order_of_layers_by_name.size());
//  // add the map between the original element and the layer (to get information)
//  //  Map_element_layer.insert(std::pair<std::string,std::string>(Name_element_aux,Name_layer));
//  // add the map between the name of the layer and the original element (to get information)
//  Map_name_of_layer_to_name_of_element.insert(std::pair<std::string,std::string>(Name_layer,Name_pigment1));

//  // create the new layer
////  shared_ptr<_layer_map_rbf_interpolation_ui> Layer=make_shared<_layer_map_rbf_interpolation_ui>(this,Name_layer);
//  shared_ptr<_layer_map_rbf_interpolation_plus_ui> Layer=make_shared<_layer_map_rbf_interpolation_plus_ui>(this,Name_layer);

//  // add to the map
//  Map_name_to_layer[Name_layer].Layer=Layer;
//  // add the name
//  Map_name_to_layer[Name_layer].Pigment_name=Name_pigment1;

//  // the result image
//  shared_ptr<cv::Mat> Image_r=make_shared<cv::Mat>();
//  Image_r->create(Initial_height,Initial_width,CV_8UC4);
//  Layer->image(Image_r);
//  // the data of the element
//  Layer->size(Initial_width,Initial_height);
//  Layer->data_type_print(Data_type_print1);

//  // the valid positions
//  Layer->add_valid_positions(Vec_active_positions);
//  // the input data
////  Layer->add_input_data(Project_data.Vec_coordinate_x,Project_data.Vec_coordinate_y,Map_pigment_data[Name_pigment1].Vec_values,RBF_radius);

//  /***********/
//  vector<cv::Vec4f> Vec_color(Project_data.Vec_coordinate_x.size());
//  for (unsigned int i=0;i<Project_data.Vec_coordinate_x.size();i++){
//    // get the color OpenCV uses a left hand CS
//    Vec_color[i]=Image_normalized->at<cv::Vec4f>(Project_data.Vec_coordinate_y[i],Project_data.Vec_coordinate_x[i]);
//  }

//  Layer->add_input_data(Project_data.Vec_coordinate_x,Project_data.Vec_coordinate_y, Map_pigment_data[Name_pigment1].Vec_values,RBF_radius, Vec_color);

//  // the normalized color image (here is used to check if there are transparent zones
//  Layer->add_input_image(Image_normalized);
//  // function type
//  Layer->set_function_type(RBF_function);

//  bool Invisible=true;
//  if (Invisible){
//    Layer->state(0,false);
//    Layer->state(1,true);
//  }

//  // create color_bar
//  std::vector<QColor> Colors;
//  Map_name_to_layer[Name_layer].Color_bar=Color_bar_widget->create_color_bar(Palette1,Map_pigment_data[Name_pigment1].Data_type,Name_pigment1,Map_pigment_data[Name_pigment1].Max_value_adjusted,Colors,Data_type_print1,Color_for_zero_value1);
//  Map_name_to_layer[Name_layer].Color_bar_name=Name_pigment1;
//  Color_bar_widget->add_palette_layer(Name_layer);
//  // pass the palette to the layer
//  Layer->set_colormap(Color_bar_widget->Palettes[Palette1]->vec_proportions(),Colors,int(Color_bar_widget->Palettes[Palette1]->type()));

//  Layer->update();

//  Map_name_to_layer[Name_layer].Texture=GL_widget->set_texture(Map_name_to_layer[Name_layer].Layer->image());

//  // update the vector with the order of images
//  update_order_images(Name_layer);

//  // add the new element of the story. The key is the name of the layer.
//  //  Element_history[Name_layer]=_pigment_data_ns::_history_data(Name_layer1,Name_element1,View_name1, Palette1,Interpolation_type,Probe1,Use_colors1,Use_positions1,Color_model1,Distance_normalization1);

//  // add 1 to the counter
//  Num_elements_computed++;
//  // change the visibility of some options
//  if (Num_elements_computed==1){
//    for (unsigned int i=1;i<View.size();i++){
//      View[i]->setEnabled(true);
//    }
//#ifdef YES_STATISTICS_GRAPHS
//    View_linear_adjust->setEnabled(true);
//    View_log_adjust->setEnabled(true);
//#endif
//  }

//  _table_layers_ns::_info Info;
//  Info.Name=QString::fromStdString(Name_layer);

//  // check
//  Info.States[0]=false;

//  Tab_widget->add_layer(Info);
//  Selected_tab=_w_tab_xmapslab_ns::_tabs::LAYERS_TAB;
//  Tab_widget->setCurrentIndex(int(Selected_tab));

//  show_layer_parameters(Selected_layer+1,0);

//  Tab_widget->select_layers_row(Selected_layer);

//  //
//  Submenu_save_single_layer->setEnabled(true);
//  Save_single_layer->setEnabled(true);
//  Save_single_layer_with_color_bar->setEnabled(true);

//  Submenu_save_all_layers->setEnabled(true);
//  Save_all_layers->setEnabled(true);
//  Save_all_layers_with_color_bar->setEnabled(true);

//  Save_composed_image->setEnabled(true);
//#ifdef YES_STATISTICS_GRAPHS
//  View_linear_adjust->setEnabled(true);
//  View_log_adjust->setEnabled(true);
//#endif
//  //  View_save_positions->setEnabled(true);
//  View_show_positions->setEnabled(true);

//#ifndef BASIC
////  View_show_triangulation->setEnabled(true);
////  View_compose_colors->setEnabled(true);
//#endif

//  for (unsigned int i=1;i<View.size();i++) View[i]->setEnabled(true);

//  GL_widget->update();
//}

/*************************************************************************/
// Adds a layer corresponding to an element (single or compound)
// It is importat to note that it is possible to have several layers obtained from
// a single element (XRF or XRD). For example, it is possible to compute the distance
// only using the color or the position
// So, it is neccesary to obtain the new values but also to link to the original data

#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
void _window_xmapslab::add_layer_compound_from_elements(std::string Name_image1, std::string Name_pigment1, std::string View_name1, std::vector<_data_xrf_ns::_data_element_num_atoms> Vec_elements1, std::vector<string> Vec_names_in_map1, std::vector<float> Vec_global_percentages1, _palette_data_ns::_palette Palette1, _palette_data_ns::_data_type_print Data_type_print1, _color_map_ns::_color_for_zero_value Color_for_zero_value1)
{
//  shared_ptr<cv::Mat> Image_normalized=make_shared<cv::Mat>();

//  // get the normalized image that will be used for computing the minimum distance
//  // currently only one image is used ???
//  Image_normalized=Map_normalized_images[Name_image1][int(_common_ns::_color_model::COLOR_MODEL_RGB)];//->clone();

//  std::string Name_layer;
//  std::string Name_pigment_aux=View_name1+"_"+Name_pigment1;

//  // the name add the position of the current layer. There are not two layers that are equal in name
//  Name_layer=Name_pigment_aux+"_"+std::to_string(Vec_order_of_layers_by_name.size());

//  // add the map between the original element and the layer (to get information)
////  Map_element_layer.insert(std::pair<std::string,std::string>(Name_pigment_aux,Name_layer));
//  // add the map between the name of the layer and the original element (to get information)
//  Map_name_of_layer_to_name_of_element.insert(std::pair<std::string,std::string>(Name_layer,Name_pigment1));

//  // create the new layer
//  shared_ptr<_layer_compound_from_elements_ui> Layer=make_shared<_layer_compound_from_elements_ui>(this,Name_layer);
//  // add to the map
//  Map_name_to_layer[Name_layer].Layer=Layer;
//  // add the name
//  Map_name_to_layer[Name_layer].Pigment_name=Name_pigment1;

//  // the result image
//  shared_ptr<cv::Mat> Image_r=make_shared<cv::Mat>();
//  Image_r->create(Initial_height,Initial_width,CV_8UC4);
//  Layer->image(Image_r);
//  // the inputa data
//  std::vector<std::shared_ptr<cv::Mat> > Vec_maps_intensities(Vec_elements1.size());
//  std::vector<float> Vec_max_intensities(Vec_elements1.size());
//  std::vector<float> Vec_percentages(Vec_elements1.size());

//  // compute the total number of atoms
//  int Num_total_atoms=0;
//  for (unsigned int i=0;i<Vec_elements1.size();i++) Num_total_atoms=Num_total_atoms+Vec_elements1[i].Num_atoms;
//  // compute the percentages
//  for (unsigned int i=0;i<Vec_elements1.size();i++){
//    Vec_percentages[i]=float(Vec_elements1[i].Num_atoms)/float(Num_total_atoms);
//  }
//  // get the maps and max values
//  for (unsigned int i=0;i<Vec_names_in_map1.size();i++){
//    Vec_maps_intensities[i]=Map_name_to_layer[Vec_names_in_map1[i]].Layer->result_floats_image();
//    Vec_max_intensities[i]=Map_name_to_element[Vec_elements1[i].Element_name].Max_value_adjusted;
//  }

//  Layer->add_input_data(Vec_maps_intensities,Vec_max_intensities,Vec_percentages,Vec_global_percentages1);

//  // the color image
//  Layer->add_input_image(Image_normalized);
////  Layer->add_image_alpha_channel(Image_alpha_channel);
//  Layer->size(Initial_width,Initial_height);
//  Layer->data_type_print(Data_type_print1);

//  Layer->update();

//  float Max_intensity=Layer->max_intensity();

//  bool Invisible=true;
//  if (Invisible){
//    Layer->state(0,false);
//    Layer->state(1,true);
//  }

//  // create color_bar
//  std::vector<QColor> Colors;
//  Map_name_to_layer[Name_layer].Color_bar=Color_bar_widget->create_color_bar(Palette1, _common_ns::_xray_data_type::XRAY_DATA_TYPE_XRF,Name_pigment1,Max_intensity,Colors,Data_type_print1,Color_for_zero_value1);

//  Map_name_to_layer[Name_layer].Color_bar_name=Name_pigment1;
//  Color_bar_widget->add_palette_layer(Name_layer);
//  // pass the palette to the layer
//  Layer->set_colormap(Color_bar_widget->Palettes[Palette1]->vec_proportions(),Colors,Color_bar_widget->Palettes[Palette1]->type());

//  // it is necessary a second update once the max_intensity is computed and the colormap created. It only updates the colors
//  Layer->update();

//  Map_name_to_layer[Name_layer].Texture=GL_widget->set_texture(Map_name_to_layer[Name_layer].Layer->image());

//  // update the vector with the order of images
//  update_order_images(Name_layer);

//  // add the new element of the story. The key is the name of the layer.
////  Element_history[Name_layer]=_pigment_data_ns::_history_data(Name_layer1,Name_element1,View_name1, Palette1,Interpolation_type,Probe1,Use_colors1,Use_positions1,Color_model1,Distance_normalization1);

//  // add 1 to the counter
//  Num_elements_computed++;
//  // change the visibility of some options
//  if (Num_elements_computed==1){
//    for (unsigned int i=1;i<View.size();i++){
//      View[i]->setEnabled(true);
//    }
////    View_linear_adjust->setEnabled(true);???
////    View_log_adjust->setEnabled(true);
//  }

//  _table_layers_ns::_info Info;
//  Info.Name=QString::fromStdString(Name_layer);

//  // check
//  Info.States[0]=false;

//  Tab_widget->add_layer(Info);
//  Selected_tab=_w_tab_xmapslab_ns::_tabs::LAYERS_TAB;
//  Tab_widget->setCurrentIndex(int(Selected_tab));

//  show_layer_parameters(Selected_layer+1,0);

//  Tab_widget->select_layers_row(Selected_layer);

//  //
//  Submenu_save_single_layer->setEnabled(true);
//  Save_single_layer->setEnabled(true);
//  Save_single_layer_with_color_bar->setEnabled(true);

//  Submenu_save_all_layers->setEnabled(true);
//  Save_all_layers->setEnabled(true);
//  Save_all_layers_with_color_bar->setEnabled(true);

//  Save_composed_image->setEnabled(true);
//  Save_image_section->setEnabled(true);

////  View_linear_adjust->setEnabled(true);???
////  View_log_adjust->setEnabled(true);
////  View_save_positions->setEnabled(true);
//  View_show_positions->setEnabled(true);

//#ifndef BASIC
////  View_show_triangulation->setEnabled(true);
////  View_compose_colors->setEnabled(true);
//#endif

//  for (unsigned int i=1;i<View.size();i++) View[i]->setEnabled(true);

//  GL_widget->update();
}
#endif

void _window_xmapslab::add_layer_map_lab(std::string Name_image1, std::shared_ptr<cv::Mat> Image1, _palette_data_ns::_palette Palette1, _palette_data_ns::_data_type_print Data_type_print1, float Max_value, _color_map_ns::_color_for_zero_value Color_for_zero_value1)
{
  std::string Name_layer;

  // the name add the position of the current layer. There are not two layers that are equal in name
  Name_layer=Name_image1+"_"+std::to_string(Vec_order_of_layers_by_name.size());

  // add the map between the original element and the layer (to get information)
  //  Map_element_layer.insert(std::pair<string,string>(Name_pigment_aux,Name_layer));
  // add the map between the name of the layer and the original element (to get information)
  Map_name_of_layer_to_name_of_element.insert(std::pair<std::string,std::string>(Name_layer,Name_image1));

  // create the new layer
  std::shared_ptr<_layer_map_lab_ui> Layer=std::make_shared<_layer_map_lab_ui>(this,Name_layer);
  // add to the map
  Map_name_to_layer[Name_layer].Layer=Layer;
  // add the name
  Map_name_to_layer[Name_layer].Pigment_name=Name_image1;
  // the result image
  std::shared_ptr<cv::Mat> Image_r=std::make_shared<cv::Mat>();
  Image_r->create(Initial_height,Initial_width,CV_8UC4);
  Layer->image(Image_r);
  // the color image
  Layer->add_input_image(Image1);

  bool Invisible=true;
  if (Invisible){
    Layer->state(0,false);
    Layer->state(1,true);
  }

  // if the name is mutable and is XRF, each one has a color assigned
  QColor Color1=Palette1.Color;
  if (Palette1.Color_assigning==_palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_MUTABLE){
    Color1=_color_bar_abstract::compute_random_color();
  }

  _palette_data_ns::_palette_data Palette_layer("",Palette1.Type,Palette1.Color_type,Palette1.Num_stops, Palette1.Color_assigning, Color1, Map_fixed_palettes[Palette1.Name_fixed_palette], Color_for_zero_value1);

  // create color_bar
  std::vector<QColor> Colors=Palette_layer.colors();
  // Send XRD tube to not check the names
  Map_name_to_layer[Name_layer].Color_bar=Color_bar_widget->create_color_bar(Palette_layer, _common_ns::_xray_data_type::XRAY_DATA_TYPE_XRD, Name_image1, Max_value, Colors, Data_type_print1, Color_for_zero_value1);

  // assign the name of the element/pigment that produces the map
  Map_name_to_layer[Name_layer].Color_bar_name=Name_image1;

  Color_bar_widget->add_palette_layer(Name_layer);

  // pass the palette to the layer
  Layer->set_colormap(Palette_layer.vec_values(),Colors,Palette_layer.type());

  Layer->update();

//   // create color_bar
// //  _pigment_data_ns::_data_type Data_type=_pigment_data_ns::_data_type::DATA_TYPE_XRF;

//   std::vector<QColor> Colors;
// //  Map_name_to_layer[Name_layer].Color_bar=Color_bar_widget->create_color_bar(Palette1,Map_pigment_data[Name_pigment1].Data_type,Name_pigment1,Map_pigment_data[Name_pigment1].Max_value_adjusted,Colors,Data_type_print1,Color_for_zero_value1);

//   Map_name_to_layer[Name_layer].Color_bar=Color_bar_widget->create_color_bar(Palette_layer, Map_pigment_data[Name_pigment1].Xray_data_type, Name_pigment1, Map_pigment_data[Name_pigment1].Max_value_adjusted, Colors, Data_type_print1, Color_for_zero_value1);

//   Map_name_to_layer[Name_layer].Color_bar=Color_bar_widget->create_color_bar(Palette1,_pigment_data_ns::_data_type::DATA_TYPE_LAB,Name_image1,Max_value,Colors,Data_type_print1,Color_for_zero_value1);

//   // assign the name of the element/pigment that produces the map
//   Map_name_to_layer[Name_layer].Color_bar_name=Name_image1;
//   Color_bar_widget->add_palette_layer(Name_layer);
//   // pass the palette to the layer
//   Layer->set_colormap(Color_bar_widget->Palettes[Palette1]->vec_proportions(),Colors,Color_bar_widget->Palettes[Palette1]->type());

//   Layer->update();

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
  Selected_tab=_w_tab_xmapslab_ns::_tabs::LAYERS_TAB;
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

void _window_xmapslab::update_layer(string Name)
{
  Map_name_to_layer[Name].Layer->update();
  GL_widget->update_texture(Name);

  GL_widget->update();
}

/*************************************************************************/

void _window_xmapslab::update_layer(int Pos)
{
  Selected_layer=Pos;
  update_layer(Vec_order_of_layers_by_name[Selected_layer]);
}

/*************************************************************************/

void _window_xmapslab::update_color_bar()
{
  Color_bar_widget->update_color_bar(Selected_tab);
}

/*************************************************************************/

void _window_xmapslab::update_color_bar_data_type_print(int Type1)
{
  Map_name_to_layer[Vec_order_of_layers_by_name[Selected_layer]].Color_bar->data_type_print(_palette_data_ns::_data_type_print(Type1));
  Map_name_to_layer[Vec_order_of_layers_by_name[Selected_layer]].Color_bar->update();

  Color_bar_widget->adjust_width(Project_data.Max_value);
}

/*************************************************************************/
// Visibility

void _window_xmapslab::change_button_state(int Row,int Col)
{
  bool Value=Map_name_to_layer[Vec_order_of_layers_by_name[Row]].Layer->state(Col);
  Map_name_to_layer[Vec_order_of_layers_by_name[Row]].Layer->state(Col,!Value);

  if (state()==_window_xmapslab_ns::_state::STATE_3D){
    // search for the nearest that is visible
    int Pos=-1;;
    for (Pos=Vec_order_of_layers_by_name.size()-1;Pos>=0;Pos--){
      if (Map_name_to_layer[Vec_order_of_layers_by_name[Pos]].Layer->state(0)==true) break;
    }

    if (Pos!=-1){
#ifdef MODE_3D_ACTIVE
      GL_widget_3D->update_data(Map_name_to_layer[Vec_order_of_layers_by_name[Pos]].Layer->image(),Map_name_to_layer[Vec_order_of_layers_by_name[Pos]].Layer->result_floats_image());
#endif
    }
    else{
#ifdef MODE_3D_ACTIVE
      GL_widget_3D->update_data(nullptr,nullptr);
#endif
    }
#ifdef MODE_3D_ACTIVE
    GL_widget_3D->update();
#endif
  }
  else GL_widget->update();
}

/*************************************************************************/
// Adjust the values to be multiple of 4, which is necessary for OpenCV

void _window_xmapslab::adjust_image_sizes(int &Width1, int &Height1)
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

QWizardPage *_window_xmapslab::createIntroPage()
{
  QWizardPage *page = new QWizardPage;
  page->setTitle("General information");

  QLabel *label = new QLabel(_window_xmapslab_ns::Help_string);

  label->setWordWrap(true);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(label);
  page->setLayout(layout);

  return page;
}

#ifndef UNIFIED
/*************************************************************************/

void _window_xmapslab::info_slot()
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
// Creates a bar chart
// For each visible layer its value and color are received

#ifdef STATISTIC_GRAPHS_ACTIVE
void _window_xmapslab::create_chart_bar(float Maximum_value,std::vector<float> &Values,std::vector<QColor> &Colors,std::vector<std::string> &Vec_element_names_aux)
{
  // creates the variables for the bar chart
  QBarSet *Set;
  QBarSeries *Series_bar = new QBarSeries();

  // computes the max value of all the values
//  float Max=-1;
  float Value;
  for (unsigned int i=0;i<Vec_element_names_aux.size();i++){
    Set=new QBarSet(QString::fromStdString(Vec_element_names_aux[i]));
    //Value=Map_name_to_element[Vec_element_names_aux[i]].Max_value;
    Value=Values[i];
//    if (Value>Max) Max=Value;

    // add the value to the series. For Log we need to remove the log 0
    if (Linear_adjust) Set->append(Value);
    else{
      if (Value<=0) cout << "<0 " << Value;
      Set->append(Value+1); // we add 1 to remove the problem with log
    }
    Set->setColor(Colors[i]);
    Series_bar->append(Set);
  }

  QChart *Chart = new QChart();
  Chart->addSeries(Series_bar);
  Chart->setTitle("Elements data");
//  Chart->setAnimationOptions(QChart::SeriesAnimations);

//  QStringList Categories;
//  Categories << "Elements" ;
//  QBarCategoryAxis *Axis_X = new QBarCategoryAxis();
//  Axis_X->append(Categories);
//  Chart->addAxis(Axis_X, Qt::AlignBottom);
//  Series->attachAxis(Axis_X);

  if (Linear_adjust){
    QValueAxis *Axis_Y = new QValueAxis();
    Axis_Y->setTitleText("PPM/AN");
    Axis_Y->setRange(0,Maximum_value);
    Chart->addAxis(Axis_Y, Qt::AlignLeft);
    Series_bar->attachAxis(Axis_Y);
  }
  else{
    QLogValueAxis *axisY = new QLogValueAxis();
    axisY->setTitleText("PPM/AN");
    axisY->setLabelFormat("%g");
    axisY->setBase(10.0);
    axisY->setMinorTickCount(-1);
    axisY->setRange(0,Maximum_value);
    Chart->addAxis(axisY, Qt::AlignLeft);
    Series_bar->attachAxis(axisY);
  }

  Chart->legend()->setVisible(true);
  Chart->legend()->setAlignment(Qt::AlignBottom);

  Chart_view= new QChartView(Chart);
  Chart_view->setRenderHint(QPainter::Antialiasing);
  Chart_view->setMinimumHeight(height()/3);

  // adjustment of the splitter
  if (Splitter_view->count()==1){
    // there is only the main display -> add the chart
    Splitter_view->insertWidget(0,Chart_view);
  }
  else{
    // There are the chart and main displays
    QWidget *Widget=Splitter_view->widget(0);
    // delete the first one -> the bar chart
    delete Widget;
    // insert the new bar chart
    Splitter_view->insertWidget(0,Chart_view);
  }

  if (Size_adjusted==false){
    Size_adjusted=true;
    Size_chart=height()/2;
    QList<int> Sizes={Size_chart,height()-Size_chart};
    Splitter_view->setSizes(Sizes);
  }
  else{
    QList<int> Sizes={Size_chart,height()-Size_chart};
    Splitter_view->setSizes(Sizes);
  }
}
#endif

/*************************************************************************/
#ifdef STATISTIC_GRAPHS_ACTIVE
void _window_xmapslab::create_chart_line(float Maximum_value, std::vector<float> &Values, std::vector<QColor> &Colors, std::vector<std::string> &Vec_element_names_aux)
{
  Q_UNUSED(Colors)
  QLineSeries *Series_line = new QLineSeries();

//  float Max=-1;
  float Value;
  for (unsigned int i=0;i<Vec_element_names_aux.size();i++){
    Value=Values[i];
//    if (Value>Max) Max=Value;
    if (Linear_adjust) Series_line->append(i,Value);
    else Series_line->append(i,Value+1); // we add 1 to remove the problem with log
  }

  QChart *Chart = new QChart();
  Chart->addSeries(Series_line);
  Chart->setTitle("Elements data");

//  QStringList Categories;
//  Categories << "Elements" ;
//  QBarCategoryAxis *Axis_X = new QBarCategoryAxis();
//  Axis_X->append(Categories);
//  Chart->addAxis(Axis_X, Qt::AlignBottom);
//  Series->attachAxis(Axis_X);

  QStringList Categories;
  for (unsigned int i=0;i<Vec_element_names_aux.size();i++){
   Categories.append(QString::fromStdString(Vec_element_names_aux[i]));
  }

  QBarCategoryAxis *AxisX = new QBarCategoryAxis();
  AxisX->append(Categories);
  Chart->addAxis(AxisX, Qt::AlignBottom);
  Series_line->attachAxis(AxisX);
  AxisX->setRange(QString::fromStdString(Vec_element_names_aux[0]),QString::fromStdString(Vec_element_names_aux[Vec_element_names_aux.size()-1]));

  if (Linear_adjust){
    QValueAxis *Axis_Y = new QValueAxis();
    Axis_Y->setTitleText("PPM/AN");
    Axis_Y->setRange(0,Maximum_value);
    Chart->addAxis(Axis_Y, Qt::AlignLeft);
    Series_line->attachAxis(Axis_Y);
  }
  else{
    QLogValueAxis *axisY = new QLogValueAxis();
    axisY->setTitleText("PPM/AN");
    axisY->setLabelFormat("%g");
    axisY->setBase(10.0);
    axisY->setMinorTickCount(-1);
    axisY->setRange(0,Maximum_value);
    Chart->addAxis(axisY, Qt::AlignLeft);
    Series_line->attachAxis(axisY);
  }

//  QLogValueAxis *axisY = new QLogValueAxis();
//  axisY->setTitleText("PPM");
//  axisY->setLabelFormat("%g");
//  axisY->setBase(10.0);
//  axisY->setMinorTickCount(-1);
//  axisY->setRange(0,Max);
//  Chart->addAxis(axisY, Qt::AlignLeft);
//  Series_line->attachAxis(axisY);

//  QValueAxis *Axis_Y = new QValueAxis();
//  Axis_Y->setTitleText("PPM");
//  Axis_Y->setRange(0,Max);
//  Chart->addAxis(Axis_Y, Qt::AlignLeft);
//  Series->attachAxis(Axis_Y);

  Chart->legend()->setVisible(true);
  Chart->legend()->setAlignment(Qt::AlignBottom);

  Chart_view= new QChartView(Chart);
  Chart_view->setRenderHint(QPainter::Antialiasing);
  Chart_view->setMinimumHeight(height()/3);

  if (Splitter_view->count()==1){
    Splitter_view->insertWidget(0,Chart_view);
  }
  else{
    QWidget *Widget=Splitter_view->widget(0);
    delete Widget;
    Splitter_view->insertWidget(0,Chart_view);
  }

  if (Size_adjusted==false){
    Size_adjusted=true;
    Size_chart=height()/2;
    QList<int> Sizes={Size_chart,height()-Size_chart};
    Splitter_view->setSizes(Sizes);
  }
  else{
    QList<int> Sizes={Size_chart,height()-Size_chart};
    Splitter_view->setSizes(Sizes);
  }
}
#endif
/*************************************************************************/
#ifdef STATISTIC_GRAPHS_ACTIVE
void _window_xmapslab::create_chart_pie(vector<float> &Values, std::vector<QColor> &Colors, std::vector<std::string> &Vec_element_names_aux)
{
  Q_UNUSED(Colors)

  QPieSlice *Slice;
  QPieSlice *Slice1;
  QPieSeries *Series_pie = new QPieSeries();
  QPieSeries *Series_pie1 = new QPieSeries();

//  float Max=-1;
  float Value;
  for (unsigned int i=0;i<Vec_element_names_aux.size();i++){
    Value=Values[i];
    Slice=new QPieSlice(QString::fromStdString(Vec_element_names_aux[i]),Value);
    Slice->setColor(Colors[i]);
    Series_pie->append(Slice);

    Slice1=new QPieSlice(QString::fromStdString(Vec_element_names_aux[i]),Value);
    Slice1->setColor(Colors[i]);
    Series_pie1->append(Slice1);
  }

  // this controls the labels
  Series_pie->setLabelsVisible();
  for(auto Slice: Series_pie->slices()){
      Slice->setLabel(QString("%1%").arg(100*Slice->percentage(), 0, 'f', 1));
  }

  QChart *Chart = new QChart();
  Chart->addSeries(Series_pie);
  Chart->addSeries(Series_pie1);
  Chart->setTitle("Elements data");

  // this controls the legends of the numbers
  const auto markers = Chart->legend()->markers(Series_pie);
  for (QLegendMarker *marker : markers) {
    QPieLegendMarker *pieMarker = qobject_cast<QPieLegendMarker *>(marker);
    // this remove the legend of the numbers
    pieMarker->setVisible(false);
  }

  // this controls the legends of the elements
  const auto markers1 = Chart->legend()->markers(Series_pie1);
  for (QLegendMarker *marker : markers1) {
    QPieLegendMarker *pieMarker = qobject_cast<QPieLegendMarker *>(marker);
    pieMarker->setVisible(true);
    pieMarker->setLabel(QString("%1").arg(pieMarker->slice()->label()));
  }

  Chart->legend()->setVisible(true);
  Chart->legend()->setAlignment(Qt::AlignBottom);

  Chart_view= new QChartView(Chart);
  Chart_view->setRenderHint(QPainter::Antialiasing);
  Chart_view->setMinimumHeight(height()/3);

  if (Splitter_view->count()==1){
    Splitter_view->insertWidget(0,Chart_view);
  }
  else{
    QWidget *Widget=Splitter_view->widget(0);
    delete Widget;
    Splitter_view->insertWidget(0,Chart_view);
  }

  // adjust the sizes
  if (Size_adjusted==false){
    Size_adjusted=true;
    Size_chart=height()/2;
    QList<int> Sizes={Size_chart,height()-Size_chart};
    Splitter_view->setSizes(Sizes);
  }
  else{
    QList<int> Sizes={Size_chart,height()-Size_chart};
    Splitter_view->setSizes(Sizes);
  }
}
#endif

/*************************************************************************/
// creates and updates the chart
// Previous it get the data of all the visble layers

#ifdef STATISTIC_GRAPHS_ACTIVE
void _window_xmapslab::update_chart(int Pos_x, int Pos_y)
{
  if (Num_elements_computed>0 && state()==_window_xmapslab_ns::_state::STATE_STATISTICS){
    float Value;
    float Max_value;
    float Maximum_value=-1;
    QColor Color;
    std::vector<float> Values;
    std::vector<QColor> Colors;
    std::string Name_layer;
    std::string Element;
    bool Mode_pos=true;

    Statistics_x=Pos_x;
    Statistics_y=Pos_y;

    if (Pos_x<0 || Pos_y<0) Mode_pos=false; // there is not sample position

    // get only the layers that are selected (Pen)
    std::vector<std::string> Vec_element_names_aux;
    for (unsigned int Row=0;Row<Vec_order_of_layers_by_name.size();Row++){
      Name_layer=Vec_order_of_layers_by_name[Row];
      if (Map_name_to_layer[Name_layer].Layer->layer_type()==_layer_xmapslab_ns::_layer_type::LAYER_TYPE_MAP_DISTANCE || Map_name_to_layer[Name_layer].Layer->layer_type()==_layer_xmapslab_ns::_layer_type::LAYER_TYPE_MAP_TRIANGULATION){
        if (Map_name_to_layer[Name_layer].Layer->state(1)==true) Vec_element_names_aux.push_back(Name_layer);
      }
    }

    // get the data
    Values.resize(Vec_element_names_aux.size());
    Colors.resize(Vec_element_names_aux.size());

    shared_ptr<_layer_xmapslab> Layer=nullptr;
    std::vector<std::string> Vec_element_short_names(Vec_element_names_aux.size());

    for (unsigned int i=0;i<Vec_element_names_aux.size();i++){
      // get the layer
      Name_layer=Vec_element_names_aux[i];

      QString Name_aux=QString::fromStdString(Name_layer);
      QStringList Tokens=Name_aux.split('_');

      Vec_element_short_names[i]=(Tokens[1]+Tokens[Tokens.size()-1]).toStdString();

      // assign the pointer
      Layer=Map_name_to_layer[Name_layer].Layer;

      // get the maximum value for the element
      Element=Map_name_of_layer_to_name_of_element[Name_layer];
      Max_value=Map_name_to_element[Element].Max_value_adjusted;

      if (Max_value>Maximum_value) Maximum_value=Max_value;

      // get the data for the selected pixel
      if (Mode_pos==true){
        // get the normalized value for the given position
        if (Layer->layer_type()==_layer_xmapslab_ns::_layer_type::LAYER_TYPE_MAP_DISTANCE){ //????
          Value=static_pointer_cast<_layer_map_distance_ui>(Layer)->get_value(Pos_x,Pos_y);
        }
        else{
          if (Layer->layer_type()==_layer_xmapslab_ns::_layer_type::LAYER_TYPE_MAP_TRIANGULATION){
            Value=static_pointer_cast<_layer_map_triangulation_ui>(Layer)->get_value(Pos_x,Pos_y);
          }
        }

        // adjust the final value
        Values[i]=Max_value*Value;
      }
      else{// get the data for all the image
        Values[i]=Max_value;
      }

      // get the end color
      if (Layer->layer_type()==_layer_xmapslab_ns::_layer_type::LAYER_TYPE_MAP_DISTANCE){
        Color=static_pointer_cast<_layer_map_distance_ui>(Map_name_to_layer[Name_layer].Layer)->end_color();
      }
      else{
        if (Layer->layer_type()==_layer_xmapslab_ns::_layer_type::LAYER_TYPE_MAP_TRIANGULATION){
          Color=static_pointer_cast<_layer_map_triangulation_ui>(Map_name_to_layer[Name_layer].Layer)->end_color();
        }
      }

      Colors[i]=Color;
    }

    if (Values.size()>0){
      switch (Chart_mode) {
      case _window_xmapslab_ns::_chart_mode::CHART_MODE_BAR:create_chart_bar(Maximum_value,Values,Colors,Vec_element_short_names);break;
      case _window_xmapslab_ns::_chart_mode::CHART_MODE_LINE:create_chart_line(Maximum_value,Values,Colors,Vec_element_short_names);break;
      case _window_xmapslab_ns::_chart_mode::CHART_MODE_PIE:create_chart_pie(Values,Colors,Vec_element_short_names);break;
      }
    }
  }
}
#endif

/*************************************************************************/

void _window_xmapslab::reverse_col(int Col)
{
  bool Value;

  for (unsigned int Row=0;Row<Vec_order_of_layers_by_name.size();Row++){
    Value=Map_name_to_layer[Vec_order_of_layers_by_name[Row]].Layer->state(Col);
    Map_name_to_layer[Vec_order_of_layers_by_name[Row]].Layer->state(Col,!Value);
  }

#ifdef STATISTIC_GRAPHS_ACTIVE
  if (Col==1) update_chart(Statistics_x,Statistics_y);
#endif

  GL_widget->update();
}

/*************************************************************************/

#ifdef STATISTIC_GRAPHS_ACTIVE
void _window_xmapslab::create_chart_bar_histogram(vector<int> &Values, std::vector<QColor> &Colors)
{
  Q_UNUSED(Colors)
  QLineSeries *Series_line = new QLineSeries();

  float Max=-1;
  float Value;
  for (unsigned int i=0;i<Values.size();i++){
    Value=Values[i];
    if (Value>Max) Max=Value;
    Series_line->append(i,Value);
  }

  QValueAxis *Axis_Y = new QValueAxis;
  Axis_Y->setRange(0,roundf(Max*1.15));
  Axis_Y->setTickCount(5);
  Axis_Y->setLabelFormat("%.2f");

  QChart *Chart = new QChart();
  Chart->addSeries(Series_line);
  Chart->legend()->hide();
  Chart->createDefaultAxes();
  Chart->setTitle("Elements data");

//  Chart->legend()->setVisible(true);
//  Chart->legend()->setAlignment(Qt::AlignBottom);

//  Series_line->attachAxis(Axis_Y); ???

//  if (Chart_view!=nullptr) delete Chart_view;

  Chart_view= new QChartView(Chart);
  Chart_view->setRenderHint(QPainter::Antialiasing);
  Chart_view->setMinimumHeight(height()/3);

  if (Splitter_view->count()==1){
    Splitter_view->insertWidget(0,Chart_view);
  }
  else{
    QWidget *Widget=Splitter_view->widget(0);
    delete Widget;
    Splitter_view->insertWidget(0,Chart_view);
  }

  if (Size_adjusted==false){
    Size_adjusted=true;
    Size_chart=height()/2;
    QList<int> Sizes={Size_chart,height()-Size_chart};
    Splitter_view->setSizes(Sizes);
  }
  else{
    QList<int> Sizes={Size_chart,height()-Size_chart};
    Splitter_view->setSizes(Sizes);
  }
}
#endif

/*************************************************************************/

#ifdef STATISTIC_GRAPHS_ACTIVE
void _window_xmapslab::update_histogram()
{
  if (Num_elements_computed>0 && state()==_window_xmapslab_ns::_state::STATE_HISTOGRAM){
    std::vector<int> Values(256,0);
    if (Map_name_to_layer[Vec_order_of_layers_by_name[Selected_layer]].Layer->layer_type()==_layer_xmapslab_ns::_layer_type::LAYER_TYPE_MAP_DISTANCE || Map_name_to_layer[Vec_order_of_layers_by_name[Selected_layer]].Layer->layer_type()==_layer_xmapslab_ns::_layer_type::LAYER_TYPE_MAP_TRIANGULATION){
      std::string Layer_name;
      Layer_name=Vec_order_of_layers_by_name[Selected_layer];

      Values=Map_name_to_layer[Layer_name].Layer->vec_values_histogram();
    }

    create_chart_bar_histogram(Values,Histogram_colors);
  }
}
#endif

#ifdef STATISTIC_GRAPHS_ACTIVE
void _window_xmapslab::compute_histogram_colors()
{
  QColor Color;
//  float Factor=4608/256; // step 42
//  int Value;
  Histogram_colors.resize(256);

  for (int i=0;i<256;i++){
//    Value=int(roundf(float(i)*Factor));
    Color.setHsv(i,255,255);
    Histogram_colors[i]=Color.toRgb();
  }
}
#endif

/*************************************************************************/

void _window_xmapslab::save_positions_image(std::string Layer)
{
  int White_space=10;
//  int Pos_x;
//  int Pos_y;

  cv::Mat Image=Map_name_to_layer[Layer].Layer->image()->clone();
  float Width1=float(Image.cols-1);
  float Height1=float(Image.rows-1);

  cv::flip(Image,Image,0);

  QImage image(Image.data,Image.cols,Image.rows,static_cast<int>(Image.step),QImage::Format_ARGB32);
  image.rgbSwapped();

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

/*************************************************************************/

void _window_xmapslab::save_composed_image_slot()
{
  int Line_width=5;

  cv::Mat Image;
  GL_widget->get_composed_image(&Image);

//  float Width1=float(Image.cols-1);
//  float Height1=float(Image.rows-1);

  cv::flip(Image,Image,0);

  QImage image(Image.data,Image.cols,Image.rows,static_cast<int>(Image.step),QImage::Format_ARGB32);
  image.rgbSwapped();

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

void _window_xmapslab::save_image_section(string File_name, string Name, float Value, bool Add_original_image, bool Add_colorbar)
{
  QFont Normal_font=QApplication::font();
  int Normal_font_size=int(float(Normal_font.pointSize())*Print_font_factor);
  Normal_font.setPointSize(Normal_font_size);

  // compute the space of a '0'
  QFontMetrics Font_metric(Normal_font);
  QRect Rect_char=Font_metric.boundingRect('0');
  int Normal_font_pixels_width=Rect_char.width();
  //  int Normal_font_pixels_height=Rect_char.height();

  // color box. It must be odd
//  int Color_box_width=int(roundf(float(Normal_font_pixels_width)*_color_bar_abstract_ns::COLOR_BOX_FACTOR));
//  if (Color_box_width<_color_bar_abstract_ns::COLOR_BOX_MIN) Color_box_width=_color_bar_abstract_ns::COLOR_BOX_MIN;
//  if (Color_box_width%2!=0) Color_box_width++;

  // The image of the selected layer
  cv::Mat Image_layer_opencv=Map_name_to_layer[Name].Layer->image()->clone();
  cv::flip(Image_layer_opencv,Image_layer_opencv,0);

  //
  int Width1=Image_layer_opencv.cols-1;
  int Height1=Image_layer_opencv.rows-1;

  // change form OpenCV to Qt format
  QImage Image_layer_qt(Image_layer_opencv.data,Image_layer_opencv.cols,Image_layer_opencv.rows,static_cast<int>(Image_layer_opencv.step),QImage::Format_ARGB32);
  Image_layer_qt.rgbSwapped();

  // cropped image
  int x, y, Width, Height;
  GL_widget->get_image_section(x,y,Width,Height);
  QRect Rect(x, y, Width, Height);
  QImage Image_layer_cropped_qt = Image_layer_qt.copy(Rect);

  // The original color image
  QImage Image_original_cropped_qt;

  if (Add_original_image==true){
    cv::Mat Image_original_opencv=Map_name_to_layer[Vec_order_of_layers_by_name[0]].Layer->image()->clone();
    cv::flip(Image_original_opencv,Image_original_opencv,0);
    // change form OpenCV to Qt format
    QImage Image_original_qt(Image_original_opencv.data,Image_original_opencv.cols,Image_original_opencv.rows,static_cast<int>(Image_original_opencv.step),QImage::Format_ARGB32);
    Image_original_qt.rgbSwapped();

    // cropped image
    Image_original_cropped_qt = Image_original_qt.copy(Rect);
  }

  //
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

  int Color_bar_width=0;
  if (Add_colorbar==true) Color_bar_width=_w_color_bar::total_width(Value,Normal_font);

  // if the image height is less than Color_bar_width, the width og the final image will be Color_bar_width
  int Image_width=Image_layer_cropped_qt.width();
  int Image_height=Image_layer_cropped_qt.height();
  if (Image_height<Color_bar_width) Image_height=Color_bar_width;

  // parameters
  int White_space=5;
  int Line_width=3;

  // WS=white space  LW=line width IW=image width WC=width_color_bar
  // vertical: WS+LW+WS+IH+WS+LW+WS
  int Image_total_width;
  int Image_total_height;

  if (Add_original_image==true){
    if (Add_colorbar==true){
      // horizontal : WS+LW+WS+IW+WS+IW+WS+LW+WS+WS+WC+WS -> 7WS+2LW+2*IW+WC
//       Image_total_width=2*Image_width+Color_bar_width+7*White_space+2*Line_width+Color_box_width;
      Image_total_width=2*Image_width+Color_bar_width+7*White_space+2*Line_width;
    }
    else{
      // horizontal : WS+LW+WS+IW+WS+IW+WS+LW+WS -> 7WS+2LW+2*IW+WC
      Image_total_width=2*Image_width+5*White_space+2*Line_width;
    }
    Image_total_height=Image_height+4*White_space+2*Line_width;
  }
  else{
    // horizontal : WS+LW+WS+IW+WS+LW+WS+WS+WC+WS -> 6WS+2LW+IW+WC
//    Image_total_width=Image_width+Color_bar_width+6*White_space+2*Line_width+Color_box_width;
    if (Add_colorbar==true){
      //    Image_total_width=Image_width+Color_bar_width+6*White_space+2*Line_width+Color_box_width;
      Image_total_width=Image_width+Color_bar_width+6*White_space+2*Line_width;
    }
    else{
      Image_total_width=Image_width+4*White_space+2*Line_width;
    }

    Image_total_height=Image_height+4*White_space+2*Line_width;
  }

  QImage Image_result(Image_total_width,Image_total_height,QImage::Format_ARGB32);
  Image_result.fill(Qt::white);

  //
  QPainter Painter(&Image_result);
  // Draw the image of the layer
  if (Add_original_image){
    Painter.drawImage(2*White_space+Line_width,2*White_space+Line_width,Image_original_cropped_qt);
    Painter.drawImage(3*White_space+Line_width+Image_width,2*White_space+Line_width,Image_layer_cropped_qt);
  }
  else{
    Painter.drawImage(2*White_space+Line_width,2*White_space+Line_width,Image_layer_cropped_qt);
  }

  QPen Previous_pen=Painter.pen();

  QPen Pen;
  Pen.setWidth(Line_width);
  Painter.setPen(Pen);

  // Draw the black border
  if (Add_original_image){
    // horizontal : WS+LW+WS+IW+WS+IW+WS+LW
    QRect Rect2(White_space,White_space,2*Image_width+3*White_space+2*Line_width,Image_height+2*White_space+2*Line_width);
    Painter.drawRect(Rect2);
  }
  else{
    // horizontal : WS+LW+WS+IW+WS+LW
    QRect Rect2(White_space,White_space,Image_width+2*White_space+2*Line_width,Image_height+2*White_space+2*Line_width);
    Painter.drawRect(Rect2);
  }

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
  Painter.drawText(QPointF(Image_result.width()-Width_title/2-Color_bar_width/2,1.5*Font_aux_pixels_height),Clipped_text); // 1+1/2

  QRect Rect3(Image_result.width()-Color_bar_width, White_space+2*Font_aux_pixels_height, Color_bar_width,Image_layer_cropped_qt.height()-2*White_space-2*Line_width-2*Font_aux_pixels_height);

  Painter.setFont(Normal_font);
  // Draw the color bar
  if (Map_name_to_layer[Name].Color_bar->palette_type()==_palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE){
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
  }
  Painter.end();

  QString Dir(Project_dir);

  Image_result.save(QString::fromStdString(File_name),"PNG");

  QMessageBox::information(this,tr("Information"),tr("The image section has been correctly saved"));
}

/*************************************************************************/

void _window_xmapslab::save_image_section_slot()
{
  QString Subdir;
  std::string Name=Vec_order_of_layers_by_name[Selected_layer];
  float Value=Project_data.Max_value;

  if (Map_name_to_layer[Name].Layer->xray_data_type()==_common_ns::_xray_data_type::XRAY_DATA_TYPE_XRF){
    //XRF
    Subdir="/xrf/maps/";
  }
  else{
    //XRD
    Subdir="/xrd/maps/";
  }

  QFileDialog Dialog(this,"Save graph",Project_dir+Subdir,"*.png");
  Dialog.setWindowModality(Qt::WindowModal);
  Dialog.setAcceptMode(QFileDialog::AcceptSave);
  Dialog.setDefaultSuffix("png");
  Dialog.selectFile(QString::fromStdString(Name+"_section"));
  if (Dialog.exec()== QDialog::Accepted){
    QString File_name=Dialog.selectedFiles().at(0);
    bool Add_color_image=false;
    bool Add_colorbar=false;

    _w_options_image_section W_dialog(this,&Add_color_image,&Add_colorbar);
    W_dialog.exec();

    save_image_section(File_name.toStdString(), Name, Value, Add_color_image, Add_colorbar);
  }
}

/*************************************************************************/

// void _window_xmapslab::selected_image(std::string Image_name)
// {
//   Mapping_selected_image_name=Image_name;

//   for (unsigned int i=0;i<Vec_order_mapping->size();i++){
//     if ((*Vec_order_mapping)[i]==Image_name){
//       Mapping_selected_image_index=i;
//       break;
//     }
//   }
//   Mapping_nodes_editor_maps_tab->set_selected_item(Mapping_selected_image_index);

// #ifdef NODE_EDITOR_ACTIVE
//   GL_widget_ge->update_texture(Image_name);
// #endif
// }

// void _window_xmapslab::selected_image(std::string Image_name)
// {
//   Mapping_selected_image_name=Image_name;

//   for (unsigned int i=0;i<Vec_order_mapping->size();i++){
//     if ((*Vec_order_mapping)[i]==Image_name){
//       Mapping_selected_image_index=i;
//       break;
//     }
//   }
//   Mapping_nodes_editor_maps_tab->set_selected_item(Mapping_selected_image_index);

//   // check the class of the filter: if binary or element or colormap, the palette is disabled
//   if (Map_filters[Image_name]->filter_class()==_filter_ns::_filter_class::FILTER_CLASS_COMBINATION || Map_filters[Image_name]->filter_class()==_filter_ns::_filter_class::FILTER_CLASS_BINARY){
//     if (Map_filters[Image_name]->filter_class()==_filter_ns::_filter_class::FILTER_CLASS_COMBINATION){
//       Mapping_nodes_editor_maps_tab->enable_palette(); // only for combinations. For binary it will be fixed
//     }
//     Mapping_nodes_editor_maps_tab->enable_add_to_layers_button();
//   }
//   else{
//     Mapping_nodes_editor_maps_tab->disable_palette();
//     if (Map_filters[Image_name]->filter_class()==_filter_ns::_filter_class::FILTER_CLASS_IMAGE || Map_filters[Image_name]->filter_class()==_filter_ns::_filter_class::FILTER_CLASS_ELEMENT){
//       Mapping_nodes_editor_maps_tab->disable_add_to_layers_button();
//     }
//   }

//   GL_widget_ge->update_texture(Image_name);
// }

void _window_xmapslab::selected_image(std::string Image_name)
{
  Mapping_selected_image_name=Image_name;

  for (unsigned int i=0;i<Vec_order_mapping->size();i++){
    if ((*Vec_order_mapping)[i]==Image_name){
      Mapping_selected_image_index=i;
      break;
    }
  }
  Mapping_nodes_editor_maps_tab->set_selected_item(Mapping_selected_image_index);

  // check the class of the filter: if binary or element or colormap, the palette is disabled
  if (Map_filters[Image_name]->filter_class()==_filter_ns::_filter_class::FILTER_CLASS_COMBINATION || Map_filters[Image_name]->filter_class()==_filter_ns::_filter_class::FILTER_CLASS_BINARY){
    Mapping_nodes_editor_maps_tab->enable_palette();
    Mapping_nodes_editor_maps_tab->enable_add_to_layers_button();
  }
  else{
    Mapping_nodes_editor_maps_tab->disable_palette();
    if (Map_filters[Image_name]->filter_class()==_filter_ns::_filter_class::FILTER_CLASS_IMAGE || Map_filters[Image_name]->filter_class()==_filter_ns::_filter_class::FILTER_CLASS_ELEMENT){
      Mapping_nodes_editor_maps_tab->disable_add_to_layers_button();
    }
  }

  GL_widget_ge->update_texture(Image_name);
  //  refresh_mapping_image(Image_name);
}

/*************************************************************************/

#ifdef NODE_EDITOR_ACTIVE
void _window_xmapslab::create_mapping()
{
  if (Created_filter_list==false) create_filter_list();
}

/*************************************************************************/

void _window_xmapslab::create_nodes_editor_widget()
{
  QSizePolicy Q(QSizePolicy::Expanding,QSizePolicy::Expanding);

  QWidget *Widget_ge=new QWidget(this);

  // layout for results
  QHBoxLayout *Result_horizontal_frame = new QHBoxLayout;
  Result_horizontal_frame->setContentsMargins(1,1,1,1);

//  QGLFormat Format;
//  Format.setDoubleBuffer(true);
//  Format.setRgba(true);
//  Format.setAlpha(true);
//  QGLFormat::setDefaultFormat(Format);

  // the result widget
  QWidget *Result_widget=new QWidget(Splitter_node_editor);

  // frame widget for OpenGL windows
  QFrame *Framed_widget= new QFrame(Result_widget);
  Framed_widget->setSizePolicy(Q);
  Framed_widget->setFrameStyle(QFrame::Panel);
  Framed_widget->setLineWidth(3);

  // OpenGL windows inside the frame widget
  GL_widget_ge=new _gl_widget_xmapslab_ge(this,Framed_widget);// Splitter_node_editor
  GL_widget_ge->setSizePolicy(Q);
  GL_widget_ge->setMinimumSize(400,400);

  // the layout of the central widget
  QHBoxLayout *Frame_horizontal_frame = new QHBoxLayout;
  // add the widgets of the result window
  Frame_horizontal_frame->addWidget(GL_widget_ge);

  Framed_widget->setLayout(Frame_horizontal_frame);

  // This is the table of the result window
  Tab_widget_mapping_visualization = new QTabWidget(Result_widget);

  // Show ****
  QWidget* W_nodes_editor_show=new QWidget;
  QVBoxLayout* Vboxlayout_nodes_editor_show=new QVBoxLayout;

  // Show graphs
  QGroupBox *Groupbox_show_binary_data=new QGroupBox("Data");
  Groupbox_show_binary_data->setAlignment(Qt::AlignHCenter);

  QGridLayout *Gridlayout_show_binary_data=new QGridLayout;

  QLabel *Label_show_binary_data1=new QLabel("True");
  QLabel *Label_show_binary_data2=new QLabel("False");

  // colors
  QFrame *Frame_color_true=new QFrame;
  Frame_color_true->setFrameStyle(QFrame::Panel);
  Frame_color_true->setFixedSize(15,15);

  QFrame *Frame_color_false=new QFrame;
  Frame_color_false->setFrameStyle(QFrame::Panel);
  Frame_color_false->setFixedSize(15,15);

  if (Color_for_zero_value==_color_map_ns::_color_for_zero_value::COLOR_ZERO_VALUE_WHITE){
    Frame_color_true->setStyleSheet("background-color: black;");
    Frame_color_false->setStyleSheet("background-color: white;");
  }
  else{
    Frame_color_true->setStyleSheet("background-color: white;");
    Frame_color_false->setStyleSheet("background-color: black;");
  }

  Gridlayout_show_binary_data->addWidget(Label_show_binary_data1,0,0,Qt::AlignRight);
  Gridlayout_show_binary_data->addWidget(Frame_color_true,0,1,Qt::AlignLeft);
  Gridlayout_show_binary_data->addWidget(Label_show_binary_data2,1,0,Qt::AlignRight);
  Gridlayout_show_binary_data->addWidget(Frame_color_false,1,1,Qt::AlignLeft);

  Groupbox_show_binary_data->setLayout(Gridlayout_show_binary_data);

  //
  Vboxlayout_nodes_editor_show->addWidget(Groupbox_show_binary_data);
  Vboxlayout_nodes_editor_show->addStretch();

  W_nodes_editor_show->setLayout(Vboxlayout_nodes_editor_show);

  // and the widgets to the tab
  Mapping_nodes_editor_maps_tab=new _nodes_editor_maps_tab(this);
  Mapping_filters_tab=new _filters_tab(this);

  Tab_widget_mapping_visualization->addTab(Mapping_nodes_editor_maps_tab, tr("Maps"));
  Tab_widget_mapping_visualization->addTab(Mapping_filters_tab, tr("Filters"));
  Tab_widget_mapping_visualization->addTab(W_nodes_editor_show, tr("Show"));

  QFontMetrics Font_metric(Tab_widget_mapping_visualization->font());
//  int Width_text = Font_metric.width("M");
  int Width_text = Font_metric.horizontalAdvance("M");
  Tab_widget_mapping_visualization->setMaximumWidth(Width_text*_window_xmapslab_ns::WIDTH_TAB_CHARS);

  // add the widgets of the result window
  Result_horizontal_frame->addWidget(Framed_widget);
  //Horizontal_frame->addWidget(GL_widget);
  Result_horizontal_frame->addWidget(Tab_widget_mapping_visualization);

  // the layout of the result widget
  Result_widget->setLayout(Result_horizontal_frame);

  // now the edition window
  QWidget *Edit_widget=new QWidget(Splitter_node_editor);

  QHBoxLayout *Edit_horizontal_frame= new QHBoxLayout;

  // the scene for designing the filter
  Scene = new _graphics_scene(this);

  QFontMetrics fm(Scene->font());
//  int w = fm.width("A");
  int w = fm.horizontalAdvance("A");
  int h = fm.height();

  Nodes_editor= new _nodes_editor(Edit_widget);
  Nodes_editor->install(Scene);
  Nodes_editor->set_font_sizes(h,w);
  Nodes_editor->add_grid();

//  int res=-w*_ne_common_ns::NUM_CHARS_LINE_BLOCK;

  // the view for the scene
  Graphics_view = new _graphics_view(Nodes_editor);
  Graphics_view->setSceneRect(_ne_common_ns::SCENE_ORIGIN,_ne_common_ns::SCENE_ORIGIN,_ne_common_ns::SCENE_WIDTH,_ne_common_ns::SCENE_WIDTH);
  Graphics_view->setAlignment(Qt::AlignLeft | Qt::AlignTop);
  Graphics_view->setRenderHint(QPainter::Antialiasing, true);
  Graphics_view->resetTransform();

  Graphics_view->setScene(Scene);
//  Graphics_view->setSceneRect(-100,-100,5000,5000);
//  Graphics_view->setRenderHint(QPainter::Antialiasing, true);

  Graphics_view->horizontalScrollBar()->setValue(-1000);
  Graphics_view->verticalScrollBar()->setValue(-1000);

  // widget for the filters
  QWidget *Filters_widget=new QWidget(Edit_widget);
  Filters_widget->setMaximumWidth(Width_text*_window_xmapslab_ns::WIDTH_TAB_CHARS);
  Filters_widget->setMinimumWidth(Width_text*_window_xmapslab_ns::WIDTH_TAB_CHARS);
  QVBoxLayout *Filters_vertical_frame= new QVBoxLayout;

  Filters_list=new _tree_widget(this,Edit_widget);
  Filters_list->setHeaderLabel(tr("Filter"));
  Filters_list->setIndentation(0);

  Filters_list->setContextMenuPolicy(Qt::CustomContextMenu);

//  connect(Filters_list, SIGNAL(itemClicked(QTreeWidgetItem *, int)),this,SLOT(filter_selected_slot(QTreeWidgetItem *, int))); !!

  Filters_list->setDragEnabled(true);
  Filters_list->setSelectionMode(QAbstractItemView::SingleSelection);
  Filters_list->setAcceptDrops(false);
  Filters_list->setDropIndicatorShown(true);
  Filters_list->setDragDropMode(QAbstractItemView::DragOnly);

  Filters_vertical_frame->addWidget(Filters_list);

  Filters_widget->setLayout(Filters_vertical_frame);

  // layout
  Edit_horizontal_frame->addWidget(Filters_widget);
  Edit_horizontal_frame->addWidget(Graphics_view);
  // set the layout
  Edit_widget->setLayout(Edit_horizontal_frame);

  // the main tab widget that has the editor window and the result window
  Tab_widget_ge=new QTabWidget(Splitter_node_editor);
  Tab_widget_ge->insertTab(0,Edit_widget,tr("Node Editor"));
  Tab_widget_ge->insertTab(1,Result_widget,tr("Results"));
  Tab_widget_ge->setTabEnabled(0,true);
  Tab_widget_ge->setTabEnabled(1,true);

  // connect the tabs for changing form edition to visualization
  connect(Tab_widget_ge,SIGNAL(currentChanged(int)),this,SLOT(tab_ge_clicked_slot(int)));

  // the layout of the central widget
  QHBoxLayout *Horizontal_main = new QHBoxLayout;
  Horizontal_main->setSpacing(10);
  Horizontal_main->setContentsMargins(3,3,3,3);
  Horizontal_main->addWidget(Tab_widget_ge);

  Widget_ge->setLayout(Horizontal_main);

  Splitter_node_editor->addWidget(Widget_ge);

  Splitter_node_editor->hide();
}

/*************************************************************************/

void _window_xmapslab::create_filter_list()
{
  QFont Font;
  Font.setBold(true);

  Created_filter_list=true;

  // Image
  _tree_widget_item *Image_type = new _tree_widget_item(Filters_list,ItemType1);
  //  Placement_and_Image_type->setBackgroundColor(0,_window_ns::Stippling_separator_color);
  Image_type->setFont(0,Font);
  Image_type->setText(0, tr("Image"));
  Image_type->setExpanded(true);

  _tree_widget_item *Image = new _tree_widget_item(Image_type,ItemType2);
  string Name=Vec_order_of_layers_by_name[0];
  Image->setData(0,0,QString::fromStdString(Name));
  Image->setData(0,1,int(_filter_ns::_filter_type::FILTER_TYPE_IMAGE));
  Image->setToolTip(0,QString::fromStdString(_filter_ns::Filter_name_text[_filter_ns::_filter_type::FILTER_TYPE_IMAGE].Description));
  Image->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);

  // Elements
  _tree_widget_item *Element_type = new _tree_widget_item(Filters_list,ItemType1);
  //  Placement_and_Element_type->setBackgroundColor(0,_window_ns::Stippling_separator_color);
  Element_type->setFont(0,Font);
  Element_type->setText(0, tr("Elements"));
  Element_type->setExpanded(true);

  QTreeWidgetItem *Element;

  int Num_layers=int(Vec_order_of_layers_by_name.size());
  for (int i=0;i<Num_layers;i++){
    string Name=Vec_order_of_layers_by_name[i];
    if (Map_name_to_layer[Name].Layer->layer_type()!=_layer_xmapslab_ns::_layer_type::LAYER_TYPE_BASIC){
#ifdef DEFINE_FILTER_ELEMENT
      Element= new QTreeWidgetItem(Element_type,ItemType2);
      Element->setData(0,0,QString::fromStdString(Name));
      Element->setData(0,1,int(_filter_ns::_filter_type::FILTER_TYPE_ELEMENT));
      Element->setToolTip(0,QString::fromStdString(_filter_ns::Filter_name_text[_filter_ns::_filter_type::FILTER_TYPE_ELEMENT].Description));
#endif
    }
  }

  // Conversion
  _tree_widget_item *Conversion_type = new _tree_widget_item(Filters_list,ItemType1);
  Conversion_type->setFont(0,Font);
  Conversion_type->setText(0, tr("Conversion operations"));
  Conversion_type->setExpanded(true);

#ifdef DEFINE_FILTER_CONVERSION_BIN
  _tree_widget_item *Conversion_to_bin = new _tree_widget_item(Conversion_type,ItemType2);
  Conversion_to_bin->setData(0,0,tr(_filter_ns::Text_list_conversion_binary.c_str()));
  Conversion_to_bin->setData(0,1,int(_filter_ns::_filter_type::FILTER_TYPE_CONVERSION_TO_BIN_OP));
  Conversion_to_bin->setToolTip(0,QString::fromStdString(_filter_ns::Filter_name_text[_filter_ns::_filter_type::FILTER_TYPE_CONVERSION_TO_BIN_OP].Description));
  Conversion_to_bin->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
#endif

#ifdef DEFINE_FILTER_CONVERSION_COLOR_BIN
  _tree_widget_item *Conversion_color_to_bin = new _tree_widget_item(Conversion_type,ItemType2);
  Conversion_color_to_bin->setData(0,0,tr(_filter_ns::Text_list_conversion_color_binary.c_str()));
  Conversion_color_to_bin->setData(0,1,int(_filter_ns::_filter_type::FILTER_TYPE_CONVERSION_COLOR_TO_BIN_OP));
  Conversion_color_to_bin->setToolTip(0,QString::fromStdString(_filter_ns::Filter_name_text[_filter_ns::_filter_type::FILTER_TYPE_CONVERSION_COLOR_TO_BIN_OP].Description));
  Conversion_color_to_bin->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
#endif

  // Binary
  _tree_widget_item *Logic_type = new _tree_widget_item(Filters_list,ItemType1);
  Logic_type->setFont(0,Font);
  Logic_type->setText(0, tr("Binary operations"));
  Logic_type->setExpanded(true);

#ifdef DEFINE_FILTER_LOGIC_NOT
  _tree_widget_item *Logic_not = new _tree_widget_item(Logic_type,ItemType2);
  Logic_not->setData(0,0,tr(_filter_ns::Text_list_binary_not.c_str()));
  Logic_not->setData(0,1,int(_filter_ns::_filter_type::FILTER_TYPE_LOGIC_NOT_OP));
  Logic_not->setToolTip(0,QString::fromStdString(_filter_ns::Filter_name_text[_filter_ns::_filter_type::FILTER_TYPE_LOGIC_NOT_OP].Description));
  Logic_not->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
#endif

#ifdef DEFINE_FILTER_LOGIC_AND
  _tree_widget_item *Logic_and = new _tree_widget_item(Logic_type,ItemType2);
  Logic_and->setData(0,0,tr(_filter_ns::Text_list_binary_and.c_str()));
  Logic_and->setData(0,1,int(_filter_ns::_filter_type::FILTER_TYPE_LOGIC_AND_OP));
  Logic_and->setToolTip(0,QString::fromStdString(_filter_ns::Filter_name_text[_filter_ns::_filter_type::FILTER_TYPE_LOGIC_AND_OP].Description));
  Logic_and->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
#endif

#ifdef DEFINE_FILTER_LOGIC_OR
  _tree_widget_item *Logic_or = new _tree_widget_item(Logic_type,ItemType2);
  Logic_or->setData(0,0,tr(_filter_ns::Text_list_binary_or.c_str()));
  Logic_or->setData(0,1,int(_filter_ns::_filter_type::FILTER_TYPE_LOGIC_OR_OP));
  Logic_or->setToolTip(0,QString::fromStdString(_filter_ns::Filter_name_text[_filter_ns::_filter_type::FILTER_TYPE_LOGIC_OR_OP].Description));
  Logic_or->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
#endif

#ifdef DEFINE_FILTER_LOGIC_XOR
  _tree_widget_item *Logic_xor = new _tree_widget_item(Logic_type,ItemType2);
  Logic_xor->setData(0,0,tr(_filter_ns::Text_list_binary_xor.c_str()));
  Logic_xor->setData(0,1,int(_filter_ns::_filter_type::FILTER_TYPE_LOGIC_XOR_OP));
  Logic_xor->setToolTip(0,QString::fromStdString(_filter_ns::Filter_name_text[_filter_ns::_filter_type::FILTER_TYPE_LOGIC_XOR_OP].Description));
  Logic_xor->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
#endif

  // Arithmetic operations
  //  _tree_widget_item *Arithmetic_type = new _tree_widget_item(Filters_list,ItemType1);
  //  Arithmetic_type->setFont(0,Font);
  //  Arithmetic_type->setText(0, tr("Arithmetic operations"));
  //  Arithmetic_type->setExpanded(true);

#ifdef DEFINE_FILTER_ARITHMETIC_PRODUCT
  _tree_widget_item *Arithmetic_product = new _tree_widget_item(Arithmetic_type,ItemType2);
  Arithmetic_product->setData(0,0,tr("A * B"));
  Arithmetic_product->setData(0,1,int(_filter_ns::_filter_type::FILTER_TYPE_ARITHMETIC_PRODUCT_OP));
  Arithmetic_product->setToolTip(0,QString::fromStdString(_filter_ns::Filter_name_text[_filter_ns::_filter_type::FILTER_TYPE_ARITHMETIC_PRODUCT_OP].Description));
  Arithmetic_product->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
#endif

#ifdef DEFINE_FILTER_ARITHMETIC_PRODUCT
  _tree_widget_item *Arithmetic__addition = new _tree_widget_item(Arithmetic_type,ItemType2);
  Arithmetic__addition->setData(0,0,tr("A + B"));
  Arithmetic__addition->setData(0,1,int(_filter_ns::_filter_type::FILTER_TYPE_ARITHMETIC_ADDITION_OP));
  Arithmetic__addition->setToolTip(0,QString::fromStdString(_filter_ns::Filter_name_text[_filter_ns::_filter_type::FILTER_TYPE_ARITHMETIC_ADDITION_OP].Description));
  Arithmetic__addition->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
#endif

  // Combination
  _tree_widget_item *Combination_type = new _tree_widget_item(Filters_list,ItemType1);
  //  Combination_type->setBackgroundColor(0,_window_ns::Halftoning_separator_color);
  Combination_type->setFont(0,Font);
  Combination_type->setText(0, tr("Combination operations"));
  Combination_type->setExpanded(true);

#ifdef DEFINE_FILTER_COMBINATION_ELEMENT
  _tree_widget_item *Combination_element = new _tree_widget_item(Combination_type,ItemType2);
  Combination_element->setData(0,0,tr(_filter_ns::Text_list_combination_element.c_str()));
  Combination_element->setData(0,1,int(_filter_ns::_filter_type::FILTER_TYPE_COMBINATION_ELEMENT_OP));
  Combination_element->setToolTip(0,QString::fromStdString(_filter_ns::Filter_name_text[_filter_ns::_filter_type::FILTER_TYPE_COMBINATION_ELEMENT_OP].Description));
  Combination_element->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
#endif

#ifdef DEFINE_FILTER_COMBINATION_ELEMENT_REMOVE
  _tree_widget_item *Combination_element_remove = new _tree_widget_item(Combination_type,ItemType2);
  Combination_element_remove->setData(0,0,tr(_filter_ns::Text_list_combination_element_remove.c_str()));
  Combination_element_remove->setData(0,1,int(_filter_ns::_filter_type::FILTER_TYPE_COMBINATION_ELEMENT_REMOVE_OP));
  Combination_element_remove->setToolTip(0,QString::fromStdString(_filter_ns::Filter_name_text[_filter_ns::_filter_type::FILTER_TYPE_COMBINATION_ELEMENT_REMOVE_OP].Description));
  Combination_element_remove->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
#endif

#ifdef DEFINE_FILTER_COMBINATION_PRODUCT
  _tree_widget_item *Combination_product = new _tree_widget_item(Combination_type,ItemType2);
  Combination_product->setData(0,0,tr(_filter_ns::Text_list_combination_product.c_str()));
  Combination_product->setData(0,1,int(_filter_ns::_filter_type::FILTER_TYPE_COMBINATION_PRODUCT_OP));
  Combination_product->setToolTip(0,QString::fromStdString(_filter_ns::Filter_name_text[_filter_ns::_filter_type::FILTER_TYPE_COMBINATION_PRODUCT_OP].Description));
  Combination_product->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
#endif

#ifdef DEFINE_FILTER_COMBINATION_DIFFERENCE
  _tree_widget_item *Combination_difference = new _tree_widget_item(Combination_type,ItemType2);
  Combination_difference->setData(0,0,tr(_filter_ns::Text_list_combination_difference.c_str()));
  Combination_difference->setData(0,1,int(_filter_ns::_filter_type::FILTER_TYPE_COMBINATION_DIFFERENCE_OP));
  Combination_difference->setToolTip(0,QString::fromStdString(_filter_ns::Filter_name_text[_filter_ns::_filter_type::FILTER_TYPE_COMBINATION_DIFFERENCE_OP].Description));
  Combination_difference->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
#endif

#ifdef DEFINE_FILTER_COMBINATION_ADDITION
  _tree_widget_item *Combination_addition = new _tree_widget_item(Combination_type,ItemType2);
  Combination_addition->setData(0,0,tr(_filter_ns::Text_list_combination_addition.c_str()));
  Combination_addition->setData(0,1,int(_filter_ns::_filter_type::FILTER_TYPE_COMBINATION_ADDITION_OP));
  Combination_addition->setToolTip(0,QString::fromStdString(_filter_ns::Filter_name_text[_filter_ns::_filter_type::FILTER_TYPE_COMBINATION_ADDITION_OP].Description));
  Combination_addition->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
#endif

#ifdef DEFINE_FILTER_COMBINATION_ADDITION_PERCENTAGE
  _tree_widget_item *Combination_addition_percentage = new _tree_widget_item(Combination_type,ItemType2);
  Combination_addition_percentage->setData(0,0,tr(_filter_ns::Text_list_combination_addition_percentage.c_str()));
  Combination_addition_percentage->setData(0,1,int(_filter_ns::_filter_type::FILTER_TYPE_COMBINATION_ADDITION_PERCENTAGE_OP));
  Combination_addition_percentage->setToolTip(0,QString::fromStdString(_filter_ns::Filter_name_text[_filter_ns::_filter_type::FILTER_TYPE_COMBINATION_ADDITION_PERCENTAGE_OP].Description));
  Combination_addition_percentage->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
#endif

#ifdef DEFINE_FILTER_COMBINATION_ADDITION_REMOVE
  _tree_widget_item *Combination_addition_remove = new _tree_widget_item(Combination_type,ItemType2);
  Combination_addition_remove->setData(0,0,tr(_filter_ns::Text_list_combination_addition_remove.c_str()));
  Combination_addition_remove->setData(0,1,int(_filter_ns::_filter_type::FILTER_TYPE_COMBINATION_ADDITION_REMOVE_OP));
  Combination_addition_remove->setToolTip(0,QString::fromStdString(_filter_ns::Filter_name_text[_filter_ns::_filter_type::FILTER_TYPE_COMBINATION_ADDITION_OP].Description));
  Combination_addition_remove->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
#endif

#ifdef DEFINE_FILTER_COLORMAP
  // Colormap
  _tree_widget_item *Colormap_type = new _tree_widget_item(Filters_list,ItemType1);
  //  Colormap_type->setBackgroundColor(0,_window_ns::Halftoning_separator_color);
  Colormap_type->setFont(0,Font);
  Colormap_type->setText(0, tr("Colormap"));
  Colormap_type->setExpanded(true);

  _tree_widget_item *Colormap_colormap = new _tree_widget_item(Colormap_type,ItemType2);
  Colormap_colormap->setData(0,0,tr(_filter_ns::Text_list_colormap.c_str()));
  Colormap_colormap->setData(0,1,int(_filter_ns::_filter_type::FILTER_TYPE_COLORMAP_OP));
  Colormap_colormap->setToolTip(0,QString::fromStdString(_filter_ns::Filter_name_text[_filter_ns::_filter_type::FILTER_TYPE_COLORMAP_OP].Description));
  Colormap_colormap->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
#endif
}

/*************************************************************************/

void _window_xmapslab::new_effect_slot()
{
//  Nodes_editor->clear();
//  Scene->clear();
//  Graphics_view->items().clear();

//  Nodes_editor->add_grid();
//  Nodes_editor->add_initial_blocks();

//  Graphics_view->setScene(Scene);
//  Graphics_view->setSceneRect(-100,-100,5000,5000);
//  Graphics_view->setRenderHint(QPainter::Antialiasing, true);

//  Graphics_view->horizontalScrollBar()->setValue(-1000);
//  Graphics_view->verticalScrollBar()->setValue(-1000);

//  Tab_widget_ge->setTabEnabled(0,true);
//  Tab_widget_ge->setTabEnabled(1,true);

//  Nodes_editor->changed(true);

//  GL_widget->clear_data();

}

/*************************************************************************/
// Llevar esto node_editor

void _window_xmapslab::add_filter(int Filter_pos, std::string Element, float Col, float Row)
{
  Filter_parameters=_filter_ns::Filter_name_parameters[_filter_ns::_filter_type(Filter_pos)];

  if (Filter_pos!=int(_filter_ns::_filter_type::FILTER_TYPE_ELEMENT) && Filter_pos!=int(_filter_ns::_filter_type::FILTER_TYPE_IMAGE)){
    Element=Filter_parameters.Name;
  }

  Nodes_editor->add_block(Filter_parameters.Type,Filter_parameters.Class,Element,Filter_parameters.Vec_input_ports, Filter_parameters.Vec_output_ports,Col,Row);

  // now the filter is deselected
  QList<QTreeWidgetItem *> List_selected=Filters_list->selectedItems();
  for (int i=0;i<List_selected.size();i++){
    List_selected[i]->setSelected(false);
  }
  //  Filter_parameters.Type="";
}

//

/*************************************************************************/

void _window_xmapslab::tab_ge_clicked_slot(int Index1)
{
  // check if the result is correct
  if (Index1==0){
    // from visualization to edition
    Nodes_editor->changed(false);
#ifndef UNCORRECT
    if (Nodes_editor->filter_valid()==true) update_filters_parameters();
#else
    update_filters_parameters();
#endif

    Graphics_view->horizontalScrollBar()->setValue(-1000);
    Graphics_view->verticalScrollBar()->setValue(-1000);
  }
  else{
    // from edition to visualization
    // check if the structure is correct (there is not loop checking)
    if (Nodes_editor->create_blocks_from_editor()==false){
      // there are problems, return to edition tab
      Tab_widget_ge->setCurrentIndex(0);
    }
    else{
      if (Nodes_editor->changed()==true){
        if (Nodes_editor->vec_order_size()>0){
          // allways the image tab is the active when passing from editor to results
          create_filters_from_blocks(Nodes_editor->map_data_blocks(),Nodes_editor->vec_order(),Nodes_editor->map_filters_parameters());
          Tab_widget_mapping_visualization->setCurrentIndex(0);
        }
        else Tab_widget_ge->setCurrentIndex(0);
      }
      else{
        std::string Name=(*Vec_order_mapping)[Mapping_selected_image_index];
        GL_widget_ge->update_texture(Name);
      }
    }
  }
}

/*************************************************************************/
// Given the graphical definition, the filters are created

void _window_xmapslab::create_filters_from_blocks()
{
  _filter_ns::_filter_type Type;
  string Name_layer;
  string Name_aux;
  string Element_name;
  string Name_in_block;
  char Aux_string[200];
  //  cv::Mat *Input_image0;
  //  cv::Mat *Output_image0;
  //  cv::Mat *Input_image1;
  //  cv::Mat *Input_image2;
  _nodes_editor_ns::_block Block;

  vector<shared_ptr<cv::Mat>> Vec_mapping_images;
  vector<shared_ptr<cv::Mat>> Vec_mapping_input_data;
  vector<shared_ptr<cv::Mat>> Vec_mapping_output_data;

  vector<shared_ptr<_filter>> Vec_mapping_input_filters;
  vector<int> Vec_mapping_input_port_index;

  vector<float> Vec_mapping_max_values;

  Map_filters.clear();
  Map_mapping_images.clear();
  Map_mapping_data.clear();
  Map_graph.clear();
  Mapping_pipeline.clear();

  for (unsigned int i=0;i<Vec_order_mapping->size();i++){
    Vec_mapping_input_data.clear();
    Vec_mapping_output_data.clear();
    Vec_mapping_images.clear();
    Vec_mapping_max_values.clear();
    Vec_mapping_input_filters.clear();
    Vec_mapping_input_port_index.clear();

    Name_in_block=(*Vec_order_mapping)[i];
    Block=(*Map_data_blocks)[Name_in_block];

    Type=Block.Type;
    //    Name=Block.Name;

    //    sprintf(Aux_string,"%s_%d",Name.c_str(),0);
    //    Name_aux=Aux_string;

    // get the input data
    string Name_input;
    // NOT ELEMENT MAP
    if (Block.Type!=_filter_ns::_filter_type::FILTER_TYPE_ELEMENT && Block.Type!=_filter_ns::_filter_type::FILTER_TYPE_IMAGE){
      // get the name of the element
      for (unsigned int j=0;j<Block.Vec_input_ports.size();j++){
        Name_input=Block.Vec_input_ports[j];

        // NOT NULL
        if (Name_input!="NULL"){
          if (Block.Vec_index_input_ports[j]==0){
            Vec_mapping_input_data.push_back(Map_mapping_data[Name_input]);
            Vec_mapping_max_values.push_back(Map_filters[Name_input]->max_value_output_data(0));
            Vec_mapping_input_filters.push_back(Map_filters[Name_input]);
            Vec_mapping_input_port_index.push_back(Block.Vec_index_input_ports[j]);
          }
          else{
            sprintf(Aux_string,"%s_%d",Name_input.c_str(),Block.Vec_index_input_ports[j]);
            Name_aux=Aux_string;

            Vec_mapping_input_data.push_back(Map_mapping_data[Name_aux]);
            Vec_mapping_max_values.push_back(Map_filters[Name_input]->max_value_output_data(Block.Vec_index_input_ports[i]));
            Vec_mapping_input_filters.push_back(Map_filters[Name_input]);
            Vec_mapping_input_port_index.push_back(Block.Vec_index_input_ports[j]);
          }
        }
        else{ //it has not inputs
          Vec_mapping_input_data.push_back(nullptr);
          Vec_mapping_max_values.push_back(-1);
          Vec_mapping_input_filters.push_back(nullptr);
          Vec_mapping_input_port_index.push_back(-1);
        }
      }
    }
    else if(Block.Type==_filter_ns::_filter_type::FILTER_TYPE_ELEMENT){// For the ELEMENT MAP type
      // get the name of each input amd get the maximum
      vector<string> Tokens=split(Name_in_block,'_');
      Element_name=Tokens[1];
      Vec_mapping_max_values.push_back(Map_name_to_element[Element_name].Max_value_adjusted);
      Vec_mapping_input_filters.push_back(nullptr);
      Vec_mapping_input_port_index.push_back(-1);
    }
    else{ //Image
      // get the name of each input amd get the maximum
      Vec_mapping_max_values.push_back(0);
      Vec_mapping_input_filters.push_back(nullptr);
      Vec_mapping_input_port_index.push_back(-1);
    }

    // save data for the Map_graph
    // input 0
    for (unsigned int j=0;j<Block.Vec_input_ports.size();j++){
      Name_input=Block.Vec_input_ports[j];
      if (Name_input!="NULL"){
        if (Map_graph.find(Block.Vec_input_ports[j])==Map_graph.end()){
          vector<string> Vec_aux;
          Vec_aux.push_back(Name_in_block);
          Map_graph[Block.Vec_input_ports[j]]=Vec_aux;
        }
        else{
          Map_graph[Block.Vec_input_ports[j]].push_back(Name_in_block);
        }
      }
    }

    //    int Width_aux=0;
    //    int Height_aux=0;

    switch(Type){
#ifdef DEFINE_FILTER_IMAGE
    case _filter_ns::_filter_type::FILTER_TYPE_IMAGE:
      {
        shared_ptr<_filter_image_ui> Filter=make_shared<_filter_image_ui>(this,(*Map_filters_parameters)[Name_in_block],Name_in_block);

        Map_filters[Name_in_block]=Filter;
      }
      break;
#endif
#ifdef DEFINE_FILTER_ELEMENT
    case _filter_ns::_filter_type::FILTER_TYPE_ELEMENT:
      {
        shared_ptr<_filter_element_ui> Filter=make_shared<_filter_element_ui>(this,(*Map_filters_parameters)[Name_in_block],Name_in_block);

        Map_filters[Name_in_block]=Filter;
      }
      break;
#endif
#ifdef DEFINE_FILTER_CONVERSION_BIN
    case _filter_ns::_filter_type::FILTER_TYPE_CONVERSION_TO_BIN_OP:
      {
        shared_ptr<_filter_conversion_bin_ui> Filter=make_shared<_filter_conversion_bin_ui>(this,(*Map_filters_parameters)[Name_in_block],Name_in_block);

        // take care that the color is for the maximum value, 255, which is assgined to true
        QColor Color_for_true;
        if  (Color_for_zero_value==_color_map_ns::_color_for_zero_value::COLOR_ZERO_VALUE_WHITE) Color_for_true.setRgb(0,0,0);
        else Color_for_true.setRgb(255,255,255);

        _palette_data_ns::_palette_data Palette_data("", _palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE, _palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE, 3, _palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_MUTABLE, Color_for_true, Map_fixed_palettes["jet"], color_for_zero_value());

        Filter->set_colormap(Palette_data.vec_values(),Palette_data.vec_colors(),Palette_data.type());
        Filter->set_original_image(Original_image);

        Map_filters[Name_in_block]=Filter;
        Map_filters_palette_data[Name_in_block]=Palette_data;
      }
      break;
#endif
#ifdef DEFINE_FILTER_CONVERSION_COLOR_BIN
    case _filter_ns::_filter_type::FILTER_TYPE_CONVERSION_COLOR_TO_BIN_OP:
      {
        shared_ptr<_filter_conversion_color_bin_ui> Filter=make_shared<_filter_conversion_color_bin_ui>(this,(*Map_filters_parameters)[Name_in_block],Name_in_block);

        // take care that the color is for the maximum value, 255, which is assgined to true
        QColor Color_for_true;
        if  (Color_for_zero_value==_color_map_ns::_color_for_zero_value::COLOR_ZERO_VALUE_WHITE) Color_for_true.setRgb(0,0,0);
        else Color_for_true.setRgb(255,255,255);

        // _color_bar_abstract::compute_random_color()

        _palette_data_ns::_palette_data Palette_data("", _palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE, _palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE, 3, _palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_MUTABLE, Color_for_true, Map_fixed_palettes["jet"], color_for_zero_value());

        Filter->set_colormap(Palette_data.vec_values(),Palette_data.vec_colors(),Palette_data.type());
        Filter->set_original_image(Original_image);

        Map_filters[Name_in_block]=Filter;
        Map_filters_palette_data[Name_in_block]=Palette_data;
      }
      break;
#endif
#ifdef DEFINE_FILTER_LOGIC_AND
    case _filter_ns::_filter_type::FILTER_TYPE_LOGIC_AND_OP:
      {
        shared_ptr<_filter_logic_and_ui> Filter=make_shared<_filter_logic_and_ui>(this,(*Map_filters_parameters)[Name_in_block],Name_in_block);

        // take care that the color is for the maximum value, 255, which is assgined to true
        QColor Color_for_true;
        if  (Color_for_zero_value==_color_map_ns::_color_for_zero_value::COLOR_ZERO_VALUE_WHITE) Color_for_true.setRgb(0,0,0);
        else Color_for_true.setRgb(255,255,255);

        _palette_data_ns::_palette_data Palette_data("", _palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE, _palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE, 3, _palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_MUTABLE, Color_for_true, Map_fixed_palettes["jet"], color_for_zero_value());

        Filter->set_colormap(Palette_data.vec_values(),Palette_data.vec_colors(),Palette_data.type());
        Filter->set_original_image(Original_image);

        Map_filters[Name_in_block]=Filter;
        Map_filters_palette_data[Name_in_block]=Palette_data;
      }
      break;
#endif
#ifdef DEFINE_FILTER_LOGIC_OR
    case _filter_ns::_filter_type::FILTER_TYPE_LOGIC_OR_OP:
      {
        shared_ptr<_filter_logic_or_ui> Filter=make_shared<_filter_logic_or_ui>(this,(*Map_filters_parameters)[Name_in_block],Name_in_block);

        // take care that the color is for the maximum value, 255, which is assgined to true
        QColor Color_for_true;
        if  (Color_for_zero_value==_color_map_ns::_color_for_zero_value::COLOR_ZERO_VALUE_WHITE) Color_for_true.setRgb(0,0,0);
        else Color_for_true.setRgb(255,255,255);

        _palette_data_ns::_palette_data Palette_data("", _palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE, _palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE, 3, _palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_MUTABLE, Color_for_true, Map_fixed_palettes["jet"], color_for_zero_value());

        Filter->set_colormap(Palette_data.vec_values(),Palette_data.vec_colors(),Palette_data.type());
        Filter->set_original_image(Original_image);

        Map_filters[Name_in_block]=Filter;
        Map_filters_palette_data[Name_in_block]=Palette_data;
      }
      break;
#endif
#ifdef DEFINE_FILTER_LOGIC_XOR
    case _filter_ns::_filter_type::FILTER_TYPE_LOGIC_XOR_OP:
      {
        shared_ptr<_filter_logic_xor_ui> Filter=make_shared<_filter_logic_xor_ui>(this,(*Map_filters_parameters)[Name_in_block],Name_in_block);

        // take care that the color is for the maximum value, 255, which is assgined to true
        QColor Color_for_true;
        if  (Color_for_zero_value==_color_map_ns::_color_for_zero_value::COLOR_ZERO_VALUE_WHITE) Color_for_true.setRgb(0,0,0);
        else Color_for_true.setRgb(255,255,255);

        _palette_data_ns::_palette_data Palette_data("", _palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE, _palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE, 3, _palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_MUTABLE, Color_for_true, Map_fixed_palettes["jet"], color_for_zero_value());

        Filter->set_colormap(Palette_data.vec_values(),Palette_data.vec_colors(),Palette_data.type());
        Filter->set_original_image(Original_image);

        Map_filters[Name_in_block]=Filter;
        Map_filters_palette_data[Name_in_block]=Palette_data;
      }
      break;
#endif
#ifdef DEFINE_FILTER_LOGIC_NOT
    case _filter_ns::_filter_type::FILTER_TYPE_LOGIC_NOT_OP:
      {
        shared_ptr<_filter_logic_not_ui> Filter=make_shared<_filter_logic_not_ui>(this,(*Map_filters_parameters)[Name_in_block],Name_in_block);

        // take care that the color is for the maximum value, 255, which is assgined to true
        QColor Color_for_true;
        if  (Color_for_zero_value==_color_map_ns::_color_for_zero_value::COLOR_ZERO_VALUE_WHITE) Color_for_true.setRgb(0,0,0);
        else Color_for_true.setRgb(255,255,255);

        _palette_data_ns::_palette_data Palette_data("", _palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE, _palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE, 3, _palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_MUTABLE, Color_for_true, Map_fixed_palettes["jet"], color_for_zero_value());

        Filter->set_colormap(Palette_data.vec_values(),Palette_data.vec_colors(),Palette_data.type());
        Filter->set_original_image(Original_image);

        Map_filters[Name_in_block]=Filter;
        Map_filters_palette_data[Name_in_block]=Palette_data;
      }
      break;
#endif
#ifdef DEFINE_FILTER_ARITHMETIC_PRODUCT
    case _filter_ns::_filter_type::FILTER_TYPE_ARITHMETIC_PRODUCT_OP:
      {
        shared_ptr<_filter_arithmetic_product_ui> Filter=make_shared<_filter_arithmetic_product_ui>(this,(*Map_filters_parameters)[Name_in_block],Name_in_block);
        vector<float> Vec_proportions={0.0f,1.0f};
        vector<QColor> Vec_colors={QColor(255,255,255),random_color()};

        Filter->set_colormap(Vec_proportions,Vec_colors,1);
        Filter->set_original_image(Original_image);

        Map_filters[Name_in_block]=Filter;
      }
      break;
#endif
#ifdef DEFINE_FILTER_ARITHMETIC_ADDITION
    case _filter_ns::_filter_type::FILTER_TYPE_ARITHMETIC_ADDITION_OP:
      {
        shared_ptr<_filter_arithmetic_addition_ui> Filter=make_shared<_filter_arithmetic_addition_ui>(this,(*Map_filters_parameters)[Name_in_block],Name_in_block);
        vector<float> Vec_proportions={0.0f,1.0f};
        vector<QColor> Vec_colors={QColor(255,255,255),random_color()};

        Filter->set_colormap(Vec_proportions,Vec_colors,1);
        Filter->set_original_image(Original_image);

        Map_filters[Name_in_block]=Filter;
      }
      break;
#endif
#ifdef DEFINE_FILTER_COMBINATION_ELEMENT
    case _filter_ns::_filter_type::FILTER_TYPE_COMBINATION_ELEMENT_OP:
      {
        shared_ptr<_filter_combination_element_ui> Filter=make_shared<_filter_combination_element_ui>(this,(*Map_filters_parameters)[Name_in_block],Name_in_block);
        QColor Color=compute_color("");

        _palette_data_ns::_palette_data Palette_data("", _palette_data_ns::_palette_type::PALETTE_TYPE_CONTINUOUS, _palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE, 3, _palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_MUTABLE, _color_bar_abstract::compute_random_color(), Map_fixed_palettes["jet"], color_for_zero_value());

        Filter->color(Color);
        Filter->set_colormap(Palette_data.vec_values(),Palette_data.vec_colors(),Palette_data.type());
        Filter->set_original_image(Original_image);

        Map_filters[Name_in_block]=Filter;
        Map_filters_palette_data[Name_in_block]=Palette_data;
      }
      break;
#endif
#ifdef DEFINE_FILTER_COMBINATION_ELEMENT_REMOVE
    case _filter_ns::_filter_type::FILTER_TYPE_COMBINATION_ELEMENT_REMOVE_OP:
      {
        shared_ptr<_filter_combination_element_remove_ui> Filter=make_shared<_filter_combination_element_remove_ui>(this,(*Map_filters_parameters)[Name_in_block],Name_in_block);
        QColor Color=compute_color("");

        _palette_data_ns::_palette_data Palette_data("", _palette_data_ns::_palette_type::PALETTE_TYPE_CONTINUOUS, _palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE, 3, _palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_MUTABLE, _color_bar_abstract::compute_random_color(), Map_fixed_palettes["jet"], color_for_zero_value());

        Filter->color(Color);
        Filter->set_colormap(Palette_data.vec_values(),Palette_data.vec_colors(),Palette_data.type());
        Filter->set_original_image(Original_image);

        Map_filters[Name_in_block]=Filter;
        Map_filters_palette_data[Name_in_block]=Palette_data;
      }
      break;
#endif
#ifdef DEFINE_FILTER_COMBINATION_PRODUCT
    case _filter_ns::_filter_type::FILTER_TYPE_COMBINATION_PRODUCT_OP:
      {
        shared_ptr<_filter_combination_product_ui> Filter=make_shared<_filter_combination_product_ui>(this,(*Map_filters_parameters)[Name_in_block],Name_in_block);
        QColor Color=compute_color("");

        _palette_data_ns::_palette_data Palette_data("", _palette_data_ns::_palette_type::PALETTE_TYPE_CONTINUOUS, _palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE, 3, _palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_MUTABLE, _color_bar_abstract::compute_random_color(), Map_fixed_palettes["jet"], color_for_zero_value());

        Filter->color(Color);
        Filter->set_colormap(Palette_data.vec_values(),Palette_data.vec_colors(),Palette_data.type());
        Filter->set_original_image(Original_image);

        Map_filters[Name_in_block]=Filter;
        Map_filters_palette_data[Name_in_block]=Palette_data;
      }
      break;
#endif
#ifdef DEFINE_FILTER_COMBINATION_ADDITION
    case _filter_ns::_filter_type::FILTER_TYPE_COMBINATION_ADDITION_OP:
      {
        shared_ptr<_filter_combination_addition_ui> Filter=make_shared<_filter_combination_addition_ui>(this,(*Map_filters_parameters)[Name_in_block],Name_in_block);
        QColor Color=compute_color("");

        _palette_data_ns::_palette_data Palette_data("", _palette_data_ns::_palette_type::PALETTE_TYPE_CONTINUOUS, _palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE, 3, _palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_MUTABLE, _color_bar_abstract::compute_random_color(), Map_fixed_palettes["jet"], color_for_zero_value());

        Filter->color(Color);
        Filter->set_colormap(Palette_data.vec_values(),Palette_data.vec_colors(),Palette_data.type());
        Filter->set_original_image(Original_image);

        Map_filters[Name_in_block]=Filter;
        Map_filters_palette_data[Name_in_block]=Palette_data;
      }
      break;
#endif
#ifdef DEFINE_FILTER_COMBINATION_DIFFERENCE
    case _filter_ns::_filter_type::FILTER_TYPE_COMBINATION_DIFFERENCE_OP:
      {
        shared_ptr<_filter_combination_difference_ui> Filter=make_shared<_filter_combination_difference_ui>(this,(*Map_filters_parameters)[Name_in_block],Name_in_block);
        QColor Color=compute_color("");

        _palette_data_ns::_palette_data Palette_data("", _palette_data_ns::_palette_type::PALETTE_TYPE_CONTINUOUS, _palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE, 3, _palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_MUTABLE, _color_bar_abstract::compute_random_color(), Map_fixed_palettes["jet"], color_for_zero_value());

        Filter->color(Color);
        Filter->set_colormap(Palette_data.vec_values(),Palette_data.vec_colors(),Palette_data.type());
        Filter->set_original_image(Original_image);

        Map_filters[Name_in_block]=Filter;
        Map_filters_palette_data[Name_in_block]=Palette_data;
      }
      break;
#endif
#ifdef DEFINE_FILTER_COMBINATION_ADDITION_PERCENTAGE
    case _filter_ns::_filter_type::FILTER_TYPE_COMBINATION_ADDITION_PERCENTAGE_OP:
      {
        shared_ptr<_filter_combination_addition_percentage_ui> Filter=make_shared<_filter_combination_addition_percentage_ui>(this,(*Map_filters_parameters)[Name_in_block],Name_in_block);
        QColor Color=compute_color("");

        _palette_data_ns::_palette_data Palette_data("", _palette_data_ns::_palette_type::PALETTE_TYPE_CONTINUOUS, _palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE, 3, _palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_MUTABLE, _color_bar_abstract::compute_random_color(), Map_fixed_palettes["jet"], color_for_zero_value());

        Filter->color(Color);
        Filter->set_colormap(Palette_data.vec_values(),Palette_data.vec_colors(),Palette_data.type());
        Filter->set_original_image(Original_image);

        Map_filters[Name_in_block]=Filter;
        Map_filters_palette_data[Name_in_block]=Palette_data;
      }
      break;
#endif
#ifdef DEFINE_FILTER_COMBINATION_ADDITION_REMOVE
    case _filter_ns::_filter_type::FILTER_TYPE_COMBINATION_ADDITION_REMOVE_OP:
      {
        shared_ptr<_filter_combination_addition_remove_ui> Filter=make_shared<_filter_combination_addition_remove_ui>(this,(*Map_filters_parameters)[Name_in_block],Name_in_block);
        QColor Color=compute_color("");

        _palette_data Palette_data("",_palette_data_ns::_data_type::DATA_TYPE_CONTINUOUS,_palette_data_ns::_color_type::COLOR_TYPE_TONE,2,Color, color_for_zero_value());

        Filter->color(Color);
        Filter->set_colormap(Palette_data.vec_values(),Palette_data.vec_colors(),Palette_data.data_type());
        Filter->set_original_image(Original_image);

        Map_filters[Name_in_block]=Filter;
        Map_filters_palette_data[Name_in_block]=Palette_data;
      }
      break;
#endif
#ifdef DEFINE_FILTER_COLORMAP
    case _filter_ns::_filter_type::FILTER_TYPE_COLORMAP_OP:
      {
        shared_ptr<_filter_colormap_ui> Filter=make_shared<_filter_colormap_ui>(this,(*Map_filters_parameters)[Name_in_block],Name_in_block);
        QColor Color=compute_color("");

        _palette_data Palette_data("",_palette_data_ns::_data_type::DATA_TYPE_CONTINUOUS,_palette_data_ns::_color_type::COLOR_TYPE_TONE,2,Color, color_for_zero_value());

        Filter->color(Color);
        Filter->set_colormap(Palette_data.vec_values(),Palette_data.vec_colors(),Palette_data.data_type());
        Filter->set_original_image(Original_image);

        Map_filters[Name_in_block]=Filter;
        Map_filters_palette_data[Name_in_block]=Palette_data;
      }
      break;
#endif
    default:break;
    }// end switch

    // ELEMENT
    if (Block.Type==_filter_ns::_filter_type::FILTER_TYPE_ELEMENT){
      // get the name
      QString Name1(Name_in_block.c_str());
      int Pos=Name1.lastIndexOf('_');
      Name_layer=Name1.left(Pos).toStdString();
      // now access the layer
      // create a reference of the data
      shared_ptr<cv::Mat> Data=make_shared<cv::Mat>();
      Data=static_pointer_cast<_layer_map_distance_ui>(Map_name_to_layer[Name_layer].Layer)->result_floats_image();
      Map_mapping_data[Name_in_block]=Data;

      shared_ptr<cv::Mat> Image=make_shared<cv::Mat>();
      // clone to not change the original
      *Image=static_pointer_cast<_layer_map_distance_ui>(Map_name_to_layer[Name_layer].Layer)->image()->clone();
      // change to 3 channels
      cv::cvtColor(*Image,*Image,cv::COLOR_BGRA2BGR,3);
      Map_mapping_images[Name_in_block]=Image;

      Vec_mapping_output_data.push_back(Data);
      Vec_mapping_images.push_back(Image);
    }
    else if (Block.Type==_filter_ns::_filter_type::FILTER_TYPE_IMAGE){
      // get the name
      QString Name1(Name_in_block.c_str());
      int Pos=Name1.lastIndexOf('_');
      Name_layer=Name1.left(Pos).toStdString();
      // now access the layer
      // create a reference of the data
//      shared_ptr<cv::Mat> Data=make_shared<cv::Mat>();

//      Data=static_pointer_cast<_layer_map_distance_ui>(Map_name_to_layer[Name_layer].Layer)->result_floats_image();
//      Map_mapping_data[Name_in_block]=Data;

      shared_ptr<cv::Mat> Image=make_shared<cv::Mat>();
      // clone to not change the original
      *Image=static_pointer_cast<_layer_basic_xmapslab_ui>(Map_name_to_layer[Name_layer].Layer)->image()->clone();

      // change the transparency to show white colors
      cv::Vec4b Pixel;
      for (int Row=0;Row<Image->rows;Row++){
        for (int Col=0;Col<Image->cols;Col++){
          Pixel=Image->at<cv::Vec4b>(Row,Col);
          if (Pixel[3]<255) Image->at<cv::Vec4b>(Row,Col)=cv::Vec4b(255,255,255,255);
        }
      }
      // change to 3 channels
      cv::cvtColor(*Image,*Image,cv::COLOR_BGRA2BGR,3);

      Map_mapping_images[Name_in_block]=Image;

      Map_mapping_data[Name_in_block]=Image;

      // is the same as the inut
      Vec_mapping_output_data.push_back(Image);
      Vec_mapping_images.push_back(Image);
    }
    else{
      // it is necessary to create a new Data image
      shared_ptr<cv::Mat> Data=make_shared<cv::Mat>();
      Data->create(Initial_height,Initial_width,CV_32F);

      Map_mapping_data[Name_in_block]=Data;

      // it is necessary to create a new Image
      shared_ptr<cv::Mat> Image=make_shared<cv::Mat>();
      Image->create(Initial_height,Initial_width,CV_8UC3);
      Map_mapping_images[Name_in_block]=Image;

      Vec_mapping_output_data.push_back(Data);
      Vec_mapping_images.push_back(Image);

//      string New_name;
//      if (Block.Type==_filter_ns::_filter_type::FILTER_TYPE_COMBINATION_ADDITION_REMOVE_OP){
//        // it is necessary to add 2 new outputs
//        New_name=Name_in_block+"_1";
//        Data=make_shared<cv::Mat>();
//        Data->create(Initial_height,Initial_width,CV_32F);
//        Map_mapping_data[New_name]=Data;
//        Vec_mapping_output_data.push_back(Data);

//        New_name=Name_in_block+"_2";
//        Data=make_shared<cv::Mat>();
//        Data->create(Initial_height,Initial_width,CV_32F);
//        Map_mapping_data[New_name]=Data;
//        Vec_mapping_output_data.push_back(Data);
//      }
    }

    Map_filters[Name_in_block]->set_data(Vec_mapping_input_data,Vec_mapping_output_data,Vec_mapping_images,Vec_mapping_max_values);
    Map_filters[Name_in_block]->set_input_filters(Vec_mapping_input_filters,Vec_mapping_input_port_index);
    Mapping_pipeline.push_back(Map_filters[Name_in_block]);
  }

  // Once all the block are converted they must be computed and show

  update_all_filters();

  Mapping_selected_image_index=0;
  Mapping_selected_filter_index=0;
  //  update_mapping_nodes_editor_maps_tab();
  //  update_mapping_filters_tab();

  Mapping_nodes_editor_maps_tab->insert_maps();
  Mapping_filters_tab->insert_filters();

  string Selected_image=(*Vec_order_mapping)[Mapping_selected_image_index];

  GL_widget_ge->refresh_texture(Initial_width,Initial_height);
  GL_widget_ge->set_texture(Selected_image);
  GL_widget_ge->update_texture(Selected_image);
}

/*************************************************************************/

void _window_xmapslab::create_filters_from_blocks(map<std::string,_nodes_editor_ns::_block> *Map_data_blocks1, std::vector<std::string> *Vec_order_mapping1, map<string, map<string, string> > *Map_filters_parameters1)
{
  Map_data_blocks=Map_data_blocks1;
  Vec_order_mapping=Vec_order_mapping1;
  Map_filters_parameters=Map_filters_parameters1;

  create_filters_from_blocks();
}

/*************************************************************************/

void _window_xmapslab::update_all_filters()
{
  for (unsigned int i=0;i<(*Vec_order_mapping).size();i++){
    Map_filters[(*Vec_order_mapping)[i]]->update();
  }
}

/*************************************************************************/

void _window_xmapslab::update_mapping_nodes_editor_maps_tab()
{
  std::string Name;

  Mapping_nodes_editor_maps_tab->clear();
  for (unsigned int i=0;i<Vec_order_mapping->size();i++){
    Name=(*Vec_order_mapping)[i];
    Mapping_nodes_editor_maps_tab->set_item(Name);
  }

  Mapping_nodes_editor_maps_tab->set_selected_item(Mapping_selected_image_index);
}

/*************************************************************************/

void _window_xmapslab::update_mapping_filters_tab()
{
  std::string Name;

  Mapping_filters_tab->clear();
  for (unsigned int i=0;i<Vec_order_mapping->size();i++){
    Name=(*Vec_order_mapping)[i];
    Mapping_filters_tab->set_item(Name);
    Map_filters[Name]->hide();
  }
  Mapping_filters_tab->set_selected_item(Mapping_selected_filter_index);
  // show the selected widget
//  Map_filters[(*Vec_order_mapping)[Mapping_selected_filter_index]]->show();
}

/*************************************************************************/

void _window_xmapslab::selected_filter(std::string Filter_name)
{
  std::string Name;

  Mapping_selected_filter_name=Filter_name;

  // to hide all the filters of the effect
  for (unsigned int i=0;i<Vec_order_mapping->size();i++){
    Name=(*Vec_order_mapping)[i];
    Map_filters[Name]->hide();
  }

  for (unsigned int i=0;i<Vec_order_mapping->size();i++){
    if ((*Vec_order_mapping)[i]==Filter_name){
      Mapping_selected_filter_index=i;
      break;
    }
  }

  // show the selected filter
  Map_filters[Filter_name]->show();
}

/*************************************************************************/

void _window_xmapslab::update_filter_aux(std::string Name)
{

  Map_filters[Name]->update();
  if (Map_graph.find(Name)!=Map_graph.end()){
    // the element exist
    for (auto &Iterator: Map_graph[Name]){
      update_filter_aux(Iterator);
    }
  }
}

/*************************************************************************/

void _window_xmapslab::update_filter(std::string Name)
{
  // update all the affected filters
  update_filter_aux(Name);

  std::string Selected_image=(*Vec_order_mapping)[Mapping_selected_image_index];

  GL_widget_ge->update_texture(Selected_image);
}

/*************************************************************************/

void _window_xmapslab::update_filters_parameters()
{
  // the values of the Map_filters_parameters must be update with the current values
  // also, the _INI_ filed must be changef to FILE. This allows to load the modified values if the effect is changed
  std::string Name;

  // to hide all the filters of the effect
  for (unsigned int i=0;i<Vec_order_mapping->size();i++){
    Name=(*Vec_order_mapping)[i];
    Map_filters[Name]->write_parameters((*Map_filters_parameters)[Name]);
    (*Map_filters_parameters)[Name]["_INI_"]="FILE";
  }
}
#endif

/*************************************************************************/

QColor _window_xmapslab::compute_color(std::string Name_element)
{
  QColor Color;
  bool Found=false;
  float Hue=0;

  if (Name_element=="") Found=false;
  else{
    auto It = _window_xmapslab_ns::Map_atomic_data.find(Name_element);

    if (It != _window_xmapslab_ns::Map_atomic_data.end()) {
      Color=It->second.Color;
      Found=true;
    }
  }

  if (Found==false){
    random_device Random_device;   // non-deterministic generator
    mt19937 Generator(Random_device());  // to seed mersenne twister.
    uniform_int_distribution<> Random(0,359);
    Hue=Random(Generator);
    Color.setHsv(Hue,255,255);
    Color.toRgb();
  }

  return(Color);
}

/*************************************************************************/

void _window_xmapslab::parameters_changed()
{
  save_settings();

  if (Loaded_image==true){
    static_pointer_cast<_layer_positions_xmapslab_ui>(Map_name_to_layer["Positions"].Layer)->parameters( Window_main->display_font_size(), Window_main->display_out_circle_size(), Window_main->display_font_color(), Window_main->display_out_circle_color(), Window_main->display_in_circle_color());

    static_pointer_cast<_layer_positions_xmapslab_ui>(Map_name_to_layer["Positions"].Layer)->update();
    GL_widget->update_texture("Positions");
    GL_widget->update();
  }
}

/*************************************************************************/

void _window_xmapslab::splitter_moved_slot(int Pos,int Index)
{
  Q_UNUSED(Index)
  Size_chart=Pos;
}

/*************************************************************************/

bool _window_xmapslab::check_project()
{
  if (QFile::exists(_window_xmapslab_ns::Project_name)){
    std::fstream File;
    std::string Line;
    File.open(_window_xmapslab_ns::Project_name.toStdString(),ios::in);
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

          QFile::remove(_window_xmapslab_ns::Project_name);

          return false;
        }
      }
    }
  }
  return false;
}

/*************************************************************************/

void _window_xmapslab::change_active_position(int Position)
{
  Vec_active_positions[Position]=!Vec_active_positions[Position];

  if (Vec_active_positions[Position]==true) Num_active_positions++;
  else Num_active_positions--;
}

/*************************************************************************/

void _window_xmapslab::xrf_recompute_data()
{
  // updates the positions image
  add_layer_positions_image();

  GL_widget->update();
}

/*************************************************************************/
// for the creation of layers

void _window_xmapslab::xrf_use_colors(int Pos,bool Value)
{
  if (Pos>=0 && Pos<=2){
    XRF_use_colors[Pos]=Value;
  }
}

/*************************************************************************/

bool _window_xmapslab::xrf_use_colors(int Pos)
{
  if (Pos>=0 && Pos<=2){
    return XRF_use_colors[Pos];
  }

  return false;
}

/*************************************************************************/

void _window_xmapslab::xrf_use_positions(int Pos,bool Value)
{
  if (Pos>=0 && Pos<=1){
    XRF_use_positions[Pos]=Value;
  }
}

/*************************************************************************/

bool _window_xmapslab::xrf_use_positions(int Pos)
{
  if (Pos>=0 && Pos<=1){
    return XRF_use_positions[Pos];
  }

  return false;
}

/*************************************************************************/

void _window_xmapslab::xrf_create_some_maps()
{
#ifndef MEASURE_RUN_TIME
  if (Num_active_positions>0){
    if (Vec_xrf_elements_selected_names.size()>0){
      int Count_progress=0;
      QProgressDialog Progress("Computing...", "Abort",0,Vec_xrf_elements_selected_names.size(),this);
      Progress.setWindowModality(Qt::WindowModal);
      Progress.setMinimumDuration(0);
      Progress.setCancelButton(0);

      for (unsigned int i=0;i<Vec_xrf_elements_selected_names.size();i++){
        Progress.setValue(Count_progress++);
        if (Progress.wasCanceled()) break;

        switch(XRF_interpolation_type){
          case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_HYPERCUBE_DISTANCE:
          case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_2D_CARTESIAN_DISTANCE:
            add_layer_map_minimum_hypercube_distance(Name_selected_image,Vec_xrf_elements_selected_names[i],XRF_view_name,XRF_color_model,XRF_use_colors,XRF_use_positions, XRF_distance_normalization, XRF_position_normalization_type, XRF_probe, XRF_palette, Data_type_print, Color_for_zero_value,Map_name_to_element, _common_ns::_xray_data_type::XRAY_DATA_TYPE_XRF);
          break;
          case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_RBF:
            add_layer_map_rbf_interpolation(Name_selected_image,Vec_xrf_elements_selected_names[i], XRF_view_name, XRF_color_model, XRF_palette, Data_type_print, Color_for_zero_value, Map_name_to_element, _common_ns::_xray_data_type::XRAY_DATA_TYPE_XRF);
          break;
          case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_TRIANGULATION:
            add_layer_map_triangulation(Name_selected_image, Vec_xrf_elements_selected_names[i], XRF_view_name, XRF_color_model, XRF_palette, XRF_triangulation_add_corners, Data_type_print, Color_for_zero_value, Map_name_to_element, _common_ns::_xray_data_type::XRAY_DATA_TYPE_XRF);
          break;
          default:break;
        }
      }

      Progress.setValue(Vec_xrf_elements_selected_names.size());
    }
    else{
       QMessageBox::warning(this,tr("Warning"),tr("There are not elements"));
    }
  }
  else{
    QMessageBox::warning(this,tr("Warning"),"There must be at least one valid position");
  }
#else
  // Get starting timepoint
  if (Num_active_positions>0){
    if (Vec_names_of_selected_elements.size()>0){
      auto Start = std::chrono::high_resolution_clock::now();
      for (unsigned int i=0;i<Vec_names_of_selected_elements.size();i++){
        for (unsigned int j=0;j<_window_xmapslab_ns::NUM_TESTS;j++){
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
      }
      // Get ending timepoint
      auto Stop = std::chrono::high_resolution_clock::now();

      // Get duration. Substart timepoints to
      // get duration. To cast it to proper unit
      // use duration cast method
      auto Duration = std::chrono::duration_cast<std::chrono::microseconds>(Stop - Start);
      float Final_duration=float(Duration.count())/float(Vec_names_of_selected_elements.size()*_window_xmapslab_ns::NUM_TESTS);

      cout << "Time taken by function: " << Final_duration/1000000.0f << " seconds" << endl;
    }
    else{
      QMessageBox::warning(this,tr("Warning"),tr("There are not elements"));
    }
  }
  else{
    QMessageBox::warning(this,tr("Warning"),"There must be at least one valid position");
  }
#endif
}

/*************************************************************************/

void _window_xmapslab::xrf_create_all_maps()
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

        switch(XRF_interpolation_type){
          case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_HYPERCUBE_DISTANCE:
          case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_2D_CARTESIAN_DISTANCE:
            add_layer_map_minimum_hypercube_distance(Name_selected_image, Vec_element_names[i], XRF_view_name,XRF_color_model,XRF_use_colors,XRF_use_positions, XRF_distance_normalization, XRF_position_normalization_type, XRF_probe, XRF_palette, Data_type_print, Color_for_zero_value,Map_name_to_element, _common_ns::_xray_data_type::XRAY_DATA_TYPE_XRF);
          break;
          case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_RBF:
            add_layer_map_rbf_interpolation(Name_selected_image, Vec_element_names[i], XRF_view_name, XRF_color_model, XRF_palette, Data_type_print, Color_for_zero_value, Map_name_to_element, _common_ns::_xray_data_type::XRAY_DATA_TYPE_XRF);
          break;
          case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_TRIANGULATION:
            add_layer_map_triangulation(Name_selected_image, Vec_element_names[i], XRF_view_name, XRF_color_model, XRF_palette, XRF_triangulation_add_corners, Data_type_print, Color_for_zero_value, Map_name_to_element, _common_ns::_xray_data_type::XRAY_DATA_TYPE_XRF);
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

#ifdef XRD_ACTIVE

/*************************************************************************/

void _window_xmapslab::xrd_use_colors(int Pos,bool Value)
{
  if (Pos>=0 && Pos<=2){
    XRD_use_colors[Pos]=Value;
  }
}

/*************************************************************************/

bool _window_xmapslab::xrd_use_colors(int Pos)
{
  if (Pos>=0 && Pos<=2){
    return XRD_use_colors[Pos];
  }

  return false;
}

/*************************************************************************/

void _window_xmapslab::xrd_use_positions(int Pos,bool Value)
{
  if (Pos>=0 && Pos<=1){
    XRD_use_positions[Pos]=Value;
  }
}

/*************************************************************************/

bool _window_xmapslab::xrd_use_positions(int Pos)
{
  if (Pos>=0 && Pos<=1){
    return XRD_use_positions[Pos];
  }

  return false;
}

/*************************************************************************/

void _window_xmapslab::xrd_create_some_maps()
{
  if (Num_active_positions>0){
    if (Vec_xrd_pigments_selected_names.size()>0){
      int Count_progress=0;
      QProgressDialog Progress("Computing...", "Abort",0,Vec_xrd_pigments_selected_names.size(),this);
      Progress.setWindowModality(Qt::WindowModal);
      Progress.setMinimumDuration(0);
      Progress.setCancelButton(0);

      for (unsigned int i=0;i<Vec_xrd_pigments_selected_names.size();i++){
        Progress.setValue(Count_progress++);
        if (Progress.wasCanceled()) break;

        switch(XRD_interpolation_type){
          case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_HYPERCUBE_DISTANCE:
          case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_2D_CARTESIAN_DISTANCE:
            add_layer_map_minimum_hypercube_distance(Name_selected_image,Vec_xrd_pigments_selected_names[i],XRD_view_name, XRD_color_model, XRD_use_colors, XRD_use_positions, XRD_distance_normalization, XRD_position_normalization_type, XRD_probe, XRD_palette, Data_type_print, Color_for_zero_value, Map_name_to_compound, _common_ns::_xray_data_type::XRAY_DATA_TYPE_XRD);
          break;
          case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_RBF:
            add_layer_map_rbf_interpolation(Name_selected_image, Vec_xrd_pigments_selected_names[i], XRD_view_name, XRD_color_model, XRD_palette, Data_type_print, Color_for_zero_value,  Map_name_to_compound, _common_ns::_xray_data_type::XRAY_DATA_TYPE_XRD);
          break;
          case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_TRIANGULATION:
            add_layer_map_triangulation(Name_selected_image, Vec_xrd_pigments_selected_names[i], XRD_view_name, XRD_color_model, XRD_palette, XRD_triangulation_add_corners, Data_type_print, Color_for_zero_value, Map_name_to_compound, _common_ns::_xray_data_type::XRAY_DATA_TYPE_XRD);
          break;
          default:break;
        }
      }

      Progress.setValue(Vec_xrd_pigments_selected_names.size());
    }
    else{
       QMessageBox::warning(this,tr("Warning"),tr("There are not pigments"));
    }
  }
  else{
    QMessageBox::warning(this,tr("Warning"),"There must be at least one valid position");
  }
}
#endif

/*************************************************************************/
#ifdef XRD_ACTIVE
void _window_xmapslab::xrd_create_all_maps()
{
  if (Num_active_positions>0){
    if (Vec_compound_names.size()>0){
      int Count_progress=0;
      QProgressDialog Progress("Computing...", "Abort",0,Vec_compound_names.size(),this);
      Progress.setWindowModality(Qt::WindowModal);
      Progress.setMinimumDuration(0);
      Progress.setCancelButton(0);

      for (unsigned int i=0;i<Vec_compound_names.size();i++){
        Progress.setValue(Count_progress++);
        if (Progress.wasCanceled()) break;

        switch(XRD_interpolation_type){
          case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_HYPERCUBE_DISTANCE:
          case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_2D_CARTESIAN_DISTANCE:
            add_layer_map_minimum_hypercube_distance(Name_selected_image, Vec_compound_names[i], XRD_view_name, XRD_color_model, XRD_use_colors, XRD_use_positions, XRD_distance_normalization, XRD_position_normalization_type, XRD_probe, XRD_palette, Data_type_print, Color_for_zero_value, Map_name_to_compound, _common_ns::_xray_data_type::XRAY_DATA_TYPE_XRD);
        break;
          break;
          case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_RBF:
            add_layer_map_rbf_interpolation(Name_selected_image, Vec_compound_names[i], XRD_view_name, XRD_color_model, XRD_palette, Data_type_print, Color_for_zero_value,  Map_name_to_compound, _common_ns::_xray_data_type::XRAY_DATA_TYPE_XRD);
          break;
          case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_TRIANGULATION:
          add_layer_map_triangulation(Name_selected_image, Vec_compound_names[i], XRD_view_name, XRD_color_model, XRD_palette, XRD_triangulation_add_corners, Data_type_print, Color_for_zero_value, Map_name_to_compound, _common_ns::_xray_data_type::XRAY_DATA_TYPE_XRD);
        break;
          break;
          default:break;
        }
      }

      Progress.setValue(Vec_compound_names.size());
    }
    else{
       QMessageBox::warning(this,tr("Warning"),tr("There are not pigments"));
    }
  }
  else{
    QMessageBox::warning(this,tr("Warning"),"There must be at least one valid position");
  }
}
#endif

/*************************************************************************/
#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
void _window_xmapslab::compounds_from_elements_create_some_maps()
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
#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
          add_layer_compound_from_elements(Name_selected_image,Vec_compounds_from_elements_pdb[j].Name,View_name,Vec_compounds_from_elements_pdb[j].Vec_elements_combination,Vec_names_in_map, Vec_global_percentages, Palette, Data_type_print,Color_for_zero_value);
#endif
        }

        break;
      }
    }
  }

  Progress.setValue(Vec_compounds_from_elements_pdb.size());
}
#endif

/*************************************************************************/
#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
void _window_xmapslab::compounds_from_elements_create_all_maps()
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

#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
      add_layer_compound_from_elements(Name_selected_image,Vec_compounds_from_elements_pdb[i].Name,View_name,Vec_compounds_from_elements_pdb[i].Vec_elements_combination,Vec_names_in_map, Vec_global_percentages, Palette, Data_type_print,Color_for_zero_value);
#endif
    }
  }

  Progress.setValue(Vec_compounds_from_elements_pdb.size());
}
#endif

/*************************************************************************/

#ifdef XRD_ACTIVE
void _window_xmapslab::xrd_recompute_data()
{
}
#endif

/*************************************************************************/

void _window_xmapslab::compute_mean_distance_between_positions()
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
// compute the mean distance of all edges of all triangles

void _window_xmapslab::compute_mean_distance_between_neighbors_positions()
{
  float Max_distance=0;
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

    Mean_distance_between_neighbors_positions=Max_distance/float(Triangles.size()*3);
  }
  else{
    // There are 1 or 2 valid points.
    if (Num_active_positions==1){
      Mean_distance_between_neighbors_positions=image_diagonal_size();
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

/*************************************************************************/

std::vector<std::string> _window_xmapslab::split(const std::string& s, char delimiter)
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

