//LIC

#ifndef COLOR_BAR_INTEPOLATION_H
#define COLOR_BAR_INTEPOLATION_H

#include "color_bar_abstract.h"

class _window_xmapslab;
 
class _color_bar_interpolation : public _color_bar_abstract
{
Q_OBJECT

public:
  _color_bar_interpolation(_palette_data_ns::_palette_color_type Palette_color_type1,int Num_stops1, std::vector<float> &Vec_values1, std::vector<QColor> &Vec_colors1,_window_xmapslab *Window1=nullptr);

  std::vector<QColor> create_random_colors();

  void draw(QPainter &Painter, QRect Rect,int Font_size);

//signals:
//  void colorChanged(std::vector<float> &Vec_values1,std::vector<QColor> &Vec_colors1);

protected:
  void mousePressEvent(QMouseEvent *Event) override;
  void mouseMoveEvent(QMouseEvent *Event) override;
  void mouseReleaseEvent(QMouseEvent*) override;
  void mouseDoubleClickEvent(QMouseEvent *Event) override;
  void paintEvent(QPaintEvent *Event) override;

private:
  void compute_tones();
};


#endif
