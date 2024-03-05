/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef WIDGET_TAB_XMAPSLAB_H
#define WIDGET_TAB_XMAPSLAB_H

#include <QWidget>
#include <QVBoxLayout>
#include <QComboBox>
#include <QListWidget>
#include <QPushButton>
#include <QIcon>
#include <QProgressDialog>

#include <vector>
#include <map>

#include "table.h"
#include "table_layers.h"
#include "table_active_positions.h"

#include "color_bar_abstract.h"
// #include "dialog_create_palette.h"
#include "layer_compound_from_elements.h"
#include "layer_map.h"

#include "palette_data.h"

#include "button_color_simple.h"

class _window_xmapslab;

namespace _w_tab_xmapslab_ns {
  enum class _tabs:unsigned char {POSITIONS_TAB, LAYERS_TAB, ELEMENTS_TAB, COMPOUNDS_FROM_XRF_TAB, COMPOUNDS_XRD_TAB, TAB_LAST,TAB_PALETTES};
  const QString VIEW_NAME_DEFAULT="view1";
}

/*************************************************************************/
class _w_tab_xmapslab: public QTabWidget
{
  Q_OBJECT
  public:
  _table_layers *Table_layers=nullptr;

  _w_tab_xmapslab(_window_xmapslab *Window1);
  ~_w_tab_xmapslab();

  void initialize();

  void create_layers_widget();
  void create_xrf_widget();
  void create_compounds_from_elements_widget();
  void create_xrd_widget();
  void xrf_create_files_widget();
  void xrd_create_files_widget();
  void create_palettes_widget();

  void select_layers_row(int Row){Table_layers->selectRow(Row);}

  void add_image(_table_layers_ns::_info Info, QIcon *Icon1);
  void add_layer(_table_layers_ns::_info Info);

  void remove_layer_from_layout(std::string Name1);

  void remove_layer(std::string Name1);

  void change_state_table_layer(int Row,int Col);

  //  void interchange_layers(int Initial_pos,int Destination_pos);
  void move_layers_backward(int Initial_pos,int Destination_pos);
  void move_layers_forward(int Initial_pos,int Destination_pos);

  void show_layer_parameters(int Row, int Col);

  void change_button_state(int Row,int Col);
  void change_button_state(int Row,int Col,bool State);

  void add_xrf(std::string Name);
  void remove_all_xrf();

#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
  void add_compound_from_elements(std::string Name);
  void remove_all_compound_from_elements();
#endif

#ifdef XRD_ACTIVE
  void add_xrd(std::string Name);
  void remove_all_xrd();
#endif

  void remove_all_positions();

  void xrf_change_buttons_state(bool State){
    if (Button_xrf_create_some_maps!=nullptr){
      Button_xrf_create_some_maps->setEnabled(State);
    }
    if (Button_xrf_create_all_maps!=nullptr){
      Button_xrf_create_all_maps->setEnabled(State);
    }
  }

#ifdef XRD_ACTIVE
  void xrd_change_buttons_state(bool State){
    if (Button_xrd_create_some_maps!=nullptr){
      Button_xrd_create_some_maps->setEnabled(State);
    }
    if (Button_xrd_create_all_maps!=nullptr){
      Button_xrd_create_all_maps->setEnabled(State);
    }
  }
#endif

  void reverse_col(int Col);

  void change_active_position(int Position);
  bool active_position(int Row);

  void add_active_positions(const std::vector<bool> &Vec_active_positions);

  _window_xmapslab* window(){return Window;}

  //
  //  void update_xrf_widget();

  void set_rbf_epsilon(int Value);

  // for obtaining the real position of each tab. This allows to change the order
  int pos_of_tab(_w_tab_xmapslab_ns::_tabs Tab){return Map_pos_of_tab[Tab];}

  public slots:
  void xrf_button_pushed_maps_parameters_slot(bool State);
  void xrf_changed_interpolation_type_slot(int Value);
  void xrf_button_pushed_palette_parameters_slot(bool State);

  void xrd_button_pushed_maps_parameters_slot(bool State);
  void xrd_changed_interpolation_type_slot(int Value);
  void xrd_button_pushed_palette_parameters_slot(bool State);

  protected slots:
  void tab_bar_clicked_slot(int Tab1);

  void add_filter_layer_slot(int Value);
  void remove_selected_layer_slot();
  void remove_all_layers_slot();
  //  void recompute_all_layers_slot();

