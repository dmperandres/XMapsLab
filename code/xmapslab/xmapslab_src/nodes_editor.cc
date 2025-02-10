//ALI

#include "nodes_editor.h"

#include <QGraphicsScene>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QInputDialog>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMessageBox>

#include <filter.h>

#include <qlineedit.h>

#include "ne_port.h"
#include "ne_connection.h"
#include "ne_block.h"

using namespace std;
using namespace _filter_ns;
using namespace _nodes_editor_ns;

// static
//int _nodes_editor::NUM_FILTERS=0;

//HEA

_nodes_editor::_nodes_editor(QWidget *Parent):
QWidget(Parent)
{

//  QFont Font(font());
//  QRect Rectangle=QFontMetrics(Font).boundingRect(_ne_common_ns::SIZE_TEXT);

//  Step_width=Rectangle.width();
//  Step_height=Rectangle.width();

  Step_height=_ne_common_ns::STEP_HEIGHT_DEFAULT;
  Step_width=_ne_common_ns::STEP_WIDTH_DEFAULT;

  for (unsigned int i=0;i<_ne_common_ns::NUM_MAX_ROWS;i++){
    for (unsigned int j=0;j<_ne_common_ns::NUM_MAX_ROWS;j++){
      Objects[i][j]=false;
    }
  }

  clear_vectors();

  Connection = nullptr;
  Selected_block=nullptr;

  Changed=true;

  Num_filters=0;
}

//HEA

_nodes_editor::~_nodes_editor()
{
  for (auto Block: List_blocks){
    delete Block;
  }
}

//HEA

void _nodes_editor::clear()
{

  // remove the blocks
  for (const auto& Block : List_blocks){
    Scene->removeItem(Block);
  }

  for (auto Block: List_blocks){
    delete Block;
  }

  List_blocks.clear();

  // remove the connections
  for (const auto& Connection : List_connections){
    Scene->removeItem(Connection);
  }

  for (const auto& Connection : List_connections){
    delete Connection;
  }

  List_connections.clear();



  for (unsigned int i=0;i<_ne_common_ns::NUM_MAX_ROWS;i++){
    for (unsigned int j=0;j<_ne_common_ns::NUM_MAX_ROWS;j++){
      Objects[i][j]=false;
    }
  }

  clear_vectors();

  Connection = nullptr;
  Selected_block=nullptr;

  Changed=true;

  Filters_json_data.clear();
  Map_blocks.clear();
  Map_data_blocks.clear();
  Map_filters_parameters.clear();

  Num_filters=0;
}

//HEA

void _nodes_editor::install(QGraphicsScene *Scene1)
{
  Scene1->installEventFilter(this);
  Scene = Scene1;
}

//HEA

void _nodes_editor::set_font_sizes(int Height1,int Width1)
{
  Font_height=Height1;
  Font_width=Width1;

  Step_width=Font_width*_ne_common_ns::NUM_CHARS_SPACE_BLOCK*_ne_common_ns::STEP_WIDTH_FACTOR;
  Step_height=Font_height*_ne_common_ns::NUM_LINES_BLOCK*_ne_common_ns::STEP_HEIGHT_FACTOR;

  // compute the space between boxes
  // step-letters-circles-offset
  Space_width=Step_width-Font_width*_ne_common_ns::NUM_CHARS_SPACE_BLOCK-4*_ne_common_ns::RADIUS-2*_ne_common_ns::CHANNEL_WIDTH_OFFSET;
  Space_height=Step_height-Font_height*_ne_common_ns::NUM_LINES_BLOCK-4*_ne_common_ns::RADIUS-2*_ne_common_ns::CHANNEL_HEIGHT_OFFSET;

  Block_width=Font_width*_ne_common_ns::NUM_CHARS_LINE_BLOCK;
  Block_height=Font_height*_ne_common_ns::NUM_LINES_BLOCK;
}

//HEA

QGraphicsItem* _nodes_editor::item_at(const QPointF &Point)
{
  QList<QGraphicsItem*> items = Scene->items(QRectF(Point - QPointF(1,1), QSize(3,3)));

	foreach(QGraphicsItem *item, items)
		if (item->type() > QGraphicsItem::UserType)
			return item;

  return nullptr;
}

//HEA

QGraphicsItem* _nodes_editor::item_selected()
{
  QList<QGraphicsItem*> items = Scene->items();

  foreach(QGraphicsItem *item, items)
    if (item->type() > QGraphicsItem::UserType && item->isSelected())
      return item;

  return nullptr;
}

//HEA

void _nodes_editor::resizeEvent(QResizeEvent * event)
{
  Q_UNUSED(event)
  adjustSize();
}

//HEA

