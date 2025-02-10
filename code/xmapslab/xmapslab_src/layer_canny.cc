//LIC

#include "layer_canny.h"
#include "window.h"

using namespace _layer_canny_ns;

//HEA

_layer_canny::_layer_canny()
{
  Canny_size=CANNY_SIZE_DEFAULT;
  Threshold1=CANNY_THRESHOLD1_DEFAULT;
  Threshold2=CANNY_THRESHOLD2_DEFAULT;
  Pixel_transparence=CANNY_PILXEL_TRANSPARENCE_DEFAULT;

  Layer_type=_layer_ns::_layer_type::LAYER_TYPE_CANNY;

  State[0]=true;
  State[1]=true;

  Num_channels=3;
}

//HEA

void _layer_canny::reset_data()
{
  Canny_size=CANNY_SIZE_DEFAULT;
  Threshold1=CANNY_THRESHOLD1_DEFAULT;
  Threshold2=CANNY_THRESHOLD2_DEFAULT;
  Pixel_transparence=CANNY_PILXEL_TRANSPARENCE_DEFAULT;
}

//HEA

void _layer_canny::update()
{
  if (Image==nullptr){
    Image=make_shared<cv::Mat>();
  }
  else{
    Image->release();
  }

  cv::Mat Mat;

  cv::cvtColor(*Vec_input_images[0],Mat,cv::COLOR_BGRA2GRAY,1);

  cv::GaussianBlur(Mat,Mat,cv::Size(3,3),0,0);
  cv::Canny(Mat,Mat,double(Threshold1),double(Threshold2),Canny_size);
//  cv::GaussianBlur(Mat,Mat,cv::Size(3,3),0,0);
  Mat=255-Mat;

  cv::cvtColor(Mat,*Image,cv::COLOR_GRAY2BGRA,4);

  // transparence per pixel
//  unsigned char Value=255;
  if (Pixel_transparence){
    for (unsigned int Pos=0;Pos<Image->total();Pos++){
      cv::Vec4b &Pixel = Image->at<cv::Vec4b>(Pos);
      // if pixel is white
      if (Pixel[0]==255 && Pixel[1]==255 && Pixel[2]==255){
          // set alpha to zero:
          Pixel[3]=0;
      }
    }
  }
}

//HEA

_layer_canny_ui::_layer_canny_ui(_window *Window1, std::string Name1)
{
  Name=Name1;
  Qtw_layer_canny=new _qtw_layer_canny(Window1,this,Name);
}

//HEA

_layer_canny_ui::~_layer_canny_ui()
{
  delete Qtw_layer_canny;
}

//HEA

void _layer_canny_ui::reset_data()
{
  _layer_canny::reset_data();
  Qtw_layer_canny->parameter1(parameter1());
  Qtw_layer_canny->parameter2(parameter2());
  Qtw_layer_canny->parameter3(parameter3());
  Qtw_layer_canny->parameter4(parameter4());
  Qtw_layer_canny->parameter5(parameter5());
  Qtw_layer_canny->parameter6(parameter6());
  hide();
}

//HEA

void _layer_canny_ui::show()
{
  Qtw_layer_canny->show();
}

//HEA

void _layer_canny_ui::hide()
{
  Qtw_layer_canny->hide();
}

//HEA

void *_layer_canny_ui::get_link()
{
  return Qtw_layer_canny->get_link();
}

//HEA

void _layer_canny_ui::enable()
{
  Qtw_layer_canny->enable();
}

//HEA

void _layer_canny_ui::disable()
{
  Qtw_layer_canny->disable();
}

//HEA

//void _layer_canny_ui::read_parameters(std::map<std::string,std::string> &Parameters)
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
//    catch (...) {
//      QMessageBox MsgBox;
//      MsgBox.setText("Error in the data of CANNY filter");
//      MsgBox.exec();
//      exit(-1);
//    }
//  }
//}

//HEA

//void _layer_canny_ui::write_parameters(std::map<std::string,std::string> &Parameters)
//{
//  char Aux[100];

//  sprintf(Aux,"%d",parameter1());
//  Parameters["kernel_size"]=string(Aux);
//  sprintf(Aux,"%d",parameter2());
//  Parameters["threshold1"]=string(Aux);
//  sprintf(Aux,"%d",parameter3());
//  Parameters["threshold2"]=string(Aux);
//}

//HEA

