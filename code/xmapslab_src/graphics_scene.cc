/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "graphics_scene.h"
#include "window_xmapslab.h"
#include <iostream>

using namespace std;

// the information for doing the drag-and-drop is taken from:
// http://doc.qt.io/qt-4.8/dnd.html

/*************************************************************************/
// Not clear to me: this function must be defined although it makes nothing

void _graphics_scene::dragEnterEvent(QGraphicsSceneDragDropEvent *Event)
{
  Q_UNUSED(Event)
}

/*************************************************************************/
// Not clear to me: this function must be defined although it makes nothing

void _graphics_scene::dragMoveEvent(QGraphicsSceneDragDropEvent *Event)
{
  Q_UNUSED(Event)
}

/*************************************************************************/

void _graphics_scene::dropEvent(QGraphicsSceneDragDropEvent *Event)
{
  const QMimeData* Mime = Event->mimeData();

  if (Mime->hasText()) {
    QPointF Position=Event->scenePos();
    QString Text=Mime->text();

    auto Parts = Text.split(';');
    string Element;
    int Type=Parts[0].toInt();
    if (Parts.size()==2){
      Element=Parts[1].toStdString();
    }

    Window->add_filter(Type,Element,float(Position.x()),Position.y());
    Event->acceptProposedAction();
  }
}

