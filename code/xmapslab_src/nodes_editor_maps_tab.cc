/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "nodes_editor_maps_tab.h"

#include "window_xmapslab.h"

/*************************************************************************/

_nodes_editor_maps_tab::_nodes_editor_maps_tab(_window_xmapslab *Window1, QWidget *Parent)
: QWidget(Parent)
{
//  QString Str;

  Window=Window1;

  // images
  QGroupBox *Groupbox_maps=new QGroupBox(tr("Maps"));
  Groupbox_maps->setAlignment(Qt::AlignCenter);

  Maps_list = new QListWidget;
  Maps_list->setToolTip(tr("Selects which map is shown or saved"));

  // for adjusting the size of the widget depending on the height of the font
  QFontMetrics Font_metrics(Maps_list->fontMetrics());
  Maps_list->setMaximumHeight(Font_metrics.height()*25);

  QVBoxLayout *Vboxlayout_list = new QVBoxLayout(this);

  Vboxlayout_list->addWidget(Maps_list,0,Qt::AlignTop);
  Groupbox_maps->setLayout(Vboxlayout_list);

  connect(Maps_list,SIGNAL(itemClicked(QListWidgetItem*)), this,SLOT(item_clicked(QListWidgetItem*)));

  // palette parameters************
  Frame_lab_palette_parameters=new QFrame;
  Frame_lab_palette_parameters->setFrameStyle(QFrame::Panel);

  Grid_lab_palette_parameters=new QGridLayout;

  //
  QLabel *Label_lab_palette_type=new QLabel("Palette type");

  QComboBox *Combobox_lab_palette_type = new QComboBox;
  Combobox_lab_palette_type->addItem("Discrete");
  Combobox_lab_palette_type->addItem("Continous");
  Combobox_lab_palette_type->setCurrentIndex(int(_palette_data_ns::PALETTE_TYPE_DEFAULT));
  connect(Combobox_lab_palette_type,SIGNAL(currentIndexChanged(int)),this,SLOT(lab_changed_palette_type_slot(int)));

  //
  QLabel *Label_lab_palette_color_type=new QLabel("Color type");

  QComboBox *Combobox_lab_palette_color_type = new QComboBox;
  Combobox_lab_palette_color_type->addItem("Single tone");
  Combobox_lab_palette_color_type->addItem("Color");
  Combobox_lab_palette_color_type->setCurrentIndex(int(_palette_data_ns::PALETTE_COLOR_TYPE_DEFAULT));
  connect(Combobox_lab_palette_color_type,SIGNAL(currentIndexChanged(int)),this,SLOT(lab_changed_palette_color_type_slot(int)));

  //
  QLabel *Label_lab_palette_num_intervals=new QLabel("Intervals");

  Spinbox_lab_palette_num_intervals=new QSpinBox;
  if (LAB_palette_type==_palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE){
    Spinbox_lab_palette_num_intervals->setRange(_palette_data_ns::PALETTE_DISCRETE_MINIMUM_INTERVALS,_palette_data_ns::PALETTE_DISCRETE_MAXIMUM_INTERVALS);
    Spinbox_lab_palette_num_intervals->setValue(LAB_palette_discrete_num_intervals_value);
  }
  else{
    Spinbox_lab_palette_num_intervals->setRange(_palette_data_ns::PALETTE_CONTINUOUS_MINIMUM_INTERVALS,_palette_data_ns::PALETTE_CONTINUOUS_MAXIMUM_INTERVALS);
    Spinbox_lab_palette_num_intervals->setValue(LAB_palette_continuous_num_intervals_value);
  }
  connect(Spinbox_lab_palette_num_intervals,SIGNAL(valueChanged(int)),this,SLOT(lab_changed_num_intervals_slot(int)));

  //
  QLabel *Label_lab_palette_color_assigning=new QLabel("Color assigning");

  QComboBox *Combobox_lab_palette_color_assigning = new QComboBox;
  Combobox_lab_palette_color_assigning->addItem("Mutable");
  Combobox_lab_palette_color_assigning->addItem("Fixed");
  Combobox_lab_palette_color_assigning->setCurrentIndex(int(_palette_data_ns::PALETTE_COLOR_ASSIGNING_DEFAULT));
  connect(Combobox_lab_palette_color_assigning,SIGNAL(currentIndexChanged(int)),this,SLOT(lab_changed_palette_color_assigning_slot(int)));

  //
  QLabel *Label_lab_palette_mutable_color=new QLabel("Color");

  // colors
  _button_color_simple *Button_lab_palette_mutable_color=new _button_color_simple(LAB_palette_mutable_color,false);
  connect(Button_lab_palette_mutable_color,SIGNAL(colorChanged(QColor)),this,SLOT(lab_palette_mutable_color_slot(QColor)));

  //
  QLabel *Label_lab_palette_fixed_palettes=new QLabel("Fixed palettes");

  QComboBox *Combobox_lab_palette_fixed_palettes = new QComboBox;
  for (const auto& Pair : Window->Map_fixed_palettes) {
    Combobox_lab_palette_fixed_palettes->addItem(QString::fromStdString(Pair.first));
  }
  // default
  LAB_palette_name_fixed_palette=Combobox_lab_palette_fixed_palettes->itemText(0);
  connect(Combobox_lab_palette_fixed_palettes,SIGNAL(currentTextChanged(QString)),this,SLOT(lab_changed_palette_fixed_palettes_slot(QString)));

  LAB_palette_parameters_num_rows=0;
  // Palette type 0
  Grid_lab_palette_parameters->addWidget(Label_lab_palette_type,LAB_palette_parameters_num_rows,0,Qt::AlignRight);
  Grid_lab_palette_parameters->addWidget(Combobox_lab_palette_type,LAB_palette_parameters_num_rows++,1,Qt::AlignLeft);
  // Palette color type 1
  Grid_lab_palette_parameters->addWidget(Label_lab_palette_color_type,LAB_palette_parameters_num_rows,0,Qt::AlignRight);
  Grid_lab_palette_parameters->addWidget(Combobox_lab_palette_color_type,LAB_palette_parameters_num_rows++,1,Qt::AlignLeft);
  // Palette num intervals 2
  Grid_lab_palette_parameters->addWidget(Label_lab_palette_num_intervals,LAB_palette_parameters_num_rows,0,Qt::AlignRight);
  Grid_lab_palette_parameters->addWidget(Spinbox_lab_palette_num_intervals,LAB_palette_parameters_num_rows++,1,Qt::AlignLeft);
  // Palette values type 3
  Grid_lab_palette_parameters->addWidget(Label_lab_palette_color_assigning,LAB_palette_parameters_num_rows,0,Qt::AlignRight);
  Grid_lab_palette_parameters->addWidget(Combobox_lab_palette_color_assigning,LAB_palette_parameters_num_rows++,1,Qt::AlignLeft);
  // Palette mutable color 4
  Grid_lab_palette_parameters->addWidget(Label_lab_palette_mutable_color,LAB_palette_parameters_num_rows,0,Qt::AlignRight);
  Grid_lab_palette_parameters->addWidget(Button_lab_palette_mutable_color,LAB_palette_parameters_num_rows++,1,Qt::AlignLeft);
  // Palette fixed palettes 5
  Grid_lab_palette_parameters->addWidget(Label_lab_palette_fixed_palettes,LAB_palette_parameters_num_rows,0,Qt::AlignRight);
  Grid_lab_palette_parameters->addWidget(Combobox_lab_palette_fixed_palettes,LAB_palette_parameters_num_rows++,1,Qt::AlignLeft);

  lab_changed_palette_color_assigning_slot(int(LAB_palette_color_assigning));

  Frame_lab_palette_parameters->setLayout(Grid_lab_palette_parameters);
  Frame_lab_palette_parameters->hide(); // initially hidden

  Pushbutton_lab_palette_parameters=new QPushButton("Show palette parameters");
  // Conectar el botón con el slot
  connect(Pushbutton_lab_palette_parameters,SIGNAL(clicked(bool)),this,SLOT(lab_button_pushed_palette_parameters_slot(bool)));

  // button
  Button_add_map_to_layers= new QPushButton("Add map to layers", this);
  connect(Button_add_map_to_layers, SIGNAL(clicked()),this,SLOT(add_map_to_layers_slot()));

  // separator
  QFrame *Separator=new QFrame();
  Separator->setFrameStyle(QFrame::HLine);

  // general
  QVBoxLayout *Vertical_parameters=new QVBoxLayout;

  Vertical_parameters->addWidget(Groupbox_maps);
  Vertical_parameters->addStretch();
  Vertical_parameters->addWidget(Pushbutton_lab_palette_parameters);
  Vertical_parameters->addWidget(Frame_lab_palette_parameters);
  Vertical_parameters->addWidget(Separator);
  Vertical_parameters->addWidget(Button_add_map_to_layers);

  setLayout(Vertical_parameters);
}

