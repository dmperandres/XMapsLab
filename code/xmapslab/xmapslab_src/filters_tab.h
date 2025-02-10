//LIC

#ifndef FILTERS_TAB_H
#define FILTERS_TAB_H

#include <QDialog>
#include <QListWidget>
#include <QGroupBox>
#include <QSpinBox>
#include <QVBoxLayout>
#include <string>

#include "map_list.h"

class _window_xmapslab;

//HEA

class _filters_tab: public QWidget
{
Q_OBJECT

public:
  _filters_tab(_window_xmapslab *Window1, QWidget *Parent = nullptr);
  void  set_item(std::string Name);
  void  insert_widgets();
  void  remove_widgets();
  void  set_selected_item(int Pos);
  void  clear(){Filters_list->clear();}

  void insert_filters();
  void remove_filters();

protected slots:
  void item_clicked(QListWidgetItem *);

private:
  QGroupBox *Group_box_filters=nullptr;
  QListWidget *Filters_list=nullptr;
  QVBoxLayout *Vertical_parameters=nullptr;
  _window_xmapslab *Window=nullptr;
};

#endif