  void xrf_update_parameters();
  void xrf_create_some_maps_slot();
  void xrf_create_all_maps_slot();
  void xrf_changed_view_name_slot(QString Text);
  void xrf_changed_normalization_slot(int State);
  void xrf_changed_position_normalization_slot(int Value);
  void xrf_changed_probe_slot(int Value);
  void xrf_changed_triangulation_add_corners_slot(int State);
  void xrf_changed_rbf_function_slot(int Value);

#ifdef ADVANCED
  void changed_color_model_slot(int Value);
  void changed_use_color1_slot(int State);
  void changed_use_color2_slot(int State);
  void changed_use_color3_slot(int State);
  void changed_use_position1_slot(int State);
  void changed_use_position2_slot(int State);
#endif

  //  void elements_update_widgets();

  void changed_selected_positions_slot();

  // compounds XRD
#ifdef XRD_ACTIVE
  void xrd_update_parameters();
  void xrd_create_some_maps_slot();
  void xrd_create_all_maps_slot();
  void xrd_changed_view_name_slot(QString Text);
  void xrd_changed_normalization_slot(int State);
  void xrd_changed_position_normalization_slot(int Value);
  void xrd_changed_probe_slot(int Value);
  void xrd_changed_triangulation_add_corners_slot(int State);
  void xrd_changed_rbf_function_slot(int Value);

#endif

  // compounds
#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
  void compounds_combination_update_parameters();
  void compounds_combination_create_combination_maps_slot();
  void compounds_combination_create_all_individual_maps_slot();
#endif

  //  void compounds_create_palette_slot();
  //  void compounds_change_row_palette_slot(int Row);

  //  void compounds_interpolation_type_slot(int Value);
  //  void compounds_state_changed_use_color1_slot(int State);
  //  void compounds_state_changed_use_color2_slot(int State);
  //  void compounds_state_changed_use_color3_slot(int State);
  //  void compounds_state_changed_use_position1_slot(int State);
  //  void compounds_state_changed_use_position2_slot(int State);

  //  void compounds_update_widgets();

  //
  void xrf_changed_palette_type_slot(int Index);
  void xrf_changed_palette_color_type_slot(int Index);
  void xrf_changed_num_intervals_slot(int Value);
  void xrf_changed_palette_color_assigning_slot(int Index);
  void xrf_palette_mutable_color_slot(QColor Color);
  void xrf_changed_palette_fixed_palettes_slot(QString Name);

  //
  void xrd_changed_palette_type_slot(int Index);
  void xrd_changed_palette_color_type_slot(int Index);
  void xrd_changed_num_intervals_slot(int Value);
  void xrd_changed_palette_color_assigning_slot(int Index);
  void xrd_palette_mutable_color_slot(QColor Color);
  void xrd_changed_palette_fixed_palettes_slot(QString Name);

  protected:
  void change_row_visibility(QGridLayout *Layout, int Row, bool Show);

  _window_xmapslab *Window=nullptr;

  QTabWidget *Tab_widget=nullptr;

  // layers tab
  QWidget *Widget_layers=nullptr;
  QVBoxLayout *Verticalbox_layers=nullptr;
  QComboBox *Combo_add_layer=nullptr;

  // elements tab
  QWidget *Widget_xrf=nullptr;
  QVBoxLayout *Verticalbox_xrf=nullptr;
  QListWidget *Listwidget_xrf_images=nullptr;
  QListWidget *Listwidget_xrf=nullptr;
  QPushButton *Button_xrf_create_some_maps=nullptr;
  QPushButton *Button_xrf_create_all_maps=nullptr;

  QComboBox *Combobox_xrf_interpolation_type=nullptr;
  QComboBox *Combobox_xrf_color_model=nullptr;
  QComboBox *Combobox_xrf_probe=nullptr;

  QCheckBox *Checkbox_xrf_use_color1=nullptr;
  QCheckBox *Checkbox_xrf_use_color2=nullptr;
  QCheckBox *Checkbox_xrf_use_color3=nullptr;

  QCheckBox *Checkbox_xrf_use_position1=nullptr;
  QCheckBox *Checkbox_xrf_use_position2=nullptr;

  QCheckBox *Checkbox_xrf_normalization=nullptr;

  QComboBox *Combobox_xrf_position_normalization_type=nullptr;

  QCheckBox *Checkbox_xrf_triangulation_add_corners=nullptr;

  QSlider *Slider_xrf_rbf_radius=nullptr;
  QComboBox *Combobox_xrf_rbf_function=nullptr;

  QComboBox *Combobox_xrf_palette=nullptr;

  QFrame *Frame_xrf_view_name=nullptr;
  QFrame *Frame_xrf_probe=nullptr;
  QFrame *Frame_xrf_interpolation_type=nullptr;
  QFrame *Frame_xrf_color_model=nullptr;
  QFrame *Frame_xrf_minimum_distance_parameters=nullptr;
  QFrame *Frame_xrf_normalization=nullptr;
  QFrame *Frame_xrf_normalization_position=nullptr;
  QFrame *Frame_xrf_triangulation_add_corners=nullptr;
  QFrame *Frame_xrf_rbf_radius=nullptr;
  QFrame *Frame_xrf_rbf_function=nullptr;

