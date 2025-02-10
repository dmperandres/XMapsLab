//LIC

#include "color_bar_sections.h"

//HEA

_color_bar_sections::_color_bar_sections(_palette_data_ns::_palette_color_type Palette_color_type1, int Num_stops1, std::vector<float> &Vec_values1, std::vector<QColor> &Vec_colors1, _common_ns::_zero_color Zero_color1, _window_xmapslab *Window1):
_color_bar_abstract(Palette_color_type1,Num_stops1,Vec_values1,Vec_colors1,Window1)
{
  Palette_type=_palette_data_ns::_palette_type::PALETTE_TYPE_DISCRETE;
  Zero_color=Zero_color1;

  Vec_rect.resize(Num_stops1);
  Vec_translations.resize(Num_stops1);
  Vec_proportions.resize(Num_stops1);

  // compute the proportions
  for (int i=0;i<Num_stops1; ++i) {
    Vec_proportions[i]=Vec_values1[i];
  }

  End_color=Vec_colors1[Num_stops1-1];
}


//HEA

void _color_bar_sections::compute_tones()
{
  if (End_color!=QColor(0,0,0)){
    float t;
    std::random_device Random_device;   // non-deterministic generator
    std::mt19937 Generator(Random_device());  // to seed mersenne twister.
    std::uniform_int_distribution<> Random(0,359);
    QColor Color=End_color;
    Color.toHsv();
    float Hue=Color.hue();

    Vec_colors.resize(Vec_values.size());

    for (unsigned int i=0;i<Vec_colors.size()-1;i++) {
      t=float(i)/float(Vec_colors.size()-2);
      if  (Zero_color==_common_ns::_zero_color::ZERO_COLOR_WHITE){
        Color.setHsv(Hue,int(t*255.0),255);
      }
      else{
        Color.setHsv(Hue,255,int(t*255.0));
      }
      Vec_colors[i]=Color.toRgb();
    }
    Vec_colors[Vec_colors.size()-1]=Vec_colors[Vec_colors.size()-2];
  }
  else{
    // Black color
    QColor Color;
    float t;
    Vec_colors.resize(Vec_values.size());

    for (unsigned int i=0;i<Vec_colors.size()-1;i++) {
      t=float(i)/float(Vec_colors.size()-2);
      Color.setHsv(0,0,(1.0f-t)*255);
      Vec_colors[i]=Color.toRgb();
    }
    Vec_colors[Vec_colors.size()-1]=Vec_colors[Vec_colors.size()-2];
  }
}

//HEA

