/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef FILTER_COMBINATION_ADDITION_REMOVE
#define FILTER_COMBINATION_ADDITION_REMOVE

#include <QDialog>
#include <QGroupBox>
#include <QSpinBox>
#include <QLabel>

// #include "line_edit.h"
#include <string>
#include "filter.h"

#include "filter_element.h"

#define DEFINED_FILTER_COMBINATION_ADDITION_REMOVE

namespace _f_combination_addition_remove_ns
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
  const int NUM_ATOMS_DEFAULT=1;
  const int PERCENTAGE_ELEMENT_A_DEFAULT=50;
  const int ERROR_ELEMENT_DEFAULT=5;

  const std::string FILTER_NAME="Combination addition remove";
}

class _window;
class _qtw_filter_combination_addition_remove;

/*************************************************************************/

class _filter_combination_addition_remove : public _filter
{
public:
  _filter_combination_addition_remove();
  void reset_data();

//  void threshold(int Threshold1){Threshold=Threshold1;}
//  int threshold(){return Threshold;}

  void color(QColor Color1);
  QColor color(){return Color;}

  void num_atoms(int Pos,int Num_atoms1);
  int num_atoms(int Pos){return Vec_num_atoms[Pos];}

  void percentage(int Pos, int Percentage1){Vec_percentages[Pos]=Percentage1;}
  int percentage(int Pos){return Vec_percentages[Pos];}

//  void error_element_A(int Error_element_A1){Error_element_A=Error_element_A1;};
//  int error_element_A(){return Error_element_A;}

  void compute_operation(int Row, int Col, std::shared_ptr<cv::Mat> Output_aux, std::shared_ptr<cv::Mat> Output_aux_A, std::shared_ptr<cv::Mat> Output_aux_B, float &Max_value_addition, float &Max_value_1, float &Max_value_2);

  void update();

protected:
  int Threshold=_filter_ns::THRESHOLD_DEFAULT;
  std::vector<int> Vec_num_atoms={1,1};
  std::vector<float> Vec_percentages={0.5f,0.5f};
  std::vector<int> Vec_error_elements={5,5};
};

/*************************************************************************/

class _filter_combination_addition_remove_ui : public _filter_combination_addition_remove
{
public:
  _filter_combination_addition_remove_ui(_window_xmapslab *Window1, std::string Name1="Arithmeti parameters");
  _filter_combination_addition_remove_ui(_window_xmapslab *Window1,std::map<std::string,std::string> &Parameters,std::string Name1="Element parameters");
  ~_filter_combination_addition_remove_ui();
  void reset_data();

  void show();
  void hide();
  void *get_link();
  void read_parameters(std::map<std::string,std::string> &Parameters);
  void write_parameters(std::map<std::string, std::string> &Parameters);

  void color(QColor Color1);

//  void parameter1(int Value){_filter_combination_addition_remove::threshold(Value);}
//  int parameter1(){return _filter_combination_addition_remove::threshold();}

  void parameter2(QColor Color1){_filter_combination_addition_remove::color(Color1);}
  QColor parameter2(){return _filter_combination_addition_remove::color();}

  void parameter3(int Value){_filter_combination_addition_remove::num_atoms(0,Value);}
  int parameter3(){return _filter_combination_addition_remove::num_atoms(0);}

  void parameter4(int Value){_filter_combination_addition_remove::num_atoms(1,Value);}
  int parameter4(){return _filter_combination_addition_remove::num_atoms(1);}

//  void parameter5(int Value){_filter_combination_addition_remove::error_element_A(Value);}
//  int parameter5(){return _filter_combination_addition_remove::error_element_A();}

private:
  _qtw_filter_combination_addition_remove *Qtw_filter_combination_addition_remove=nullptr;
};

/*************************************************************************/

class _qtw_filter_combination_addition_remove: public QWidget
{
  Q_OBJECT
public:

  _qtw_filter_combination_addition_remove(_window_xmapslab *Window1, _filter_combination_addition_remove_ui *Filter1, std::string Box_name="Element parameters");

  void show(){Group_box_main->show();}
  void hide(){Group_box_main->hide();}
  QGroupBox *get_link(){return Group_box_main;}

//  void parameter1(int Value);
  void parameter2(QColor Color1);
  void parameter3(int Value);
  void parameter4(int Value);

//  void parameter5(int Value);

protected slots:
//  void parameter1_slot(int Value);
  void parameter2_slot(QColor Color1);
  void parameter3_slot(int Value);
  void parameter4_slot(int Value);
//  void parameter5_slot(int Value);

private:
  QGroupBox *Group_box_main=nullptr;
  QGroupBox *Group_box_parameter1=nullptr;

  // 0 Threshold
  QSpinBox *Spinbox_parameter1=nullptr;

  // color
  _button_color_simple *Button_parameter2=nullptr;

  // %A
  QSpinBox *Spinbox_parameter3=nullptr;
  // %B
  QSpinBox *Spinbox_parameter4=nullptr;
  // Error of A
//  QSpinBox *Spinbox_parameter5=nullptr;

  _filter_combination_addition_remove_ui *Filter=nullptr;
  _window_xmapslab *Window=nullptr;
};
#endif