  //
  QLineEdit *Lineedit_xrf_view_name=nullptr;

  // compounds combination tab
#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
  QWidget *Widget_compounds_from_elements=nullptr;
  QVBoxLayout *Verticalbox_compounds_combination=nullptr;
  QListWidget *Listwidget_compounds_combination=nullptr;
  QPushButton *Button_compounds_combination_create_combination_maps=nullptr;
  QPushButton *Button_compounds_combination_create_all_individual_maps=nullptr;

  QComboBox *Combobox_compounds_combination_interpolation_type=nullptr;
  QComboBox *Combobox_compounds_combination_color_model=nullptr;
  QComboBox *Combobox_compounds_combination_probe=nullptr;

  QCheckBox *Checkbox_compounds_combination_use_color1=nullptr;
  QCheckBox *Checkbox_compounds_combination_use_color2=nullptr;
  QCheckBox *Checkbox_compounds_combination_use_color3=nullptr;

  QCheckBox *Checkbox_compounds_combination_use_position1=nullptr;
  QCheckBox *Checkbox_compounds_combination_use_position2=nullptr;

  QCheckBox *Checkbox_compounds_combination_normalization=nullptr;

  QComboBox *Combobox_compounds_combination_position_normalization_type=nullptr;

  QCheckBox *Checkbox_compounds_combination_triangulation_add_corners=nullptr;

  QSlider *Slider_compounds_combination_rbf_radius=nullptr;
  QComboBox *Combobox_compounds_combination_rbf_function=nullptr;

  QComboBox *Combobox_compounds_combination_palette=nullptr;

  QFrame *Frame_compounds_combination_view_name=nullptr;
  QFrame *Frame_compounds_combination_probe=nullptr;
  QFrame *Frame_compounds_combination_interpolation_type=nullptr;
  QFrame *Frame_compounds_combination_color_model=nullptr;
  QFrame *Frame_compounds_combination_minimum_distance_parameters=nullptr;
  QFrame *Frame_compounds_combination_normalization=nullptr;
  QFrame *Frame_compounds_combination_normalization_position=nullptr;
  QFrame *Frame_compounds_combination_triangulation_add_corners=nullptr;
  QFrame *Frame_compounds_combination_rbf_radius=nullptr;
  QFrame *Frame_compounds_combination_rbf_function=nullptr;

  //
  QLineEdit *Lineedit_compounds_combination_view_name=nullptr;
#endif

  // compounds tab
#ifdef XRD_ACTIVE
  QWidget *Widget_xrd=nullptr;
  QVBoxLayout *Verticalbox_xrd=nullptr;
  QListWidget *Listwidget_xrd_images=nullptr;
  QListWidget *Listwidget_xrd=nullptr;
  QPushButton *Button_xrd_create_some_maps=nullptr;
  QPushButton *Button_xrd_create_all_maps=nullptr;

  QComboBox *Combobox_xrd_interpolation_type=nullptr;
  QComboBox *Combobox_xrd_color_model=nullptr;
  QComboBox *Combobox_xrd_probe=nullptr;

  QCheckBox *Checkbox_xrd_use_color1=nullptr;
  QCheckBox *Checkbox_xrd_use_color2=nullptr;
  QCheckBox *Checkbox_xrd_use_color3=nullptr;

  QCheckBox *Checkbox_xrd_use_position1=nullptr;
  QCheckBox *Checkbox_xrd_use_position2=nullptr;

  QCheckBox *Checkbox_xrd_normalization=nullptr;

  QComboBox *Combobox_xrd_position_normalization_type=nullptr;

  QCheckBox *Checkbox_xrd_triangulation_add_corners=nullptr;

  QSlider *Slider_xrd_rbf_radius=nullptr;
  QComboBox *Combobox_xrd_rbf_function=nullptr;

  QComboBox *Combobox_xrd_palette=nullptr;

  QFrame *Frame_xrd_view_name=nullptr;
  QFrame *Frame_xrd_probe=nullptr;
  QFrame *Frame_xrd_interpolation_type=nullptr;
  QFrame *Frame_xrd_color_model=nullptr;
  QFrame *Frame_xrd_minimum_distance_parameters=nullptr;
  QFrame *Frame_xrd_normalization=nullptr;
  QFrame *Frame_xrd_normalization_position=nullptr;
  QFrame *Frame_xrd_triangulation_add_corners=nullptr;
  QFrame *Frame_xrd_rbf_radius=nullptr;
  QFrame *Frame_xrd_rbf_function=nullptr;