/*************************************************************************/

void _nodes_editor_maps_tab::set_item(std::string Name)
{
  QListWidgetItem *Item=new QListWidgetItem;
  Item->setText(tr(Name.c_str()));
  Maps_list->insertItem(Maps_list->count(),Item);
  Maps_list->updateGeometry();
}

/*************************************************************************/

QString _nodes_editor_maps_tab::selected_item()
{
  QListWidgetItem *Item=Maps_list->currentItem();
  return Item->text();
}

/*************************************************************************/

void _nodes_editor_maps_tab::set_selected_item(int Pos)
{
  Maps_list->setCurrentRow(Pos);
}

/*************************************************************************/

void _nodes_editor_maps_tab::item_clicked(QListWidgetItem *Item)
{
  Q_UNUSED(Item)
  Window->selected_image((Item->text()).toStdString());
}

/*************************************************************************/

void _nodes_editor_maps_tab::insert_maps()
{
  std::string Name;
  QListWidgetItem *Item;

  remove_maps();

  // add the names
  for (unsigned int i=0;i<Window->Vec_order_mapping->size();i++){
    Name=(*Window->Vec_order_mapping)[i];
    Item=new QListWidgetItem;
    Item->setText(tr(Name.c_str()));
    Maps_list->insertItem(Maps_list->count(),Item);
  }
  Maps_list->setCurrentRow(Window->mapping_selected_image_index());

  // enable or disable the palette
  Name=Maps_list->currentItem()->text().toStdString();
  if (Window->Map_filters[Name]->filter_class()==_filter_ns::_filter_class::FILTER_CLASS_COMBINATION){
    enable_palette();
    enable_add_to_layers_button();
  }
  else{
    disable_palette();
    if (Window->Map_filters[Name]->filter_class()==_filter_ns::_filter_class::FILTER_CLASS_IMAGE || Window->Map_filters[Name]->filter_class()==_filter_ns::_filter_class::FILTER_CLASS_ELEMENT){
      disable_add_to_layers_button();
    }
  }

  update();
}