bool _nodes_editor::eventFilter(QObject *Object, QEvent *Event)
{
  QGraphicsSceneMouseEvent *Mouse_event = static_cast<QGraphicsSceneMouseEvent *>(Event);

  switch (int(Event->type())){
  case QEvent::GraphicsSceneMousePress:
    switch (int(Mouse_event->button())){
    case Qt::LeftButton:
      {
        QGraphicsItem *item = item_at(Mouse_event->scenePos());
        _ne_port *port1=static_cast<_ne_port *>(item);

        if (item && (item->type() == _ne_port::Type) && port1->port_type()==_ne_port_ns::_port_type::PORT_TYPE_OUTPUT){
          // start a connection
          Connection = new _ne_connection(this,nullptr);
          Scene->addItem(Connection);
          Connection->set_start_port(static_cast<_ne_port *>(item)); // ist the same as port1??
          Connection->set_start_pos(item->scenePos());
          Connection->set_end_pos(Mouse_event->scenePos());
          Connection->update_path();
          return true;
        }
        else{
//          QPointF P=Mouse_event->scenePos();
//          int Col=int(round(P.x()/Step_width));
//          int Row=int(round(P.y()/Step_height));

          if (item && item->type() == _ne_block::Type){
            Selected_block = static_cast<_ne_block *>(item);

            QPointF P=Mouse_event->scenePos();
            X_old=int(round(P.x()/Step_width));
            Y_old=int(round(P.y()/Step_height));

            Objects[Y_old][X_old]=false;
          }

        }
      }
      break;
    }
    break;
  case QEvent::GraphicsSceneMouseMove:
    {
      QPointF Position=Mouse_event->scenePos();

      if (Position.x()<_ne_common_ns::STEP_WIDTH_DEFAULT/2) Position.setX(_ne_common_ns::STEP_WIDTH_DEFAULT/2);

      if (Connection){
        Connection->set_end_pos(Position);
        Connection->update_path();
        return true;
      }
      if (Selected_block){
        Selected_block->setPos(Position);

      }
    }
    break;
  case QEvent::GraphicsSceneMouseRelease:
    if (Mouse_event->button() == Qt::LeftButton){
      if (Connection){ // end point of a connection
        // get the element under the cursor
        QGraphicsItem *item = item_at(Mouse_event->scenePos());

        // check that is port
        if (item && item->type() == _ne_port::Type){
          // get the information of the connection
          _ne_port *Start_port = Connection->start_port();
          _ne_port *End_port = static_cast<_ne_port *>(item);

          // check that is not a loop and that it is correctly connected
          if (Start_port->block() != End_port->block() && !(End_port->port_type()==_ne_port_ns::_port_type::PORT_TYPE_OUTPUT)  && !Start_port->is_connected(End_port) && End_port->num_conections()==0){
            // check the valis class conection
            if (Start_port->port_class()==End_port->port_class()){
              // update data
              Connection->set_end_pos(End_port->scenePos());
              Connection->set_end_port(End_port,Start_port->index());

              redraw_paths();

              // check if the block that has the input connection port, has all its ports connected. In that case, the name can be recomputed
              // start block
              _ne_block *Block=Start_port->block();
              Block->count_output_connections();

              // end block
              Block=End_port->block();
              Block->count_input_connections();
              if (Block->all_input_ports_connected()==true){
                // recompute the name
                string Old_name=Block->name();
                Block->update_name();

                // delete the old name of structs
                Map_filters_parameters.erase(Old_name);
                // add the new one
                map<string,string> Map_aux;
                Map_aux["_INI_"]="EDITOR";
                Map_filters_parameters[Block->name()]=Map_aux;
              }

              Connection = nullptr;
              Changed=true;

              return true;
            }
            else{ // the class of ports is diiferent
              if (End_port->port_class()==_ne_port_ns::_port_class::PORT_CLASS_BINARY){
                QMessageBox::warning(this,tr("Warning"),tr("Connect a binary output with a binary input"));
              }
              else{
                QMessageBox::warning(this,tr("Warning"),tr("Connect a continuous output with a continuous input"));
              }
              Scene->removeItem(Connection);
              delete Connection;
              Connection = nullptr;
              return true;
            }
          }
          else{
            Scene->removeItem(Connection);
            delete Connection;
            Connection = nullptr;
            return true;
          }
        }
        else{
          Scene->removeItem(Connection);
          delete Connection;
          Connection = nullptr;
          return true;
        }
      }
      else{ // the dragged block is left
        if (Selected_block){

          QPointF P=Mouse_event->scenePos();
          int x=int(round(P.x()/Step_width));
          int y=int(round(P.y()/Step_height));

          if (Selected_block->filter_type()==_filter_ns::_filter_type::FILTER_TYPE_ELEMENT){
            if (get_mat_objects(y,0)==0) x=0;
            else{
              y=Y_old;
              x=X_old;
            }
          }
          else{
            // the other objects can move freely but not in col 0
            if (x==0) x=1;

            // search for an empty place  for a col look at all rows
            bool Found=false;

            while (Found==false){
              if (Objects[y][x]!=false){
                if (x<_ne_common_ns::NUM_MAX_ROWS){
                  y=0;
                  while (Objects[y][x]!=false && y<_ne_common_ns::NUM_MAX_ROWS){
                    y++;
                  }
                  if (!(y<_ne_common_ns::NUM_MAX_ROWS)) x++;
                  else Found=true;
                }
                else{
                  QMessageBox MsgBox(this);
                  MsgBox.setText("There is not any free place");
                  MsgBox.exec();
                  exit(-1);
                }
              }
              else Found=true;
            }

//            if (Objects[y][x]!=false){
//              x--;
//              do{
//                x++;
//                y=0;
//                while (Objects[y][x]!=false && y<_ne_common_ns::NUM_MAX_ROWS){
//                  y++;
//                }
//              } while (Objects[y][x]!=false);
//            }
          }

          Selected_block->set_mat_pos(y,x);

          redraw_paths();

          Changed=true;

          Selected_block=nullptr;
        }
      }
    }
    break;
  case QEvent::GraphicsSceneMouseDoubleClick:
    {
      if (Mouse_event->button() == Qt::LeftButton){
        QPointF P=Mouse_event->scenePos();
        int Col=int(round(P.x()/Step_width));
//        int Row=int(round(P.y()/Step_height));
        if (Col>0){
          // only the added blocks that are not elements
          QGraphicsItem *item = item_at(Mouse_event->scenePos());

          if (item && item->type() == _ne_block::Type){
            _ne_block *Block=static_cast<_ne_block *>(item);
            QString Text = QInputDialog::getText(Mouse_event->widget(),tr("Edit Text"), tr("Enter new text:"),QLineEdit::Normal, QString::fromStdString(Block->name()));
            if (!Text.isEmpty()) Block->name(Text.toStdString());
            Block->update();
            Changed=true;
          }
        }
      }
      break;
    }
  case QEvent::KeyRelease:
    {
      QKeyEvent* key = static_cast<QKeyEvent*>(Event);
      switch(key->key()){
      case Qt::Key_Delete:
        {
          QGraphicsItem *item = item_selected();
          if (item && (item->type() == _ne_block::Type)){
            _ne_block *Block=static_cast<_ne_block *>(item);
            string Name=Block->name();

            QPointF P=Block->pos();
            int x=int(round(P.x()/Step_width));
            int y=int(round(P.y()/Step_height));

            Objects[y][x]=false;
            List_blocks.remove(Block);
            Map_filters_parameters.erase(Name);
            delete Block;
            redraw_paths();
            Changed=true;
          }
          break;
        }
      default:
        break;
      }
    }
    break;
  default:break;
  }
  return QObject::eventFilter(Object, Event);
}

