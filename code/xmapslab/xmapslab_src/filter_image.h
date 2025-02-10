//LIC

#ifndef FILTER_IMAGE
#define FILTER_IMAGE

#include <QDialog>
#include <QGroupBox>
#include <QSlider>
#include <QLabel>

// #include "line_edit.h"
#include <string>
#include "filter.h"

#define DEFINED_FILTER_IMAGE

namespace _f_image_ns
{
  // parameter 1
  const std::string String_group_box_parameter1("Size");
//  const std::string String_label_parameter1_min("1  ");
//  const std::string String_label_parameter1_max("100");
//  const std::string String_label_parameter1_tooltip("Display the value of Kernel size");
//  const int Parameter1_min_value=1;
//  const int Parameter1_max_value=100;
//  const int Parameter1_single_step=1;
//  const int Parameter1_page_step=5;
//  const int Parameter1_tick_interval=5;
//  const bool Parameter1_set_tracking=false;
//  const std::string String_parameter1_tooltip("Controls the effect on the dilation");
//  const int Parameter1_divisor=10;

  // Default values
//  const int BILATERAL_KERNEL_SIZE_DEFAULT=1;
  const std::string FILTER_NAME="Element";
}

class _window_xmapslab;
class _qtw_filter_image;

//HEA

class _filter_image : public _filter
{
public:
    _filter_image();
    void reset_data();

//    void color(QColor Color1){Color=Color1;}
//    QColor color(){return Color;}

    float get_max_value();

    void update();
};

//HEA

class _filter_image_ui : public _filter_image
{
public:
  _filter_image_ui(_window_xmapslab *Window1,std::string Name1=_f_image_ns::FILTER_NAME);
  _filter_image_ui(_window_xmapslab *Window1,std::map<std::string,std::string> &Parameters,std::string Name1=_f_image_ns::FILTER_NAME);
  ~_filter_image_ui();
  void reset_data();

  void show();
  void hide();
  void *get_link();
  void read_parameters(std::map<std::string,std::string> &Parameters);
  void write_parameters(std::map<std::string, std::string> &Parameters);

  void color(QColor Color1);

//  void parameter1(int Value){_filter_image::kernel_size(Value);}
//  int parameter1(){return _filter_image::kernel_size();}

//  void parameter2(QColor Color1){_filter_image::color(Color1);}
//  QColor parameter2(){return _filter_image::color();}

private:
  _qtw_filter_image *Qtw_filter_image=nullptr;
};

//HEA

class _qtw_filter_image: public QWidget
{
  Q_OBJECT
public:

  _qtw_filter_image(_window_xmapslab *Window1,_filter_image_ui *Filter1,std::string Box_name=_f_image_ns::FILTER_NAME);

  void show(){} //Group_box_main->show();}
  void hide(){} // Group_box_main->hide();}
  QGroupBox *get_link(){return nullptr;} //{return Group_box_main;}

//  void parameter1(int Value);
//  void parameter2(QColor Color1);

//protected slots:
//  void parameter1_slot(int Value);
//  void parameter2_slot(QColor Color1);

private:
  QGroupBox *Group_box_main=nullptr;
  QGroupBox *Group_box_parameter1=nullptr;

  // Size
//  QSlider *Slider_parameter1=nullptr;
//  QLineEdit *Line_edit_parameter1=nullptr;

  // color
  _button_color_simple *Button_parameter2=nullptr;


  _filter_image_ui *Filter=nullptr;
  _window_xmapslab *Window=nullptr;
};
#endif
