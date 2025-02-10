//LIC

#ifndef GLWIDGET_XMAPSLAB_H
#define GLWIDGET_XMAPSLAB_H

#include <GL/glew.h>
#include <QOpenGLWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QImageReader>
#include <QGuiApplication>
#include <QDir>
#include <QFrame>
#include <QSplitter>
#include <QVBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QFileDialog>
#include <QRadioButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QGroupBox>
#include <QComboBox>
#include <QString>
#include <QTableWidget>

#include <iostream>
#include <fstream>
#include <random>

#include <opencv.hpp>

#include "shaders.h"
#include <vertex.h>

#include "color_bar_interpolation.h"
#include "color_bar_sections.h"
#include "image_IO.h"
//#include "file_dat.h"
//#include "file_elements_weight.h"
#include "table.h"
//#include <palette_data.h>

class _button_icon;
class _button_color_index;
class _table_layers;
class _w_color_bar;

namespace _gl_widget_xmapslab_ns
{
  const cv::Vec3b VEC_COLORS[3]={{255,0,0},{0,255,0},{0,0,255}};

  enum {VISIBILITY,WRITABILITY};

//  const _vertex3f COLORS[]={{0,0,0}, {1,0,0}, {0,1,0}, {0,0,1}, {0,1,1}, {1,0,1}, {1,1,0}, {1,1,1}, {0.5,0.5,0.5}};

//  const int DEFAULT_COLOR=0;
  const int DEFAULT_WINDOW_WIDTH=512;
  const int DEFAULT_WINDOW_HEIGHT=512;
  const unsigned char DEFAULT_TONE=240;

//  const int BLACK=0;
//  const int WHITE=7;

  typedef enum{ACTION_SELECTION,ACTION_CHANGE_CAMERA,ACTION_SELECTION_LINES_VP,ACTION_NOTHING,ACTION_LAST} _action_type;

  const unsigned int MAX_LAYERS=256;
  const unsigned int MAX_COLORS=255;

  const int WIDTH_TAB_CHARS=30;
}

class _table;
class _window;

class _gl_widget_xmapslab : public QOpenGLWidget
{
    Q_OBJECT
public:

   _gl_widget_xmapslab(_window_xmapslab *Window1);
  ~_gl_widget_xmapslab();

  void update_size_texture(int Width1, int Height1);

  void add_table_layer(QString Name1, int Row);

  void initialize_object();

  void load_shaders();

  void draw_objects();

  QLayout *gl_main_layout(){return Horizontal_layout;}

  void save_image(std::string File);

  void compute_position();

  GLuint set_texture(std::shared_ptr<cv::Mat> Image);
  void update_texture(GLuint Texture, std::shared_ptr<cv::Mat> Image);

  void get_composed_image(cv::Mat *Composed_image1);
  // this function is for obtaining an image form the composition of the layers
  void create_texture(cv::Mat *Composed_image1);

  void compose_colors(bool Compose_colors1){Compose_colors=Compose_colors1;}
  bool compose_colors(){return Compose_colors;}

  void activate_image_section(bool Activate_image_section1){Activate_image_section=Activate_image_section1;}

  void get_image_section(int &x1, int &y1, int &Width1, int &Height1);

protected:
  void resizeGL(int Width1, int Height1) override;
  void paintGL() override;
  void initializeGL() override;
  void mousePressEvent(QMouseEvent *Event) override;
  void mouseReleaseEvent(QMouseEvent *Event) override;
  void mouseDoubleClickEvent(QMouseEvent *Event) override;
  void mouseMoveEvent(QMouseEvent *Event) override;
  void wheelEvent(QWheelEvent *Event) override;
  void paintEvent(QPaintEvent *event) override;

  void create_palettes();

  void draw_box(QPainter& Painter);

private:
  _window_xmapslab *Window=nullptr;

//  bool Get_composed_image=false;
//  cv::Mat *Composed_image=nullptr;

  GLuint Program1=0;
  GLuint VAO1=0;
  GLuint VBO1_1=0;
  GLuint VBO1_2=0;

  GLuint Program2=0;
  GLuint VAO2=0;

  std::string Initial_image;

  int Window_width=0;
  int Window_height=0;

  float Scale_factor=1.0f;
  _vertex2f Translation=_vertex2f(0,0);

  int Initial_position_X=0;
  int Initial_position_Y=0;

  int Start_box_position_X=0;
  int Start_box_position_Y=0;
  int End_box_position_X=0;
  int End_box_position_Y=0;


  int Selection_position_X=0;
  int Selection_position_Y=0;

  bool Change_pos;
  bool Select_zone;
  bool Image_changed;

  int Draw_object;

  std::vector<_vertex3f> Vertices;
  std::vector<_vertex2f> Tex_coordinates;

  float Angle_camera_x=0;
  float Angle_camera_y=0;
  float Distance=0;

  int Mode;

  // float Scale_factor;

  float Mix_value;

  bool Change_camera;

  int Initial_position_x;
  int Initial_position_y;
  bool Change_position;

  QHBoxLayout *Horizontal_layout=nullptr;

  int Initial_width;
  int Initial_height;

  int Num_elements=-1;

  QIcon Icon_discrete;
  QIcon Icon_continuous;

  _w_color_bar *Color_bar_widget=nullptr;

  bool Compose_colors=false;
  // compose image
  std::shared_ptr<cv::Mat> Compose_image=nullptr;

  //
  bool Activate_image_section=false;

  // pixel ratio
  float Device_pixel_ratio=1.0f;
};

#endif
