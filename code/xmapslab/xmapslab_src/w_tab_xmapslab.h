//LIC

#ifndef WIDGET_TAB_XMAPSLAB_H
#define WIDGET_TAB_XMAPSLAB_H

#include <QWidget>
#include <QVBoxLayout>
#include <QComboBox>
#include <QListWidget>
#include <QPushButton>
#include <QIcon>
#include <QProgressDialog>
#include <QStyle>
#include <QButtonGroup>

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
  enum class _tabs:unsigned char {POSITIONS_TAB, LAYERS_TAB, DATA_TAB, TAB_LAST,TAB_PALETTES};
  const QString VIEW_NAME_DEFAULT="view1";
}

//HEA
class _w_tab_xmapslab: public QTabWidget
{
  Q_OBJECT
  public:
  _table_layers *Table_layers=nullptr;

  _w_tab_xmapslab(_window_xmapslab *Window1);
  ~_w_tab_xmapslab();

  void initialize();

  void create_selected_positions_widget();
  void create_layers_widget();
  void create_data_widget();
  void create_compounds_from_elements_widget();

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

  void add_element(std::string Type, std::string Name);
  void remove_all();

#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
  void add_compound_from_elements(std::string Name);
  void remove_all_compound_from_elements();
#endif

  void remove_all_positions();

  void change_buttons_state(bool State){
    if (Button_create_some_maps!=nullptr){
      Button_create_some_maps->setEnabled(State);
    }
    if (Button_create_all_maps!=nullptr){
      Button_create_all_maps->setEnabled(State);
    }
  }

  void reverse_col(int Col);

  void change_active_position(int Position);
  bool active_position(int Row);

  void add_active_positions(const std::vector<bool> &Vec_active_positions);

  _window_xmapslab* window(){return Window;}

  //
  //  void update_widget();

  void set_rbf_epsilon(int Value);

  // for obtaining the real position of each tab. This allows to change the order
  int pos_of_tab(_w_tab_xmapslab_ns::_tabs Tab){return Map_pos_of_tab[Tab];}

  //
  void adjust_interpolation_options(bool Masks_ids_image_loaded);

  public slots:
  void button_pushed_show_maps_parameters_slot(bool State);
  void changed_interpolation_type_slot(int Value);
  void button_pushed_show_palette_parameters_slot(bool State);

  protected slots:
  void tab_bar_clicked_slot(int Tab1);

  void add_filter_layer_slot(int Value);
  void remove_selected_layer_slot();
  void remove_all_layers_slot();
  //  void recompute_all_layers_slot();

  void update_parameters();
  void create_some_maps_slot();
  void create_all_maps_slot();
  void changed_view_name_slot(QString Text);
  void changed_distance_normalization_slot(int State);
  void changed_position_normalization_slot(int State);
  void changed_probe_slot(int Value);
  void changed_triangulation_add_corners_slot(int State);
  void changed_rbf_function_slot(int Value);

  // void changed_color_model_slot(int Value);

  void changed_mhd_color_position_slot(int Id, bool Checked);


  void changed_selected_positions_slot();
  // compounds

#ifdef COMPOUNDS_FROM_ELEMENTS_ACTIVE
  void compounds_combination_update_parameters();
  void compounds_combination_create_combination_maps_slot();
  void compounds_combination_create_all_individual_maps_slot();
#endif

  //
  void changed_palette_type_slot(int Index);
  void changed_palette_color_type_slot(int Index);
  void changed_palette_num_intervals_slot(int Value);
  void changed_palette_zero_color_slot(int Index);
  void changed_palette_color_assigning_slot(int Index);
  void changed_palette_fixed_color_slot(QColor Color);
  void changed_palette_fixed_palettes_slot(QString Name);

  protected:
  void change_row_visibility(QGridLayout *Layout, int Row, bool Show);

  _window_xmapslab *Window=nullptr;

  QTabWidget *Tab_widget=nullptr;

  // layers tab
  QWidget *Widget_layers=nullptr;
  QVBoxLayout *Verticalbox_layers=nullptr;
  QComboBox *Combo_add_layer=nullptr;