  QLineEdit *Lineedit_xrd_view_name=nullptr;
#endif

  // palettes tab
  QWidget *Widget_palettes=nullptr;
  QVBoxLayout *Verticalbox_palettes=nullptr;
  QListWidget *Listwidget_palettes=nullptr;

  QIcon Icon_discrete;
  QIcon Icon_continuous;
  QPixmap *Pixmap_palette_discrete=nullptr;
  QPixmap *Pixmap_palette_continuous=nullptr;

  // valid positions
  QWidget *Widget_valid_positions=nullptr;
  QVBoxLayout *Verticalbox_valid_positions=nullptr;
  _table_active_positions *Table_valid_positions=nullptr;

  // for obtaining the real position of each tab. This allows to change the order
  std::map<_w_tab_xmapslab_ns::_tabs,int> Map_pos_of_tab;

  // XRF
  int XRF_maps_parameters_num_rows;
  QFrame *Frame_xrf_maps_parameters=nullptr;
  QPushButton *Pushbutton_xrf_maps_parameters=nullptr;
  QGridLayout *Grid_xrf_maps_parameters=nullptr;
  bool XRF_show_maps_parameters=false;

  int XRF_palette_parameters_num_rows;
  QFrame *Frame_xrf_palette_parameters=nullptr;
  QPushButton *Pushbutton_xrf_palette_parameters=nullptr;
  QGridLayout *Grid_xrf_palette_parameters=nullptr;
  QSpinBox *Spinbox_xrf_palette_num_intervals=nullptr;

  bool XRF_show_palette_parameters=false;
  _palette_data_ns::_palette_type XRF_palette_type=_palette_data_ns::PALETTE_TYPE_DEFAULT;
  _palette_data_ns::_palette_color_type XRF_palette_color_type=_palette_data_ns::PALETTE_COLOR_TYPE_DEFAULT;
  _palette_data_ns::_palette_color_assigning_type XRF_palette_color_assigning=_palette_data_ns::PALETTE_COLOR_ASSIGNING_DEFAULT;
  //  _button_color_simple *Button_palette_mutable_color=nullptr;
  QColor XRF_palette_mutable_color=_palette_data_ns::MUTABLE_COLOR;
  QString XRF_palette_name_fixed_palette;
  int XRF_palette_discrete_num_intervals_value=_palette_data_ns::PALETTE_DISCRETE_MINIMUM_INTERVALS;
  int XRF_palette_continuous_num_intervals_value=_palette_data_ns::PALETTE_CONTINUOUS_MINIMUM_INTERVALS;

  // XRD
  int XRD_maps_parameters_num_rows;
  QFrame *Frame_xrd_maps_parameters=nullptr;
  QPushButton *Pushbutton_xrd_maps_parameters=nullptr;
  QGridLayout *Grid_xrd_maps_parameters=nullptr;
  bool XRD_show_maps_parameters=false;

  int XRD_palette_parameters_num_rows;
  QFrame *Frame_xrd_palette_parameters=nullptr;
  QPushButton *Pushbutton_xrd_palette_parameters=nullptr;
  QGridLayout *Grid_xrd_palette_parameters=nullptr;
  QSpinBox *Spinbox_xrd_palette_num_intervals=nullptr;

  bool XRD_show_palette_parameters=false;
  _palette_data_ns::_palette_type XRD_palette_type=_palette_data_ns::PALETTE_TYPE_DEFAULT;
  _palette_data_ns::_palette_color_type XRD_palette_color_type=_palette_data_ns::PALETTE_COLOR_TYPE_DEFAULT;
  _palette_data_ns::_palette_color_assigning_type XRD_palette_color_assigning=_palette_data_ns::PALETTE_COLOR_ASSIGNING_DEFAULT;
  //  _button_color_simple *Button_palette_mutable_color=nullptr;
  QColor XRD_palette_mutable_color=_palette_data_ns::MUTABLE_COLOR;
  QString XRD_palette_name_fixed_palette;
  int XRD_palette_discrete_num_intervals_value=_palette_data_ns::PALETTE_DISCRETE_MINIMUM_INTERVALS;
  int XRD_palette_continuous_num_intervals_value=_palette_data_ns::PALETTE_CONTINUOUS_MINIMUM_INTERVALS;

  // xrf files tab
  //  QWidget *Widget_xrd_files=nullptr;
  //  QVBoxLayout *Verticalbox_xrd_files=nullptr;
  //  _table_pigments_files *Table_xrd_files=nullptr;
};

#endif