//HEA
// Computes the positions of the path for each block taking into account the space between columns and rows and the positions of the blocks
// The idea is to compute the number of paths that are in each row and col. This helps to compute how to share the space between different connections
// Also, each conection is asigned a position, from 0 to m, being m the number of connections

void _nodes_editor::redraw_paths()
{
  clear_vectors();
  // traverse the blocks
  _ne_port *Start_port;
  _ne_port *End_port;
  QVector<_ne_connection*> Vec_connections;
  _ne_block *Block2;
  int Row1,Col1,Row2,Col2;

  // visit all the blocks
  for (auto *Block1: List_blocks){
    // get output port

    Start_port=Block1->output_port(0); // !!!!!!!!!!!

    if (Start_port!=nullptr){
      // there is a blocK

      // get the mat position
      Row1=Block1->get_mat_row();
      Col1=Block1->get_mat_col();

      // get connections (usually one)
      Vec_connections=Start_port->connections();
      // for each connection
      if (Vec_connections.size()>0){
        for (auto *Connection: Vec_connections){
          // get the end port, the port to which is connected the block1 as input
          End_port=Connection->end_port();
          // get the block of the port. This is the input block of block1
          Block2=End_port->block();
          // now we get the mat position
          Row2=Block2->get_mat_row();
          Col2=Block2->get_mat_col();
          // compute the indices for the path
          compute_path_indices(Row1,Col1,Row2,Col2,Connection);
        }
      }
    }
  }

  for (auto *Block1: List_blocks){
    // get output port
    Start_port=Block1->output_port(0); // !!!!!!!!!!!
    if (Start_port!=nullptr){
      // get connections (usually one)
      Vec_connections=Start_port->connections();
      if (Vec_connections.size()>0){
        // for each connection
        for (auto *Connection: Vec_connections){
          // update the path
          Connection->update_final_path();
        }
      }
    }
  }
}

