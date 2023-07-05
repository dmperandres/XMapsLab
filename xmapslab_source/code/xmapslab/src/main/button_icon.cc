/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#include "button_icon.h"
#include "table_layers.h"

/*************************************************************************/

_button_icon::_button_icon(int Row1, int Col1)
{
  Row=Row1;
  Col=Col1;
}

/*************************************************************************/

void _button_icon::mousePressEvent(QMouseEvent *Event)
{
  Q_UNUSED(Event)

  emit change_state(Row,Col);
}

