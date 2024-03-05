/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef OBJECT3D_H
#define OBJECT3D_H

#include <vector>
#include "vertex.h"
//#include <GL/gl.h>
#include <random>

class _object3D{
public:
  std::vector<_vertex3f> Vertices;
  std::vector<_vertex3i> Triangles;
  std::vector<_vertex3f> Vertices_normals;
  std::vector<_vertex3f> Triangles_normals;
  std::vector<_vertex3f> Vertices_colors;
  std::vector<_vertex3f> Triangles_colors;
  std::vector<_vertex2f> Vertices_texture_coordinates;
//  std::vector<_vertex3f> Vertices_tangents;
//  std::vector<_vertex3f> Vertices_bitangents;

  std::vector<_vertex3f> Vertices_drawarray;
  std::vector<_vertex3f> Vertices_colors_drawarray;
  std::vector<_vertex3f> Vertices_triangles_normals_drawarray;
  std::vector<_vertex3f> Vertices_normals_drawarray;
  std::vector<_vertex2f> Vertices_texture_coordinates_drawarray;
//  std::vector<_vertex3f> Vertices_tangents_drawarray;
//  std::vector<_vertex3f> Vertices_bitangents_drawarray;

  void compute_triangles_normals();
  void compute_vertices_normals();
  void bounding_box();

protected:
  _vertex3f Pos_min;
  _vertex3f Pos_max;
};
#endif
