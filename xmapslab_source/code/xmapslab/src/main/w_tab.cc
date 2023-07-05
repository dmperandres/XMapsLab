/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#include "w_tab.h"
#include "window.h"

/*************************************************************************/

_w_tab::_w_tab(_window *Window1): Window(Window1)
{
  setMinimumSize(QSize(100,300));

  // 10% of the size of the widow
  setMaximumWidth(Window->width()/10);
}

/*************************************************************************/

_w_tab::~_w_tab()
{
}

/*************************************************************************/

void _w_tab::initialize()
{
  xrf_create_files_widget();
  create_layers_widget();
  create_elements_widget();
  create_compounds_from_elements_widget();

  int Position=0;
  addTab(Widget_valid_positions, tr("Positions"));
  Map_pos_of_tab[_w_tab_ns::_tabs::POSITIONS_TAB]=Position++;
  addTab(Widget_layers, tr("Layers"));
  Map_pos_of_tab[_w_tab_ns::_tabs::LAYERS_TAB]=Position++;
  addTab(Widget_elements, tr("XRF"));
  Map_pos_of_tab[_w_tab_ns::_tabs::ELEMENTS_TAB]=Position++;
  addTab(Widget_compounds_from_elements, tr("Compounds"));
  Map_pos_of_tab[_w_tab_ns::_tabs::COMPOUNDS_FROM_XRF_TAB]=Position++;

  setCurrentIndex(pos_of_tab(_w_tab_ns::_tabs::POSITIONS_TAB));

//  create_palettes_widget();
//  addTab(Widget_palettes, tr("Palettes"));

  for (int i=0;i<int(_w_tab_ns::_tabs::TAB_LAST);i++){
    setTabEnabled(i,false);
  }

  setCurrentIndex(0);

  QFontMetrics Font_metric(font());
//  int Width_text = Font_metric.width("M");
  int Width_text = Font_metric.horizontalAdvance("M");

  setMinimumWidth(Width_text*_gl_widget_ns::WIDTH_TAB_CHARS);
  setMaximumWidth(Width_text*_gl_widget_ns::WIDTH_TAB_CHARS);

  connect(this,SIGNAL(tabBarClicked(int)),this,SLOT(tab_bar_clicked_slot(int)));
}

/*************************************************************************/

void _w_tab::create_layers_widget()
{
  Widget_layers=new QWidget;

  Verticalbox_layers=new QVBoxLayout;

  std::string Name_table0="Layers";
  Table_layers=new _table_layers(Name_table0,this);

//   connect(Table_layers,SIGNAL(cellClicked(int,int)),this,SLOT(cell_clicked_slot(int,int)));

  // separator
  QFrame *Separator=new QFrame();
  Separator->setFrameStyle(QFrame::HLine);

  QFrame *Separator1=new QFrame();
  Separator1->setFrameStyle(QFrame::HLine);

  QFrame *Separator2=new QFrame();
  Separator2->setFrameStyle(QFrame::HLine);

  QFrame *Separator3=new QFrame();
  Separator3->setFrameStyle(QFrame::HLine);

  QWidget *Group_box_buttons=new QWidget;
  QVBoxLayout *Vertical_box_buttons=new QVBoxLayout;

  Combo_add_layer = new QComboBox;
  for (unsigned int i=0;i<_layer_ns::Vec_additional_layers.size();i++){
    Combo_add_layer->addItem(_layer_ns::Vec_additional_layers[i]);
  }
  Combo_add_layer->setCurrentIndex(0);

  connect(Combo_add_layer, SIGNAL(activated(int)), this,SLOT(add_filter_layer_slot(int)));

  QPushButton *Button_remove_layer= new QPushButton("Remove selected layer", this);
  connect(Button_remove_layer, SIGNAL(clicked()),this,SLOT(remove_selected_layer_slot()));

  QPushButton *Button_remove_all_layers= new QPushButton("Remove all layers", this);
  connect(Button_remove_all_layers, SIGNAL(clicked()),this,SLOT(remove_all_layers_slot()));

//  QPushButton *Button_recompute_all_layers= new QPushButton("Recompute all element layers", this);
//  Button_recompute_all_layers->setStyleSheet("background-color : orange");
//  connect(Button_recompute_all_layers, SIGNAL(clicked()),this,SLOT(recompute_all_layers_slot()));

  Vertical_box_buttons->addWidget(Combo_add_layer);
  Vertical_box_buttons->addWidget(Separator1);
  Vertical_box_buttons->addWidget(Button_remove_layer);
  Vertical_box_buttons->addWidget(Separator2);
  Vertical_box_buttons->addWidget(Button_remove_all_layers);
//  Vertical_box_buttons->addWidget(Separator3);
//  Vertical_box_buttons->addWidget(Button_recompute_all_layers);

  Group_box_buttons->setLayout(Vertical_box_buttons);

  //
  Verticalbox_layers->addWidget(static_cast<QTableWidget *>(Table_layers));
  Verticalbox_layers->addWidget(Separator);
  Verticalbox_layers->addWidget(Group_box_buttons);

  Widget_layers->setLayout(Verticalbox_layers);

  Widget_layers->setEnabled(false);
}

/*************************************************************************/

