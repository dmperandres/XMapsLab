#include "table_xrd_xmapslab.h"
#include "window_xmapslab.h"

/*************************************************************************/

_table_xrd_xmapslab::_table_xrd_xmapslab(_window_xmapslab *Window1)
{
  Window=Window1;

//  horizontalHeader()->setStretchLastSection(true);
  setSelectionMode(QAbstractItemView::SingleSelection);

  connect(this,SIGNAL(cellClicked(int,int)),this,SLOT(cell_clicked_slot(int,int)));
}

/*************************************************************************/

_table_xrd_xmapslab::~_table_xrd_xmapslab()
{
}

/*************************************************************************/

void _table_xrd_xmapslab::set_data(vector<string> Row_names, vector<string> Col_names,vector<vector<_common_ns::_result_linear_regresion>> &Result_linear_regresion)
{
  for (int i=rowCount()-1;i>=0;i--) removeRow(i);

  int Num_spaces=6;

  setColumnCount(Col_names.size()+1);
  setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

  QStringList List1;
  QFont Font=font();
  QFontMetrics Font_metric(Font);
  QString String;
  int Width_char1;
  int Max_width=0;
  int Min_width=Font_metric.horizontalAdvance("0.000000000");

  // search for the largest name for rows
  for (unsigned int i=0; i<Row_names.size();i++){
    String=QString::fromStdString(Row_names[i]);
    Width_char1=Font_metric.horizontalAdvance(String);
    if (Width_char1>Max_width) Max_width=Width_char1;
  }
  setColumnWidth(0,Max_width+Num_spaces*3);

  List1.push_back("File");
  for (unsigned int i=0; i<Col_names.size();i++){
    String=QString::fromStdString(Col_names[i]);
    List1.push_back(String);

    Width_char1=Font_metric.horizontalAdvance(String);
    if (Width_char1<Min_width) Width_char1=Min_width;
    setColumnWidth(i+1,Width_char1+Num_spaces);
  }

//  setHorizontalHeaderLabels(QString("View;Graph;Name").split(";"));
  setHorizontalHeaderLabels(List1);
//  horizontalHeader()->setStretchLastSection(true);

  QTableWidgetItem *Item;
//  _button_icon *Button;
  int Value;
  for (unsigned int i=0;i<Row_names.size();i++){
    insertRow(i);

    // insert the name of the row
    Item = new QTableWidgetItem(QString::fromStdString(Row_names[i]));
    Item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
    setItem(i,0,Item);

    // insert the rest of values

    for (unsigned int j=0;j<Result_linear_regresion[i].size();j++){
      Value=int(pow(Result_linear_regresion[i][j].Correlation_coefficient,2)*100); // R^2
      Item = new QTableWidgetItem(QString("%1%").arg(Value));
      Item->setTextAlignment(Qt::AlignCenter);
      if (Value>80) Item->setBackground(Qt::green);
      else{
        if (Value>60) Item->setBackground(Qt::yellow);
        else Item->setBackground(Qt::red);
      }
      Item->setFlags(Qt::ItemIsSelectable|Qt::ItemIsDragEnabled|Qt::ItemIsDropEnabled|Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsEditable);
      setItem(i,j+1,Item);
    }
  }

  item(Window->selected_row(),Window->selected_col())->setSelected(true);
}

/*************************************************************************/

void _table_xrd_xmapslab::cell_clicked_slot(int Row,int Col)
{
  Window->selected_xrd_data(Row,Col);
//  W_tab->show_layer_parameters(Row,Col);
}

