//**************************************************************************
//
// Domingo Martin Perandres© 2014-2017
// http://calipso.ugr.es/dmartin
// dmartin@ugr.es
//
// GPL
//**************************************************************************

#ifndef SHADERS_H
#define SHADERS_H

#include <string>
#include <GL/glew.h>
#include <iostream>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

using namespace std;

class _shaders
{
public:

  GLuint load_shaders(QString File_vertex_shader, QString File_fragment_shader, QString File_geometry_shader=QString());
  GLuint load_shaders(const GLchar **Vertex_shader_source,const GLchar **Fragment_shader_source);

protected:
  bool read_file(QString File_name,QString &Code);
  void show_error(GLint Shader);
};

#endif // SHADERS_H
