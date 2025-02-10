//ALI

#include "ne_block.h"

#include <QPen>
#include <QGraphicsScene>
#include <QFontMetrics>
#include <QPainter>

#include "ne_port.h"
#include "nodes_editor.h"

using namespace std;


//HEA

_ne_block::_ne_block(_nodes_editor *Nodes_editor1, QGraphicsItem *Parent) : QGraphicsPathItem(Parent)
{
  Nodes_editor=Nodes_editor1;

//  QFont Font(Nodes_editor->font());
//  QRect Rectangle=QFontMetrics(Font).boundingRect(_ne_common_ns::SIZE_TEXT);
//  int Width1=Rectangle.width();

  QPainterPath Painter_path;
  Painter_path.addRoundedRect(-50, -50, 100, 100, 5, 5);
  setPath(Painter_path);
  setPen(QPen(Qt::darkGreen));
  setBrush(Qt::green);
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsSelectable);
  Horizontal_margin = 20;
  Vertical_margin = 5;
  Width = Horizontal_margin;
  Height = Vertical_margin;

//  Name_port=nullptr;
//  Type_port=nullptr;
}

//HEA

_ne_port *_ne_block::input_port(int Pos)
{
  if (Vec_input_ports.size()>0){
    if (Pos>=0 && Pos<int(Vec_input_ports.size())) return(Vec_input_ports[Pos]);
    else return(nullptr);
  }
  else return(nullptr);
}

//HEA

_ne_port *_ne_block::output_port(int Pos)
{
  if (Vec_output_ports.size()>0){
    if (Pos>=0 && Pos<int(Vec_output_ports.size())) return(Vec_output_ports[Pos]);
    else return(nullptr);
  }
  else return(nullptr);
}

//HEA

void _ne_block::name(string Name1)
{
  Name=Name1;
  Label_name = new QGraphicsTextItem(this);
}

//HEA

std::string _ne_block::adjusted_name()
{
  QString Name1=QString::fromStdString(Name);
  QStringList Tokens = Name1.split('_');

  if (Filter_type==_filter_ns::_filter_type::FILTER_TYPE_IMAGE){
    return Name1.toStdString();
  }
  else if (Filter_type==_filter_ns::_filter_type::FILTER_TYPE_ELEMENT){
    // get the name of the element
    return Tokens[1].toStdString();
  }
  else{ // remove the number
    return Tokens[0].toStdString();
  }
}

//HEA

bool _ne_block::all_input_ports_connected()
{
  if (Filter_class==_filter_ns::_filter_class::FILTER_CLASS_COMBINATION){
    if (!(Filter_type==_filter_ns::_filter_type::FILTER_TYPE_COMBINATION_ELEMENT_OP || Filter_type==_filter_ns::_filter_type::FILTER_TYPE_COMBINATION_ELEMENT_REMOVE_OP)){ // only one continuous input
      if (Vec_input_ports[1]->num_conections()>0 && Vec_input_ports[2]->num_conections()>0) return true;
    }
    else{ // combination * binary
      if (Vec_input_ports[1]->num_conections()>0) return true;
    }
  }
  else if (Filter_class==_filter_ns::_filter_class::FILTER_CLASS_BINARY){
    if (Num_input_ports_connected==int(Vec_input_ports.size())) return true;
  }
  return false;
}

//HEA