void _w_tab::create_elements_widget()
{
  Widget_elements=new QWidget;
  Verticalbox_elements=new QVBoxLayout;

  // Images
  QGroupBox *Groupbox_images=new QGroupBox("Images");
  QVBoxLayout *Verticalbox_images1=new QVBoxLayout;

  Listwidget_elements_images=new QListWidget;
  Listwidget_elements_images->setSelectionMode(QAbstractItemView::ExtendedSelection);
  if (Window->screen_height()<=1080) Listwidget_elements_images->setIconSize(QSize(_window_ns::ICON_SIZE_1080,_window_ns::ICON_SIZE_1080));
  else Listwidget_elements_images->setIconSize(QSize(_window_ns::ICON_SIZE_1080*2,_window_ns::ICON_SIZE_1080*2));

  Verticalbox_images1->addWidget(Listwidget_elements_images);
  Groupbox_images->setLayout(Verticalbox_images1);

  // Elements
  QGroupBox *Groupbox_elements=new QGroupBox("Elements");
  QVBoxLayout *Verticalbox_elements1=new QVBoxLayout;

  Listwidget_elements=new QListWidget;
  Listwidget_elements->setSelectionMode(QAbstractItemView::MultiSelection);

  Verticalbox_elements1->addWidget(Listwidget_elements);
  Groupbox_elements->setLayout(Verticalbox_elements1);

  // view name
  Frame_elements_view_name=new QFrame;
  Frame_elements_view_name->setFrameStyle(QFrame::Panel);

  Lineedit_elements_view_name=new QLineEdit(_w_tab_ns::VIEW_NAME_DEFAULT);

  QGridLayout *Grid_view_name=new QGridLayout;

  QLabel *Label_view_name=new QLabel("View_name");
  Grid_view_name->addWidget(Label_view_name,0,0,Qt::AlignRight);
  Grid_view_name->addWidget(Lineedit_elements_view_name,0,1,Qt::AlignLeft);

  Frame_elements_view_name->setLayout(Grid_view_name);

  connect(Lineedit_elements_view_name,SIGNAL(textChanged(QString)),this,SLOT(changed_view_name_slot(QString)));

  // type of interpolation
  Frame_elements_interpolation_type=new QFrame;
  Frame_elements_interpolation_type->setFrameStyle(QFrame::Panel);

  QGridLayout *Grid_interpolation_type=new QGridLayout;

  Combobox_elements_interpolation_type = new QComboBox;

  for (unsigned int i=0; i<_layer_map_ns::Vec_interpolation_method_names.size();i++){
    Combobox_elements_interpolation_type->addItem(_layer_map_ns::Vec_interpolation_method_names[i]);
  }
  Combobox_elements_interpolation_type->setCurrentIndex(int(Window->map_interpolation_type()));

  QLabel *Label_interpolation_type=new QLabel("Interpolation type");
  Grid_interpolation_type->addWidget(Label_interpolation_type,0,0,Qt::AlignRight);
  Grid_interpolation_type->addWidget(Combobox_elements_interpolation_type,0,1,Qt::AlignLeft);

  Frame_elements_interpolation_type->setLayout(Grid_interpolation_type);

  connect(Combobox_elements_interpolation_type,SIGNAL(activated(int)),this,SLOT(changed_interpolation_type_slot(int)));

  // for distance only
  // color model

  // normalization
  Frame_elements_normalization=new QFrame;
  Frame_elements_normalization->setFrameStyle(QFrame::Panel);

  QGridLayout *Grid_normalization=new QGridLayout;

  QLabel *Label_normalization=new QLabel("Normalization");

  Checkbox_elements_normalization=new QCheckBox;
  Checkbox_elements_normalization->setChecked(Window->distance_normalization());

  Grid_normalization->addWidget(Label_normalization,0,0,Qt::AlignRight);
  Grid_normalization->addWidget(Checkbox_elements_normalization,0,1,Qt::AlignLeft);

  Frame_elements_normalization->setLayout(Grid_normalization);

  connect(Checkbox_elements_normalization,SIGNAL(stateChanged(int)),this,SLOT(changed_normalization_slot(int)));

  // normalization position
  Frame_elements_normalization_position=new QFrame;
  Frame_elements_normalization_position->setFrameStyle(QFrame::Panel);

  QGridLayout *Grid_normalization_position=new QGridLayout;

  QLabel *Label_normalization_homogeneous=new QLabel("Pos. normalization");

  Combobox_elements_position_normalization_type = new QComboBox;
  for (unsigned int i=0; i<_layer_map_distance_ns::Vec_names_position_interpolation_type.size();i++){
    Combobox_elements_position_normalization_type->addItem(_layer_map_distance_ns::Vec_names_position_interpolation_type[i]);
  }
  Combobox_elements_position_normalization_type->setCurrentIndex(int(Window->position_normalization_type()));

  Grid_normalization_position->addWidget(Label_normalization_homogeneous,0,0,Qt::AlignCenter);
  Grid_normalization_position->addWidget(Combobox_elements_position_normalization_type,0,1,Qt::AlignCenter);

  Frame_elements_normalization_position->setLayout(Grid_normalization_position);

  connect(Combobox_elements_position_normalization_type,SIGNAL(activated(int)),this,SLOT(changed_position_normalization_slot(int)));

  // Probe
  Frame_elements_probe=new QFrame;
  Frame_elements_probe->setFrameStyle(QFrame::Panel);

  QGridLayout *Grid_element_parameters=new QGridLayout;

  Combobox_elements_probe = new QComboBox;
  for (unsigned int i=0; i<_layer_map_ns::Vec_name_probe.size();i++){
    Combobox_elements_probe->addItem(_layer_map_ns::Vec_name_probe[i]);
  }
  Combobox_elements_probe->setCurrentIndex(Window->probe());

  QLabel *Label_element_parameters2=new QLabel("Probe");
  Grid_element_parameters->addWidget(Label_element_parameters2,0,0,Qt::AlignRight);
  Grid_element_parameters->addWidget(Combobox_elements_probe,0,1,Qt::AlignLeft);

  Frame_elements_probe->setLayout(Grid_element_parameters);

  connect(Combobox_elements_probe,SIGNAL(activated(int)),this,SLOT(changed_probe_slot(int)));

  // for triangulation
  // add corners
  Frame_elements_triangulation_add_corners=new QFrame;
  Frame_elements_triangulation_add_corners->setFrameStyle(QFrame::Panel);

  QLabel *Label_triangulation_add_corners=new QLabel("Add corners");

  Checkbox_elements_triangulation_add_corners=new QCheckBox;
  Checkbox_elements_triangulation_add_corners->setChecked(Window->triangulation_add_corners());

  QGridLayout *Grid_triangulation_add_corners=new QGridLayout;

  Grid_triangulation_add_corners->addWidget(Label_triangulation_add_corners,0,0,Qt::AlignRight);
  Grid_triangulation_add_corners->addWidget(Checkbox_elements_triangulation_add_corners,0,1,Qt::AlignLeft);

  Frame_elements_triangulation_add_corners->setLayout(Grid_triangulation_add_corners);

  Frame_elements_triangulation_add_corners->hide();

  connect(Checkbox_elements_triangulation_add_corners,SIGNAL(stateChanged(int)),this,SLOT(changed_triangulation_add_corners_slot(int)));

  //** for RBF

  // RBF function
  Frame_elements_rbf_function=new QFrame;
  Frame_elements_rbf_function->setFrameStyle(QFrame::Panel);

  QLabel *Label_elements_rbf_function=new QLabel("Function");

  Combobox_elements_rbf_function = new QComboBox;
  for (unsigned int i=0;i<_new_rbf_interpolation_2d_ns::Vec_names_function.size();i++){
    Combobox_elements_rbf_function->addItem(QString::fromStdString(_new_rbf_interpolation_2d_ns::Vec_names_function[i]));
  }
  Combobox_elements_rbf_function->setCurrentIndex(int(_new_rbf_interpolation_2d_ns::FUNCTION_TYPE_DEFAULT));

  connect(Combobox_elements_rbf_function,SIGNAL(currentIndexChanged(int)),this,SLOT(changed_rbf_function_slot(int)));

  // Radius
  Frame_elements_rbf_radius=new QFrame;
  Frame_elements_rbf_radius->setFrameStyle(QFrame::Panel);

  QLabel *Label_elements_rbf_radius=new QLabel("Radius");
  QLabel *Label_elements_rbf_radius_min=new QLabel("Min");
  QLabel *Label_elements_rbf_radius_max=new QLabel("Max");

  Slider_elements_rbf_radius=new QSlider(Qt::Horizontal);
  Slider_elements_rbf_radius->setRange(0,255);
  Slider_elements_rbf_radius->setSingleStep(1);
  Slider_elements_rbf_radius->setPageStep(10);
  Slider_elements_rbf_radius->setTickInterval(25);
  Slider_elements_rbf_radius->setTickPosition(QSlider::TicksRight);
//  Slider_elements_rbf_radius->setToolTip(tr(String_parameter2_tooltip.c_str()));

//  Slider_elements_rbf_radius->setMinimumWidth(width());

  QGridLayout *Grid_elements_rbf_radius=new QGridLayout;

  Grid_elements_rbf_radius->addWidget(Label_elements_rbf_radius,0,1,Qt::AlignCenter);
  Grid_elements_rbf_radius->addWidget(Label_elements_rbf_radius_min,1,0,Qt::AlignLeft);
  Grid_elements_rbf_radius->addWidget(Slider_elements_rbf_radius,1,1);
  Grid_elements_rbf_radius->addWidget(Label_elements_rbf_radius_max,1,2,Qt::AlignRight);

  Frame_elements_rbf_radius->setLayout(Grid_elements_rbf_radius);

  Frame_elements_rbf_radius->hide();

  QGridLayout *Grid_elements_rbf_function=new QGridLayout;

  Grid_elements_rbf_function->addWidget(Label_elements_rbf_function,0,0,Qt::AlignRight);
  Grid_elements_rbf_function->addWidget(Combobox_elements_rbf_function,0,1,Qt::AlignLeft);

  Frame_elements_rbf_function->setLayout(Grid_elements_rbf_function);

  Frame_elements_rbf_function->hide();

  // Palette
  QFrame *Frame_elements_palette=new QFrame;
  Frame_elements_palette->setFrameStyle(QFrame::Panel);

  QGridLayout *Grid_element_palette=new QGridLayout;

  QLabel *Label_element_palette1=new QLabel("Palette");

  Combobox_elements_palette = new QComboBox;
  for (unsigned int i=0;i<Window->Vec_palette_data.size();i++){
    Combobox_elements_palette->addItem(Window->Vec_palette_data[i].name());
  }
  Combobox_elements_palette->setCurrentIndex(Window->palette());

  Grid_element_palette->addWidget(Label_element_palette1,0,0,Qt::AlignRight);
  Grid_element_palette->addWidget(Combobox_elements_palette,0,1,Qt::AlignLeft);

  Frame_elements_palette->setLayout(Grid_element_palette);

  connect(Combobox_elements_palette,SIGNAL(activated(int)),this,SLOT(changed_palette_slot(int)));

  // separator
  QFrame *Separator=new QFrame();
  Separator->setFrameStyle(QFrame::HLine);

  // separator 1
  QFrame *Separator1=new QFrame();
  Separator1->setFrameStyle(QFrame::HLine);

  // separator 2
  QFrame *Separator2=new QFrame();
  Separator2->setFrameStyle(QFrame::HLine);

  QWidget *Group_box_buttons=new QWidget;
  QVBoxLayout *Vertical_box_buttons=new QVBoxLayout;

  Button_elements_create_some_maps= new QPushButton("Create some maps", this);
  Button_elements_create_some_maps->setEnabled(false);
  connect(Button_elements_create_some_maps, SIGNAL(clicked()),this,SLOT(elements_create_some_maps_slot()));

  Button_elements_create_all_maps= new QPushButton("Create all the maps", this);
  Button_elements_create_all_maps->setEnabled(false);
  connect(Button_elements_create_all_maps, SIGNAL(clicked()),this,SLOT(elements_create_all_maps_slot()));

  Vertical_box_buttons->addWidget(Button_elements_create_some_maps);
  Vertical_box_buttons->addWidget(Separator2);
  Vertical_box_buttons->addWidget(Button_elements_create_all_maps);

  Group_box_buttons->setLayout(Vertical_box_buttons);

  //
  Verticalbox_elements->addWidget(Groupbox_images);
  Verticalbox_elements->addWidget(Groupbox_elements);
  Verticalbox_elements->addWidget(Frame_elements_view_name);
  Verticalbox_elements->addWidget(Frame_elements_interpolation_type);
  Verticalbox_elements->addWidget(Frame_elements_normalization);
  Verticalbox_elements->addWidget(Frame_elements_normalization_position);
  Verticalbox_elements->addWidget(Frame_elements_probe);
  Verticalbox_elements->addWidget(Frame_elements_triangulation_add_corners);
  Verticalbox_elements->addWidget(Frame_elements_rbf_function);
  Verticalbox_elements->addWidget(Frame_elements_rbf_radius);
  Verticalbox_elements->addWidget(Frame_elements_palette);
  Verticalbox_elements->addWidget(Separator1);
  Verticalbox_elements->addWidget(Group_box_buttons);

  Widget_elements->setLayout(Verticalbox_elements);
}