/*************************************************************************/

void _nodes_editor_maps_tab::remove_maps()
{
  std::string Name;
  QListWidgetItem *Item;
  int Num_intems=Maps_list->count();

  for (int i=0;i<Num_intems;i++){
    Item=Maps_list->takeItem(0);
    delete Item;
  }
}

/*************************************************************************/

void _nodes_editor_maps_tab::add_map_to_layers_slot()
{
  // check the type
  string Selected_image=(*Window->Vec_order_mapping)[Window->mapping_selected_image_index()];

  if (Window->Map_filters[Selected_image]->filter_type()!=_filter_ns::_filter_type::FILTER_TYPE_ELEMENT){
    // create the name
    string Name=Window->Map_filters[Selected_image]->name();

    string Type_name=Window->Map_filters[Selected_image]->filter_type_name();

    // the parameters for the palette depend on the class of filter. Defaults are for BINARY
    _palette_data_ns::_data_type_print Data_type_print=_palette_data_ns::_data_type_print::DATA_TYPE_PRINT_INT;
    float Max_value=1.0f;

    if (Window->Map_filters[Selected_image]->filter_class()==_filter_ns::_filter_class::FILTER_CLASS_COMBINATION){
      Max_value=Window->Map_filters[Selected_image]->get_max_value();
      Data_type_print=Window->data_type_print();
    }

    _palette_data_ns::_palette Palette={LAB_palette_type, LAB_palette_color_type, 0, LAB_palette_color_assigning, LAB_palette_mutable_color, LAB_palette_name_fixed_palette.toStdString()};
    if (LAB_palette_type==_palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE) Palette.Num_stops=LAB_palette_discrete_num_intervals_value+1;
    else Palette.Num_stops=LAB_palette_continuous_num_intervals_value+1;

    Window->add_layer_map_lab(Name, Window->Map_filters[Selected_image]->get_result(), Palette, Data_type_print, Max_value, Window->color_for_zero_value());

    QMessageBox::information(Window,tr("Information"),tr("The selected image has been correctly saved in Layers<br>Return to <b>normal</b> mode to see it"));
  }
}

