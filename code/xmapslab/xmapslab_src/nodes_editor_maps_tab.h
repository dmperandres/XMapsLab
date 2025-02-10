//LIC

#ifndef NODES_EDITOR_MAPS_TAB_H
#define NODES_EDITOR_MAPS_TAB_H

#include <QDialog>
#include <QListWidget>
#include <QGroupBox>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QComboBox>
#include <QFrame>
#include <QPushButton>
#include <string>
#include "palette_data.h"

// #include "line_edit.h"

class _window_xmapslab;

//HEA
// class for the tab that includes the images in the XRF and XRD widgets

class _nodes_editor_maps_tab: public QWidget
{
  Q_OBJECT

public:
        _nodes_editor_maps_tab(_window_xmapslab *Window1, QWidget *Parent = nullptr);
  void  set_item(std::string Name);
  void  set_selected_item(int Pos);
  void  clear(){Maps_list->clear();}

  QString selected_item();

  void insert_maps();
  void remove_maps();

  void enable_palette(){Frame_lab_palette_parameters->setEnabled(true);}
  void disable_palette(){Frame_lab_palette_parameters->setEnabled(false);}

  void enable_add_to_layers_button(){Button_add_map_to_layers->setEnabled(true);}
  void disable_add_to_layers_button(){Button_add_map_to_layers->setEnabled(false);}

protected slots:
  void item_clicked(QListWidgetItem *);
  void add_map_to_layers_slot();

  //
  void lab_changed_palette_type_slot(int Index);
  void lab_changed_palette_color_type_slot(int Index);
  void lab_changed_num_intervals_slot(int Value);
  void lab_changed_palette_color_assigning_slot(int Index);
  void lab_changed_palette_fixed_color_slot(QColor Color);
  void lab_changed_palette_fixed_palettes_slot(QString Name);
  void lab_button_pushed_palette_parameters_slot(bool State);

private:
  void change_row_visibility(QGridLayout *Layout, int Row, bool Show);
void lab_update_parameters();

  QListWidget *Maps_list=nullptr;
  QPushButton *Button_add_map_to_layers=nullptr;
  _window_xmapslab *Window=nullptr;

  //
  int LAB_palette_parameters_num_rows;
  QFrame *Frame_lab_palette_parameters=nullptr;
  QPushButton *Pushbutton_lab_palette_parameters=nullptr;
  QGridLayout *Grid_lab_palette_parameters=nullptr;
  QSpinBox *Spinbox_lab_palette_num_intervals=nullptr;

  bool LAB_show_palette_parameters=false;
  _palette_data_ns::_palette_type LAB_palette_type=_palette_data_ns::PALETTE_TYPE_DEFAULT;
  _palette_data_ns::_palette_color_type LAB_palette_color_type=_palette_data_ns::PALETTE_COLOR_TYPE_DEFAULT;
  _palette_data_ns::_palette_color_assigning_type LAB_palette_color_assigning=_palette_data_ns::PALETTE_COLOR_ASSIGNING_DEFAULT;
  //  _button_color_simple *Button_palette_mutable_color=nullptr;
  QColor LAB_palette_fixed_color=_palette_data_ns::FIXED_COLOR;
  QString LAB_palette_name_fixed_palette;
  int LAB_palette_discrete_num_intervals_value=_palette_data_ns::PALETTE_DISCRETE_MINIMUM_INTERVALS;
  int LAB_palette_continuous_num_intervals_value=_palette_data_ns::PALETTE_CONTINUOUS_MINIMUM_INTERVALS;
};

#endif