//HEA

void _nodes_editor::compute_path_indices(int Row1,int Col1,int Row2,int Col2,_ne_connection* Connection)
{
  int Colum;

  if (Row1==Row2){ // the same row
    if (Col2>Col1){ // the second block is at the right of block1
      if ((Col2-Col1)==1){ // the blocks are consecutive, nothing to do  B1->B2
        if (Col1>=0){
          Colum=increment_col(Col1);
          Connection->set_start_col(Col1,Colum);
          Connection->set_end_col(Col1,Colum);
          Connection->set_row(-1,-1); // direct connection
        }
      }
      else{ // the blocks are not consecutive
        // check if there is a block in between
        bool Found=false;
        for (int i=Col1+1;i<Col2;i++){
          if (Objects[Row1][i]!=false) Found=true;
        }

        if (Found==false){ // direct connetion B1-->B2
          if (Col1>=0){
            Colum=increment_col(Col1);
            Connection->set_start_col(Col1,Colum);
            Connection->set_end_col(Col1,Colum);
            Connection->set_row(-1,-1);
          }
        }
        else{ // the conection is done throug the row below the block
          // B1-   B  ->B2
          //    |----|
          if (Col1>=0 && (Col2-1)>=0){
            Connection->set_start_col(Col1,increment_col(Col1));
            Connection->set_end_col(Col2-1,increment_col(Col2-1));
            Connection->set_row(Row1,increment_row(Row1));
          }
        }
      }
    }
    else{ // the second block is at the left of block1
      if ((Col1-Col2)==1){ // the blocks are consecutive,
        //   ->b2   b1-
        //  |----------|
        if (Col1>=0 && (Col2-1)>=0){
          Connection->set_start_col(Col1,increment_col(Col1));
          Connection->set_end_col(Col2-1,increment_col(Col2-1));
          Connection->set_row(Row1,increment_row(Row1));
        }
      }
      else{ // the blocks are not consecutive
        //   ->b2   b1-
        //  |----------|
        if (Col1>=0 && (Col2-1)>=0){
          Connection->set_start_col(Col1,increment_col(Col1));
          Connection->set_end_col(Col2-1,increment_col(Col2-1));
          Connection->set_row(Row1,increment_row(Row1));
        }
      }
    }
  }
  else{ // rows are different
    if (Row1<Row2){ // block1 is up block2 down
      if (Col1==Col2){ // in the same col
        //   b1-
        //   ---|
        //  |->b2
        if (Col1>=0 && (Col2-1)>=0){
          Connection->set_start_col(Col1,increment_col(Col1));
          Connection->set_end_col(Col2-1,increment_col(Col2-1));
          Connection->set_row(Row1,increment_row(Row1));
        }
      }
      else{ // different columns
        if (Col1<Col2){// the second block is at the right of block1
          if ((Col2-1)==Col1){ // only onw col of difference
            //   b1-
            //      |
            //      |->b2
            if (Col1>=0){
              Colum=increment_col(Col1);
              Connection->set_start_col(Col1,Colum);
              Connection->set_end_col(Col2-1,Colum);
              Connection->set_row(Row1,increment_row(Row1));
            }
          }
          else{
            //   b1-
            //      |---
            //          |->b2
            if (Col1>=0 && (Col2-1)>=0){
              Connection->set_start_col(Col1,increment_col(Col1));
              Connection->set_end_col(Col2-1,increment_col(Col2-1));
              Connection->set_row(Row1,increment_row(Row1));
            }
          }
        }
        else{ // the second block is at the left of block1
          //          b1-
          //  ----------|
          //  |->b2
          if (Col1>=0 && (Col2-1)>=0){
            Connection->set_start_col(Col1,increment_col(Col1));
            Connection->set_end_col(Col2-1,increment_col(Col2-1));
            Connection->set_row(Row1,increment_row(Row1));
          }
        }
      }
    }
    else{ // block2 is up
      if (Col1==Col2){ // in the same col
        //   ->b2
        //  |-----|
        //     b1-
        if (Col1>=0 && (Col2-1)>=0){
          Connection->set_start_col(Col1,increment_col(Col1));
          Connection->set_end_col(Col2-1,increment_col(Col2-1));
          Connection->set_row(Row2,increment_row(Row2));
        }
      }
      else{ // different columns
        if (Col1<Col2){// the second block is at the right of block1
          if ((Col2-1)==Col1){ // one colum od difference
            //        ->b2
            //        |
            //     b1-
            if (Col1>=0){
              Colum=increment_col(Col1);
              Connection->set_start_col(Col1,Colum);
              Connection->set_end_col(Col2-1,Colum);
              Connection->set_row(Row2,increment_row(Row2));
            }
          }
          else{
            //               ->b2
            //        |-----|
            //     b1-
            if (Col1>=0 && (Col2-1)>=0){
              Connection->set_start_col(Col1,increment_col(Col1));
              Connection->set_end_col(Col2-1,increment_col(Col2-1));
              Connection->set_row(Row2,increment_row(Row2));
            }
          }
        }
        else{ // the second block is at the left of block1
          //   ->b2
          //  |-------------|
          //             b1-
          if (Col1>=0 && (Col2-1)>=0){
            Connection->set_start_col(Col1,increment_col(Col1));
            Connection->set_end_col(Col2-1,increment_col(Col2-1));
            Connection->set_row(Row2,increment_row(Row2));
          }
        }
      }
    }
  }
}

