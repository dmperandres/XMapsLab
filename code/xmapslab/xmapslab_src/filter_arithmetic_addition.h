//LIC

#ifndef FILTER_ARTITHMETIC_ADDITION
#define FILTER_ARTITHMETIC_ADDITION

#include <QDialog>
#include <QGroupBox>
#include <QSpinBox>
#include <QLabel>

#include "line_edit.h"
#include <string>
#include "filter.h"

#define DEFINED_FILTER_ARTITHMETIC_ADDITION

namespace _f_arithmetic_addition_ns
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

  const std::string FILTER_NAME="Arithmetic addition";
}

class _window;
class _qtw_filter_arithmetic_addition;

//HEA

class _filter_arithmetic_addition : public _filter
{
public:
  _filter_arithmetic_addition();
  void reset_data();

  void threshold(int Threshold1){Threshold=Threshold1;}
  int threshold(){return Threshold;}

  void update();

protected:
  int Threshold=_filter_ns::THRESHOLD_DEFAULT;
};

//HEA

class _filter_arithmetic_addition_ui : public _filter_arithmetic_addition
{
public:
  _filter_arithmetic_addition_ui(_window_xmapslab *Window1, std::string Name1="Arithmeti parameters");
  _filter_arithmetic_addition_ui(_window_xmapslab *Window1,std::map<std::string,std::string> &Parameters,std::string Name1="Element parameters");
  ~_filter_arithmetic_addition_ui();
  void reset_data();

  void show();
  void hide();
  void *get_link();
  void read_parameters(std::map<std::string,std::string> &Parameters);
  void write_parameters(std::map<std::string, std::string> &Parameters);

  void parameter1(int Value){_filter_arithmetic_addition::threshold(Value);}
  int parameter1(){return _filter_arithmetic_addition::threshold();}

private:
  _qtw_filter_arithmetic_addition *Qtw_filter_arithmetic_addition;
};

//HEA

class _qtw_filter_arithmetic_addition: public QWidget
{
  Q_OBJECT
public:

  _qtw_filter_arithmetic_addition(_window_xmapslab *Window1, _filter_arithmetic_addition_ui *Filter1, std::string Box_name="Element parameters");

  void show(){Group_box_main->show();}
  void hide(){Group_box_main->hide();}
  QGroupBox *get_link(){return Group_box_main;}

  void parameter1(int Value);

protected slots:
  void parameter1_slot(int Value);

private:
  QGroupBox *Group_box_main=nullptr;
  QGroupBox *Group_box_parameter1=nullptr;

  // 0 Threshold
  QSpinBox *Spinbox_0_threshold_parameter1=nullptr;

  _filter_arithmetic_addition_ui *Filter=nullptr;
  _window_xmapslab *Window=nullptr;
};
#endif
