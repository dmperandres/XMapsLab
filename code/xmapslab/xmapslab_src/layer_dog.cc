//LIC

#include "layer_dog.h"
#include "window_xmapslab.h"

using namespace _layer_dog_ns;

//HEA

_layer_dog::_layer_dog()
{
  Dog_threshold=DOG_THRESHOLD_DEFAULT;
  Big_gaussian_size=DOG_BIG_GAUSSIAN_SIZE_DEFAULT;
  Small_gaussian_size=DOG_SMALL_GAUSSIAN_SIZE_DEFAULT;

  Type=_layer_xmapslab_ns::_type::TYPE_IMAGE;
  Subtype=_layer_xmapslab_ns::_subtype::SUBTYPE_DOG;

  Pixel_transparency=PIXEL_TRANSPARENCY_DEFAULT;

  Num_channels=1;
}

//HEA

void _layer_dog::reset_data()
{
  Dog_threshold=DOG_THRESHOLD_DEFAULT;
  Big_gaussian_size=DOG_BIG_GAUSSIAN_SIZE_DEFAULT;
  Small_gaussian_size=DOG_SMALL_GAUSSIAN_SIZE_DEFAULT;

  Pixel_transparency=PIXEL_TRANSPARENCY_DEFAULT;
}

//HEA

void _layer_dog::update()
{
  if (Image==nullptr){
    Image=make_shared<cv::Mat>();
  }
  else{
    Image->release();
  }

  cv::Mat Mat;

  cv::cvtColor(*Vec_input_images[0].get(),Mat,cv::COLOR_BGRA2GRAY,1);

  cv::Mat Borders_dog_big,Borders_dog_small;

  Borders_dog_big.create(Mat.rows,Mat.cols,CV_8U);
  Borders_dog_small.create(Mat.rows,Mat.cols,CV_8U);
  cv::GaussianBlur(Mat, Borders_dog_big,cv::Size(Big_gaussian_size,Big_gaussian_size),0,0);
  cv::GaussianBlur(Mat, Borders_dog_small,cv::Size(Small_gaussian_size,Small_gaussian_size),0,0);
  Borders_dog_big=Borders_dog_big-Borders_dog_small;
  //invert
  Borders_dog_big=255-Borders_dog_big;
  cv::threshold(Borders_dog_big,Mat,Dog_threshold,255,cv::THRESH_BINARY);

//  cv::GaussianBlur(Mat,Mat,cv::Size(5,5),0,0);

  cv::cvtColor(Mat,*Image,cv::COLOR_GRAY2BGRA,4);

  // transparence per pixel
  if (Pixel_transparency){
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

void _layer_dog::dog_threshold(int Threshold)
{
  Dog_threshold=Threshold;
}

//HEA

void _layer_dog::big_gaussian_size(int Size)
{
  Big_gaussian_size=Size;
}

//HEA

void _layer_dog::small_gaussian_size(int Size)
{
  Small_gaussian_size=Size;
}

//HEA

_layer_dog_ui::_layer_dog_ui(_window_xmapslab *Window1, std::string Name1)
{
  Window=Window1;
  Name=Name1;
  Qtw_layer_dog=new _qtw_layer_dog(Window1,this,Name);
}

//HEA

_layer_dog_ui::~_layer_dog_ui()
{
  delete Qtw_layer_dog;
}

//HEA

void _layer_dog_ui::reset_data()
{
  _layer_dog::reset_data();
  Qtw_layer_dog->parameter1(parameter1());
  Qtw_layer_dog->parameter4(parameter4());
  Qtw_layer_dog->parameter5(parameter5());
  Qtw_layer_dog->parameter6(parameter6());
  hide();
}

//HEA

void _layer_dog_ui::show()
{
  Qtw_layer_dog->show();
}

//HEA

void _layer_dog_ui::hide()
{
  Qtw_layer_dog->hide();
}

//HEA

void *_layer_dog_ui::get_link()
{
  return Qtw_layer_dog->get_link();
}

//HEA

void _layer_dog_ui::enable()
{
  Qtw_layer_dog->enable();
}

//HEA

void _layer_dog_ui::disable()
{
  Qtw_layer_dog->disable();
}

//HEA

_qtw_layer_dog::_qtw_layer_dog(_window_xmapslab *Window1,_layer_dog_ui *Filter1,std::string Box_name)
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
  Vertical_box_main->addWidget(Group_box_parameter4);
  Vertical_box_main->addWidget(Group_box_parameter5);
  Vertical_box_main->addWidget(Group_box_parameter6);

  Group_box_main->setLayout(Vertical_box_main);
}

//HEA

void _qtw_layer_dog::parameter1(int Value)
{
  QString Str;

  Str=Str.number(Value);
  Line_edit_parameter1->setText(Str);
  Slider_parameter1->blockSignals(true);
  Slider_parameter1->setValue(Value);
  Slider_parameter1->blockSignals(false);
}

//HEA

void _qtw_layer_dog::parameter2(int Value)
{
  QString Str;

  Checkbox_parameter2->blockSignals(true);
  if (Value==0) Checkbox_parameter2->setCheckState(Qt::Unchecked);
  else Checkbox_parameter2->setCheckState(Qt::Checked);
  Checkbox_parameter2->blockSignals(false);
}

//HEA

void _qtw_layer_dog::parameter4(int Value)
{
  QString Str;

  Str=Str.number(Value);
  Line_edit_parameter4->setText(Str);
  Slider_parameter4->blockSignals(true);
  Slider_parameter4->setValue(Value);
  Slider_parameter4->blockSignals(false);
}

//HEA

void _qtw_layer_dog::parameter5(int Value)
{
  QString Str;

  Str=Str.number(Value);
  Line_edit_parameter5->setText(Str);
  Slider_parameter5->blockSignals(true);
  Slider_parameter5->setValue(Value);
  Slider_parameter5->blockSignals(false);
}

//HEA

void _qtw_layer_dog::parameter6(int Value)
{
  QString Str;

  Str=Str.number(Value);
  Line_edit_parameter6->setText(Str);
  Slider_parameter6->blockSignals(true);
  Slider_parameter6->setValue(Value);
  Slider_parameter6->blockSignals(false);
}

//HEA

void _qtw_layer_dog::parameter1_slot(int Value)
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

void _qtw_layer_dog::parameter2_slot(int Value)
{

  if (Value==Qt::Unchecked) Value=0;
  else Value=1;

  Filter->parameter2(Value);
  Window->update_layer(Filter->name());
}

//HEA

void _qtw_layer_dog::parameter4_slot(int Value)
{
  QString Str;
  char Aux[100];

  sprintf(Aux,"%2d",Value);
  Str=Aux;
  Line_edit_parameter4->setText(Str);
  Filter->parameter4(Value);
  Window->update_layer(Filter->name());
}

//HEA

void _qtw_layer_dog::parameter5_slot(int Value)
{
  QString Str;
  char Aux[100];

  if (Value%2==0) Value++;
  sprintf(Aux,"%2d",Value);
  Str=Aux;
  Line_edit_parameter5->setText(Str);
  Filter->parameter5(Value);
  Window->update_layer(Filter->name());
}

//HEA

void _qtw_layer_dog::parameter6_slot(int Value)
{
  QString Str;
  char Aux[100];

  if (Value%2==0) Value++;
  sprintf(Aux,"%2d",Value);
  Str=Aux;
  Line_edit_parameter6->setText(Str);
  Filter->parameter6(Value);
  Window->update_layer(Filter->name());
}
