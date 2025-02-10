//LIC

#ifndef GLWIDGET_GE
#define GLWIDGET_GE

#include <GL/glew.h>
#include <QOpenGLWidget>
//#include <QGLFormat>
#include <QMatrix4x4>
#include <opencv.hpp>
#include <math.h>
#include <string>
#include <map>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <memory>
#include <sys/timeb.h>
#include <QMessageBox>
#include <QPainter>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QString>
#include <QByteArray>
#include <QDir>
#include <QList>

//#include "window_xmapslab.h"
#include "nodes_editor_maps_tab.h"
#include "filters_tab.h"
#include "shaders.h"
#include "image_IO.h"
#include "map_list.h"

#include "nodes_editor.h"

#include "vertex.h"
#include "w_tab_xmapslab.h"

// filters
//#include "filter.h"
//#ifdef DEFINE_FILTER_ELEMENT
//#include "filter_element.h"
//#endif
//#ifdef DEFINE_FILTER_LOGIC_AND
//#include "filter_logic_and.h"
//#endif

class _window;

namespace _gl_widget_xmapslab_ge_ns
{
  typedef enum {TYPE_FILTER,INPUT_IMAGE_0,OUTPUT_IMAGE_0,INPUT_IMAGE_1} _info_filter;

  const int NUM_TABS=4;

  const std::string FILE_NAME_PAPER={"./papers/default.png"};

  typedef enum {RESOLUTION_300PPI,RESOLUTION_600PPI,RESOLUTION_1200PPI,LAST_RESOLUTION} _resolution;

  const int VEC_RESOLUTION[3]={300,600,1200};
  const int VEC_RESOLUTION_FACTOR[3]={1,2,4};

  const unsigned int MIN_DOT_SIZE=4;
  const unsigned int MAX_DOT_SIZE=8;
}

//HEA

class _gl_widget_xmapslab_ge : public QOpenGLWidget
{
Q_OBJECT

public:
  static int Counter_draw;


  _gl_widget_xmapslab_ge(_window_xmapslab *Window1,QWidget *Parent = nullptr);
  ~_gl_widget_xmapslab_ge() override;
  void  clear_data();

  void update_size_texture(int Width1,int Height1);
  void update_texture(std::string Name);
  void set_texture(std::string Name);

  // change tab
  void change_tab(int Index1);

  void load_shaders();
  void initialize_object();

  void save_image(string File);

protected:
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int width, int height) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mouseDoubleClickEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void wheelEvent(QWheelEvent *Event) override;

  void draw_objects();

private:
  _window_xmapslab *Window=nullptr;

  GLuint Program1;
  GLuint Texture1;
  GLuint VAO1;
  GLuint VBO1_1;
  GLuint VBO1_2;

  std::vector<QImage> Vec_images;

  std::vector<_vertex3f> Vertices;
  std::vector<_vertex2f> Tex_coordinates;

  float Window_width;
  float Window_height;

  float Scale_drawing_mode=1.0f;
  _vertex2f Translation=_vertex2f(0,0);

  // translation of the window
  bool Change_pos;
//  QTime Click_time;

  int Initial_position_X;
  int Initial_position_Y;

  _w_tab_xmapslab_ns::_tabs Selected_tab;
  int Selected_index; // the general index for mouse
  //
  int Max_texture_size;
  // parameters for filters
//  std::vector< map<std::string,std::string> > Filters_json_data;

  bool Shaders_loaded=false;

  // pixel ratio
  float Device_pixel_ratio=1.0f;
};


#endif