/*************************************************************************/

void _nodes_editor_maps_tab::change_row_visibility(QGridLayout *Layout, int Row, bool Show)
{
  for (int i = 0; i < Layout->columnCount(); i++) {
    QLayoutItem *item = Layout->itemAtPosition(Row, i);
    if (item != nullptr) {
      QWidget *Widget = item->widget();
      if (Widget != nullptr) {
        if (Show==true) Widget->show();
        else Widget->hide();
      }
    }
  }

  update();
}

/*************************************************************************/

void _nodes_editor_maps_tab::lab_changed_palette_type_slot(int Index)
{
  LAB_palette_type=_palette_data_ns::_palette_type(Index);
  if (LAB_palette_type==_palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE){
    Spinbox_lab_palette_num_intervals->setRange(_palette_data_ns::PALETTE_DISCRETE_MINIMUM_INTERVALS,_palette_data_ns::PALETTE_DISCRETE_MAXIMUM_INTERVALS);

    Spinbox_lab_palette_num_intervals->blockSignals(true);
    Spinbox_lab_palette_num_intervals->setValue(LAB_palette_discrete_num_intervals_value);
    Spinbox_lab_palette_num_intervals->blockSignals(false);
  }
  else{
    Spinbox_lab_palette_num_intervals->setRange(_palette_data_ns::PALETTE_CONTINUOUS_MINIMUM_INTERVALS,_palette_data_ns::PALETTE_CONTINUOUS_MAXIMUM_INTERVALS);

    Spinbox_lab_palette_num_intervals->blockSignals(true);
    Spinbox_lab_palette_num_intervals->setValue(LAB_palette_continuous_num_intervals_value);
    Spinbox_lab_palette_num_intervals->blockSignals(false);
  }
}

/*************************************************************************/

void _nodes_editor_maps_tab::lab_changed_palette_color_type_slot(int Index)
{
  LAB_palette_color_type=_palette_data_ns::_palette_color_type(Index);
  if (LAB_palette_color_type==_palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE){
    if (LAB_palette_color_assigning==_palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_FIXED){
      change_row_visibility(Grid_lab_palette_parameters,4,true);
      change_row_visibility(Grid_lab_palette_parameters,5,false);
    }
    else{
      change_row_visibility(Grid_lab_palette_parameters,4,false);
      change_row_visibility(Grid_lab_palette_parameters,5,false);
    }
  }
  else{ // color
    if (LAB_palette_color_assigning==_palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_FIXED){
      change_row_visibility(Grid_lab_palette_parameters,4,false);
      change_row_visibility(Grid_lab_palette_parameters,5,true);
    }
    else{
      change_row_visibility(Grid_lab_palette_parameters,4,false);
      change_row_visibility(Grid_lab_palette_parameters,5,false);
    }
  }
}