void _color_bar_sections::paintEvent(QPaintEvent *Event)
{
  // size of the colorbar
  QRect Rect = Event->rect();

  QPainter Painter(this);

  QFont Font(QApplication::font());
  Font_size=Font.pointSize();

  // compute the space of a '0'
  QFontMetrics Font_metric(Font);
  QRect Rect_char=Font_metric.boundingRect('0');
  Font_pixels_width=Rect_char.width();
  Font_pixels_height=Rect_char.height();

  // compute the parameters
  // border
  int Border_space_width=int(roundf(float(Font_pixels_width)*_color_bar_abstract_ns::BORDER_SPACE_FACTOR));
  if (Border_space_width<1) Border_space_width=1;

  int Border_space_height=int(roundf(float(Font_pixels_height)*_color_bar_abstract_ns::BORDER_SPACE_FACTOR));
  if (Border_space_height<1) Border_space_height=1;

  // white space
  int White_space_width=int(roundf(float(Font_pixels_width)*_color_bar_abstract_ns::WHITE_SPACE_FACTOR));
  if (White_space_width<1) White_space_width=1;

  // color box. It must be odd
  Color_box_width=int(roundf(float(Font_pixels_width)*_color_bar_abstract_ns::COLOR_BOX_FACTOR));
  if (Color_box_width<_color_bar_abstract_ns::COLOR_BOX_MIN) Color_box_width=_color_bar_abstract_ns::COLOR_BOX_MIN;
  if (Color_box_width%2!=0) Color_box_width++;

  // removes the borders
  Widget_width = Rect.width()-2*Border_space_width; // Border -- Border/
  Widget_height = Rect.height()-3*Border_space_height; // 2 border spaces in the bottom

  // the color box square
  QRect rect(0,0,Color_box_width,Color_box_width);

  // compute the translations of each color box that is drawn
  Vec_translations[0]=Widget_height-1;
  for (int i=1;i<Num_stops; ++i) {
    Vec_translations[i]=int(roundf((1.0f-Vec_proportions[i])*float(Widget_height-1)));
  }  
  Vec_translations[Num_stops-1]=0;

  // draw each color box
  for (int i=0;i<Num_stops-1; ++i) {
    rect.translate(Border_space_width,Vec_translations[i]+Font_pixels_height-Color_box_width);
    Vec_rect[i]=rect;
    paintCell(&Painter,i,rect);
    rect.translate(-Border_space_width,-(Vec_translations[i]+Font_pixels_height-Color_box_width));
  }

  // places the origin Font_pixels_height below
  Painter.translate(0,Font_pixels_height);

  // draw color bar
  QLinearGradient linearGrad(QPointF(Color_box_width+White_space_width,0),  QPointF(Color_box_width,Widget_height-1));

  Rect_bar=QRect(Border_space_width+Color_box_width+White_space_width,0,Color_box_width,Widget_height-1);

  for (int i=0;i<Num_stops-1; ++i) {
    linearGrad.setColorAt(1-Vec_proportions[i],Vec_colors[i]);
    linearGrad.setColorAt(1-Vec_proportions[i+1]+0.001,Vec_colors[i]);
  }

  QRect rect_linear(Border_space_width+Color_box_width+White_space_width,0,Color_box_width,Widget_height-1);

  Painter.fillRect(rect_linear, linearGrad);
  Painter.drawRect(rect_linear);

  // draw lines
  int Line_pos1=Border_space_width+Color_box_width;
  int Line_pos2=Border_space_width+2*(Color_box_width+White_space_width);

  Painter.drawLine(QPointF(Line_pos1,0),QPointF(Line_pos2,0));
  for (int i=1;i<Num_stops;i++){
    Painter.drawLine(QPointF(Line_pos1,int(roundf((1.0f-Vec_proportions[i])*float(Widget_height-1)))),QPointF(Line_pos2,int(roundf((1.0f-Vec_proportions[i])*float(Widget_height-1)))));
  }
  Painter.drawLine(QPointF(Line_pos1,Widget_height-1),QPointF(Line_pos2,Widget_height-1));

  // text
  Painter.setFont(Font);
  if (Show_data){
    switch (Data_type_print) {
    case _palette_data_ns::_data_type_print::DATA_TYPE_PRINT_INT:draw_text_int(Painter);break;
    case _palette_data_ns::_data_type_print::DATA_TYPE_PRINT_FLOAT:draw_text_float(Painter);break;
    case _palette_data_ns::_data_type_print::DATA_TYPE_PRINT_SCIENTIFIC:draw_text_scientific(Painter);break;
    case _palette_data_ns::_data_type_print::DATA_TYPE_PRINT_PERCENT:draw_text_percent(Painter);break;
    }
  }
}



//HEA

void _color_bar_sections::mousePressEvent(QMouseEvent *Event)
{
  if (Changeable){
    QPoint Pos=Event->pos();

    // check if is pressing on a color
    if ((Pos_selected=row_at(Pos))>0 && Pos_selected<Num_stops){
      Initial_position=Pos;
      Offset=Pos-Vec_rect[Pos_selected].bottomLeft();
      Color_selected=true;
      Color_selected_rect=Vec_rect[Pos_selected];

    }
  }
}

//HEA

