/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "layer_data_xmapslab.h"

/*************************************************************************/

_layer_data_xmapslab::_layer_data_xmapslab(QString Name1,unsigned int Pos_texture1)
{
  Button_visibility=nullptr;
  Button_writability=nullptr;
  Visibility=true;
  Writability=true;
  Transparence=0;
//  Palette=0;
  Name=QString(Name1);
  Pos_texture=Pos_texture1;
}
