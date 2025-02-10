//LIC

#ifndef LAYER_DATA_POSITIONS_H
#define LAYER_DATA_POSITIONS_H

#include <QString>

class _button_icon;

class _layer_data_positions
{
public:

  _layer_data_positions(QString Name1="",unsigned int Pos_texture1=0);

  void visibility(bool State){Visibility=State;}
  bool visibility(){return Visibility;}

  void writability(bool State){Writability=State;}
  bool writability(){return Writability;}

  void transparence(float Transparence1){Transparence=Transparence1;}
  float transparence(){return Transparence;}

  void pos_texture(unsigned int Pos_texure1){Pos_texture=Pos_texure1;}
  unsigned int pos_texure(){return Pos_texture;}

  void button_visibility(_button_icon *Button){Button_visibility=Button;}
  _button_icon *button_visibility(){return Button_visibility;}

  void button_writability(_button_icon *Button){Button_writability=Button;}
  _button_icon *button_writability(){return Button_writability;}

  void name(QString Name1){Name=Name1;}
  QString name(){return Name;}


private:
  _button_icon *Button_visibility;
  _button_icon *Button_writability;
  bool Visibility;
  bool Writability;
  float Transparence;
//  unsigned int Palette;
  QString Name;
  unsigned int Pos_texture;
};

#endif