/*************************************************************************/
// compounds combinations

void _w_tab::create_compounds_from_elements_widget()
{
  Widget_compounds_from_elements=new QWidget;
  Verticalbox_compounds_combination=new QVBoxLayout;

  // Compounds of the PDB
  QGroupBox *Groupbox_compounds_combination=new QGroupBox("Compounds");
  QVBoxLayout *Verticalbox_compounds_combination1=new QVBoxLayout;

  Listwidget_compounds_combination=new QListWidget;
  Listwidget_compounds_combination->setSelectionMode(QAbstractItemView::MultiSelection);

  Verticalbox_compounds_combination1->addWidget(Listwidget_compounds_combination);
  Groupbox_compounds_combination->setLayout(Verticalbox_compounds_combination1);

  // view name
  Frame_compounds_combination_view_name=new QFrame;
  Frame_compounds_combination_view_name->setFrameStyle(QFrame::Panel);

  Lineedit_compounds_combination_view_name=new QLineEdit(_w_tab_ns::VIEW_NAME_DEFAULT);

  QGridLayout *Grid_view_name=new QGridLayout;

  QLabel *Label_view_name=new QLabel("View_name");
  Grid_view_name->addWidget(Label_view_name,0,0,Qt::AlignRight);
  Grid_view_name->addWidget(Lineedit_compounds_combination_view_name,0,1,Qt::AlignLeft);

  Frame_compounds_combination_view_name->setLayout(Grid_view_name);

  connect(Lineedit_compounds_combination_view_name,SIGNAL(textChanged(QString)),this,SLOT(changed_view_name_slot(QString)));

  // parameters
//  Frame_compounds_combination_minimum_distance_parameters=new QFrame;
//  Frame_compounds_combination_minimum_distance_parameters->setFrameStyle(QFrame::Panel);

//  QGridLayout *Grid_minimum_distance_parameters=new QGridLayout;

//  QLabel *Label_minimum_distance_parameters1=new QLabel("Color 1");

//  Checkbox_compounds_combination_use_color1=new QCheckBox;
//  Checkbox_compounds_combination_use_color1->setChecked(Window->use_colors(0));

//  connect(Checkbox_compounds_combination_use_color1,SIGNAL(stateChanged(int)),this,SLOT(changed_use_color1_slot(int)));

//  Grid_minimum_distance_parameters->addWidget(Label_minimum_distance_parameters1,0,0,Qt::AlignRight);
//  Grid_minimum_distance_parameters->addWidget(Checkbox_compounds_combination_use_color1,0,1,Qt::AlignLeft);

//  Frame_compounds_combination_minimum_distance_parameters->setLayout(Grid_minimum_distance_parameters);

  // Probe
  Frame_compounds_combination_probe=new QFrame;
  Frame_compounds_combination_probe->setFrameStyle(QFrame::Panel);

  QGridLayout *Grid_element_parameters=new QGridLayout;

  Combobox_compounds_combination_probe = new QComboBox;
  for (unsigned int i=0; i<_layer_map_ns::Vec_name_probe.size();i++){
    Combobox_compounds_combination_probe->addItem(_layer_map_ns::Vec_name_probe[i]);
  }
  Combobox_compounds_combination_probe->setCurrentIndex(Window->probe());

  QLabel *Label_element_parameters2=new QLabel("Probe");
  Grid_element_parameters->addWidget(Label_element_parameters2,0,0,Qt::AlignRight);
  Grid_element_parameters->addWidget(Combobox_compounds_combination_probe,0,1,Qt::AlignLeft);

  Frame_compounds_combination_probe->setLayout(Grid_element_parameters);

  connect(Combobox_compounds_combination_probe,SIGNAL(activated(int)),this,SLOT(changed_probe_slot(int)));

  // Palette
  QFrame *Frame_compounds_combination_palette=new QFrame;
  Frame_compounds_combination_palette->setFrameStyle(QFrame::Panel);

  QGridLayout *Grid_element_palette=new QGridLayout;

  QLabel *Label_element_palette1=new QLabel("Palette");

  Combobox_compounds_combination_palette = new QComboBox;
  for (unsigned int i=0;i<Window->Vec_palette_data.size();i++){
    Combobox_compounds_combination_palette->addItem(Window->Vec_palette_data[i].name());
  }
  Combobox_compounds_combination_palette->setCurrentIndex(Window->palette());

  Grid_element_palette->addWidget(Label_element_palette1,0,0,Qt::AlignRight);
  Grid_element_palette->addWidget(Combobox_compounds_combination_palette,0,1,Qt::AlignLeft);

  Frame_compounds_combination_palette->setLayout(Grid_element_palette);

  connect(Combobox_compounds_combination_palette,SIGNAL(activated(int)),this,SLOT(changed_palette_slot(int)));

  // separator
  QFrame *Separator=new QFrame();
  Separator->setFrameStyle(QFrame::HLine);

  // separator 1
  QFrame *Separator1=new QFrame();
  Separator1->setFrameStyle(QFrame::HLine);

  // separator 2
  QFrame *Separator2=new QFrame();
  Separator2->setFrameStyle(QFrame::HLine);

  QWidget *Group_box_buttons=new QWidget;
  QVBoxLayout *Vertical_box_buttons=new QVBoxLayout;

  Button_compounds_combination_create_combination_maps= new QPushButton("Create combination maps", this);
//  Button_compounds_combination_create_combination_maps->setEnabled(false);
  connect(Button_compounds_combination_create_combination_maps, SIGNAL(clicked()),this,SLOT(compounds_combination_create_combination_maps_slot()));

  Button_compounds_combination_create_all_individual_maps= new QPushButton("Create all individual maps", this);
//  Button_compounds_combination_create_all_individual_maps->setEnabled(false);
  connect(Button_compounds_combination_create_all_individual_maps, SIGNAL(clicked()),this,SLOT(compounds_combination_create_all_individual_maps_slot()));

  Vertical_box_buttons->addWidget(Button_compounds_combination_create_combination_maps);
  Vertical_box_buttons->addWidget(Separator2);
  Vertical_box_buttons->addWidget(Button_compounds_combination_create_all_individual_maps);

  Group_box_buttons->setLayout(Vertical_box_buttons);

  //
  Verticalbox_compounds_combination->addWidget(Groupbox_compounds_combination);
  Verticalbox_compounds_combination->addWidget(Frame_compounds_combination_view_name);
//  Verticalbox_compounds_combination->addWidget(Frame_compounds_combination_interpolation_type);

  Verticalbox_compounds_combination->addWidget(Frame_compounds_combination_probe);
  Verticalbox_compounds_combination->addWidget(Frame_compounds_combination_palette);
  Verticalbox_compounds_combination->addWidget(Separator1);
  Verticalbox_compounds_combination->addWidget(Group_box_buttons);

  Widget_compounds_from_elements->setLayout(Verticalbox_compounds_combination);
}

