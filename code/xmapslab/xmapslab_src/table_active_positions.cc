#include "table_active_positions.h"
#include "w_tab_xmapslab.h"
#include "window_xmapslab.h"

using namespace _table_active_positions_ns;

//HEA

_table_active_positions::_table_active_positions(std::string Name1, _w_tab_xmapslab *Widget1)
{
  Name=Name1;
  Parent=Widget1;

  setColumnCount(NUM_COLS+1);
  setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
  setHorizontalHeaderLabels(QStringList("Valid"));

  QFont Font=font();
  QFontMetrics Font_metric(Font);
  int Width_char1=Font_metric.horizontalAdvance("_Valid_");


  setColumnWidth(0,Width_char1);
  // stretch the last column to the father size
  horizontalHeader()->setStretchLastSection(true);

  connect(horizontalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(header_clicked_slot(int)));

  // to allow drag and drop
  setDragEnabled(true);
  setAcceptDrops(true);
  viewport()->setAcceptDrops(true);
  setDragDropOverwriteMode(false);
  setDropIndicatorShown(true);
//  setDragDropMode(QAbstractItemView::InternalMove);
  setSelectionMode(QAbstractItemView::SingleSelection);
//  setSelectionBehavior(QAbstractItemView::SelectRows);

  setColumnCount(NUM_COLS);

  // read icons
  Vec_icons.resize(NUM_COLS);
  QPixmap Pixmap;
  Pixmap.load(":/common/icons/valid.png");
  Vec_icons[VISIBILITY].Icon_on.addPixmap(Pixmap);
  Pixmap.load(":/common/icons/invalid.png");
  Vec_icons[VISIBILITY].Icon_off.addPixmap(Pixmap);
}


_table_active_positions::~_table_active_positions()
{
#ifdef DEBUG_XML
  cout << "Terminando table layers" << endl;
#endif
}

//HEA

QList<QTableWidgetItem*> _table_active_positions::get_row(int Row)
{
  QList<QTableWidgetItem*> rowItems;
  for (int col = 0; col < columnCount(); ++col){
    rowItems << takeItem(Row, col);
  }
  return rowItems;
}

//HEA

void _table_active_positions::set_row(int row, const QList<QTableWidgetItem*>& rowItems)
{
  for (int col = 0; col < columnCount(); ++col){
    setItem(row, col, rowItems.at(col));
  }
}

//HEA

void _table_active_positions::update_table(const std::vector<bool> &Vec_active_positionss)
{
  // delete all the rows
  for (int i=rowCount()-1;i>=0;i--) removeRow(i);

//  QTableWidgetItem *Item;
  _button_icon *Button;
  for (unsigned int i=0;i<Vec_active_positionss.size();i++){
    insertRow(i);

    for (int j=0;j<NUM_COLS;j++){
      Button=new _button_icon(i,j);
      if (Vec_active_positionss[i]==true) Button->setIcon(Vec_icons[j].Icon_on);
      else Button->setIcon(Vec_icons[j].Icon_off);

      connect(Button,SIGNAL(change_state(int,int)),this,SLOT(button_clicked_slot(int,int)));
      setCellWidget(i,j,(QWidget*)Button);
    }
  }
}

//HEA

void _table_active_positions::button_clicked_slot(int Row,int Col)
{
  if (Col==0){
    selectRow(Row);
    Parent->change_active_position(Row);

    change_button(Row);
  }
}

//HEA

void _table_active_positions::change_button(int Row)
{
  if (Row<rowCount()){
    _button_icon *Button=static_cast<_button_icon *>(cellWidget(Row,0));

    if (Parent->active_position(Row)==true) Button->setIcon(Vec_icons[0].Icon_on);
    else Button->setIcon(Vec_icons[0].Icon_off);
  }
}

//HEA

void _table_active_positions::header_clicked_slot(int Col)
{
  if (Col==0){
    std::vector<bool> &Vec_active_positions=Parent->window()->vec_active_positions();

    for (unsigned int Row=0;Row<Vec_active_positions.size();Row++){
      Parent->change_active_position(Row);

      change_button(Row);
    }
  }
}

//HEA

void _table_active_positions::remove_all()
{
  // delete all the rows
  for (int i=rowCount()-1;i>=0;i--) removeRow(i);
}

