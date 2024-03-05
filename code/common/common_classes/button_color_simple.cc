/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "button_color_simple.h"
//#include "window_xmapslab.h"

/*************************************************************************/

_button_color_simple::_button_color_simple(QColor Color1, bool Solid_black1, float Factor1)
{
  Color=Color1;
  Solid_black=Solid_black1;

  Button_width=int(float(_button_color_simple_ns::BUTTON_WIDTH)*Factor1);
  if (Button_width%2!=0) Button_width++;

  Button_height=int(float(_button_color_simple_ns::BUTTON_HEIGHT)*Factor1);
  if (Button_height%2!=0) Button_height++;

  setMaximumSize(Button_width,Button_height);
  setMinimumSize(Button_width,Button_height);
}

/*************************************************************************/

QSize _button_color_simple::sizeHint() const
{
  ensurePolished();
  return QSize(_button_color_simple_ns::BUTTON_WIDTH,_button_color_simple_ns::BUTTON_HEIGHT);
}

/*************************************************************************/

QSize _button_color_simple::minimumSizeHint() const
{
    ensurePolished();
    return QSize(_button_color_simple_ns::BUTTON_WIDTH,_button_color_simple_ns::BUTTON_HEIGHT);
}

/*************************************************************************/

void _button_color_simple::color(QColor Color1)
{
  Color=Color1;
  repaint();
}

/*************************************************************************/

void _button_color_simple::paintEvent(QPaintEvent *Event)
{
  Q_UNUSED(Event)

  QPainter Painter(this);

  QRect rect(0,0,Button_width-_button_color_simple_ns::BORDER_SPACE,Button_height-_button_color_simple_ns::BORDER_SPACE);
  QRect rect1(0,0,Button_width-_button_color_simple_ns::BORDER_SPACE,Button_height-_button_color_simple_ns::BORDER_SPACE);

  Painter.fillRect(rect, QBrush(Color));
  Painter.drawRect(rect1);
}

/*************************************************************************/

void _button_color_simple::mouseDoubleClickEvent(QMouseEvent *Event)
{
//  QPoint Pos_mouse=Event->pos();

  if (Event->button()==Qt::LeftButton){
    if (Color_type==_palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE){
      _dialog_pure_color Dialog(&Color,Solid_black);
      Dialog.exec();
    }
    else {
      Color=QColorDialog::getColor(Color,nullptr, "Select Color");
    }

    emit colorChanged(Color);
    update();
  }
}
