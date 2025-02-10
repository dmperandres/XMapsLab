//LIC

#include "glwidget_xmapslab_ge.h"
// #include "w_tab.h"
#include "window_xmapslab.h"

using namespace _gl_widget_xmapslab_ge_ns;
using namespace _filter_ns;

//HEA

int _gl_widget_xmapslab_ge::Counter_draw=0;

_gl_widget_xmapslab_ge::_gl_widget_xmapslab_ge(_window_xmapslab *Window1, QWidget *Parent)
: QOpenGLWidget(Parent)
{
  Window=Window1;

//  QGLFormat GLformat;
//  GLformat.setSwapInterval(0);
//  QGLFormat::setDefaultFormat(GLformat);

  Selected_tab=_w_tab_xmapslab_ns::_tabs::LAYERS_TAB;
  Selected_index=0;
}

//HEA

_gl_widget_xmapslab_ge::~_gl_widget_xmapslab_ge()
{
  clear_data();
}

//HEA

void _gl_widget_xmapslab_ge::clear_data()
{
}

//HEA

void _gl_widget_xmapslab_ge::mousePressEvent(QMouseEvent *Event)
{
  if (Event->buttons() & Qt::LeftButton) {
    Change_pos=true;
    Initial_position_X=Event->position().x()*Device_pixel_ratio;
    Initial_position_Y=Event->position().y()*Device_pixel_ratio;
  }
}

//HEA

void _gl_widget_xmapslab_ge::mouseReleaseEvent(QMouseEvent *Event)
{
  Q_UNUSED(Event)
  Change_pos=false;
}

//HEA

void _gl_widget_xmapslab_ge::mouseMoveEvent(QMouseEvent *Event)
{
  int Last_position_X=Event->position().x()*Device_pixel_ratio;
  int Last_position_Y=Event->position().y()*Device_pixel_ratio;

  if (Change_pos==true){
    Translation.x+=Last_position_X-Initial_position_X;
    Translation.y+=Initial_position_Y-Last_position_Y;
    Initial_position_X=Last_position_X;
    Initial_position_Y=Last_position_Y;
    }

//  Drawn=false;

  update();
}

//HEA

void _gl_widget_xmapslab_ge::wheelEvent(QWheelEvent *Event)
{
  QPoint Num_degrees = Event->angleDelta();
  int Step = Num_degrees.y();

  if (Step<0) Scale_drawing_mode/=_common_ns::MOUSE_SCALING_FACTOR;
  else Scale_drawing_mode*=_common_ns::MOUSE_SCALING_FACTOR;

  update();
}

//HEA

void _gl_widget_xmapslab_ge::mouseDoubleClickEvent(QMouseEvent *Event)
{
  if (Event->buttons() & Qt::LeftButton) {
    Translation.x=0;
    Translation.y=0;
    update();
  }
  if (Event->buttons() & Qt::RightButton) {
    Scale_drawing_mode=1.0f;
    update();
  }
}

//HEA

void _gl_widget_xmapslab_ge::load_shaders()
{
  _shaders Shader;
  static const GLchar * P0_vs[]={
#include "basic_ge.vert"
  };

  static const GLchar * P0_fs[]={
#include "basic_ge.frag"
  };

  Program1=Shader.load_shaders(P0_vs,P0_fs);
  if (Program1==0){
    QMessageBox Message;
    Message.setText("Error with the GPU program basic_ge");
    Message.exec();
    exit(-1);
  }
}

//HEA

void _gl_widget_xmapslab_ge::initialize_object()
{
  int Width1=512;
  int Height1=512;

  QImage Image1(Width1,Height1,QImage::Format_RGB888);
  Image1.fill(QColor(255,0,0));

  if (Texture1>0) glDeleteTextures(1,&Texture1);

  glCreateTextures(GL_TEXTURE_2D,1,&Texture1);
  glTextureStorage2D(Texture1,1,GL_RGB,Width1,Height1);

  glBindTexture(GL_TEXTURE_2D,Texture1);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // fill with data
  glTextureSubImage2D(Texture1,0,0,0,Width1,Height1,GL_RGB,GL_UNSIGNED_BYTE,Image1.constBits());

  // adjust the sizes
  if (Vertices.size()==0){
    Vertices.resize(6);
    Tex_coordinates.resize(6);

    Vertices[0]=_vertex3f(-Width1/2, -Height1/2, 0.);
    Vertices[1]=_vertex3f(Width1/2, -Height1/2, 0.);
    Vertices[2]=_vertex3f(-Width1/2, Height1/2, 0.);
    Vertices[3]=_vertex3f(Width1/2, -Height1/2, 0.);
    Vertices[4]=_vertex3f(Width1/2, Height1/2, 0.);
    Vertices[5]=_vertex3f(-Width1/2, Height1/2, 0.);

    Tex_coordinates[0]=_vertex2f(0.0,0.0);
    Tex_coordinates[1]=_vertex2f(1.0,0.0);
    Tex_coordinates[2]=_vertex2f(0.0,1.0);
    Tex_coordinates[3]=_vertex2f(1.0,0.0);
    Tex_coordinates[4]=_vertex2f(1.0,1.0);
    Tex_coordinates[5]=_vertex2f(0.0,1.0);
  }

  if (VAO1>0) glDeleteVertexArrays(1,&VAO1);

  glCreateVertexArrays(1,&VAO1);
  glBindVertexArray(VAO1);

  // vertices coordinates
  // create
  if (VBO1_1>0) glDeleteBuffers(1,&VBO1_1);

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


  if (VBO1_2>0) glDeleteBuffers(1,&VBO1_2);

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
}


