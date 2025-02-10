#include "basic_object3d.h"


using namespace std;

_basic_object3d::_basic_object3d()
{
  Initial_position=0;
  Num_vertices=0;
}

//*************************************************************************
//
//*************************************************************************

void _basic_object3d::update_drawing_data(int Initial_position1,int Num_vertices1)
{
  Initial_position=Initial_position1;
  Num_vertices=Num_vertices1;
}


//*************************************************************************
//
//*************************************************************************

void _basic_object3d::compute_triangles_normals()
{
_planef Plane1;
//bool Error=false;

Triangles_normals.resize(Triangles.size());
for (unsigned int i=0;i<Triangles.size();i++)
  {
  if (Plane1.compute_coefficients(Vertices[Triangles[i]._0],Vertices[Triangles[i]._1],Vertices[Triangles[i]._2])!=0)
    {
    printf("Error en Triangle %d\n",i);
    Triangles[i].show_values();
    Vertices[Triangles[i].x].show_values();
    Vertices[Triangles[i].y].show_values();
    Vertices[Triangles[i].z].show_values();
//    Error=true;
    }
  Triangles_normals[i]=Plane1.normal();
  }
//if (Error){
//  printf("Error: la normal de la Triangle no puede ser calculada Fichero=%s Linea=%d\n",__FILE__,__LINE__);
//  }
}


//*************************************************************************
// 030425
// compute normals of vertices
// We create a vector of vertex3f, the normal, and an int value, the number
// of normal values that are asigned for each vertex.
// For each face, for each vertex of the face, the normal is adedd to the
// corresponding vertex
// The number of normals is incremented.
// In this way, all the faces that share a vertex add its normal value
//*************************************************************************

void _basic_object3d::compute_vertices_normals()
{
  int Pos;
  vector<int> Num_normals;

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

