//LIC

#include "glwidget_xmapslab_3D.h"
#include "window_xmapslab.h"

using namespace _gl_widget_xmapslab_3D_ns;

//HEA

_gl_widget_xmapslab_3D::_gl_widget_xmapslab_3D(_window_xmapslab *Window1):Window(Window1)
{
  setMinimumSize(300, 300);
  setFocusPolicy(Qt::StrongFocus);

  Draw_points=false;
  Draw_lines=true;
  Draw_fill=true;
  Mode_shading=_gl_widget_xmapslab_3D_ns::_mode_shading::MODE_SHADING_PHONG;
  Mode_color=_gl_widget_xmapslab_3D_ns::_mode_color::MODE_COLOR_FIXED;
  Illumination_active=true;
  Texture_active=false;

  Angle_camera_x=45;
  Angle_camera_y=0;
  Distance=DEFAULT_DISTANCE;

  Scale_factor=DEFAULT_SCALE_FACTOR;

  Sphere_material.Ambient=_vertex3f(0,0,.1);
  Sphere_material.Diffuse=_vertex3f(0,0,0.8);
//  Sphere_material.Specular=_vertex3f(0.5,0.3,0.0);
  Sphere_material.Specular=_vertex3f(0,0,0.1);
  Sphere_material.Specular_exponent=5;

  Light.Position=_vertex4f(0,0,1,0);
  Light.Color=_vertex3f(1,1,1);

  Ambient_coeff=_vertex3f(0.1,0.1,0.1);

  Vec_textures.resize(8);

  Mix_value=0;

  Change_camera=true;

  Angle_light_x=0;
  Angle_light_y=0;
  Angle_light_z=0;
}

//HEA

//bool _gl_widget_xmapslab_3D::load_file(const QString &fileName,QImage &Image)
//{
//  QImageReader Reader(fileName);
//  Reader.setAutoTransform(true);
//  Image = Reader.read();
//  if (Image.isNull()) {
//      QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
//                               tr("Cannot load %1.").arg(QDir::toNativeSeparators(fileName)));
//      return false;
//  }
//  Image=Image.mirrored();
//  Image=Image.convertToFormat(QImage::Format_RGB888);
//  return true;
//}

//HEA

void _gl_widget_xmapslab_3D::keyPressEvent(QKeyEvent *Keyevent)
{
  switch(Keyevent->key()){
  case Qt::Key_P:Draw_points=!Draw_points;break;
  case Qt::Key_L:Draw_lines=!Draw_lines;break;
  case Qt::Key_F:Draw_fill=!Draw_fill;break;
  //
  case Qt::Key_I:Illumination_active=!Illumination_active;break;
  case Qt::Key_T:Texture_active=!Texture_active;break;
  //
  case Qt::Key_1:Mode_shading=_gl_widget_xmapslab_3D_ns::_mode_shading::MODE_SHADING_FLAT;break;
  case Qt::Key_2:Mode_shading=_gl_widget_xmapslab_3D_ns::_mode_shading::MODE_SHADING_GOURAUD;break;
  case Qt::Key_3:Mode_shading=_gl_widget_xmapslab_3D_ns::_mode_shading::MODE_SHADING_PHONG;break;

  case Qt::Key_C:
      if (Mode_color==_gl_widget_xmapslab_3D_ns::_mode_color::MODE_COLOR_FIXED) Mode_color=_gl_widget_xmapslab_3D_ns::_mode_color::MODE_COLOR_INTERPOLATE;
      else Mode_color=_gl_widget_xmapslab_3D_ns::_mode_color::MODE_COLOR_FIXED;
      break;
  //
  case Qt::Key_Left:
//    if (Change_camera==true) Angle_camera_y-=ANGLE_STEP_KEY;
//    else Angle_light_y+=ANGLE_STEP_KEY;
    if (Change_camera==true) Angle_camera_y-=ANGLE_STEP_KEY;
    else Angle_light_z+=ANGLE_STEP_KEY;
    break;
  case Qt::Key_Right:
//    if (Change_camera==true) Angle_camera_y+=ANGLE_STEP_KEY;
//    else Angle_light_y-=ANGLE_STEP_KEY;
    if (Change_camera==true) Angle_camera_y+=ANGLE_STEP_KEY;
    else Angle_light_z-=ANGLE_STEP_KEY;
    break;
  case Qt::Key_Up:
    if (Change_camera==true) Angle_camera_x-=ANGLE_STEP_KEY;
//    else Angle_light_x+=ANGLE_STEP_KEY;
    break;
  case Qt::Key_Down:
    if (Change_camera==true) Angle_camera_x+=ANGLE_STEP_KEY;
//    else Angle_light_x-=ANGLE_STEP_KEY;
    break;
  case Qt::Key_PageUp:
    if (Projection_type==PERSPECTIVE_PROJECTION) Distance*=DISTANCE_FACTOR;
    else Scale_factor*=DISTANCE_FACTOR;
    break;
  case Qt::Key_PageDown:
    if (Projection_type==PERSPECTIVE_PROJECTION) Distance/=DISTANCE_FACTOR;
    else Scale_factor/=DISTANCE_FACTOR;
    break;
  //
  case Qt::Key_M:
    if (Projection_type==PERSPECTIVE_PROJECTION) Projection_type=PARALLEL_PROJECTION;
    else Projection_type=PERSPECTIVE_PROJECTION;
    break;
  //
  case Qt::Key_Plus:
    Mix_value+=0.1;
    if (Mix_value>1) Mix_value=1;
    break;
  case Qt::Key_Minus:
    Mix_value-=0.1;
    if (Mix_value<0) Mix_value=0;
    break;
  //
  case Qt::Key_F1:Change_camera=!Change_camera;break;
  }

  update();
}

