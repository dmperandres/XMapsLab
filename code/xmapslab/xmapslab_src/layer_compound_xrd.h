//LIC

#ifndef LAYER_COMPOUND
#define LAYER_COMPOUND

#include <QDialog>
#include <QGroupBox>
#include <QSlider>
#include <QLabel>
#include <QComboBox>

#include "line_edit.h"
#include <string>
#include "layer.h"
#include "color_bar_abstract.h"

#define DEFINED_LAYER_COMPOUND

namespace _layer_compound_ns
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

  enum class _type_compound_operation:unsigned char {TYPE_COMPOUND_OPERATION_FREE,TYPE_COMPOUND_OPERATION_FIXED};

  const int THRESHOLD_DEFAULT=0;
  const int ELEMENT_VALUE_DEFAULT=50;
  const int ELEMENT_ERROR_DEFAULT=0;
}

class _window;
class _qtw_layer_compound;

//HEA

class _layer_compound : public _layer
{
public:
  _layer_compound();
  void reset_data();

  void size(int Widht1,int Height1){Width=Widht1;Height=Height1;}
  void add_image(std::shared_ptr<cv::Mat> Image1){Vec_images.push_back(Image1);}


  void add_element_atomic_numbers(vector<float> &Vec_element_atomic_number1){Vec_element_atomic_number=Vec_element_atomic_number1;}
  void add_element_max_values(vector<float> Vec_element_max_value1){Vec_element_max_value=Vec_element_max_value1;}
  void add_element_values(vector<float> Vec_element_value1){Vec_element_value=Vec_element_value1;}
  void add_element_error(float Element_error1){Element_error=Element_error1;}

  void data_type(int Data_type1){Data_type=_palette_data_ns::_data_type(Data_type1);}
  int data_type(){return int(Data_type);}

  void set_colormap(std::vector<float> &Vec_proportions,std::vector<QColor> &Vec_colors,int Type);

  void apply_colormap();

  void compute_values_free_type_operation();
  void compute_values_fixed_type_operation();
  void compute_values();
  void update();

  QColor end_color(){return End_color;}
  float max_value(){return Max_value;}

  void type_compound_operation(_layer_compound_ns::_type_compound_operation Type_compound_operation1){Type_compound_operation=Type_compound_operation1;}
  void threshold(float Threshold1){Threshold=Threshold1;}
  void logic_operation(_layer_ns::_logic_operation Logic_operation1){Logic_operation=Logic_operation1;}
  void arithmetic_operation(_layer_ns::_arithmetic_operation Arithmetic_operation1){Arithmetic_operation=Arithmetic_operation1;}

protected:
//  int Transparence;
  int Width=0;
  int Height=0;

  std::vector<std::shared_ptr<cv::Mat>> Vec_images;

  vector<float> Vec_element_atomic_number;
  vector<float> Vec_element_max_value;
  vector<float> Vec_element_value;
  float Element_error=0;

  shared_ptr<cv::Mat> Color_table;

  QColor End_color;

  int Color_map=0;
  bool Computed=false;

  _palette_data_ns::_data_type Data_type;

  float Max_value=-1;

  float Threshold=_layer_compound_ns::THRESHOLD_DEFAULT;
  _layer_compound_ns::_type_compound_operation Type_compound_operation=_layer_compound_ns::_type_compound_operation::TYPE_COMPOUND_OPERATION_FREE;
  _layer_ns::_logic_operation Logic_operation=_layer_ns::_logic_operation::LOGIC_OPERATION_A_AND_B;
  _layer_ns::_arithmetic_operation Arithmetic_operation=_layer_ns::_arithmetic_operation::ARITHMETC_OPERATION_ADDITION;
};

//HEA

class _layer_compound_ui : public _layer_compound
{
public:
  _layer_compound_ui(_window *Window1, std::string Name1=_layer_compound_ns::BOX_TEXT);
  ~_layer_compound_ui();
  void reset_data();

  void show();
  void hide();
  void *get_link();
//  void read_parameters(std::map<std::string,std::string> &Parameters);
//  void write_parameters(std::map<std::string,std::string> &Parameters);
//  void get_parameters(std::map<std::string,std::string> &Parameters);

  void parameter1(int Value){_layer_compound::transparence(float(Value)/255.0f);}
  int parameter1(){return int(_layer_compound::transparence()*255.0f);}

  void parameter2(int Value){_layer_compound::data_type(Value);}
  int parameter2(){return _layer_compound::data_type();}

  void colormap(int Value);

private:
  _qtw_layer_compound *Qtw_layer_compound=nullptr;
};

//HEA

class _qtw_layer_compound: public QWidget
{
  Q_OBJECT
public:
  _qtw_layer_compound(_window *Window1,_layer_compound_ui *Filter1,std::string Box_name="Canny parameters");

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

  _layer_compound_ui *Filter=nullptr;
  _window *Window=nullptr;
};
#endif
