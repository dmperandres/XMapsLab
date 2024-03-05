/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef FILTER_H
#define FILTER_H

#include <opencv.hpp>
#include <string>
#include <memory>
#include <string>
#include <vector>
#include <QString>
#include <QColor>
#include <memory>
#include <vector>

#include "button_color_simple.h"
#include "palette_data.h"
#include "ne_port.h"

namespace _filter_ns
{
  const int MAX_CONNECTIONS=3;

  const int THRESHOLD_DEFAULT=10;

//  typedef enum {TYPE_UI_8=CV_8UC1,TYPE_FLOAT_32=CV_32FC1} _type;

  // 1 include the name of the filter as an identifier
  enum class _filter_type:unsigned char {FILTER_TYPE_IMAGE,FILTER_TYPE_ELEMENT,FILTER_TYPE_CONVERSION_TO_BIN_OP,FILTER_TYPE_CONVERSION_COLOR_TO_BIN_OP,FILTER_TYPE_LOGIC_AND_OP,FILTER_TYPE_LOGIC_OR_OP,FILTER_TYPE_LOGIC_XOR_OP,FILTER_TYPE_LOGIC_NOT_OP,FILTER_TYPE_ARITHMETIC_PRODUCT_OP,FILTER_TYPE_ARITHMETIC_ADDITION_OP,FILTER_TYPE_COMBINATION_ELEMENT_OP,FILTER_TYPE_COMBINATION_ELEMENT_REMOVE_OP,FILTER_TYPE_COMBINATION_PRODUCT_OP,FILTER_TYPE_COMBINATION_ADDITION_OP,FILTER_TYPE_COMBINATION_ADDITION_REMOVE_OP,FILTER_TYPE_COMBINATION_DIFFERENCE_OP,FILTER_TYPE_COMBINATION_ADDITION_PERCENTAGE_OP,FILTER_TYPE_COLORMAP_OP,FILTER_TYPE_ERROR};

  const std::vector<std::string> Vec_filter_type_name={"IMAGE","ELEMENT","CONVERSION_BIN","CONVERSION_COLOR_BIN","LOGIC_AND","LOGIC_OR","LOGIC_XOR","LOGIC_NOT","ARITHMETIC_PRODUCT","ARITHMETIC_ADDITION","COMBINATION_ELEMENT","COMBINATION_ELEMENT_REMOVE","COMBINATION_PRODUCT","COMBINATION_ADDITION","COMBINATION_ADDITION_REMOVE","COMBINATION_DIFFERENCE","COMBINATION_ADD_%","COLORMAP","ERROR"};

  const std::vector<std::string> Vec_filter_type_name_short={"","","B","CB","&","|","X","~","*","+","","-","*","+","+_R","-","%","C","E"};

  enum class _filter_class:unsigned char {FILTER_CLASS_IMAGE,FILTER_CLASS_ELEMENT,FILTER_CLASS_BINARY,FILTER_CLASS_COMBINATION,FILTER_CLASS_COLORMAP,FILTER_CLASS_ARITHMETIC};

  typedef struct {
    std::string Port_name;
    _ne_port_ns::_port_class Port_class;
    bool Open;
  } _port_data;

  typedef struct {
    _filter_type Type;
    _filter_class Class;
    std::string Name;
    std::vector<_port_data> Vec_input_ports;
    std::vector<_port_data> Vec_output_ports;
  } _filter_parameters;

  typedef struct {
    std::string Name;
    std::string Description;
  } _filter_text; 

//  typedef enum {FILTER_ELEMENT,FILTER_LOGIC_Y_OP,FILTER_LOGIC_O_OP,FILTER_LOGIC_NO_OP} _type_filter;

  static std::string to_upper_case(std::string String)
  {
    std::string Result=String;
    std::for_each(Result.begin(), Result.end(), [](char & c){c = ::toupper(c);});
    return Result;
  }

  const std::string Image_lower="image";
  const std::string Element_lower="element";
  const std::string Element_lower_short="ele";
  const std::string Binary_lower="binary";
  const std::string Color_binary_lower="color_bin";
  const std::string Arithmetic_pre_lower="arith";
  const std::string Combination_pre_lower="combi";
  const std::string Product_lower="pro";
  const std::string Addition_lower="add";
  const std::string Remove_lower="rem";
  const std::string Percentage_lower="per";
  const std::string Not_lower="not";
  const std::string Difference_lower="dif";
  const std::string Product="*";
  const std::string Addition="+";
  const std::string Percentage="%";
  const std::string Difference="-";

