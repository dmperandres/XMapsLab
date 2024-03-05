 #include "best_color.h"

QColor _best_color::best_color_between_bw(QColor Color1)
{
  int Lightness = (Color1.red() * 0.299) + (Color1.green() * 0.587) + (Color1.blue() * 0.114);
  if (Lightness<=128) return(Qt::white);
  else return(Qt::black);
}
