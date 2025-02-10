//LIC

#include "layer_data_xmapslab.h"

//HEA

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