void _color_bar_sections::mouseMoveEvent(QMouseEvent *Event)
{
  if (Changeable){
    if (Color_selected){
      QPoint Pos=Event->pos();
      QPoint Diff=Initial_position-Pos;

      if (fabs(Diff.y())>1){
        float Prop_previous=Vec_proportions[Pos_selected-1];
        float Prop_next=Vec_proportions[Pos_selected+1];
        float Prop_new=1-(float(Pos.y()-Offset.y()-Font_pixels_height)/float(Widget_height-1));

        if (Prop_new>Prop_previous && Prop_new<Prop_next){
          Vec_proportions[Pos_selected]=Prop_new;
          repaint();
        }
      }
    }
  }
}

//HEA

void _color_bar_sections::mouseReleaseEvent(QMouseEvent *Event)
{
  if (Changeable){
    if (Color_selected){
      QPoint Pos=Event->pos();
      QPoint Diff=Initial_position-Pos;

      if (fabs(Diff.y())>1){
        float Prop_previous=Vec_proportions[Pos_selected-1];
        float Prop_next=Vec_proportions[Pos_selected+1];
        float Prop_new=1-(float(Pos.y()-Offset.y()-Font_pixels_height)/float(Widget_height-1));

        if (Prop_new>Prop_previous && Prop_new<Prop_next){
          Vec_proportions[Pos_selected]=Prop_new;
          repaint();
        }
        Color_selected=false;
        emit colorChanged(Vec_proportions,Vec_colors,int(Palette_type));
        Event->accept();
      }
    }
    else Event->ignore();
  }
}

//HEA

void _color_bar_sections::mouseDoubleClickEvent(QMouseEvent *Event)
{
  if (Changeable){
    QPoint Pos_mouse=Event->pos();
    int Pos=row_at(Pos_mouse);

    if (Pos>=0){
      if (Event->button()==Qt::LeftButton){
        if (Palette_color_type==_palette_data_ns::_palette_color_type::PALETTE_COLOR_TYPE_SINGLE_TONE){
          if (Pos==Num_stops-2){
            QColor Color=End_color;

            _dialog_pure_color Dialog(this, &Color);
            if (Dialog.exec()==QDialog::Accepted){
              End_color=Color;
            }
            compute_tones();
            emit colorChanged(Vec_proportions,Vec_colors,int(Palette_type));
            update();
          }
        }
        else{
          if (Pos>=0){
            Vec_colors[Pos]=QColorDialog::getColor(Vec_colors[Pos],nullptr, "Select Color");
            emit colorChanged(Vec_proportions,Vec_colors,int(Palette_type));
            update();
          }
        }
      }
      else{
        if (Event->button()==Qt::RightButton){
          // remove the milestone
          if (Num_stops>3){
            if (row_at(Pos_mouse)!=0 && row_at(Pos_mouse)!=int(Vec_proportions.size()-2)){

              Vec_values.erase(Vec_values.begin()+Pos);
              Vec_colors.erase(Vec_colors.begin()+Pos);
              Vec_proportions.erase(Vec_proportions.begin()+Pos);

              Num_stops--;

              emit colorChanged(Vec_proportions,Vec_colors,int(Palette_type));
              update();
            }
          }
        }
      }
    }
    else{
      // check if the click is on the bar
      if (Event->button()==Qt::LeftButton){
        if (pos_in_bar(Pos_mouse)){
          // compute the proportion
          float Prop_new=1-(float(Pos_mouse.y()-Offset.y()-Font_pixels_height)/float(Widget_height-1));

          // search for the position of the proportion
          int Pos_aux;
          for (Pos_aux=0;Pos_aux<int(Vec_proportions.size());Pos_aux++){
            if (Vec_proportions[Pos_aux]>Prop_new) break;
          }

          // check that is not after the last milstone
          if (Pos_aux<int(Vec_proportions.size()-1)){

            Vec_values.insert(Vec_values.begin()+Pos_aux,Prop_new);
            Vec_proportions.insert(Vec_proportions.begin()+Pos_aux,Prop_new);
            Vec_colors.insert(Vec_colors.begin()+Pos_aux,compute_new_tone(Prop_new,End_color));

            // only need to add one element. Then the correct values are computed
            Vec_translations.push_back(0);

            // the new rect must be added to allow changing the color
            QRect Rect(0,0,Color_box_width,Color_box_width);
            Rect.translate(0,int((1-Prop_new)*float(Widget_height-1))-Color_box_width/2+Font_pixels_height);

            Vec_rect.insert(Vec_rect.begin()+Pos_aux,Rect);

            Num_stops++;

            emit colorChanged(Vec_proportions,Vec_colors,int(Palette_type));
            update();
          }
        }
      }
    }
  }
}

