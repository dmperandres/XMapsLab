/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef FILTER_WCVD_H
#define FILTER_WCVD_H

#include <GL/glew.h>
#include <QDialog>
#include <QGroupBox>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>
#include <QSpinBox>
#include <QComboBox>
#include <QProgressDialog>
#include <QCoreApplication>
#include <string>

#include "shaders.h"
#include "line_edit.h"
#include "filter.h"
#include "vertex.h"
#include "random.h"
#include "shaders.h"

namespace _f_wcvd_ns
{
  // Defines for controling the drawing of the if the WCVD
  #define WCVD_DRAWING
  //#define WCVD_FIRST_TIME

  typedef enum {SELECTOR_TYPE_PERCENTAGE,SELECTOR_TYPE_NUMBER} _selector_type;

  // Number of dots
  // parameter 1
  const std::string String_group_box_parameter1("Percent of dots");
  const std::string String_label_parameter1_min("0%");
  const std::string String_label_parameter1_max("100% ");
  const std::string String_label_parameter1_tooltip("Display the percentage of dots that will be computed");
  const int Parameter1_min_value=0;
  const int Parameter1_max_value=100;
  const int Parameter1_single_step=1;
  const int Parameter1_page_step=5;
  const int Parameter1_tick_interval=5;
  const bool Parameter1_set_tracking=false;
  const std::string String_parameter1_tooltip("Controls the number of dots to be computed");

  // Number of dots
  // parameter 2
  const std::string String_group_box_parameter2("Number of dots");
  const std::string String_parameter2_tooltip("Controls the number of dots to be computed");

  // modulate dot size
  // parameter 3
  const std::string String_group_box_parameter3("Save intermediate results");
  const std::string String_checkbox_parameter3("Save");
  const std::string String_parameter3_tooltip("Controls if the intermediate results are saved");

  // Stop condition % of moving centroidals
  // parameter 4
  const std::string String_group_box_parameter4("Stop condition (movement)");
  const std::string String_label_parameter4_min("0%  ");
  const std::string String_label_parameter4_max("100%");
  const std::string String_label_parameter4_tooltip("Display the percentage of dots that must be in fixed positions to stop the computation");
  const int Parameter4_min_value=0;
  const int Parameter4_max_value=100;
  const int Parameter4_single_step=3;
  const int Parameter4_page_step=5;
  const int Parameter4_tick_interval=5;
  const bool Parameter4_set_tracking=false;
  const std::string String_parameter4_tooltip("Controls the number of dots that must be in fixed positions to stop the computation");

  // Stop condition Number of iterations
  // parameter 5
  const std::string String_group_box_parameter5("Stop condition (iterations)");
  const std::string String_parameter5_tooltip("Controls the number of iterations to stop the computation");

  // parameter 6
  const std::string String_group_box_parameter6("Selector");
  const std::string String_combo_parameter6("Selector");
  const std::string String_parameter6_tooltip("This value allows to change the type of selector");

  // Default values
  const float WCVD_NUMBER_OF_DARK_DOTS_DEFAULT=1000;
  const float WCVD_NUMBER_OF_DOTS_DEFAULT=100;
  const unsigned int WCVD_PERCENT_OF_DOTS_DEFAULT=25;
  const bool WCWD_SAVE_INTERMEDIATE_IMAGES_DEFAULT=false;
  //const float WCVD_MIN_NUMBER_OF_DOTS_DEFAULT=1;
  const int WCVD_PERCENT_FIXED_CENTROIDALS=99;
  const int WCVD_NUM_ITERACTIONS_DEFAULT=1000;

  const float DOTS_FACTOR=0.75f;//0.125;
  //const float DOTS_UNMOVED_FACTOR=0.01f; // 1%
  const float MIN_DOTS_DISTANCE=1.0f; // 1 pixel

  const unsigned int Num_renderbuffers=2;

  const int Front_plane=-100;
  const int Back_plane=100;
  const int Apex_height=60;
  const int Point_height=80;

  const _vertex3uc Vec_colors[]={{255,0,0},{0,255,0},{0,0,255},{0,255,255},{255,0,255},{255,255,0}};
  const int MAX_COLORS=5;

  class _pixel
  {
  public:
    unsigned char Red;
    unsigned char Green;
    unsigned char Blue;
  };

  #ifdef WINDOWS
  const double M_PI=3.1415926535897932;
  #endif

  const char FILE_NAME[]="aux_code/wcvd/wcvd_%02d.png";
}

class _gl_widget;
class _qtw_filter_wcvd;

/*************************************************************************/

class _filter_wcvd : public _filter
{
public:
  _filter_wcvd();
  bool use_dots(){return Use_dots;}
  void reset_data();

  void hsv_to_rbg(float h,float s, float v,unsigned char &r,unsigned char &g,unsigned char &b);
  void create_cone(vector<_vertex3f> &Vertices);
  void create_colors(vector<_vertex3uc> &Colors, vector<_vertex3uc> &False_colors);

  void count_dark_pixels(cv::Mat *Input_image);
  void create_random_points(cv::Mat *Input_image);
  void draw_points(cv::Mat *Output_image);

  void wcvd(cv::Mat *Input_image0,cv::Mat *Output_image0);
  void update_filter();
  void update();

  void percent_of_dots(int Percent_of_dots1);
  int percent_of_dots(){return Percent_of_dots;}

  void save_intermediate_images(bool Value){Save_intermediate_images=Value;}
  bool save_intermediate_images(){return Save_intermediate_images;}

  void number_of_dots(int Number_of_dots1);
  int number_of_dots(){return Number_of_good_dots;}

