//LIC

#include "glwidget_pos.h"
#include "window.h"


using namespace std;
using namespace _gl_widget_pos_ns;


_gl_widget_pos::_gl_widget_pos(_window *Window1,int Position1):Window(Window1),Position(Position1)
{
  setMinimumSize(300, 300);
  setFocusPolicy(Qt::StrongFocus);
}

//HEA

_gl_widget_pos::~_gl_widget_pos()
{
  std::cout << "terminando gl_widget_pos" << std::endl;
}

//HEA

void _gl_widget_pos::save_image(string File)
{
  QImage Image(Window->Initial_width,Window->Initial_height,QImage::Format_RGBA8888);

  glReadPixels(0,0,Window->Initial_width,Window->Initial_height,GL_RGBA,GL_UNSIGNED_BYTE,Image.bits());
  Image=Image.mirrored();
  Image.save(QString::fromStdString(File),"PNG");
}

//HEA

GLuint _gl_widget_pos::set_texture(shared_ptr<cv::Mat> Image)
{
  GLuint Texture;

//  defaultFramebufferObject();

  glBindVertexArray(VAO1);

  glCreateTextures(GL_TEXTURE_2D,1,&Texture);

  cout << "Texture=" << Texture << endl;

  glTextureStorage2D(Texture,1,GL_RGBA8,Image->cols,Image->rows);

  glBindTexture(GL_TEXTURE_2D,Texture);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  // fill with data
  glTextureSubImage2D(Texture,0,0,0,Image->cols,Image->rows,GL_BGRA,GL_UNSIGNED_BYTE,&Image->data[0]);

  glBindVertexArray(0);

  return Texture;
}


void _gl_widget_pos::update_texture(string Name)
{
//  makeCurrent();
//  defaultFramebufferObject();

  GLuint Texture=Window->Map_layers_data[Name].Texture;
  shared_ptr<cv::Mat> Image=Window->Map_layers_data[Name].Layer->image();

  glBindVertexArray(VAO1);
  glBindTexture(GL_TEXTURE_2D,Texture);
  glTextureSubImage2D(Texture,0,0,0,Image->cols,Image->rows,GL_BGRA,GL_UNSIGNED_BYTE,&Image->data[0]);
  glBindVertexArray(0);
}


//*************************************************************************
//
//*************************************************************************

void _gl_widget_pos::refresh_texture(int Width1,int Height1)
{
  makeCurrent();

  Vertices[0]=_vertex3f(-Width1/2, -Height1/2, 0.1f);
  Vertices[1]=_vertex3f(Width1/2, -Height1/2, 0.1f);
  Vertices[2]=_vertex3f(-Width1/2, Height1/2, 0.1f);
  Vertices[3]=_vertex3f(Width1/2, -Height1/2, 0.1f);
  Vertices[4]=_vertex3f(Width1/2, Height1/2, 0.1f);
  Vertices[5]=_vertex3f(-Width1/2, Height1/2, 0.1f);

  glBindVertexArray(VAO1);
  // uptdate vertices coordinates
  glNamedBufferSubData(VBO1_1,0,Vertices.size()*3*sizeof(float),&Vertices[0]);

  glBindVertexArray(0);
}


//HEA

void _gl_widget_pos::mousePressEvent(QMouseEvent *Event)
{
  if (Position==1){
    if (Event->button()==Qt::LeftButton) {
      Change_pos=true;
      Initial_position_X=Event->x();
      Initial_position_Y=Event->y();

      if (Event->modifiers() & Qt::ShiftModifier) {
        Selection_position_X=Event->x();
        Selection_position_Y=height()-Event->y();
        Selection_add=true;
      }
    }
    else{
      if ((Event->button()==Qt::RightButton) && (Event->modifiers() & Qt::ShiftModifier)) {
        Selection_position_X=Event->x();
        Selection_position_Y=height()-Event->y();
        Selection_add=false;
      }
    }
  }
}

//HEA

void _gl_widget_pos::mouseReleaseEvent(QMouseEvent *Event)
{
  if (Position==1){
    compute_position(Event);
    Change_pos=false;
  }
}

//HEA