//HEA

void _gl_widget_xmapslab_3D::mousePressEvent(QMouseEvent *Event)
{
  if (Event->buttons() & Qt::LeftButton) {
    Change_position=true;
    Initial_position_x=Event->x();
    Initial_position_y=Event->y();
  }
}

//HEA

void _gl_widget_xmapslab_3D::mouseReleaseEvent(QMouseEvent *Event)
{
  Q_UNUSED(Event)
  Change_position=false;
}

//HEA

void _gl_widget_xmapslab_3D::mouseDoubleClickEvent(QMouseEvent *Event)
{
  if (Event->buttons() & Qt::LeftButton) {
    if (Change_camera==true){
      Angle_camera_x=0;
      Angle_camera_y=0;
    }
    else{
      Angle_light_x=0;
      Angle_light_y=0;
      Angle_light_z=0;
    }
  }

  if (Event->buttons() & Qt::RightButton) {
    Distance=DEFAULT_DISTANCE;
  }

  update();
}

//HEA

void _gl_widget_xmapslab_3D::mouseMoveEvent(QMouseEvent *Event)
{
  int Last_position_x=Event->x();
  int Last_position_y=Event->y();

//  cout << Initial_position_x << " " << Last_position_x << endl;
  if (Change_position==true){
    if (Event->buttons() & Qt::LeftButton) {
      if (Change_camera==true){
        Angle_camera_y+=float(Last_position_x-Initial_position_x)*ANGLE_STEP_MOUSE;
        Angle_camera_x+=float(Last_position_y-Initial_position_y)*ANGLE_STEP_MOUSE;
      }
      else{
//        Angle_light_y-=float(Last_position_x-Initial_position_x)*ANGLE_STEP_MOUSE;
//        Angle_light_x-=float(Last_position_y-Initial_position_y)*ANGLE_STEP_MOUSE;
        Angle_light_z-=float(Last_position_x-Initial_position_x)*ANGLE_STEP_MOUSE;
      }
    }
  }

  Initial_position_x=Last_position_x;
  Initial_position_y=Last_position_y;

  update();
}

//HEA

void _gl_widget_xmapslab_3D::wheelEvent(QWheelEvent *Event)
{
  QPoint Num_degrees = Event->angleDelta();
  int Step = Num_degrees.y();

//  int Step=Event->delta()/120;

  if (Step<0){
    if (Projection_type==PERSPECTIVE_PROJECTION) Distance/=DISTANCE_FACTOR;
    else Scale_factor/=DISTANCE_FACTOR;
  }
  else{
    if (Projection_type==PERSPECTIVE_PROJECTION) Distance*=DISTANCE_FACTOR;
    else Scale_factor*=DISTANCE_FACTOR;
  }

  update();
}

//HEA

//void _gl_widget_xmapslab_3D::draw_objects()
//{
//  QMatrix4x4 Modelviewprojection;
//  QMatrix4x4 Camera_matrix;
//  QMatrix4x4 Light_matrix;

//  float Aspect=(float)Window_height/(float)Window_width;

//  if (Projection_type==PERSPECTIVE_PROJECTION){
//    Modelviewprojection.frustum(X_MIN,X_MAX,Y_MIN*Aspect,Y_MAX*Aspect,FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);
//  }
//  else{
//    Modelviewprojection.ortho(X_MIN*Scale_factor,X_MAX*Scale_factor,Y_MIN*Aspect*Scale_factor,Y_MAX*Aspect*Scale_factor,FRONT_PLANE_PARALLEL,BACK_PLANE_PARALLEL);
//  }

//  Modelviewprojection.translate(0,0,-Distance);
//  Modelviewprojection.rotate(Angle_camera_x,1,0,0);
//  Modelviewprojection.rotate(Angle_camera_y,0,1,0);

//  // camera position
//  Camera_matrix.rotate(-Angle_camera_y,0,1,0);
//  Camera_matrix.rotate(-Angle_camera_x,1,0,0);
//  QVector3D Camera_position=(QVector3D)(Camera_matrix*QVector4D(0,0,Distance,1));
//  // light position
////  Light_matrix.rotate(-Angle_light_y,0,1,0);
////  Light_matrix.rotate(-Angle_light_x,1,0,0);

//  Light_matrix.rotate(Angle_light_z,0,0,1);
//  QVector4D Light_position=Light_matrix*QVector4D(0,1,0,0);

