/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "glwidget_positions.h"
#include "window_positions.h"

//using namespace _gl_widget_positions_ns;

_gl_widget_positions::_gl_widget_positions(_window_positions *Window1,int Position_gl_widget1):Window(Window1),Position_gl_widget(Position_gl_widget1)
{
  #ifdef DEBUG_XML
  cout << "_gl_widget constructor" << endl;
  #endif
  setMinimumSize(300, 300);
  setFocusPolicy(Qt::StrongFocus);
}

/*************************************************************************/

_gl_widget_positions::~_gl_widget_positions()
{
  #ifdef DEBUG_XML
  std::cout << "terminando gl_widget" << std::endl;
  #endif
}

/*************************************************************************/

void _gl_widget_positions::save_image(std::string File)
{
  QImage Image(Window->image_width(),Window->image_height(),QImage::Format_RGBA8888);

  glReadPixels(0,0,Window->image_width(),Window->image_height(),GL_RGBA,GL_UNSIGNED_BYTE,Image.bits());
  Image=Image.mirrored();
  Image.save(QString::fromStdString(File),"PNG");
}

/*************************************************************************/

GLuint _gl_widget_positions::set_texture(std::shared_ptr<cv::Mat> Image)
{
  GLuint Texture;

  glCreateTextures(GL_TEXTURE_2D,1,&Texture);

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

/*************************************************************************/

void _gl_widget_positions::update_texture(int Position_gl_widget1)
{
//  makeCurrent();
//  defaultFramebufferObject();

  GLuint Texture=Window->Vec_textures[Position_gl_widget1];
  std::shared_ptr<cv::Mat> Image=Window->Vec_layers[Position_gl_widget1]->image();

  glBindVertexArray(VAO1);
  glBindTexture(GL_TEXTURE_2D,Texture);
  glTextureSubImage2D(Texture,0,0,0,Image->cols,Image->rows,GL_BGRA,GL_UNSIGNED_BYTE,&Image->data[0]);
  glBindVertexArray(0);
}

//*************************************************************************
//
//*************************************************************************

void _gl_widget_positions::refresh_texture(int Width1,int Height1)
{
  makeCurrent();

  Vertices[0]=_vertex3f(-Width1/2, -Height1/2, 0.1);
  Vertices[1]=_vertex3f(Width1/2, -Height1/2, 0.1);
  Vertices[2]=_vertex3f(-Width1/2, Height1/2, 0.1);
  Vertices[3]=_vertex3f(Width1/2, -Height1/2, 0.1);
  Vertices[4]=_vertex3f(Width1/2, Height1/2, 0.1);
  Vertices[5]=_vertex3f(-Width1/2, Height1/2, 0.1);

  glBindVertexArray(VAO1);
  // uptdate vertices coordinates
  glNamedBufferSubData(VBO1_1,0,Vertices.size()*3*sizeof(float),&Vertices[0]);

  glBindVertexArray(0);
}

/*************************************************************************/

void _gl_widget_positions::mousePressEvent(QMouseEvent *Event)
{
//  if (Position_gl_widget==_window_positions_ns::MAIN_IMAGE){
    if (Event->button()==Qt::LeftButton) {
      Change_pos=true;
      Initial_position_X=Event->position().x();
      Initial_position_Y=Event->position().y();
    }
    else{
      if (Editing && Event->button()==Qt::RightButton){
        Selection_position_X=Event->position().x();
        Selection_position_Y=height()-Event->position().y();
      }
    }
//  }
}

/*************************************************************************/

void _gl_widget_positions::mouseReleaseEvent(QMouseEvent *Event)
{
  if (Event->button()==Qt::RightButton){
    Change_pos=false;
    if (Position_gl_widget==_window_positions_ns::MAIN_IMAGE) compute_position(Event);
  }
}

/*************************************************************************/

void _gl_widget_positions::mouseDoubleClickEvent(QMouseEvent *Event)
{
  if (Event->buttons() & Qt::LeftButton) {
    Translation.x=0;
    Translation.y=0;
  }

  if (Event->buttons() & Qt::RightButton) {
    Scaling=1.0;
  }

  update();
}

//*************************************************************************
//
//*************************************************************************

void _gl_widget_positions::mouseMoveEvent(QMouseEvent *Event)
{
//  if (Position_gl_widget==_window_positions_ns::MAIN_IMAGE){
    int Last_position_X=Event->position().x();
    int Last_position_Y=Event->position().y();

    if (Change_pos==true){
      Translation.x+=Last_position_X-Initial_position_X;
      Translation.y+=Initial_position_Y-Last_position_Y;
      Initial_position_X=Last_position_X;
      Initial_position_Y=Last_position_Y;

//      Window->change_position_w1(Translation.x,Translation.y);
      }

    update();
//  }
}

//*************************************************************************
//
//*************************************************************************

void _gl_widget_positions::wheelEvent(QWheelEvent *Event)
{
//  if (Position_gl_widget==_window_positions_ns::MAIN_IMAGE){
//    QPoint Num_degrees = Event->angleDelta();
//    int Step = Num_degrees.y() / 120;
    float Factor;

    if (Event->angleDelta().y()<0){
      Scaling/=_common_ns::SCALING_FACTOR;
      Factor=1/_common_ns::SCALING_FACTOR;
    }
    else{
      Scaling*=_common_ns::SCALING_FACTOR;
      Factor=_common_ns::SCALING_FACTOR;
    }

    Window->change_scale(Factor);

    update();
//  }
}

/*************************************************************************/

void _gl_widget_positions::draw_objects()
{
#ifdef LINUX
  glViewport(0,0,Window_width,Window_height);
#endif

  glClearColor(0.8,0.8,0.8,1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  if (Window->Vec_layers.size()>0){
    QMatrix4x4 Model_view;

    int Width=int(roundf(float(Window_width)*Scaling));
    int Height=int(roundf(float(Window_height)*Scaling));

    if (Position_gl_widget==0){
      if (Width%2!=0) Width++;
      if (Height%2!=0) Height++;
    }

    Model_view.ortho(-Width/2,Width/2,-Height/2,Height/2,-100,100);

    Model_view.translate(Translation.x,Translation.y,0);
    glUseProgram(Program1);
    glBindVertexArray(VAO1);

    glUniformMatrix4fv(0,1,GL_FALSE,Model_view.data());

    if (Position_gl_widget==0){
      // num textures
      glUniform1i(20,Window->Vec_layers.size());
      // background color
      glUniform3fv(21,1,(GLfloat*) &_common_ns::COLORS[_common_ns::WHITE]);

      for (unsigned int i=0;i<Window->Vec_layers.size();i++){
        glBindTextureUnit(i,Window->Vec_textures[i]);
      }
    }
    else{
      // num textures
      glUniform1i(20,1);
      // background color
      glUniform3fv(21,1,(GLfloat*) &_common_ns::COLORS[_common_ns::WHITE]);

      glBindTextureUnit(0,Window->Auxiliary_texture);
    }

    glDrawArrays(GL_TRIANGLES,0,6);

    glBindVertexArray(0);
    glUseProgram(0);
  }
}

//*************************************************************************
//
//*************************************************************************

//void _gl_widget_positions::paintEvent(QPaintEvent *Event)
//{
//  Q_UNUSED(Event)

//  QPainter Painter;
//  Painter.begin(this);

//  Painter.beginNativePainting();
//  draw_objects();
//  Painter.endNativePainting();

//  if (Position_gl_widget==0){
//    QPen Pen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
//    QRect Rect_color=QRect((Window_width-Window->ZOI.x)/2,(Window_height-Window->ZOI.y)/2,Window->ZOI.x,Window->ZOI.y);
//    Painter.setPen(Pen);
//    Painter.drawRect(Rect_color);
//  }

//  Painter.end();
//}

/*************************************************************************/

void _gl_widget_positions::paintGL()
{
  QPainter Painter;
  Painter.begin(this);

  Painter.beginNativePainting();
  draw_objects();
  Painter.endNativePainting();

//  if (Position_gl_widget==0){
//    QPen Pen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
//    QRect Rect_color=QRect((Window_width-Window->ZOI.x)/2,(Window_height-Window->ZOI.y)/2,Window->ZOI.x,Window->ZOI.y);
//    Painter.setPen(Pen);
//    Painter.drawRect(Rect_color);
//  }

  Painter.end();
}

/*************************************************************************/

void _gl_widget_positions::resizeGL(int Width1, int Height1)
{
  #ifdef DEBUG_XML
  cout << "_gl_widget resizeGL" << endl;
  #endif

  Window_width=Width1;
  Window_height=Height1;
  glViewport(0,0,Width1,Height1);

  if (Position_gl_widget==_window_positions_ns::MAIN_IMAGE) Window->compute_dimensions();
}

/*************************************************************************/

void _gl_widget_positions::initialize_object()
{
  #ifdef DEBUG_XML
  cout << "_gl_widget initialize_object" << endl;
  #endif

  _shaders Shader;

  static const GLchar * P0_vs[]={
  #include "basic_positions.vert"
  };

  static const GLchar * P0_fs[]={
  #include "basic_positions.frag"
  };

  Program1=Shader.load_shaders(P0_vs,P0_fs);
  if (Program1==0){
    QMessageBox Message;
    Message.setText("Error with the GPU program basic");
    Message.exec();
    exit(-1);
  }

  // adjust the sizes
  Vertices.resize(6);

  Tex_coordinates.resize(6);
  Tex_coordinates[0]=_vertex2f(0.0,0.0);
  Tex_coordinates[1]=_vertex2f(1.0,0.0);
  Tex_coordinates[2]=_vertex2f(0.0,1.0);
  Tex_coordinates[3]=_vertex2f(1.0,0.0);
  Tex_coordinates[4]=_vertex2f(1.0,1.0);
  Tex_coordinates[5]=_vertex2f(0.0,1.0);

  glCreateVertexArrays(1,&VAO1);
  glBindVertexArray(VAO1);

  // vertices coordinates
  // create
  glCreateBuffers(1,&VBO1_1);
  // reserve espace (and initialice; if use NULL there is not initialization)
  glNamedBufferStorage(VBO1_1,Vertices.size()*3*sizeof(float),&Vertices[0],GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT);
  // bind to VAO
  glVertexArrayVertexBuffer(VAO1,0,VBO1_1,0,3*sizeof(float));
  // state the format of the data
  glVertexArrayAttribFormat(VAO1,1,3,GL_FLOAT,GL_FALSE,0);
  // state what vertex buffer binding ot use for this attribute
  glVertexArrayAttribBinding(VAO1,1,0);
  // enable the attribute
  glEnableVertexAttribArray(1);

  glCreateBuffers(1,&VBO1_2);
  // reserve espace (and initialice; if use NULL there is not initialization)
  glNamedBufferStorage(VBO1_2,Tex_coordinates.size()*2*sizeof(float),&Tex_coordinates[0],GL_DYNAMIC_STORAGE_BIT);
  // bind to VAO
  glVertexArrayVertexBuffer(VAO1,1,VBO1_2,0,2*sizeof(float));
  // state the format of the data
  glVertexArrayAttribFormat(VAO1,2,2,GL_FLOAT,GL_FALSE,0);
  // state what vertex buffer binding ot use for this attribute
  glVertexArrayAttribBinding(VAO1,2,1);
  // enable the attribute
  glEnableVertexAttribArray(2);

  glBindVertexArray(0);

  //
  Scaling=1.0;
  Translation=_vertex2f(0,0);

  Image_changed=true;
}

/*************************************************************************/

void _gl_widget_positions::initializeGL()
{

//  const GLubyte* strm;

//  strm = glGetString(GL_VENDOR);
//  std::cerr << "Vendor: " << strm << "\n";
//  strm = glGetString(GL_RENDERER);
//  std::cerr << "Renderer: " << strm << "\n";
//  strm = glGetString(GL_VERSION);
//  std::cerr << "OpenGL Version: " << strm << "\n";

//  if (strm[0] == '1'){
//    std::cerr << "Only OpenGL 1.X supported!\n";
//    exit(-1);
//    }

//  strm = glGetString(GL_SHADING_LANGUAGE_VERSION);
//  std::cerr << "GLSL Version: " << strm << "\n";

  glewExperimental = GL_TRUE;
  int err = glewInit();
  if (GLEW_OK != err){
    // Problem: glewInit failed, something is seriously wrong.
    std::cerr << "Error: " << glewGetErrorString(err) << "\n";
    exit (-1);
    }

  // este codigo es para limpiar un error que se produce con GLEW (inclido 1.10)
  // http://www.opengl.org/wiki/OpenGL_Loading_Library
  GLenum glErr;
  glErr = glGetError();
  while (glErr!=GL_NO_ERROR) glErr = glGetError();

  //
//  int Max_texture_size=0;
//  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &Max_texture_size);
//  std::cout << "Max texture size: " << Max_texture_size << "\n";

//  int Max_texture_units=0;
//  glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &Max_texture_units);
//  std::cout << "Max texture units: " << Max_texture_units << "\n";

//  int Max_texture_units_shader=0;
//  glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &Max_texture_units_shader);
//  std::cout << "Max texture units per shader: " << Max_texture_units_shader << "\n";

  Window_width=width();
  Window_height=height();

  initialize_object();
}

/*************************************************************************/

void _gl_widget_positions::compute_position(QMouseEvent *Event)
{
  Q_UNUSED(Event)

  int Width=int(roundf(float(Window_width)*Scaling));
  int Height=int(roundf(float(Window_height)*Scaling));

  int xmin=-Width/2;
  int xmax=-xmin;
  int ymin=-Height/2;
  int ymax=-ymin;

  int Pos_x=(xmax-xmin)*Selection_position_X/Window_width+xmin-Translation.x;
  int Pos_y=(ymax-ymin)*Selection_position_Y/Window_height+ymin-Translation.y;

  Pos_x=Pos_x+Window->image_width()/2;
  Pos_y=Pos_y+Window->image_height()/2;

  if (Pos_x>=0 && Pos_x<Window->image_width() && Pos_y>=0 && Pos_y<Window->image_height()){
    Window->update_positions(Pos_x,Window->image_height()-Pos_y);
  }
}
