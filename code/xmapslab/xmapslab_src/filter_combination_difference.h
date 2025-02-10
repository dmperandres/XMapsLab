//LIC

#ifndef FILTER_COMBINATION_DIFFERENCE
#define FILTER_COMBINATION_DIFFERENCE

#include <QDialog>
#include <QGroupBox>
#include <QSpinBox>
#include <QLabel>

// #include "line_edit.h"
#include <string>
#include "filter.h"

#include "filter_element.h"

#define DEFINED_FILTER_COMBINATION_DIFFERENCE

namespace _f_combination_difference_ns
{
  // parameter 1
  const std::string String_group_box_parameter1("0 threshold");
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
  const int THRESHOLD_DEFAULT=_filter_ns::THRESHOLD_DEFAULT;

  const std::string FILTER_NAME="Combination difference";
}

class _window_xmapslab;
class _qtw_filter_combination_difference;

//HEA

class _filter_combination_difference : public _filter
{
public:
  _filter_combination_difference();
  void reset_data();

  void threshold(int Threshold1){Threshold=Threshold1;}
  int threshold(){return Threshold;}

  void color(QColor Color1);
  QColor color(){return Color;}

  void use_normalized_values(bool Use_normalized_values1){Use_normalized_values=Use_normalized_values1;}
  bool use_normalized_values(){return Use_normalized_values;}

  float max_value();

  float get_max_value();

  void update_normalized();
  void update_absolute();

  void update();

protected:
  int Threshold=_filter_ns::THRESHOLD_DEFAULT;

  bool Use_normalized_values=false;
};

//HEA

class _filter_combination_difference_ui : public _filter_combination_difference
{
public:
  _filter_combination_difference_ui(_window_xmapslab *Window1, std::string Name1="Combination difference parameters");
  _filter_combination_difference_ui(_window_xmapslab *Window1,std::map<std::string,std::string> &Parameters,std::string Name1="Combination difference parameters");
  ~_filter_combination_difference_ui();
  void reset_data();

  void show();
  void hide();
  void *get_link();
  void read_parameters(std::map<std::string,std::string> &Parameters);
  void write_parameters(std::map<std::string, std::string> &Parameters);

  void color(QColor Color1);

  void parameter1(int Value){_filter_combination_difference::threshold(Value);}
  int parameter1(){return _filter_combination_difference::threshold();}

  void parameter2(QColor Color1){_filter_combination_difference::color(Color1);}
  QColor parameter2(){return _filter_combination_difference::color();}

  void parameter3(bool State1){_filter_combination_difference::use_normalized_values(State1);}
  bool parameter3(){return _filter_combination_difference::use_normalized_values();}

private:
  _qtw_filter_combination_difference *Qtw_filter_combination_difference=nullptr;
};

//HEA

class _qtw_filter_combination_difference: public QWidget
{
  Q_OBJECT
public:

  _qtw_filter_combination_difference(_window_xmapslab *Window1,_filter_combination_difference_ui *Filter1,std::string Box_name="Element parameters");

  void show(){Group_box_main->show();}
  void hide(){Group_box_main->hide();}
  QGroupBox *get_link(){return Group_box_main;}

  void parameter1(int Value);
  void parameter2(QColor Color1);
  void parameter3(bool State1);

protected slots:
  void parameter1_slot(int Value);
  void parameter2_slot(QColor Color1);
  void parameter3_slot(int State1);

private:
  QGroupBox *Group_box_main=nullptr;
  QGroupBox *Group_box_parameter1=nullptr;

  // 0 Threshold
  QSpinBox *Spinbox_parameter1=nullptr;

  // color
  _button_color_simple *Button_parameter2=nullptr;

  // use normalized values
  QCheckBox *Checkbox_parameter3=nullptr;


  _filter_combination_difference_ui *Filter=nullptr;
  _window_xmapslab *Window=nullptr;
};
#endif