/*************************************************************************/
// compounds xrd

/*************************************************************************/

void _w_tab::create_palettes_widget()
{
  Widget_palettes=new QWidget;
  Verticalbox_palettes=new QVBoxLayout;

    Pixmap_palette_discrete=new QPixmap;
  Pixmap_palette_discrete->load(":/common/icons/discrete.png");
  Icon_discrete.addPixmap(*Pixmap_palette_discrete);

  Pixmap_palette_continuous=new QPixmap;
  Pixmap_palette_continuous->load(":/common/icons/continuous.png");
  Icon_continuous.addPixmap(*Pixmap_palette_continuous);

  Listwidget_palettes=new QListWidget;

  QListWidgetItem *Item;
  for (unsigned int i=0;i<Window->Color_bar_widget->Palettes.size();i++){
    Item=new QListWidgetItem;
    Item->setText(Window->Vec_palette_data[i].name());
    if (Window->Vec_palette_data[i].data_type()==_palette_data_ns::_data_type::DATA_TYPE_CONTINUOUS) Item->setIcon(Icon_continuous);
    else Item->setIcon(Icon_discrete);
//    Item->setCheckState(Qt::Checked);
    Listwidget_palettes->addItem(Item);
  }

  Listwidget_palettes->setCurrentRow(0);

  connect(Listwidget_palettes, SIGNAL(currentRowChanged(int)),this,SLOT(change_row_palette_slot(int)));

  // separator
  QFrame *Separator=new QFrame();
  Separator->setFrameStyle(QFrame::HLine);

  QWidget *Group_box_buttons=new QWidget;
  QVBoxLayout *Vertical_box_buttons=new QVBoxLayout;

  QPushButton *Button_add_palette= new QPushButton("Create palette", this);
  connect(Button_add_palette, SIGNAL(clicked()),this,SLOT(create_palette_slot()));

  QPushButton *Button_remove_palette= new QPushButton("Remove palette", this);
//  connect(Button_remove_palette, SIGNAL(clicked()),this,SLOT(remove_element_slot()));

  Vertical_box_buttons->addWidget(Button_add_palette);
  Vertical_box_buttons->addWidget(Button_remove_palette);

  Group_box_buttons->setLayout(Vertical_box_buttons);
//  Verticalbox_palettes->addWidget(static_cast<QTableWidget *>(Tables.get_data(Name_table0).get()));

  Verticalbox_palettes->addWidget(Listwidget_palettes);
  Verticalbox_palettes->addWidget(Separator);
  Verticalbox_palettes->addWidget(Group_box_buttons);
  //  Verticalbox_palettes->addStretch();

  Widget_palettes->setLayout(Verticalbox_palettes);
  Widget_palettes->setEnabled(true);
}

