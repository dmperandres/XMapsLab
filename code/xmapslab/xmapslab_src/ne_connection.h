//ALI

#ifndef NE_CONNECTION_H
#define NE_CONNECTION_H

#include <QGraphicsPathItem>

class _ne_port;
class _nodes_editor;

//HEA

class _ne_connection : public QGraphicsPathItem
{
public:
	enum { Type = QGraphicsItem::UserType + 2 };

    _ne_connection(_nodes_editor *Nodes_editor1,QGraphicsItem *Parent = nullptr);
  ~_ne_connection();

  void set_start_pos(const QPointF &Pos){Start_pos=Pos;}
  QPointF start_pos(){return Start_pos;}

  void set_end_pos(const QPointF &Pos){End_pos=Pos;}
  QPointF end_pos(){return End_pos;}

  void set_start_port(_ne_port *Port);
  void set_end_port(_ne_port *Port, int Index=0);

  void update_pos_from_ports();
  void update_path();
  void update_final_path();

  _ne_port* start_port() const;
  _ne_port* end_port() const;

	int type() const { return Type; }

  void set_start_col(int Col,int Counter){Col1=Col;Counter_col1=Counter;}
  void set_end_col(int Col,int Counter){Col2=Col;Counter_col2=Counter;}
  void set_row(int Row1,int Counter){Row=Row1;Counter_row=Counter;}

  void paint(QPainter *Painter, const QStyleOptionGraphicsItem *Option, QWidget *Widget);
  void contextMenuEvent(QGraphicsSceneContextMenuEvent *Event);

protected:
  QVariant itemChange(GraphicsItemChange Change, const QVariant &Value);

private:
  QPointF Start_pos;
  QPointF End_pos;
  _ne_port *Start_port=nullptr;
  _ne_port *End_port=nullptr;

  _nodes_editor *Nodes_editor;

  int Col1;
  int Counter_col1;
  int Col2;
  int Counter_col2;
  int Row;
  int Counter_row;
};
#endif