  const std::string Binary_not_lower="not";
  const std::string Binary_and_lower="and";
  const std::string Binary_or_lower="or";
  const std::string Binary_xor_lower="xor";

  const std::string Arithmetic_product_lower=Arithmetic_pre_lower+"_"+Product_lower;
  const std::string Arithmetic_addition_lower=Arithmetic_pre_lower+"_"+Addition_lower;

  const std::string Combination_element_lower=Combination_pre_lower+"_"+Element_lower_short;
  const std::string Combination_element_remove_lower=Combination_pre_lower+"_"+Element_lower_short+"_"+Remove_lower;
  const std::string Combination_product_lower=Combination_pre_lower+"_"+Product_lower;
  const std::string Combination_addition_lower=Combination_pre_lower+"_"+Addition_lower;
  const std::string Combination_addition_remove_lower=Combination_pre_lower+"_"+Addition_lower+"_"+Remove_lower;
  const std::string Combination_difference_lower=Combination_pre_lower+"_"+Difference_lower;
  const std::string Combination_addition_percentage_lower=Combination_pre_lower+"_"+Addition_lower+"_"+Percentage_lower;

  const std::string Colormap_lower="colormap";

  const std::string Image_upper=to_upper_case(Image_lower);
  const std::string Element_upper=to_upper_case(Element_lower);
  const std::string Binary_upper=to_upper_case(Binary_lower);
  const std::string Color_binary_upper=to_upper_case(Color_binary_lower);
  const std::string Arithmetic_pre_upper=to_upper_case(Arithmetic_pre_lower);
  const std::string Combination_pre_upper=to_upper_case(Combination_pre_lower);
  const std::string Product_upper=to_upper_case(Product_lower);
  const std::string Addition_upper=to_upper_case(Addition_lower);
  const std::string Remove_upper=to_upper_case(Remove_lower);
  const std::string Difference_upper=to_upper_case(Difference_lower);
  const std::string Not_upper=to_upper_case(Not_lower);

  const std::string Binary_not_upper=to_upper_case(Binary_not_lower);
  const std::string Binary_and_upper=to_upper_case(Binary_and_lower);
  const std::string Binary_or_upper=to_upper_case(Binary_or_lower);
  const std::string Binary_xor_upper=to_upper_case(Binary_xor_lower);

  const std::string Arithmetic_product_upper=to_upper_case(Arithmetic_product_lower);
  const std::string Arithmetic_addition_upper=to_upper_case(Arithmetic_addition_lower);

  const std::string Combination_element_upper=to_upper_case(Combination_element_lower);
  const std::string Combination_element_remove_upper=to_upper_case(Combination_element_remove_lower);
  const std::string Combination_product_upper=to_upper_case(Combination_product_lower);
  const std::string Combination_addition_upper=to_upper_case(Combination_addition_lower);
  const std::string Combination_addition_remove_upper=to_upper_case(Combination_addition_remove_lower);
  const std::string Combination_difference_upper=to_upper_case(Combination_difference_lower);
  const std::string Combination_addition_percentage_upper=to_upper_case(Combination_addition_percentage_lower);

  const std::string Colormap_upper=to_upper_case(Colormap_lower);

  const std::string Port_input_1="A";
  const std::string Port_input_2="B";
  const std::string Port_input_3="C";

  const std::string Port_output_1="out";

  const std::string Rest_of="~";

  const std::string Text_list_conversion_binary=Binary_upper+" "+Port_input_1;
  const std::string Text_list_conversion_color_binary=Color_binary_upper+" "+Port_input_1;

  const std::string Text_list_binary_not=Not_upper+" "+Port_input_1;
  const std::string Text_list_binary_and=Port_input_1+" "+Binary_and_upper+" "+Port_input_2;
  const std::string Text_list_binary_or=Port_input_1+" "+Binary_or_upper+" "+Port_input_2;
  const std::string Text_list_binary_xor=Port_input_1+" "+Binary_xor_upper+" "+Port_input_2;

