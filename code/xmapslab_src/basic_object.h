//**************************************************************************
//
// Domingo Martin Perandres© 2014-2017
// http://calipso.ugr.es/dmartin
// dmartin@ugr.es
//
// GPL
//**************************************************************************

#ifndef BASIC_OBJECT_H
#define BASIC_OBJECT_H

#include <vector>
#include "vertex.h"
#include <GL/glew.h>
#include <QMatrix4x4>
#include "pile.h"
#include "material.h"

class _object_management;

using namespace std;

class _basic_object
{
public:
  static _pile Pile;
  static vector<_material> Vec_materials;

  void add_symbol(_basic_object* Basic_object1){Vec_objects.push_back(Basic_object1);}
  virtual void draw(){}

protected:
  vector<_basic_object*> Vec_objects;
};

#endif