//HEA

//void _color_bar_sections::draw(QPainter &Painter, QRect Rect, int Font_size)
//{
////  int Offset_x=Rect.x();
////  int Offset_y=Rect.y();
//  Widget_height = Rect.height();
//  Widget_width = Rect.width();

////  Painter.translate(Offset_x,Offset_y);

//  QFont Font=Painter.font();
//  Font.setPointSize(Font_size);
////  Font_size=Font.pointSize();

//  QFontMetrics Font_metric(Font);
//  QRect Rect_char=Font_metric.boundingRect('0');
//  Font_pixels_width=Rect_char.width();
//  Font_pixels_height=Rect_char.height();

//  // compute the size of the widget with
//  Widget_height = Rect.height()-Font_pixels_height*2;
//  Widget_width = Rect.width()-Font_pixels_width;

//  Painter.translate(0,Font_pixels_height);

//  int Horizontal_space=Font_pixels_width/2;

//  Color_box_width=Font_pixels_width*1.5;
//  if (Color_box_width%2!=0) Color_box_width++;

//  QRect rect(0,0,Color_box_width,Color_box_width);

//  Vec_translations[0]=Widget_height-1;
//  for (int i=0;i<Num_steps; ++i) {
//    Vec_translations[i]=int((1-Vec_proportions[i])*float(Widget_height-1));
//  }
//  Vec_translations[Num_steps-1]=0;

//  for (int i=0;i<Num_steps-1; ++i) {
//    rect.translate(0,Vec_translations[i]-Color_box_width);
//    Vec_rect[i]=rect;
//    paintCell(&Painter,i,rect);
//    rect.translate(0,-(Vec_translations[i]-Color_box_width));
//  }

//  // gradient
//  QLinearGradient linearGrad(QPointF(Color_box_width+Horizontal_space,0), QPointF(Color_box_width,Widget_height));
//  for (int i=0;i<Num_steps-1; ++i) {
//    linearGrad.setColorAt(1-Vec_proportions[i],Vec_colors[i]);
//    linearGrad.setColorAt(1-Vec_proportions[i+1]+0.001, Vec_colors[i]);

//  }

//  QRect rect_linear(Color_box_width+Horizontal_space,0,Color_box_width,Widget_height);

//  Painter.fillRect(rect_linear, linearGrad);
//  Painter.drawRect(rect_linear);

//  // lines
//  int Line_pos1=Color_box_width;
//  int Line_pos2=2*(Color_box_width+Horizontal_space);

//  Painter.drawLine(QPointF(Line_pos1,0),QPointF(Line_pos2,0));
//  for (int i=1;i<Num_steps;i++){
//    Painter.drawLine(QPointF(Line_pos1,int((1-Vec_proportions[i])*float(Widget_height))),QPointF(Line_pos2,int((1-Vec_proportions[i])*float(Widget_height))));
//  }
//  Painter.drawLine(QPointF(Line_pos1,Widget_height),QPointF(Line_pos2,Widget_height));

