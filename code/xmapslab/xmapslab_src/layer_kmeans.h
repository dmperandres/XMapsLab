//LIC

#ifndef LAYER_KMEANS_H
#define LAYER_KMEANS_H

#include <QDialog>
#include <QGroupBox>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>

#include "line_edit.h"
#include <string>
#include "layer.h"

#define DEFINED_LAYER_KMEANS

namespace _layer_kmeans_ns
{
  // parameter 1
  const std::string String_group_box_parameter1("Transparency");
  const std::string String_label_parameter1_min("0");
  const std::string String_label_parameter1_max("1");
  const std::string String_label_parameter1_tooltip("Display the value of the transparency");
  const int Parameter1_min_value=0;
  const int Parameter1_max_value=255;
  const int Parameter1_single_step=1;
  const int Parameter1_page_step=1;
  const int Parameter1_tick_interval=25;
  const bool Parameter1_set_tracking=false;
  const std::string String_parameter1_tooltip("Controls the value of the transparency");

  // parameter 2
  const std::string String_group_box_parameter2("Num Colors");
  const std::string String_label_parameter2_min("2");
  const std::string String_label_parameter2_max("50");
  const std::string String_label_parameter2_tooltip("Display the number of colors");
  const int Parameter2_min_value=2;
  const int Parameter2_max_value=50;
  const int Parameter2_single_step=1;
  const int Parameter2_page_step=5;
  const int Parameter2_tick_interval=4;
  const bool Parameter2_set_tracking=false;
  const std::string String_parameter2_tooltip("Controls the appearance of borders: more to the left, less to the right");

  // Default values
  const int KMEANS_NUM_COLORS_DEFAULT=6;// take care of the previous warning

  const std::string BOX_TEXT="K-means parameters";
}

class _window;
class _qtw_layer_kmeans;

//HEA

class _layer_kmeans : public _layer
{
public:
  _layer_kmeans();
  void reset_data();

  void update_layer();
  void update();

  void num_colors(int Num_colors1){Num_colors=Num_colors1;}
  int num_colors(){return Num_colors;}

protected:
  int Num_colors;
};

//HEA

class _layer_kmeans_ui : public _layer_kmeans
{
public:
  _layer_kmeans_ui(_window *Window1, std::string Name1=_layer_kmeans_ns::BOX_TEXT);
  ~_layer_kmeans_ui();
  void reset_data();

  void show();
  void hide();
  void *get_link();
  void enable();
  void disable();
//  void read_parameters(std::map<std::string,std::string> &Parameters);
//  void write_parameters(std::map<std::string,std::string> &Parameters);
//  void get_parameters(std::map<std::string,std::string> &Parameters);

  void parameter1(int Value){_layer_kmeans::transparency(float(Value)/255.0f);}
  int parameter1(){return int(_layer_kmeans::transparency()*255.0f);}

  void parameter2(int Value){_layer_kmeans::num_colors(Value);}
  int parameter2(){return _layer_kmeans::num_colors();}

private:
  _qtw_layer_kmeans *Qtw_layer_kmeans=nullptr;
};

//HEA

class _qtw_layer_kmeans: public QWidget
{
  Q_OBJECT
public:
  _qtw_layer_kmeans(_window *Window1,_layer_kmeans_ui *Filter1,std::string Box_name=_layer_kmeans_ns::BOX_TEXT);

  void show(){Group_box_main->show();}
  void hide(){Group_box_main->hide();}
  QGroupBox *get_link(){return Group_box_main;}
  void enable(){Group_box_main->setEnabled(true);}
  void disable(){Group_box_main->setEnabled(false);}

  void parameter1(int Value);
  void parameter2(int Value);

protected slots:
  void parameter1_slot(int Value);
  void parameter2_slot(int Value);

private:
  QGroupBox *Group_box_main=nullptr;
  QGroupBox *Group_box_parameter1=nullptr;
  QGroupBox *Group_box_parameter2=nullptr;

  // Transparency
  QSlider *Slider_parameter1=nullptr;
  QLineEdit *Line_edit_parameter1=nullptr;

  // Num_colors
  QSlider *Slider_parameter2=nullptr;
  QLineEdit *Line_edit_parameter2=nullptr;

  _layer_kmeans_ui *Filter=nullptr;
  _window *Window=nullptr;
};
#endif
