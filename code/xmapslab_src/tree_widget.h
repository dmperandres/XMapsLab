/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef TREE_WIDGET_H
#define TREE_WIDGET_H

#include <QTreeWidget>
#include <QWidget>
#include <QPoint>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QDrag>
#include <QMimeData>
#include <QPoint>
#include <QApplication>
#include <QPainter>

//#include "window_xmapslab.h"

#include "tree_widget_item.h"

class _window_xmapslab;

// Qt documentation states that user types should begin at this value.
static const int ItemType1 = QTreeWidgetItem::UserType;
static const int ItemType2 = QTreeWidgetItem::UserType + 1;

/*************************************************************************/

class _tree_widget : public QTreeWidget
{
Q_OBJECT

public:
       _tree_widget(_window_xmapslab *Window1, QWidget *Parent1);
  void initialize();

protected slots:
  void context_menu_slot(const QPoint& Pos);
  void add_filter_slot(QTreeWidgetItem *Item);
  void description_slot(QTreeWidgetItem *Item);

protected:
  void show_context_menu(QTreeWidgetItem* Item, const QPoint& Global_pos);

  void mousePressEvent(QMouseEvent *Event);
  void mouseMoveEvent(QMouseEvent *Event);

  _window_xmapslab *Window=nullptr;

  QPoint Drag_start_position;
  _tree_widget_item *Selected_item=nullptr;
  QPixmap Icon;
};

#endif
