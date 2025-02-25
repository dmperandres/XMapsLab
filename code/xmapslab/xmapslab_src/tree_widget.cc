//LIC

#include "tree_widget.h"
#include "window_xmapslab.h"
#include <iostream>

//HEA

_tree_widget::_tree_widget(_window_xmapslab *Window1, QWidget *Parent1):QTreeWidget(Parent1)
{
  Window=Window1;

  setContextMenuPolicy(Qt::CustomContextMenu);
  connect(this,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(context_menu_slot(const QPoint&)));

  Selected_item=nullptr;
  Icon.load(":/common/icons/filter.png");
}


//HEA

void _tree_widget::initialize()
{
  reset(); // _tree_widget
  clear();
  Selected_item=nullptr;
}

//HEA

void _tree_widget::context_menu_slot(const QPoint& Pos)
{
  QTreeWidgetItem* item = itemAt(Pos);

  if (item && item->type()==ItemType2){
    // Note: We must map the point to global from the viewport to
    // account for the header.
    show_context_menu(item, viewport()->mapToGlobal(Pos));
  }
  else item->setSelected(false);
}

//HEA

void _tree_widget::show_context_menu(QTreeWidgetItem* Item, const QPoint& globalPos)
{
  Q_UNUSED(Item)
  Q_UNUSED(globalPos)

  QMenu menu;

//  QAction *Add_filter = new QAction(tr("Add filter"),nullptr);
//  connect(Add_filter, &QAction::triggered, [&](){add_filter_slot(Item);});
//  menu.addAction(Add_filter);

//  QAction *Description = new QAction(tr("Description"),nullptr);
//  connect(Description, &QAction::triggered, [&](){description_slot(Item);});
//  menu.addAction(Description);

//  menu.exec(globalPos);
}

//HEA

void _tree_widget::add_filter_slot(QTreeWidgetItem* Item)
{
  QVariant Value=Item->data(0,1);
//  Window->add_filter(Value.toInt()); !!!
}

//HEA

void _tree_widget::description_slot(QTreeWidgetItem* Item)
{
  Q_UNUSED(Item)
//  QVariant Value=Item->data(0,1);

//  Window->description(Value.toInt()); !!!
}

//HEA

void _tree_widget::mousePressEvent(QMouseEvent *Event)
{
  if (Selected_item!=nullptr) Selected_item->setSelected(false);

  Selected_item =(_tree_widget_item *) itemAt(Event->pos());

  if (Selected_item!=nullptr && Selected_item->type()==ItemType2){
    // Note: We must map the point to global from the viewport to
    // account for the header.
    Selected_item->setSelected(true);
    Drag_start_position = Event->pos();
  }
}

//HEA

void _tree_widget::mouseMoveEvent(QMouseEvent *Event)
{
  if (!(Event->buttons() & Qt::LeftButton)) return;
  if ((Event->pos() - Drag_start_position).manhattanLength() < QApplication::startDragDistance()) return;

  if (Selected_item && Selected_item->type()!=ItemType2) return;

  QDrag *Drag = new QDrag(this);
  QMimeData *Mime_data = new QMimeData;

  QString Name_image_or_element;
  if (Selected_item->data(0,1).toInt()==int(_filter_ns::_filter_type::FILTER_TYPE_ELEMENT) || Selected_item->data(0,1).toInt()==int(_filter_ns::_filter_type::FILTER_TYPE_IMAGE)){
    Name_image_or_element=Selected_item->data(0,0).toString();
  }
  // type
  QString Text=Selected_item->data(0,1).toString()+";"+Name_image_or_element;
  //

  // prepare the drag and drop data
  Mime_data->setText(Text);
  Drag->setMimeData(Mime_data);
  Drag->setPixmap(Icon);
  Drag->setHotSpot(QPoint(Icon.width()/2,Icon.height()/2));

  Drag->exec(Qt::CopyAction | Qt::MoveAction);
}
