//ALI

#ifndef NE_PORT_H
#define NE_PORT_H

#include <QGraphicsPathItem>
#include <string>

namespace _ne_port_ns {

  enum class _port_type:unsigned char {PORT_TYPE_INPUT,PORT_TYPE_OUTPUT};
  enum class _port_class:unsigned char {PORT_CLASS_BINARY,PORT_CLASS_CONTINUOUS};

}

class _ne_block;
class _ne_connection;

/*************************************************************************/

class _ne_port : public QGraphicsPathItem
{
public:
	enum { Type = QGraphicsItem::UserType + 1 };
	enum { NamePort = 1, TypePort = 2 };

  _ne_port(_ne_port_ns::_port_class Port_class1, QGraphicsItem *Parent = nullptr);
  ~_ne_port();

  void block(_ne_block *Block1){Block=Block1;}
  _ne_block* block() const;

  void name(const std::string &Name1);
  std::string name(){return Name;}

  void port_type(_ne_port_ns::_port_type Port_type1,bool Port_open1);
  _ne_port_ns::_port_type port_type(){return Port_type;}

  void port_class(_ne_port_ns::_port_class Port_class1){Port_class=Port_class1;}
  _ne_port_ns::_port_class port_class(){return Port_class;}

//  void port_open(bool Port_open1){Port_open=Port_open1;}
  bool port_open(){return Port_open;}

  void index(int Index1){Index=Index1;}
  int index(){return Index;}
//  void is_output(bool Is_output1);
//  bool is_output(){return  Is_output;};

  int radius(){return Radius;}

  _ne_connection* connection(int Pos1){
    if (Pos1>=0 && Pos1<Vec_connections.size()){
      return Vec_connections[Pos1];
    }
    else return nullptr;
  }

  QVector<_ne_connection*>& connections();

  const std::string port_name() const { return Name; }

	int type() const { return Type; }

  void connected();
  void unconnected();

  bool is_connected(_ne_port *Port);

  int num_conections(){return Vec_connections.size();}

protected:
  QVariant itemChange(GraphicsItemChange Change, const QVariant &Value);

private:
  _ne_block *Block=nullptr;
  std::string Name;
//  bool Is_output;
  _ne_port_ns::_port_type Port_type;
  _ne_port_ns::_port_class Port_class;
  bool Port_open=false;

  // this index is
  // input ports -> what is the number of the output port to which is conected
  // output port -> what positions occupies
  int Index=-1;
  QGraphicsTextItem *Label=nullptr;
  int Radius;
  int Margin;
  QVector<_ne_connection*> Vec_connections;
  QGraphicsLineItem *Line=nullptr;
  QGraphicsLineItem *Line1=nullptr;
  QGraphicsLineItem *Line2=nullptr;
};

#endif
