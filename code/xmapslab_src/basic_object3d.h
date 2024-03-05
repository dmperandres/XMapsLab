//**************************************************************************
//
// Domingo Martin Perandres© 2014-2017
// http://calipso.ugr.es/dmartin
// dmartin@ugr.es
//
// GPL
//**************************************************************************

#ifndef BASIC_OBJECT3D_H
#define BASIC_OBJECT3D_H

#include "basic_object.h"

using namespace std;

class _basic_object3d: public _basic_object
{
public:
  vector<_vertex3f> Vertices;
  vector<_vertex3f> Vertices_colors;
  vector<_vertex3f> Vertices_normals;
  vector<_vertex2f> Vertices_texture_coordinates;

  vector<_vertex3i> Triangles;
  vector<_vertex3f> Triangles_colors;
  vector<_vertex3f> Triangles_normals;

  vector<_vertex3f> Vertices_drawarray;
  vector<_vertex3f> Vertices_colors_drawarray;
  vector<_vertex3f> Vertices_normals_drawarray;
  vector<_vertex3f> Vertices_triangles_normals_drawarray;
  vector<_vertex2f> Vertices_texture_coordinates_drawarray;

  _basic_object3d();
  
  void draw(){};
  int num_vertices_drawarray(){return Vertices_drawarray.size();};
  void update_drawing_data(int Initial_position1, int Num_vertices1);
  void compute_triangles_normals();
  void compute_vertices_normals();

protected:
  int Initial_position;
  int Num_vertices;
};

#endif
