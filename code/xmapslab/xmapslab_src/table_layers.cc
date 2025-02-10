//LIC

#include "table_layers.h"
#include "w_tab_xmapslab.h"

//HEA

_table_layers::_table_layers(std::string Name1,_w_tab_xmapslab *W_tab1):_table(Name1,W_tab1)
{
  W_tab=W_tab1;

  // setTextElideMode(Qt::ElideNone);
  setWordWrap(false);

  setColumnCount(_table_layers_ns::NUM_COLS+1);
  setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
#ifdef STATISTIC_GRAPHS_ACTIVE
  setHorizontalHeaderLabels(QString("View;Graph;Name").split(";"));
#else
  setHorizontalHeaderLabels(QString("View;Name").split(";"));
#endif

  QFont Font=font();
  QFontMetrics Font_metric(Font);
  int Width_char1=Font_metric.horizontalAdvance("_View_");
#ifdef STATISTIC_GRAPHS_ACTIVE
  int Width_char2=Font_metric.horizontalAdvance("_Graph_");
#endif


  setColumnWidth(0,Width_char1);
#ifdef STATISTIC_GRAPHS_ACTIVE
  setColumnWidth(1,Width_char2);
#endif
  // stretch the last column to the father size
  horizontalHeader()->setStretchLastSection(true);

#ifdef STATISTIC_GRAPHS_ACTIVE
  connect(horizontalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(header_clicked_slot(int)));
#endif

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

#ifdef STATISTIC_GRAPHS_ACTIVE
  Pixmap.load(":/common/icons/button_write.png");
  Vec_icons[_table_layers_ns::WRITABILITY].Icon_on.addPixmap(Pixmap);
  Pixmap.load(":/common/icons/button_no_write");
  Vec_icons[_table_layers_ns::WRITABILITY].Icon_off.addPixmap(Pixmap);
#endif

  connect(this,SIGNAL(cellClicked(int,int)),this,SLOT(cell_clicked_slot(int,int)));
}


_table_layers::~_table_layers()
{
#ifdef DEBUG_XML
  std::cout << "Terminando table layers" << std::endl;
#endif
}


//HEA

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


//HEA
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

//HEA
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

//HEA

QList<QTableWidgetItem*> _table_layers::get_row(int Row)
{
  QList<QTableWidgetItem*> rowItems;
  for (int col = 0; col < columnCount(); ++col){
    rowItems << takeItem(Row, col);
  }
  return rowItems;
}

//HEA

void _table_layers::set_row(int row, const QList<QTableWidgetItem*>& rowItems)
{
  for (int col = 0; col < columnCount(); ++col){
    setItem(row, col, rowItems.at(col));
  }
}

//HEA

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
    Item->setToolTip(Vec_info[i].Name);
    Item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
    setItem(i,_table_layers_ns::NUM_COLS,Item);
  }
}

//HEA

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

//HEA

void _table_layers::cell_clicked_slot(int Row,int Col)
{
  if (Col==_table_layers_ns::NUM_COLS){
    selectRow(Row);
    W_tab->show_layer_parameters(Row,Col);
  }
}

//HEA
#ifdef STATISTIC_GRAPHS_ACTIVE
void _table_layers::header_clicked_slot(int Col)
{
  if (Col<2){
    _button_icon *Button;

    for (unsigned int Row=0;Row<Vec_info.size();Row++){
      Button=static_cast<_button_icon *>(cellWidget(Row,Col));

      if (Vec_info[Row].States[Col]==true){
        Button->setIcon(Vec_icons[Col].Icon_off);
      }
      else{
        Button->setIcon(Vec_icons[Col].Icon_on);
      }

      Vec_info[Row].States[Col]=!Vec_info[Row].States[Col];
    }

    W_tab->reverse_col(Col);
  }
}
#endif
//HEA

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

//HEA

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

//HEA

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

//HEA

void _table_layers::remove_row(int Row)
{
  for (int i=Row;i<rowCount()-1;i++){
    Vec_info[i]=Vec_info[i+1];
  }
  Vec_info.pop_back();

  update_table();
}


