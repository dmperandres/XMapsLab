/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#include "splitter.h"
#include "splitter_handle.h"

/*************************************************************************/

_splitter::_splitter(Qt::Orientation orientation, QWidget *parent):QSplitter(orientation,parent)
{
}

/*************************************************************************/

QSplitterHandle *_splitter::createHandle()
{
  return new _splitter_handle(orientation(), this);
}
