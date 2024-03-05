/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "layer_triangulation.h"
#include "window.h"

using namespace _layer_triangulation_ns;

/*************************************************************************/

_layer_triangulation::_layer_triangulation()
{
  Transparence=0;
  State[0]=true;
  State[1]=true;
  Pixel_transparence=false;

  Layer_type=_layer_ns::_layer_type::LAYER_TYPE_BASIC;

  Num_channels=3;
}

/*************************************************************************/

void _layer_triangulation::reset_data()
{
  Transparence=0;
  Pixel_transparence=false;
}

/*************************************************************************/

void _layer_triangulation::add_input_data(std::vector<_element_data_ns::_data_sample> &Vec_samples1)
{
  Vec_samples=Vec_samples1;
}

/*************************************************************************/

void _layer_triangulation::triangles(std::vector<_delaunay_triangulator_ns::_triangle> &Triangles1)
{
  Triangles=Triangles1;
}

/*************************************************************************/

void _layer_triangulation::parameters(int Display_font_size1, int Display_out_circle_size1, QColor Display_font_color1, QColor Display_out_circle_color1, QColor Display_in_circle_color1)
{
  Display_font_size=Display_font_size1;
  Display_out_circle_size=Display_out_circle_size1;
  Display_font_color=Display_font_color1;
  Display_out_circle_color=Display_out_circle_color1;
  Display_in_circle_color=Display_in_circle_color1;
}

/*************************************************************************/

void _layer_triangulation::draw(QPainter &Painter,float Width1,float Height1)
{
//  float Pos_x;
//  float Pos_y;

//  QFont Font("Courier");
//  Font.setStyleHint(QFont::SansSerif,QFont::NoAntialias);
//  Font.setBold(true);
//  Font.setPointSize(Display_font_size);
//  Painter.setFont(Font);

//  QFontMetrics Font_metric(Font);
//  int Letters_pixels_width;
//  int Letters_pixels_height = Font_metric.ascent();

//  QBrush Brush_out_circle(Display_out_circle_color);
//  QBrush Brush_in_circle(Display_in_circle_color);

//  QPen Pen_font(Display_font_color);
  QPen Pen_out_circle(Display_out_circle_color);
  Painter.setPen(Pen_out_circle);

  QPointF Points[3];

//  cout << "Num_triangles=" << Triangles.size() << endl;

  for (unsigned int i=0;i<Triangles.size();i++){
    Points[0].setX(roundf(Vec_samples[Triangles[i].P1].x*Width1));
    Points[1].setX(roundf(Vec_samples[Triangles[i].P2].x*Width1));
    Points[2].setX(roundf(Vec_samples[Triangles[i].P3].x*Width1));

    if (CS_origin==_project_data_ns::_cs_origin::CS_ORIGIN_TOP_LEFT){
      // to undone the inversion for OpenGL
      Points[0].setY(roundf((1-Vec_samples[Triangles[i].P1].y)*Height1));
      Points[1].setY(roundf((1-Vec_samples[Triangles[i].P2].y)*Height1));
      Points[2].setY(roundf((1-Vec_samples[Triangles[i].P3].y)*Height1));
    }
    else{
      Points[0].setY(roundf(Vec_samples[Triangles[i].P1].y*Height1));
      Points[1].setY(roundf(Vec_samples[Triangles[i].P2].y*Height1));
      Points[2].setY(roundf(Vec_samples[Triangles[i].P3].y*Height1));
    }

    // pixel

    Painter.drawPolygon(Points,3);
  }
}

/*************************************************************************/