  const std::string Text_list_combination_element=Binary_upper+" "+Product+" ("+Port_input_1+")";
  const std::string Text_list_combination_element_remove=Binary_upper+" "+Product+" ("+Port_input_1+")"+Rest_of;
  const std::string Text_list_combination_product=Binary_upper+" "+Product+" ("+Port_input_1+" "+Product+" "+Port_input_2+")";
  const std::string Text_list_combination_addition=Binary_upper+" "+Product+" ("+Port_input_1+" "+Addition+" "+Port_input_2+")";
  const std::string Text_list_combination_addition_remove=Binary_upper+" "+Product+" ("+Port_input_1+ Percentage+" "+Addition+" "+Port_input_2+Percentage+")"+Rest_of;
  const std::string Text_list_combination_difference=Binary_upper+" "+Product+" ("+Port_input_1+" "+Difference+" "+Port_input_2+")";
  const std::string Text_list_combination_addition_percentage=Binary_upper+" "+Product+" ("+Port_input_1+Percentage+" "+Addition+" "+Port_input_2+Percentage+")";
  const std::string Text_list_colormap=Colormap_upper;

  const std::vector<std::string> Vec_names_filters={Image_upper,Element_upper, Binary_upper, Color_binary_upper, Binary_and_upper, Binary_or_upper, Binary_xor_upper, Binary_not_upper,  Arithmetic_product_upper, Arithmetic_addition_upper, Combination_element_upper, Combination_element_remove_upper, Combination_product_upper, Combination_addition_upper, Combination_addition_remove_upper, Combination_difference_upper, Combination_addition_percentage_upper, Colormap_upper};

  // 2 include the name of the filter as a string
  static std::map<std::string,_filter_type> Type_filter_name={
    {Image_upper,_filter_type::FILTER_TYPE_IMAGE},
    {Element_upper,_filter_type::FILTER_TYPE_ELEMENT},
    {Binary_upper,_filter_type::FILTER_TYPE_CONVERSION_TO_BIN_OP},
    {Color_binary_upper,_filter_type::FILTER_TYPE_CONVERSION_COLOR_TO_BIN_OP},
    {Binary_and_upper,_filter_type::FILTER_TYPE_LOGIC_AND_OP},
    {Binary_or_upper,_filter_type::FILTER_TYPE_LOGIC_OR_OP},
    {Binary_xor_upper,_filter_type::FILTER_TYPE_LOGIC_XOR_OP},
    {Binary_not_upper,_filter_type::FILTER_TYPE_LOGIC_NOT_OP},
    {Arithmetic_product_upper,_filter_type::FILTER_TYPE_ARITHMETIC_PRODUCT_OP},
    {Arithmetic_addition_upper,_filter_type::FILTER_TYPE_ARITHMETIC_ADDITION_OP},
    {Combination_element_upper,_filter_type::FILTER_TYPE_COMBINATION_ELEMENT_OP},
    {Combination_element_remove_upper,_filter_type::FILTER_TYPE_COMBINATION_ELEMENT_REMOVE_OP},
    {Combination_product_upper,_filter_type::FILTER_TYPE_COMBINATION_PRODUCT_OP},
    {Combination_addition_upper,_filter_type::FILTER_TYPE_COMBINATION_ADDITION_OP},
    {Combination_addition_remove_upper,_filter_type::FILTER_TYPE_COMBINATION_ADDITION_REMOVE_OP},
    {Combination_difference_upper,_filter_type::FILTER_TYPE_COMBINATION_DIFFERENCE_OP},
    {Combination_addition_percentage_upper,_filter_type::FILTER_TYPE_COMBINATION_ADDITION_PERCENTAGE_OP},
    {Colormap_upper,_filter_type::FILTER_TYPE_COLORMAP_OP}
  };

//  _filter_type Type;
//  _filter_class Class;
//  std::string Name;
//  std::vector<std::string> Vec_input_ports;
//  std::vector<std::string> Vec_output_ports;

  const _ne_port_ns::_port_class PORT_CONTINUOUS=_ne_port_ns::_port_class::PORT_CLASS_CONTINUOUS;
  const _ne_port_ns::_port_class PORT_BINARY=_ne_port_ns::_port_class::PORT_CLASS_BINARY;
//  const _ne_port_ns::_port_class PORT_BINARY_OPEN=_ne_port_ns::_port_class::PORT_CLASS_BINARY_OPEN;