void _ne_block::create(const _filter_ns::_filter_type &Filter_type1, const _filter_ns::_filter_class &Filter_class1, const string &Name1, int Num_filter1, std::vector<_filter_ns::_port_data> &Vec_names_input_ports, std::vector<_filter_ns::_port_data> &Vec_names_output_ports)
{
  Name=Name1;
  Filter_type=Filter_type1;
  Filter_class=Filter_class1;
  Num_filter=Num_filter1;

  //  QFontMetrics fm(Nodes_editor->font());
  //  int w = fm.width("a");
  //  int h = fm.height();

  QFont Font(Nodes_editor->font());
  QRect Rectangle=QFontMetrics(Font).boundingRect("A");
  int w=Rectangle.width();
  int h=Rectangle.height();

  int Border=0;
  float Factor=1;

  int Size;
  if (Vec_names_input_ports.size()>=Vec_names_output_ports.size()) Size=Vec_names_input_ports.size();
  else Size=Vec_names_output_ports.size();


  //  QFont Font(Nodes_editor->font());
  //  QRect Rectangle=QFontMetrics(Font).boundingRect(_ne_common_ns::SIZE_TEXT);
  //  Width=Rectangle.width();

  Width=w*_ne_common_ns::NUM_CHARS_LINE_BLOCK;
  Height=2*Border+(3+Size)*h*Factor;

  QPainterPath p;
  p.addRoundedRect(-Width/2, -Height/2, Width, Height, 5, 5);
  setPath(p);

  // Type
  QGraphicsTextItem *Label_type = new QGraphicsTextItem(this);
  Label_type->setPlainText(QString::fromStdString(_filter_ns::Vec_names_filters[int(Filter_type)]));

  QFont Font1(scene()->font());
  Font1.setBold(true);
  Font1.setStretch(80);
  Label_type->setFont(Font1);
  Label_type->setPos(-Width/2,-Height/2);

  // Name (elided)
  // QFontMetrics Font_metrics(scene()->font());
  QFontMetrics Font_metrics(Nodes_editor->font());
  QString Clipped_text = Font_metrics.elidedText(QString::fromStdString(Name1),Qt::ElideMiddle, Width-w);

  Label_name = new QGraphicsTextItem(this);
  Label_name->setPlainText(Clipped_text);
  QFont Font2(scene()->font());
  Label_name->setFont(Font);
  Label_name->setPos(-Width/2,-Height/2+h);

  Vec_input_ports.resize(Vec_names_input_ports.size());
  for (unsigned int i=0;i<Vec_names_input_ports.size();i++){
    // create the input ports.
    Vec_input_ports[i]= new _ne_port(Vec_names_input_ports[i].Port_class,this);
    Vec_input_ports[i]->name(Vec_names_input_ports[i].Port_name);
    Vec_input_ports[i]->port_type(_ne_port_ns::_port_type::PORT_TYPE_INPUT,Vec_names_input_ports[i].Open);
    Vec_input_ports[i]->block(this);
    Vec_input_ports[i]->setPos(-Width/2 - Vec_input_ports[i]->radius(),-Height/2+(i+3)*h);
  }

  Vec_output_ports.resize(Vec_names_output_ports.size());
  for (unsigned int i=0;i<Vec_names_output_ports.size();i++){
    // create the output ports
    Vec_output_ports[i] = new _ne_port(Vec_names_output_ports[i].Port_class,this);
    Vec_output_ports[i]->name(Vec_names_output_ports[i].Port_name);
    Vec_output_ports[i]->port_type(_ne_port_ns::_port_type::PORT_TYPE_OUTPUT,Vec_names_output_ports[i].Open);
    Vec_output_ports[i]->index(i);
    Vec_output_ports[i]->block(this);
    Vec_output_ports[i]->setPos(Width/2 + Vec_output_ports[i]->radius(),-Height/2+(i+3)*h);
  }
}

//HEA

void _ne_block::set_mat_pos(int Row1,int Col1)
{
  if (Row1>=0 && Col1>=0){
    if (Nodes_editor->get_mat_objects(Row1,Col1)==false){
      Row=Row1;
      Colum=Col1;
      setPos(Colum*Nodes_editor->step_width(),Row*Nodes_editor->step_height());
      Nodes_editor->set_mat_objects(Row,Colum,true);
    }
    else{
      cout << "Error: the position in mat is occoupied " << endl;
      exit(-1);
    }
  }
  else{
    cout << "Error: the position must be >=0 " << endl;
    exit(-1);
  }
}

#include <QStyleOptionGraphicsItem>

//HEA

void _ne_block::paint(QPainter *Painter, const QStyleOptionGraphicsItem *Option, QWidget *Widget)
{
  Q_UNUSED(Option)
  Q_UNUSED(Widget)

	if (isSelected()) {
    Painter->setPen(QPen(Qt::darkYellow));
    Painter->setBrush(Qt::yellow);
  }
  else{ // not selected
    Painter->setPen(QPen(Qt::black));
    Painter->setBrush(_ne_block_ns::Gray);
	}

  Painter->drawPath(path());
}

//HEA

void _ne_block::contextMenuEvent(QGraphicsSceneContextMenuEvent *Event)
{
  if (isSelected()){
    QMenu Menu;
    QAction *Remove_action=Menu.addAction("Remove");
    QAction *Show_action=Menu.addAction("Show full name");
    QAction *Description_action=Menu.addAction("Description");
    QAction *Selection=Menu.exec(Event->screenPos());
    if (Selection!=nullptr){
      if (Selection==Remove_action) Nodes_editor->remove_block(this);
      if (Selection==Show_action){
        QMessageBox::information(Nodes_editor,Nodes_editor->tr("Name information"),QString::fromStdString(Name));
      }
      if (Selection==Description_action){
        QMessageBox::information(Nodes_editor,Nodes_editor->tr("Information"),QString::fromStdString(_filter_ns::Filter_name_text[Filter_type].Description));
      }
    }
  }
}

