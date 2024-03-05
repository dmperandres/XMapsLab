/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "object3D.h"

/*************************************************************************/

void _object3D::compute_triangles_normals()
{
  _planef Plane1;

  for (unsigned int i=0;i<Triangles.size();i++){
    if (Plane1.compute_coefficients(Vertices[Triangles[i].x],Vertices[Triangles[i].y],Vertices[Triangles[i].z])!=0){
      std::cout << "Error en Triangle " << i << std::endl;
      Triangles[i].show_values();
      Vertices[Triangles[i].x].show_values();
      Vertices[Triangles[i].y].show_values();
      Vertices[Triangles[i].z].show_values();
      }
    Triangles_normals[i]=Plane1.normal();
  }
}

/*************************************************************************/

void _object3D::compute_vertices_normals()
{
  int Pos;
  std::vector<int> Num_normals;

  Vertices_normals.resize(Vertices.size());
  Num_normals.resize(Vertices.size());

  for (unsigned int i=0;i<Triangles.size();i++){
    for (unsigned int j=0;j<3;j++){
      Pos=Triangles[i][j];
      Vertices_normals[Pos]+=Triangles_normals[i];
      Num_normals[Pos]++;
    }
  }
  for (unsigned int i=0;i<Vertices_normals.size();i++){
    Vertices_normals[i]/=Num_normals[i];
    Vertices_normals[i].normalize();
  }
}

/*************************************************************************/

void _object3D::bounding_box()
{
  Pos_min=_vertex3f(1e8,1e8,1e8);
  Pos_max=_vertex3f(-1e8,-1e8,-1e8);

  for (unsigned int i=0;i<Vertices.size();i++){
    if (Vertices[i].x<Pos_min.x) Pos_min.x=Vertices[i].x;
    if (Vertices[i].y<Pos_min.y) Pos_min.y=Vertices[i].y;
    if (Vertices[i].z<Pos_min.z) Pos_min.z=Vertices[i].z;

    if (Vertices[i].x>Pos_max.x) Pos_max.x=Vertices[i].x;
    if (Vertices[i].y>Pos_max.y) Pos_max.y=Vertices[i].y;
    if (Vertices[i].z>Pos_max.z) Pos_max.z=Vertices[i].z;
  }
}
