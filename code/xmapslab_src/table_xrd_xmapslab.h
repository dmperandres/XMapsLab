#ifndef TABLE_XRD_XMAPSLAB_H
#define TABLE_XRD_XMAPSLAB_H

#include <QTableWidget>
#include <QPushButton>
#include <QPixmap>
#include <QIcon>
#include <QSize>
#include <QHeaderView>
#include <QDropEvent>
#include <QString>
#include <iostream>
#include <QTableWidgetItem>

#include <vector>

//#include "table.h"
#include "button_icon.h"

#include "common.h"

using namespace std;

namespace _table_xrd_xmapslab_ns
{
  const int NUM_BUTTONS=2;

  const int NUM_COLS=2;
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

class _window_xmapslab;

class _table_xrd_xmapslab: public QTableWidget
{
Q_OBJECT

public:
  vector<_table_xrd_xmapslab_ns::_info> Vec_info;

  _table_xrd_xmapslab(_window_xmapslab *Window1);
  ~_table_xrd_xmapslab();

  void set_data(vector<string> Row_names, vector<string> Col_names,vector<vector<_common_ns::_result_linear_regresion>> &Result_linear_regresion);

public slots:
  void cell_clicked_slot(int Row,int Col);

protected:
  _window_xmapslab *Window=nullptr;
};

#endif