_qtw_layer_canny::_qtw_layer_canny(_window *Window1,_layer_canny_ui *Filter1,string Box_name)
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

  // Parameter3
  QGroupBox *Group_box_parameter3=new QGroupBox(tr(String_group_box_parameter3.c_str()));
  Group_box_parameter3->setAlignment(Qt::AlignCenter);

  QHBoxLayout *Horizontal_box_parameter3=new QHBoxLayout;
  Horizontal_box_parameter3->setAlignment(Qt::AlignCenter);

  Checkbox_parameter3=new QCheckBox;

  Horizontal_box_parameter3->addWidget(Checkbox_parameter3);

  Group_box_parameter3->setLayout(Horizontal_box_parameter3);

  connect(Checkbox_parameter3, SIGNAL(stateChanged(int)),this,SLOT(parameter3_slot(int)));

  // Parameter 4
  Group_box_parameter4=new QGroupBox(tr(String_group_box_parameter4.c_str()));
  Group_box_parameter4->setAlignment(Qt::AlignCenter);

  QGridLayout *Grid_parameter4 = new QGridLayout;

  QLabel *Label_parameter4_min= new QLabel(tr(String_label_parameter4_min.c_str()));
  QLabel *Label_parameter4_max= new QLabel(tr(String_label_parameter4_max.c_str()));

  Line_edit_parameter4=new QLineEdit();
  Line_edit_parameter4->setAlignment(Qt::AlignRight);
  Line_edit_parameter4->setReadOnly(true);
  Line_edit_parameter4->setEnabled(false);
  Line_edit_parameter4->setToolTip(tr(String_label_parameter4_tooltip.c_str()));

  Slider_parameter4 = new QSlider(Qt::Horizontal);
  Slider_parameter4->setRange(Parameter4_min_value,Parameter4_max_value);
  Slider_parameter4->setSingleStep(Parameter4_single_step);
  Slider_parameter4->setPageStep(Parameter4_page_step);
  Slider_parameter4->setTickInterval(Parameter4_tick_interval);
  Slider_parameter4->setTickPosition(QSlider::TicksRight);
  Slider_parameter4->setTracking(Parameter4_set_tracking);
  Slider_parameter4->setToolTip(tr(String_parameter4_tooltip.c_str()));

  parameter4(Filter->parameter4());

  Grid_parameter4->addWidget(Line_edit_parameter4,0,1,Qt::AlignCenter);
  Grid_parameter4->addWidget(Label_parameter4_min,1,0,Qt::AlignRight);
  Grid_parameter4->addWidget(Slider_parameter4,1,1);
  Grid_parameter4->addWidget(Label_parameter4_max,1,4,Qt::AlignLeft);

  Group_box_parameter4->setLayout(Grid_parameter4);

  connect(Slider_parameter4, SIGNAL(valueChanged(int)),this,SLOT(parameter4_slot(int)));

  // parameter 5
  Group_box_parameter5=new QGroupBox(tr(String_group_box_parameter5.c_str()));
  Group_box_parameter5->setAlignment(Qt::AlignCenter);

  QGridLayout *Grid_parameter5 = new QGridLayout;

  QLabel *Label_parameter5_min= new QLabel(tr(String_label_parameter5_min.c_str()));
  QLabel *Label_parameter5_max= new QLabel(tr(String_label_parameter5_max.c_str()));

  Line_edit_parameter5=new QLineEdit();
  Line_edit_parameter5->setAlignment(Qt::AlignRight);
  Line_edit_parameter5->setReadOnly(true);
  Line_edit_parameter5->setEnabled(false);
  Line_edit_parameter5->setToolTip(tr(String_label_parameter5_tooltip.c_str()));

  Slider_parameter5 = new QSlider(Qt::Horizontal);
  Slider_parameter5->setRange(Parameter5_min_value,Parameter5_max_value);
  Slider_parameter5->setSingleStep(Parameter5_single_step);
  Slider_parameter5->setPageStep(Parameter5_page_step);
  Slider_parameter5->setTickInterval(Parameter5_tick_interval);
  Slider_parameter5->setTickPosition(QSlider::TicksRight);
  Slider_parameter5->setTracking(Parameter5_set_tracking);
  Slider_parameter5->setToolTip(tr(String_parameter5_slider_tooltip.c_str()));

  parameter5(Filter->parameter5());

  Grid_parameter5->addWidget(Line_edit_parameter5,0,1,Qt::AlignCenter);
  Grid_parameter5->addWidget(Label_parameter5_min,1,0,Qt::AlignRight);
  Grid_parameter5->addWidget(Slider_parameter5,1,1);
  Grid_parameter5->addWidget(Label_parameter5_max,1,2,Qt::AlignLeft);

  Group_box_parameter5->setLayout(Grid_parameter5);

  connect(Slider_parameter5, SIGNAL(valueChanged(int)),this,SLOT(parameter5_slot(int)));

  // parameter 6
  Group_box_parameter6=new QGroupBox(tr(String_group_box_parameter6.c_str()));
  Group_box_parameter6->setAlignment(Qt::AlignCenter);

  QGridLayout *Grid_parameter6 = new QGridLayout;

  QLabel *Label_parameter6_min= new QLabel(tr(String_label_parameter6_min.c_str()));
  QLabel *Label_parameter6_max= new QLabel(tr(String_label_parameter6_max.c_str()));

  Line_edit_parameter6=new QLineEdit();
  Line_edit_parameter6->setAlignment(Qt::AlignRight);
  Line_edit_parameter6->setReadOnly(true);
  Line_edit_parameter6->setEnabled(false);
  Line_edit_parameter6->setToolTip(tr(String_label_parameter6_tooltip.c_str()));

  Slider_parameter6 = new QSlider(Qt::Horizontal);
  Slider_parameter6->setRange(Parameter6_min_value,Parameter6_max_value);
  Slider_parameter6->setSingleStep(Parameter6_single_step);
  Slider_parameter6->setPageStep(Parameter6_page_step);
  Slider_parameter6->setTickInterval(Parameter6_tick_interval);
  Slider_parameter6->setTickPosition(QSlider::TicksRight);
  Slider_parameter6->setTracking(Parameter6_set_tracking);
  Slider_parameter6->setToolTip(tr(String_parameter6_slider_tooltip.c_str()));

  parameter6(Filter->parameter6());

  Grid_parameter6->addWidget(Line_edit_parameter6,0,1,Qt::AlignCenter);
  Grid_parameter6->addWidget(Label_parameter6_min,1,0,Qt::AlignRight);
  Grid_parameter6->addWidget(Slider_parameter6,1,1);
  Grid_parameter6->addWidget(Label_parameter6_max,1,2,Qt::AlignLeft);

  Group_box_parameter6->setLayout(Grid_parameter6);

  connect(Slider_parameter6, SIGNAL(valueChanged(int)),this,SLOT(parameter6_slot(int)));

  //
  Vertical_box_main->addWidget(Group_box_parameter1);
  Vertical_box_main->addWidget(Group_box_parameter2);
  Vertical_box_main->addWidget(Group_box_parameter3);
  Vertical_box_main->addWidget(Group_box_parameter4);
  Vertical_box_main->addWidget(Group_box_parameter5);
  Vertical_box_main->addWidget(Group_box_parameter6);

  Group_box_main->setLayout(Vertical_box_main);
}

