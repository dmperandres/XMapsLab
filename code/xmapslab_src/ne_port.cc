//ALI

#include "ne_common.h"
#include "ne_port.h"
#include "ne_connection.h"
#include <QGraphicsScene>
#include <QFontMetrics>

#include <QPen>

#include "ne_block.h"
#include "nodes_editor.h"

/*************************************************************************/

_ne_port::_ne_port(_ne_port_ns::_port_class Port_class1, QGraphicsItem *Parent):QGraphicsPathItem(Parent), Port_class(Port_class1)
{
  Label = new QGraphicsTextItem(this);

  Radius = _ne_common_ns::RADIUS;
  Margin = _ne_common_ns::MARGIN;

  QPainterPath Painter_path;
  Painter_path.addEllipse(-Radius, -Radius, 2*Radius, 2*Radius);
  setPath(Painter_path);

  if (Port_class1==_ne_port_ns::_port_class::PORT_CLASS_BINARY){
    setPen(QPen(Qt::darkGreen));
    setBrush(Qt::green);
  }
  else{
    setPen(QPen(Qt::darkRed));
    setBrush(Qt::red);
  }

//  QPainterPath Path();
//  Path.moveTo(-Radius,0);
//  Path.lineTo(-2*Radius,0);
//  Path.lineTo(-2*Radius,-2*Radius);

  setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}

/*************************************************************************/

_ne_port::~_ne_port()
{
  foreach(_ne_connection *Conn_aux, Vec_connections)
    delete Conn_aux;
}

/*************************************************************************/

void _ne_port::name(const std::string &Name1)
{
  Name = Name1;
  Label->setPlainText(QString::fromStdString(Name1));
}

/*************************************************************************/

void _ne_port::port_type(_ne_port_ns::_port_type Port_type1, bool Port_open1)
{
//  Is_output = Is_output1;
  Port_type=Port_type1;
  Port_open=Port_open1;

  if (Port_type==_ne_port_ns::_port_type::PORT_TYPE_OUTPUT){
    Label->setPos(-Radius - Margin - Label->boundingRect().width(), -Label->boundingRect().height()/2);
  }
  else{
    Label->setPos(Radius + Margin, -Label->boundingRect().height()/2);
    // ground conection
    if (Port_open==true){
      Line=new QGraphicsLineItem(this);
      Line->setLine(-Radius,0,-2*Radius,0);

      Line1=new QGraphicsLineItem(this);
      Line1->setLine(-2*Radius,0,-2*Radius,-2*Radius);

      Line2=new QGraphicsLineItem(this);
      Line2->setLine(-3*Radius,-2*Radius,-Radius,-2*Radius);
    }
  }
}

/*************************************************************************/

//void _ne_port::is_output(bool Is_output1)
//{
//  Is_output = Is_output1;

//  if (Is_output)
//    Label->setPos(-Radius - Margin - Label->boundingRect().width(), -Label->boundingRect().height()/2);
//  else
//    Label->setPos(Radius + Margin, -Label->boundingRect().height()/2);
//}

/*************************************************************************/

QVector<_ne_connection*>& _ne_port::connections()
{
  return Vec_connections;
}

/*************************************************************************/

//void _ne_port::set_port_flags(int Flags)
//{
//  Port_flags = Flags;

//  if (Port_flags & TypePort){
//    QFont Font(scene()->font());
//    Font.setBold(true);
//    Font.setStretch(80);
//    Label->setFont(Font);
//		setPath(QPainterPath());
//  }
//  else{
//    if (Port_flags & NamePort){
//      QFont Font(scene()->font());
//      Label->setFont(Font);
//      setPath(QPainterPath());
//    }
//  }
//}

/*************************************************************************/

_ne_block* _ne_port::block() const
{
  return Block;
}

/*************************************************************************/

bool _ne_port::is_connected(_ne_port *Port)
{
  foreach(_ne_connection *Conn_aux, Vec_connections)
    if (Conn_aux->start_port() == Port || Conn_aux->end_port() == Port)
			return true;

	return false;
}

/*************************************************************************/

void _ne_port::connected()
{
  if (Port_class==_ne_port_ns::_port_class::PORT_CLASS_BINARY && Port_open==true){
    block()->nodes_editor()->remove_item(Line);
    block()->nodes_editor()->remove_item(Line1);
    block()->nodes_editor()->remove_item(Line2);
    Line=nullptr;
    Line1=nullptr;
    Line2=nullptr;
  }
}

/*************************************************************************/

void _ne_port::unconnected()
{
  if (Port_class==_ne_port_ns::_port_class::PORT_CLASS_BINARY && Port_open==true){
    Line=new QGraphicsLineItem(this);
    Line->setLine(-Radius,0,-2*Radius,0);

    Line1=new QGraphicsLineItem(this);
    Line1->setLine(-2*Radius,0,-2*Radius,-2*Radius);

    Line2=new QGraphicsLineItem(this);
    Line2->setLine(-3*Radius,-2*Radius,-Radius,-2*Radius);
  }
}

/*************************************************************************/

QVariant _ne_port::itemChange(GraphicsItemChange Change, const QVariant &Value)
{
  if (Change == ItemScenePositionHasChanged)
	{
    foreach(_ne_connection *Conn_aux, Vec_connections)
		{
      Conn_aux->update_pos_from_ports();
      Conn_aux->update_path();
		}
	}
  return Value;
}