/*************************************************************************/

void _w_tab::xrf_create_files_widget()
{
  Widget_valid_positions=new QWidget;

  Verticalbox_valid_positions=new QVBoxLayout;

  std::string Name_table0="XRF files";
  Table_valid_positions=new _table_active_positions(Name_table0,this);

//   connect(Table_valid_positions,SIGNAL(cellClicked(int,int)),this,SLOT(cell_clicked_slot(int,int)));

  // separator
  QFrame *Separator=new QFrame();
  Separator->setFrameStyle(QFrame::HLine);

  QPushButton *Button_xrf_files_apply_changes= new QPushButton("Update data", this);
  connect(Button_xrf_files_apply_changes, SIGNAL(clicked()),this,SLOT(changed_selected_positions_slot()));

  //
  Verticalbox_valid_positions->addWidget(static_cast<QTableWidget *>(Table_valid_positions));
  Verticalbox_valid_positions->addWidget(Separator);
  Verticalbox_valid_positions->addWidget(Button_xrf_files_apply_changes);

  Widget_valid_positions->setLayout(Verticalbox_valid_positions);
}

/*************************************************************************/

/*************************************************************************/

void _w_tab::tab_bar_clicked_slot(int Tab1)
{
  Window->selected_tab(static_cast<_w_tab_ns::_tabs>(Tab1));

  Window->update_color_bar();
}

