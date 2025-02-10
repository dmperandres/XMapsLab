//LIC

#include "layer_positions_positions.h"
#include "window_positions.h"

//HEA

_layer_positions_positions::_layer_positions_positions()
{
  Layer_type=_layer_positions_ns::_layer_type::LAYER_TYPE_POSITIONS;
}

//HEA

void _layer_positions_positions::reset_data()
{
}

//HEA

void _layer_positions_positions::add_input_data(std::vector<_common_ns::_position_data> &Vec_positions1)
{
  Vec_positions=Vec_positions1;
}

//HEA

void _layer_positions_positions::parameters(int Display_font_size1, int Display_out_circle_size1, QColor Display_font_color1, QColor Display_out_circle_color1, QColor Display_in_circle_color1, QColor Display_selection_out_circle_color1, QColor Display_selection_in_circle_color1)
{
  Display_font_size=Display_font_size1;
  Display_out_circle_size=Display_out_circle_size1;
  Display_font_color=Display_font_color1;
  Display_out_circle_color=Display_out_circle_color1;
  Display_in_circle_color=Display_in_circle_color1;
  Display_selection_out_circle_color=Display_selection_out_circle_color1;
  Display_selection_in_circle_color=Display_selection_in_circle_color1;
}

//HEA

void _layer_positions_positions::draw(QPainter &Painter, float Width1, float Height1, int Font_size1, int Out_circle_size1, QColor Font_color1, QColor Out_circle_color1, QColor In_circle_color1)
{
  float Pos_x;
  float Pos_y;

#ifdef LINUX
  QFont Font("Courier");
#else
  QFont Font("Courier New");
#endif
  Font.setStyleHint(QFont::SansSerif,QFont::NoAntialias);
  Font.setBold(true);
  Font.setPointSize(Font_size1);
  Painter.setFont(Font);

  QFontMetrics Font_metric(Font);
  int Letters_pixels_width;
  int Letters_pixels_height = Font_metric.ascent();

  QPainterPath Path;

  QBrush Brush_out_circle(Out_circle_color1);
  QBrush Brush_in_circle(In_circle_color1);

  QPen Pen_font(Font_color1);
  QPen Pen_out_circle(Out_circle_color1);

  int Radius=Out_circle_size1/2;
  int Step=Radius/3;

  for (unsigned int i=0;i<Vec_positions.size();i++){
    // compute the pixel
    Pos_x=Vec_positions[i].Coordinates.x;
    if (CS_origin==_project_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT){
      // to undone the inversion for OpenGL
      Pos_y=Vec_positions[i].Coordinates.y;
    }
    else{
      Pos_y=int(Height1)-Vec_positions[i].Coordinates.y;
    }

    Painter.setPen(Qt::NoPen);

    QPainterPath Path1,Path2;

    Path1.addEllipse(QPoint(Pos_x,Pos_y),Radius,Radius);
    Path1.addEllipse(QPoint(Pos_x,Pos_y),Radius-Step,Radius-Step);
    Path2.addEllipse(QPoint(Pos_x,Pos_y),Radius-Step,Radius-Step);
    Path2.addEllipse(QPoint(Pos_x,Pos_y),Radius-2*Step,Radius-2*Step);

    Painter.setBrush(Brush_out_circle);
    Painter.drawPath(Path1);
    // In circle
    Painter.setBrush(Brush_in_circle);
    Painter.drawPath(Path2);

    // text
    Painter.setPen(Pen_font);

    // compute the width of the text
    Letters_pixels_width= Font_metric.horizontalAdvance(QString("%1").arg(i+1));

    // check if it is out of the top of image
    int Pos_y_text;

    if ((Pos_y-1-int(Out_circle_size1/2)-Letters_pixels_height)<10){
      // move to the bottom part of the circle
      Pos_y_text=Pos_y+1+int(Out_circle_size1/2)+Letters_pixels_height;
    }
    else{
      Pos_y_text=Pos_y-1-int(Out_circle_size1/2);
    }

    // try to place the text at the middle
    int Pos_x_text;

    if ((Pos_x+Letters_pixels_width/2+1)>(Width1-10)){
      // out by the right -> move to the left
      Pos_x_text=Pos_x-Letters_pixels_width;
    }
    else{
      if ((Pos_x-Letters_pixels_width/2+1)<10){
        // out by the left -> move to the right
        Pos_x_text=Pos_x;
      }
      else{ // it is okay in the middle
        Pos_x_text=Pos_x-Letters_pixels_width/2;
      }
    }

    Painter.drawText(QPointF(Pos_x_text,Pos_y_text),QString("%1").arg(i+1));
  }
}

//HEA