//HEA

void _gl_widget_xmapslab_ge::initializeGL()
{
#ifdef DEBUG_XML
  const GLubyte* strm;

  strm = glGetString(GL_VENDOR);
  cout << "Vendor: " << strm << "\n";
  strm = glGetString(GL_RENDERER);
  cout << "Renderer: " << strm << "\n";
  strm = glGetString(GL_VERSION);
  cout << "OpenGL Version: " << strm << "\n";
  strm = glGetString(GL_SHADING_LANGUAGE_VERSION);
  cout << "GLSL Version: " << strm << "\n";
#endif

  //Glew init:
   GLenum err = glewInit();
  if (GLEW_OK != err){
    // Problem: glewInit failed, something is seriously wrong.
//    cout << "Error: " << glewGetErrorString(err) << "\n";

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

  Window_width=width();
  Window_height=height();

  Device_pixel_ratio=devicePixelRatio();

  load_shaders();
  initialize_object();
}

//HEA

void _gl_widget_xmapslab_ge::paintGL()
{
//  glViewport(0,0,width(),height());
  draw_objects();
}

//HEA

void _gl_widget_xmapslab_ge::resizeGL(int width, int height)
{
  Window_width=width;
  Window_height=height;

  glViewport(0,0,width*Device_pixel_ratio,height*Device_pixel_ratio);
}

//HEA

void _gl_widget_xmapslab_ge::draw_objects()
{

  QMatrix4x4 Model_view;

  Model_view.ortho(-Window_width*Scale_drawing_mode/2,Window_width*Scale_drawing_mode/2,-Window_height*Scale_drawing_mode/2, Window_height*Scale_drawing_mode/2,-100,100);
  Model_view.translate(Translation.x,Translation.y,0);

  glViewport(0,0,Window_width*Device_pixel_ratio,Window_height*Device_pixel_ratio);
  glClearColor(0.8f,0.8f,0.8f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  //  glPointSize(10);
  glUseProgram(Program1);
  glBindVertexArray(VAO1);

  glUniformMatrix4fv(0,1,GL_FALSE,Model_view.data());
  glBindTextureUnit(0,Texture1);

  glDrawArrays(GL_TRIANGLES,0,6);

  glBindVertexArray(0);
  glUseProgram(0);
}

//HEA

void _gl_widget_xmapslab_ge::update_size_texture(int Width1,int Height1)
{
  makeCurrent();

  glBindVertexArray(VAO1);

//  glDeleteVec_textures(1,&Texture1);

//  glCreateVec_textures(GL_TEXTURE_2D,1,&Texture1);
//  glTextureStorage2D(Texture1,1,GL_BGRA,Width1,Height1);

//  glActiveTexture(GL_TEXTURE0);
//  glBindTexture(GL_TEXTURE_2D,Texture1);
//  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // fill with data
//  glTextureSubImage2D(Texture1,0,0,0,Width1,Height1,GL_BGR,GL_UNSIGNED_BYTE,Frame_buffer->data);


  Vertices[0]=_vertex3f(-Width1/2, -Height1/2, 0.0f);
  Vertices[1]=_vertex3f(Width1/2, -Height1/2, 0.0f);
  Vertices[2]=_vertex3f(-Width1/2, Height1/2, 0.0f);
  Vertices[3]=_vertex3f(Width1/2, -Height1/2, 0.0f);
  Vertices[4]=_vertex3f(Width1/2, Height1/2, 0.0f);
  Vertices[5]=_vertex3f(-Width1/2, Height1/2, 0.0f);


  // uptdate vertices coordinates
  glNamedBufferSubData(VBO1_1,0,Vertices.size()*3*sizeof(float),&Vertices[0]);

  glBindVertexArray(0);
}

//HEA

void _gl_widget_xmapslab_ge::update_texture(std::string Name)
{
  //  GLuint Texture=Window->Map_layers_data[Name].Texture;
  shared_ptr<cv::Mat> Image=Window->Map_mapping_images[Name];
  //  int Row=Image->cols;
  //  int Col=Image->rows;

  glBindVertexArray(VAO1);
  glBindTexture(GL_TEXTURE_2D,Texture1);
  glTextureSubImage2D(Texture1,0,0,0,Image->cols,Image->rows,GL_BGR,GL_UNSIGNED_BYTE,&Image->data[0]);
  glBindVertexArray(0);

  update();
}

//HEA

void _gl_widget_xmapslab_ge::set_texture(std::string Name)
{
  //  GLuint Texture;
  shared_ptr<cv::Mat> Image=Window->Map_mapping_images[Name];

  glDeleteTextures(1,&Texture1);

  glCreateTextures(GL_TEXTURE_2D,1,&Texture1);

  glTextureStorage2D(Texture1,1,GL_RGB8,Image->cols,Image->rows);

  //  cout << "Texture=" << Texture << " Width=" << Image1.width() << endl;

  glBindTexture(GL_TEXTURE_2D,Texture1);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // fill with data
  //  glTextureSubImage2D(Texture1,0,0,0,Image->cols,Image->rows,GL_BGRA,GL_UNSIGNED_BYTE,&Image->data[0]);
}

//HEA

void _gl_widget_xmapslab_ge::save_image(std::string File)
{
  QImage Image(Window->Initial_width,Window->Initial_height,QImage::Format_RGBA8888);

  makeCurrent();

  glReadPixels(0,0,Window->Initial_width,Window->Initial_height,GL_RGBA,GL_UNSIGNED_BYTE,Image.bits());
  Image=Image.mirrored();
  Image.save(QString::fromStdString(File),"PNG");
}