//HEA

QVector<_ne_port*> _ne_block::ports()
{
  QVector<_ne_port*> Vec_ports;
  foreach(QGraphicsItem *Port_aux, childItems())
	{
    if (Port_aux->type() == _ne_port::Type)
      Vec_ports.append((_ne_port*) Port_aux);
	}
  return Vec_ports;
}

//HEA

QVariant _ne_block::itemChange(GraphicsItemChange Change, const QVariant &Value)
{
  Q_UNUSED(Change);

  return Value;
}

//HEA

//void _ne_block::name(QString Name1)
//{
//  Name=Name1;
////  Name_port->name(Name);
//}

//HEA

//void _ne_block::folter_type(QString Type1)
//{
//  Block_type=Type1;
////  Type_port->name(Block_type);
//}


//HEA
// returns the name of the block that is input in port Pos

_ne_block *_ne_block::block_of_input_port(int Pos)
{
  if (Vec_input_ports.size()>0){
    if (Pos>=0 && Pos<int(Vec_input_ports.size())){
      _ne_port *In_port1=Vec_input_ports[Pos];

      // get the vector of connections. There must be only one connection
      QVector<_ne_connection*> Vec_connections=In_port1->connections();
      if (Vec_connections.size()>0){
        // get the first one
        _ne_connection *Connection=Vec_connections[0];
        // get the output port of the connection, that is the port1
        _ne_port *Out_port1=Connection->start_port();
        // get the block of the output port
        return (Out_port1->block());
      }
      else return(nullptr);
    }
    else return(nullptr);
  }
  else return(nullptr);
}

//HEA

std::string _ne_block::name_of_block_of_input_port(int Pos)
{
  if (Vec_input_ports.size()>0){
    if (Pos>=0 && Pos<int(Vec_input_ports.size())){
      _ne_port *In_port1=Vec_input_ports[Pos];

      // get the vector of connections. There must be only one connection
      QVector<_ne_connection*> Vec_connections=In_port1->connections();
      if (Vec_connections.size()>0){
        // get the first one
        _ne_connection *Connection=Vec_connections[0];
        // get the output port of the connection, that is the port1
        _ne_port *Out_port1=Connection->start_port();

        return Out_port1->block()->name();
      }
      else return("");
    }
    else return("");
  }
  else return("");
}

//HEA

std::string _ne_block::get_name(int Pos)
{
  // get the connection
  _ne_connection *Connection=Vec_input_ports[Pos]->connection(0);
  // get the port
  _ne_port *Port=Connection->start_port();
  // get the block
  _ne_block *Block=Port->block();

  return Block->adjusted_name();
}

//HEA

void _ne_block::update_name()
{

  std::string Name1,Name2,Name3;

  if (Vec_input_ports.size()==1){ // 1 port
    // get the name of port 0
    Name1=get_name(0);

    Name=_filter_ns::Vec_filter_type_name_short[int(Filter_type)]+"("+Name1+")_"+std::to_string(Num_filter);
  }
  else if (Vec_input_ports.size()==2){ // 2 ports
    if (Filter_class==_filter_ns::_filter_class::FILTER_CLASS_BINARY){
      Name1=get_name(0);
      Name2=get_name(1);

      Name="("+Name1+" "+_filter_ns::Vec_filter_type_name_short[int(Filter_type)]+" "+Name2+")_"+std::to_string(Num_filter);
    }
    else if (Filter_class==_filter_ns::_filter_class::FILTER_CLASS_COMBINATION){
      // check if the binary is null
      if (Vec_input_ports[0]->num_conections()==0) Name1="1";
      else Name1=get_name(0);

      Name2=get_name(1);

      Name=Name1+"*("+_filter_ns::Vec_filter_type_name_short[int(Filter_type)]+Name2+")_"+std::to_string(Num_filter);
    }
  }
  else{ // 3 ports
    // check if the binary is null
    if (Vec_input_ports[0]->num_conections()==0) Name1="1";
    else Name1=get_name(0);

    Name2=get_name(1);
    Name3=get_name(2);


    Name=Name1+"*("+Name2+_filter_ns::Vec_filter_type_name_short[int(Filter_type)]+Name3+")_"+std::to_string(Num_filter);
  }

  // Name (elided)
  QFontMetrics Font_metrics(scene()->font());
  QString Clipped_text = Font_metrics.elidedText(QString::fromStdString(Name),Qt::ElideMiddle, Width-10);

  Label_name->setPlainText(Clipped_text);
}