  void percent_fixed_centroidals(int Percent_fixed_centroidals1){Percent_fixed_centroidals=Percent_fixed_centroidals1;}
  int  percent_fixed_centroidals(){return Percent_fixed_centroidals;}

  void number_of_iteractions(int Number_of_iteractions1){Number_of_iteractions=Number_of_iteractions1;}
  int  number_of_iteractions(){return Number_of_iteractions;}

  void save_wcvd_image_to_file(std::string File_name);
  void save_wcvd_image();

  void selector_type(int Selector_type1){Selector_type=_f_wcvd_ns::_selector_type(Selector_type1);}
  int selector_type(){return int(Selector_type);}

  virtual void update_percent_of_dots(){}
  virtual void update_number_of_dots(){}

  void save_GL_state();
  void restore_GL_state();

protected:
  _gl_widget *GL_widget;

  _shaders Shader;
  GLuint Color_texture;
  GLuint Depth_texture;
  GLuint Image_texture;

  GLuint FBO;
  GLuint Program1;
  GLuint Program2;
  GLuint Program3;
  GLuint Program4;

  GLuint VAO1a;

  GLuint VBO1a;
  GLuint VBO2a;
  GLuint VBO3a;

  GLuint Buffer_offsets[2];
  GLuint Buffer_movement;

  GLuint *Map;
  GLuint *Map_offsets;

  GLint Counter_movements;

  int Number_of_dark_dots;
  int Number_of_dots;
  int Number_of_good_dots;
  int Percent_of_dots;

  vector<_vertex3ui> Offsets;

  vector<_vertex3uc> Colors;
  vector<_vertex3uc> False_colors;
  vector<_vertex3f> Vertices_cone;

  vector<_vertex2i> Points;

  // for drawing
  int Window_width;
  int Window_height;

  int Num_divisions;
  int Num_vertices;
  int Num_faces;
  int Radius;
  int Height;
  int Moved_points;
  int Percent_fixed_centroidals;
  int Number_of_iteractions;

  bool Local_change;
  bool Dark_points_counted;

  _random_uniform_double C1;

  cv::Mat Aux_image;
  cv::Mat Aux_image1;
  cv::Mat Image_orig;

  bool Save_intermediate_images;

  _f_wcvd_ns::_selector_type Selector_type;
};

/*************************************************************************/

class _filter_wcvd_ui :public _filter_wcvd
{
public:
  _filter_wcvd_ui(_gl_widget *GL_widget1,std::string Box_name="WCVD parameters");
  _filter_wcvd_ui(_gl_widget *GL_widget1,std::map<std::string,std::string> &Parameters,std::string Box_name="WCVD parameters");
  ~_filter_wcvd_ui();
  void reset_data();

  void show();
  void hide();
  void *get_link();
  void read_parameters(std::map<std::string,std::string> &Parameters);
  void write_parameters(std::map<std::string,std::string> &Parameters);

  void parameter1(int Value){percent_of_dots(Value);}
  int parameter1(){return percent_of_dots();}

  void parameter2(int Value){number_of_dots(Value);}
  int parameter2(){return number_of_dots();}

  void parameter3(bool Value){save_intermediate_images(Value);}
  bool parameter3(){return save_intermediate_images();}

  void parameter4(int Value){percent_fixed_centroidals(Value);}
  int parameter4(){return percent_fixed_centroidals();}

  void parameter5(int Value){number_of_iteractions(Value);}
  int parameter5(){return number_of_iteractions();}

  void parameter6(int Value){selector_type(Value);}
  int parameter6(){return selector_type();}

  void local_change(bool Value){Local_change=Value;}

  void update_percent_of_dots();
  void update_number_of_dots();

  private:
  _qtw_filter_wcvd *Qtw_filter_wcvd;
};

/*************************************************************************/

class _qtw_filter_wcvd: public QWidget
{
  Q_OBJECT
public:

  _qtw_filter_wcvd(_gl_widget *GL_widget1,_filter_wcvd_ui *Filter1,std::string Box_name="WCVD parameters");
  void show(){Group_box_main->show();}
  void hide(){Group_box_main->hide();}
  QGroupBox *get_link(){return Group_box_main;}

  void parameter1(int Value);
  void parameter2(int Value);
  void parameter3(bool Value);
  void parameter4(int Value);
  void parameter5(int Value);
  void parameter6(int Value);

protected slots:
  void parameter1_slot(int Value);
  void parameter2_slot(int Value);
  void parameter3_slot(int Value);
  void parameter4_slot(int Value);
  void parameter5_slot(int Value);
  void parameter6_slot(int Value);

private:
  QGroupBox *Group_box_main;
  QGroupBox *Group_box_parameter1;  
  QGroupBox *Group_box_parameter2;
  QGroupBox *Group_box_parameter3;
  QGroupBox *Group_box_parameter4;
  QGroupBox *Group_box_parameter5;
  QGroupBox *Group_box_parameter6;

  // Percent of dots
  QSlider *Slider_parameter1;
  QLineEdit *Line_edit_parameter1;

  // Number of dots
  QSpinBox *Spinbox_parameter2;

  // save wcvd images
  QCheckBox *Checkbox_parameter3;

  // Percent of fixed centroidals
  QSlider *Slider_parameter4;
  QLineEdit *Line_edit_parameter4;

  // number of iteractions
  QSpinBox *Spinbox_parameter5;

  // selector type
  QComboBox *Combo_parameter6;

  _filter_wcvd_ui *Filter;
  _gl_widget *GL_widget;
};
#endif
