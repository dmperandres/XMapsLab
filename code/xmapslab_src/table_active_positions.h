#ifndef TABLE_VALID_POSITIONS_H
#define TABLE_VALID_POSITIONS_H

#include <QTableWidget>
#include <QPushButton>
#include <QPixmap>
#include <QIcon>
#include <QSize>
#include <QHeaderView>
#include <QDropEvent>
#include <iostream>
#include <vector>

//#include "data_xrf.h"

//#include "table.h"

#include "button_icon.h"

namespace _table_active_positions_ns
{
  const int NUM_BUTTONS=1;

  const int NUM_COLS=1;
  const int NUM_ROWS=5;
  const int WIDTH_BUTTON_COLUMN=50;

  enum{VISIBILITY,WRITABILITY};

  class _icon_state {
  public:
      QIcon Icon_on;
      QIcon Icon_off;
  };

  struct _info {
    bool States[NUM_BUTTONS]={true};
    float Transparence=0;
    QString Name="NONE";
  };
}

class _w_tab_xmapslab;

class _table_active_positions: public QTableWidget
{
Q_OBJECT

public:
//  std::vector<_table_active_positions_ns::_info> Vec_info;

  _table_active_positions(std::string Name1,_w_tab_xmapslab *W_tab1);
  ~_table_active_positions();
  void change_button(int Row);
  void update_table(const std::vector<bool> &Vec_active_positionss);
  void remove_all();

public slots:
  void button_clicked_slot(int Row,int Col);
  void header_clicked_slot(int Col);

protected:

  _w_tab_xmapslab *Parent=nullptr;

  QList<QTableWidgetItem*> get_row(int Row);
  void set_row(int row, const QList<QTableWidgetItem*>& rowItems);

  std::vector<_table_active_positions_ns::_icon_state> Vec_icons;

  std::string Name;
  uint Num_rows;
  uint Active_row;
};

#endif