  // 3 information for the node editor
  // {Key,{Values}}
  // Type, Class, Name, Num_parameters, input_ports, output_ports
  static std::map<_filter_type,_filter_parameters> Filter_name_parameters={
    {_filter_type::FILTER_TYPE_IMAGE, {_filter_type::FILTER_TYPE_IMAGE,_filter_class::FILTER_CLASS_IMAGE, Image_lower,{},{{Port_output_1,PORT_CONTINUOUS, false}}}},
    {_filter_type::FILTER_TYPE_ELEMENT, {_filter_type::FILTER_TYPE_ELEMENT,_filter_class::FILTER_CLASS_ELEMENT, Element_lower,{},{{Port_output_1,PORT_CONTINUOUS, false}}}},
    {_filter_type::FILTER_TYPE_CONVERSION_TO_BIN_OP,{_filter_type::FILTER_TYPE_CONVERSION_TO_BIN_OP,_filter_class::FILTER_CLASS_BINARY, Binary_lower,{{Port_input_1,PORT_CONTINUOUS, false}},{{Port_output_1,PORT_BINARY, false}}}},
    {_filter_type::FILTER_TYPE_CONVERSION_COLOR_TO_BIN_OP,{_filter_type::FILTER_TYPE_CONVERSION_COLOR_TO_BIN_OP,_filter_class::FILTER_CLASS_BINARY, Color_binary_lower,{{Port_input_1,PORT_CONTINUOUS, false}},{{Port_output_1,PORT_BINARY, false}}}},
    {_filter_type::FILTER_TYPE_LOGIC_AND_OP, {_filter_type::FILTER_TYPE_LOGIC_AND_OP,_filter_class::FILTER_CLASS_BINARY,Binary_and_lower,{{Port_input_1,PORT_BINARY, false},{Port_input_2,PORT_BINARY, false}},{{Port_output_1,PORT_BINARY, false}}}},
    {_filter_type::FILTER_TYPE_LOGIC_OR_OP,{_filter_type::FILTER_TYPE_LOGIC_OR_OP,_filter_class::FILTER_CLASS_BINARY, Binary_or_lower,{{Port_input_1,PORT_BINARY, false},{Port_input_2,PORT_BINARY, false}},{{Port_output_1,PORT_BINARY, false}}}},
    {_filter_type::FILTER_TYPE_LOGIC_XOR_OP,{_filter_type::FILTER_TYPE_LOGIC_XOR_OP,_filter_class::FILTER_CLASS_BINARY, Binary_xor_lower,{{Port_input_1,PORT_BINARY, false},{Port_input_2,PORT_BINARY, false}},{{Port_output_1,PORT_BINARY, false}}}},
    {_filter_type::FILTER_TYPE_LOGIC_NOT_OP,{_filter_type::FILTER_TYPE_LOGIC_NOT_OP,_filter_class::FILTER_CLASS_BINARY, Binary_not_lower,{{Port_input_1,PORT_BINARY, false}},{{Port_output_1,PORT_BINARY, false}}}},
    {_filter_type::FILTER_TYPE_ARITHMETIC_PRODUCT_OP,{_filter_type::FILTER_TYPE_ARITHMETIC_PRODUCT_OP,_filter_class::FILTER_CLASS_ARITHMETIC,Arithmetic_product_lower,{{Port_input_1,PORT_CONTINUOUS, false},{Port_input_2,PORT_CONTINUOUS, false}},{{Port_output_1,PORT_CONTINUOUS, false}}}},
    {_filter_type::FILTER_TYPE_ARITHMETIC_ADDITION_OP,{_filter_type::FILTER_TYPE_ARITHMETIC_ADDITION_OP, _filter_class::FILTER_CLASS_ARITHMETIC, Arithmetic_addition_lower,{{Port_input_1,PORT_CONTINUOUS, false},{Port_input_2,PORT_CONTINUOUS, false}},{{Port_output_1,PORT_CONTINUOUS, false}}}},
    {_filter_type::FILTER_TYPE_COMBINATION_ELEMENT_OP,{_filter_type::FILTER_TYPE_COMBINATION_ELEMENT_OP, _filter_class::FILTER_CLASS_COMBINATION, Combination_element_lower,{{Binary_lower,PORT_BINARY, true},{Port_input_1,PORT_CONTINUOUS, false}},{{Port_output_1,PORT_CONTINUOUS, false}}}},
    {_filter_type::FILTER_TYPE_COMBINATION_ELEMENT_REMOVE_OP,{_filter_type::FILTER_TYPE_COMBINATION_ELEMENT_REMOVE_OP,_filter_class::FILTER_CLASS_COMBINATION, Combination_element_remove_lower,{{Binary_lower,PORT_BINARY,true},{Port_input_1,PORT_CONTINUOUS, false}},{{Port_output_1,PORT_CONTINUOUS, false}}}},
    {_filter_type::FILTER_TYPE_COMBINATION_PRODUCT_OP,{_filter_type::FILTER_TYPE_COMBINATION_PRODUCT_OP, _filter_class::FILTER_CLASS_COMBINATION, Combination_product_lower,{{Binary_lower,PORT_BINARY, true},{Port_input_1,PORT_CONTINUOUS, false},{Port_input_2,PORT_CONTINUOUS, false}},{{Port_output_1,PORT_CONTINUOUS, false}}}},
    {_filter_type::FILTER_TYPE_COMBINATION_ADDITION_OP,{_filter_type::FILTER_TYPE_COMBINATION_ADDITION_OP, _filter_class::FILTER_CLASS_COMBINATION, Combination_addition_lower,{{Binary_lower,PORT_BINARY, true},{Port_input_1,PORT_CONTINUOUS, false},{Port_input_2,PORT_CONTINUOUS, false}},{{Port_output_1,PORT_CONTINUOUS, false}}}},
    {_filter_type::FILTER_TYPE_COMBINATION_ADDITION_REMOVE_OP,{_filter_type::FILTER_TYPE_COMBINATION_ADDITION_REMOVE_OP, _filter_class::FILTER_CLASS_COMBINATION, Combination_addition_remove_lower,{{Binary_lower,PORT_BINARY, true},{Port_input_1,PORT_CONTINUOUS, false},{Port_input_2,PORT_CONTINUOUS, false}},{{Port_output_1,PORT_CONTINUOUS, false},{Rest_of+Port_input_1,PORT_CONTINUOUS, false},{Rest_of+Port_input_2,PORT_CONTINUOUS, false}}}},
    {_filter_type::FILTER_TYPE_COMBINATION_DIFFERENCE_OP,{_filter_type::FILTER_TYPE_COMBINATION_DIFFERENCE_OP, _filter_class::FILTER_CLASS_COMBINATION, Combination_difference_lower,{{Binary_lower,PORT_BINARY, true},{Port_input_1,PORT_CONTINUOUS, false},{Port_input_2,PORT_CONTINUOUS, false}},{{Port_output_1,PORT_CONTINUOUS, false}}}},
    {_filter_type::FILTER_TYPE_COMBINATION_ADDITION_PERCENTAGE_OP,{_filter_type::FILTER_TYPE_COMBINATION_ADDITION_PERCENTAGE_OP, _filter_class::FILTER_CLASS_COMBINATION, Combination_addition_percentage_lower,{{Binary_lower,PORT_BINARY, true},{Port_input_1,PORT_CONTINUOUS, false},{Port_input_2,PORT_CONTINUOUS, false}},{{Port_output_1,PORT_CONTINUOUS, false}}}},
{_filter_type::FILTER_TYPE_COLORMAP_OP,{_filter_type::FILTER_TYPE_COLORMAP_OP, _filter_class::FILTER_CLASS_COLORMAP, Colormap_lower,{{Port_input_1,PORT_CONTINUOUS, false}},{{Port_output_1,PORT_CONTINUOUS, false}}}}
  };

