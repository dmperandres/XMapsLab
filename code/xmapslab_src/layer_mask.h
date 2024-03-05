/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef LAYER_MASK
#define LAYER_MASK

#include <QDialog>
#include <QGroupBox>
#include <QSlider>
#include <QLabel>
#include <QComboBox>

#include <string>
#include "layer_xmapslab.h"
#include "color_bar_abstract.h"

#define DEFINED_layer_mask

namespace _layer_mask_ns
{
  // parameter 1
  const std::string String_group_box_parameter1("Transparence");
  const std::string String_label_parameter1_min("0");
  const std::string String_label_parameter1_max("1");
  const std::string String_label_parameter1_tooltip("Display the value of the transparence");
  const int Parameter1_min_value=0;
  const int Parameter1_max_value=255;
  const int Parameter1_single_step=1;
  const int Parameter1_page_step=1;
  const int Parameter1_tick_interval=25;
  const bool Parameter1_set_tracking=false;
  const std::string String_parameter1_tooltip("Controls the value of the transparence");

  // parameter 2
  const std::string String_group_box_parameter2("Color map");

  const std::string BOX_TEXT="Basic parameters";

  const std::vector<std::string> COLOR_MAPS={"Red","Green","Blue","Autum","Bone","Jet","Winter","Rainbow","Ocean","Summer","Spring","cool","Hsv","Pink","Hot"};

  const int THRESHOLD_DEFAULT=0;
  const int ELEMENT_VALUE_DEFAULT=50;
  const int ELEMENT_ERROR_DEFAULT=0;
}

class _window;
class _qtw_layer_mask;

/*************************************************************************/

class _layer_mask : public _layer_xmapslab
{
public:
  _layer_mask();
  void reset_data();

  void size(int Widht1,int Height1){Width=Widht1;Height=Height1;}
  void add_image(std::shared_ptr<cv::Mat> Image1){Vec_images.push_back(Image1);}

  void data_type(int Data_type1){Data_type=_palette_data_ns::_data_type(Data_type1);}
  int data_type(){return int(Data_type);}

  void set_colormap(std::vector<float> &Vec_proportions,std::vector<QColor> &Vec_colors,int Type);

  void apply_colormap();

  void compute_logic_operation();
  void compute_values();
  void update();

  QColor end_color(){return End_color;}
  float max_value(){return Max_value;}

  void threshold(float Threshold1){Threshold=Threshold1;}
  void logic_operation(_layer_xmapslab_ns::_logic_operation Logic_operation1){Logic_operation=Logic_operation1;}

protected:
  int Width=0;
  int Height=0;

  std::vector<std::shared_ptr<cv::Mat>> Vec_images;
  std::shared_ptr<cv::Mat> Result_gray_image=nullptr;
  float Element_error=0;

  std::shared_ptr<cv::Mat> Color_table=nullptr;

  QColor End_color;

  int Color_map=0;
  bool Computed=false;

  _palette_data_ns::_data_type Data_type;

  float Max_value=-1;

  float Threshold=_layer_mask_ns::THRESHOLD_DEFAULT;
  _layer_ns::_logic_operation Logic_operation=_layer_ns::_logic_operation::LOGIC_OPERATION_A_AND_B;
};

/*************************************************************************/

class _layer_mask_ui : public _layer_mask
{
public:
  _layer_mask_ui(_window *Window1, std::string Name1=_layer_mask_ns::BOX_TEXT);
  ~_layer_mask_ui();
  void reset_data();

  void show();
  void hide();
  void *get_link();
//  void read_parameters(std::map<std::string,std::string> &Parameters);
//  void write_parameters(std::map<std::string,std::string> &Parameters);
//  void get_parameters(std::map<std::string,std::string> &Parameters);

  void parameter1(int Value){_layer_mask::transparency(float(Value)/255.0f);}
  int parameter1(){return int(_layer_mask::transparency()*255.0f);}

  void parameter2(int Value){_layer_mask::data_type(Value);}
  int parameter2(){return _layer_mask::data_type();}

  void colormap(int Value);

private:
  _qtw_layer_mask *Qtw_layer_mask=nullptr;
};

/*************************************************************************/

class _qtw_layer_mask: public QWidget
{
  Q_OBJECT
public:
  _qtw_layer_mask(_window *Window1,_layer_mask_ui *Filter1,std::string Box_name="Canny parameters");

  void show(){Group_box_main->show();}
  void hide(){Group_box_main->hide();}
  QGroupBox *get_link(){return Group_box_main;}

  void parameter1(int Value);
  void parameter2(int Value);

protected slots:
  void parameter1_slot(int Value);
  void parameter2_slot(int Value);

private:
  QGroupBox *Group_box_main=nullptr;
  QGroupBox *Group_box_parameter1=nullptr;
  QGroupBox *Group_box_parameter2=nullptr;

  // Transparence
  QSlider *Slider_parameter1=nullptr;
  QLineEdit *Line_edit_parameter1=nullptr;

  //
  QComboBox *Combobox_parameter2=nullptr;

  _layer_mask_ui *Filter=nullptr;
  _window *Window=nullptr;
};
#endif