/*************************************************************************/

void _w_tab::add_filter_layer_slot(int Value)
{
  Combo_add_layer->setCurrentIndex(0);

  switch (Value){
  case int(_layer_ns::_additional_layer::ADDITIONAL_LAYER_NOTHING):break;
  }
}

/*************************************************************************/

void _w_tab::remove_layer_from_layout(std::string Name)
{
  Verticalbox_layers->removeWidget(static_cast<QWidget *>(Window->Map_name_to_layer[Name].Layer->get_link()));
  static_cast<QWidget *>(Window->Map_name_to_layer[Name].Layer->get_link())->setParent(0);
  static_cast<QWidget *>(Window->Map_name_to_layer[Name].Layer->get_link())->deleteLater();
}

/*************************************************************************/

void _w_tab::remove_selected_layer_slot()
{
  Window->remove_pigment_layer();
}

/*************************************************************************/

void _w_tab::remove_all_layers_slot()
{
  Window->remove_all_pigment_layers();
}

/*************************************************************************/

void _w_tab::elements_update_parameters()
{
  bool Value;
  // view name
  Window->view_name(Lineedit_elements_view_name->text().toStdString());

  // interpolation type
  Window->map_interpolation_type(static_cast<_layer_map_ns::_map_interpolation_methods>(Combobox_elements_interpolation_type->currentIndex()));

  switch (Window->map_interpolation_type()) {
  case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_HYPERCUBE_DISTANCE:
     Window->use_colors(0,true);
     Window->use_colors(1,true);
     Window->use_colors(2,true);
     Window->use_positions(0,true);
     Window->use_positions(1,true);
    break;
  case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_2D_CARTESIAN_DISTANCE:
    Window->use_colors(0,false);
    Window->use_colors(1,false);
    Window->use_colors(2,false);
    Window->use_positions(0,true);
    Window->use_positions(1,true);
    break;
  default:
    break;
  }

  // normalization
  if (Checkbox_elements_normalization->checkState()==Qt::Checked) Value=true;
  else Value=false;
  Window->distance_normalization(Value);

  // the position normalization
  Window->position_normalization_type(static_cast<_layer_map_distance_ns::_position_normalization_type>(Combobox_elements_position_normalization_type->currentIndex()));

  // the selected palette
  Window->palette(Combobox_elements_palette->currentIndex());

  // the selected probe
  Window->probe(_layer_map_ns::Vec_value_probe[Combobox_elements_probe->currentIndex()]);

  // add corners
  if (Checkbox_elements_triangulation_add_corners->checkState()==Qt::Checked) Value=true;
  else Value=false;
  Window->triangulation_add_corners(Value);

  // RBF_radius
  float Radius_value=float(Window->mean_distance_between_neighbors_positions())*float(Slider_elements_rbf_radius->value())/255.0f;
  Radius_value=Radius_value/float(Window->max_dimension());
  Window->rbf_radius(Radius_value);

  // RBF_function
  Window->rbf_function(_new_rbf_interpolation_2d_ns::_function_type(Combobox_elements_rbf_function->currentIndex()));

  Window->save_settings();
}

/*************************************************************************/

void _w_tab::elements_create_some_maps_slot()
{
  std::string Name_layer;
  std::string Name_element;

  QList<QListWidgetItem *> Selected_items_layers=Listwidget_elements_images->selectedItems();
  if (Selected_items_layers.size()>0){
    QList<QListWidgetItem *> Selected_items_elements=Listwidget_elements->selectedItems();

    if (Selected_items_elements.size()>0){
      // color image
      Window->name_selected_image(Selected_items_layers[0]->text().toStdString());

      //
      std::vector<std::string> Vec_names_selected_elements;
      for (int i=0;i<Selected_items_elements.size();i++){
        Vec_names_selected_elements.push_back(Selected_items_elements[i]->text().toStdString());
      }

      // data image
      Window->elements_selected_names(Vec_names_selected_elements);

      // view name
      // check that the _ are converted to -
      Window->view_name(Lineedit_elements_view_name->text().replace('_','-').toStdString());

      //
      elements_update_parameters();

      // create the element
      Window->elements_create_some_maps();
    }
    else{
      QMessageBox::information(Window, Window->tr("Information"),Window->tr("One element must be selected at least"));
    }
  }
  else{
    QMessageBox::information(Window, Window->tr("Information"),Window->tr("One image must be selected at least"));
  }
}

/*************************************************************************/

void _w_tab::elements_create_all_maps_slot()
{
  std::string Name_layer;
  std::string Name_element;

  QList<QListWidgetItem *> Selected_items_layers=Listwidget_elements_images->selectedItems();
  if (Selected_items_layers.size()>0){
    // color image
    Window->name_selected_image(Selected_items_layers[0]->text().toStdString());

    // view name
    Window->view_name(Lineedit_elements_view_name->text().toStdString());

    //
    elements_update_parameters();

    Window->elements_create_all_maps();
  }
  else{
    QMessageBox::information(Window, Window->tr("Information"),Window->tr("One image must be selected at least"));
  }
}