  // 4 help information
  static std::map<_filter_type,_filter_text> Filter_name_text={
  {_filter_type::FILTER_TYPE_IMAGE,
  {"<b>Image</b>","<p>This is the input data of the element</p><p><b>Output:</b> Color map</p>"}},
  {_filter_type::FILTER_TYPE_ELEMENT,
  {"<b>Element</b>","<p>This is the input data of the element</p><p><b>Output:</b> Color map</p>"}},
  {_filter_type::FILTER_TYPE_CONVERSION_TO_BIN_OP,
  {"<b>Conversion BIN</b>","<p>This filter convert the input data to binary data using a threshold</p><p><b>Input:</b> Color map</p><p><b>Output:</b> Binary image (White color=No data, Black color= data)</p><p><b>Threshold:</b> Input values that are less than the threshold are mapped to 0; The rest of values are mapped to 1</p>"}},
  {_filter_type::FILTER_TYPE_CONVERSION_COLOR_TO_BIN_OP,
  {"<b>Conversion COLOR BIN</b>","<p>This filter convert the input data to binary data using a threshold</p><p><b>Input:</b> Color map</p><p><b>Output:</b> Binary image (White color=No data, Black color= data)</p><p><b>Threshold:</b> Input values that are less than the threshold are mapped to 0; The rest of values are mapped to 1</p>"}},
  {_filter_type::FILTER_TYPE_LOGIC_NOT_OP,
  {"<b>Binary NOT</b>","<p>This filter convert the input data to binary data using a threshold. The result is negated</p><p><b>Input:</b> Color map</p><p><b>Output:</b> Binary image (White color=No data, Black color= data)</p><p><b>Threshold:</b> Input values that are less than the threshold are mapped to 0; The rest of values are mapped to 1</p>"}},
  {_filter_type::FILTER_TYPE_LOGIC_AND_OP,
  {"<b>Binary AND</b>","<p>This filter applies an AND logic operation</p><p><b>Input:</b> Binary data</p><p><b>Output:</b> Binary data (White color=No data, Black color= data)</p>"}},
  {_filter_type::FILTER_TYPE_LOGIC_OR_OP,
  {"<b>Binary OR</b>","<p>This filter applies an OR logic operation</p><p><b>Input:</b> Binary data</p><p><b>Output:</b> Binary data (White color=No data, Black color= data)</p>"}},
  {_filter_type::FILTER_TYPE_LOGIC_XOR_OP,
  {"<b>Binary XOR</b>","<p>This filter applies an XOR logic operation</p><p><b>Input:</b> Binary data</p><p><b>Output:</b> Binary data (White color=No data, Black color= data)</p>"}},
  {_filter_type::FILTER_TYPE_ARITHMETIC_PRODUCT_OP,
  {"<b>Arithmetic product</b>","<p>This filter applies Canny edge detector</p><p><b>Input:</b> Grayscale image</p><p><b>Output:</b> Grayscale image</p>"}},
  {_filter_type::FILTER_TYPE_ARITHMETIC_ADDITION_OP,
  {"<b>Arithmetic addition</b>","<p>This filter applies Canny edge detector</p><p><b>Input:</b> Grayscale image</p><p><b>Output:</b> Grayscale image</p>"}},
  {_filter_type::FILTER_TYPE_COMBINATION_ELEMENT_OP,
  {"<b>Combination element</b>","<p>This filter applies Canny edge detector</p><p><b>Input:</b> Grayscale image</p><p><b>Output:</b> Grayscale image</p>"}},
  {_filter_type::FILTER_TYPE_COMBINATION_ELEMENT_REMOVE_OP,
  {"<b>Combination remove</b>","<p>This filter applies Canny edge detector</p><p><b>Input:</b> Grayscale image</p><p><b>Output:</b> Grayscale image</p>"}},
  {_filter_type::FILTER_TYPE_COMBINATION_PRODUCT_OP,
  {"<b>Combination product</b>","<p>This filter applies Canny edge detector</p><p><b>Input:</b> Grayscale image</p><p><b>Output:</b> Grayscale image</p>"}},
  {_filter_type::FILTER_TYPE_COMBINATION_ADDITION_OP,
  {"<b>Combination addition</b>","<p>This filter applies Canny edge detector</p><p><b>Input:</b> Grayscale image</p><p><b>Output:</b> Grayscale image</p>"}},
  {_filter_type::FILTER_TYPE_COMBINATION_ADDITION_REMOVE_OP,
  {"<b>Combination addition</b>","<p>This filter applies Canny edge detector</p><p><b>Input:</b> Grayscale image</p><p><b>Output:</b> Grayscale image</p>"}},
  {_filter_type::FILTER_TYPE_COMBINATION_DIFFERENCE_OP,
  {"<b>Combination difference</b>","<p>This filter applies Canny edge detector</p><p><b>Input:</b> Grayscale image</p><p><b>Output:</b> Grayscale image</p>"}},
  {_filter_type::FILTER_TYPE_COMBINATION_ADDITION_PERCENTAGE_OP,
  {"<b>Combination addition percentage</b>","<p>This filter applies Canny edge detector</p><p><b>Input:</b> Grayscale image</p><p><b>Output:</b> Grayscale image</p>"}},
  {_filter_type::FILTER_TYPE_COLORMAP_OP,
  {"<b>Combination addition</b>","<p>This filter applies Canny edge detector</p><p><b>Input:</b> Grayscale image</p><p><b>Output:</b> Grayscale image</p>"}}
  };
}

