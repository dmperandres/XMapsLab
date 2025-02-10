//LIC

#include "layer_positions_xmapslab.h"
#include "window_xmapslab.h"

using namespace _layer_positions_xmapslab_ns;


//HEA

_layer_positions_xmapslab::_layer_positions_xmapslab()
{
  Vec_transparency=0;
  State[0]=true;
  State[1]=true;
  Pixel_transparency=false;

  Type=_layer_xmapslab_ns::_type::TYPE_IMAGE;
  Subtype=_layer_xmapslab_ns::_subtype::SUBTYPE_POSITIONS;

  Num_channels=3;
}

//HEA

void _layer_positions_xmapslab::reset_data()
{
  Vec_transparency=0;
  Pixel_transparency=false;
}

//HEA

void _layer_positions_xmapslab::add_valid_coordinates(std::vector<bool> Vec_valid_coordinates1)
{
  Vec_valid_coordinates=Vec_valid_coordinates1;
}

//HEA

void _layer_positions_xmapslab::add_coordinates(std::vector<float> Vec_coordinate_x1, std::vector<float> Vec_coordinate_y1)
{
  Vec_coordinate_x=Vec_coordinate_x1;
  Vec_coordinate_y=Vec_coordinate_y1;
}

//HEA

void _layer_positions_xmapslab::add_coordinates_with_corners(std::vector<float> Vec_coordinate_x1, std::vector<float> Vec_coordinate_y1)
{
  Vec_coordinate_x_corners=Vec_coordinate_x1;
  Vec_coordinate_y_corners=Vec_coordinate_y1;
}

//HEA

void _layer_positions_xmapslab::parameters(int Display_font_size1, int Display_out_circle_size1, QColor Display_font_color1, QColor Display_out_circle_color1, QColor Display_in_circle_color1)
{
  Display_font_size=Display_font_size1;
  Display_out_circle_size=Display_out_circle_size1;
  Display_font_color=Display_font_color1;
  Display_out_circle_color=Display_out_circle_color1;
  Display_in_circle_color=Display_in_circle_color1;
}

//HEA

void _layer_positions_xmapslab::draw(QPainter &Painter,float Width1,float Height1)
{
  if (Triangulation_mode!=_layer_map_triangulation_ns::_triangulation_mode::TRIANGULATION_MODE_NONE){
    QPen Pen_out_circle(Display_out_circle_color);
    Pen_out_circle.setWidth(3);
    Painter.setPen(Pen_out_circle);
    Painter.setBrush(Qt::NoBrush);

    QPointF Points[3];

    if (Triangulation_mode==_layer_map_triangulation_ns::_triangulation_mode::TRIANGULATION_MODE_NORMAL){
      for (unsigned int i=0;i<Triangles.size();i++){
        Points[0].setX(Vec_coordinate_x[Triangles[i].P1]);
        Points[1].setX(Vec_coordinate_x[Triangles[i].P2]);
        Points[2].setX(Vec_coordinate_x[Triangles[i].P3]);

        Points[0].setY(Height1-1-Vec_coordinate_y[Triangles[i].P1]);
        Points[1].setY(Height1-1-Vec_coordinate_y[Triangles[i].P2]);
        Points[2].setY(Height1-1-Vec_coordinate_y[Triangles[i].P3]);

        // Triangle
        Painter.drawPolygon(Points,3);
      }
    }
    else{
      for (unsigned int i=0;i<Triangles_with_corners.size();i++){
        Points[0].setX(Vec_coordinate_x_corners[Triangles_with_corners[i].P1]);
        Points[1].setX(Vec_coordinate_x_corners[Triangles_with_corners[i].P2]);
        Points[2].setX(Vec_coordinate_x_corners[Triangles_with_corners[i].P3]);

        Points[0].setY(Height1-1-Vec_coordinate_y_corners[Triangles_with_corners[i].P1]);
        Points[1].setY(Height1-1-Vec_coordinate_y_corners[Triangles_with_corners[i].P2]);
        Points[2].setY(Height1-1-Vec_coordinate_y_corners[Triangles_with_corners[i].P3]);

        // Triangle
        Painter.drawPolygon(Points,3);
      }
    }
  }

  if (Draw_positions){
    float Pos_x;
    float Pos_y;

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
    QRect Text_rect;
    int Letters_pixels_height = Font_metric.ascent();

    QBrush Brush_out_circle(Display_out_circle_color);
    QBrush Brush_in_circle(Display_in_circle_color);

    QPen Pen_font(Display_font_color);
    QPen Pen_out_circle(Display_out_circle_color);
    QPen Pen_no_valid(Qt::red,5);

    int Radius=Display_out_circle_size/2;
    int Step=Radius/3;

    for (unsigned int i=0;i<Vec_coordinate_x.size();i++){
      // compute the pixel
      Pos_x=Vec_coordinate_x[i];
      Pos_y=Height1-1-Vec_coordinate_y[i];

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
      if (Draw_position_numbers){
        Painter.setPen(Pen_font);

        // compute the width of the text
        Letters_pixels_width= Font_metric.horizontalAdvance(QString("%1").arg(i+1));
        Text_rect=Font_metric.boundingRect(QString("%1").arg(i+1));

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

        Painter.drawText(QPointF(Pos_x_text,Pos_y_text),QString("%1").arg(i+1));
      }

      if (Vec_valid_coordinates[i]==false){
        Painter.setPen(Pen_no_valid);
        Painter.drawLine(Pos_x-2*Radius,Pos_y-2*Radius,Pos_x+2*Radius,Pos_y+2*Radius);
        Painter.drawLine(Pos_x-2*Radius,Pos_y+2*Radius,Pos_x+2*Radius,Pos_y-2*Radius);
      }
    }
  }
}