//HEA

//const int MIN_INDEX_GRID_LINES=-10;
//const int MAX_INDEX_GRID_LINES=50;
//const int MAX_LINE_VALUE=10000;

//QFont Font(Nodes_editor->font());
//QRect Rectangle=QFontMetrics(Font).boundingRect("A");
//int w=Rectangle.width();
//int h=Rectangle.height();

//int Border=0;
//float Factor=1;

//int Size;
//if (Vec_names_input_ports.size()>=Vec_names_output_ports.size()) Size=Vec_names_input_ports.size();
//else Size=Vec_names_output_ports.size();


//  QFont Font(Nodes_editor->font());
//  QRect Rectangle=QFontMetrics(Font).boundingRect(_ne_common_ns::SIZE_TEXT);
//  Width=Rectangle.width();

//Width=w*_ne_common_ns::NUM_CHARS_LINE_BLOCK;

void _nodes_editor::add_grid()
{
  QPen Pen;
  Pen.setColor(QColor(_ne_common_ns::Gray.Red,_ne_common_ns::Gray.Green,_ne_common_ns::Gray.Blue));
  QGraphicsLineItem *Line;

  for (int i=_ne_common_ns::MIN_INDEX_GRID_LINES;i<_ne_common_ns::MAX_INDEX_GRID_LINES;i++){
    Line=new QGraphicsLineItem;
    Line->setZValue(-1000);
    Line->setPen(Pen);
    Line->setLine(i*Step_width,-_ne_common_ns::MAX_LINE_VALUE,i*Step_width,_ne_common_ns::MAX_LINE_VALUE);
    Scene->addItem(Line);
  }

  for (int i=_ne_common_ns::MIN_INDEX_GRID_LINES;i<_ne_common_ns::MAX_INDEX_GRID_LINES;i++){
    Line=new QGraphicsLineItem;
    Line->setZValue(-1000);
    Line->setPen(Pen);
    Line->setLine(-_ne_common_ns::MAX_LINE_VALUE,i*Step_height,_ne_common_ns::MAX_LINE_VALUE,i*Step_height);
    Scene->addItem(Line);
  }
}

//HEA

void _nodes_editor::clear_vectors()
{
  for (unsigned int i=0;i<_ne_common_ns::NUM_MAX_ROWS;i++) Rows[i]=0;
  for (unsigned int i=0;i<_ne_common_ns::NUM_MAX_COLS;i++) Cols[i]=0;
}

//HEA

int _nodes_editor::increment_col(int Col1)
{
  int i;
  if (Col1>=0){
    i=Cols[Col1]++;
  }
  else{
    cout << "Error: the index Col1 < 0" << endl;
    exit(-1);
  }
  return i;
}

//HEA

int _nodes_editor::increment_row(int Row1)
{
  int i;
  if (Row1>=0){
    i=Rows[Row1]++;
  }
  else{
    cout << "Error: the index Row1 < 0" << endl;
    exit(-1);
  }
  return i;
}

//HEA

void _nodes_editor::set_mat_objects(int Row,int Col,bool Value)
{
  if (Row>=0 && Row<_ne_common_ns::NUM_MAX_ROWS && Col>=0 && Col<_ne_common_ns::NUM_MAX_COLS) Objects[Row][Col]=Value;
  else{
    cout << "Error: in mat object index " << endl;
    exit(-1);
  }
}

//HEA

bool _nodes_editor::get_mat_objects(int Row,int Col)
{
  if (Row>=0 && Row<_ne_common_ns::NUM_MAX_ROWS && Col>=0 && Col<_ne_common_ns::NUM_MAX_COLS) return Objects[Row][Col];
  else{
    cout << "Error: in mat object index " << endl;
    exit(-1);
  }
}

//HEA

