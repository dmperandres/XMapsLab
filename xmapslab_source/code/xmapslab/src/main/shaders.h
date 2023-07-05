/*************************************************************************
Copyright (c) 2022, 2023 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: XXX

*************************************************************************/

#ifndef SHADERS_H
#define SHADERS_H

#include <string>
#include <GL/glew.h>
#include <iostream>
#include <QString>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

/*************************************************************************/

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