  // elements tab
  QWidget *Widget_data=nullptr;
  QVBoxLayout *Verticalbox_data=nullptr;
  QListWidget *Listwidget_images=nullptr;
  QListWidget *ListWidget_data=nullptr;
  QPushButton *Button_create_some_maps=nullptr;
  QPushButton *Button_create_all_maps=nullptr;

  QComboBox *Combobox_interpolation_type=nullptr;
  QComboBox *Combobox_color_model=nullptr;
  QComboBox *Combobox_probe=nullptr;

  std::vector<QCheckBox*> Vec_checkbox_mhd_parameters;

  std::map<std::string,QFrame*> Map_interpolation_frames;

  QCheckBox *Checkbox_distance_normalization=nullptr;

  // QComboBox *Combobox_position_normalization_type=nullptr;
  QCheckBox *Checkbox_position_normalization=nullptr;

  QCheckBox *Checkbox_triangulation_add_corners=nullptr;

  QSlider *Slider_rbf_radius=nullptr;
  QComboBox *Combobox_rbf_function=nullptr;

  QComboBox *Combobox_palette=nullptr;

  QFrame *Frame_view_name=nullptr;
  QFrame *Frame_probe=nullptr;
  QFrame *Frame_interpolation_type=nullptr;
  QFrame *Frame_color_model=nullptr;
  QFrame *Frame_minimum_distance_parameters=nullptr;
  QFrame *Frame_normalization=nullptr;
  QFrame *Frame_normalization_position=nullptr;
  QFrame *Frame_triangulation_add_corners=nullptr;
  QFrame *Frame_rbf_radius=nullptr;
  QFrame *Frame_rbf_function=nullptr;

  //
  QLineEdit *Lineedit_label=nullptr;

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

  //
  bool Show_maps_parameters=false;
  int Maps_parameters_num_rows;
  QFrame *Frame_maps_parameters=nullptr;
  QPushButton *Pushbutton_show_maps_parameters=nullptr;
  QGridLayout *Grid_maps_parameters=nullptr;

  // mhd
  QFrame *Frame_mhd_parameters=nullptr;
  QGridLayout *Grid_mhd_parameters=nullptr;

  // mhd
  QFrame *Frame_rbf_parameters=nullptr;
  QGridLayout *Grid_rbf_parameters=nullptr;

  // triangulation
  QFrame *Frame_triangulation_parameters=nullptr;
  QGridLayout *Grid_triangulation_parameters=nullptr;

  // segmentation-based value
  QFrame *Frame_segmentation_based_value_parameters=nullptr;
  QGridLayout *Grid_segmentation_based_value_parameters=nullptr;


  int Palette_parameters_num_rows;
  QFrame *Frame_palette_parameters=nullptr;
  QPushButton *Pushbutton_show_palette_parameters=nullptr;
  QGridLayout *Grid_palette_parameters=nullptr;
  QSpinBox *Spinbox_palette_num_intervals=nullptr;

  bool Show_palette_parameters=false;
  _palette_data_ns::_palette_type Palette_type=_palette_data_ns::PALETTE_TYPE_DEFAULT;
  _palette_data_ns::_palette_color_type Palette_color_type=_palette_data_ns::PALETTE_COLOR_TYPE_DEFAULT;
  _palette_data_ns::_palette_color_assigning_type Palette_color_assigning=_palette_data_ns::PALETTE_COLOR_ASSIGNING_DEFAULT;
  //  _button_color_simple *Button_palette_fixed_color=nullptr;
  _common_ns::_zero_color Palette_zero_color=_common_ns::ZERO_COLOR_DEFAULT;
  QColor Palette_fixed_color=_palette_data_ns::FIXED_COLOR;
  QString Palette_name_fixed_palette;
  int Palette_discrete_num_intervals_value=_palette_data_ns::PALETTE_DISCRETE_MINIMUM_INTERVALS;
  int Palette_continuous_num_intervals_value=_palette_data_ns::PALETTE_CONTINUOUS_MINIMUM_INTERVALS;
};

#endif