void _nodes_editor::add_connection(_ne_block *Block_out,_ne_block *Block_in,int Num_port)
{
  Connection = new _ne_connection(this,nullptr);
  Scene->addItem(Connection);
  Connection->set_start_port(Block_out->output_port(0)); // !!!!!!!!!!!!!!!!!!!!!!!!!1
  Connection->set_start_pos(Block_out->output_port(0)->scenePos());

  // for the reset
  List_connections.push_back(Connection);

  switch(Num_port){
  case 0:
    Connection->set_end_port(Block_in->input_port(0)); // in_port1 !!!!!!!!!!
    Connection->set_end_pos(Block_in->input_port(0)->scenePos());
    break;
  case 1:
    Connection->set_end_port(Block_in->input_port(1)); // in_port2 !!!!!!!!!!
    Connection->set_end_pos(Block_in->input_port(1)->scenePos());
    break;
  case 2:
    Connection->set_end_port(Block_in->input_port(2));
    Connection->set_end_pos(Block_in->input_port(2)->scenePos());
    break;
  }
  Connection->update_path();
  Connection=nullptr;
}

//HEA

void _nodes_editor::read_data_effect(string Name)
{
  QJsonObject Filter_object;
  QStringList Key_list;
  map<string,string> Values;

  QFile File(Name.c_str());

  if (!File.open(QIODevice::ReadOnly)) {
      qWarning("Couldn't open json file.");
      exit(-1);
  }

  QByteArray Data=File.readAll();
  // the file is converted to a Json document
  QJsonDocument Document(QJsonDocument::fromJson(Data));
  // A json object is obtained from the document
  QJsonObject Object=Document.object();
  // filters appear as an array
  QJsonArray Filter_array=Object["effect"].toArray();
  // each filter is treated
  for (int i=0;i<Filter_array.size();i++) {
    // the data of each filter is put on an json object
    Filter_object=Filter_array[i].toObject();
    Key_list=Filter_object.keys();

    Values.clear();
    for (int j=0;j<Key_list.size();j++){
      //cout << Key_list[j].toStdString() << " " << Filter_object.value(Key_list[j]).toString().toStdString() << endl;
      Values[Key_list[j].toStdString()]=Filter_object.value(Key_list[j]).toString().toStdString();
    }
    Filters_json_data.push_back(Values);
  }
  File.close();
}


//HEA

bool _nodes_editor::find_root(_ne_block *Block1)
{
  _ne_block *Block_aux;
  _ne_port *Port;

  // if find an element
  if (Block1->filter_type()==_filter_ns::_filter_type::FILTER_TYPE_ELEMENT) return true;
  else{
    // get the name of the block that is connected to each input port and try again
    for (int i=0;i<Block1->num_input_ports();i++){
      Port=Block1->input_port(i);
      if (Port->port_class()==_ne_port_ns::_port_class::PORT_CLASS_BINARY && Port->port_open()==true){
        // can be unconected
        Block_aux=Block1->block_of_input_port(i);
        if (Block_aux==nullptr) return true;
        else{
          if (find_root(Block_aux)==false) return false;
        }
      }
      else{
        Block_aux=Block1->block_of_input_port(i);
        if (Block_aux==nullptr) return false;
        else{
          if (find_root(Block_aux)==false) return false;
        }
      }
    }
    return true;
  }
}

//HEA
// this function is called when the filter is designed and we want to see the results