class _window_xmapslab;
class _gl_widget_ge;

class _filter
{
public:
//  _filter(_window *Window1){Window=Window1;}

  void name(std::string Name1){Name=Name1;}
  std::string name(){return Name;}

  std::string filter_type_name(){
    return _filter_ns::Vec_filter_type_name[int(Filter_type)];
  }

  void set_data(std::vector<std::shared_ptr<cv::Mat>> Vec_input_data1, std::vector<std::shared_ptr<cv::Mat>> Vec_output_data1, std::vector<std::shared_ptr<cv::Mat>> Vec_output_images1, std::vector<float> Vec_max_value_input_data1);
  void set_input_filters(std::vector<std::shared_ptr<_filter>> Vec_input_filters1,std::vector<int> Vec_input_port_index1);
  void set_original_image(std::shared_ptr<cv::Mat> Original_image1){Original_image=Original_image1;}

  std::shared_ptr<cv::Mat> get_result(){
    if (Vec_output_data.size()>0) return Vec_output_data[0];
    else return nullptr;
  }

  virtual void update()=0;
  virtual void show()=0;
  virtual void hide()=0;
  virtual void *get_link()=0;
  virtual void reset_data()=0;
  virtual void read_parameters(std::map<std::string,std::string> &Parameters)=0;
  virtual void write_parameters(std::map<std::string,std::string> &Parameters)=0;

//  void palette(int Palette1){Palette=Palette1;}
//  int palette(){return Palette;}

