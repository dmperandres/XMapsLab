//LIC

#ifndef LAYER_XMAPSLAB_H
#define LAYER_XMAPSLAB_H

#include <opencv.hpp>
#include <string>
#include <memory>
#include <string>
#include <QIcon>
#include <QLineEdit>

#include "common.h"

namespace _layer_xmapslab_ns
{
   enum class _type: unsigned char {TYPE_IMAGE,TYPE_MAP};

   enum class _subtype: unsigned char {SUBTYPE_IMAGE,SUBTYPE_POSITIONS,SUBTYPE_MASKS,SUBTYPE_CANNY,SUBTYPE_DOG,SUBTYPE_KANG,SUBTYPE_MHD_DISTANCE,SUBTYPE_TRIANGULATION, SUBTYPE_RBF_INTERPOLATION,SUBTYPE_RBF_FAST_INTERPOLATION, SUBTYPE_KMEANS, SUBTYPE_COMPOUND_COMBINATION,SUBTYPE_LAB, SUBTYPE_MHD_SEGMENTATION, SUBTYPE_VALUE_SEGMENTATION};

  enum class _logic_operation: unsigned char {LOGIC_OPERATION_A_AND_B,LOGIC_OPERATION_A_OR_B,LOGIC_OPERATION_A_AND_NOT_B,LOGIC_OPERATION_A_OR_NOT_B,LOGIC_OPERATION_NOT_A};
  enum class _arithmetic_operation: unsigned char {ARITHMETC_OPERATION_ADDITION,ARITHMETC_OPERATION_PRODUCT};

  const std::vector<QString> Vec_names_logic_operations={"A AND B","A OR  B","A AND NOT B","A OR  NOT B","NOT A"};
  const std::vector<QString> Vec_names_arithmetic_operations={"Quantities (+)","Proportions (*)"};


//  const std::vector<QString> Vec_additional_layers={"Add auxiliary layers","Canny","Difference of Gaussians","Kang", "K-means"};
//  enum class _additional_layer: unsigned char{ADDITIONAL_LAYER_NOTHING, ADDITIONAL_LAYER_CANNY, ADDITIONAL_LAYER_DOG, ADDITIONAL_LAYER_KANG, ADDITIONAL_LAYER_KMEANS};

  const std::vector<QString> Vec_additional_layers={"Add auxiliary layers","Difference of Gaussians"};
  enum class _additional_layer: unsigned char{ADDITIONAL_LAYER_NOTHING, ADDITIONAL_LAYER_DOG};

}

//class _gl_widget;
class _window_xmapslab;

class _layer_xmapslab
{
public:

  _layer_xmapslab();

  std::string name(){return Name;}

  void image(std::shared_ptr<cv::Mat> Image1){Image=Image1;}
  std::shared_ptr<cv::Mat> image(){return Image;}

  std::shared_ptr<cv::Mat> result_floats_image(){return Result_floats_image;}

  void add_input_image(std::shared_ptr<cv::Mat> Image1){Vec_input_images.push_back(Image1);}
  std::shared_ptr<cv::Mat> input_image(int Pos);

//  void add_image_alpha_channel(std::shared_ptr<cv::Mat> Image_alpha_channel1){Image_alpha_channel=Image_alpha_channel1;}
//  std::shared_ptr<cv::Mat> image_alpha_channel(){return Image_alpha_channel;}

  void icon(QIcon *Icon1){Icon=Icon1;}
  QIcon *icon(){return Icon;}

  void state(int Pos,bool State1){State[Pos]=State1;}
  bool state(int Pos){return State[Pos];}

  void transparency(float Vec_transparency1){Vec_transparency=Vec_transparency1;}
  float transparency(){return Vec_transparency;}

  void inversion(bool Inversion1){Inversion=Inversion1;}
  bool inversion(){return Inversion;}

  void color_mixing_min(float Color_mixing1){Color_mixing_min=Color_mixing1;Color_mixing_changed=true;}
  float color_mixing_min(){return Color_mixing_min;}

  void color_mixing_max(float Color_mixing1){Color_mixing_max=Color_mixing1;Color_mixing_changed=true;}
  float color_mixing_max(){return Color_mixing_max;}

  _layer_xmapslab_ns::_type type(){return Type;}
  _layer_xmapslab_ns::_subtype subtype(){return Subtype;}

  // void xray_data_type(_common_ns::_xray_data_type Xray_data_type1){Xray_data_type=Xray_data_type1;}
  // _common_ns::_xray_data_type xray_data_type(){return Xray_data_type;}

  std::vector<int> vec_values_histogram();

  virtual void update()=0;
  virtual void show()=0;
  virtual void hide()=0;
  virtual void *get_link()=0;
  virtual void enable()=0;
  virtual void disable()=0;
//  virtual void reset_data()=0;
//  virtual void read_parameters(std::map<std::string,std::string> &Parameters)=0;
//  virtual void write_parameters(std::map<std::string,std::string> &Parameters)=0;
//  virtual bool use_dots()=0;

//  void copy_input_to_output();

  int width(){return Image->cols;}
  int height(){return Image->rows;}

protected:

  void compute_histogram();

  _window_xmapslab *Window=nullptr;

  std::vector<std::shared_ptr<cv::Mat>> Vec_input_images;

  std::shared_ptr<cv::Mat> Image=nullptr;

//  std::shared_ptr<cv::Mat> Image_alpha_channel=nullptr;

  std::shared_ptr<cv::Mat> Result_floats_image=nullptr;

  std::string Name;

  bool State[2];
  float Vec_transparency=0.0f;

  bool Color_mixing_changed=true;
  float Color_mixing_min=0.0;
  float Color_mixing_max=1.0;


  _layer_xmapslab_ns::_type Type;
  _layer_xmapslab_ns::_subtype Subtype;
  bool Inversion=false;

  QIcon *Icon=nullptr;

  int Num_channels;

  bool Histogram_computed=false;
  std::vector<int> Vec_values_histogram;

  //
  _common_ns::_xray_data_type Xray_data_type;
};

#endif
