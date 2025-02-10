//ALI

#include "ne_connection.h"
#include "ne_port.h"
#include "ne_block.h"
#include "nodes_editor.h"
#include "ne_common.h"

#include <QBrush>
#include <QPen>
#include <QGraphicsScene>

//HEA

_ne_connection::_ne_connection(_nodes_editor *Nodes_editor1, QGraphicsItem *Parent) : QGraphicsPathItem(Parent)
{
  Nodes_editor=Nodes_editor1;

	setPen(QPen(Qt::black, 2));
	setBrush(Qt::NoBrush);
	setZValue(-1);
  Start_port = nullptr;
  End_port = nullptr;

  setFlag(QGraphicsItem::ItemIsSelectable);
}

//HEA

_ne_connection::~_ne_connection()
{
  if (Start_port){
    Start_port->connections().remove(Start_port->connections().indexOf(this));
  }
  if (End_port){
    End_port->unconnected();
    End_port->connections().remove(End_port->connections().indexOf(this));
  }
}

//HEA

void _ne_connection::set_start_port(_ne_port *Port)
{
  Start_port = Port;
  Start_port->connections().append(this);
}

//HEA

void _ne_connection::set_end_port(_ne_port *Port,int Index)
{
  End_port = Port;
  End_port->connected();
  // the index of the output port tha connect whit this input port
  End_port->index(Index);
  End_port->connections().append(this);
}

//HEA

void _ne_connection::update_pos_from_ports()
{
  Start_pos = Start_port->scenePos();
  End_pos = End_port->scenePos();
}

//HEA

void _ne_connection::update_path()
{
  QPainterPath Path;

  Path.moveTo(Start_pos);

  qreal dx = End_pos.x() - Start_pos.x();

  Path.lineTo(Start_pos.x()+dx/2,Start_pos.y());
  Path.lineTo(Start_pos.x()+dx/2,End_pos.y());
  Path.lineTo(End_pos.x(),End_pos.y());

  setPath(Path);
}

//HEA

void _ne_connection::update_final_path()
{
  QPainterPath Path;

  _ne_port *Port=start_port(); // output port
  _ne_block *Block=Port->block(); // Block output
  _nodes_editor *Nodes_editor=Block->nodes_editor();
  int Counter_c1=Nodes_editor->get_col(Col1)-1;
  int Counter_c2=Nodes_editor->get_col(Col2)-1;
  int Counter_r1=Nodes_editor->get_row(Row)-1;
  int Step_col1;
  int Step_col2;
  int Step_row=int(roundf(float(Nodes_editor->space_height())*float(Counter_row)/float(Counter_r1)));

  if (Counter_c1==0) Step_col1=0;
  else Step_col1=int(roundf(float(Nodes_editor->space_width())*float(Counter_col1)/float(Counter_c1)));
  if (Counter_c2==0) Step_col2=0;
  else Step_col2=int(roundf(float(Nodes_editor->space_width())*(1.0f-float(Counter_col2)/float(Counter_c2))));
  if (Counter_r1==0) Step_row=0;
  else Step_row=int(roundf(float(Nodes_editor->space_height())*float(Counter_row)/float(Counter_r1)));

  if (Counter_row!=-1){ // indirect
#ifdef USE_COLORS
    QPen Pen;
    Pen.setColor(QColor(_ne_common_ns::Colors[Counter_col1%_ne_common_ns::MAX_NUM_COLORS].Red,_ne_common_ns::Colors[Counter_col1%_ne_common_ns::MAX_NUM_COLORS].Green,_ne_common_ns::Colors[Counter_col1%_ne_common_ns::MAX_NUM_COLORS].Blue));
    setPen(Pen);
#endif

    if (Col1==Col2){
      Path.moveTo(Start_pos);
      Path.lineTo(Start_pos.x()+_ne_common_ns::RADIUS+_ne_common_ns::CHANNEL_WIDTH_OFFSET+Step_col1,Start_pos.y());
      Path.lineTo(Start_pos.x()+_ne_common_ns::RADIUS+_ne_common_ns::CHANNEL_WIDTH_OFFSET+Step_col1,End_pos.y());
      Path.lineTo(End_pos.x(),End_pos.y());
    }
    else{
      Path.moveTo(Start_pos);
      Path.lineTo(Start_pos.x()+_ne_common_ns::RADIUS+_ne_common_ns::CHANNEL_WIDTH_OFFSET+Step_col1,Start_pos.y());
      Path.lineTo(Start_pos.x()+_ne_common_ns::RADIUS+_ne_common_ns::CHANNEL_WIDTH_OFFSET+Step_col1,Row*Nodes_editor->step_height()+Nodes_editor->block_height()/2+_ne_common_ns::RADIUS+_ne_common_ns::CHANNEL_HEIGHT_OFFSET+Step_row);
      Path.lineTo(End_pos.x()-_ne_common_ns::RADIUS-_ne_common_ns::CHANNEL_WIDTH_OFFSET-Step_col2,Row*Nodes_editor->step_height()+Nodes_editor->block_height()/2+_ne_common_ns::RADIUS+_ne_common_ns::CHANNEL_HEIGHT_OFFSET+Step_row);
      Path.lineTo(End_pos.x()-_ne_common_ns::RADIUS-_ne_common_ns::CHANNEL_WIDTH_OFFSET-Step_col2,End_pos.y());
      Path.lineTo(End_pos.x(),End_pos.y());
    }
  }
  else{ // direct
    Path.moveTo(Start_pos);
    Path.lineTo(Start_pos.x()+_ne_common_ns::RADIUS+_ne_common_ns::CHANNEL_WIDTH_OFFSET+Step_col1,Start_pos.y());
    Path.lineTo(Start_pos.x()+_ne_common_ns::RADIUS+_ne_common_ns::CHANNEL_WIDTH_OFFSET+Step_col1,End_pos.y());
    Path.lineTo(End_pos.x(),End_pos.y());
  }

  if (isSelected()) {
    setPen(QPen(Qt::darkYellow));
  }
  else {
      setPen(QPen(Qt::black));
  }

  setPath(Path);
}

//HEA

_ne_port* _ne_connection::start_port() const
{
  return Start_port;
}

//HEA

_ne_port* _ne_connection::end_port() const
{
  return End_port;
}

//HEA

void _ne_connection::paint(QPainter *Painter, const QStyleOptionGraphicsItem *Option, QWidget *Widget)
{
  Q_UNUSED(Option)
  Q_UNUSED(Widget)

  if (isSelected()) {
    Painter->setPen(QPen(Qt::gray,1,Qt::DashDotLine));
  }
  else { // not selected
    Painter->setPen(QPen(Qt::black));
  }

  Painter->drawPath(path());
}

//HEA

void _ne_connection::contextMenuEvent(QGraphicsSceneContextMenuEvent *Event)
{
  setSelected(true);

  QMenu Menu;
  Menu.addAction("Remove");
  QAction *Selection = Menu.exec(Event->screenPos());
  if (Selection){
    Nodes_editor->remove_connection(this);
  }
}

//HEA

QVariant _ne_connection::itemChange(GraphicsItemChange Change, const QVariant &Value)
{
  Q_UNUSED(Change);

  return Value;
}
