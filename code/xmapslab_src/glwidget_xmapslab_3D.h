/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef GLWIDGET_3D_H
#define GLWIDGET_3D_H

#include <GL/glew.h>
#include <QOpenGLWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QImageReader>
#include <QGuiApplication>
#include <QDir>
#include <iostream>
#include <fstream>
#include <random>

#include <opencv.hpp>

#include "shaders.h"
#include "vertex.h"

#include "board.h"
#include "bounding_box.h"
#include "cube.h"
#include "board_cubes.h"

class _material {
public:
  _vertex3f Ambient;
  _vertex3f Diffuse;
  _vertex3f Specular;
  float Specular_exponent;
};

class _light {
public:
  _vertex4f Position;
  _vertex3f Color;
};

namespace _gl_widget_xmapslab_3D_ns {

  const _vertex3f COLORS[]={{0,0,0},{1,0,0},{0,1,0},{0,0,1},{0,1,1},{1,0,1},{1,1,0},{1,1,1}};

  enum class _mode_rendering:unsigned char{MODE_POINT,MODE_LINE,MODE_FILL};
  enum class _mode_color:unsigned char{MODE_COLOR_FIXED, MODE_COLOR_INTERPOLATE};
  enum class _mode_shading:unsigned char{MODE_SHADING_FLAT,MODE_SHADING_GOURAUD,MODE_SHADING_PHONG};
  typedef enum {PERSPECTIVE_PROJECTION,PARALLEL_PROJECTION} _projection_type;

  const int DEFAULT_COLOR=0;

  const float X_MIN=-10;
  const float X_MAX=10;
  const float Y_MIN=-10;
  const float Y_MAX=10;
  const float FRONT_PLANE_PARALLEL=-5000;
  const float BACK_PLANE_PARALLEL=5000;
  const float FRONT_PLANE_PERSPECTIVE=(X_MAX-X_MIN)/2;
  const float BACK_PLANE_PERSPECTIVE=5000;

  const float MAX_AXIS_SIZE=5000;
  const float DEFAULT_DISTANCE=2000; //2000
  const float ANGLE_STEP_KEY=1;
  const float ANGLE_STEP_MOUSE=.05;
  const float DISTANCE_STEP=DEFAULT_DISTANCE/20;
  const float DISTANCE_FACTOR=1.1;
  const float DEFAULT_SCALE_FACTOR=10;
  const float SCALE_STEP=DEFAULT_SCALE_FACTOR/10;

  const int DEFAULT_WINDOW_WIDTH=512;
  const int DEFAULT_WINDOW_HEIGHT=512;
  const unsigned char DEFAULT_TONE=240;

  const int COLOR_POINT=0;
  const int COLOR_LINE=1;
  const int COLOR_FILL=3;
}

class _window_xmapslab;

class _gl_widget_xmapslab_3D : public QOpenGLWidget
{
    Q_OBJECT
public:
   _gl_widget_xmapslab_3D(_window_xmapslab *Window1);
  ~_gl_widget_xmapslab_3D(){};

  void initialize_axis_data(std::vector<_vertex3f> &Axis_vertices, std::vector<_vertex3f> &Axis_colors);
  void initialize_triangle_data(std::vector<_vertex3f> &Triangle_vertices, std::vector<_vertex3f> &Triangle_colors,std::vector<_vertex3f> &Triangle_normals,std::vector<_vertex3f> &Triangle_vertices_normals);
//  void initialize_objects();

  void draw_objects();

  GLuint set_texture(std::shared_ptr<cv::Mat> Image);

  void create_object(float Width, float Height, int Num_divisions, std::shared_ptr<cv::Mat> Image, std::shared_ptr<cv::Mat> Result_floats_image);
  void update_data(std::shared_ptr<cv::Mat> Image,std::shared_ptr<cv::Mat> Result_floats_image);

protected:
  void resizeGL(int Width1, int Height1) override;
  void paintGL() override;
  void initializeGL() override;
  void keyPressEvent(QKeyEvent *Keyevent) override;
  void mousePressEvent(QMouseEvent *Event) override;
  void mouseReleaseEvent(QMouseEvent *Event) override;
  void mouseDoubleClickEvent(QMouseEvent *Event) override;
  void mouseMoveEvent(QMouseEvent *Event) override;
  void wheelEvent(QWheelEvent *Event) override;

  bool load_file(const QString &fileName, QImage &Image);
//  GLuint set_image(QImage &Image1);

private:
  _window_xmapslab *Window;

  GLuint Program1;
  GLuint VAO1;
  GLuint VBO_vertices1;
  GLuint VBO_colors1;
  GLuint VBO_triangles_normals1;
  GLuint VBO_vertices_normals1;
//  GLuint VBO_texture_coordinates1;

  GLuint VBO_instances_positions1;
  GLuint VBO_instances_scaling1;
  GLuint VBO_instances_colors1;

//  GLuint VBO_vertices_tangents1;
//  GLuint VBO_vertices_bitangents1;

  GLuint Program2;
  GLuint VAO2;
  GLuint VBO_vertices_wire1;

  GLuint Program3;

  GLuint Texture=0;

  std::vector<GLuint> Vec_textures;

  float Angle_camera_x;
  float Angle_camera_y;
  float Distance;

  float Angle_light_x;
  float Angle_light_y;
  float Angle_light_z;

  int Window_width;
  int Window_height;

  int Axis_vertices_size;
  int Sphere_vertices_size;

  bool Draw_points=false;
  bool Draw_lines=false;
  bool Draw_fill=true;

  _gl_widget_xmapslab_3D_ns::_mode_rendering Mode_rendering;
  _gl_widget_xmapslab_3D_ns::_mode_color Mode_color;
  _gl_widget_xmapslab_3D_ns::_mode_shading Mode_shading;

  _material Sphere_material;

  _light Light;

  _vertex3f Ambient_coeff;

  _gl_widget_xmapslab_3D_ns::_projection_type Projection_type=_gl_widget_xmapslab_3D_ns::_projection_type::PERSPECTIVE_PROJECTION;

  float Scale_factor;

  bool Illumination_active=false;

  bool Texture_active=true;
  bool No_texture=false;

  float Mix_value;

  bool Change_camera;

  int Initial_position_x;
  int Initial_position_y;
  bool Change_position;

  std::shared_ptr<_board> Board=nullptr;
  _bounding_box Bounding_box;

  std::shared_ptr<_cube> Cube=nullptr;
//  int Num_cubes=0;

  std::shared_ptr<_board_cubes> Board_cubes=nullptr;
};

#endif