void _layer_triangulation::update()
{
  if (Image!=nullptr){
    Image->release();
    Image.reset();
  }

  float Width1=float(Width)-1;
  float Height1=float(Height)-1;
//  float Pos_x;
//  float Pos_y;

  QImage Image1(Width,Height,QImage::Format_ARGB32);
  Image1.fill(Qt::white);
  QPainter Painter(&Image1);

//  QFontInfo Font_info(Painter.font());
//  QString Font_family = Font_info.family();
//  cout << "Font family " << Font_family.toStdString() << endl;

  draw(Painter,Width1,Height1);
  Painter.end();

  Image=make_shared<cv::Mat>(Height,Width,CV_8UC4,const_cast<uchar*>(Image1.bits()), static_cast<size_t>(Image1.bytesPerLine()));

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

/*************************************************************************/

_layer_triangulation_ui::_layer_triangulation_ui(_window *Window1, string Name1)
{
  Name=Name1;
  Qtw_layer_triangulation=new _qtw_layer_triangulation(Window1,this,Name);
}

/*************************************************************************/

_layer_triangulation_ui::~_layer_triangulation_ui()
{
  delete Qtw_layer_triangulation;
}

/*************************************************************************/

void _layer_triangulation_ui::reset_data()
{
  _layer_triangulation::reset_data();
  Qtw_layer_triangulation->parameter1(parameter1());
  hide();
}

/*************************************************************************/

void _layer_triangulation_ui::show()
{
  Qtw_layer_triangulation->show();
}

/*************************************************************************/

void _layer_triangulation_ui::hide()
{
  Qtw_layer_triangulation->hide();
}

/*************************************************************************/

void *_layer_triangulation_ui::get_link()
{
  return Qtw_layer_triangulation->get_link();
}

/*************************************************************************/

void _layer_triangulation_ui::enable()
{
  Qtw_layer_triangulation->enable();
}

/*************************************************************************/

void _layer_triangulation_ui::disable()
{
  Qtw_layer_triangulation->disable();
}

/*************************************************************************/

//void _layer_triangulation_ui::read_parameters(std::map<std::string,std::string> &Parameters)
//{
//  if (Parameters["_INI_"]=="EDITOR"){// default parameters
//    parameter1(CANNY_SIZE_DEFAULT);
//    parameter2(CANNY_THRESHOLD1_DEFAULT);
//    parameter3(CANNY_THRESHOLD2_DEFAULT);
//  }
//  else{// Parameters from file or from initialised filter
//    try{
//      if (Parameters["kernel_size"]=="default") parameter1(CANNY_SIZE_DEFAULT);
//      else parameter1(atoi(Parameters["kernel_size"].c_str()));
//      if (Parameters["threshold1"]=="default") parameter2(CANNY_THRESHOLD1_DEFAULT);
//      else parameter2(atoi(Parameters["threshold1"].c_str()));
//      if (Parameters["threshold2"]=="default") parameter3(CANNY_THRESHOLD2_DEFAULT);
//      else parameter3(atoi(Parameters["threshold2"].c_str()));
//    }
//    catch (const std::out_of_range) {
//      QMessageBox MsgBox;
//      MsgBox.setText("Error in the data of CANNY filter");
//      MsgBox.exec();
//      exit(-1);
//    }
//  }
//}

/*************************************************************************/

//void _layer_triangulation_ui::write_parameters(std::map<std::string,std::string> &Parameters)
//{
//  char Aux[100];

//  sprintf(Aux,"%d",parameter1());
//  Parameters["kernel_size"]=string(Aux);
//  sprintf(Aux,"%d",parameter2());
//  Parameters["threshold1"]=string(Aux);
//  sprintf(Aux,"%d",parameter3());
//  Parameters["threshold2"]=string(Aux);
//}

/*************************************************************************/

_qtw_layer_triangulation::_qtw_layer_triangulation(_window *Window1,_layer_triangulation_ui *Filter1,string Box_name)
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

/*************************************************************************/

void _qtw_layer_triangulation::parameter1(int Value)
{
  QString Str;

  Str=Str.number(Value);
  Line_edit_parameter1->setText(Str);
  Slider_parameter1->blockSignals(true);
  Slider_parameter1->setValue((Value/2)-1);
  Slider_parameter1->blockSignals(false);
}

/*************************************************************************/

void _qtw_layer_triangulation::parameter2(int Value)
{
  QString Str;

  Checkbox_parameter2->blockSignals(true);
  if (Value==0) Checkbox_parameter2->setCheckState(Qt::Unchecked);
  else Checkbox_parameter2->setCheckState(Qt::Checked);
  Checkbox_parameter2->blockSignals(false);
}

/*************************************************************************/

void _qtw_layer_triangulation::parameter1_slot(int Value)
{
  QString Str;
  char Aux[100];

  sprintf(Aux,"%2d",Value);
  Str=Aux;
  Line_edit_parameter1->setText(Str);
  Filter->parameter1(Value);
  Window->update_layer(Filter->name());
}

/*************************************************************************/

void _qtw_layer_triangulation::parameter2_slot(int Value)
{

  if (Value==Qt::Unchecked) Value=0;
  else Value=1;

  Filter->parameter2(Value);
  Window->update_layer(Filter->name());
}

