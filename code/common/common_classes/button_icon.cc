//LIC

#include "button_icon.h"

//HEA

_button_icon::_button_icon(int Row1, int Col1)
{
  Row=Row1;
  Col=Col1;
}

//HEA

void _button_icon::mousePressEvent(QMouseEvent *Event)
{
  Q_UNUSED(Event)

  emit change_state(Row,Col);
}