//  cout << "Ligh x=" << Light_position.x() << " y=" << Light_position.y() << " z=" << Light_position.z() << " w=" << Light_position.w() << endl;

//  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

//  glUseProgram(Program1);
//  glBindVertexArray(VAO1);

//  glUniformMatrix4fv(10,1,GL_FALSE,Modelviewprojection.data());


////  // axis
////  glUniform1i(20,int(_gl_widget_xmapslab_3D_ns::_mode_color::MODE_INTERPOLATE_COLORS));// interpolation
////  glUniform1i(22,int(false)); // no illumination
////  glUniform1i(23,int(false)); // no texture

////  glDrawArrays(GL_LINES,0,Axis_vertices_size);

//  if (Draw_points){
//    glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
//    glPointSize(3);
//    glUniform1i(20,int(_gl_widget_xmapslab_3D_ns::_mode_color::MODE_SOLID));// interpolation
//    glUniform1i(22,int(false)); // no illumination
//    glUniform1i(23,int(false)); // no texture
//    glUniform3fv(21,1,(GLfloat*) &COLORS[COLOR_POINT]);
//    // sphere
//    glDrawArrays(GL_TRIANGLES,0,Board.Vertices_drawarray.size());
//  }

//  if (Draw_lines){
//    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
//    glPolygonOffset(-1,1);
//    glUniform1i(20,int(_gl_widget_xmapslab_3D_ns::_mode_color::MODE_SOLID));// interpolation
//    glUniform1i(22,int(false)); // no illumination
//    glUniform1i(23,int(false)); // no texture
//    glUniform3fv(21,1,(GLfloat*) &COLORS[COLOR_LINE]);
//    // sphere
//    glDrawArrays(GL_TRIANGLES,0,Board.Vertices_drawarray.size());
//  }

//  if (Draw_fill){
//    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
//    glUniform1i(20,Mode);
//    glUniform1i(22,int(Illumination_active));
//    glUniform1i(23,int(Texture_active));
//    glUniform1f(24,Mix_value);
//    glUniform3fv(21,1,(GLfloat*) &COLORS[COLOR_FILL]);
//    glUniform3fv(15,1,(GLfloat*) &Camera_position);
//    glUniform4fv(30,1,(GLfloat*) &Light_position);
//    glUniform3fv(31,1,(GLfloat*) &Light.Color);
//    glUniform3fv(35,1,(GLfloat*) &Ambient_coeff);

//    // sphere
////    glActiveTexture(GL_TEXTURE0);
////    glBindTexture(GL_TEXTURE_2D,Vec_textures[0]);
//    glBindTextureUnit(0,Texture);


////    glActiveTexture(GL_TEXTURE1);
////    glBindTexture(GL_TEXTURE_2D,Vec_textures[1]);

//    glUniform3fv(40,1,(GLfloat*) &Sphere_material.Ambient);
//    glUniform3fv(41,1,(GLfloat*) &Sphere_material.Diffuse);
//    glUniform3fv(42,1,(GLfloat*) &Sphere_material.Specular);
//    glUniform1f(43,Sphere_material.Specular_exponent);
//    glDrawArrays(GL_TRIANGLES,0,Board.Vertices_drawarray.size());
//  }

//  glUseProgram(0);
//  glBindVertexArray(0);
//}

//HEA


