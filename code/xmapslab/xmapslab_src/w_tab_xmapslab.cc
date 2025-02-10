//LIC

#include "w_tab_xmapslab.h"
#include "window_xmapslab.h"
#include "palette_data.h"

//HEA

_w_tab_xmapslab::_w_tab_xmapslab(_window_xmapslab *Window1): Window(Window1)
{
  setMinimumSize(QSize(100,300));

  // 10% of the size of the widow
  setMaximumWidth(Window->width()/10);
}

//HEA

_w_tab_xmapslab::~_w_tab_xmapslab()
{
#ifdef DEBUG_XML
  std::cout << "Terminando w_tab" << endl;
#endif
}

//HEA

void _w_tab_xmapslab::initialize()
{
  create_selected_positions_widget();
  create_layers_widget();
  create_data_widget();
#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
  create_compounds_from_elements_widget();
#endif

  int Position=0;
  addTab(Widget_valid_positions, tr("Positions"));
  Map_pos_of_tab[_w_tab_xmapslab_ns::_tabs::POSITIONS_TAB]=Position++;
  addTab(Widget_layers, tr("Layers"));
  Map_pos_of_tab[_w_tab_xmapslab_ns::_tabs::LAYERS_TAB]=Position++;
  addTab(Widget_data, tr("Data"));
  Map_pos_of_tab[_w_tab_xmapslab_ns::_tabs::DATA_TAB]=Position++;
#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
  addTab(Widget_compounds_from_elements, tr("Compounds"));
  Map_pos_of_tab[_w_tab_xmapslab_ns::_tabs::COMPOUNDS_FROM_TAB]=Position++;
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

//HEA

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

//HEA

void _w_tab_xmapslab::create_data_widget()
{
  Widget_data=new QWidget;
  Verticalbox_data=new QVBoxLayout;

  // Images
//  QGroupBox *Groupbox_images=new QGroupBox("Images");
//  QVBoxLayout *Verticalbox_images1=new QVBoxLayout;

//  Listwidget_images=new QListWidget;
//  Listwidget_images->setSelectionMode(QAbstractItemView::ExtendedSelection);
//  if (Window->screen_height()<=1080) Listwidget_images->setIconSize(QSize(_window_xmapslab_ns::ICON_SIZE_1080,_window_xmapslab_ns::ICON_SIZE_1080));
//  else Listwidget_images->setIconSize(QSize(_window_xmapslab_ns::ICON_SIZE_1080*2,_window_xmapslab_ns::ICON_SIZE_1080*2));

//  Verticalbox_images1->addWidget(Listwidget_images);
//  Groupbox_images->setLayout(Verticalbox_images1);

  // Elements
  QGroupBox *Groupbox_data=new QGroupBox("Elements");
  QVBoxLayout *Verticalbox_list=new QVBoxLayout;

  ListWidget_data=new QListWidget;
  ListWidget_data->setSelectionMode(QAbstractItemView::MultiSelection);

  Verticalbox_list->addWidget(ListWidget_data);
  Groupbox_data->setLayout(Verticalbox_list);


  // label
  //
  // maps parameters ********
  QFrame *Frame_label=new QFrame;
  Frame_label->setFrameStyle(QFrame::Panel);

  QGridLayout *Grid_label=new QGridLayout;

  QLabel *Label_label=new QLabel("Label");
  Lineedit_label=new QLineEdit(_w_tab_xmapslab_ns::VIEW_NAME_DEFAULT);
  connect(Lineedit_label,SIGNAL(textChanged(QString)),this,SLOT(changed_view_name_slot(QString)));

  Grid_label->addWidget(Label_label,0,0);
  Grid_label->addWidget(Lineedit_label,0,1);

  Frame_label->setLayout(Grid_label);

  // maps parameters ********
  Frame_maps_parameters=new QFrame;
  Frame_maps_parameters->setFrameStyle(QFrame::Panel);
  Grid_maps_parameters=new QGridLayout(Frame_maps_parameters);

  //
  Maps_parameters_num_rows=0;

  QStyle *Style = static_cast<QApplication*>(QApplication::instance())->style();
  Pushbutton_show_maps_parameters=new QPushButton("Show maps parameters");
  Pushbutton_show_maps_parameters->setStyleSheet("text-align: left;");
  Pushbutton_show_maps_parameters->setIcon(QIcon(Style->standardIcon(QStyle::SP_ArrowRight)));
  // Conectar el botón con el slot
  connect(Pushbutton_show_maps_parameters,SIGNAL(clicked(bool)),this,SLOT(button_pushed_show_maps_parameters_slot(bool)));

  Grid_maps_parameters->addWidget(Pushbutton_show_maps_parameters,Maps_parameters_num_rows++,0,1,2);


  //
  QLabel *Label_interpolation_type=new QLabel("Interpolation type");

  Combobox_interpolation_type = new QComboBox;
  for (unsigned int i=0; i<_layer_map_ns::Vec_interpolation_standard_method_names.size();i++){
    Combobox_interpolation_type->addItem(_layer_map_ns::Vec_interpolation_standard_method_names[i]);
  }
  Combobox_interpolation_type->setCurrentIndex(int(Window->map_interpolation_type()));
  connect(Combobox_interpolation_type,SIGNAL(activated(int)),this,SLOT(changed_interpolation_type_slot(int)));

  Grid_maps_parameters->addWidget(Label_interpolation_type,Maps_parameters_num_rows,0);
  Grid_maps_parameters->addWidget(Combobox_interpolation_type,Maps_parameters_num_rows++,1);


  // MHD parameters
  Frame_mhd_parameters=new QFrame;
  Frame_mhd_parameters->setFrameStyle(QFrame::Panel);
  Grid_mhd_parameters=new QGridLayout(Frame_mhd_parameters);

  Map_interpolation_frames["MHD"]=Frame_mhd_parameters;

  int MHD_num_parameters=0;

  // join several buttons to get the IDs
   QButtonGroup *Buttongroup = new QButtonGroup(this);
  Buttongroup->setExclusive(false);

  //
   const std::vector<QString> Vec_names={"Color 1", "Color 2", "Color 3", "Position 1", "Position 2"};
  Vec_checkbox_mhd_parameters.resize(5);
  for (unsigned int i=0;i<5;i++){
    QLabel *Label=new QLabel(Vec_names[i]);
    Vec_checkbox_mhd_parameters[i]=new QCheckBox;
    Vec_checkbox_mhd_parameters[i]->setChecked(Window->mhd_parameter(i));
    Grid_mhd_parameters->addWidget(Label,i,0);
    Grid_mhd_parameters->addWidget(Vec_checkbox_mhd_parameters[i],i,1);
    Buttongroup->addButton(Vec_checkbox_mhd_parameters[i],i);
    MHD_num_parameters++;
  }

  connect(Buttongroup, SIGNAL(idToggled(int, bool)), this, SLOT(changed_mhd_color_position_slot(int, bool)));

  //
  QLabel *Label_distance_normalization=new QLabel("Distance normalization");

  Checkbox_distance_normalization=new QCheckBox;
  Checkbox_distance_normalization->setChecked(Window->mhd_distance_normalization());
  connect(Checkbox_distance_normalization,SIGNAL(stateChanged(int)),this,SLOT(changed_distance_normalization_slot(int)));

  Grid_mhd_parameters->addWidget(Label_distance_normalization,MHD_num_parameters,0);
  Grid_mhd_parameters->addWidget(Checkbox_distance_normalization,MHD_num_parameters++,1);

  //
  QLabel *Label_position_normalization=new QLabel("Position normalization");

  Checkbox_position_normalization=new QCheckBox;
  Checkbox_position_normalization->setChecked(Window->mhd_position_normalization());
  connect(Checkbox_position_normalization,SIGNAL(stateChanged(int)),this,SLOT(changed_position_normalization_slot(int)));

  Grid_mhd_parameters->addWidget(Label_position_normalization,MHD_num_parameters,0);
  Grid_mhd_parameters->addWidget(Checkbox_position_normalization,MHD_num_parameters++,1);

  // Combobox_position_normalization_type = new QComboBox;
  // for (unsigned int i=0; i<_layer_map_distance_ns::Vec_names_position_interpolation_type.size();i++){
  //   Combobox_position_normalization_type->addItem(_layer_map_distance_ns::Vec_names_position_interpolation_type[i]);
  // }
  // Combobox_position_normalization_type->setCurrentIndex(int(Window->position_normalization_type()));
  // connect(Combobox_position_normalization_type,SIGNAL(activated(int)),this,SLOT(changed_position_normalization_slot(int)));

  //
  QLabel *Label_probe=new QLabel("Probe");

  Combobox_probe = new QComboBox;
  for (unsigned int i=0; i<_layer_map_ns::Vec_name_probe.size();i++){
    Combobox_probe->addItem(_layer_map_ns::Vec_name_probe[i]);
  }
  Combobox_probe->setCurrentIndex(Window->probe());
  connect(Combobox_probe,SIGNAL(activated(int)),this,SLOT(changed_probe_slot(int)));

  Grid_mhd_parameters->addWidget(Label_probe,MHD_num_parameters,0);
  Grid_mhd_parameters->addWidget(Combobox_probe,MHD_num_parameters++,1);

  Frame_mhd_parameters->setLayout(Grid_mhd_parameters);

  // add to maps grid
  Grid_maps_parameters->addWidget(Frame_mhd_parameters,Maps_parameters_num_rows++,0,1,2);


  // triangulation parameters
  Frame_triangulation_parameters=new QFrame;
  Frame_triangulation_parameters->setFrameStyle(QFrame::Panel);
  Grid_triangulation_parameters=new QGridLayout(Frame_triangulation_parameters);

  Map_interpolation_frames["TRIANGULATION"]=Frame_triangulation_parameters;

  int Triangulation_num_parameters=0;

  QLabel *Label_triangulation_add_corners=new QLabel("Add corners");

  Checkbox_triangulation_add_corners=new QCheckBox;
  Checkbox_triangulation_add_corners->setChecked(Window->triangulation_add_corners());
  // Checkbox_triangulation_add_corners->hide();

  connect(Checkbox_triangulation_add_corners,SIGNAL(stateChanged(int)),this,SLOT(changed_triangulation_add_corners_slot(int)));

  Grid_triangulation_parameters->addWidget(Label_triangulation_add_corners,Triangulation_num_parameters,0);
  Grid_triangulation_parameters->addWidget(Checkbox_triangulation_add_corners,Triangulation_num_parameters++,1);

  Frame_triangulation_parameters->setLayout(Grid_triangulation_parameters);

  // add to maps grid
  Grid_maps_parameters->addWidget(Frame_triangulation_parameters,Maps_parameters_num_rows++,0,1,2);


  // RBF parameters
  Frame_rbf_parameters=new QFrame;
  Frame_rbf_parameters->setFrameStyle(QFrame::Panel);
  Grid_rbf_parameters=new QGridLayout(Frame_rbf_parameters);

  Map_interpolation_frames["RBF"]=Frame_rbf_parameters;

  int RBF_num_parameters=0;

  QLabel *Label_rbf_function=new QLabel("Function");

  Combobox_rbf_function = new QComboBox;
  for (unsigned int i=0;i<_new_rbf_interpolation_2d_ns::Vec_names_function.size();i++){
    Combobox_rbf_function->addItem(QString::fromStdString(_new_rbf_interpolation_2d_ns::Vec_names_function[i]));
  }
  Combobox_rbf_function->setCurrentIndex(int(_new_rbf_interpolation_2d_ns::FUNCTION_TYPE_DEFAULT));
  // Combobox_rbf_function->hide();

  connect(Combobox_rbf_function,SIGNAL(currentIndexChanged(int)),this,SLOT(changed_rbf_function_slot(int)));

  Grid_rbf_parameters->addWidget(Label_rbf_function,RBF_num_parameters,0);
  Grid_rbf_parameters->addWidget(Combobox_rbf_function,RBF_num_parameters++,1);

  // RBF radius
  Frame_rbf_radius=new QFrame;
  Frame_rbf_radius->setFrameStyle(QFrame::Panel);
  QGridLayout *Grid_rbf_radius=new QGridLayout;

  QLabel *Label_rbf_radius=new QLabel("Radius");
  QLabel *Label_rbf_radius_min=new QLabel("Min");
  QLabel *Label_rbf_radius_max=new QLabel("Max");

  Slider_rbf_radius=new QSlider(Qt::Horizontal);
  Slider_rbf_radius->setRange(1,255);
  Slider_rbf_radius->setSingleStep(1);
  Slider_rbf_radius->setPageStep(10);
  Slider_rbf_radius->setTickInterval(25);
  Slider_rbf_radius->setTickPosition(QSlider::TicksRight);

  int Row=0;
  Grid_rbf_radius->addWidget(Label_rbf_radius,Row++,1,Qt::AlignCenter);
  Grid_rbf_radius->addWidget(Label_rbf_radius_min,Row,0,Qt::AlignLeft);
  Grid_rbf_radius->addWidget(Slider_rbf_radius,Row,1);
  Grid_rbf_radius->addWidget(Label_rbf_radius_max,Row,2,Qt::AlignRight);

  Frame_rbf_radius->setLayout(Grid_rbf_radius);
  // Frame_rbf_radius->setMinimumWidth(350);
  // Frame_rbf_radius->hide(); //initially hidden

  // add to RBF grid
  Grid_rbf_parameters->addWidget(Frame_rbf_radius,RBF_num_parameters++,0,1,2); // span

  Frame_rbf_parameters->setLayout(Grid_rbf_parameters);

  // add to maps grid
  Grid_maps_parameters->addWidget(Frame_rbf_parameters,Maps_parameters_num_rows++,0,1,2);

  //
  Frame_maps_parameters->setLayout(Grid_maps_parameters);

  // hide everything
  change_row_visibility(Grid_maps_parameters,1,false);
  for (auto &Data : Map_interpolation_frames) Data.second->hide();
  changed_rbf_function_slot(int(_new_rbf_interpolation_2d_ns::FUNCTION_TYPE_DEFAULT));


  // Palette ***********
  Frame_palette_parameters=new QFrame;
  Frame_palette_parameters->setFrameStyle(QFrame::Panel);

  Grid_palette_parameters=new QGridLayout;

  Palette_parameters_num_rows=0;
  //
  Pushbutton_show_palette_parameters=new QPushButton("Show palette parameters");
  Pushbutton_show_palette_parameters->setStyleSheet("text-align: left;");
  Pushbutton_show_palette_parameters->setIcon(QIcon(Style->standardIcon(QStyle::SP_ArrowRight)));

  connect(Pushbutton_show_palette_parameters,SIGNAL(clicked(bool)),this,SLOT(button_pushed_show_palette_parameters_slot(bool)));

  Grid_palette_parameters->addWidget(Pushbutton_show_palette_parameters,Palette_parameters_num_rows++,0,1,2);

  //
  QLabel *Label_palette_type=new QLabel("Palette type");

  QComboBox *Combobox_palette_type = new QComboBox;
  Combobox_palette_type->addItem("Discrete");
  Combobox_palette_type->addItem("Continous");
  Combobox_palette_type->setCurrentIndex(int(_palette_data_ns::PALETTE_TYPE_DEFAULT));
  connect(Combobox_palette_type,SIGNAL(currentIndexChanged(int)),this,SLOT(changed_palette_type_slot(int)));

  Grid_palette_parameters->addWidget(Label_palette_type,Palette_parameters_num_rows,0);
  Grid_palette_parameters->addWidget(Combobox_palette_type,Palette_parameters_num_rows++,1);

  //
  QLabel *Label_palette_color_type=new QLabel("Color type");

  QComboBox *Combobox_palette_color_type = new QComboBox;
  Combobox_palette_color_type->addItem("Single tone");
  Combobox_palette_color_type->addItem("Color");
  Combobox_palette_color_type->setCurrentIndex(int(_palette_data_ns::PALETTE_COLOR_TYPE_DEFAULT));
  connect(Combobox_palette_color_type,SIGNAL(currentIndexChanged(int)),this,SLOT(changed_palette_color_type_slot(int)));

  Grid_palette_parameters->addWidget(Label_palette_color_type,Palette_parameters_num_rows,0);
  Grid_palette_parameters->addWidget(Combobox_palette_color_type,Palette_parameters_num_rows++,1);

  //
  QLabel *Label_palette_num_intervals=new QLabel("Intervals");

  Spinbox_palette_num_intervals=new QSpinBox;
  if (Palette_type==_palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE){
    Spinbox_palette_num_intervals->setRange(_palette_data_ns::PALETTE_DISCRETE_MINIMUM_INTERVALS,_palette_data_ns::PALETTE_DISCRETE_MAXIMUM_INTERVALS);
    Spinbox_palette_num_intervals->setValue(Palette_discrete_num_intervals_value);
  }
  else{
    Spinbox_palette_num_intervals->setRange(_palette_data_ns::PALETTE_CONTINUOUS_MINIMUM_INTERVALS,_palette_data_ns::PALETTE_CONTINUOUS_MAXIMUM_INTERVALS);
    Spinbox_palette_num_intervals->setValue(Palette_continuous_num_intervals_value);
  }
  connect(Spinbox_palette_num_intervals,SIGNAL(valueChanged(int)),this,SLOT(changed_palette_num_intervals_slot(int)));

  Grid_palette_parameters->addWidget(Label_palette_num_intervals,Palette_parameters_num_rows,0);
  Grid_palette_parameters->addWidget(Spinbox_palette_num_intervals,Palette_parameters_num_rows++,1);

  //
  QLabel *Label_palette_zero_color=new QLabel("0 color");

  QComboBox *Combobox_palette_zero_color = new QComboBox;
  Combobox_palette_zero_color->addItem("Black");
  Combobox_palette_zero_color->addItem("White");
  Combobox_palette_zero_color->setCurrentIndex(int(_palette_data_ns::PALETTE_COLOR_ASSIGNING_DEFAULT));
  connect(Combobox_palette_zero_color,SIGNAL(currentIndexChanged(int)),this,SLOT(changed_palette_zero_color_slot(int)));

  Grid_palette_parameters->addWidget(Label_palette_zero_color,Palette_parameters_num_rows,0);
  Grid_palette_parameters->addWidget(Combobox_palette_zero_color,Palette_parameters_num_rows++,1);

  //
  QLabel *Label_palette_color_assigning=new QLabel("Color assigning");

  QComboBox *Combobox_palette_color_assigning = new QComboBox;
  Combobox_palette_color_assigning->addItem("Fixed");
  Combobox_palette_color_assigning->addItem("Random");
  Combobox_palette_color_assigning->setCurrentIndex(int(_palette_data_ns::PALETTE_COLOR_ASSIGNING_DEFAULT));
  connect(Combobox_palette_color_assigning,SIGNAL(currentIndexChanged(int)),this,SLOT(changed_palette_color_assigning_slot(int)));

  Grid_palette_parameters->addWidget(Label_palette_color_assigning,Palette_parameters_num_rows,0);
  Grid_palette_parameters->addWidget(Combobox_palette_color_assigning,Palette_parameters_num_rows++,1);

  //
  QLabel *Label_palette_fixed_color=new QLabel("Color");

  // colors
  _button_color_simple *Button_palette_fixed_color=new _button_color_simple(Palette_fixed_color,false);
  connect(Button_palette_fixed_color,SIGNAL(colorChanged(QColor)),this,SLOT(changed_palette_fixed_color_slot(QColor)));

  Grid_palette_parameters->addWidget(Label_palette_fixed_color,Palette_parameters_num_rows,0);
  Grid_palette_parameters->addWidget(Button_palette_fixed_color,Palette_parameters_num_rows++,1);

  //
  QLabel *Label_palette_fixed_palettes=new QLabel("Fixed palettes");

  QComboBox *Combobox_palette_fixed_palettes = new QComboBox;
  for (const auto& Pair : Window->Map_fixed_palettes) {
    Combobox_palette_fixed_palettes->addItem(QString::fromStdString(Pair.first));
  }
  // default
  Palette_name_fixed_palette=Combobox_palette_fixed_palettes->itemText(0);
  connect(Combobox_palette_fixed_palettes,SIGNAL(currentTextChanged(QString)),this,SLOT(changed_palette_fixed_palettes_slot(QString)));

  Grid_palette_parameters->addWidget(Label_palette_fixed_palettes,Palette_parameters_num_rows,0);
  Grid_palette_parameters->addWidget(Combobox_palette_fixed_palettes,Palette_parameters_num_rows++,1);

  //
  // changed_palette_color_assigning_slot(int(Palette_color_assigning));

  //
  Frame_palette_parameters->setLayout(Grid_palette_parameters);
  // Frame_palette_parameters->hide(); // initially hidden

  // hide everything
  for (int Pos=1;Pos<Grid_palette_parameters->rowCount();Pos++){
    change_row_visibility(Grid_palette_parameters,Pos,false);
  }

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

  Button_create_some_maps= new QPushButton("Create some maps", this);
  Button_create_some_maps->setEnabled(false);
  connect(Button_create_some_maps, SIGNAL(clicked()),this,SLOT(create_some_maps_slot()));

  Button_create_all_maps= new QPushButton("Create all maps", this);
  Button_create_all_maps->setEnabled(false);
  connect(Button_create_all_maps, SIGNAL(clicked()),this,SLOT(create_all_maps_slot()));

  Vertical_box_buttons->addWidget(Button_create_some_maps);
  Vertical_box_buttons->addWidget(Separator2);
  Vertical_box_buttons->addWidget(Button_create_all_maps);

  Group_box_buttons->setLayout(Vertical_box_buttons);

  //
//  Verticalbox_data->addWidget(Groupbox_images);
  Verticalbox_data->addWidget(Groupbox_data);
  Verticalbox_data->addWidget(Frame_label);
  // Verticalbox_data->addWidget(Pushbutton_maps_parameters);
  Verticalbox_data->addWidget(Frame_maps_parameters); // is colapsed
  // Verticalbox_data->addWidget(Pushbutton_palette_parameters);
  Verticalbox_data->addWidget(Frame_palette_parameters); // is colapsed
  Verticalbox_data->addWidget(Separator1);
  Verticalbox_data->addWidget(Group_box_buttons);

  Widget_data->setLayout(Verticalbox_data);
}


//HEA

void _w_tab_xmapslab::adjust_interpolation_options(bool Masks_ids_image_loaded)
{
  if (Masks_ids_image_loaded){
    for (unsigned int i=0; i<_layer_map_ns::Vec_interpolation_segmentation_based_method_names.size();i++){
      Combobox_interpolation_type->addItem(_layer_map_ns::Vec_interpolation_segmentation_based_method_names[i]);
    }
  }
}


//HEA
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


//HEA

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

//HEA

void _w_tab_xmapslab::create_selected_positions_widget()
{
  Widget_valid_positions=new QWidget;

  Verticalbox_valid_positions=new QVBoxLayout;

  std::string Name_table0="XRF files";
  Table_valid_positions=new _table_active_positions(Name_table0,this);

//   connect(Table_valid_positions,SIGNAL(cellClicked(int,int)),this,SLOT(cell_clicked_slot(int,int)));

  // separator
  QFrame *Separator=new QFrame();
  Separator->setFrameStyle(QFrame::HLine);

  QPushButton *Button_files_apply_changes= new QPushButton("Update data", this);
  connect(Button_files_apply_changes, SIGNAL(clicked()),this,SLOT(changed_selected_positions_slot()));

  //
  Verticalbox_valid_positions->addWidget(static_cast<QTableWidget *>(Table_valid_positions));
  Verticalbox_valid_positions->addWidget(Separator);
  Verticalbox_valid_positions->addWidget(Button_files_apply_changes);

  Widget_valid_positions->setLayout(Verticalbox_valid_positions);
}

//HEAD

void _w_tab_xmapslab::tab_bar_clicked_slot(int Tab1)
{
  Window->selected_tab(static_cast<_w_tab_xmapslab_ns::_tabs>(Tab1));

  Window->update_color_bar();
}

//HEA

void _w_tab_xmapslab::add_filter_layer_slot(int Value)
{
//  Combo_add_layer->setCurrentIndex(0);
  switch (Value){
  case int(_layer_xmapslab_ns::_additional_layer::ADDITIONAL_LAYER_NOTHING):break;
#ifdef YES_LAYERS_EDGES_CANNY
  case int(_layer_xmapslab_ns::_additional_layer::ADDITIONAL_LAYER_CANNY):Window->add_layer_filter(_layer_xmapslab_ns::_subtype::LAYER_TYPE_CANNY);break;
#endif
#ifdef YES_LAYERS_EDGES_DOG
  case int(_layer_xmapslab_ns::_additional_layer::ADDITIONAL_LAYER_DOG):Window->add_layer_filter(_layer_xmapslab_ns::_subtype::SUBTYPE_DOG);break;
#endif
#ifdef YES_LAYERS_EDGES_KANG
  case int(_layer_xmapslab_ns::_additional_layer::ADDITIONAL_LAYER_KANG):Window->add_layer_filter(_layer_xmapslab_ns::_layer_type::LAYER_TYPE_KANG);break;
#endif
#ifdef YES_LAYERS_EDGES_KMEANS
  case int(_layer_xmapslab_ns::_additional_layer::ADDITIONAL_LAYER_KMEANS):Window->add_layer_filter(_layer_xmapslab_ns::_layer_type::LAYER_TYPE_KMEANS);break;
#endif
  }
}

//HEA

void _w_tab_xmapslab::remove_layer_from_layout(std::string Name)
{
  Verticalbox_layers->removeWidget(static_cast<QWidget *>(Window->Map_name_to_layer[Name].Layer->get_link()));
  static_cast<QWidget *>(Window->Map_name_to_layer[Name].Layer->get_link())->setParent(0);
  static_cast<QWidget *>(Window->Map_name_to_layer[Name].Layer->get_link())->deleteLater();
}

//HEA

void _w_tab_xmapslab::remove_selected_layer_slot()
{
  Window->remove_element_layer();
}

//HEA

void _w_tab_xmapslab::remove_all_layers_slot()
{
  Window->remove_all_pigment_layers();
}

//HEA

void _w_tab_xmapslab::change_row_visibility(QGridLayout *Layout, int Row, bool Show)
{
  for (int Col = 0; Col < Layout->columnCount(); Col++) {
    QLayoutItem *item = Layout->itemAtPosition(Row, Col);
    if (item != nullptr) {
      QWidget *Widget = item->widget();
      if (Widget != nullptr) {
        if (Show==true) Widget->show();
        else Widget->hide();
      }
    }
  }
}

//HEA

void _w_tab_xmapslab::update_parameters()
{
  bool Value;
  // view name
  Window->view_name(Lineedit_label->text().toStdString());

  // interpolation type
  Window->map_interpolation_type(static_cast<_layer_map_ns::_map_interpolation_methods>(Combobox_interpolation_type->currentIndex()));

  // the color model
  // Window->color_model(static_cast<_common_ns::_color_model>(Combobox_color_model->currentIndex()));

  for (unsigned int i=0;i<5;i++){
    if (Vec_checkbox_mhd_parameters[i]->checkState()==Qt::Checked) Window->mhd_parameter(i,true);
    else Window->mhd_parameter(i,false);
  }

  // value normalization
  if (Checkbox_distance_normalization->checkState()==Qt::Checked) Value=true;
  else Value=false;
  Window->mhd_distance_normalization(Value);

  // the position normalization
  if (Checkbox_position_normalization->checkState()==Qt::Checked) Value=true;
  else Value=false;
  Window->mhd_position_normalization(Value);

  // the selected palette
  _palette_data_ns::_palette Palette={Palette_type, Palette_color_type, 0, Palette_color_assigning, Palette_fixed_color, Palette_name_fixed_palette.toStdString()};
  if (Palette_type==_palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE) Palette.Num_stops=Palette_discrete_num_intervals_value+1;
  else Palette.Num_stops=Palette_continuous_num_intervals_value+1;
  Window->palette(Palette);

  // the zero color
  Window->zero_color(Palette_zero_color);

  // the selected probe
  Window->probe(_layer_map_ns::Vec_value_probe[Combobox_probe->currentIndex()]);

  // add corners
  if (Checkbox_triangulation_add_corners->checkState()==Qt::Checked) Value=true;
  else Value=false;
  Window->triangulation_add_corners(Value);

  // RBF_radius
  float Radius_value=float(Slider_rbf_radius->value())*Window->mean_distance_between_neighbors_positions()/255.0f;
  Radius_value=Radius_value/Window->image_diagonal_size();
  Window->rbf_radius(Radius_value);

  // RBF_function
  Window->rbf_function(_new_rbf_interpolation_2d_ns::_function_type(Combobox_rbf_function->currentIndex()));

  Window->save_settings();
}


//HEA

void _w_tab_xmapslab::create_some_maps_slot()
{
//  std::string Name_layer;
//  std::string Name_element;

  QList<QListWidgetItem *> Selected_items_elements=ListWidget_data->selectedItems();

  if (Selected_items_elements.size()>0){
    // color image
    Window->name_selected_image(Window->image_layer_name());

    //
    std::vector<std::string> Vec_selected_names;
    for (int i=0;i<Selected_items_elements.size();i++){
      Vec_selected_names.push_back(Selected_items_elements[i]->text().toStdString());
    }

    // data image
    Window->selected_names(Vec_selected_names);

    // view name
    // check that the _ are converted to -
    Window->view_name(Lineedit_label->text().replace('_','-').toStdString());

    //
    update_parameters();

    // create the element
    Window->create_some_maps();
  }
  else{
    QMessageBox::information(Window, Window->tr("Information"),Window->tr("One element must be selected at least"));
  }
}

//HEA

void _w_tab_xmapslab::create_all_maps_slot()
{
//  std::string Name_layer;
//  std::string Name_element;

  // color image
  Window->name_selected_image(Window->image_layer_name());

  // view name
  Window->view_name(Lineedit_label->text().toStdString());

  //
  update_parameters();

  Window->create_all_maps();
}

//HEA

void _w_tab_xmapslab::changed_view_name_slot(QString Text)
{
  Lineedit_label->blockSignals(true);
  Lineedit_label->setText(Text);
  Lineedit_label->blockSignals(false);
}

//HEA

void _w_tab_xmapslab::button_pushed_show_maps_parameters_slot(bool State)
{
  Q_UNUSED(State)
  Show_maps_parameters=!Show_maps_parameters;
  QStyle *Style = static_cast<QApplication*>(QApplication::instance())->style();
  if (Show_maps_parameters==true){
    Pushbutton_show_maps_parameters->setText("Hide maps parameters");
    Pushbutton_show_maps_parameters->setIcon(QIcon(Style->standardIcon(QStyle::SP_ArrowDown)));
    change_row_visibility(Grid_maps_parameters,1,true); // interpolation combobox
    changed_interpolation_type_slot(int(Window->map_interpolation_type()));
  }
  else{    
    Pushbutton_show_maps_parameters->setText("Show maps parameters");
    Pushbutton_show_maps_parameters->setIcon(QIcon(Style->standardIcon(QStyle::SP_ArrowRight)));
    change_row_visibility(Grid_maps_parameters,1,false); // interpolation combobox
    for (auto &Data : Map_interpolation_frames) Data.second->hide();
  }
}

//HEA
//????
void _w_tab_xmapslab::button_pushed_show_palette_parameters_slot(bool State)
{
  Q_UNUSED(State)
  Show_palette_parameters=!Show_palette_parameters;
  QStyle *Style = static_cast<QApplication*>(QApplication::instance())->style();
  if (Show_palette_parameters==true){
    Pushbutton_show_palette_parameters->setText("Hide palette parameters");
    Pushbutton_show_palette_parameters->setIcon(QIcon(Style->standardIcon(QStyle::SP_ArrowDown)));
    // Frame_palette_parameters->show();

    for (unsigned int i=0;i<6;i++){
      change_row_visibility(Grid_palette_parameters,i,true);
    }
    if (Palette_color_assigning==_palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_RANDOM){
      change_row_visibility(Grid_palette_parameters,6,false);
      change_row_visibility(Grid_palette_parameters,7,false);
    }
    else{
      if (Palette_color_type==_palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE){
        change_row_visibility(Grid_palette_parameters,6,true);
        change_row_visibility(Grid_palette_parameters,7,false);
      }
      else{
        change_row_visibility(Grid_palette_parameters,6,false);
        change_row_visibility(Grid_palette_parameters,7,true);
      }
    }
  }
  else{
    Pushbutton_show_palette_parameters->setText("Show palette parameters");
    Pushbutton_show_palette_parameters->setIcon(QIcon(Style->standardIcon(QStyle::SP_ArrowRight)));
    // Frame_palette_parameters->hide();

    for (int i=1;i<Grid_palette_parameters->rowCount();i++){
      change_row_visibility(Grid_palette_parameters,i,false);
    }
  }
}

//HEA

void _w_tab_xmapslab::changed_palette_type_slot(int Index)
{
  Palette_type=_palette_data_ns::_palette_type(Index);
  if (Palette_type==_palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE){
    Spinbox_palette_num_intervals->setRange(_palette_data_ns::PALETTE_DISCRETE_MINIMUM_INTERVALS,_palette_data_ns::PALETTE_DISCRETE_MAXIMUM_INTERVALS);

    Spinbox_palette_num_intervals->blockSignals(true);
    Spinbox_palette_num_intervals->setValue(Palette_discrete_num_intervals_value);
    Spinbox_palette_num_intervals->blockSignals(false);
  }
  else{
    Spinbox_palette_num_intervals->setRange(_palette_data_ns::PALETTE_CONTINUOUS_MINIMUM_INTERVALS,_palette_data_ns::PALETTE_CONTINUOUS_MAXIMUM_INTERVALS);

    Spinbox_palette_num_intervals->blockSignals(true);
    Spinbox_palette_num_intervals->setValue(Palette_continuous_num_intervals_value);
    Spinbox_palette_num_intervals->blockSignals(false);
  }
}

//HEA

void _w_tab_xmapslab::changed_palette_color_type_slot(int Index)
{
  Palette_color_type=_palette_data_ns::_palette_color_type(Index);
  if (Palette_color_type==_palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE){
    if (Palette_color_assigning==_palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_FIXED){
      change_row_visibility(Grid_palette_parameters,6,true);
      change_row_visibility(Grid_palette_parameters,7,false);
    }
    else{
      change_row_visibility(Grid_palette_parameters,6,false);
      change_row_visibility(Grid_palette_parameters,7,false);
    }
  }
  else{ // color
    if (Palette_color_assigning==_palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_FIXED){
      change_row_visibility(Grid_palette_parameters,6,false);
      change_row_visibility(Grid_palette_parameters,7,true);
    }
    else{
      change_row_visibility(Grid_palette_parameters,6,false);
      change_row_visibility(Grid_palette_parameters,7,false);
    }
  }
}

//HEA

void _w_tab_xmapslab::changed_palette_zero_color_slot(int Index)
{
  Palette_zero_color=_common_ns::_zero_color(Index);
}


//HEA

void _w_tab_xmapslab::changed_palette_num_intervals_slot(int Value)
{
  if (Palette_type==_palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE){
    Palette_discrete_num_intervals_value=Value;
  }
  else{
    Palette_continuous_num_intervals_value=Value;
  }
}

//HEA

void _w_tab_xmapslab::changed_palette_color_assigning_slot(int Index)
{
  Palette_color_assigning=_palette_data_ns::_palette_color_assigning_type(Index);
  if (Palette_color_assigning==_palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_FIXED){
    if (Palette_color_type==_palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE){
      change_row_visibility(Grid_palette_parameters,6,true);
      change_row_visibility(Grid_palette_parameters,7,false);
    }
    else{
      change_row_visibility(Grid_palette_parameters,6,false);
      change_row_visibility(Grid_palette_parameters,7,true);
    }
  }
  else{ // random
    change_row_visibility(Grid_palette_parameters,6,false);
    change_row_visibility(Grid_palette_parameters,7,false);
  }

  Grid_palette_parameters->update();
}

//HEA

void _w_tab_xmapslab::changed_palette_fixed_color_slot(QColor Color)
{
  Palette_fixed_color=Color;
}

//HEA

void _w_tab_xmapslab::changed_palette_fixed_palettes_slot(QString Name)
{
  Palette_name_fixed_palette=Name;
}

//HEA

void _w_tab_xmapslab::changed_interpolation_type_slot(int Value)
{
  Window->map_interpolation_type(_layer_map_ns::_map_interpolation_methods(Value));

  for (auto &Data : Map_interpolation_frames) Data.second->hide();

  switch(static_cast<_layer_map_ns::_map_interpolation_methods>(Value)){
  case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_HYPERCUBE_DISTANCE:
  case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MHD_SEGMENTATION:
    Map_interpolation_frames["MHD"]->show();
    break;
  case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_TRIANGULATION:
    Map_interpolation_frames["TRIANGULATION"]->show();
    break;
  case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_RBF:
    Map_interpolation_frames["RBF"]->show();
  case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MEAN_SEGMENTATION:
  case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_SEGMENTATION:
  case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MAXIMUM_SEGMENTATION:
    break;
  }



  // if (Show_maps_parameters==false){
  //   for (int i=1;i<Grid_maps_parameters->rowCount();i++){
  //     change_row_visibility(Grid_maps_parameters,i,false);
  //   }
  // }
  // else{
  //   // button
  //   change_row_visibility(Grid_maps_parameters,0,true);

  //   switch(static_cast<_layer_map_ns::_map_interpolation_methods>(Value)){
  //     case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_HYPERCUBE_DISTANCE:
  //     case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_2D_CARTESIAN_DISTANCE:
  //     case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MHD_SEGMENTATION:
  //     case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MEAN_SEGMENTATION:
  //     case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MINIMUM_SEGMENTATION:
  //     case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_MAXIMUM_SEGMENTATION:
  //       // interpolation type 1
  //       change_row_visibility(Grid_maps_parameters,1,true);
  //       // Normalization 2
  //       change_row_visibility(Grid_maps_parameters,2,true);
  //       // Positions normalization 3
  //       change_row_visibility(Grid_maps_parameters,3,true);
  //       // Probe 4
  //       change_row_visibility(Grid_maps_parameters,4,true);
  //       // add corners 5
  //       change_row_visibility(Grid_maps_parameters,5,false);
  //       // RBF functions 6
  //       change_row_visibility(Grid_maps_parameters,6,false);
  //       // RBF radius 7
  //       change_row_visibility(Grid_maps_parameters,7,false);
  //     break;
  //     case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_RBF:
  //       // interpolation type 1
  //       change_row_visibility(Grid_maps_parameters,1,true);
  //       // Normalization 2
  //       change_row_visibility(Grid_maps_parameters,2,false);
  //       // Positions normalization 3
  //       change_row_visibility(Grid_maps_parameters,3,false);
  //       // Probe 4
  //       change_row_visibility(Grid_maps_parameters,4,false);
  //       // add corners 5
  //       change_row_visibility(Grid_maps_parameters,5,false);
  //       // RBF functions 6
  //       change_row_visibility(Grid_maps_parameters,6,true);

  //       // the radius is only for some functions
  //       if (Window->rbf_function()==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_GAUSSIAN || Window->rbf_function()==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_MULTIQUADRIC || Window->rbf_function()==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_INVERSE_MULTIQUADRIC){

  //         // RBF radius 7
  //         change_row_visibility(Grid_maps_parameters,7,true);
  //       }
  //       else{
  //         // RBF radius 7
  //         change_row_visibility(Grid_maps_parameters,7,false);
  //       }
  //     break;
  //     case _layer_map_ns::_map_interpolation_methods::MAP_INTERPOLATION_TYPE_TRIANGULATION:
  //       // interpolation type 1
  //       change_row_visibility(Grid_maps_parameters,1,true);
  //       // Normalization 2
  //       change_row_visibility(Grid_maps_parameters,2,false);
  //       // Positions normalization 3
  //       change_row_visibility(Grid_maps_parameters,3,false);
  //       // Probe 4
  //       change_row_visibility(Grid_maps_parameters,4,false);
  //       // add corners 5
  //       change_row_visibility(Grid_maps_parameters,5,true);
  //       // RBF functions 6
  //       change_row_visibility(Grid_maps_parameters,6,false);
  //       // RBF radius 7
  //       change_row_visibility(Grid_maps_parameters,7,false);
  //     break;
  //   }
  // }

  // Combobox_interpolation_type->blockSignals(true);
  // Combobox_interpolation_type->setCurrentIndex(Value);
  // Combobox_interpolation_type->blockSignals(false);
}



//HEA

#ifdef ADVANCED
void _w_tab_xmapslab::changed_color_model_slot(int Value)
{
  if (currentIndex()==int(_w_tab_xmapslab_ns::_tabs::ELEMENTS_TAB)){
  }
  else{
    Combobox_elements_color_model->blockSignals(true);
    Combobox_elements_color_model->setCurrentIndex(Value);
    Combobox_elements_color_model->blockSignals(false);
  }
}
#endif

//HEA

void _w_tab_xmapslab::changed_mhd_color_position_slot(int Id, bool Checked)
{
  if (Checked==Qt::Unchecked){
    // check that at least there is one checked
    int Counter=0;
    for (unsigned int i=0;i<Vec_checkbox_mhd_parameters.size();i++){
      if (Vec_checkbox_mhd_parameters[i]->checkState()==Qt::Checked) Counter++;
    }
    if (Counter==0){
      Vec_checkbox_mhd_parameters[Id]->blockSignals(true);
      Vec_checkbox_mhd_parameters[Id]->setCheckState(Qt::Checked);
      Vec_checkbox_mhd_parameters[Id]->blockSignals(false);
    }
  }
}

//HEA

void _w_tab_xmapslab::changed_distance_normalization_slot(int State)
{
  Q_UNUSED(State)
  Checkbox_distance_normalization->blockSignals(true);
  Checkbox_distance_normalization->setChecked(Checkbox_distance_normalization->isChecked());
  Checkbox_distance_normalization->blockSignals(false);
}

//HEA

void _w_tab_xmapslab::changed_position_normalization_slot(int State)
{
  Q_UNUSED(State)
  Checkbox_position_normalization->blockSignals(true);
  Checkbox_position_normalization->setChecked(Checkbox_position_normalization->isChecked());
  Checkbox_position_normalization->blockSignals(false);

  // Combobox_position_normalization_type->blockSignals(true);
  // Combobox_position_normalization_type->setCurrentIndex(State);
  // Combobox_position_normalization_type->blockSignals(false);
}

//HEA

void _w_tab_xmapslab::changed_probe_slot(int Value)
{
  Combobox_probe->blockSignals(true);
  Combobox_probe->setCurrentIndex(Value);
  Combobox_probe->blockSignals(false);
}

//HEA

void _w_tab_xmapslab::changed_rbf_function_slot(int Value)
{
  _new_rbf_interpolation_2d_ns::_function_type Function=_new_rbf_interpolation_2d_ns::_function_type(Value);
  if (Function==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_GAUSSIAN || Function==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_MULTIQUADRIC || Function==_new_rbf_interpolation_2d_ns::_function_type::FUNCTION_TYPE_INVERSE_MULTIQUADRIC){
    Frame_rbf_radius->show();
  }
  else{
    Frame_rbf_radius->hide();
  }
}


//HEA

void _w_tab_xmapslab::changed_triangulation_add_corners_slot(int State)
{
  Q_UNUSED(State)
  Checkbox_triangulation_add_corners->blockSignals(true);
  Checkbox_triangulation_add_corners->setChecked(Checkbox_triangulation_add_corners->isChecked());
  Checkbox_triangulation_add_corners->blockSignals(false);
}



//HEA

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

//HEA
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
//HEA
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



//HEA

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


//HEA

void _w_tab_xmapslab::show_layer_parameters(int Row,int Col)
{
  Window->show_layer_parameters(Row,Col);
}


//HEA

//void _w_tab_xmapslab::add_image(_table_layers_ns::_info Info,QIcon *Icon1)
//{
//  QListWidgetItem *Item;
//  Item=new QListWidgetItem;
//  Item->setText(Info.Name);
//  Item->setIcon(*Icon1);
//  // Only one image so it is selected
//  Listwidget_elements_images->addItem(Item);

//}


//HEA

void _w_tab_xmapslab::add_layer(_table_layers_ns::_info Info)
{
  Table_layers->add_row(Info,Window->selected_layer());

  // insert the control widget
  Verticalbox_layers->insertWidget(1,(QGroupBox *)(Window->Map_name_to_layer[Info.Name.toStdString()].Layer->get_link()),0,Qt::AlignTop);
}

//HEA

void _w_tab_xmapslab::remove_layer(std::string Name1)
{
  if (Listwidget_images!=nullptr){
     QList<QListWidgetItem *> List=Listwidget_images->findItems(QString::fromStdString(Name1.c_str()),Qt::MatchFixedString | Qt::MatchCaseSensitive);

     if (List.size()==1){
      delete  List[0];
     }
  }
}


//HEA

void _w_tab_xmapslab::add_element(std::string Type, std::string Element)
{
  QListWidgetItem *Item;
  Item=new QListWidgetItem;
  Item->setText(QString::fromStdString(Type+'_'+Element));
  ListWidget_data->addItem(Item);
}

//HEA

void _w_tab_xmapslab::remove_all()
{
  if (Listwidget_images!=nullptr){
     QListWidgetItem *Item;
     // this variable is because the list changes in each step
     int Num_elements=Listwidget_images->count();
     for (int i=0;i<Num_elements;i++){
      Item=Listwidget_images->takeItem(0);
      delete Item;
     }
  }

  if (ListWidget_data!=nullptr){
     QListWidgetItem *Item;
     // this variable is because the list changes in each step
     int Num_elements=ListWidget_data->count();
     for (int i=0;i<Num_elements;i++){
      Item=ListWidget_data->takeItem(0);
      delete Item;
     }
  }
}


//HEA

#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
void _w_tab_xmapslab::add_compound_from_elements(std::string Name)
{
  QListWidgetItem *Item;
  Item=new QListWidgetItem;
  Item->setText(QString::fromStdString(Name));
  Listwidget_combination->addItem(Item);
}

//HEA

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



//HEA

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

//HEA

void _w_tab_xmapslab::remove_all_positions()
{
  if (Table_valid_positions!=nullptr){
     Table_valid_positions->remove_all();
  }
}

//HEA

void _w_tab_xmapslab::change_button_state(int Row,int Col)
{
  Window->change_button_state(Row,Col);
}

//HEA

void _w_tab_xmapslab::change_button_state(int Row,int Col,bool State)
{
  Table_layers->change_button(Row,Col,State);
}

//HEA

void _w_tab_xmapslab::reverse_col(int Col)
{
  Window->reverse_col(Col);
}

//HEA
// xrf files

void _w_tab_xmapslab::add_active_positions(const std::vector<bool>& Vec_active_positions)
{
  Table_valid_positions->update_table(Vec_active_positions);
}

//HEA

void _w_tab_xmapslab::change_active_position(int Position)
{
  Window->change_active_position(Position);
}

//HEA

bool _w_tab_xmapslab::active_position(int Row)
{
  return Window->active_position(Row);
}

void _w_tab_xmapslab::changed_selected_positions_slot()
{
  // check that at least there is one selected position
  if (Window->num_valid_positions()>0){
    Window->recompute_data();
  }
  else{
    QMessageBox::warning(this,tr("Warning"),"There must be at least one valid position");
  }
}


//HEA

void _w_tab_xmapslab::set_rbf_epsilon(int Value)
{
  Slider_rbf_radius->blockSignals(true);
  Slider_rbf_radius->setValue(Value);
  Slider_rbf_radius->blockSignals(false);
}
