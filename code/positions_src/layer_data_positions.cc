#include "layer_data_positions.h"

_layer_data_positions::_layer_data_positions(QString Name1,unsigned int Pos_texture1)
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
