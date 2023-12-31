/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#include "shaders.h"

//**************************************************************************
//
//***************************************************************************

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

//**************************************************************************
//
//***************************************************************************

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
    std::cout << "Error compiling the vertex shader" << std::endl;
    return(0);
  }
//  print_shader_info_log(Vertex_shader);

  glCompileShader(Fragment_shader);
  // Check
  glGetShaderiv(Fragment_shader, GL_COMPILE_STATUS, &Fragment_shader_compiled);
  if (Fragment_shader_compiled==GL_FALSE){
    std::cout << "Error compiling the fragment shader" << std::endl;
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
    std::cout << "Error linking" << std::endl;
    return(0);
  }

  return(Program);
}

