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

class _shaders
{
public:

  GLuint load_shaders(const GLchar **Vertex_shader_source,const GLchar **Fragment_shader_source);

protected:
  bool  read_file(QString File_name,QString &Code);
};

#endif // SHADERS_H