/*************************************************************************/

void _w_tab::changed_view_name_slot(QString Text)
{
  if (currentIndex()==int(_w_tab_ns::_tabs::ELEMENTS_TAB)){
  }
  else{
    Lineedit_elements_view_name->blockSignals(true);
    Lineedit_elements_view_name->setText(Text);
    Lineedit_elements_view_name->blockSignals(false);
  }
}

/*************************************************************************/

void _w_tab::changed_interpolation_type_slot(int Value)
{
  switch(static_cast<_layer_map_ns::_map_interpolation_methods>(Value)){
    case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_HYPERCUBE_DISTANCE:
    case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_2D_CARTESIAN_DISTANCE:

      Frame_elements_view_name->show();
      Frame_elements_normalization->show();
      Frame_elements_normalization_position->show();
      Frame_elements_probe->show();
      Frame_elements_triangulation_add_corners->hide();
      Frame_elements_rbf_function->hide();
      Frame_elements_rbf_radius->hide();      
      // compounds

    break;
    case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_RBF:
      Frame_elements_view_name->show();
      Frame_elements_normalization->hide();
      Frame_elements_normalization_position->hide();
      Frame_elements_probe->hide();
      Frame_elements_triangulation_add_corners->hide();
      Frame_elements_rbf_function->show();

      // the radius is only for some functions
      if (Window->rbf_function()==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_GAUSSIAN || Window->rbf_function()==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_MULTIQUADRIC || Window->rbf_function()==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_INVERSE_MULTIQUADRIC){

      Frame_elements_rbf_radius->show();
      }
      else{
      Frame_elements_rbf_radius->hide();
      }

      // compounds
    break;
    case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_TRIANGULATION:
      // elements
      Frame_elements_view_name->show();
  //    Frame_elements_color_model->hide();
//      Frame_elements_minimum_distance_parameters->hide();
      Frame_elements_normalization->hide();
      Frame_elements_normalization_position->hide();
      Frame_elements_probe->hide();
      Frame_elements_triangulation_add_corners->show();
      Frame_elements_rbf_function->hide();
      Frame_elements_rbf_radius->hide();
      // compounds
    break;
  }

  if (currentIndex()==int(_w_tab_ns::_tabs::ELEMENTS_TAB)){
  }
  else{
    Combobox_elements_interpolation_type->blockSignals(true);
    Combobox_elements_interpolation_type->setCurrentIndex(Value);
    Combobox_elements_interpolation_type->blockSignals(false);
  }
}

/*************************************************************************/

/*************************************************************************/

void _w_tab::changed_normalization_slot(int State)
{
  Q_UNUSED(State)

  if (currentIndex()==int(_w_tab_ns::_tabs::ELEMENTS_TAB)){
  }
  else{
    Checkbox_elements_normalization->blockSignals(true);
    Checkbox_elements_normalization->blockSignals(false);
  }
}

/*************************************************************************/

void _w_tab::changed_position_normalization_slot(int Value)
{
  if (currentIndex()==int(_w_tab_ns::_tabs::ELEMENTS_TAB)){
  }
  else{
    Combobox_elements_position_normalization_type->blockSignals(true);
    Combobox_elements_position_normalization_type->setCurrentIndex(Value);
    Combobox_elements_position_normalization_type->blockSignals(false);
  }
}

/*************************************************************************/

void _w_tab::changed_probe_slot(int Value)
{
  if (currentIndex()==int(_w_tab_ns::_tabs::ELEMENTS_TAB)){
  }
  else{
    Combobox_elements_probe->blockSignals(true);
    Combobox_elements_probe->setCurrentIndex(Value);
    Combobox_elements_probe->blockSignals(false);
  }
}

/*************************************************************************/

void _w_tab::changed_palette_slot(int Value)
{
  if (currentIndex()==int(_w_tab_ns::_tabs::ELEMENTS_TAB)){
  }
  else{
    Combobox_elements_palette->blockSignals(true);
    Combobox_elements_palette->setCurrentIndex(Value);
    Combobox_elements_palette->blockSignals(false);
  }
}

/*************************************************************************/

void _w_tab::changed_rbf_function_slot(int Value)
{
  _new_rbf_interpolation_2d_ns::_function_type Function=_new_rbf_interpolation_2d_ns::_function_type(Value);
  if (Function==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_GAUSSIAN || Function==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_MULTIQUADRIC || Function==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_INVERSE_MULTIQUADRIC){

    Frame_elements_rbf_radius->show();
  }
  else{
    Frame_elements_rbf_radius->hide();
  }
}

/*************************************************************************/

void _w_tab::changed_triangulation_add_corners_slot(int State)
{
  Q_UNUSED(State)

  if (currentIndex()==int(_w_tab_ns::_tabs::ELEMENTS_TAB)){
  }
  else{
  }
}

/*************************************************************************/

void _w_tab::compounds_combination_update_parameters()
{
  // view name
  Window->view_name(Lineedit_compounds_combination_view_name->text().toStdString());

  // check the use_colors
//  bool Value;
//  if (Checkbox_compounds_xrd_use_color1->checkState()==Qt::Checked) Value=true;
//  else Value=false;
//  Window->use_colors(0,Value);

  // the selected palette
  Window->palette(Combobox_compounds_combination_palette->currentIndex());

  // the selected probe
  Window->probe(_layer_map_ns::Vec_value_probe[Combobox_compounds_combination_probe->currentIndex()]);

  Window->save_settings();
}

