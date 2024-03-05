/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef OBJECT3D_WIRE_H
#define OBJECT3D_WIRE_H

#include <vector>
#include "vertex.h"
//#include <GL/gl.h>
#include <random>

class _object3D_wire{
public:
  std::vector<_vertex3f> Vertices;

  std::vector<_vertex3f> Vertices_drawarray;
  std::vector<_vertex3f> Vertices_colors_drawarray;

  void bounding_box();

protected:
  _vertex3f Pos_min;
  _vertex3f Pos_max;
};
#endif