void _gl_widget_xmapslab_3D::draw_objects()
{
  if (Cube!=nullptr){
    makeCurrent();

    QMatrix4x4 Modelview;
    QMatrix4x4 Projection;
    QMatrix4x4 Modelview_normals;
    QMatrix4x4 Camera;
    QMatrix4x4 Light_matrix;


    float Aspect=(float)Window_height/(float)Window_width;

    if (Projection_type==PERSPECTIVE_PROJECTION){
      Projection.frustum(X_MIN,X_MAX,Y_MIN*Aspect,Y_MAX*Aspect,FRONT_PLANE_PERSPECTIVE,BACK_PLANE_PERSPECTIVE);
    }
    else{
      Projection.ortho(X_MIN*Scale_factor,X_MAX*Scale_factor,Y_MIN*Aspect*Scale_factor,Y_MAX*Aspect*Scale_factor,FRONT_PLANE_PARALLEL,BACK_PLANE_PARALLEL);
    }

    Modelview.translate(0,0,-Distance);
    Modelview.rotate(Angle_camera_x,1,0,0);
    Modelview.rotate(Angle_camera_y,0,1,0);

    Modelview_normals=Modelview;
    Modelview_normals.inverted();
    Modelview_normals.transposed();

    Camera.rotate(-Angle_camera_y,0,1,0);
    Camera.rotate(-Angle_camera_x,1,0,0);
    QVector3D Camera_position=(QVector3D)(Camera*QVector4D(0,0,Distance,1));

    Light_matrix.rotate(Angle_light_z,0,0,1);
    QVector4D Light_position=Light_matrix*QVector4D(0,1,0,0);

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(VAO1);

    glUseProgram(Program3);
    glUniformMatrix4fv(10,1,GL_FALSE,Modelview.data());
    glUniformMatrix4fv(11,1,GL_FALSE,Projection.data());
    glUniformMatrix4fv(12,1,GL_FALSE,Modelview_normals.data());


    // axis
  //  glUniform1i(20,(int)MODE_LINE);
  //  glUniform1i(21,(int)MODE_COLORS_VARIABLE);
  //  glUniform1i(23,(int)false); // no illumination
  //  glUniform1i(24,(int)false); // no texture

  //  glDrawArrays(GL_LINES,0,Axis.Vertices_drawarray.size());

    if (Draw_points){
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
      glPointSize(3);
      glUniform1i(20,int(_gl_widget_xmapslab_3D_ns::_mode_rendering::MODE_POINT));
  //    glUniform1i(21,int(_gl_widget_xmapslab_3D_ns::_mode_color::MODE_COLOR_FIXED));
      glUniform3fv(25,1,(GLfloat*) &COLORS[COLOR_POINT]);
      glDrawArraysInstanced(GL_TRIANGLES,0,Cube->Vertices_drawarray.size(),Board_cubes->num_cubes());
//      glDrawArrays(GL_TRIANGLES,0,Cube->Vertices_drawarray.size());
    }

    if (Draw_lines){
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      glPolygonOffset(-1,1);
      glUniform1i(20,int(_gl_widget_xmapslab_3D_ns::_mode_rendering::MODE_LINE));
  //    glUniform1i(21,int(_gl_widget_xmapslab_3D_ns::_mode_color::MODE_COLOR_FIXED));
      glUniform3fv(26,1,(GLfloat*) &COLORS[COLOR_LINE]);
      glDrawArraysInstanced(GL_TRIANGLES,0,Cube->Vertices_drawarray.size(),Board_cubes->num_cubes());
//      glDrawArrays(GL_TRIANGLES,0,Cube->Vertices_drawarray.size());
    }

    if (Draw_fill){
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glUniform1i(20,int(_gl_widget_xmapslab_3D_ns::_mode_rendering::MODE_FILL));
  //    glUniform1i(21,int(Mode_color));
      glUniform3fv(27,1,(GLfloat*) &COLORS[COLOR_FILL]);

      if (Illumination_active){
        glUniform1i(22,int(Mode_shading));
        glUniform1i(23,int(Illumination_active));
  //      glUniform4fv(30,1,(GLfloat*) &Light.Position);
        glUniform4fv(30,1,(GLfloat*) &Light_position);
        glUniform3fv(31,1,(GLfloat*) &Light.Color);
        glUniform3fv(32,1,(GLfloat*) &Camera_position);
        glUniform3fv(40,1,(GLfloat*) &Sphere_material.Ambient);
        glUniform3fv(41,1,(GLfloat*) &Sphere_material.Diffuse);
        glUniform3fv(42,1,(GLfloat*) &Sphere_material.Specular);
        glUniform1f(43,Sphere_material.Specular_exponent);
        glUniform3fv(44,1,(GLfloat*) &Ambient_coeff);
      }
      else{
        glUniform1i(23,(int)Illumination_active);
      }

//      if (No_texture==false && Texture_active){
//        glUniform1i(24,int(Texture_active));
//  //      glActiveTexture(GL_TEXTURE0);
//  //      glBindTexture(GL_TEXTURE_2D,Vec_textures[0]);
//        glBindTextureUnit(0,Texture);
//      }
//      else{
//        if (No_texture) glUniform1i(24,0); // no texture. There is not selected image
//        else glUniform1i(24,int(Texture_active));
//      }

      glDrawArraysInstanced(GL_TRIANGLES,0,Cube->Vertices_drawarray.size(),Board_cubes->num_cubes());
//      glDrawArrays(GL_TRIANGLES,0,Cube->Vertices_drawarray.size());

    }

    glUseProgram(0);
    glBindVertexArray(0);
  }
  else{
    glClear(GL_COLOR_BUFFER_BIT);
  }
}


//HEA

void _gl_widget_xmapslab_3D::paintGL()
{
  draw_objects();
}

//HEA

void _gl_widget_xmapslab_3D::resizeGL(int Width1, int Height1)
{
  Window_width=Width1;
  Window_height=Height1;

  glViewport(0,0,Width1,Height1);
}


//HEA

//void _gl_widget_xmapslab_3D::initialize_axis_data(vector<_vertex3f> &Axis_vertices,
//vector<_vertex3f> &Axis_colors)
//{
//   Axis_vertices.resize(6);
//   Axis_vertices[0]=_vertex3f(MAX_AXIS_SIZE,0,0); // x
//   Axis_vertices[1]=_vertex3f(-MAX_AXIS_SIZE,0,0);
//   Axis_vertices[2]=_vertex3f(0,MAX_AXIS_SIZE,0); // y
//   Axis_vertices[3]=_vertex3f(0,-MAX_AXIS_SIZE,0);
//   Axis_vertices[4]=_vertex3f(0,0,MAX_AXIS_SIZE); // z
//   Axis_vertices[5]=_vertex3f(0,0,-MAX_AXIS_SIZE);

