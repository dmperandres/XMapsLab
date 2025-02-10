//LIC

#ifndef LAYER_POSITIONS_H
#define LAYER_POSITIONS_H

#include <opencv.hpp>
#include <string>
#include <memory>
#include <string>
#include <QIcon>

namespace _layer_positions_ns
{
   enum class _layer_type:unsigned char {LAYER_TYPE_BASIC, LAYER_TYPE_CANNY, LAYER_TYPE_DOG, LAYER_TYPE_KANG, LAYER_TYPE_ELEMENT, LAYER_TYPE_ELEMENT_A, LAYER_TYPE_COMBINATION, LAYER_TYPE_POSITIONS} ;
}

class _gl_widget;

class _layer_positions
{
public:

  _layer_positions();

  std::string name(){return Name;}

  void image(std::shared_ptr<cv::Mat> Image1){Image=Image1;}
  std::shared_ptr<cv::Mat> image(){return Image;}

  void add_input_image(std::shared_ptr<cv::Mat> Image1){Vec_input_images.push_back(Image1);}
  std::shared_ptr<cv::Mat> input_image(int Pos);

  void icon(QIcon *Icon1){Icon=Icon1;}
  QIcon *icon(){return Icon;}

  void state(int Pos,bool State1){State[Pos]=State1;}
  bool state(int Pos){return State[Pos];}

  void transparence(float Transparence1){Transparence=Transparence1;}
  float transparence(){return Transparence;}

  void inversion(bool Inversion1){Inversion=Inversion1;}
  bool inversion(){return Inversion;}

  _layer_positions_ns::_layer_type layer_type(){return Layer_type;}

  virtual void update()=0;
  virtual void show()=0;
  virtual void hide()=0;
  virtual void *get_link()=0;
//  virtual void reset_data()=0;
//  virtual void read_parameters(std::map<std::string,std::string> &Parameters)=0;
//  virtual void write_parameters(std::map<std::string,std::string> &Parameters)=0;
//  virtual bool use_dots()=0;

//  void copy_input_to_output();

protected:
  std::vector<std::shared_ptr<cv::Mat>> Vec_input_images;
  std::shared_ptr<cv::Mat> Image=nullptr;

  std::string Name;

  bool State[2];
  float Transparence=0.0f;
  _layer_positions_ns::_layer_type Layer_type;
  bool Inversion=false;

  QIcon *Icon=nullptr;
};

#endif