//HEA

void _layer_positions_xmapslab::update()
{
  if (Image!=nullptr){
    Image->release();
    Image.reset();
  }

  float Width1=float(Width)-1;
  float Height1=float(Height)-1;

  QImage Image1(Width,Height,QImage::Format_ARGB32);
  Image1.fill(Qt::white);
  QPainter Painter(&Image1);

  draw(Painter,Width1,Height1);
  Painter.end();

  Image=make_shared<cv::Mat>(Height,Width,CV_8UC4,const_cast<uchar*>(Image1.bits()), static_cast<size_t>(Image1.bytesPerLine()));

  // this is important to get a real content
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

//HEA

_layer_positions_xmapslab_ui::_layer_positions_xmapslab_ui(_window_xmapslab *Window1, std::string Name1)
{
  Window=Window1;
  Name=Name1;
  Qtw_layer_positions_xmapslab=new _qtw_layer_positions_xmapslab(Window1,this,Name);
}

//HEA

_layer_positions_xmapslab_ui::~_layer_positions_xmapslab_ui()
{
  delete Qtw_layer_positions_xmapslab;
}

//HEA

void _layer_positions_xmapslab_ui::reset_data()
{
  _layer_positions_xmapslab::reset_data();
  Qtw_layer_positions_xmapslab->parameter1(parameter1());
  hide();
}

//HEA

void _layer_positions_xmapslab_ui::show()
{
  Qtw_layer_positions_xmapslab->show();
}

//HEA

void _layer_positions_xmapslab_ui::hide()
{
  Qtw_layer_positions_xmapslab->hide();
}

//HEA

void *_layer_positions_xmapslab_ui::get_link()
{
  return Qtw_layer_positions_xmapslab->get_link();
}

//HEA

void _layer_positions_xmapslab_ui::enable()
{
  Qtw_layer_positions_xmapslab->enable();
}

//HEA

void _layer_positions_xmapslab_ui::disable()
{
  Qtw_layer_positions_xmapslab->disable();
}

//HEA

_qtw_layer_positions_xmapslab::_qtw_layer_positions_xmapslab(_window_xmapslab *Window1,_layer_positions_xmapslab_ui *Filter1,std::string Box_name)
{
  Window=Window1;
  Filter=Filter1;

  Group_box_main=new QGroupBox(tr(Box_name.c_str()));
  Group_box_main->setAlignment(Qt::AlignCenter);

  QVBoxLayout *Vertical_box_main=new QVBoxLayout;

  // Parameter1
  QGroupBox *Group_box_parameter1=new QGroupBox(tr(String_group_box_parameter1.c_str()));
  Group_box_parameter1->setAlignment(Qt::AlignCenter);

  QGridLayout *Grid_parameter1 = new QGridLayout;

  QLabel *Label_parameter1_min= new QLabel(tr(String_label_parameter1_min.c_str()));
  QLabel *Label_parameter1_max= new QLabel(tr(String_label_parameter1_max.c_str()));

  Line_edit_parameter1=new QLineEdit();
  Line_edit_parameter1->setAlignment(Qt::AlignRight);
  Line_edit_parameter1->setReadOnly(true);
  Line_edit_parameter1->setEnabled(false);
  Line_edit_parameter1->setToolTip(tr(String_label_parameter1_tooltip.c_str()));

  Slider_parameter1 = new QSlider(Qt::Horizontal);
  Slider_parameter1->setRange(Parameter1_min_value,Parameter1_max_value);
  Slider_parameter1->setSingleStep(Parameter1_single_step);
  Slider_parameter1->setPageStep(Parameter1_page_step);
  Slider_parameter1->setTickInterval(Parameter1_tick_interval);
  Slider_parameter1->setTickPosition(QSlider::TicksRight);
  Slider_parameter1->setTracking(Parameter1_set_tracking);
  Slider_parameter1->setToolTip(tr(String_parameter1_tooltip.c_str()));

  parameter1(Filter->parameter1());

  Grid_parameter1->addWidget(Line_edit_parameter1,0,1,Qt::AlignCenter);
  Grid_parameter1->addWidget(Label_parameter1_min,1,0,Qt::AlignRight);
  Grid_parameter1->addWidget(Slider_parameter1,1,1);
  Grid_parameter1->addWidget(Label_parameter1_max,1,2,Qt::AlignLeft);

  Group_box_parameter1->setLayout(Grid_parameter1);

  connect(Slider_parameter1, SIGNAL(valueChanged(int)),this,SLOT(parameter1_slot(int)));

  // Parameter2
  QGroupBox *Group_box_parameter2=new QGroupBox(tr(String_group_box_parameter2.c_str()));
  Group_box_parameter2->setAlignment(Qt::AlignCenter);

  QHBoxLayout *Horizontal_box_parameter2=new QHBoxLayout;
  Horizontal_box_parameter2->setAlignment(Qt::AlignCenter);

  Checkbox_parameter2=new QCheckBox;

  Horizontal_box_parameter2->addWidget(Checkbox_parameter2);

  Group_box_parameter2->setLayout(Horizontal_box_parameter2);

  connect(Checkbox_parameter2, SIGNAL(stateChanged(int)),this,SLOT(parameter2_slot(int)));


  //
  Vertical_box_main->addWidget(Group_box_parameter1);
  Vertical_box_main->addWidget(Group_box_parameter2);

  Group_box_main->setLayout(Vertical_box_main);
}

//HEA

void _qtw_layer_positions_xmapslab::parameter1(int Value)
{
  QString Str;

  Str=Str.number(Value);
  Line_edit_parameter1->setText(Str);
  Slider_parameter1->blockSignals(true);
  Slider_parameter1->setValue((Value/2)-1);
  Slider_parameter1->blockSignals(false);
}

//HEA

void _qtw_layer_positions_xmapslab::parameter2(int Value)
{
  QString Str;

  Checkbox_parameter2->blockSignals(true);
  if (Value==0) Checkbox_parameter2->setCheckState(Qt::Unchecked);
  else Checkbox_parameter2->setCheckState(Qt::Checked);
  Checkbox_parameter2->blockSignals(false);
}

//HEA

void _qtw_layer_positions_xmapslab::parameter1_slot(int Value)
{
  QString Str;
  char Aux[100];

  sprintf(Aux,"%2d",Value);
  Str=Aux;
  Line_edit_parameter1->setText(Str);
  Filter->parameter1(Value);
  Window->update_layer(Filter->name());
}

//HEA

void _qtw_layer_positions_xmapslab::parameter2_slot(int Value)
{

  if (Value==Qt::Unchecked) Value=0;
  else Value=1;

  Filter->parameter2(Value);
  Window->update_layer(Filter->name());
}