/*************************************************************************/

void _nodes_editor_maps_tab::lab_changed_num_intervals_slot(int Value)
{
  if (LAB_palette_type==_palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE){
    LAB_palette_discrete_num_intervals_value=Value;
  }
  else{
    LAB_palette_continuous_num_intervals_value=Value;
  }
}

/*************************************************************************/

void _nodes_editor_maps_tab::lab_changed_palette_color_assigning_slot(int Index)
{
  LAB_palette_color_assigning=_palette_data_ns::_palette_color_assigning_type(Index);
  if (LAB_palette_color_assigning==_palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_MUTABLE){
    change_row_visibility(Grid_lab_palette_parameters,4,false);
    change_row_visibility(Grid_lab_palette_parameters,5,false);
  }
  else{
    if (LAB_palette_color_type==_palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE){
      change_row_visibility(Grid_lab_palette_parameters,4,true);
      change_row_visibility(Grid_lab_palette_parameters,5,false);
    }
    else{
      change_row_visibility(Grid_lab_palette_parameters,4,false);
      change_row_visibility(Grid_lab_palette_parameters,5,true);
    }
  }

  Grid_lab_palette_parameters->update();
}

/*************************************************************************/

void _nodes_editor_maps_tab::lab_palette_mutable_color_slot(QColor Color)
{
  LAB_palette_mutable_color=Color;
}

/*************************************************************************/

void _nodes_editor_maps_tab::lab_changed_palette_fixed_palettes_slot(QString Name)
{
  LAB_palette_name_fixed_palette=Name;
}

/*************************************************************************/

void _nodes_editor_maps_tab::lab_button_pushed_palette_parameters_slot(bool State)
{
  Q_UNUSED(State)
  LAB_show_palette_parameters=!LAB_show_palette_parameters;
  if (LAB_show_palette_parameters==true){
    Pushbutton_lab_palette_parameters->setText("Hide palette parameters");
    Frame_lab_palette_parameters->show();

    for (int i=0;i<4;i++){
      change_row_visibility(Grid_lab_palette_parameters,i,true);
    }
    if (LAB_palette_color_assigning==_palette_data_ns::_palette_color_assigning_type::PALETTE_COLOR_ASSIGNING_MUTABLE){
      change_row_visibility(Grid_lab_palette_parameters,4,false);
      change_row_visibility(Grid_lab_palette_parameters,5,false);
    }
    else{
      if (LAB_palette_color_type==_palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE){
        change_row_visibility(Grid_lab_palette_parameters,4,true);
        change_row_visibility(Grid_lab_palette_parameters,5,false);
      }
      else{
        change_row_visibility(Grid_lab_palette_parameters,4,false);
        change_row_visibility(Grid_lab_palette_parameters,5,true);
      }
    }
  }
  else{
    Pushbutton_lab_palette_parameters->setText("Show palette parameters");
    Frame_lab_palette_parameters->hide();

    for (int i=0;i<LAB_palette_parameters_num_rows;i++){
      change_row_visibility(Grid_lab_palette_parameters,i,false);
    }
  }
}

/*************************************************************************/

void _nodes_editor_maps_tab::lab_update_parameters()
{
  // the selected palette
  _palette_data_ns::_palette Palette={LAB_palette_type, LAB_palette_color_type, 0, LAB_palette_color_assigning, LAB_palette_mutable_color, LAB_palette_name_fixed_palette.toStdString()};
  if (LAB_palette_type==_palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE) Palette.Num_stops=LAB_palette_discrete_num_intervals_value+1;
  else Palette.Num_stops=LAB_palette_continuous_num_intervals_value+1;
  Window->lab_palette(Palette);

  Window->save_settings();
}
