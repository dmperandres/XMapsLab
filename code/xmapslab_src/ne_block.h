//ALI

#ifndef NE_BLOCK_H
#define NE_BLOCK_H

#include <QColor>
#include <QFont>

#include <iostream>
#include <QGraphicsPathItem>

#include "ne_connection.h"
#include "filter.h"

class _nodes_editor;
class _ne_port;

namespace _ne_block_ns
{
  const QColor Orange={255,215,0};
  const QColor Gray={240,240,240};
}

/*************************************************************************/

class _ne_block : public QGraphicsPathItem
{
public:
	enum { Type = QGraphicsItem::UserType + 3 };

  _ne_block(_nodes_editor *Nodes_editor1, QGraphicsItem *Parent = nullptr);

  void create(const _filter_ns::_filter_type &Filter_type1, const _filter_ns::_filter_class &Filter_class1, const std::string &Name1, int Num_filter1, std::vector<_filter_ns::_port_data> &Vec_names_input_ports, std::vector<_filter_ns::_port_data> &Vec_names_output_ports);

  void paint(QPainter *Painter, const QStyleOptionGraphicsItem *Option, QWidget *Widget);
  void contextMenuEvent(QGraphicsSceneContextMenuEvent *Event);

  QVector<_ne_port*> ports();

  int type() const { return Type; }

  void set_mat_pos(int Row1,int Col1);
  int get_mat_row(){return Row;}
  int get_mat_col(){return Colum;}

  _nodes_editor *nodes_editor(){return Nodes_editor;}

  void name(std::string Name1);
  std::string name(){return Name;};
  std::string adjusted_name();

  // for using with connections
  std::string get_name(int Pos);

  void filter_type(_filter_ns::_filter_type Filter_type1){Filter_type=Filter_type1;};
  _filter_ns::_filter_type filter_type(){return Filter_type;}

  void filter_class(_filter_ns::_filter_class Filter_class1){Filter_class=Filter_class1;}
  _filter_ns::_filter_class filter_class(){return Filter_class;}

  int num_input_ports(){return Vec_input_ports.size();}
  int num_output_ports(){return Vec_output_ports.size();}

  _ne_port *input_port(int Pos);
  _ne_port *output_port(int Pos);

  _ne_block *block_of_input_port(int Pos);
  std::string name_of_block_of_input_port(int Pos);

//  int num_inputs(){return Num_inputs;}
  void count_input_connections(){Num_input_ports_connected++;}
  void reset_input_connections(){Num_input_ports_connected=0;}

  void count_output_connections(){Num_output_ports_connected++;}
  void reset_output_connections(){Num_output_ports_connected=0;}

  bool all_input_ports_connected();

  void update_name();

protected:
  QVariant itemChange(GraphicsItemChange Change, const QVariant &Value);

private:
  int Horizontal_margin;
  int Vertical_margin;
  int Width;
  int Height;
  int Row;
  int Colum;

  _nodes_editor *Nodes_editor=nullptr;

  QGraphicsTextItem *Label_name=nullptr;

//  _ne_port *Name_port;
//  _ne_port *Type_port;
  std::vector<_ne_port *> Vec_input_ports;
  std::vector<_ne_port *> Vec_output_ports;
  std::vector<int> Vec_index_input_ports;

//  int Num_inputs;
  std::string Name;
  _filter_ns::_filter_type Filter_type;
  _filter_ns::_filter_class Filter_class;
//  unsigned char Num_channels;

  // this allow to maintain the number if the name is changed
  int Num_filter=0;

  int Num_input_ports_connected=0;
  int Num_output_ports_connected=0;
};
#endif
