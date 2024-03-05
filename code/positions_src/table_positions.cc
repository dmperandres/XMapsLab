/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "table_positions.h"
#include "window_positions.h"

using namespace _table_positions_ns;

/*************************************************************************/

_table_positions::_table_positions(_window_positions *Window1):Window(Window1)
{
//  W_tab=W_tab1;

  setColumnCount(NUM_COLS+1);
  setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
  setHorizontalHeaderLabels(QString("X;Y").split(";"));

//  QFont Font=font();
//  QFontMetrics Font_metric(Font);
//  int Width_char1=Font_metric.horizontalAdvance("_0000_");

  horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

//  setColumnWidth(0,Width_char1);
//  setColumnWidth(1,Width_char1);
  // stretch the last column to the father size
//  horizontalHeader()->setStretchLastSection(true);

  // remove the numbers
  // verticalHeader()->setVisible(false);

  connect(verticalHeader(),SIGNAL(sectionClicked(int)),this,SLOT(vertical_header_clicked_slot(int)));

  // to allow drag and drop
  setDragEnabled(true);
  setAcceptDrops(true);
  viewport()->setAcceptDrops(true);
  setDragDropOverwriteMode(false);
  setDropIndicatorShown(true);
  setDragDropMode(QAbstractItemView::InternalMove);
  setSelectionMode(QAbstractItemView::SingleSelection);
  setSelectionBehavior(QAbstractItemView::SelectRows);

  setColumnCount(NUM_COLS);

  // read icons
//  Vec_icons.resize(NUM_COLS);
//  QPixmap Pixmap;
//  Pixmap.load(":/icons/button_visible.png");
//  Vec_icons[VISIBILITY].Icon_on.addPixmap(Pixmap);
//  Pixmap.load(":/icons/button_invisible.png");
//  Vec_icons[VISIBILITY].Icon_off.addPixmap(Pixmap);

//  Pixmap.load(":/icons/button_write.png");
//  Vec_icons[WRITABILITY].Icon_on.addPixmap(Pixmap);
//  Pixmap.load(":/icons/button_no_write");
//  Vec_icons[WRITABILITY].Icon_off.addPixmap(Pixmap);

  connect(this,SIGNAL(cellClicked(int,int)),this,SLOT(cell_clicked_slot(int,int)));
}

_table_positions::~_table_positions()
{
#ifdef DEBUG_XML
  cout << "Terminando table layers" << endl;
#endif
}

/*************************************************************************/

void _table_positions::update_table(std::vector<_common_ns::_position_data> &Vec_positions)
{
  // delete all the rows
  for (int i=rowCount()-1;i>=0;i--) removeRow(i);

  QTableWidgetItem *Item;
  for (unsigned int i=0;i<Vec_positions.size();i++){
    insertRow(i);

    Item = new QTableWidgetItem(QString::number(Vec_positions[i].Coordinates.x));
    Item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    Item->setFlags(Qt::ItemIsSelectable| Qt::ItemIsEnabled);
    setItem(i,0,Item);

    Item = new QTableWidgetItem(QString::number(Vec_positions[i].Coordinates.y));
    Item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    Item->setFlags(Qt::ItemIsSelectable| Qt::ItemIsEnabled);
    setItem(i,1,Item);
  }
}

/*************************************************************************/

void _table_positions::cell_clicked_slot(int Row,int Col)
{
  Q_UNUSED(Col)

  if (Row!=Selected_row){
    Selected_row=Row;
    Active=true;
    selectRow(Row);
  }
  else{
    if (Active){
      clearSelection();
      Active=false;
    }
    else{
      Active=true;
      selectRow(Row);
    }
  }

  Window->selected_position(Row,Active);
}

/*************************************************************************/

void _table_positions::vertical_header_clicked_slot(int Row)
{
  if (Row!=Selected_row){
    Selected_row=Row;
    Active=true;
    selectRow(Row);
  }
  else{
    if (Active){
      clearSelection();
      Active=false;
    }
    else{
      Active=true;
      selectRow(Row);
    }
  }

  Window->selected_position(Row,Active);
}