//HEA

void _qtw_layer_canny::parameter1(int Value)
{
  QString Str;

  Str=Str.number(Value);
  Line_edit_parameter1->setText(Str);
  Slider_parameter1->blockSignals(true);
  Slider_parameter1->setValue(Value);
  Slider_parameter1->blockSignals(false);
}

//HEA

void _qtw_layer_canny::parameter2(int Value)
{
  QString Str;

  Checkbox_parameter2->blockSignals(true);
  if (Value==0) Checkbox_parameter2->setCheckState(Qt::Unchecked);
  else Checkbox_parameter2->setCheckState(Qt::Checked);
  Checkbox_parameter2->blockSignals(false);
}

//HEA

void _qtw_layer_canny::parameter3(int Value)
{
  QString Str;

  Checkbox_parameter3->blockSignals(true);
  if (Value==0) Checkbox_parameter3->setCheckState(Qt::Unchecked);
  else Checkbox_parameter3->setCheckState(Qt::Checked);
  Checkbox_parameter3->blockSignals(false);
}

//HEA

void _qtw_layer_canny::parameter4(int Value)
{
  QString Str;

  Str=Str.number(Value);
  Line_edit_parameter4->setText(Str);
  Slider_parameter4->blockSignals(true);
  Slider_parameter4->setValue((Value-1)/2);
  Slider_parameter4->blockSignals(false);
}

//HEA

void _qtw_layer_canny::parameter5(int Value)
{
  QString Str;

  Str=Str.number(Value);
  Line_edit_parameter5->setText(Str);
  Slider_parameter5->blockSignals(true);
  Slider_parameter5->setValue(Value);
  Slider_parameter5->blockSignals(false);
}

//HEA

void _qtw_layer_canny::parameter6(int Value)
{
  QString Str;

  Str=Str.number(Value);
  Line_edit_parameter6->setText(Str);
  Slider_parameter6->blockSignals(true);
  Slider_parameter6->setValue(Value);
  Slider_parameter6->blockSignals(false);
}

//HEA

void _qtw_layer_canny::parameter1_slot(int Value)
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

void _qtw_layer_canny::parameter2_slot(int Value)
{

  if (Value==Qt::Unchecked) Value=0;
  else Value=1;

  Filter->parameter2(Value);
  Window->update_layer(Filter->name());
}

//HEA

void _qtw_layer_canny::parameter3_slot(int Value)
{

  if (Value==Qt::Unchecked) Value=0;
  else Value=1;

  Filter->parameter3(Value);
  Window->update_layer(Filter->name());
}

//HEA

void _qtw_layer_canny::parameter4_slot(int Value)
{
  QString Str;
  char Aux[100];

  sprintf(Aux,"%2d",Value*2+1);
  Str=Aux;
  Line_edit_parameter4->setText(Str);
  Filter->parameter4(Value*2+1);
  Window->update_layer(Filter->name());
}

//HEA

void _qtw_layer_canny::parameter5_slot(int Value)
{
  QString Str;
  char Aux[100];

  sprintf(Aux,"%2d",Value);
  Str=Aux;
  Line_edit_parameter5->setText(Str);
  Filter->parameter5(Value);
  Window->update_layer(Filter->name());
}

//HEA

void _qtw_layer_canny::parameter6_slot(int Value)
{
  QString Str;
  char Aux[100];

  sprintf(Aux,"%2d",Value);
  Str=Aux;
  Line_edit_parameter6->setText(Str);
  Filter->parameter6(Value);
  Window->update_layer(Filter->name());
}