//  // text
//  if (Show_data){
//    switch (Data_type_print) {
//    case _palette_data_ns::_data_type_print::DATA_TYPE_PRINT_INT:draw_text_int(Painter);break;
//    case _palette_data_ns::_data_type_print::DATA_TYPE_PRINT_FLOAT:draw_text_float(Painter);break;
//    case _palette_data_ns::_data_type_print::DATA_TYPE_PRINT_SCIENTIFIC:draw_text_scientific(Painter);break;
//    case _palette_data_ns::_data_type_print::DATA_TYPE_PRINT_PERCENT:draw_text_percent(Painter);break;
//    }
//  }
//}

void _color_bar_sections::draw(QPainter &Painter, QRect Rect, int Font_size)
{
  Widget_height = Rect.height();
  Widget_width = Rect.width();

  QFont Font=Painter.font();
  Font.setPointSize(Font_size);

  QFontMetrics Font_metric(Font);
  QRect Rect_char=Font_metric.boundingRect('0');
  Font_pixels_width=Rect_char.width();
  Font_pixels_height=Rect_char.height();

  Widget_height = Rect.height()-Font_pixels_height*2;
  Widget_width = Rect.width()-Font_pixels_width;

  int Horizontal_space=Font_pixels_width/2;

  Color_box_width=Font_pixels_width*1.5;
  if (Color_box_width%2!=0) Color_box_width++;

  QRect rect(0,0,Color_box_width,Color_box_width);

  Vec_translations[0]=Widget_height-Color_box_width-1;
  for (int i=1;i<Num_stops-1; ++i) {
    Vec_translations[i]=int((1-Vec_proportions[i])*float(Widget_height-1))-Color_box_width/2;
  }
  Vec_translations[Num_stops-1]=0;

  for (int i=0;i<Num_stops; ++i) {
    rect.translate(0,Vec_translations[i]+Font_pixels_height);
    Vec_rect[i]=rect;
    paintCell(&Painter,i,rect);
    rect.translate(0,-(Vec_translations[i]+Font_pixels_height));
  }

  Painter.translate(0,Font_pixels_height);

  // gradient
  QLinearGradient linearGrad(QPointF(Color_box_width+Horizontal_space,0), QPointF(Color_box_width,Widget_height));
  for (int i=0;i<Num_stops-1; ++i) {
    linearGrad.setColorAt(1-Vec_proportions[i],Vec_colors[i]);
    linearGrad.setColorAt(1-Vec_proportions[i+1]+0.001, Vec_colors[i]);
  }
  QRect rect_linear(Color_box_width+Horizontal_space,0,Color_box_width,Widget_height-1);

  Painter.fillRect(rect_linear, linearGrad);
  Painter.drawRect(rect_linear);

  // lines
  int Line_pos1=Color_box_width;
  int Line_pos2=2*(Color_box_width+Horizontal_space);

  Painter.drawLine(QPointF(Line_pos1,0),QPointF(Line_pos2,0));
  for (int i=1;i<Num_stops-1;i++){
    Painter.drawLine(QPointF(Line_pos1,int((1-Vec_proportions[i])*float(Widget_height-1))),QPointF(Line_pos2,int((1-Vec_proportions[i])*float(Widget_height-1))));
  }
  Painter.drawLine(QPointF(Line_pos1,Widget_height-1),QPointF(Line_pos2,Widget_height-1));

  // text
  if (Show_data){
    switch (Data_type_print) {
    case _palette_data_ns::_data_type_print::DATA_TYPE_PRINT_INT:draw_text_int(Painter);break;
    case _palette_data_ns::_data_type_print::DATA_TYPE_PRINT_FLOAT:draw_text_float(Painter);break;
    case _palette_data_ns::_data_type_print::DATA_TYPE_PRINT_SCIENTIFIC:draw_text_scientific(Painter);break;
    case _palette_data_ns::_data_type_print::DATA_TYPE_PRINT_PERCENT:draw_text_percent(Painter);break;
    }
  }
}