bool _nodes_editor::create_blocks_from_editor()
{
  string Type;
  string Name;
  _ne_block *Block=nullptr;
  _ne_block *Block_in=nullptr;

  Filter_valid=false;

  // first all the data is cleared
  Map_data_blocks.clear();

  // check if there is any block that is not connected to an element block
  bool Found=false;
  for (list<_ne_block *>::iterator Block_aux=List_blocks.begin();Block_aux!=List_blocks.end();Block_aux++){
    Found=find_root(*Block_aux);
    if (Found==false) break;
  }

  if (Found==false){
    // error
    QMessageBox::warning(this, tr("Error"),tr("Error: there are blocks that are not connected"), QMessageBox::Ok);
    return false;
  }

  // used the _ne_blocks data to create the _blocks infor
  for (list<_ne_block *>::iterator Block_aux=List_blocks.begin();Block_aux!=List_blocks.end();Block_aux++){
    // get the block    
    Block=*Block_aux;

    _block Block1;
    _ne_port *Port1=nullptr;

    Block1.Name=Block->name();
    Block1.Type=Block->filter_type();

    // only the added filters are included

    for (int i=0;i<Block->num_input_ports();i++){
      Port1=Block->input_port(i);
      Block_in=Block->block_of_input_port(i);
      if (Block_in==nullptr){
        Block1.Vec_input_ports.push_back("NULL");
        Block1.Vec_index_input_ports.push_back(-1);
      }
      else{
        Block1.Vec_input_ports.push_back(Block_in->name());
        Block1.Vec_index_input_ports.push_back(Port1->index());
      }
    }

    Block1.Row=-1;
    Block1.Col=-1;

    Map_data_blocks[Block1.Name]=Block1;
  }

  // the structure is ok. Now it is necessary to establish the correct order of the blocks to run correctly:
  // all the previous connected blocks must be computed to update one

  // find the final blocks (they have no next one)
  vector<string> Vec_final_blocks;

  for (auto &Block_aux: Map_data_blocks){
    // get a _block A
    Name=Block_aux.second.Name;
    Found=false;
    for (auto &Block_aux1: Map_data_blocks){
      // get another _block B
      if (Block_aux.first!=Block_aux1.first){
        // they are different
        // check if A is input in any port of B
        for (unsigned int i=0;i<Block_aux1.second.Vec_input_ports.size();i++){
          if (Block_aux1.second.Vec_input_ports[i]==Name){
            // yes, it is connected
            Found=true;
            break;
          }
        }
      }
    }
    if (Found==false)
      Vec_final_blocks.push_back(Name);
  }

  // compute the position of each block recursively
  // counts the number of blocks for each column
  for (int i=0;i<_ne_common_ns::NUM_MAX_COLS;i++){
    Num_blocks_per_col[i]=0;
  }

  Pos_row=0;
  for (unsigned int i=0;i<Vec_final_blocks.size();i++){
    compute_position(Vec_final_blocks[i]);
  }

  // now compute the linear position
  // ugly method but I need to finish asap
  string Mat_names[_ne_common_ns::NUM_MAX_ROWS][_ne_common_ns::NUM_MAX_COLS];
  for (unsigned int Row=0;Row<_ne_common_ns::NUM_MAX_ROWS;Row++){
    for (unsigned int Col=0;Col<_ne_common_ns::NUM_MAX_COLS;Col++){
      Mat_names[Row][Col]="";
    }
  }

  // get the information of each block
  int Max_col=0;
  for (auto &Block_aux: Map_data_blocks){
    Mat_names[Block_aux.second.Row][Block_aux.second.Col]=Block_aux.second.Name;
    if (Block_aux.second.Col>Max_col) Max_col=Block_aux.second.Col;
  }

  // move by columns to get the correct order
  Vec_order.clear();

  for (unsigned int Col=0;Col<_ne_common_ns::NUM_MAX_COLS;Col++){
    for (unsigned int Row=0;Row<_ne_common_ns::NUM_MAX_ROWS;Row++){
      if (Mat_names[Row][Col]!="") Vec_order.push_back(Mat_names[Row][Col]);
    }
  }

  Filter_valid=true;

  return true;
}


//HEA

_position _nodes_editor::compute_position(string Name)
{
  _block &Block=Map_data_blocks[Name];
  _position Position;

  if (Block.Type==_filter_ns::_filter_type::FILTER_TYPE_ELEMENT){
    if (Block.Row==-1){
      // the first time that the element is visited
      Block.Row=Num_blocks_per_col[0];
      Block.Col=0;

      Position.Row=Num_blocks_per_col[0];
      Position.Col=0;
//      Pos_row++;

      Num_blocks_per_col[0]++;
      return(Position);
    }
    else{
      Position.Row=Block.Row;
      Position.Col=Block.Col;
      return(Position);
    }
  }
  else{
    // it is not a final block
    vector<_position> Positions;
    vector<string> Conns;
//    _position Position_aux;
    string Type_block;

    // get the input Blocks of selected Block
    for (unsigned int i=0;i<Block.Vec_input_ports.size();i++){
      Conns.push_back(Block.Vec_input_ports[i]);
    }

    Positions.resize(Conns.size());
    // search for each input the recursive connections
    // I have to check what path is longer
    for (unsigned int i=0;i<Conns.size();i++){
      Positions[i].Row=-1;
      Positions[i].Col=-1;

      if (Conns[i]!="NULL"){
        Positions[i]=compute_position(Conns[i]);
      }
    }

    // now check what are the bigger value for col and row
//    int Min_row=-1;
    int Max_col=-1;
    for (unsigned int i=0;i<Positions.size();i++){
//      if (Positions[i].Row>Min_row) Min_row=Positions[i].Row;
      if (Positions[i].Col>Max_col) Max_col=Positions[i].Col;
    }

//    Block.Row = Min_row;
    Block.Row=Num_blocks_per_col[Max_col+1];
    Block.Col = Max_col+1;

    Position.Row=Num_blocks_per_col[Max_col+1];
    Position.Col=Max_col+1;

    Num_blocks_per_col[Max_col+1]++;

    return Position;
  }
}