void _gl_widget_pos::mouseMoveEvent(QMouseEvent *event)
{
  if (Position==1){
    int Last_position_X=event->x();
    int Last_position_Y=event->y();

    if (Change_pos==true){
      Translation.x+=Last_position_X-Initial_position_X;
      Translation.y+=Initial_position_Y-Last_position_Y;
      Initial_position_X=Last_position_X;
      Initial_position_Y=Last_position_Y;

      Window->change_position_w1(Translation.x,Translation.y);
      }

    update();
  }
}

//*************************************************************************
//
//*************************************************************************

void _gl_widget_pos::wheelEvent(QWheelEvent *event)
{
  if (Position==1){
    int Step=event->delta()/120;
    float Factor;

    if (Step<0){
      Scale_drawing_mode/=1.2f;
      Factor=1/1.2f;
    }
    else{
      Scale_drawing_mode*=1.2f;
      Factor=1.2f;
    }

    Window->change_scale_w1(Factor);

    update();
  }
}

//HEA

void _gl_widget_pos::draw_objects()
{
  glViewport(0,0,Window_width,Window_height);
  glClearColor(0.8f,0.8f,0.8f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  if (Window->Map_layers_data.size()>0){
    QMatrix4x4 Model_view;

    if (Position==0){
      int Width=int(roundf(float(Window_width)*Window->Scaling[0]));
      int Height=int(roundf(float(Window_height)*Window->Scaling[0]));

      if (Width%2!=0) Width++;
      if (Height%2!=0) Height++;

      Model_view.ortho(-Width/2,Width/2,-Height/2,Height/2,-100,100);
    }
    else{
      int Width=int(roundf(float(Window_width)*Window->Scaling[1]));
      int Height=int(roundf(float(Window_height)*Window->Scaling[1]));

      Model_view.ortho(-Width/2,Width/2,-Height/2,Height/2,-100,100);
    }

    Model_view.translate(Translation.x,Translation.y,0);

//    glViewport(0,0,Window_width,Window_height);
//    glClearColor(0.8,0.8,0.8,1.0);
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    glUseProgram(Program1);
    glBindVertexArray(VAO1);

    glUniformMatrix4fv(0,1,GL_FALSE,Model_view.data());

    // num textures
    glUniform1i(20,Window->Map_layers_data.size());
    // background color
    glUniform3fv(21,1,(GLfloat*) &COLORS[WHITE]);

    for (unsigned int i=0;i<Window->Order_images.size();i++){
      glBindTextureUnit(i,Window->Map_layers_data[Window->Order_images[i]].Texture);
//      glBindTextureUnit(i,Window->Textures[i]);
    }

    glDrawArrays(GL_TRIANGLES,0,6);

    glBindVertexArray(0);
    glUseProgram(0);
  }
}

//HEA

void _gl_widget_pos::paintEvent(QPaintEvent *event)
{
  Q_UNUSED(event)

  QPainter Painter;
  Painter.begin(this);

  Painter.beginNativePainting();
  draw_objects();
  Painter.endNativePainting();


  if (Position==0){
    QPen Pen(Qt::black, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    QRect Rect_color=QRect((Window_width-Window->ZOI.x)/2,(Window_height-Window->ZOI.y)/2,Window->ZOI.x,Window->ZOI.y);
    Painter.setPen(Pen);
    Painter.drawRect(Rect_color);
  }

  Painter.end();
}

//HEA

void _gl_widget_pos::paintGL()
{
//  QPainter painter;
//  painter.begin(this);

//  painter.fillRect(0, 0, 128, 128, Qt::green);

//  painter.beginNativePainting();

//  draw_objects();

//  painter.endNativePainting();

//  painter.end();
}

//HEA

void _gl_widget_pos::resizeGL(int Width1, int Height1)
{
  Window_width=Width1;
  Window_height=Height1;
  glViewport(0,0,Width1,Height1);

  cout << "Position=" << Position << " W=" << Width1 << " H=" << Height1 << endl;

  if (Position==1) Window->compute_dimensions();
}

//HEA

void _gl_widget_pos::initialize_object()
{
  _shaders Shader;

  static const GLchar * P0_vs[]={
  #include "shaders/basic_pos.vert"
  };

  static const GLchar * P0_fs[]={
  #include "shaders/basic_pos.frag"
  };

  Program1=Shader.load_shaders(P0_vs,P0_fs);
  if (Program1==0){
    QMessageBox Message;
    Message.setText("Error with the GPU program basic_pos");
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
  Scale_drawing_mode=1.0;
  Translation=_vertex3f(0,0,0);

  Image_changed=true;
}

//HEA

void _gl_widget_pos::initializeGL()
{
  const GLubyte* strm;

  strm = glGetString(GL_VENDOR);
  cout << "Vendor: " << strm << "\n";
  strm = glGetString(GL_RENDERER);
  cout << "Renderer: " << strm << "\n";
  strm = glGetString(GL_VERSION);
  cout << "OpenGL Version: " << strm << "\n";

  if (strm[0] == '1'){
    cout << "Only OpenGL 1.X supported!\n";
    exit(-1);
    }

  strm = glGetString(GL_SHADING_LANGUAGE_VERSION);
  cout << "GLSL Version: " << strm << "\n";

  glewExperimental = GL_TRUE;
  int err = glewInit();
  if (GLEW_OK != err){
    // Problem: glewInit failed, something is seriously wrong.
    cout << "Error: " << glewGetErrorString(err) << "\n";

    QMessageBox MsgBox(this);
    QFont Font=MsgBox.font();
    Font.setPointSize(20);
    MsgBox.setFont(Font);
    MsgBox.setText("Error: There is not OpenGL drivers\n\nPlease, look for the information of your GPU (AMD, INTEL or NVIDIA) and install the drivers");
    MsgBox.exec();
    Window->close();
    }

  // este codigo es para limpiar un error que se produce con GLEW (inclido 1.10)
  // http://www.opengl.org/wiki/OpenGL_Loading_Library
  GLenum glErr;
  glErr = glGetError();
  while (glErr!=GL_NO_ERROR) glErr = glGetError();

  //
  int Max_texture_size=0;
  glGetIntegerv(GL_MAX_TEXTURE_SIZE, &Max_texture_size);
  std::cout << "Max texture size: " << Max_texture_size << "\n";

  int Max_texture_units=0;
  glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &Max_texture_units);
  std::cout << "Max texture units: " << Max_texture_units << "\n";

  int Max_texture_units_shader=0;
  glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &Max_texture_units_shader);
  std::cout << "Max texture units per shader: " << Max_texture_units_shader << "\n";

  Window_width=width();
  Window_height=height();

  initialize_object();
}

//HEA

void _gl_widget_pos::compute_position(QMouseEvent *Event)
{
//  cout << "x=" << Selection_position_X << " y=" << Selection_position_Y << endl;

  int Width=int(roundf(float(Window_width)*Window->Scaling[1]));
  int Height=int(roundf(float(Window_height)*Window->Scaling[1]));

  int xmin=-Width/2;
  int xmax=-xmin;
  int ymin=-Height/2;
  int ymax=-ymin;

  int Pos_x=(xmax-xmin)*Selection_position_X/Window_width+xmin-Translation.x;
  int Pos_y=(ymax-ymin)*Selection_position_Y/Window_height+ymin-Translation.y;


  Pos_x=Pos_x+Window->Initial_width/2;
  Pos_y=Pos_y+Window->Initial_height/2;

  if (Pos_x>=0 && Pos_x<Window->Initial_width && Pos_y>=0 && Pos_y<Window->Initial_height){
//    cout << "x1=" << Pos_x << " y1=" << Pos_y << endl;

    _window_ns::_update_mode Update_mode=_window_ns::_update_mode::UPDATE_MODE_NOTHING;

    if (Event->modifiers() & Qt::ShiftModifier){
      if (Event->button()==Qt::LeftButton){
        Update_mode=_window_ns::_update_mode::UPDATE_MODE_ADD;
      }
      else{
        if (Event->button()==Qt::RightButton){
          Update_mode=_window_ns::_update_mode::UPDATE_MODE_REPLACE;
        }
      }
    }
    else{
      if (Event->modifiers() & Qt::ControlModifier){
        Update_mode=_window_ns::_update_mode::UPDATE_MODE_REMOVE;
      }
    }

    Window->update_positions(Pos_x,Window->Initial_height-Pos_y,Update_mode);
  }
}
