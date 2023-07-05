/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#ifndef WIDGET_TAB
#define WIDGET_TAB

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
#include "dialog_create_palette.h"
#include "layer_compound_combination.h"
#include "layer_map.h"

class _window;

namespace _w_tab_ns {
  enum class _tabs:unsigned char {POSITIONS_TAB, LAYERS_TAB, ELEMENTS_TAB, COMPOUNDS_FROM_XRF_TAB, COMPOUNDS_XRD_TAB, TAB_LAST,TAB_PALETTES};
  const QString VIEW_NAME_DEFAULT="view1";
}

/*************************************************************************/

class _w_tab: public QTabWidget
{
Q_OBJECT
public:
  _table_layers *Table_layers=nullptr;

  _w_tab(_window *Window1);
  ~_w_tab();

  void initialize();

  void create_layers_widget();
  void create_elements_widget();
  void create_compounds_from_elements_widget();
  void create_compounds_widget();
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

  void add_element(std::string Name);

  void add_compound_combination(std::string Name);

  void remove_all_images();
  void remove_all_elements();

  void remove_all_xrf_files();

  void elements_change_buttons_state(bool State){
    Button_elements_create_some_maps->setEnabled(State);
    Button_elements_create_all_maps->setEnabled(State);
  }

  void reverse_col(int Col);

  void change_active_position(int Position);
  bool active_position(int Row);

  void add_active_positions(const std::vector<bool> &Vec_active_positions);

  _window* window(){return Window;}

  //
//  void update_elements_widget();

  void set_rbf_epsilon(int Value);

  // for obtaining the real position of each tab. This allows to change the order
  int pos_of_tab(_w_tab_ns::_tabs Tab){return Map_pos_of_tab[Tab];}

public slots:
  void changed_interpolation_type_slot(int Value);

protected slots:
  void tab_bar_clicked_slot(int Tab1);

  void add_filter_layer_slot(int Value);
  void remove_selected_layer_slot();
  void remove_all_layers_slot();
//  void recompute_all_layers_slot();

  void elements_update_parameters();
  void elements_create_some_maps_slot();
  void elements_create_all_maps_slot();  
//  void elements_create_palette_slot();
//  void elements_change_row_palette_slot(int Row);

  void changed_view_name_slot(QString Text);
  void changed_normalization_slot(int State);
  void changed_position_normalization_slot(int Value);
  void changed_probe_slot(int Value);
  void changed_palette_slot(int Value);
  void changed_triangulation_add_corners_slot(int State);
  void changed_rbf_function_slot(int Value);
//  void changed_rbf_fast_radius_slot(int Value);

//  void elements_update_widgets();

  void changed_selected_positions_slot();

  // compounds XRD

  // compounds
  void compounds_combination_update_parameters();
  void compounds_combination_create_combination_maps_slot();
  void compounds_combination_create_all_individual_maps_slot();

  //  void compounds_create_palette_slot();
//  void compounds_change_row_palette_slot(int Row);

//  void compounds_interpolation_type_slot(int Value);
//  void compounds_state_changed_use_color1_slot(int State);
//  void compounds_state_changed_use_color2_slot(int State);
//  void compounds_state_changed_use_color3_slot(int State);
//  void compounds_state_changed_use_position1_slot(int State);
//  void compounds_state_changed_use_position2_slot(int State);

//  void compounds_update_widgets();

protected:
  _window *Window=nullptr;

  QTabWidget *Tab_widget=nullptr;

  // layers tab
  QWidget *Widget_layers=nullptr;
  QVBoxLayout *Verticalbox_layers=nullptr;
  QComboBox *Combo_add_layer=nullptr;

  // elements tab
  QWidget *Widget_elements=nullptr;
  QVBoxLayout *Verticalbox_elements=nullptr;
  QListWidget *Listwidget_elements_images=nullptr;
  QListWidget *Listwidget_elements=nullptr;
  QPushButton *Button_elements_create_some_maps=nullptr;
  QPushButton *Button_elements_create_all_maps=nullptr;

  QComboBox *Combobox_elements_interpolation_type=nullptr;
  QComboBox *Combobox_elements_color_model=nullptr;
  QComboBox *Combobox_elements_probe=nullptr;

  QCheckBox *Checkbox_elements_use_color1=nullptr;
  QCheckBox *Checkbox_elements_use_color2=nullptr;
  QCheckBox *Checkbox_elements_use_color3=nullptr;

  QCheckBox *Checkbox_elements_use_position1=nullptr;
  QCheckBox *Checkbox_elements_use_position2=nullptr;

  QCheckBox *Checkbox_elements_normalization=nullptr;

  QComboBox *Combobox_elements_position_normalization_type=nullptr;

  QCheckBox *Checkbox_elements_triangulation_add_corners=nullptr;

  QSlider *Slider_elements_rbf_radius=nullptr;
  QComboBox *Combobox_elements_rbf_function=nullptr;

  QComboBox *Combobox_elements_palette=nullptr;

  QFrame *Frame_elements_view_name=nullptr;
  QFrame *Frame_elements_probe=nullptr;
  QFrame *Frame_elements_interpolation_type=nullptr;
  QFrame *Frame_elements_color_model=nullptr;
  QFrame *Frame_elements_minimum_distance_parameters=nullptr;
  QFrame *Frame_elements_normalization=nullptr;
  QFrame *Frame_elements_normalization_position=nullptr;
  QFrame *Frame_elements_triangulation_add_corners=nullptr;
  QFrame *Frame_elements_rbf_radius=nullptr;
  QFrame *Frame_elements_rbf_function=nullptr;

  //
  QLineEdit *Lineedit_elements_view_name=nullptr;

  // compounds combination tab
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

  // compounds tab

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
  std::map<_w_tab_ns::_tabs,int> Map_pos_of_tab;

  // xrf files tab
//  QWidget *Widget_xrd_files=nullptr;
//  QVBoxLayout *Verticalbox_xrd_files=nullptr;
//  _table_pigments_files *Table_xrd_files=nullptr;
};

#endif

