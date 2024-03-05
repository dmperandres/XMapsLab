/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "w_tab_xmapslab.h"
#include "window_xmapslab.h"
#include "palette_data.h"

/*************************************************************************/

_w_tab_xmapslab::_w_tab_xmapslab(_window_xmapslab *Window1): Window(Window1)
{
  setMinimumSize(QSize(100,300));

  // 10% of the size of the widow
  setMaximumWidth(Window->width()/10);
}

/*************************************************************************/

_w_tab_xmapslab::~_w_tab_xmapslab()
{
#ifdef DEBUG_XML
  std::cout << "Terminando w_tab" << endl;
#endif
}

/*************************************************************************/

void _w_tab_xmapslab::initialize()
{
  xrf_create_files_widget();
#ifdef XRD_ACTIVE
  xrd_create_files_widget();
#endif
  create_layers_widget();
  create_xrf_widget();
#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
  create_compounds_from_elements_widget();
#endif

#ifdef XRD_ACTIVE
  create_xrd_widget();
#endif

  int Position=0;
  addTab(Widget_valid_positions, tr("Positions"));
  Map_pos_of_tab[_w_tab_xmapslab_ns::_tabs::POSITIONS_TAB]=Position++;
  addTab(Widget_layers, tr("Layers"));
  Map_pos_of_tab[_w_tab_xmapslab_ns::_tabs::LAYERS_TAB]=Position++;
  addTab(Widget_xrf, tr("XRF"));
  Map_pos_of_tab[_w_tab_xmapslab_ns::_tabs::ELEMENTS_TAB]=Position++;
#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
  addTab(Widget_compounds_from_elements, tr("Compounds"));
  Map_pos_of_tab[_w_tab_xmapslab_ns::_tabs::COMPOUNDS_FROM_XRF_TAB]=Position++;
#endif

#ifdef XRD_ACTIVE
  addTab(Widget_xrd, tr("XRD"));
  Map_pos_of_tab[_w_tab_xmapslab_ns::_tabs::COMPOUNDS_XRD_TAB]=Position++;
#endif

  setCurrentIndex(pos_of_tab(_w_tab_xmapslab_ns::_tabs::POSITIONS_TAB));

//  create_palettes_widget();
//  addTab(Widget_palettes, tr("Palettes"));

  for (int i=0;i<int(_w_tab_xmapslab_ns::_tabs::TAB_LAST);i++){
    setTabEnabled(i,false);
  }

  setCurrentIndex(0);

  QFontMetrics Font_metric(font());
//  int Width_text = Font_metric.width("M");
  int Width_text = Font_metric.horizontalAdvance("M");

  setMinimumWidth(Width_text*_gl_widget_xmapslab_ns::WIDTH_TAB_CHARS);
  setMaximumWidth(Width_text*_gl_widget_xmapslab_ns::WIDTH_TAB_CHARS);

  connect(this,SIGNAL(tabBarClicked(int)),this,SLOT(tab_bar_clicked_slot(int)));
}

/*************************************************************************/