//HEA

void _nodes_editor::add_block(_filter_ns::_filter_type Type, _filter_ns::_filter_class Class, std::string Name, std::vector<_port_data> &Vec_input_ports, std::vector<_port_data> &Vec_names_output_ports)
{
  if (get_mat_objects(2,0)==false){
    Changed=true;
    string Name1=Name+"_"+std::to_string(Num_filters);

    _ne_block *Block = new _ne_block(this,nullptr);
    Scene->addItem(Block);
    Block->create(Type,Class,Name1,Num_filters,Vec_input_ports,Vec_names_output_ports);
    Block->set_mat_pos(2,0);
    List_blocks.push_back(Block);

    map<string,string> Map_aux;
    Map_aux["_INI_"]="EDITOR";
    Map_filters_parameters[Name1]=Map_aux;

    // update Num filters
    Num_filters++;
  }
  else{
     QMessageBox::warning(this, tr("Warning"),tr("Please, move the block before add a new one"), QMessageBox::Ok);
  }
}

//HEA

void _nodes_editor::add_block(_filter_ns::_filter_type Type, _filter_ns::_filter_class Class, std::string Name, std::vector<_filter_ns::_port_data> &Vec_names_input_ports, std::vector<_port_data> &Vec_names_output_ports, float Col, float Row)
{
  int Col1=int(roundf(Col/Step_width));
  int Row1=int(roundf(Row/Step_height));

  // check if the block is an element. In such case, they must be in the first column
  if (Type==_filter_ns::_filter_type::FILTER_TYPE_ELEMENT || Type==_filter_ns::_filter_type::FILTER_TYPE_IMAGE){
    if (Col1!=0){
      QMessageBox::warning(this, tr("Warning"),tr("the element block will be moved to column 0"), QMessageBox::Ok);
      Col1=0;
    }
  }
  else{
    if (Col1==0) Col1=1;
  }

  if (get_mat_objects(Row1,Col1)==false){
    Changed=true;
    string Name1=Name+"_"+std::to_string(Num_filters);

    _ne_block *Block = new _ne_block(this,nullptr);
    Scene->addItem(Block);
    Block->create(Type,Class,Name1,Num_filters, Vec_names_input_ports,Vec_names_output_ports);
    Block->set_mat_pos(Row1,Col1);
    List_blocks.push_back(Block);

    map<string,string> Map_aux;
    Map_aux["_INI_"]="EDITOR";
    Map_filters_parameters[Name1]=Map_aux;

    // update Num filters
    Num_filters++;
  }
  else{
     QMessageBox::warning(this, tr("Warning"),tr("Please, move the block to a unoccupied place"), QMessageBox::Ok);
  }
}

//HEA

//void _nodes_editor::add_initial_blocks()
//{
//  _ne_block *Block;
//  vector<QString> Vec_input_ports;
//  vector<QString> Vec_output_ports={"Out"};

//  // generate the blocks
//  Block=new _ne_block(this,nullptr);
//  Scene->addItem(Block);
//  Block->create("COLOR","COLOR",Vec_input_ports,Vec_output_ports);
//  Block->set_mat_pos(0,0);
//  Block->setFlag(QGraphicsItem::ItemIsMovable,false);
//  Block->setFlag(QGraphicsItem::ItemIsSelectable,false);
//  List_blocks.push_back(Block);
//  Map_blocks["COLOR"]=Block;

//  Block=new _ne_block(this,nullptr);
//  Scene->addItem(Block);
//  Block->create("GRAY","GRAY",Vec_input_ports,Vec_output_ports);
//  Block->set_mat_pos(1,0);
//  Block->setFlag(QGraphicsItem::ItemIsMovable,false);
//  Block->setFlag(QGraphicsItem::ItemIsSelectable,false);
//  List_blocks.push_back(Block);
//  Map_blocks["GRAY"]=Block;
//}

//HEA

void _nodes_editor::remove_block(_ne_block *Block)
{
  string Name=Block->name();

  int x=Block->get_mat_col();
  int y=Block->get_mat_row();

  // remove the object from the matrix
  Objects[y][x]=false;
  // remove one
  if (Block->num_input_ports()==1) Cols[x-1]--;
  if (Block->num_input_ports()==2) Cols[x-1]=Cols[x-1]-2;

  List_blocks.remove(Block);
  Map_filters_parameters.erase(Name);
  delete Block;
  redraw_paths();
  Changed=true;
}

//HEA

void _nodes_editor::remove_connection(_ne_connection *Connection1)
{
  delete Connection1;
  redraw_paths();
  Changed=true;
}