  void set_colormap(std::vector<float> &Vec_proportions,std::vector<QColor> &Vec_colors,_palette_data_ns::_palette_type Palette_type);
  void apply_colormap(std::shared_ptr<cv::Mat> Float_values_image, std::shared_ptr<cv::Mat> Result_image);

  void max_value_input_data(int Pos,float Max_value1);
  float max_value_input_data(int Pos);

  void max_value_output_data(int Pos,float Max_value1);
  float max_value_output_data(int Pos);

  void update_max_values();

  void filter_type(_filter_ns::_filter_type Filter_type1){Filter_type=Filter_type1;}
  _filter_ns::_filter_type filter_type(){return Filter_type;}

  void filter_class(_filter_ns::_filter_class Filter_class1){Filter_class=Filter_class1;}
  _filter_ns::_filter_class filter_class(){return Filter_class;}

  float max_value(){return Max_value;}

  virtual float get_max_value(){return 0;};

protected:
  std::vector<std::shared_ptr<cv::Mat>> Vec_input_data;
  std::vector<std::shared_ptr<cv::Mat>> Vec_output_data;
  std::vector<std::shared_ptr<cv::Mat>> Vec_output_images;
  std::vector<float> Vec_max_value_input_data;
  std::vector<float> Vec_max_value_output_data;

  std::vector<std::shared_ptr<_filter>> Vec_input_filters;
  std::vector<int> Vec_input_port_index;

  std::shared_ptr<cv::Mat> Color_table=nullptr;

  // used for showing the transparent parts as a pattern
  std::shared_ptr<cv::Mat> Original_image=nullptr;
  
  bool Ready=false;
  std::string Name;
  _filter_ns::_filter_type Filter_type;
  _filter_ns::_filter_class Filter_class;

  float Max_value=0;

  QColor Color;

//  int Palette;
  _window_xmapslab *Window=nullptr;

  bool Relative_normalization=false;
};

#endif
