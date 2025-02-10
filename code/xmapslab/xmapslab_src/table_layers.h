//LIC

#ifndef TABLE_LAYERS_H
#define TABLE_LAYERS_H

#include <QTableWidget>
#include <QPushButton>
#include <QPixmap>
#include <QIcon>
#include <QSize>
#include <QHeaderView>
#include <QDropEvent>
#include <iostream>
#include <vector>

#include "table.h"
#include "button_icon.h"

namespace _table_layers_ns
{
  const int NUM_BUTTONS=2;

#ifdef STATISTIC_GRAPHS_ACTIVE
  const int NUM_COLS=2;
#else
  const int NUM_COLS=1;
#endif

  const int NUM_ROWS=5;
  const int WIDTH_BUTTON_COLUMN=50;

  enum{VISIBILITY,WRITABILITY};

  class _icon_state {
  public:
      QIcon Icon_on;
      QIcon Icon_off;
  };

  struct _info {
    _button_icon *Buttons[NUM_BUTTONS]={nullptr,nullptr};
    bool States[NUM_BUTTONS]={true,true};
    float Transparence=0;
    QString Name="NONE";
  };
}

class _w_tab_xmapslab;

//HEA

class _table_layers: public _table
{
Q_OBJECT

public:
  std::vector<_table_layers_ns::_info> Vec_info;

  _table_layers(std::string Name1,_w_tab_xmapslab *W_tab1);
  ~_table_layers();

  void change_row(int Row);

  void remove_widget(QWidget *Widget);

  void change_button(int Row,int Col);  
  void change_button(int Row,int Col,bool State);

  void add_row(_table_layers_ns::_info Info, int Row=-1);

  void update_table();

  void move_layers_backward(int Initial_row,int Destination_row);
  void move_layers_forward(int Initial_row,int Destination_row);

  void remove_row(int Row);

public slots:
  void button_clicked_slot(int Row,int Col);
  void cell_clicked_slot(int Row,int Col);
#ifdef STATISTIC_GRAPHS_ACTIVE
  void header_clicked_slot(int Col);
#endif

protected:
  void dropEvent(QDropEvent *Event);
  // for update
  void remove_all_rows();

  QList<QTableWidgetItem*> get_row(int Row);
  void set_row(int row, const QList<QTableWidgetItem*>& rowItems);

  std::vector<_table_layers_ns::_icon_state> Vec_icons;

  _w_tab_xmapslab *W_tab=nullptr;

  uint Num_rows;
  uint Active_row;
};

#endif
