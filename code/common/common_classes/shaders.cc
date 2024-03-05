//**************************************************************************
//
// Domingo Martin Perandres© 2014-2017
// http://calipso.ugr.es/dmartin
// dmartin@ugr.es
//
// GPL
//**************************************************************************

#include "shaders.h"

/*************************************************************************/

bool _shaders::read_file(QString File_name, QString &Code)
{
  QFile File(File_name);
  if (!File.open(QIODevice::ReadOnly | QIODevice::Text)){
    QMessageBox::information(0,"Error in shader",File.errorString());
    return false;
  }
  QTextStream Input(&File);
  Code=Input.readAll();
  File.close();
  return true;
}

/*************************************************************************/

void _shaders::show_error(GLint Shader)
{
  GLint Max_length = 0;
  glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &Max_length);

  // The maxLength includes the NULL character
  std::vector<GLchar> Error_log(Max_length);
  glGetShaderInfoLog(Shader,Max_length,&Max_length,&Error_log[0]);
  string Error(&Error_log[0]);
  cout << "Error: " << Error << endl;
}

/*************************************************************************/

GLuint _shaders::load_shaders(QString File_vertex_shader,QString File_fragment_shader,QString File_geometry_shader)
{
  GLuint Vertex_shader;
  GLuint Fragment_shader;
  GLuint Geometry_shader;
  GLuint Program;
  GLint  Vertexshader_compiled, Fragment_shader_compiled, Geometry_shader_compiled;
  GLint  Shaders_compiled;
  bool Geometry_shader_active=false;

  // Read the files
  QString Vertex_shader_source;
  read_file(File_vertex_shader,Vertex_shader_source);
//  check_opengl_error();

  QString Fragment_shader_source;
  read_file(File_fragment_shader,Fragment_shader_source);

  QString Geometry_shader_source;
  if (File_geometry_shader!=""){
    read_file(File_geometry_shader,Geometry_shader_source);
    Geometry_shader_active=true;
  }

  // Create the shaders
  Vertex_shader=glCreateShader(GL_VERTEX_SHADER);
  Fragment_shader=glCreateShader(GL_FRAGMENT_SHADER);

  if (Geometry_shader_active) Geometry_shader=glCreateShader(GL_GEOMETRY_SHADER);

  // Assign the source code
  string Str=Vertex_shader_source.toStdString();
  const char *Aux=Str.c_str();
  glShaderSource(Vertex_shader,1,(const GLchar **) &Aux,NULL);

  Str=Fragment_shader_source.toStdString();
  const char *Aux1=Str.c_str();
  glShaderSource(Fragment_shader,1,(const GLchar **) &Aux1,NULL);

  if (Geometry_shader_active){
    Str=Geometry_shader_source.toStdString();
    const char *Aux2=Str.c_str();
    glShaderSource(Geometry_shader,1,(const GLchar **) &Aux2,NULL);
  }

  // Compiling the code
  glCompileShader(Vertex_shader);
  glGetShaderiv(Vertex_shader, GL_COMPILE_STATUS, &Vertexshader_compiled);
  if (Vertexshader_compiled==GL_FALSE){
    QMessageBox::information(0,"Error","Error compiling the vertex shader");
    show_error(Vertex_shader);
    return(0);
  }

  if (Geometry_shader_active){
    glCompileShader(Geometry_shader);
    glGetShaderiv(Geometry_shader, GL_COMPILE_STATUS, &Geometry_shader_compiled);
    if (Geometry_shader_compiled==GL_FALSE){
      QMessageBox::information(0,"Error","Error compiling the geometry shader");
      show_error(Geometry_shader);
      return(0);
    }
  }

  glCompileShader(Fragment_shader);
  glGetShaderiv(Fragment_shader, GL_COMPILE_STATUS, &Fragment_shader_compiled);
  if (Fragment_shader_compiled==GL_FALSE){
    QMessageBox::information(0,"Error","Error compiling the fragment shader");
    show_error(Fragment_shader);
    return(0);
  }

  // Create the program
  Program=glCreateProgram();

  // Attach
  glAttachShader(Program,Vertex_shader);
  glAttachShader(Program,Fragment_shader);
  if (Geometry_shader_active) glAttachShader(Program,Geometry_shader);

  // geometry shader
//  if (File_geometry_shader!=""){
//    QString Geometry_shader_source;
//    read_file(File_geometry_shader,Geometry_shader_source);
//    Geometry_shader=glCreateShader(GL_GEOMETRY_SHADER);

//    Str=Geometry_shader_source.toStdString();
//    const char *Aux1=Str.c_str();
//    glShaderSource(Geometry_shader,1,(const GLchar **) &Aux1,NULL);

//    glCompileShader(Geometry_shader);
//    glGetShaderiv(Geometry_shader, GL_COMPILE_STATUS, &Geometry_shader_compiled);
//    if (Geometry_shader_compiled==GL_FALSE){
//      cout << "Error compiling the geometry shader" << endl;
//      return(0);
//    }

//    glAttachShader(Program,Geometry_shader);
//  }

  // Link
  glLinkProgram(Program);
  glGetProgramiv(Program, GL_LINK_STATUS, &Shaders_compiled);
  if (Shaders_compiled==GL_FALSE){
    QMessageBox::information(0,"Error","Error linking the shaders");
    return(0);
  }

  return(Program);
}

/*************************************************************************/

GLuint _shaders::load_shaders(const GLchar **Vertex_shader_source, const GLchar **Fragment_shader_source)
{
  GLuint Vertex_shader;
  GLuint Fragment_shader;
  GLuint Program;
  GLint  Vertices_shader_compiled, Fragment_shader_compiled;
  GLint  Shaders_compiled;

  // Create the shader
  Vertex_shader=glCreateShader(GL_VERTEX_SHADER);
  Fragment_shader=glCreateShader(GL_FRAGMENT_SHADER);

  // Assign the source code
  glShaderSource(Vertex_shader,1,Vertex_shader_source,nullptr);

  glShaderSource(Fragment_shader,1,Fragment_shader_source,nullptr);

  // Compiling
  glCompileShader(Vertex_shader);
  // Check
  glGetShaderiv(Vertex_shader, GL_COMPILE_STATUS, &Vertices_shader_compiled);
  if (Vertices_shader_compiled==GL_FALSE){
    cout << "Error compiling the vertex shader" << endl;
    show_error(Vertex_shader);
    return(0);
  }
//  print_shader_info_log(Vertex_shader);

  glCompileShader(Fragment_shader);
  // Check
  glGetShaderiv(Fragment_shader, GL_COMPILE_STATUS, &Fragment_shader_compiled);
  if (Fragment_shader_compiled==GL_FALSE){
    cout << "Error compiling the fragment shader" << endl;
    show_error(Fragment_shader);
    return(0);
  }
//  print_shader_info_log(Fragment_shader);

  // Create the program
  Program=glCreateProgram();

  // Attach
  glAttachShader(Program,Vertex_shader);
  glAttachShader(Program,Fragment_shader);

  // Link
  glLinkProgram(Program);
//  print_program_info_log(Program);
  // check
  glGetProgramiv(Program, GL_LINK_STATUS, &Shaders_compiled);
  if (Shaders_compiled==GL_FALSE){
    cout << "Error linking" << endl;
    return(0);
  }

  return(Program);
}

