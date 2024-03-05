/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef TREE_WIDGET_ITEM_H
#define TREE_WIDGET_ITEM_H

#include <QTreeWidgetItem>
#include <QMouseEvent>
#include <iostream>

/*************************************************************************/

class _tree_widget_item : public QTreeWidgetItem
{
public:
  _tree_widget_item(QTreeWidget *Parent, int Type1 = Type):QTreeWidgetItem(Parent,Type1){}
  _tree_widget_item(_tree_widget_item *Tree_widget_item1, int Type1 = Type):QTreeWidgetItem(Tree_widget_item1,Type1){}
};

#endif
