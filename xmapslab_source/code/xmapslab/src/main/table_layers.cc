/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#include "table_layers.h"
#include "w_tab.h"

/*************************************************************************/

_table_layers::_table_layers(std::string Name1,_w_tab *W_tab1):_table(Name1,W_tab1)
{
  W_tab=W_tab1;

  setColumnCount(_table_layers_ns::NUM_COLS+1);
  setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
  setHorizontalHeaderLabels(QString("View;Name").split(";"));

  QFont Font=font();
  QFontMetrics Font_metric(Font);
  int Width_char1=Font_metric.horizontalAdvance("_View_");

  setColumnWidth(0,Width_char1);
  // stretch the last column to the father size
  horizontalHeader()->setStretchLastSection(true);

  // to allow drag and drop
  setDragEnabled(true);
  setAcceptDrops(true);
  viewport()->setAcceptDrops(true);
  setDragDropOverwriteMode(false);
  setDropIndicatorShown(true);
  setDragDropMode(QAbstractItemView::InternalMove);
  setSelectionMode(QAbstractItemView::SingleSelection);
  setSelectionBehavior(QAbstractItemView::SelectRows);

  setColumnCount(_table_layers_ns::NUM_COLS+1);

  // read icons
  Vec_icons.resize(_table_layers_ns::NUM_COLS);
  QPixmap Pixmap;
  Pixmap.load(":/common/icons/button_visible.png");
  Vec_icons[_table_layers_ns::VISIBILITY].Icon_on.addPixmap(Pixmap);
  Pixmap.load(":/common/icons/button_invisible.png");
  Vec_icons[_table_layers_ns::VISIBILITY].Icon_off.addPixmap(Pixmap);

  connect(this,SIGNAL(cellClicked(int,int)),this,SLOT(cell_clicked_slot(int,int)));
}

_table_layers::~_table_layers()
{
}

/*************************************************************************/

void _table_layers::dropEvent(QDropEvent *Event)
{
  Q_UNUSED(Event)
  int Initial_row=currentRow();

  QTableWidgetItem *Item=itemAt(Event->position().x(), Event->position().y());

  if (Item!=nullptr){
    int Destination_row=Item->row();
    if (Destination_row<Initial_row) move_layers_forward(Initial_row,Destination_row);
    else move_layers_backward(Initial_row,Destination_row);
  }
  else{
    move_layers_backward(Initial_row,rowCount()-1);
  }
}

/*************************************************************************/
// The moved layer is moved to the end direction

void _table_layers::move_layers_backward(int Initial_row,int Destination_row)
{
  _table_layers_ns::_info Info=Vec_info[Initial_row];

  for (int i=Initial_row;i<Destination_row;i++){
    Vec_info[i]=Vec_info[i+1];
  }
  Vec_info[Destination_row]=Info;

  update_table();
  setCurrentCell(Destination_row,2);

  W_tab->move_layers_backward(Initial_row,Destination_row);
}

/*************************************************************************/
// The moved layer is moved to the start direction

void _table_layers::move_layers_forward(int Initial_row,int Destination_row)
{
  _table_layers_ns::_info Info=Vec_info[Initial_row];

  for (int i=Initial_row;i>Destination_row;i--){
    Vec_info[i]=Vec_info[i-1];
  }
  Vec_info[Destination_row]=Info;

  update_table();
  setCurrentCell(Destination_row,2);

  W_tab->move_layers_forward(Initial_row,Destination_row);
}

/*************************************************************************/

QList<QTableWidgetItem*> _table_layers::get_row(int Row)
{
  QList<QTableWidgetItem*> rowItems;
  for (int col = 0; col < columnCount(); ++col){
    rowItems << takeItem(Row, col);
  }
  return rowItems;
}

/*************************************************************************/

void _table_layers::set_row(int row, const QList<QTableWidgetItem*>& rowItems)
{
  for (int col = 0; col < columnCount(); ++col){
    setItem(row, col, rowItems.at(col));
  }
}

/*************************************************************************/

void _table_layers::update_table()
{
  // delete all the rows
  for (int i=rowCount()-1;i>=0;i--) removeRow(i);

  QTableWidgetItem *Item;
  _button_icon *Button;
  for (unsigned int i=0;i<Vec_info.size();i++){
    insertRow(i);

    for (int j=0;j<_table_layers_ns::NUM_COLS;j++){
      Button=new _button_icon(i,j);
      if (Vec_info[i].States[j]==true) Button->setIcon(Vec_icons[j].Icon_on);
      else Button->setIcon(Vec_icons[j].Icon_off);

      connect(Button,SIGNAL(change_state(int,int)),this,SLOT(button_clicked_slot(int,int)));
      setCellWidget(i,j,(QWidget*)Button);
    }

    Item = new QTableWidgetItem(Vec_info[i].Name);
    Item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
    setItem(i,_table_layers_ns::NUM_COLS,Item);
  }
}

/*************************************************************************/

void _table_layers::button_clicked_slot(int Row,int Col)
{
  if (Col==0){ // the eyes
    int Counter=0;
    for (unsigned int i=0;i<Vec_info.size();i++){
      if (Vec_info[i].States[0]==true){
        Counter++;
      }
    }
    if (Counter>6){
      if (Vec_info[Row].States[0]==false){
        QMessageBox MsgBox(this);
        MsgBox.setText("The maximum number of simultaneous visible layers is 7");
        MsgBox.exec();
        return;
      }
    }
  }

  W_tab->change_button_state(Row,Col);

  change_button(Row,Col);
  selectRow(Row);

  W_tab->show_layer_parameters(Row,Col);

}

/*************************************************************************/

void _table_layers::cell_clicked_slot(int Row,int Col)
{
  if (Col==_table_layers_ns::NUM_COLS){
    selectRow(Row);
    W_tab->show_layer_parameters(Row,Col);
  }
}

/*************************************************************************/
/*************************************************************************/

void _table_layers::change_button(int Row,int Col)
{
  if (Row<rowCount()){
    _button_icon *Button=static_cast<_button_icon *>(cellWidget(Row,Col));

    if (Vec_info[Row].States[Col]==true){
      Button->setIcon(Vec_icons[Col].Icon_off);
    }
    else{
      Button->setIcon(Vec_icons[Col].Icon_on);
    }

    Vec_info[Row].States[Col]=!Vec_info[Row].States[Col];
  }
}

/*************************************************************************/

void _table_layers::change_button(int Row,int Col,bool State)
{
  if (Row<rowCount()){
    _button_icon *Button=static_cast<_button_icon *>(cellWidget(Row,Col));

    Vec_info[Row].States[Col]=State;

    if (Vec_info[Row].States[Col]==true){
      Button->setIcon(Vec_icons[Col].Icon_on);
    }
    else{
      Button->setIcon(Vec_icons[Col].Icon_off);
    }
  }
}

/*************************************************************************/

void _table_layers::add_row(_table_layers_ns::_info Info,int Row)
{
  int Pos;

  // add the row AFTER the indicated value

  if (Row==-1 || Row==(rowCount()-1)) Pos=rowCount();
  else Pos=Row+1;

  // order elements
  Vec_info.push_back(Info);
  for (int i=int(Vec_info.size())-1;i>Pos;i--){
    Vec_info[i]=Vec_info[i-1];
  }
  Vec_info[Pos]=Info;

  update_table();

  selectRow(Pos);
}

/*************************************************************************/

void _table_layers::remove_row(int Row)
{
  for (int i=Row;i<rowCount()-1;i++){
    Vec_info[i]=Vec_info[i+1];
  }
  Vec_info.pop_back();

  update_table();
}

