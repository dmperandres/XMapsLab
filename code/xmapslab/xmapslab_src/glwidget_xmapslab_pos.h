
#ifndef GLWIDGET_POS
#define GLWIDGET_POS

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

#include "image_IO.h"

namespace _gl_widget_pos_ns
{
  const cv::Vec3b VEC_COLORS[3]={{255,0,0},
{0,255},
{0,0,255}};

  enum {VISIBILITY,WRITABILITY};

  const _vertex3f COLORS[]={{0,0,0},
{1,0,0},
{0,1,0},
{0,0,1},
{0,1,1},
{1,0,1},
{1,1,0},
{1,1,1},
{0.5,0.5,0.5}};

  const int DEFAULT_COLOR=0;
  const int DEFAULT_WINDOW_WIDTH=512;
  const int DEFAULT_WINDOW_HEIGHT=512;
  const unsigned char DEFAULT_TONE=240;

  const int BLACK=0;
  const int WHITE=7;

  typedef enum{ACTION_SELECTION,ACTION_CHANGE_CAMERA,ACTION_SELECTION_LINES_VP,ACTION_NOTHING,ACTION_LAST} _action_type;

  const unsigned int MAX_LAYERS=256;
  const unsigned int MAX_COLORS=255;

  const int WIDTH_TAB_CHARS=30;
}

class _table;
class _window;

class _gl_widget_pos : public QOpenGLWidget
{
    Q_OBJECT
public:

   _gl_widget_pos(_window *Window1,int Position);
  ~_gl_widget_pos();

  void refresh_texture(int Width1, int Height1);

  void initialize_object();

  void load_shaders();

  void draw_objects();

  QLayout *gl_main_layout(){return Horizontal_layout;}

  GLuint set_texture(shared_ptr<cv::Mat> Image);
  void update_texture(int Position);

  void translation(int x,int y){Translation.x=x;Translation.y=y;}
  _vertex2i translation(){return _vertex2i(Translation.x,Translation.y);}

  float scale(){return Scale_factor;}

  void compute_position(QMouseEvent *Event);

  void save_image(string File);

  void update_texture(string Name);

protected:
  void resizeGL(int Width1, int Height1) override;
  void paintGL() override;
  void initializeGL() override;
  void mousePressEvent(QMouseEvent *Event) override;
  void mouseReleaseEvent(QMouseEvent *Event) override;
  void mouseMoveEvent(QMouseEvent *Event) override;
  void wheelEvent(QWheelEvent *Event) override;
  void paintEvent(QPaintEvent *event) override;

private:
  _window *Window=nullptr;
  int Position=0;

  GLuint Program1;
  GLuint VAO1;
  GLuint VBO1_1;
  GLuint VBO1_2;

  string Initial_image;

  int Window_width;
  int Window_height;

  float Scale_drawing_mode;
  _vertex3f Translation;

//  int Drawing_image;

  int Initial_position_X;
  int Initial_position_Y;

  int Selection_position_X;
  int Selection_position_Y;

  bool Change_pos;
  bool Image_changed;

  int Draw_object;

  std::vector<_vertex3f> Vertices;
  std::vector<_vertex2f> Tex_coordinates;

  float Angle_camera_x;
  float Angle_camera_y;
  float Distance;

  float Angle_light_x;
  float Angle_light_y;

  int Axis_vertices_size;
  int Sphere_vertices_size;

  bool Draw_point;
  bool Draw_line;
  bool Draw_fill;

  int Mode;

  float Scale_factor;

  int Initial_position_x;
  int Initial_position_y;
  bool Change_position;

  bool Insert=false;
  QHBoxLayout *Horizontal_layout=nullptr;

  int Initial_width;
  int Initial_height;

  int Num_elements=-1;

  bool Selection_add=true;
};

#endif