/*************************************************************************/
void _w_tab::compounds_combination_create_combination_maps_slot()
{
  std::string Name_layer;
  std::string Name_element;

  QList<QListWidgetItem *> Selected_items_compounds=Listwidget_compounds_combination->selectedItems();

  if (Selected_items_compounds.size()>0){
    //
    std::vector<std::string> Vec_names_selected_compounds;
    for (int i=0;i<Selected_items_compounds.size();i++){
      Vec_names_selected_compounds.push_back(Selected_items_compounds[i]->text().toStdString());
    }

    // data image
    Window->compounds_from_elements_selected_names(Vec_names_selected_compounds);

    // view name
    Window->view_name(Lineedit_compounds_combination_view_name->text().toStdString());

    //
    compounds_combination_update_parameters();

    // create the compound
    Window->compounds_from_elements_create_some_maps();
  }
  else{
    QMessageBox::information(Window, Window->tr("Information"),Window->tr("One compound must be selected at least"));
  }
}
/*************************************************************************/
void _w_tab::compounds_combination_create_all_individual_maps_slot()
{
  std::string Name_layer;
  std::string Name_compound;

  // view name
  Window->view_name(Lineedit_compounds_combination_view_name->text().toStdString());
//  Window->view_name(Lineedit_compounds_xrd_view_name->text().toStdString()); ?? esto es para XRD?
  //
  compounds_combination_update_parameters();

  Window->compounds_from_elements_create_all_maps();
}

/*************************************************************************/

/*************************************************************************/

/*************************************************************************/

 void _w_tab::change_state_table_layer(int Row,int Col)
 {
   Q_UNUSED(Col)

   for(unsigned int i=0; i<Window->Vec_order_of_layers_by_name.size();i++){
     Window->Map_name_to_layer[Window->Vec_order_of_layers_by_name[i]].Layer->hide();
   }
   Window->Map_name_to_layer[Window->Vec_order_of_layers_by_name[Row]].Layer->show();

   update();
 }

 //HEA
 // the destination is at the end

 void _w_tab::move_layers_backward(int Initial_pos, int Destination_pos)
 {
   Window->move_layers_backward(Initial_pos,Destination_pos);
 }

 //HEA
 // the destination is at the begin

 void _w_tab::move_layers_forward(int Initial_pos, int Destination_pos)
 {
   Window->move_layers_forward(Initial_pos,Destination_pos);
 }

/*************************************************************************/

void _w_tab::show_layer_parameters(int Row,int Col)
{
  Window->show_layer_parameters(Row,Col);
}

/*************************************************************************/

void _w_tab::add_image(_table_layers_ns::_info Info,QIcon *Icon1)
{
  QListWidgetItem *Item;
  Item=new QListWidgetItem;
  Item->setText(Info.Name);
  Item->setIcon(*Icon1);
  // Only one image so it is selected
  Listwidget_elements_images->addItem(Item);

}

/*************************************************************************/

void _w_tab::add_layer(_table_layers_ns::_info Info)
{
  Table_layers->add_row(Info,Window->selected_layer());

  // insert the control widget
  Verticalbox_layers->insertWidget(1,(QGroupBox *)(Window->Map_name_to_layer[Info.Name.toStdString()].Layer->get_link()),0,Qt::AlignTop);
}

/*************************************************************************/

void _w_tab::remove_layer(std::string Name1)
{
  QList<QListWidgetItem *> List=Listwidget_elements_images->findItems(QString::fromStdString(Name1.c_str()),Qt::MatchFixedString | Qt::MatchCaseSensitive);

  if (List.size()==1){
    delete  List[0];
  }
}

/*************************************************************************/

void _w_tab::add_element(std::string Name)
{
//  cout << "Se añade " << Name << endl;
  QListWidgetItem *Item;
  Item=new QListWidgetItem;
  Item->setText(QString::fromStdString(Name));
  Listwidget_elements->addItem(Item);
}

/*************************************************************************/

void _w_tab::remove_all_elements()
{
  QListWidgetItem *Item;

  int Num_elements=Listwidget_elements->count();
  for (int i=0;i<Num_elements;i++){
    Item=Listwidget_elements->takeItem(0);
    delete Item;
  }
}

/*************************************************************************/

void _w_tab::add_compound_combination(std::string Name)
{
  QListWidgetItem *Item;
  Item=new QListWidgetItem;
  Item->setText(QString::fromStdString(Name));
  Listwidget_compounds_combination->addItem(Item);
}

/*************************************************************************/

/*************************************************************************/

/*************************************************************************/

void _w_tab::remove_all_images()
{
  // elements
  Listwidget_elements_images->clear();
  // compounds
}

/*************************************************************************/

void _w_tab::remove_all_xrf_files()
{
  Table_valid_positions->remove_all();
}

/*************************************************************************/

/*************************************************************************/

void _w_tab::change_button_state(int Row,int Col)
{
  Window->change_button_state(Row,Col);
}

/*************************************************************************/

void _w_tab::change_button_state(int Row,int Col,bool State)
{
  Table_layers->change_button(Row,Col,State);
}

/*************************************************************************/

void _w_tab::reverse_col(int Col)
{
  Window->reverse_col(Col);
}

/*************************************************************************/
// xrf files

void _w_tab::add_active_positions(const std::vector<bool>& Vec_active_positions)
{
  Table_valid_positions->update_table(Vec_active_positions);
}

/*************************************************************************/

void _w_tab::change_active_position(int Position)
{
  Window->change_active_position(Position);
}

/*************************************************************************/

bool _w_tab::active_position(int Row)
{
  return Window->active_position(Row);
}

void _w_tab::changed_selected_positions_slot()
{
  // check that at least there is one selected position
  if (Window->num_valid_positions()>0){
    Window->xrf_recompute_data();
  }
  else{
    QMessageBox::warning(this,tr("Warning"),"There must be at least one valid position");
  }
}

/*************************************************************************/

void _w_tab::set_rbf_epsilon(int Value)
{
  Slider_elements_rbf_radius->blockSignals(true);
  Slider_elements_rbf_radius->setValue(Value);
  Slider_elements_rbf_radius->blockSignals(false);
}