void _layer_positions_positions::update()
{
  if (Image!=nullptr){
    Image->release();
    Image.reset();
  }

  float Width1=float(Width)-1;
  float Height1=float(Height)-1;
  int Pos_x;
  int Pos_y;

  QImage Image1(Width,Height,QImage::Format_ARGB32);
  Image1.fill(Qt::white);
  QPainter Painter(&Image1);

#ifdef LINUX
  QFont Font("Courier");
#else
  QFont Font("Courier New");
#endif
  Font.setStyleHint(QFont::SansSerif,QFont::NoAntialias);
  Font.setBold(true);
  Font.setPointSize(Display_font_size);
  Painter.setFont(Font);

  QFontMetrics Font_metric(Font);
  int Letters_pixels_width;
  int Letters_pixels_height = Font_metric.ascent();

  QBrush Brush_out_circle(Display_out_circle_color);
  QBrush Brush_in_circle(Display_in_circle_color);

  QBrush Brush_selection_out_circle(Display_selection_out_circle_color);
  QBrush Brush_selection_in_circle(Display_selection_in_circle_color);

  QPen Pen_font(Display_font_color);
//  QPen Pen_out_circle(Display_out_circle_color);
//  QPen Pen_in_circle(Display_in_circle_color);

  int Radius=Display_out_circle_size/2;
  int Step=Radius/3;

  for (unsigned int i=0;i<Vec_positions.size();i++){
    // compute the pixel
    Pos_x=Vec_positions[i].Coordinates.x;
    Pos_y=Vec_positions[i].Coordinates.y;

    // Out circle
    Painter.setPen(Qt::NoPen);

    QPainterPath Path1,Path2;

    Path1.addEllipse(QPoint(Pos_x,Pos_y),Radius,Radius);
    Path1.addEllipse(QPoint(Pos_x,Pos_y),Radius-Step,Radius-Step);
    Path2.addEllipse(QPoint(Pos_x,Pos_y),Radius-Step,Radius-Step);
    Path2.addEllipse(QPoint(Pos_x,Pos_y),Radius-2*Step,Radius-2*Step);

    if (Vec_positions[i].Active==false) Painter.setBrush(Brush_out_circle);
    else Painter.setBrush(Brush_selection_out_circle);
    Painter.drawPath(Path1);
    // In circle
    if (Vec_positions[i].Active==false) Painter.setBrush(Brush_in_circle);
    else Painter.setBrush(Brush_selection_in_circle);
    Painter.drawPath(Path2);

    // text
    Painter.setPen(Pen_font);

    // compute the width of the text
    Letters_pixels_width= Font_metric.horizontalAdvance(QString("%1").arg(Vec_positions[i].Position_index));

    // check if it is out of the top of image
    int Pos_y_text;

    if ((Pos_y-1-int(Display_out_circle_size/2)-Letters_pixels_height)<10){
      // move to the bottom part of the circle
      Pos_y_text=Pos_y+1+int(Display_out_circle_size/2)+Letters_pixels_height;
    }
    else{
      Pos_y_text=Pos_y-1-int(Display_out_circle_size/2);
    }

    // try to place the text at the middle
    int Pos_x_text;

    if ((Pos_x+Letters_pixels_width/2+1)>(Width1-10)){
      // out by the right -> move to the left
      Pos_x_text=Pos_x-Letters_pixels_width;
    }
    else{
      if ((Pos_x-Letters_pixels_width/2+1)<10){
        // out by the left -> move to the right
        Pos_x_text=Pos_x;
      }
      else{ // it is okay in the middle
        Pos_x_text=Pos_x-Letters_pixels_width/2;
      }
    }

    Painter.drawText(QPointF(Pos_x_text,Pos_y_text),QString("%1").arg(Vec_positions[i].Position_index));
  }

  if (Position_active==true){
    Pos_x=Vec_positions[Selected_position].Coordinates.x;
    if (CS_origin==_project_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT){
      // to undone the inversion for OpenGL
      Pos_y=Vec_positions[Selected_position].Coordinates.y;
    }
    else{
      Pos_y=int(Height1)-Vec_positions[Selected_position].Coordinates.y;
    }

    Painter.setPen(Qt::NoPen);

    QPainterPath Path1,Path2;

    Path1.addEllipse(QPoint(Pos_x,Pos_y),Radius*2,Radius*2);
    Path1.addEllipse(QPoint(Pos_x,Pos_y),Radius*2-Step,Radius*2-Step);
    Path2.addEllipse(QPoint(Pos_x,Pos_y),Radius*2-Step,Radius*2-Step);
    Path2.addEllipse(QPoint(Pos_x,Pos_y),2*(Radius-Step),2*(Radius-Step));

    // Out circle
    Painter.setBrush(QBrush(QColor(250,250,250)));
    Painter.drawPath(Path1);
    // In circle
    Painter.setBrush(QBrush(Qt::black));
    Painter.drawPath(Path2);
  }

  Painter.end();

  Image=std::make_shared<cv::Mat>(Height,Width,CV_8UC4,const_cast<uchar*>(Image1.bits()), static_cast<size_t>(Image1.bytesPerLine()));
//    Image=make_shared<cv::Mat>(Height,Width,CV_8UC4,const_cast<uchar*>(Image1.bits()));
  *Image=Image->clone();
  cv::flip(*Image,*Image,0);

  // transparence per pixel
  for (unsigned int Pos=0;Pos<Image->total();Pos++){
    cv::Vec4b &Pixel = Image->at<cv::Vec4b>(Pos);
    // if pixel is white
    if (Pixel[0]==255 && Pixel[1]==255 && Pixel[2]==255){
      // set alpha to zero:
      Pixel[3]=0;
    }
  }
}