//   Axis_colors.resize(6);
//   Axis_colors[0]=COLORS[1];// red
//   Axis_colors[1]=COLORS[1];
//   Axis_colors[2]=COLORS[2];// red
//   Axis_colors[3]=COLORS[2];
//   Axis_colors[4]=COLORS[3];// red
//   Axis_colors[5]=COLORS[3];
//}

//HEA

void _gl_widget_xmapslab_3D::create_object(float Width, float Height, int Num_divisions, shared_ptr<cv::Mat> Image, shared_ptr<cv::Mat> Result_floats_image)
{
  // axis
//  std::vector<_vertex3f> Axis_vertices;
//  std::vector<_vertex3f> Axis_colors;

//  initialize_axis_data(Axis_vertices,Axis_colors);

//  _sphere Sphere(50,50,50); ??

//  Axis_vertices_size=Axis_vertices.size();
//  Sphere_vertices_size=Sphere.Vertices_drawarray.size();??

  makeCurrent();

//  Board=make_shared<_board>();

//  Board->create(Width,Height,Num_divisions,COLORS[1],Results_floats_image);

  Cube=make_shared<_cube>();

  Board_cubes=make_shared<_board_cubes>();

  Board_cubes->create(Width,Height,Num_divisions,Image,Result_floats_image);

//  // compute the numer of row and columns, as well as the size of the base of the cube.
//  // The height depends on the layer data
//  int Num_vertical_divisions;
//  int Num_horizontal_divisions;

//  if (Width/Height>=1){
//    // Height is smaller
//    Num_vertical_divisions=Num_divisions;
//    float Height_quotient=Height/float(Num_divisions);
//    Num_horizontal_divisions=int(roundf(Width/Height_quotient));

//  }
//  else{
//    // Widht is smaller
//    Num_horizontal_divisions=Num_divisions;
//    float Width_quotient=Width/float(Num_divisions);
//    Num_vertical_divisions=int(roundf(Height/Width_quotient));
//  }

//  float Cube_width=Width/Num_horizontal_divisions;
//  float Cube_height=Height/Num_vertical_divisions;
//  float Cube_half_width=Cube_width/2;
//  float Cube_half_height=Cube_height/2;

//  Num_cubes=Num_horizontal_divisions*Num_vertical_divisions;

//  float Width_result=0;
//  float Height_result=0;
//  float Depth_result=0;

//  if (Result_floats_image!=nullptr){
//    Width_result=float(Result_floats_image->cols-1);
//    Height_result=float(Result_floats_image->rows-1);
//    if (Width_result>Height_result) Depth_result=Width_result/50;
//    else Depth_result=Height_result/50;
//  }

//  // compute the positions
//  std::vector<_vertex3f> Vec_positions;
//  std::vector<_vertex3f> Vec_scaling;
//  std::vector<_vertex3uc> Vec_colors;

//  Vec_positions.resize(Num_cubes);
//  Vec_scaling.resize(Num_cubes);
//  Vec_colors.resize(Num_cubes);

//  float Min_x=-Width/2;
//  float Min_y=-Height/2;
//  float s,t;
//  float Pos_x,Pos_y;
//  int Position=0;

//  float Value;

//  for (int Row=0;Row<Num_vertical_divisions;Row++){
//    s=float(Row)/float(Num_vertical_divisions);
//    Pos_y=roundf(s*float(Height-1)+Cube_half_height);
//    for (int Col=0;Col<Num_horizontal_divisions;Col++){
//      t=float(Col)/float(Num_horizontal_divisions);
//      Pos_x=roundf(t*float(Width-1)+Cube_half_width);
//      // positions
//      // plane Y=0;
////      Value=Width*t+Min_x+Cube_half_width;
////      Value=-(Height*s+Min_y+Cube_half_height);

//      Vec_positions[Position].x=Width*t+Min_x+Cube_half_width;
//      Vec_positions[Position].z=-(Height*s+Min_y+Cube_half_height);

//      // scaling
//      Vec_scaling[Position].x=Cube_width;

//      if (Result_floats_image!=nullptr){
//        Vec_scaling[Position].y=Result_floats_image->at<float>(int(Pos_y),int(Pos_x))*Depth_result;
//      }
//      else{
//        Vec_scaling[Position].y=Cube_width;
//      }

//      Vec_scaling[Position].z=Cube_height;

//      // colors
//      cv::Vec4b Vector;
//      if (Image!=nullptr){
//        Vector=Image->at<cv::Vec4b>(int(Pos_y),int(Pos_x));
//        Vec_colors[Position]=_vertex3uc(Vector[2],Vector[1],Vector[0]);
//      }

//      Position++;
//    }
//  }

//  Bounding_box.create(1000,1000,500);

//  //
//  _shaders Shader;

//  // basic
//  static const GLchar * P0_vs[]={
//  #include "shaders/basic3D.vert"
//  };

//  static const GLchar * P0_fs[]={
//  #include "shaders/basic3D.frag"
//  };

//  Program1=Shader.load_shaders(P0_vs,P0_fs);
//  if (Program1==0){
//    QMessageBox Message;
//    Message.setText("Error with the GPU program basic3D");
//    Message.exec();
//    exit(-1);
//  }

//  // wire
//  static const GLchar * P1_vs[]={
//  #include "shaders/basic3D_wire.vert"
//  };

//  static const GLchar * P1_fs[]={
//  #include "shaders/basic3D_wire.frag"
//  };

//  Program2=Shader.load_shaders(P1_vs,P1_fs);
//  if (Program2==0){
//    QMessageBox Message;
//    Message.setText("Error with the GPU program basic3D wire");
//    Message.exec();
//    exit(-1);
//  }

  glCreateVertexArrays(1,&VAO1);
  glBindVertexArray(VAO1);

  set_texture(Image);

  glCreateBuffers(1,&VBO_vertices1);
  glNamedBufferStorage(VBO_vertices1,(Cube->Vertices_drawarray.size())*3*sizeof(float),nullptr,GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
  glVertexArrayVertexBuffer(VAO1,0,VBO_vertices1,0,3*sizeof(float)); // 0,VBO
  glVertexArrayAttribFormat(VAO1,0,3,GL_FLOAT,GL_FALSE,0);
  glVertexArrayAttribBinding(VAO1,0,0);// 1,0)
  glEnableVertexArrayAttrib(VAO1,0);

  glCreateBuffers(1,&VBO_colors1);
  glNamedBufferStorage(VBO_colors1,(Cube->Vertices_drawarray.size())*3*sizeof(float),nullptr,GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
  glVertexArrayVertexBuffer(VAO1,1,VBO_colors1,0,3*sizeof(float)); // 1,VBO
  glVertexArrayAttribFormat(VAO1,1,3,GL_FLOAT,GL_FALSE,0);
  glVertexArrayAttribBinding(VAO1,1,1); //2,1)
  glEnableVertexArrayAttrib(VAO1,1);

  glCreateBuffers(1,&VBO_triangles_normals1);
  glNamedBufferStorage(VBO_triangles_normals1,(Cube->Vertices_drawarray.size())*3*sizeof(float),nullptr,GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
  glVertexArrayVertexBuffer(VAO1,2,VBO_triangles_normals1,0,3*sizeof(float)); // 1,VBO
  glVertexArrayAttribFormat(VAO1,2,3,GL_FLOAT,GL_FALSE,0);
  glVertexArrayAttribBinding(VAO1,2,2); //2,1)
  glEnableVertexArrayAttrib(VAO1,2);

  glCreateBuffers(1,&VBO_vertices_normals1);
  glNamedBufferStorage(VBO_vertices_normals1,(Cube->Vertices_drawarray.size())*3*sizeof(float),nullptr,GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
  glVertexArrayVertexBuffer(VAO1,3,VBO_vertices_normals1,0,3*sizeof(float)); // 1,VBO
  glVertexArrayAttribFormat(VAO1,3,3,GL_FLOAT,GL_FALSE,0);
  glVertexArrayAttribBinding(VAO1,3,3); //2,1)
  glEnableVertexArrayAttrib(VAO1,3);

//  glCreateBuffers(1,&VBO_texture_coordinates1);
//  glNamedBufferStorage(VBO_texture_coordinates1,(Cube->Vertices_drawarray.size())*2*sizeof(float),nullptr,GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
//  glVertexArrayVertexBuffer(VAO1,4,VBO_texture_coordinates1,0,2*sizeof(float)); // 1,VBO
//  glVertexArrayAttribFormat(VAO1,4,2,GL_FLOAT,GL_FALSE,0);
//  glVertexArrayAttribBinding(VAO1,4,4); //2,1)
//  glEnableVertexArrayAttrib(VAO1,4);

//  glCreateBuffers(1,&VBO_vertices_wire1);
//  glNamedBufferStorage(VBO_vertices_wire1,(Bounding_box.Vertices_drawarray.size())*3*sizeof(float),nullptr,GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
//  glVertexArrayVertexBuffer(VAO1,5,VBO_vertices_wire1,0,3*sizeof(float)); // 0,VBO
//  glVertexArrayAttribFormat(VAO1,5,3,GL_FLOAT,GL_FALSE,0);
//  glVertexArrayAttribBinding(VAO1,5,5);// 1,0)
//  glEnableVertexArrayAttrib(VAO1,5);


    glCreateBuffers(1,&VBO_instances_positions1);
    glNamedBufferStorage(VBO_instances_positions1,Board_cubes->num_cubes()*3*sizeof(float),nullptr,GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
    glVertexArrayVertexBuffer(VAO1,4,VBO_instances_positions1,0,3*sizeof(float)); // 1,VBO
    glVertexArrayAttribFormat(VAO1,4,3,GL_FLOAT,GL_FALSE,0);
    glVertexArrayAttribBinding(VAO1,4,4); //2,1)
    glEnableVertexArrayAttrib(VAO1,4);
    glVertexAttribDivisor(4,1);

    glCreateBuffers(1,&VBO_instances_scaling1);
    glNamedBufferStorage(VBO_instances_scaling1,Board_cubes->num_cubes()*3*sizeof(float),nullptr,GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
    glVertexArrayVertexBuffer(VAO1,5,VBO_instances_scaling1,0,3*sizeof(float)); // 1,VBO
    glVertexArrayAttribFormat(VAO1,5,3,GL_FLOAT,GL_FALSE,0);
    glVertexArrayAttribBinding(VAO1,5,5);
    glEnableVertexArrayAttrib(VAO1,5);
    glVertexAttribDivisor(5,1);

    glCreateBuffers(1,&VBO_instances_colors1);
    glNamedBufferStorage(VBO_instances_colors1,Board_cubes->num_cubes()*3*sizeof(GLubyte),nullptr,GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
    glVertexArrayVertexBuffer(VAO1,6,VBO_instances_colors1,0,3*sizeof(GLubyte)); // 1,VBO
    glVertexArrayAttribFormat(VAO1,6,3,GL_UNSIGNED_BYTE,GL_TRUE,0); // se normaliza
    glVertexArrayAttribBinding(VAO1,6,6); //2,1)
    glEnableVertexArrayAttrib(VAO1,6);
    glVertexAttribDivisor(6,1);


  // Put data
  // vertices
  glNamedBufferSubData(VBO_vertices1,0,Cube->Vertices_drawarray.size()*3*sizeof(GLfloat),&Cube->Vertices_drawarray[0]);
  // colors
  glNamedBufferSubData(VBO_colors1,0,Cube->Vertices_drawarray.size()*3*sizeof(GLfloat),&Cube->Vertices_colors_drawarray[0]);

  // triangles normals
  glNamedBufferSubData(VBO_triangles_normals1,0,Cube->Vertices_drawarray.size()*3*sizeof(GLfloat),&Cube->Vertices_triangles_normals_drawarray[0]);

  // vertices normals
  glNamedBufferSubData(VBO_vertices_normals1,0,Cube->Vertices_drawarray.size()*3*sizeof(GLfloat),&Cube->Vertices_normals_drawarray[0]);

  // texture coordinates
//  glNamedBufferSubData(VBO_texture_coordinates1,0,Cube->Vertices_drawarray.size()*2*sizeof(GLfloat),&Cube->Vertices_texture_coordinates_drawarray[0]);

  // texture coordinates
//  glNamedBufferSubData(VBO_vertices_wire1,0,Bounding_box.Vertices_drawarray.size()*3*sizeof(GLfloat),&Bounding_box.Vertices_drawarray[0]);

  // translation for each cube
  glNamedBufferSubData(VBO_instances_positions1,0,Board_cubes->num_cubes()*3*sizeof(GLfloat),&Board_cubes->Vec_positions[0]);

  // scaling for each cube
  glNamedBufferSubData(VBO_instances_scaling1,0,Board_cubes->num_cubes()*3*sizeof(GLfloat),&Board_cubes->Vec_scaling[0]);

  // color for each cube
  glNamedBufferSubData(VBO_instances_colors1,0,Board_cubes->num_cubes()*3*sizeof(GLubyte),&Board_cubes->Vec_colors[0]);

  glBindVertexArray(0);

  update();
}

//HEA

//GLuint _gl_widget_xmapslab_3D::set_image(QImage &Image1)
//{
//  GLuint Texture;

//  glCreateVec_textures(GL_TEXTURE_2D,1,&Texture);
//  glTextureStorage2D(Texture,1,GL_RGB8,Image1.width(),Image1.height());

//  glBindTexture(GL_TEXTURE_2D,Texture);
//  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//  // fill with data
//  glTextureSubImage2D(Texture,0,0,0,Image1.width(),Image1.height(),GL_RGB,GL_UNSIGNED_BYTE,Image1.constBits());

//  return Texture;
//}

//HEA

GLuint _gl_widget_xmapslab_3D::set_texture(std::shared_ptr<cv::Mat> Image)
{
//  GLuint Texture;

  if (Texture!=0) glDeleteVec_textures(1,&Texture);

  glCreateVec_textures(GL_TEXTURE_2D,1,&Texture);

#ifdef DEBUG_XML
  cout << "Texture=" << Texture << endl;
#endif

  glTextureStorage2D(Texture,1,GL_RGBA8,Image->cols,Image->rows);

//  cout << "Texture=" << Texture << " Width=" << Image1.width() << endl;

  glBindTexture(GL_TEXTURE_2D,Texture);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // fill with data
  glTextureSubImage2D(Texture,0,0,0,Image->cols,Image->rows,GL_BGRA,GL_UNSIGNED_BYTE,&Image->data[0]);

  return Texture;
}

//HEA

void _gl_widget_xmapslab_3D::initializeGL()
{
#ifdef DEBUG_XML
  const GLubyte* strm;

  strm = glGetString(GL_VENDOR);
  std::cerr << "Vendor: " << strm << "\n";
  strm = glGetString(GL_RENDERER);
  std::cerr << "Renderer: " << strm << "\n";
  strm = glGetString(GL_VERSION);
  std::cerr << "OpenGL Version: " << strm << "\n";

  if (strm[0] == '1'){
    std::cerr << "Only OpenGL 1.X supported!\n";
    exit(-1);
    }

  strm = glGetString(GL_SHADING_LANGUAGE_VERSION);
  std::cerr << "GLSL Version: " << strm << "\n";
#endif

  glewExperimental = GL_TRUE;
  int err = glewInit();
  if (GLEW_OK != err){
//    std::cerr << "Error: " << glewGetErrorString(err) << "\n";
    QMessageBox::warning(this, tr("Warning"),tr("glewInit failed"));
    QMessageBox MsgBox(this);
    QFont Font=MsgBox.font();
    Font.setPointSize(20);
    MsgBox.setFont(Font);
    MsgBox.setText("Error: There is not OpenGL drivers\n\nPlease, look for the information of your GPU (AMD, INTEL or NVIDIA) and install the drivers");
    MsgBox.exec();
    Window->close();
    exit(-1);
    }

#ifdef DEBUG_XML
  int Max_texture_size=0;
  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &Max_texture_size);
  std::cout << "Max texture size: " << Max_texture_size << "\n";
#endif

  glClearColor(1.0,1.0,1.0,1.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_POLYGON_OFFSET_LINE);

  Window_width=width();
  Window_height=height();

  // Load the programs
  _shaders Shader;

  // basic
//  static const GLchar * P0_vs[]={
//  #include "shaders/basic3D.vert"
//  };

//  static const GLchar * P0_fs[]={
//  #include "shaders/basic3D.frag"
//  };

//  Program1=Shader.load_shaders(P0_vs,P0_fs);
//  if (Program1==0){
//    QMessageBox Message;
//    Message.setText("Error with the GPU program basic3D");
//    Message.exec();
//    exit(-1);
//  }

//  // wire
//  static const GLchar * P1_vs[]={
//  #include "shaders/basic3D_wire.vert"
//  };

//  static const GLchar * P1_fs[]={
//  #include "shaders/basic3D_wire.frag"
//  };

//  Program2=Shader.load_shaders(P1_vs,P1_fs);
//  if (Program2==0){
//    QMessageBox Message;
//    Message.setText("Error with the GPU program basic3D wire");
//    Message.exec();
//    exit(-1);
//  }

  // basic
  static const GLchar * P2_vs[]={
  #include "basic3D_instances.vert"
  };

  static const GLchar * P2_fs[]={
  #include "basic3D_instances.frag"
  };

  Program3=Shader.load_shaders(P2_vs,P2_fs);
  if (Program3==0){
    QMessageBox::critical(Window, Window->tr("Error"),Window->tr("Error with the GPU program 'basic3D_instances'"));
    QApplication::quit();
    exit(-1);
//    QMessageBox Message;
//    Message.setText("Error with the GPU program basic3D_instances");
//    Message.exec();
//    exit(-1);
  }

//  glCreateVertexArrays(1,&VAO1);
//  initialize_objects();
//  create_object(1000,1000,50,nullptr);
}

//HEA

//void _gl_widget_xmapslab_3D::update_data(shared_ptr<cv::Mat> Image,shared_ptr<cv::Mat> Result_floats_image)
//{
//  Board->update_data(Result_floats_image);

//  glBindVertexArray(VAO1);

//  if (Image==nullptr) No_texture=true;
//  else{
//    No_texture=false;
//    set_texture(Image);
//  }

//  // Put data
//  // vertices
//  glNamedBufferSubData(VBO_vertices1,0,Board->Vertices_drawarray.size()*3*sizeof(GLfloat),&Board->Vertices_drawarray[0]);

//  // triangles normals
//  glNamedBufferSubData(VBO_triangles_normals1,0,Board->Vertices_drawarray.size()*3*sizeof(GLfloat),&Board->Vertices_triangles_normals_drawarray[0]);

//  // vertices normals
//  glNamedBufferSubData(VBO_vertices_normals1,0,Board->Vertices_drawarray.size()*3*sizeof(GLfloat),&Board->Vertices_normals_drawarray[0]);

//  glBindVertexArray(0);
//}


void _gl_widget_xmapslab_3D::update_data(std::shared_ptr<cv::Mat> Image, std::shared_ptr<cv::Mat> Result_floats_image)
{
  Board_cubes->update_data(Image,Result_floats_image);

  glBindVertexArray(VAO1);

  if (Image==nullptr) No_texture=true;
  else{
    No_texture=false;
//    set_texture(Image);
  }

  // Put data
  // scaling for each cube
  glNamedBufferSubData(VBO_instances_scaling1,0,Board_cubes->num_cubes()*3*sizeof(GLfloat),&Board_cubes->Vec_scaling[0]);

  // color for each cube
  glNamedBufferSubData(VBO_instances_colors1,0,Board_cubes->num_cubes()*3*sizeof(GLubyte),&Board_cubes->Vec_colors[0]);

  glBindVertexArray(0);
}