void _w_tab_xmapslab::create_layers_widget()
{
  Widget_layers=new QWidget;

  Verticalbox_layers=new QVBoxLayout;

  std::string Name_table0="Vec_layers";
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
  for (unsigned int i=0;i<_layer_xmapslab_ns::Vec_additional_layers.size();i++){
    Combo_add_layer->addItem(_layer_xmapslab_ns::Vec_additional_layers[i]);
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

void _w_tab_xmapslab::create_xrf_widget()
{
  Widget_xrf=new QWidget;
  Verticalbox_xrf=new QVBoxLayout;

  // Images
//  QGroupBox *Groupbox_images=new QGroupBox("Images");
//  QVBoxLayout *Verticalbox_images1=new QVBoxLayout;

//  Listwidget_xrf_images=new QListWidget;
//  Listwidget_xrf_images->setSelectionMode(QAbstractItemView::ExtendedSelection);
//  if (Window->screen_height()<=1080) Listwidget_xrf_images->setIconSize(QSize(_window_xmapslab_ns::ICON_SIZE_1080,_window_xmapslab_ns::ICON_SIZE_1080));
//  else Listwidget_xrf_images->setIconSize(QSize(_window_xmapslab_ns::ICON_SIZE_1080*2,_window_xmapslab_ns::ICON_SIZE_1080*2));

//  Verticalbox_images1->addWidget(Listwidget_xrf_images);
//  Groupbox_images->setLayout(Verticalbox_images1);

  // Elements
  QGroupBox *Groupbox_xrf=new QGroupBox("Elements");
  QVBoxLayout *Verticalbox_xrf_list=new QVBoxLayout;

  Listwidget_xrf=new QListWidget;
  Listwidget_xrf->setSelectionMode(QAbstractItemView::MultiSelection);

  Verticalbox_xrf_list->addWidget(Listwidget_xrf);
  Groupbox_xrf->setLayout(Verticalbox_xrf_list);

  // maps parameters ********
  Frame_xrf_maps_parameters=new QFrame;
  Frame_xrf_maps_parameters->setFrameStyle(QFrame::Panel);

  Grid_xrf_maps_parameters=new QGridLayout;

  //
  QLabel *Label_xrf_view_name=new QLabel("View_name");
  Lineedit_xrf_view_name=new QLineEdit(_w_tab_xmapslab_ns::VIEW_NAME_DEFAULT);
  connect(Lineedit_xrf_view_name,SIGNAL(textChanged(QString)),this,SLOT(xrf_changed_view_name_slot(QString)));
  //
  QLabel *Label_xrf_interpolation_type=new QLabel("Interpolation type");

  Combobox_xrf_interpolation_type = new QComboBox;
  for (unsigned int i=0; i<_layer_map_ns::Vec_interpolation_method_names.size();i++){
    Combobox_xrf_interpolation_type->addItem(_layer_map_ns::Vec_interpolation_method_names[i]);
  }
  Combobox_xrf_interpolation_type->setCurrentIndex(int(Window->xrf_map_interpolation_type()));
  connect(Combobox_xrf_interpolation_type,SIGNAL(activated(int)),this,SLOT(xrf_changed_interpolation_type_slot(int)));
  //
  QLabel *Label_xrf_normalization=new QLabel("Normalization");

  Checkbox_xrf_normalization=new QCheckBox;
  Checkbox_xrf_normalization->setChecked(Window->xrf_distance_normalization());
  connect(Checkbox_xrf_normalization,SIGNAL(stateChanged(int)),this,SLOT(xrf_changed_normalization_slot(int)));
  //
  QLabel *Label_xrf_normalization_homogeneous=new QLabel("Pos. normalization");

  Combobox_xrf_position_normalization_type = new QComboBox;
  for (unsigned int i=0; i<_layer_map_distance_ns::Vec_names_position_interpolation_type.size();i++){
    Combobox_xrf_position_normalization_type->addItem(_layer_map_distance_ns::Vec_names_position_interpolation_type[i]);
  }
  Combobox_xrf_position_normalization_type->setCurrentIndex(int(Window->xrf_position_normalization_type()));
  connect(Combobox_xrf_position_normalization_type,SIGNAL(activated(int)),this,SLOT(xrf_changed_position_normalization_slot(int)));
  //
  QLabel *Label_xrf_probe=new QLabel("Probe");

  Combobox_xrf_probe = new QComboBox;
  for (unsigned int i=0; i<_layer_map_ns::Vec_name_probe.size();i++){
    Combobox_xrf_probe->addItem(_layer_map_ns::Vec_name_probe[i]);
  }
  Combobox_xrf_probe->setCurrentIndex(Window->xrf_probe());
  connect(Combobox_xrf_probe,SIGNAL(activated(int)),this,SLOT(xrf_changed_probe_slot(int)));

  // Add triagulation corners
  QLabel *Label_xrf_triangulation_add_corners=new QLabel("Add corners");
  Label_xrf_triangulation_add_corners->hide();

  Checkbox_xrf_triangulation_add_corners=new QCheckBox;
  Checkbox_xrf_triangulation_add_corners->setChecked(Window->xrf_triangulation_add_corners());
  Checkbox_xrf_triangulation_add_corners->hide();

  connect(Checkbox_xrf_triangulation_add_corners,SIGNAL(stateChanged(int)),this,SLOT(xrf_changed_triangulation_add_corners_slot(int)));

  // RBF function
  QLabel *Label_xrf_rbf_function=new QLabel("Function");
  Label_xrf_rbf_function->hide();

  Combobox_xrf_rbf_function = new QComboBox;
  for (unsigned int i=0;i<_new_rbf_interpolation_2d_ns::Vec_names_function.size();i++){
    Combobox_xrf_rbf_function->addItem(QString::fromStdString(_new_rbf_interpolation_2d_ns::Vec_names_function[i]));
  }
  Combobox_xrf_rbf_function->setCurrentIndex(int(_new_rbf_interpolation_2d_ns::FUNCTION_TYPE_DEFAULT));
  Combobox_xrf_rbf_function->hide();

  connect(Combobox_xrf_rbf_function,SIGNAL(currentIndexChanged(int)),this,SLOT(xrf_changed_rbf_function_slot(int)));

  // RBF radius
  Frame_xrf_rbf_radius=new QFrame;
  Frame_xrf_rbf_radius->setFrameStyle(QFrame::Panel);
//  Frame_xrf_rbf_radius->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

  QLabel *Label_xrf_rbf_radius=new QLabel("Radius");
  QLabel *Label_xrf_rbf_radius_min=new QLabel("Min");
  QLabel *Label_xrf_rbf_radius_max=new QLabel("Max");

  Slider_xrf_rbf_radius=new QSlider(Qt::Horizontal);
  Slider_xrf_rbf_radius->setRange(1,255);
  Slider_xrf_rbf_radius->setSingleStep(1);
  Slider_xrf_rbf_radius->setPageStep(10);
  Slider_xrf_rbf_radius->setTickInterval(25);
  Slider_xrf_rbf_radius->setTickPosition(QSlider::TicksRight);
  //  Slider_xrf_rbf_radius->setToolTip(tr(String_parameter2_tooltip.c_str()));

  //  Slider_xrf_rbf_radius->setMinimumWidth(width());

  QGridLayout *Grid_xrf_rbf_radius=new QGridLayout;

  int Row=0;
  Grid_xrf_rbf_radius->addWidget(Label_xrf_rbf_radius,Row++,1,Qt::AlignCenter);
  Grid_xrf_rbf_radius->addWidget(Label_xrf_rbf_radius_min,Row,0,Qt::AlignLeft);
  Grid_xrf_rbf_radius->addWidget(Slider_xrf_rbf_radius,Row,1);
  Grid_xrf_rbf_radius->addWidget(Label_xrf_rbf_radius_max,Row,2,Qt::AlignRight);

  Frame_xrf_rbf_radius->setLayout(Grid_xrf_rbf_radius);
  Frame_xrf_rbf_radius->setMinimumWidth(350);
  Frame_xrf_rbf_radius->hide(); //initially hidden

//  QGridLayout *Grid_xrf_rbf_function=new QGridLayout;

//  Grid_xrf_rbf_function->addWidget(Label_xrf_rbf_function,0,0,Qt::AlignRight);
//  Grid_xrf_rbf_function->addWidget(Combobox_xrf_rbf_function,0,1,Qt::AlignLeft);

//  Frame_xrf_rbf_function->setLayout(Grid_xrf_rbf_function);

//  Frame_xrf_rbf_function->hide();

  //

  //
  XRF_maps_parameters_num_rows=0;
  // View 0
  Grid_xrf_maps_parameters->addWidget(Label_xrf_view_name,XRF_maps_parameters_num_rows,0,Qt::AlignRight);
  Grid_xrf_maps_parameters->addWidget(Lineedit_xrf_view_name,XRF_maps_parameters_num_rows++,1,Qt::AlignLeft);
  // interpolation type 1
  Grid_xrf_maps_parameters->addWidget(Label_xrf_interpolation_type,XRF_maps_parameters_num_rows,0,Qt::AlignRight);
  Grid_xrf_maps_parameters->addWidget(Combobox_xrf_interpolation_type,XRF_maps_parameters_num_rows++,1,Qt::AlignLeft);
  // Normalization 2
  Grid_xrf_maps_parameters->addWidget(Label_xrf_normalization,XRF_maps_parameters_num_rows,0,Qt::AlignRight);
  Grid_xrf_maps_parameters->addWidget(Checkbox_xrf_normalization,XRF_maps_parameters_num_rows++,1,Qt::AlignLeft);
  // Positions normalization 3
  Grid_xrf_maps_parameters->addWidget(Label_xrf_normalization_homogeneous,XRF_maps_parameters_num_rows,0,Qt::AlignRight);
  Grid_xrf_maps_parameters->addWidget(Combobox_xrf_position_normalization_type,XRF_maps_parameters_num_rows++,1,1,3,Qt::AlignLeft);
  // probe 4
  Grid_xrf_maps_parameters->addWidget(Label_xrf_probe,XRF_maps_parameters_num_rows,0,Qt::AlignRight);
  Grid_xrf_maps_parameters->addWidget(Combobox_xrf_probe,XRF_maps_parameters_num_rows++,1,Qt::AlignLeft);
  // add corners 5
  Grid_xrf_maps_parameters->addWidget(Label_xrf_triangulation_add_corners,XRF_maps_parameters_num_rows,0,Qt::AlignRight);
  Grid_xrf_maps_parameters->addWidget(Checkbox_xrf_triangulation_add_corners,XRF_maps_parameters_num_rows++,1,Qt::AlignLeft);
  // RBF functions 6
  Grid_xrf_maps_parameters->addWidget(Label_xrf_rbf_function,XRF_maps_parameters_num_rows,0,Qt::AlignRight);
  Grid_xrf_maps_parameters->addWidget(Combobox_xrf_rbf_function,XRF_maps_parameters_num_rows++,1,Qt::AlignLeft);
  // RBF Radius 7
  Grid_xrf_maps_parameters->addWidget(Frame_xrf_rbf_radius,XRF_maps_parameters_num_rows,0,1,2,Qt::AlignHCenter);
//  Grid_xrf_maps_parameters->addWidget(Combobox_xrf_rbf_function,XRF_maps_parameters_num_rows++,1,Qt::AlignLeft);

  Frame_xrf_maps_parameters->setLayout(Grid_xrf_maps_parameters);
  Frame_xrf_maps_parameters->hide(); // initially hidden

  Pushbutton_xrf_maps_parameters=new QPushButton("Show maps parameters");
  // Conectar el botón con el slot
  connect(Pushbutton_xrf_maps_parameters,SIGNAL(clicked(bool)),this,SLOT(xrf_button_pushed_maps_parameters_slot(bool)));

  // Palette ***********
  Frame_xrf_palette_parameters=new QFrame;
  Frame_xrf_palette_parameters->setFrameStyle(QFrame::Panel);

  Grid_xrf_palette_parameters=new QGridLayout;

  //
  QLabel *Label_xrf_palette_type=new QLabel("Palette type");

  QComboBox *Combobox_xrf_palette_type = new QComboBox;
  Combobox_xrf_palette_type->addItem("Discrete");
  Combobox_xrf_palette_type->addItem("Continous");
  Combobox_xrf_palette_type->setCurrentIndex(int(_palette_data_ns::PALETTE_TYPE_DEFAULT));
  connect(Combobox_xrf_palette_type,SIGNAL(currentIndexChanged(int)),this,SLOT(xrf_changed_palette_type_slot(int)));

  //
  QLabel *Label_xrf_palette_color_type=new QLabel("Color type");

  QComboBox *Combobox_xrf_palette_color_type = new QComboBox;
  Combobox_xrf_palette_color_type->addItem("Single tone");
  Combobox_xrf_palette_color_type->addItem("Color");
  Combobox_xrf_palette_color_type->setCurrentIndex(int(_palette_data_ns::PALETTE_COLOR_TYPE_DEFAULT));
  connect(Combobox_xrf_palette_color_type,SIGNAL(currentIndexChanged(int)),this,SLOT(xrf_changed_palette_color_type_slot(int)));

  //
  QLabel *Label_xrf_palette_num_intervals=new QLabel("Intervals");

  Spinbox_xrf_palette_num_intervals=new QSpinBox;
  if (XRF_palette_type==_palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE){
    Spinbox_xrf_palette_num_intervals->setRange(_palette_data_ns::PALETTE_DISCRETE_MINIMUM_INTERVALS,_palette_data_ns::PALETTE_DISCRETE_MAXIMUM_INTERVALS);
    Spinbox_xrf_palette_num_intervals->setValue(XRF_palette_discrete_num_intervals_value);
  }
  else{
    Spinbox_xrf_palette_num_intervals->setRange(_palette_data_ns::PALETTE_CONTINUOUS_MINIMUM_INTERVALS,_palette_data_ns::PALETTE_CONTINUOUS_MAXIMUM_INTERVALS);
    Spinbox_xrf_palette_num_intervals->setValue(XRF_palette_continuous_num_intervals_value);
  }
  connect(Spinbox_xrf_palette_num_intervals,SIGNAL(valueChanged(int)),this,SLOT(xrf_changed_num_intervals_slot(int)));

  //
  QLabel *Label_xrf_palette_color_assigning=new QLabel("Color assigning");

  QComboBox *Combobox_xrf_palette_color_assigning = new QComboBox;
  Combobox_xrf_palette_color_assigning->addItem("Mutable");
  Combobox_xrf_palette_color_assigning->addItem("Fixed");
  Combobox_xrf_palette_color_assigning->setCurrentIndex(int(_palette_data_ns::PALETTE_COLOR_ASSIGNING_DEFAULT));
  connect(Combobox_xrf_palette_color_assigning,SIGNAL(currentIndexChanged(int)),this,SLOT(xrf_changed_palette_color_assigning_slot(int)));

  //
  QLabel *Label_xrf_palette_mutable_color=new QLabel("Color");

  // colors
  _button_color_simple *Button_xrf_palette_mutable_color=new _button_color_simple(XRF_palette_mutable_color,false);
  connect(Button_xrf_palette_mutable_color,SIGNAL(colorChanged(QColor)),this,SLOT(xrf_palette_mutable_color_slot(QColor)));

  //
  QLabel *Label_xrf_palette_fixed_palettes=new QLabel("Fixed palettes");

  QComboBox *Combobox_xrf_palette_fixed_palettes = new QComboBox;
  for (const auto& Pair : Window->Map_fixed_palettes) {
    Combobox_xrf_palette_fixed_palettes->addItem(QString::fromStdString(Pair.first));
  }
  // default
  XRF_palette_name_fixed_palette=Combobox_xrf_palette_fixed_palettes->itemText(0);
  connect(Combobox_xrf_palette_fixed_palettes,SIGNAL(currentTextChanged(QString)),this,SLOT(xrf_changed_palette_fixed_palettes_slot(QString)));

  XRF_palette_parameters_num_rows=0;
  // Palette type 0
  Grid_xrf_palette_parameters->addWidget(Label_xrf_palette_type,XRF_palette_parameters_num_rows,0,Qt::AlignRight);
  Grid_xrf_palette_parameters->addWidget(Combobox_xrf_palette_type,XRF_palette_parameters_num_rows++,1,Qt::AlignLeft);
  // Palette color type 1
  Grid_xrf_palette_parameters->addWidget(Label_xrf_palette_color_type,XRF_palette_parameters_num_rows,0,Qt::AlignRight);
  Grid_xrf_palette_parameters->addWidget(Combobox_xrf_palette_color_type,XRF_palette_parameters_num_rows++,1,Qt::AlignLeft);
  // Palette num intervals 2
  Grid_xrf_palette_parameters->addWidget(Label_xrf_palette_num_intervals,XRF_palette_parameters_num_rows,0,Qt::AlignRight);
  Grid_xrf_palette_parameters->addWidget(Spinbox_xrf_palette_num_intervals,XRF_palette_parameters_num_rows++,1,Qt::AlignLeft);
  // Palette values type 3
  Grid_xrf_palette_parameters->addWidget(Label_xrf_palette_color_assigning,XRF_palette_parameters_num_rows,0,Qt::AlignRight);
  Grid_xrf_palette_parameters->addWidget(Combobox_xrf_palette_color_assigning,XRF_palette_parameters_num_rows++,1,Qt::AlignLeft);
  // Palette mutable color 4
  Grid_xrf_palette_parameters->addWidget(Label_xrf_palette_mutable_color,XRF_palette_parameters_num_rows,0,Qt::AlignRight);
  Grid_xrf_palette_parameters->addWidget(Button_xrf_palette_mutable_color,XRF_palette_parameters_num_rows++,1,Qt::AlignLeft);
  // Palette fixed palettes 5
  Grid_xrf_palette_parameters->addWidget(Label_xrf_palette_fixed_palettes,XRF_palette_parameters_num_rows,0,Qt::AlignRight);
  Grid_xrf_palette_parameters->addWidget(Combobox_xrf_palette_fixed_palettes,XRF_palette_parameters_num_rows++,1,Qt::AlignLeft);

  xrf_changed_palette_color_assigning_slot(int(XRF_palette_color_assigning));

  Frame_xrf_palette_parameters->setLayout(Grid_xrf_palette_parameters);
  Frame_xrf_palette_parameters->hide(); // initially hidden

  Pushbutton_xrf_palette_parameters=new QPushButton("Show palette parameters");
  // Conectar el botón con el slot
  connect(Pushbutton_xrf_palette_parameters,SIGNAL(clicked(bool)),this,SLOT(xrf_button_pushed_palette_parameters_slot(bool)));

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

  Button_xrf_create_some_maps= new QPushButton("Create some maps", this);
  Button_xrf_create_some_maps->setEnabled(false);
  connect(Button_xrf_create_some_maps, SIGNAL(clicked()),this,SLOT(xrf_create_some_maps_slot()));

  Button_xrf_create_all_maps= new QPushButton("Create all the maps", this);
  Button_xrf_create_all_maps->setEnabled(false);
  connect(Button_xrf_create_all_maps, SIGNAL(clicked()),this,SLOT(xrf_create_all_maps_slot()));

  Vertical_box_buttons->addWidget(Button_xrf_create_some_maps);
  Vertical_box_buttons->addWidget(Separator2);
  Vertical_box_buttons->addWidget(Button_xrf_create_all_maps);

  Group_box_buttons->setLayout(Vertical_box_buttons);

  //
//  Verticalbox_xrf->addWidget(Groupbox_images);
  Verticalbox_xrf->addWidget(Groupbox_xrf);
  Verticalbox_xrf->addWidget(Pushbutton_xrf_maps_parameters);
  Verticalbox_xrf->addWidget(Frame_xrf_maps_parameters);
  Verticalbox_xrf->addWidget(Pushbutton_xrf_palette_parameters);
  Verticalbox_xrf->addWidget(Frame_xrf_palette_parameters);
  Verticalbox_xrf->addWidget(Separator1);
  Verticalbox_xrf->addWidget(Group_box_buttons);

  Widget_xrf->setLayout(Verticalbox_xrf);
}

/*************************************************************************/
// compounds combinations

#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
void _w_tab_xmapslab::create_compounds_from_elements_widget()
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

  Lineedit_compounds_combination_view_name=new QLineEdit(_w_tab_xmapslab_ns::VIEW_NAME_DEFAULT);

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
//  Combobox_compounds_combination_palette->setCurrentIndex(Window->palette());

  Grid_element_palette->addWidget(Label_element_palette1,0,0,Qt::AlignRight);
  Grid_element_palette->addWidget(Combobox_compounds_combination_palette,0,1,Qt::AlignLeft);

  Frame_compounds_combination_palette->setLayout(Grid_element_palette);

//  connect(Combobox_compounds_combination_palette,SIGNAL(activated(int)),this,SLOT(changed_palette_slot(int)));

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
#endif

/*************************************************************************/
// compounds xrd
#ifdef XRD_ACTIVE
void _w_tab_xmapslab::create_xrd_widget()
{
  Widget_xrd=new QWidget;
  Verticalbox_xrd=new QVBoxLayout;

  // Images
//  QGroupBox *Groupbox_images=new QGroupBox("Images");
//  QVBoxLayout *Verticalbox_images1=new QVBoxLayout;

//  Listwidget_xrd_images=new QListWidget;
//  Listwidget_xrd_images->setSelectionMode(QAbstractItemView::ExtendedSelection);
//  if (Window->screen_height()<=1080) Listwidget_xrd_images->setIconSize(QSize(_window_xmapslab_ns::ICON_SIZE_1080,_window_xmapslab_ns::ICON_SIZE_1080));
//  else Listwidget_xrd_images->setIconSize(QSize(_window_xmapslab_ns::ICON_SIZE_1080*2,_window_xmapslab_ns::ICON_SIZE_1080*2));

//  Verticalbox_images1->addWidget(Listwidget_xrd_images);
//  Groupbox_images->setLayout(Verticalbox_images1);

  // Compounds
  QGroupBox *Groupbox_xrd=new QGroupBox("Pigments");
  QVBoxLayout *Verticalbox_xrd_list=new QVBoxLayout;

  Listwidget_xrd=new QListWidget;
  Listwidget_xrd->setSelectionMode(QAbstractItemView::MultiSelection);

  Verticalbox_xrd_list->addWidget(Listwidget_xrd);
  Groupbox_xrd->setLayout(Verticalbox_xrd_list);

  // maps parameters ********
  Frame_xrd_maps_parameters=new QFrame;
  Frame_xrd_maps_parameters->setFrameStyle(QFrame::Panel);

  Grid_xrd_maps_parameters=new QGridLayout;

  //
  QLabel *Label_xrd_view_name=new QLabel("View_name");
  Lineedit_xrd_view_name=new QLineEdit(_w_tab_xmapslab_ns::VIEW_NAME_DEFAULT);
  connect(Lineedit_xrd_view_name,SIGNAL(textChanged(QString)),this,SLOT(xrd_changed_view_name_slot(QString)));

  //
  QLabel *Label_xrd_interpolation_type=new QLabel("Interpolation type");

  Combobox_xrd_interpolation_type = new QComboBox;
  for (unsigned int i=0; i<_layer_map_ns::Vec_interpolation_method_names.size();i++){
    Combobox_xrd_interpolation_type->addItem(_layer_map_ns::Vec_interpolation_method_names[i]);
  }
  Combobox_xrd_interpolation_type->setCurrentIndex(int(Window->xrd_map_interpolation_type()));
  connect(Combobox_xrd_interpolation_type,SIGNAL(activated(int)),this,SLOT(xrd_changed_interpolation_type_slot(int)));

  //
  QLabel *Label_xrd_normalization=new QLabel("Normalization");

  Checkbox_xrd_normalization=new QCheckBox;
  Checkbox_xrd_normalization->setChecked(Window->xrd_distance_normalization());
  connect(Checkbox_xrd_normalization,SIGNAL(stateChanged(int)),this,SLOT(xrd_changed_normalization_slot(int)));

  //
  QLabel *Label_xrd_normalization_homogeneous=new QLabel("Pos. normalization");

  Combobox_xrd_position_normalization_type = new QComboBox;
  for (unsigned int i=0; i<_layer_map_distance_ns::Vec_names_position_interpolation_type.size();i++){
    Combobox_xrd_position_normalization_type->addItem(_layer_map_distance_ns::Vec_names_position_interpolation_type[i]);
  }
  Combobox_xrd_position_normalization_type->setCurrentIndex(int(Window->xrd_position_normalization_type()));
  connect(Combobox_xrd_position_normalization_type,SIGNAL(activated(int)),this,SLOT(xrd_changed_position_normalization_slot(int)));

  //
  QLabel *Label_xrd_probe=new QLabel("Probe");

  Combobox_xrd_probe = new QComboBox;
  for (unsigned int i=0; i<_layer_map_ns::Vec_name_probe.size();i++){
    Combobox_xrd_probe->addItem(_layer_map_ns::Vec_name_probe[i]);
  }
  Combobox_xrd_probe->setCurrentIndex(Window->xrd_probe());
  connect(Combobox_xrd_probe,SIGNAL(activated(int)),this,SLOT(xrd_changed_probe_slot(int)));

  // Add triagulation corners
  QLabel *Label_xrd_triangulation_add_corners=new QLabel("Add corners");
  Label_xrd_triangulation_add_corners->hide();

  Checkbox_xrd_triangulation_add_corners=new QCheckBox;
  Checkbox_xrd_triangulation_add_corners->setChecked(Window->xrd_triangulation_add_corners());
  Checkbox_xrd_triangulation_add_corners->hide();

  connect(Checkbox_xrd_triangulation_add_corners,SIGNAL(stateChanged(int)),this,SLOT(xrd_changed_triangulation_add_corners_slot(int)));

  // RBF function
  QLabel *Label_xrd_rbf_function=new QLabel("Function");
  Label_xrd_rbf_function->hide();

  Combobox_xrd_rbf_function = new QComboBox;
  for (unsigned int i=0;i<_new_rbf_interpolation_2d_ns::Vec_names_function.size();i++){
    Combobox_xrd_rbf_function->addItem(QString::fromStdString(_new_rbf_interpolation_2d_ns::Vec_names_function[i]));
  }
  Combobox_xrd_rbf_function->setCurrentIndex(int(_new_rbf_interpolation_2d_ns::FUNCTION_TYPE_DEFAULT));
  Combobox_xrd_rbf_function->hide();

  connect(Combobox_xrd_rbf_function,SIGNAL(currentIndexChanged(int)),this,SLOT(xrd_changed_rbf_function_slot(int)));

  // RBF radius
  Frame_xrd_rbf_radius=new QFrame;
  Frame_xrd_rbf_radius->setFrameStyle(QFrame::Panel);
  //  Frame_xrd_rbf_radius->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

  QLabel *Label_xrd_rbf_radius=new QLabel("Radius");
  QLabel *Label_xrd_rbf_radius_min=new QLabel("Min");
  QLabel *Label_xrd_rbf_radius_max=new QLabel("Max");

  Slider_xrd_rbf_radius=new QSlider(Qt::Horizontal);
  Slider_xrd_rbf_radius->setRange(1,255);
  Slider_xrd_rbf_radius->setSingleStep(1);
  Slider_xrd_rbf_radius->setPageStep(10);
  Slider_xrd_rbf_radius->setTickInterval(25);
  Slider_xrd_rbf_radius->setTickPosition(QSlider::TicksRight);
  //  Slider_xrd_rbf_radius->setToolTip(tr(String_parameter2_tooltip.c_str()));

  //  Slider_xrd_rbf_radius->setMinimumWidth(width());

  QGridLayout *Grid_xrd_rbf_radius=new QGridLayout;

  int Row=0;
  Grid_xrd_rbf_radius->addWidget(Label_xrd_rbf_radius,Row++,1,Qt::AlignCenter);
  Grid_xrd_rbf_radius->addWidget(Label_xrd_rbf_radius_min,Row,0,Qt::AlignLeft);
  Grid_xrd_rbf_radius->addWidget(Slider_xrd_rbf_radius,Row,1);
  Grid_xrd_rbf_radius->addWidget(Label_xrd_rbf_radius_max,Row,2,Qt::AlignRight);

  Frame_xrd_rbf_radius->setLayout(Grid_xrd_rbf_radius);
  Frame_xrd_rbf_radius->setMinimumWidth(350);
  Frame_xrd_rbf_radius->hide(); //initially hidden

  //  QGridLayout *Grid_xrd_rbf_function=new QGridLayout;

  //  Grid_xrd_rbf_function->addWidget(Label_xrd_rbf_function,0,0,Qt::AlignRight);
  //  Grid_xrd_rbf_function->addWidget(Combobox_xrd_rbf_function,0,1,Qt::AlignLeft);

  //  Frame_xrd_rbf_function->setLayout(Grid_xrd_rbf_function);

  //  Frame_xrd_rbf_function->hide();

  //

  //
  XRF_maps_parameters_num_rows=0;
  // View 0
  Grid_xrd_maps_parameters->addWidget(Label_xrd_view_name,XRF_maps_parameters_num_rows,0,Qt::AlignRight);
  Grid_xrd_maps_parameters->addWidget(Lineedit_xrd_view_name,XRF_maps_parameters_num_rows++,1,Qt::AlignLeft);
  // interpolation type 1
  Grid_xrd_maps_parameters->addWidget(Label_xrd_interpolation_type,XRF_maps_parameters_num_rows,0,Qt::AlignRight);
  Grid_xrd_maps_parameters->addWidget(Combobox_xrd_interpolation_type,XRF_maps_parameters_num_rows++,1,Qt::AlignLeft);
  // Normalization 2
  Grid_xrd_maps_parameters->addWidget(Label_xrd_normalization,XRF_maps_parameters_num_rows,0,Qt::AlignRight);
  Grid_xrd_maps_parameters->addWidget(Checkbox_xrd_normalization,XRF_maps_parameters_num_rows++,1,Qt::AlignLeft);
  // Positions normalization 3
  Grid_xrd_maps_parameters->addWidget(Label_xrd_normalization_homogeneous,XRF_maps_parameters_num_rows,0,Qt::AlignRight);
  Grid_xrd_maps_parameters->addWidget(Combobox_xrd_position_normalization_type,XRF_maps_parameters_num_rows++,1,1,3,Qt::AlignLeft);
  // probe 4
  Grid_xrd_maps_parameters->addWidget(Label_xrd_probe,XRF_maps_parameters_num_rows,0,Qt::AlignRight);
  Grid_xrd_maps_parameters->addWidget(Combobox_xrd_probe,XRF_maps_parameters_num_rows++,1,Qt::AlignLeft);
  // add corners 5
  Grid_xrd_maps_parameters->addWidget(Label_xrd_triangulation_add_corners,XRF_maps_parameters_num_rows,0,Qt::AlignRight);
  Grid_xrd_maps_parameters->addWidget(Checkbox_xrd_triangulation_add_corners,XRF_maps_parameters_num_rows++,1,Qt::AlignLeft);
  // RBF functions 6
  Grid_xrd_maps_parameters->addWidget(Label_xrd_rbf_function,XRF_maps_parameters_num_rows,0,Qt::AlignRight);
  Grid_xrd_maps_parameters->addWidget(Combobox_xrd_rbf_function,XRF_maps_parameters_num_rows++,1,Qt::AlignLeft);
  // RBF Radius 7
  Grid_xrd_maps_parameters->addWidget(Frame_xrd_rbf_radius,XRF_maps_parameters_num_rows,0,1,2,Qt::AlignHCenter);
  //  Grid_xrd_maps_parameters->addWidget(Combobox_xrd_rbf_function,XRF_maps_parameters_num_rows++,1,Qt::AlignLeft);

  Frame_xrd_maps_parameters->setLayout(Grid_xrd_maps_parameters);
  Frame_xrd_maps_parameters->hide(); // initially hidden

  Pushbutton_xrd_maps_parameters=new QPushButton("Show maps parameters");
  // Conectar el botón con el slot
  connect(Pushbutton_xrd_maps_parameters,SIGNAL(clicked(bool)),this,SLOT(xrd_button_pushed_maps_parameters_slot(bool)));

  // Palette ***********
  Frame_xrd_palette_parameters=new QFrame;
  Frame_xrd_palette_parameters->setFrameStyle(QFrame::Panel);

  Grid_xrd_palette_parameters=new QGridLayout;

  //
  QLabel *Label_xrd_palette_type=new QLabel("Palette type");

  QComboBox *Combobox_xrd_palette_type = new QComboBox;
  Combobox_xrd_palette_type->addItem("Discrete");
  Combobox_xrd_palette_type->addItem("Continous");
  Combobox_xrd_palette_type->setCurrentIndex(int(_palette_data_ns::PALETTE_TYPE_DEFAULT));
  connect(Combobox_xrd_palette_type,SIGNAL(currentIndexChanged(int)),this,SLOT(xrd_changed_palette_type_slot(int)));

  //
  QLabel *Label_xrd_palette_color_type=new QLabel("Color type");

  QComboBox *Combobox_xrd_palette_color_type = new QComboBox;
  Combobox_xrd_palette_color_type->addItem("Single tone");
  Combobox_xrd_palette_color_type->addItem("Color");
  Combobox_xrd_palette_color_type->setCurrentIndex(int(_palette_data_ns::PALETTE_COLOR_TYPE_DEFAULT));
  connect(Combobox_xrd_palette_color_type,SIGNAL(currentIndexChanged(int)),this,SLOT(xrd_changed_palette_color_type_slot(int)));

  //
  QLabel *Label_xrd_palette_num_intervals=new QLabel("Intervals");

  Spinbox_xrd_palette_num_intervals=new QSpinBox;
  if (XRD_palette_type==_palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE){
    Spinbox_xrd_palette_num_intervals->setRange(_palette_data_ns::PALETTE_DISCRETE_MINIMUM_INTERVALS,_palette_data_ns::PALETTE_DISCRETE_MAXIMUM_INTERVALS);
    Spinbox_xrd_palette_num_intervals->setValue(XRD_palette_discrete_num_intervals_value);
  }
  else{
    Spinbox_xrd_palette_num_intervals->setRange(_palette_data_ns::PALETTE_CONTINUOUS_MINIMUM_INTERVALS,_palette_data_ns::PALETTE_CONTINUOUS_MAXIMUM_INTERVALS);
    Spinbox_xrd_palette_num_intervals->setValue(XRD_palette_continuous_num_intervals_value);
  }
  connect(Spinbox_xrd_palette_num_intervals,SIGNAL(valueChanged(int)),this,SLOT(xrd_changed_num_intervals_slot(int)));

  //
  QLabel *Label_xrd_palette_color_assigning=new QLabel("Color assigning");

  QComboBox *Combobox_xrd_palette_color_assigning = new QComboBox;
  Combobox_xrd_palette_color_assigning->addItem("Mutable");
  Combobox_xrd_palette_color_assigning->addItem("Fixed");
  Combobox_xrd_palette_color_assigning->setCurrentIndex(int(_palette_data_ns::PALETTE_COLOR_ASSIGNING_DEFAULT));
  connect(Combobox_xrd_palette_color_assigning,SIGNAL(currentIndexChanged(int)),this,SLOT(xrd_changed_palette_color_assigning_slot(int)));

  //
  QLabel *Label_xrd_palette_mutable_color=new QLabel("Color");

  // colors
  _button_color_simple *Button_xrd_palette_mutable_color=new _button_color_simple(XRD_palette_mutable_color,false);
  connect(Button_xrd_palette_mutable_color,SIGNAL(colorChanged(QColor)),this,SLOT(xrd_palette_mutable_color_slot(QColor)));

  //
  QLabel *Label_xrd_palette_fixed_palettes=new QLabel("Fixed palettes");

  QComboBox *Combobox_xrd_palette_fixed_palettes = new QComboBox;
  for (const auto& Pair : Window->Map_fixed_palettes) {
    Combobox_xrd_palette_fixed_palettes->addItem(QString::fromStdString(Pair.first));
  }
  // default
  XRD_palette_name_fixed_palette=Combobox_xrd_palette_fixed_palettes->itemText(0);
  connect(Combobox_xrd_palette_fixed_palettes,SIGNAL(currentTextChanged(QString)),this,SLOT(xrd_changed_palette_fixed_palettes_slot(QString)));

  XRD_palette_parameters_num_rows=0;
  // Palette type 0
  Grid_xrd_palette_parameters->addWidget(Label_xrd_palette_type,XRD_palette_parameters_num_rows,0,Qt::AlignRight);
  Grid_xrd_palette_parameters->addWidget(Combobox_xrd_palette_type,XRD_palette_parameters_num_rows++,1,Qt::AlignLeft);
  // Palette color type 1
  Grid_xrd_palette_parameters->addWidget(Label_xrd_palette_color_type,XRD_palette_parameters_num_rows,0,Qt::AlignRight);
  Grid_xrd_palette_parameters->addWidget(Combobox_xrd_palette_color_type,XRD_palette_parameters_num_rows++,1,Qt::AlignLeft);
  // Palette num intervals 2
  Grid_xrd_palette_parameters->addWidget(Label_xrd_palette_num_intervals,XRD_palette_parameters_num_rows,0,Qt::AlignRight);
  Grid_xrd_palette_parameters->addWidget(Spinbox_xrd_palette_num_intervals,XRD_palette_parameters_num_rows++,1,Qt::AlignLeft);
  // Palette values type 3
  Grid_xrd_palette_parameters->addWidget(Label_xrd_palette_color_assigning,XRD_palette_parameters_num_rows,0,Qt::AlignRight);
  Grid_xrd_palette_parameters->addWidget(Combobox_xrd_palette_color_assigning,XRD_palette_parameters_num_rows++,1,Qt::AlignLeft);
  // Palette mutable color 4
  Grid_xrd_palette_parameters->addWidget(Label_xrd_palette_mutable_color,XRD_palette_parameters_num_rows,0,Qt::AlignRight);
  Grid_xrd_palette_parameters->addWidget(Button_xrd_palette_mutable_color,XRD_palette_parameters_num_rows++,1,Qt::AlignLeft);
  // Palette fixed palettes 5
  Grid_xrd_palette_parameters->addWidget(Label_xrd_palette_fixed_palettes,XRD_palette_parameters_num_rows,0,Qt::AlignRight);
  Grid_xrd_palette_parameters->addWidget(Combobox_xrd_palette_fixed_palettes,XRD_palette_parameters_num_rows++,1,Qt::AlignLeft);

  xrd_changed_palette_color_assigning_slot(int(XRD_palette_color_assigning));

  Frame_xrd_palette_parameters->setLayout(Grid_xrd_palette_parameters);
  Frame_xrd_palette_parameters->hide(); // initially hidden

  Pushbutton_xrd_palette_parameters=new QPushButton("Show palette parameters");
  // Conectar el botón con el slot
  connect(Pushbutton_xrd_palette_parameters,SIGNAL(clicked(bool)),this,SLOT(xrd_button_pushed_palette_parameters_slot(bool)));

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

  Button_xrd_create_some_maps= new QPushButton("Create some maps", this);
  Button_xrd_create_some_maps->setEnabled(false);
  connect(Button_xrd_create_some_maps, SIGNAL(clicked()),this,SLOT(xrd_create_some_maps_slot()));

  Button_xrd_create_all_maps= new QPushButton("Create all the maps", this);
  Button_xrd_create_all_maps->setEnabled(false);
  connect(Button_xrd_create_all_maps, SIGNAL(clicked()),this,SLOT(xrd_create_all_maps_slot()));

  Vertical_box_buttons->addWidget(Button_xrd_create_some_maps);
  Vertical_box_buttons->addWidget(Separator2);
  Vertical_box_buttons->addWidget(Button_xrd_create_all_maps);

  Group_box_buttons->setLayout(Vertical_box_buttons);

  //
//  Verticalbox_xrd->addWidget(Groupbox_images);
  Verticalbox_xrd->addWidget(Groupbox_xrd);
  Verticalbox_xrd->addWidget(Pushbutton_xrd_maps_parameters);
  Verticalbox_xrd->addWidget(Frame_xrd_maps_parameters);
  Verticalbox_xrd->addWidget(Pushbutton_xrd_palette_parameters);
  Verticalbox_xrd->addWidget(Frame_xrd_palette_parameters);
  Verticalbox_xrd->addWidget(Separator1);
  Verticalbox_xrd->addWidget(Group_box_buttons);

  Widget_xrd->setLayout(Verticalbox_xrd);
}
#endif

/*************************************************************************/

void _w_tab_xmapslab::create_palettes_widget()
{
  Widget_palettes=new QWidget;
  Verticalbox_palettes=new QVBoxLayout;

  // read icons  VALGRIND
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
    if (Window->Vec_palette_data[i].type()==_palette_data_ns::_palette_type::PALETTE_TYPE_CONTINUOUS) Item->setIcon(Icon_continuous);
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

void _w_tab_xmapslab::xrf_create_files_widget()
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

#ifdef XRD_ACTIVE
void _w_tab_xmapslab::xrd_create_files_widget()
{
}
#endif

/*************************************************************************/

void _w_tab_xmapslab::tab_bar_clicked_slot(int Tab1)
{
  Window->selected_tab(static_cast<_w_tab_xmapslab_ns::_tabs>(Tab1));

  Window->update_color_bar();
}

/*************************************************************************/

void _w_tab_xmapslab::add_filter_layer_slot(int Value)
{
//  Combo_add_layer->setCurrentIndex(0);

  switch (Value){
  case int(_layer_xmapslab_ns::_additional_layer::ADDITIONAL_LAYER_NOTHING):break;
#ifdef YES_LAYERS_EDGES_CANNY
  case int(_layer_xmapslab_ns::_additional_layer::ADDITIONAL_LAYER_CANNY):Window->add_layer_filter(_layer_xmapslab_ns::_layer_type::LAYER_TYPE_CANNY);break;
#endif
#ifdef YES_LAYERS_EDGES_DOG
  case int(_layer_xmapslab_ns::_additional_layer::ADDITIONAL_LAYER_DOG):Window->add_layer_filter(_layer_xmapslab_ns::_layer_type::LAYER_TYPE_DOG);break;
#endif
#ifdef YES_LAYERS_EDGES_KANG
  case int(_layer_xmapslab_ns::_additional_layer::ADDITIONAL_LAYER_KANG):Window->add_layer_filter(_layer_xmapslab_ns::_layer_type::LAYER_TYPE_KANG);break;
#endif
#ifdef YES_LAYERS_EDGES_KMEANS
  case int(_layer_xmapslab_ns::_additional_layer::ADDITIONAL_LAYER_KMEANS):Window->add_layer_filter(_layer_xmapslab_ns::_layer_type::LAYER_TYPE_KMEANS);break;
#endif
  }
}

/*************************************************************************/

void _w_tab_xmapslab::remove_layer_from_layout(std::string Name)
{
  Verticalbox_layers->removeWidget(static_cast<QWidget *>(Window->Map_name_to_layer[Name].Layer->get_link()));
  static_cast<QWidget *>(Window->Map_name_to_layer[Name].Layer->get_link())->setParent(0);
  static_cast<QWidget *>(Window->Map_name_to_layer[Name].Layer->get_link())->deleteLater();
}

/*************************************************************************/

void _w_tab_xmapslab::remove_selected_layer_slot()
{
  Window->remove_pigment_layer();
}

/*************************************************************************/

void _w_tab_xmapslab::remove_all_layers_slot()
{
  Window->remove_all_pigment_layers();
}

/*************************************************************************/

void _w_tab_xmapslab::change_row_visibility(QGridLayout *Layout, int Row, bool Show)
{
  for (int i = 0; i < Layout->columnCount(); ++i) {
    QLayoutItem *item = Layout->itemAtPosition(Row, i);
    if (item != nullptr) {
      QWidget *Widget = item->widget();
      if (Widget != nullptr) {
        if (Show==true) Widget->show();
        else Widget->hide();
      }
    }
  }
  // Opcionalmente, puedes actualizar el layout
  //  Layout->update();
}

/*************************************************************************/

void _w_tab_xmapslab::xrf_update_parameters()
{
  bool Value;
  // view name
  Window->xrf_view_name(Lineedit_xrf_view_name->text().toStdString());

  // interpolation type
  Window->xrf_map_interpolation_type(static_cast<_layer_map_ns::_map_interpolation_methods>(Combobox_xrf_interpolation_type->currentIndex()));

#ifdef ADVANCED
  // the color model
  Window->color_model(static_cast<_common_ns::_color_model>(Combobox_xrf_color_model->currentIndex()));

  // check the use_colors
  if (Checkbox_xrf_use_color1->checkState()==Qt::Checked) Value=true;
  else Value=false;
  Window->use_colors(0,Value);

  if (Checkbox_xrf_use_color2->checkState()==Qt::Checked) Value=true;
  else Value=false;
  Window->use_colors(1,Value);

  if (Checkbox_xrf_use_color3->checkState()==Qt::Checked) Value=true;
  else Value=0;
  Window->use_colors(2,Value);

  // the use_positions
  if (Checkbox_xrf_use_position1->checkState()==Qt::Checked) Value=true;
  else Value=false;
  Window->use_positions(0,true);

  if (Checkbox_xrf_use_position2->checkState()==Qt::Checked) Value=true;
  else Value=false;
  Window->use_positions(1,Value);
#else
  switch (Window->xrf_map_interpolation_type()) {
  case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_HYPERCUBE_DISTANCE:
     Window->xrf_use_colors(0,true);
     Window->xrf_use_colors(1,true);
     Window->xrf_use_colors(2,true);
     Window->xrf_use_positions(0,true);
     Window->xrf_use_positions(1,true);
    break;
  case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_2D_CARTESIAN_DISTANCE:
    Window->xrf_use_colors(0,false);
    Window->xrf_use_colors(1,false);
    Window->xrf_use_colors(2,false);
    Window->xrf_use_positions(0,true);
    Window->xrf_use_positions(1,true);
    break;
  default:
    break;
  }
#endif

  // normalization
  if (Checkbox_xrf_normalization->checkState()==Qt::Checked) Value=true;
  else Value=false;
  Window->xrf_distance_normalization(Value);

  // the position normalization
  Window->xrf_position_normalization_type(static_cast<_layer_map_distance_ns::_position_normalization_type>(Combobox_xrf_position_normalization_type->currentIndex()));

  // the selected palette
  _palette_data_ns::_palette Palette={XRF_palette_type, XRF_palette_color_type, 0, XRF_palette_color_assigning, XRF_palette_mutable_color, XRF_palette_name_fixed_palette.toStdString()};
  if (XRF_palette_type==_palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE) Palette.Num_stops=XRF_palette_discrete_num_intervals_value+1;
  else Palette.Num_stops=XRF_palette_continuous_num_intervals_value+1;
  Window->xrf_palette(Palette);

  // the selected probe
  Window->xrf_probe(_layer_map_ns::Vec_value_probe[Combobox_xrf_probe->currentIndex()]);

  // add corners
  if (Checkbox_xrf_triangulation_add_corners->checkState()==Qt::Checked) Value=true;
  else Value=false;
  Window->xrf_triangulation_add_corners(Value);

  // RBF_radius
  float Radius_value=float(Slider_xrf_rbf_radius->value())*Window->mean_distance_between_neighbors_positions()/255.0f;
  Radius_value=Radius_value/Window->image_diagonal_size();
  Window->xrf_rbf_radius(Radius_value);

  // RBF_function
  Window->xrf_rbf_function(_new_rbf_interpolation_2d_ns::_function_type(Combobox_xrf_rbf_function->currentIndex()));

  Window->save_settings();
}

/*************************************************************************/

void _w_tab_xmapslab::xrf_create_some_maps_slot()
{
//  std::string Name_layer;
//  std::string Name_element;

  QList<QListWidgetItem *> Selected_items_elements=Listwidget_xrf->selectedItems();

  if (Selected_items_elements.size()>0){
    // color image
    Window->name_selected_image(Window->image_layer_name());

    //
    std::vector<std::string> Vec_selected_names;
    for (int i=0;i<Selected_items_elements.size();i++){
      Vec_selected_names.push_back(Selected_items_elements[i]->text().toStdString());
    }

    // data image
    Window->xrf_selected_names(Vec_selected_names);

    // view name
    // check that the _ are converted to -
    Window->xrf_view_name(Lineedit_xrf_view_name->text().replace('_','-').toStdString());

    //
    xrf_update_parameters();

    // create the element
    Window->xrf_create_some_maps();
  }
  else{
    QMessageBox::information(Window, Window->tr("Information"),Window->tr("One element must be selected at least"));
  }
}

/*************************************************************************/

void _w_tab_xmapslab::xrf_create_all_maps_slot()
{
//  std::string Name_layer;
//  std::string Name_element;

  // color image
  Window->name_selected_image(Window->image_layer_name());

  // view name
  Window->xrf_view_name(Lineedit_xrf_view_name->text().toStdString());

  //
  xrf_update_parameters();

  Window->xrf_create_all_maps();
}

/*************************************************************************/

void _w_tab_xmapslab::xrf_changed_view_name_slot(QString Text)
{
  Lineedit_xrf_view_name->blockSignals(true);
  Lineedit_xrf_view_name->setText(Text);
  Lineedit_xrf_view_name->blockSignals(false);
}

/*************************************************************************/

void _w_tab_xmapslab::xrf_button_pushed_maps_parameters_slot(bool State)
{
  Q_UNUSED(State)
  XRF_show_maps_parameters=!XRF_show_maps_parameters;
  if (XRF_show_maps_parameters==true){
    Pushbutton_xrf_maps_parameters->setText("Hide maps parameters");
    Frame_xrf_maps_parameters->show();
  }
  else{
    Pushbutton_xrf_maps_parameters->setText("Show maps parameters");
    Frame_xrf_maps_parameters->hide();
  }

  xrf_changed_interpolation_type_slot(int(Window->xrf_map_interpolation_type()));
}

/*************************************************************************/

void _w_tab_xmapslab::xrf_button_pushed_palette_parameters_slot(bool State)
{
  Q_UNUSED(State)
  XRF_show_palette_parameters=!XRF_show_palette_parameters;
  if (XRF_show_palette_parameters==true){
    Pushbutton_xrf_palette_parameters->setText("Hide palette parameters");
    Frame_xrf_palette_parameters->show();

    for (unsigned int i=0;i<4;i++){
      change_row_visibility(Grid_xrf_palette_parameters,i,true);
    }
    if (XRF_palette_color_assigning==_palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_MUTABLE){
      change_row_visibility(Grid_xrf_palette_parameters,4,false);
      change_row_visibility(Grid_xrf_palette_parameters,5,false);
    }
    else{
      if (XRF_palette_color_type==_palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE){
        change_row_visibility(Grid_xrf_palette_parameters,4,true);
        change_row_visibility(Grid_xrf_palette_parameters,5,false);
      }
      else{
        change_row_visibility(Grid_xrf_palette_parameters,4,false);
        change_row_visibility(Grid_xrf_palette_parameters,5,true);
      }
    }
  }
  else{
    Pushbutton_xrf_palette_parameters->setText("Show palette parameters");
    Frame_xrf_palette_parameters->hide();

    for (int i=0;i<XRF_palette_parameters_num_rows;i++){
      change_row_visibility(Grid_xrf_palette_parameters,i,false);
    }
  }
}

/*************************************************************************/

void _w_tab_xmapslab::xrf_changed_palette_type_slot(int Index)
{
  XRF_palette_type=_palette_data_ns::_palette_type(Index);
  if (XRF_palette_type==_palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE){
    Spinbox_xrf_palette_num_intervals->setRange(_palette_data_ns::PALETTE_DISCRETE_MINIMUM_INTERVALS,_palette_data_ns::PALETTE_DISCRETE_MAXIMUM_INTERVALS);

    Spinbox_xrf_palette_num_intervals->blockSignals(true);
    Spinbox_xrf_palette_num_intervals->setValue(XRF_palette_discrete_num_intervals_value);
    Spinbox_xrf_palette_num_intervals->blockSignals(false);
  }
  else{
    Spinbox_xrf_palette_num_intervals->setRange(_palette_data_ns::PALETTE_CONTINUOUS_MINIMUM_INTERVALS,_palette_data_ns::PALETTE_CONTINUOUS_MAXIMUM_INTERVALS);

    Spinbox_xrf_palette_num_intervals->blockSignals(true);
    Spinbox_xrf_palette_num_intervals->setValue(XRF_palette_continuous_num_intervals_value);
    Spinbox_xrf_palette_num_intervals->blockSignals(false);
  }
}

/*************************************************************************/

void _w_tab_xmapslab::xrf_changed_palette_color_type_slot(int Index)
{
  XRF_palette_color_type=_palette_data_ns::_palette_color_type(Index);
  if (XRF_palette_color_type==_palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE){
    if (XRF_palette_color_assigning==_palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_FIXED){
      change_row_visibility(Grid_xrf_palette_parameters,4,true);
      change_row_visibility(Grid_xrf_palette_parameters,5,false);
    }
    else{
      change_row_visibility(Grid_xrf_palette_parameters,4,false);
      change_row_visibility(Grid_xrf_palette_parameters,5,false);
    }
  }
  else{ // color
    if (XRF_palette_color_assigning==_palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_FIXED){
      change_row_visibility(Grid_xrf_palette_parameters,4,false);
      change_row_visibility(Grid_xrf_palette_parameters,5,true);
    }
    else{
      change_row_visibility(Grid_xrf_palette_parameters,4,false);
      change_row_visibility(Grid_xrf_palette_parameters,5,false);
    }
  }
}

/*************************************************************************/

void _w_tab_xmapslab::xrf_changed_num_intervals_slot(int Value)
{
  if (XRF_palette_type==_palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE){
    XRF_palette_discrete_num_intervals_value=Value;
  }
  else{
    XRF_palette_continuous_num_intervals_value=Value;
  }
}

/*************************************************************************/

void _w_tab_xmapslab::xrf_changed_palette_color_assigning_slot(int Index)
{
  XRF_palette_color_assigning=_palette_data_ns::_palette_color_assigning_type(Index);
  if (XRF_palette_color_assigning==_palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_MUTABLE){
    change_row_visibility(Grid_xrf_palette_parameters,4,false);
    change_row_visibility(Grid_xrf_palette_parameters,5,false);
  }
  else{
    if (XRF_palette_color_type==_palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE){
      change_row_visibility(Grid_xrf_palette_parameters,4,true);
      change_row_visibility(Grid_xrf_palette_parameters,5,false);
    }
    else{
      change_row_visibility(Grid_xrf_palette_parameters,4,false);
      change_row_visibility(Grid_xrf_palette_parameters,5,true);
    }
  }

  Grid_xrf_palette_parameters->update();
}

/*************************************************************************/

void _w_tab_xmapslab::xrf_palette_mutable_color_slot(QColor Color)
{
  XRF_palette_mutable_color=Color;
}

/*************************************************************************/

void _w_tab_xmapslab::xrf_changed_palette_fixed_palettes_slot(QString Name)
{
  XRF_palette_name_fixed_palette=Name;
}

/*************************************************************************/

void _w_tab_xmapslab::xrf_changed_interpolation_type_slot(int Value)
{
  if (XRF_show_maps_parameters==false){
    for (unsigned int i=0;i<XRF_maps_parameters_num_rows;i++){
      change_row_visibility(Grid_xrf_maps_parameters,i,false);
    }
  }
  else{

    switch(static_cast<_layer_map_ns::_map_interpolation_methods>(Value)){
      case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_HYPERCUBE_DISTANCE:
      case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_2D_CARTESIAN_DISTANCE:
        // View 0
        change_row_visibility(Grid_xrf_maps_parameters,0,true);
        // interpolation type 1
        change_row_visibility(Grid_xrf_maps_parameters,1,true);
        // Normalization 2
        change_row_visibility(Grid_xrf_maps_parameters,2,true);
        // Positions normalization 3
        change_row_visibility(Grid_xrf_maps_parameters,3,true);
        // Probe 4
        change_row_visibility(Grid_xrf_maps_parameters,4,true);
        // add corners 5
        change_row_visibility(Grid_xrf_maps_parameters,5,false);
        // RBF functions 6
        change_row_visibility(Grid_xrf_maps_parameters,6,false);
        // RBF radius 7
        change_row_visibility(Grid_xrf_maps_parameters,7,false);
      break;
      case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_RBF:
        // View 0
        change_row_visibility(Grid_xrf_maps_parameters,0,true);
        // interpolation type 1
        change_row_visibility(Grid_xrf_maps_parameters,1,true);
        // Normalization 2
        change_row_visibility(Grid_xrf_maps_parameters,2,false);
        // Positions normalization 3
        change_row_visibility(Grid_xrf_maps_parameters,3,false);
        // Probe 4
        change_row_visibility(Grid_xrf_maps_parameters,4,false);
        // add corners 5
        change_row_visibility(Grid_xrf_maps_parameters,5,false);
        // RBF functions 6
        change_row_visibility(Grid_xrf_maps_parameters,6,true);

        // the radius is only for some functions
        if (Window->xrf_rbf_function()==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_GAUSSIAN || Window->xrf_rbf_function()==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_MULTIQUADRIC || Window->xrf_rbf_function()==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_INVERSE_MULTIQUADRIC){

          // RBF radius 7
          change_row_visibility(Grid_xrf_maps_parameters,7,true);
        }
        else{
          // RBF radius 7
          change_row_visibility(Grid_xrf_maps_parameters,7,false);
        }
      break;
      case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_TRIANGULATION:
        // View 0
        change_row_visibility(Grid_xrf_maps_parameters,0,true);
        // interpolation type 1
        change_row_visibility(Grid_xrf_maps_parameters,1,true);
        // Normalization 2
        change_row_visibility(Grid_xrf_maps_parameters,2,false);
        // Positions normalization 3
        change_row_visibility(Grid_xrf_maps_parameters,3,false);
        // Probe 4
        change_row_visibility(Grid_xrf_maps_parameters,4,false);
        // add corners 5
        change_row_visibility(Grid_xrf_maps_parameters,5,true);
        // RBF functions 6
        change_row_visibility(Grid_xrf_maps_parameters,6,false);
        // RBF radius 7
        change_row_visibility(Grid_xrf_maps_parameters,7,false);
      break;
    }
  }

  Combobox_xrf_interpolation_type->blockSignals(true);
  Combobox_xrf_interpolation_type->setCurrentIndex(Value);
  Combobox_xrf_interpolation_type->blockSignals(false);
}

//XRD************
/*************************************************************************/

void _w_tab_xmapslab::xrd_update_parameters()
{
  bool Value;
  // view name
  Window->xrd_view_name(Lineedit_xrd_view_name->text().toStdString());

  // interpolation type
  Window->xrd_map_interpolation_type(static_cast<_layer_map_ns::_map_interpolation_methods>(Combobox_xrd_interpolation_type->currentIndex()));

#ifdef ADVANCED
  // the color model
  Window->color_model(static_cast<_common_ns::_color_model>(Combobox_xrd_color_model->currentIndex()));

  // check the use_colors
  if (Checkbox_xrd_use_color1->checkState()==Qt::Checked) Value=true;
  else Value=false;
  Window->use_colors(0,Value);

  if (Checkbox_xrd_use_color2->checkState()==Qt::Checked) Value=true;
  else Value=false;
  Window->use_colors(1,Value);

  if (Checkbox_xrd_use_color3->checkState()==Qt::Checked) Value=true;
  else Value=0;
  Window->use_colors(2,Value);

  // the use_positions
  if (Checkbox_xrd_use_position1->checkState()==Qt::Checked) Value=true;
  else Value=false;
  Window->use_positions(0,true);

  if (Checkbox_xrd_use_position2->checkState()==Qt::Checked) Value=true;
  else Value=false;
  Window->use_positions(1,Value);
#else
  switch (Window->xrd_map_interpolation_type()) {
  case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_HYPERCUBE_DISTANCE:
    Window->xrd_use_colors(0,true);
    Window->xrd_use_colors(1,true);
    Window->xrd_use_colors(2,true);
    Window->xrd_use_positions(0,true);
    Window->xrd_use_positions(1,true);
    break;
  case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_2D_CARTESIAN_DISTANCE:
    Window->xrd_use_colors(0,false);
    Window->xrd_use_colors(1,false);
    Window->xrd_use_colors(2,false);
    Window->xrd_use_positions(0,true);
    Window->xrd_use_positions(1,true);
    break;
  default:
    break;
  }
#endif

  // normalization
  if (Checkbox_xrd_normalization->checkState()==Qt::Checked) Value=true;
  else Value=false;
  Window->xrd_distance_normalization(Value);

  // the position normalization
  Window->xrd_position_normalization_type(static_cast<_layer_map_distance_ns::_position_normalization_type>(Combobox_xrd_position_normalization_type->currentIndex()));

  // the selected palette
  _palette_data_ns::_palette Palette={XRD_palette_type, XRD_palette_color_type, 0, XRD_palette_color_assigning, XRD_palette_mutable_color, XRD_palette_name_fixed_palette.toStdString()};
  if (XRD_palette_type==_palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE) Palette.Num_stops=XRD_palette_discrete_num_intervals_value+1;
  else Palette.Num_stops=XRD_palette_continuous_num_intervals_value+1;
  Window->xrd_palette(Palette);

  // the selected probe
  Window->xrd_probe(_layer_map_ns::Vec_value_probe[Combobox_xrd_probe->currentIndex()]);

  // add corners
  if (Checkbox_xrd_triangulation_add_corners->checkState()==Qt::Checked) Value=true;
  else Value=false;
  Window->xrd_triangulation_add_corners(Value);

  // RBF_radius
  float Radius_value=float(Slider_xrd_rbf_radius->value())*Window->mean_distance_between_neighbors_positions()/255.0f;
  Radius_value=Radius_value/Window->image_diagonal_size();
  Window->xrd_rbf_radius(Radius_value);

  // RBF_function
  Window->xrd_rbf_function(_new_rbf_interpolation_2d_ns::_function_type(Combobox_xrd_rbf_function->currentIndex()));

  Window->save_settings();
}

/*************************************************************************/

void _w_tab_xmapslab::xrd_create_some_maps_slot()
{
  //  std::string Name_layer;
  //  std::string Name_element;

  QList<QListWidgetItem *> Selected_items_elements=Listwidget_xrd->selectedItems();

  if (Selected_items_elements.size()>0){
    // color image
    Window->name_selected_image(Window->image_layer_name());

    //
    std::vector<std::string> Vec_selected_names;
    for (int i=0;i<Selected_items_elements.size();i++){
      Vec_selected_names.push_back(Selected_items_elements[i]->text().toStdString());
    }

    // data image
    Window->xrd_selected_names(Vec_selected_names);

    // view name
    // check that the _ are converted to -
    Window->xrd_view_name(Lineedit_xrd_view_name->text().replace('_','-').toStdString());

    //
    xrd_update_parameters();

    // create the element
    Window->xrd_create_some_maps();
  }
  else{
    QMessageBox::information(Window, Window->tr("Information"),Window->tr("One pigment must be selected at least"));
  }
}

/*************************************************************************/

void _w_tab_xmapslab::xrd_create_all_maps_slot()
{
  //  std::string Name_layer;
  //  std::string Name_element;

  // color image
  Window->name_selected_image(Window->image_layer_name());

  // view name
  Window->xrd_view_name(Lineedit_xrd_view_name->text().toStdString());

  //
  xrd_update_parameters();

  Window->xrd_create_all_maps();
}

/*************************************************************************/

void _w_tab_xmapslab::xrd_changed_view_name_slot(QString Text)
{
  Lineedit_xrd_view_name->blockSignals(true);
  Lineedit_xrd_view_name->setText(Text);
  Lineedit_xrd_view_name->blockSignals(false);
}

/*************************************************************************/

void _w_tab_xmapslab::xrd_button_pushed_maps_parameters_slot(bool State)
{
  Q_UNUSED(State)
  XRF_show_maps_parameters=!XRF_show_maps_parameters;
  if (XRF_show_maps_parameters==true){
    Pushbutton_xrd_maps_parameters->setText("Hide maps parameters");
    Frame_xrd_maps_parameters->show();
  }
  else{
    Pushbutton_xrd_maps_parameters->setText("Show maps parameters");
    Frame_xrd_maps_parameters->hide();
  }

  xrd_changed_interpolation_type_slot(int(Window->xrd_map_interpolation_type()));
}

/*************************************************************************/

void _w_tab_xmapslab::xrd_button_pushed_palette_parameters_slot(bool State)
{
  Q_UNUSED(State)
  XRD_show_palette_parameters=!XRD_show_palette_parameters;
  if (XRD_show_palette_parameters==true){
    Pushbutton_xrd_palette_parameters->setText("Hide palette parameters");
    Frame_xrd_palette_parameters->show();

    for (unsigned int i=0;i<4;i++){
      change_row_visibility(Grid_xrd_palette_parameters,i,true);
    }
    if (XRF_palette_color_assigning==_palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_MUTABLE){
      change_row_visibility(Grid_xrd_palette_parameters,4,false);
      change_row_visibility(Grid_xrd_palette_parameters,5,false);
    }
    else{
      if (XRF_palette_color_type==_palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE){
        change_row_visibility(Grid_xrd_palette_parameters,4,true);
        change_row_visibility(Grid_xrd_palette_parameters,5,false);
      }
      else{
        change_row_visibility(Grid_xrd_palette_parameters,4,false);
        change_row_visibility(Grid_xrd_palette_parameters,5,true);
      }
    }
  }
  else{
    Pushbutton_xrd_palette_parameters->setText("Show palette parameters");
    Frame_xrd_palette_parameters->hide();

    for (int i=0;i<XRD_palette_parameters_num_rows;i++){
      change_row_visibility(Grid_xrd_palette_parameters,i,false);
    }
  }
}

/*************************************************************************/

void _w_tab_xmapslab::xrd_changed_palette_type_slot(int Index)
{
  XRD_palette_type=_palette_data_ns::_palette_type(Index);
  if (XRD_palette_type==_palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE){
    Spinbox_xrd_palette_num_intervals->setRange(_palette_data_ns::PALETTE_DISCRETE_MINIMUM_INTERVALS,_palette_data_ns::PALETTE_DISCRETE_MAXIMUM_INTERVALS);

    Spinbox_xrd_palette_num_intervals->blockSignals(true);
    Spinbox_xrd_palette_num_intervals->setValue(XRF_palette_discrete_num_intervals_value);
    Spinbox_xrd_palette_num_intervals->blockSignals(false);
  }
  else{
    Spinbox_xrd_palette_num_intervals->setRange(_palette_data_ns::PALETTE_CONTINUOUS_MINIMUM_INTERVALS,_palette_data_ns::PALETTE_CONTINUOUS_MAXIMUM_INTERVALS);

    Spinbox_xrd_palette_num_intervals->blockSignals(true);
    Spinbox_xrd_palette_num_intervals->setValue(XRF_palette_continuous_num_intervals_value);
    Spinbox_xrd_palette_num_intervals->blockSignals(false);
  }
}

/*************************************************************************/

void _w_tab_xmapslab::xrd_changed_palette_color_type_slot(int Index)
{
  XRD_palette_color_type=_palette_data_ns::_palette_color_type(Index);
  if (XRD_palette_color_type==_palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE){
    if (XRD_palette_color_assigning==_palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_FIXED){
      change_row_visibility(Grid_xrd_palette_parameters,4,true);
      change_row_visibility(Grid_xrd_palette_parameters,5,false);
    }
    else{
      change_row_visibility(Grid_xrd_palette_parameters,4,false);
      change_row_visibility(Grid_xrd_palette_parameters,5,false);
    }
  }
  else{ // color
    if (XRD_palette_color_assigning==_palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_FIXED){
      change_row_visibility(Grid_xrd_palette_parameters,4,false);
      change_row_visibility(Grid_xrd_palette_parameters,5,true);
    }
    else{
      change_row_visibility(Grid_xrd_palette_parameters,4,false);
      change_row_visibility(Grid_xrd_palette_parameters,5,false);
    }
  }
}

/*************************************************************************/

void _w_tab_xmapslab::xrd_changed_num_intervals_slot(int Value)
{
  if (XRD_palette_type==_palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE){
    XRD_palette_discrete_num_intervals_value=Value;
  }
  else{
    XRD_palette_continuous_num_intervals_value=Value;
  }
}

/*************************************************************************/

void _w_tab_xmapslab::xrd_changed_palette_color_assigning_slot(int Index)
{
  XRD_palette_color_assigning=_palette_data_ns::_palette_color_assigning_type(Index);
  if (XRD_palette_color_assigning==_palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_MUTABLE){
    change_row_visibility(Grid_xrd_palette_parameters,4,false);
    change_row_visibility(Grid_xrd_palette_parameters,5,false);
  }
  else{
    if (XRD_palette_color_type==_palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE){
      change_row_visibility(Grid_xrd_palette_parameters,4,true);
      change_row_visibility(Grid_xrd_palette_parameters,5,false);
    }
    else{
      change_row_visibility(Grid_xrd_palette_parameters,4,false);
      change_row_visibility(Grid_xrd_palette_parameters,5,true);
    }
  }

  Grid_xrd_palette_parameters->update();
}

/*************************************************************************/

void _w_tab_xmapslab::xrd_palette_mutable_color_slot(QColor Color)
{
  XRD_palette_mutable_color=Color;
}

/*************************************************************************/

void _w_tab_xmapslab::xrd_changed_palette_fixed_palettes_slot(QString Name)
{
  XRD_palette_name_fixed_palette=Name;
}

/*************************************************************************/

void _w_tab_xmapslab::xrd_changed_interpolation_type_slot(int Value)
{
  if (XRD_show_maps_parameters==false){
    for (unsigned int i=0;i<XRD_maps_parameters_num_rows;i++){
      change_row_visibility(Grid_xrd_maps_parameters,i,false);
    }
  }
  else{

    switch(static_cast<_layer_map_ns::_map_interpolation_methods>(Value)){
    case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_HYPERCUBE_DISTANCE:
    case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_2D_CARTESIAN_DISTANCE:
      // View 0
      change_row_visibility(Grid_xrd_maps_parameters,0,true);
      // interpolation type 1
      change_row_visibility(Grid_xrd_maps_parameters,1,true);
      // Normalization 2
      change_row_visibility(Grid_xrd_maps_parameters,2,true);
      // Positions normalization 3
      change_row_visibility(Grid_xrd_maps_parameters,3,true);
      // Probe 4
      change_row_visibility(Grid_xrd_maps_parameters,4,true);
      // add corners 5
      change_row_visibility(Grid_xrd_maps_parameters,5,false);
      // RBF functions 6
      change_row_visibility(Grid_xrd_maps_parameters,6,false);
      // RBF radius 7
      change_row_visibility(Grid_xrd_maps_parameters,7,false);
      break;
    case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_RBF:
      // View 0
      change_row_visibility(Grid_xrd_maps_parameters,0,true);
      // interpolation type 1
      change_row_visibility(Grid_xrd_maps_parameters,1,true);
      // Normalization 2
      change_row_visibility(Grid_xrd_maps_parameters,2,false);
      // Positions normalization 3
      change_row_visibility(Grid_xrd_maps_parameters,3,false);
      // Probe 4
      change_row_visibility(Grid_xrd_maps_parameters,4,false);
      // add corners 5
      change_row_visibility(Grid_xrd_maps_parameters,5,false);
      // RBF functions 6
      change_row_visibility(Grid_xrd_maps_parameters,6,true);

      // the radius is only for some functions
      if (Window->xrd_rbf_function()==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_GAUSSIAN || Window->xrd_rbf_function()==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_MULTIQUADRIC || Window->xrd_rbf_function()==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_INVERSE_MULTIQUADRIC){

        // RBF radius 7
        change_row_visibility(Grid_xrd_maps_parameters,7,true);
      }
      else{
        // RBF radius 7
        change_row_visibility(Grid_xrd_maps_parameters,7,false);
      }
      break;
    case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_TRIANGULATION:
      // View 0
      change_row_visibility(Grid_xrd_maps_parameters,0,true);
      // interpolation type 1
      change_row_visibility(Grid_xrd_maps_parameters,1,true);
      // Normalization 2
      change_row_visibility(Grid_xrd_maps_parameters,2,false);
      // Positions normalization 3
      change_row_visibility(Grid_xrd_maps_parameters,3,false);
      // Probe 4
      change_row_visibility(Grid_xrd_maps_parameters,4,false);
      // add corners 5
      change_row_visibility(Grid_xrd_maps_parameters,5,true);
      // RBF functions 6
      change_row_visibility(Grid_xrd_maps_parameters,6,false);
      // RBF radius 7
      change_row_visibility(Grid_xrd_maps_parameters,7,false);
      break;
    }
  }

  Combobox_xrd_interpolation_type->blockSignals(true);
  Combobox_xrd_interpolation_type->setCurrentIndex(Value);
  Combobox_xrd_interpolation_type->blockSignals(false);
}

/*************************************************************************/

#ifdef ADVANCED
void _w_tab_xmapslab::changed_color_model_slot(int Value)
{
  if (currentIndex()==int(_w_tab_xmapslab_ns::_tabs::ELEMENTS_TAB)){
#ifdef XRD_ACTIVE
    Combobox_xrd_color_model->blockSignals(true);
    Combobox_xrd_color_model->setCurrentIndex(Value);
    Combobox_xrd_color_model->blockSignals(false);
#endif
  }
  else{
    Combobox_elements_color_model->blockSignals(true);
    Combobox_elements_color_model->setCurrentIndex(Value);
    Combobox_elements_color_model->blockSignals(false);
  }
}

/*************************************************************************/

void _w_tab_xmapslab::changed_use_color1_slot(int State)
{
  if (currentIndex()==int(_w_tab_xmapslab_ns::_tabs::ELEMENTS_TAB)){
    if (State==Qt::Unchecked){
      if (Checkbox_elements_use_color2->checkState()==Qt::Unchecked && Checkbox_elements_use_color3->checkState()==Qt::Unchecked && Checkbox_elements_use_position1->checkState()==Qt::Unchecked && Checkbox_elements_use_position2->checkState()==Qt::Unchecked){
        Checkbox_elements_use_color1->blockSignals(true);
        Checkbox_elements_use_color1->setCheckState(Qt::Checked);
        Checkbox_elements_use_color1->blockSignals(false);
      }
    }
#ifdef XRD_ACTIVE
    Checkbox_compounds_xrd_use_color1->blockSignals(true);
    Checkbox_compounds_xrd_use_color1->setChecked(Checkbox_elements_use_color1->isChecked());
    Checkbox_compounds_xrd_use_color1->blockSignals(false);
#endif
  }
  else{
    if (State==Qt::Unchecked){
#ifdef XRD_ACTIVE
      if (Checkbox_compounds_xrd_use_color2->checkState()==Qt::Unchecked && Checkbox_compounds_xrd_use_color3->checkState()==Qt::Unchecked && Checkbox_compounds_xrd_use_position1->checkState()==Qt::Unchecked && Checkbox_compounds_xrd_use_position2->checkState()==Qt::Unchecked){
        Checkbox_compounds_xrd_use_color1->blockSignals(true);
        Checkbox_compounds_xrd_use_color1->setCheckState(Qt::Checked);
        Checkbox_compounds_xrd_use_color1->blockSignals(false);
      }
#endif
    }

    Checkbox_elements_use_color1->blockSignals(true);
#ifdef XRD_ACTIVE
    Checkbox_elements_use_color1->setChecked(Checkbox_compounds_xrd_use_color1->isChecked());
#endif
    Checkbox_elements_use_color1->blockSignals(false);
  }
}

/*************************************************************************/

void _w_tab_xmapslab::changed_use_color2_slot(int State)
{
  if (currentIndex()==int(_w_tab_xmapslab_ns::_tabs::ELEMENTS_TAB)){
    if (State==Qt::Unchecked){
      if (Checkbox_elements_use_color1->checkState()==Qt::Unchecked && Checkbox_elements_use_color3->checkState()==Qt::Unchecked && Checkbox_elements_use_position1->checkState()==Qt::Unchecked && Checkbox_elements_use_position2->checkState()==Qt::Unchecked){
        Checkbox_elements_use_color2->blockSignals(true);
        Checkbox_elements_use_color2->setCheckState(Qt::Checked);
        Checkbox_elements_use_color2->blockSignals(false);
      }
    }
#ifdef XRD_ACTIVE
    Checkbox_compounds_xrd_use_color2->blockSignals(true);
    Checkbox_compounds_xrd_use_color2->setChecked(Checkbox_elements_use_color2->isChecked());
    Checkbox_compounds_xrd_use_color2->blockSignals(false);
#endif
  }
  else{
    if (State==Qt::Unchecked){
#ifdef XRD_ACTIVE
      if (Checkbox_compounds_xrd_use_color1->checkState()==Qt::Unchecked && Checkbox_compounds_xrd_use_color3->checkState()==Qt::Unchecked && Checkbox_compounds_xrd_use_position1->checkState()==Qt::Unchecked && Checkbox_compounds_xrd_use_position2->checkState()==Qt::Unchecked){
        Checkbox_compounds_xrd_use_color2->blockSignals(true);
        Checkbox_compounds_xrd_use_color2->setCheckState(Qt::Checked);
        Checkbox_compounds_xrd_use_color2->blockSignals(false);
      }
#endif
    }

    Checkbox_elements_use_color2->blockSignals(true);
#ifdef XRD_ACTIVE
    Checkbox_elements_use_color2->setChecked(Checkbox_compounds_xrd_use_color2->isChecked());
#endif
    Checkbox_elements_use_color2->blockSignals(false);
  }
}

/*************************************************************************/

void _w_tab_xmapslab::changed_use_color3_slot(int State)
{
  if (currentIndex()==int(_w_tab_xmapslab_ns::_tabs::ELEMENTS_TAB)){
    if (State==Qt::Unchecked){
      if (Checkbox_elements_use_color1->checkState()==Qt::Unchecked && Checkbox_elements_use_color2->checkState()==Qt::Unchecked && Checkbox_elements_use_position1->checkState()==Qt::Unchecked && Checkbox_elements_use_position2->checkState()==Qt::Unchecked){
        Checkbox_elements_use_color3->blockSignals(true);
        Checkbox_elements_use_color3->setCheckState(Qt::Checked);
        Checkbox_elements_use_color3->blockSignals(false);
      }
    }
#ifdef XRD_ACTIVE
    Checkbox_compounds_xrd_use_color3->blockSignals(true);
    Checkbox_compounds_xrd_use_color3->setChecked(Checkbox_elements_use_color3->isChecked());
    Checkbox_compounds_xrd_use_color3->blockSignals(false);
#endif
  }
  else{
    if (State==Qt::Unchecked){
#ifdef XRD_ACTIVE
      if (Checkbox_compounds_xrd_use_color1->checkState()==Qt::Unchecked && Checkbox_compounds_xrd_use_color2->checkState()==Qt::Unchecked && Checkbox_compounds_xrd_use_position1->checkState()==Qt::Unchecked && Checkbox_compounds_xrd_use_position2->checkState()==Qt::Unchecked){
        Checkbox_compounds_xrd_use_color3->blockSignals(true);
        Checkbox_compounds_xrd_use_color3->setCheckState(Qt::Checked);
        Checkbox_compounds_xrd_use_color3->blockSignals(false);
      }
#endif
    }

    Checkbox_elements_use_color3->blockSignals(true);
#ifdef XRD_ACTIVE
    Checkbox_elements_use_color3->setChecked(Checkbox_compounds_xrd_use_color1->isChecked());
#endif
    Checkbox_elements_use_color3->blockSignals(false);
  }
}

/*************************************************************************/

void _w_tab_xmapslab::changed_use_position1_slot(int State)
{
  if (currentIndex()==int(_w_tab_xmapslab_ns::_tabs::ELEMENTS_TAB)){
    if (State==Qt::Unchecked){
      if (Checkbox_elements_use_color1->checkState()==Qt::Unchecked && Checkbox_elements_use_color2->checkState()==Qt::Unchecked && Checkbox_elements_use_color3->checkState()==Qt::Unchecked && Checkbox_elements_use_position2->checkState()==Qt::Unchecked){
        Checkbox_elements_use_position1->blockSignals(true);
        Checkbox_elements_use_position1->setCheckState(Qt::Checked);
        Checkbox_elements_use_position1->blockSignals(false);
      }
    }
#ifdef XRD_ACTIVE
    Checkbox_compounds_xrd_use_position1->blockSignals(true);
    Checkbox_compounds_xrd_use_position1->setChecked(Checkbox_elements_use_position1->isChecked());
    Checkbox_compounds_xrd_use_position1->blockSignals(false);
#endif
  }
  else{
    if (State==Qt::Unchecked){
#ifdef XRD_ACTIVE
      if (Checkbox_elements_use_color1->checkState()==Qt::Unchecked && Checkbox_elements_use_color2->checkState()==Qt::Unchecked && Checkbox_elements_use_color3->checkState()==Qt::Unchecked && Checkbox_elements_use_position2->checkState()==Qt::Unchecked){
        Checkbox_compounds_xrd_use_position1->blockSignals(true);
        Checkbox_compounds_xrd_use_position1->setCheckState(Qt::Checked);
        Checkbox_compounds_xrd_use_position1->blockSignals(false);
      }
#endif
    }

    Checkbox_elements_use_position1->blockSignals(true);
#ifdef XRD_ACTIVE
    Checkbox_elements_use_position1->setChecked(Checkbox_compounds_xrd_use_position1->isChecked());
#endif
    Checkbox_elements_use_position1->blockSignals(false);
  }
}

/*************************************************************************/

void _w_tab_xmapslab::changed_use_position2_slot(int State)
{
  if (currentIndex()==int(_w_tab_xmapslab_ns::_tabs::ELEMENTS_TAB)){
    if (State==Qt::Unchecked){
      if (Checkbox_elements_use_color1->checkState()==Qt::Unchecked && Checkbox_elements_use_color2->checkState()==Qt::Unchecked && Checkbox_elements_use_color3->checkState()==Qt::Unchecked && Checkbox_elements_use_position1->checkState()==Qt::Unchecked){
        Checkbox_elements_use_position2->blockSignals(true);
        Checkbox_elements_use_position2->setCheckState(Qt::Checked);
        Checkbox_elements_use_position2->blockSignals(false);
      }
    }
#ifdef XRD_ACTIVE
    Checkbox_compounds_xrd_use_position2->blockSignals(true);
    Checkbox_compounds_xrd_use_position2->setChecked(Checkbox_elements_use_position1->isChecked());
    Checkbox_compounds_xrd_use_position2->blockSignals(false);
#endif
  }
  else{
    if (State==Qt::Unchecked){
#ifdef XRD_ACTIVE
      if (Checkbox_elements_use_color1->checkState()==Qt::Unchecked && Checkbox_elements_use_color2->checkState()==Qt::Unchecked && Checkbox_elements_use_color3->checkState()==Qt::Unchecked && Checkbox_elements_use_position1->checkState()==Qt::Unchecked){
        Checkbox_compounds_xrd_use_position2->blockSignals(true);
        Checkbox_compounds_xrd_use_position2->setCheckState(Qt::Checked);
        Checkbox_compounds_xrd_use_position2->blockSignals(false);
      }
#endif
    }

    Checkbox_elements_use_position2->blockSignals(true);
#ifdef XRD_ACTIVE
    Checkbox_elements_use_position2->setChecked(Checkbox_compounds_xrd_use_position2->isChecked());
#endif
    Checkbox_elements_use_position2->blockSignals(false);
  }
}
#endif

/*************************************************************************/

void _w_tab_xmapslab::xrf_changed_normalization_slot(int State)
{
  Q_UNUSED(State)
  Checkbox_xrf_normalization->blockSignals(true);
  Checkbox_xrf_normalization->setChecked(Checkbox_xrf_normalization->isChecked());
  Checkbox_xrf_normalization->blockSignals(false);
}

/*************************************************************************/

void _w_tab_xmapslab::xrf_changed_position_normalization_slot(int Value)
{
  Combobox_xrf_position_normalization_type->blockSignals(true);
  Combobox_xrf_position_normalization_type->setCurrentIndex(Value);
  Combobox_xrf_position_normalization_type->blockSignals(false);
}

/*************************************************************************/

void _w_tab_xmapslab::xrf_changed_probe_slot(int Value)
{
  Combobox_xrf_probe->blockSignals(true);
  Combobox_xrf_probe->setCurrentIndex(Value);
  Combobox_xrf_probe->blockSignals(false);
}

/*************************************************************************/

void _w_tab_xmapslab::xrf_changed_rbf_function_slot(int Value)
{
  _new_rbf_interpolation_2d_ns::_function_type Function=_new_rbf_interpolation_2d_ns::_function_type(Value);
  if (Function==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_GAUSSIAN || Function==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_MULTIQUADRIC || Function==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_INVERSE_MULTIQUADRIC){
    Frame_xrf_rbf_radius->show();
  }
  else{
    Frame_xrf_rbf_radius->hide();
  }
}

/*************************************************************************/

void _w_tab_xmapslab::xrf_changed_triangulation_add_corners_slot(int State)
{
  Q_UNUSED(State)
  Checkbox_xrf_triangulation_add_corners->blockSignals(true);
  Checkbox_xrf_triangulation_add_corners->setChecked(Checkbox_xrd_triangulation_add_corners->isChecked());
  Checkbox_xrf_triangulation_add_corners->blockSignals(false);
}

/*************************************************************************/
//XRD********

void _w_tab_xmapslab::xrd_changed_normalization_slot(int State)
{
  Q_UNUSED(State)
  Checkbox_xrd_normalization->blockSignals(true);
  Checkbox_xrd_normalization->setChecked(Checkbox_xrd_normalization->isChecked());
  Checkbox_xrd_normalization->blockSignals(false);
}

/*************************************************************************/

void _w_tab_xmapslab::xrd_changed_position_normalization_slot(int Value)
{
  Combobox_xrd_position_normalization_type->blockSignals(true);
  Combobox_xrd_position_normalization_type->setCurrentIndex(Value);
  Combobox_xrd_position_normalization_type->blockSignals(false);
}

/*************************************************************************/

void _w_tab_xmapslab::xrd_changed_probe_slot(int Value)
{
  Combobox_xrd_probe->blockSignals(true);
  Combobox_xrd_probe->setCurrentIndex(Value);
  Combobox_xrd_probe->blockSignals(false);
}

/*************************************************************************/

void _w_tab_xmapslab::xrd_changed_rbf_function_slot(int Value)
{
  _new_rbf_interpolation_2d_ns::_function_type Function=_new_rbf_interpolation_2d_ns::_function_type(Value);
  if (Function==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_GAUSSIAN || Function==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_MULTIQUADRIC || Function==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_INVERSE_MULTIQUADRIC){
    Frame_xrd_rbf_radius->show();
  }
  else{
    Frame_xrd_rbf_radius->hide();
  }
}

/*************************************************************************/

void _w_tab_xmapslab::xrd_changed_triangulation_add_corners_slot(int State)
{
  Q_UNUSED(State)
  Checkbox_xrd_triangulation_add_corners->blockSignals(true);
  Checkbox_xrd_triangulation_add_corners->setChecked(Checkbox_xrd_triangulation_add_corners->isChecked());
  Checkbox_xrf_triangulation_add_corners->blockSignals(false);
}

/*************************************************************************/

#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
void _w_tab_xmapslab::compounds_combination_update_parameters()
{
  // view name
  Window->view_name(Lineedit_combination_view_name->text().toStdString());

  // check the use_colors
//  bool Value;
//  if (Checkbox_xrd_use_color1->checkState()==Qt::Checked) Value=true;
//  else Value=false;
//  Window->use_colors(0,Value);

  // the selected palette
//  Window->palette(Combobox_compounds_combination_palette->currentIndex());

  // the selected probe
  Window->probe(_layer_map_ns::Vec_value_probe[Combobox_compounds_combination_probe->currentIndex()]);

  Window->save_settings();
}
#endif

/*************************************************************************/
#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
void _w_tab_xmapslab::compounds_combination_create_combination_maps_slot()
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
#endif
/*************************************************************************/
#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
void _w_tab_xmapslab::compounds_combination_create_all_individual_maps_slot()
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
#endif

/*************************************************************************/
#ifdef XRD_ACTIVE
// void _w_tab_xmapslab::xrd_update_parameters()
// {
//   bool Value;

//   // view name
//   Window->view_name(Lineedit_xrd_view_name->text().toStdString());

//    Window->map_interpolation_type(static_cast<_layer_map_ns::_map_interpolation_methods>(Combobox_xrd_interpolation_type->currentIndex()));

//   // interpolation type
// #ifdef ADVANCED
//   // the color model
//   Window->color_model(static_cast<_common_ns::_color_model>(Combobox_xrd_color_model->currentIndex()));

//   // check the use_colors

//   if (Checkbox_xrd_use_color1->checkState()==Qt::Checked) Value=true;
//   else Value=false;
//   Window->use_colors(0,Value);

//   if (Checkbox_xrd_use_color2->checkState()==Qt::Checked) Value=true;
//   else Value=false;
//   Window->use_colors(1,Value);

//   if (Checkbox_xrd_use_color3->checkState()==Qt::Checked) Value=true;
//   else Value=0;
//   Window->use_colors(2,Value);

//   // the use_positions
//   if (Checkbox_xrd_use_position1->checkState()==Qt::Checked) Value=true;
//   else Value=false;
//   Window->use_positions(0,Value);

//   if (Checkbox_xrd_use_position2->checkState()==Qt::Checked) Value=true;
//   else Value=false;
//   Window->use_positions(1,Value);
// #else
//   switch (Window->map_interpolation_type()) {
//   case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_HYPERCUBE_DISTANCE:
//      Window->use_colors(0,true);
//      Window->use_colors(1,true);
//      Window->use_colors(2,true);
//      Window->use_positions(0,true);
//      Window->use_positions(1,true);
//     break;
//   case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_2D_CARTESIAN_DISTANCE:
//     Window->use_colors(0,false);
//     Window->use_colors(1,false);
//     Window->use_colors(2,false);
//     Window->use_positions(0,true);
//     Window->use_positions(1,true);
//     break;
//   default:
//     break;
//   }
// #endif

//   // normalization
//   if (Checkbox_xrd_normalization->checkState()==Qt::Checked) Value=true;
//   else Value=false;
//   Window->distance_normalization(Value);

//   // the position normalization
//   Window->position_normalization_type(static_cast<_layer_map_distance_ns::_position_normalization_type>(Combobox_xrd_position_normalization_type->currentIndex()));

//   // the selected palette
// //  Window->palette(Combobox_xrd_palette->currentIndex());

//   // the selected probe
//   Window->probe(_layer_map_ns::Vec_value_probe[Combobox_xrd_probe->currentIndex()]);

//   // add corners
//   if (Checkbox_xrd_triangulation_add_corners->checkState()==Qt::Checked) Value=true;
//   else Value=false;
//   Window->triangulation_add_corners(Value);

//   // RBF_radius
//   float Radius_value=float(Slider_xrd_rbf_radius->value())*Window->image_diagonal_size()/255.0f;
// //  Radius_value=Radius_value/Window->image_diagonal_size();
//   Window->rbf_radius(Radius_value);

//   // RBF_function
//   Window->rbf_function(_new_rbf_interpolation_2d_ns::_function_type(Combobox_xrd_rbf_function->currentIndex()));

//   Window->save_settings();
// }
#endif

/*************************************************************************/

#ifdef XRD_ACTIVE
// void _w_tab_xmapslab::xrd_create_some_maps_slot()
// {
//   std::string Name_layer;
//   std::string Name_element;

//   QList<QListWidgetItem *> Selected_items_compounds=Listwidget_xrd->selectedItems();

//   if (Selected_items_compounds.size()>0){
//     // color image
//     Window->name_selected_image(Window->image_layer_name());

//     //
//     std::vector<std::string> Vec_names_selected_compounds;
//     for (int i=0;i<Selected_items_compounds.size();i++){
//       Vec_names_selected_compounds.push_back(Selected_items_compounds[i]->text().toStdString());
//     }

//     // data image
//     Window->compounds_selected_names(Vec_names_selected_compounds);

//     // view name
//     Window->view_name(Lineedit_xrd_view_name->text().toStdString());

//     //
//     compounds_xrd_update_parameters();

//     // create the compound
//     Window->compounds_create_some_maps();
//   }
//   else{
//     QMessageBox::information(Window, Window->tr("Information"),Window->tr("One element must be selected at least"));
//   }
// }

/*************************************************************************/

// void _w_tab_xmapslab::compounds_xrd_create_all_maps_slot()
// {
//   std::string Name_layer;
//   std::string Name_compound;

//   // color image
//   Window->name_selected_image(Window->image_layer_name());

//   // view name
//   Window->view_name(Lineedit_xrd_view_name->text().toStdString());

//   //
//   compounds_xrd_update_parameters();

//   Window->compounds_create_all_maps();
// }
#endif

/*************************************************************************/

 void _w_tab_xmapslab::change_state_table_layer(int Row,int Col)
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

 void _w_tab_xmapslab::move_layers_backward(int Initial_pos, int Destination_pos)
 {
   Window->move_layers_backward(Initial_pos,Destination_pos);
 }

 //HEA
 // the destination is at the begin

 void _w_tab_xmapslab::move_layers_forward(int Initial_pos, int Destination_pos)
 {
   Window->move_layers_forward(Initial_pos,Destination_pos);
 }

/*************************************************************************/

void _w_tab_xmapslab::show_layer_parameters(int Row,int Col)
{
  Window->show_layer_parameters(Row,Col);
}

/*************************************************************************/

//void _w_tab_xmapslab::add_image(_table_layers_ns::_info Info,QIcon *Icon1)
//{
//  QListWidgetItem *Item;
//  Item=new QListWidgetItem;
//  Item->setText(Info.Name);
//  Item->setIcon(*Icon1);
//  // Only one image so it is selected
//  Listwidget_elements_images->addItem(Item);

//#ifdef XRD_ACTIVE
//  Item=new QListWidgetItem;
//  Item->setText(Info.Name);
//  Item->setIcon(*Icon1);
//  // Only one image so it is selected
////  Item->setSelected(true);
//  Listwidget_xrd_images->addItem(Item);
//#endif
//}

/*************************************************************************/

void _w_tab_xmapslab::add_layer(_table_layers_ns::_info Info)
{
  Table_layers->add_row(Info,Window->selected_layer());

  // insert the control widget
  Verticalbox_layers->insertWidget(1,(QGroupBox *)(Window->Map_name_to_layer[Info.Name.toStdString()].Layer->get_link()),0,Qt::AlignTop);
}

/*************************************************************************/

void _w_tab_xmapslab::remove_layer(std::string Name1)
{
  if (Listwidget_xrf_images!=nullptr){
     QList<QListWidgetItem *> List=Listwidget_xrf_images->findItems(QString::fromStdString(Name1.c_str()),Qt::MatchFixedString | Qt::MatchCaseSensitive);

     if (List.size()==1){
      delete  List[0];
     }
  }
}

/*************************************************************************/

void _w_tab_xmapslab::add_xrf(std::string Name)
{
//  cout << "Se añade " << Name << endl;
  QListWidgetItem *Item;
  Item=new QListWidgetItem;
  Item->setText(QString::fromStdString(Name));
  Listwidget_xrf->addItem(Item);
}

/*************************************************************************/

void _w_tab_xmapslab::remove_all_xrf()
{
  if (Listwidget_xrf_images!=nullptr){
     QListWidgetItem *Item;
     // this variable is because the list changes in each step
     int Num_elements=Listwidget_xrf_images->count();
     for (int i=0;i<Num_elements;i++){
      Item=Listwidget_xrf_images->takeItem(0);
      delete Item;
     }
  }

  if (Listwidget_xrf!=nullptr){
     QListWidgetItem *Item;
     // this variable is because the list changes in each step
     int Num_elements=Listwidget_xrf->count();
     for (int i=0;i<Num_elements;i++){
      Item=Listwidget_xrf->takeItem(0);
      delete Item;
     }
  }
}

/*************************************************************************/

#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
void _w_tab_xmapslab::add_compound_from_elements(std::string Name)
{
  QListWidgetItem *Item;
  Item=new QListWidgetItem;
  Item->setText(QString::fromStdString(Name));
  Listwidget_combination->addItem(Item);
}

/*************************************************************************/

void _w_tab_xmapslab::remove_all_compound_from_elements()
{
  if (Listwidget_elements_images!=nullptr){
     QListWidgetItem *Item;
     // this variable is because the list changes in each step
     int Num_elements=Listwidget_compounds_combination->count();
     for (int i=0;i<Num_elements;i++){
      Item=Listwidget_compounds_combination->takeItem(0);
      delete Item;
     }
  }

  if (Listwidget_elements!=nullptr){
     QListWidgetItem *Item;
     // this variable is because the list changes in each step
     int Num_elements=Listwidget_elements->count();
     for (int i=0;i<Num_elements;i++){
      Item=Listwidget_elements->takeItem(0);
      delete Item;
     }
  }
}
#endif

/*************************************************************************/
#ifdef XRD_ACTIVE
void _w_tab_xmapslab::add_xrd(std::string Name)
{
  QListWidgetItem *Item;
  Item=new QListWidgetItem;
  Item->setText(QString::fromStdString(Name));
  Listwidget_xrd->addItem(Item);
}

/*************************************************************************/

void _w_tab_xmapslab::remove_all_xrd()
{
  if (Listwidget_xrd_images!=nullptr){
     QListWidgetItem *Item;
     // this variable is because the list changes in each step
     int Num_elements=Listwidget_xrd_images->count();
     for (int i=0;i<Num_elements;i++){
      Item=Listwidget_xrd_images->takeItem(0);
      delete Item;
     }
  }

  if (Listwidget_xrd!=nullptr){
     QListWidgetItem *Item;
     // this variable is because the list changes in each step
     int Num_elements=Listwidget_xrd->count();
     for (int i=0;i<Num_elements;i++){
      Item=Listwidget_xrd->takeItem(0);
      delete Item;
     }
  }
}
#endif

/*************************************************************************/

//void _w_tab_xmapslab::remove_all_images()
//{
//  if (Listwidget_elements_images!=nullptr){
//     // elements
//     Listwidget_elements_images->clear();
//  }
//  // compounds
//#ifdef XRD_ACTIVE
//  if (Listwidget_xrd_images!=nullptr){
//     Listwidget_xrd_images->clear();
//  }
//#endif
//}

/*************************************************************************/

void _w_tab_xmapslab::remove_all_positions()
{
  if (Table_valid_positions!=nullptr){
     Table_valid_positions->remove_all();
  }
}

/*************************************************************************/

#ifdef XRD_ACTIVE
//void _w_tab_xmapslab::remove_all_xrd_files()
//{
////  Table_xrd_files->remove_all();
//}
#endif

/*************************************************************************/

void _w_tab_xmapslab::change_button_state(int Row,int Col)
{
  Window->change_button_state(Row,Col);
}

/*************************************************************************/

void _w_tab_xmapslab::change_button_state(int Row,int Col,bool State)
{
  Table_layers->change_button(Row,Col,State);
}

/*************************************************************************/

void _w_tab_xmapslab::reverse_col(int Col)
{
  Window->reverse_col(Col);
}

/*************************************************************************/
// xrf files

void _w_tab_xmapslab::add_active_positions(const std::vector<bool>& Vec_active_positions)
{
  Table_valid_positions->update_table(Vec_active_positions);
}

/*************************************************************************/

void _w_tab_xmapslab::change_active_position(int Position)
{
  Window->change_active_position(Position);
}

/*************************************************************************/

bool _w_tab_xmapslab::active_position(int Row)
{
  return Window->active_position(Row);
}

void _w_tab_xmapslab::changed_selected_positions_slot()
{
  // check that at least there is one selected position
  if (Window->num_valid_positions()>0){
    Window->xrf_recompute_data();
#ifdef XRD_ACTIVE
    Window->xrd_recompute_data();
#endif
  }
  else{
    QMessageBox::warning(this,tr("Warning"),"There must be at least one valid position");
  }
}

/*************************************************************************/

void _w_tab_xmapslab::set_rbf_epsilon(int Value)
{
  Slider_xrf_rbf_radius->blockSignals(true);
  Slider_xrf_rbf_radius->setValue(Value);
  Slider_xrf_rbf_radius->blockSignals(false);
#ifdef XRD_ACTIVE
  Slider_xrd_rbf_radius->blockSignals(true);
  Slider_xrd_rbf_radius->setValue(Value);
  Slider_xrd_rbf_radius->blockSignals(false);
#endif
}
