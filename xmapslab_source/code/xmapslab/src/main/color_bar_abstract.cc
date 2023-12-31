/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#include "color_bar_abstract.h"
#include "window.h"

using namespace _color_bar_abstract_ns;

/*************************************************************************/

_color_bar_abstract::_color_bar_abstract(_palette_data_ns::_color_type Color_type1, int Num_steps1, std::vector<float> &Vec_values1, std::vector<QColor> &Vec_colors1, _window *Window1):
Window(Window1)
{
  // margins
  setContentsMargins(0, 0, 0, 0);
  // borders
  setStyleSheet("border: none;");
  // Establece la bandera de ventana sin marco para eliminar los bordes del sistema operativo
  setWindowFlags(Qt::FramelessWindowHint);
  // padding
  setStyleSheet("QWidget { padding: 0px; }");

  if (Num_steps1>=2){
    Color_box_width=COLOR_BOX_WIDTH*Window->screen_height()/1080;
    if (Color_box_width%2!=0) Color_box_width++;

    Num_steps=Num_steps1;
    Color_type=Color_type1;

    Vec_original_values=Vec_values1;
    Vec_original_colors=Vec_colors1;

    Vec_values=Vec_values1;
    Vec_colors=Vec_colors1;

    Changeable=CHANGEABLE_DEFAULT;

//    QFont Font=font();
//    QFontMetrics Font_metric(Font);
//    int Width_char=Font_metric.horizontalAdvance("________.___")*Window->screen_height()/1080;

//    setMinimumWidth(Width_char);
//    setMaximumWidth(Width_char);
  }
  else{
    std::cout << "Error: the number of steps must greater or equal to 2" << std::endl;
    exit(-1);
  }
}

/*************************************************************************/

QSize _color_bar_abstract::sizeHint() const
{
  ensurePolished();
  return QSize(100,300);
}

/*************************************************************************/

QSize _color_bar_abstract::minimumSizeHint() const
{
    ensurePolished();
    return QSize(100,300);
}

/*************************************************************************/

int _color_bar_abstract::row_at(QPoint Pos1)
{
  for (unsigned int i=0;i<Vec_rect.size();i++){
    if (Vec_rect[i].contains(Pos1)){
      return i;
    }
  }
  return -1;
}

/*************************************************************************/

bool _color_bar_abstract::pos_in_bar(QPoint Pos1)
{

  if (Rect_bar.contains(Pos1)){
    return true;
  }
  return false;
}

/*************************************************************************/

void _color_bar_abstract::paintCell(QPainter* Painter, int Pos, const QRect &Rect)
{
  Painter->fillRect(Rect, QColor(Vec_colors[Pos]));
  Painter->drawRect(Rect);
}

/*************************************************************************/

QColor _color_bar_abstract::compute_new_tone(float Value, QColor Color1)
{
  QColor Color;

  Color.setHsv(Color1.hue(),int(255.0f*Value),Color1.value(),255);

  return(Color.toRgb());
}

/*************************************************************************/

QColor _color_bar_abstract::compute_new_color()
{
  std::random_device Random_device;   // non-deterministic generator
  std::mt19937 Generator(Random_device());  // to seed mersenne twister.
  std::uniform_int_distribution<> Random(0,359);
  QColor Color;

  Color.setHsv(Random(Generator),255,255);

  return(Color.toRgb());
}

/*************************************************************************/

void _color_bar_abstract::draw_text_int(QPainter &Painter)
{
  int Pos;
  int HFont_pos=3*Color_box_width+Font_pixels_width/3;

  int Step=(End_value-Start_value) ;
  Pos=Widget_height/(Num_steps);

  Painter.drawText(QPointF(HFont_pos,Font_pixels_height/2), QString("%1").arg(int(End_value)));
  for (int i=1;i<Num_steps-1;i++){
    Painter.drawText(QPointF(HFont_pos,int((1-Vec_proportions[i])*float(Widget_height-1))+Font_pixels_height/2), QString("%1").arg(int(Vec_proportions[i]*float(Step))+int(Start_value)));
  }
  Painter.drawText(QPointF(HFont_pos,float(Num_steps)*Pos+Font_pixels_height/2), QString("%1").arg(int(Start_value)));
}

/*************************************************************************/

int compute_log_value(float Value)
{
  int Log10=log10f(Value);
  if (Log10<0) Log10=1;
  else Log10=Log10+2;

  return Log10;
}

void _color_bar_abstract::draw_text_float(QPainter &Painter)
{
  int Pos;
  int HFont_pos=3*Color_box_width+Font_pixels_width/3;

  float Step=End_value-Start_value;
  Pos=Widget_height/(Num_steps);

  int Num_decimals=_common_ns::NUM_MAX_DECIMALS-compute_log_value(End_value);
  if (Num_decimals<0) Num_decimals=0;

  Painter.drawText(QPointF(HFont_pos,Font_pixels_height/2), QString::number(End_value,'f',Num_decimals));
  for (int i=1;i<Num_steps-1;i++){
    Painter.drawText(QPointF(HFont_pos,int((1-Vec_proportions[i])*float(Widget_height-1))+Font_pixels_height/2), QString::number(Vec_proportions[i]*Step+Start_value,'f',Num_decimals));
  }
  Painter.drawText(QPointF(HFont_pos,float(Num_steps)*Pos+Font_pixels_height/2), QString::number(Start_value,'f',Num_decimals));
}

/*************************************************************************/

void _color_bar_abstract::draw_text_scientific(QPainter &Painter)
{
  int Pos;
  int HFont_pos=3*Color_box_width+Font_pixels_width/3;

  float Step=End_value-Start_value;
  Pos=Widget_height/(Num_steps);

  int Num_decimals=_common_ns::NUM_MAX_DECIMALS-compute_log_value(End_value);
  if (Num_decimals<0) Num_decimals=0;

  Painter.drawText(QPointF(HFont_pos,Font_pixels_height/2), QString::number(End_value,'g',Num_decimals));
  for (int i=1;i<Num_steps-1;i++){
    Painter.drawText(QPointF(HFont_pos,int((1-Vec_proportions[i])*float(Widget_height-1))+Font_pixels_height/2), QString::number(Vec_proportions[i]*Step+Start_value,'g',Num_decimals));
  }
  Painter.drawText(QPointF(HFont_pos,float(Num_steps)*Pos+Font_pixels_height/2), QString::number(Start_value,'g',Num_decimals));
}

/*************************************************************************/

void _color_bar_abstract::draw_text_percent(QPainter &Painter)
{
  int Pos;
  int HFont_pos=3*Color_box_width+Font_pixels_width/3;

  int Step=100;
  Pos=Widget_height/(Num_steps);

  Painter.drawText(QPointF(HFont_pos,Font_pixels_height/2), QString::number(100,'i',0)+"%");
  for (int i=1;i<Num_steps-1;i++){
    Painter.drawText(QPointF(HFont_pos,int((1-Vec_proportions[i])*float(Widget_height-1))+Font_pixels_height/2), QString::number(int(Vec_proportions[i]*float(Step)),'i',0)+"%");
  }
  Painter.drawText(QPointF(HFont_pos,float(Num_steps)*Pos+Font_pixels_height/2), QString::number(0,'i',0)+"%");
}

