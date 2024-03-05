/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef GRAPHICS_SCENE_H
#define GRAPHICS_SCENE_H

#include <QGraphicsScene>
#include <QMenu>
#include <QAction>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsView>
#include <QScrollBar>
#include <QMimeData>
#include <iostream>

class _window_xmapslab;

/*************************************************************************/
// This class is for foing the drag and drop od the tree items

class _graphics_scene : public QGraphicsScene
{
Q_OBJECT

public:
  _graphics_scene(_window_xmapslab *Window1){Window=Window1;}

protected:
  void dragEnterEvent(QGraphicsSceneDragDropEvent *Event);
  void dragMoveEvent(QGraphicsSceneDragDropEvent *Event);
  void dropEvent(QGraphicsSceneDragDropEvent *Event);

private:
  _window_xmapslab *Window=nullptr;
};
#endif
