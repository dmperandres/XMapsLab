//LIC

#ifndef TABLE_POSITIONS_H
#define TABLE_POSITIONS_H

#include <QTableWidget>
#include <QPushButton>
#include <QPixmap>
#include <QIcon>
#include <QSize>
#include <QHeaderView>
#include <QDropEvent>
#include <QMessageBox>

#include <iostream>
#include <vector>
//#include <deque>

#include "common.h"

#include "vertex.h"

//#include "table.h"
//#include "button_icon.h"

namespace _table_positions_ns
{
//  const int NUM_BUTTONS=2;

  const int NUM_COLS=2;
//  const int NUM_ROWS=5;
//  const int WIDTH_BUTTON_COLUMN=50;

//  enum{VISIBILITY,WRITABILITY};

//  class _icon_state {
//  public:
//      QIcon Icon_on;
//      QIcon Icon_off;
//  };

//  struct _info {
//    _button_icon *Buttons[NUM_BUTTONS]={nullptr,nullptr};
//    bool States[NUM_BUTTONS]={true,true};
//    float Transparence=0;
//    QString Name="NONE";
//  };
}

class _window_positions;

//HEA

class _table_positions: public QTableWidget
{
Q_OBJECT

public:

  _table_positions(_window_positions *Window1);
  ~_table_positions();

//  void change_row(int Row);

//  void remove_widget(QWidget *Widget);

//  void change_button(int Row,int Col);
//  void change_button(int Row,int Col,bool State);

//  void add_row(_table_positions_ns::_info Info, int Row=-1);

  void update_table(std::vector<_common_ns::_position_data> &Vec_positions);

//  void move_layers_backward(int Initial_row,int Destination_row);
//  void move_layers_forward(int Initial_row,int Destination_row);

//  void remove_row(int Row);

public slots:
//  void button_clicked_slot(int Row,int Col);
  void vertical_header_clicked_slot(int Row);
  void cell_clicked_slot(int Row,int Col);

protected:
  _window_positions *Window;

  int Selected_row=-1;
  bool Active=false;
};

#endif
