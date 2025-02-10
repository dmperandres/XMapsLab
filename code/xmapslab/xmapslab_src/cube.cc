//LIC

#include "cube.h"

//HEA

_cube::_cube()
{
  // vertices
  Vertices.resize(8);
  Vertices[0]=_vertex3f(-0.5,0,0.5);
  Vertices[1]=_vertex3f(0.5,0,0.5);
  Vertices[2]=_vertex3f(-0.5,1,0.5);
  Vertices[3]=_vertex3f(0.5,1,0.5);
  Vertices[4]=_vertex3f(-0.5,0,-0.5);
  Vertices[5]=_vertex3f(0.5,0,-0.5);
  Vertices[6]=_vertex3f(-0.5,1,-0.5);
  Vertices[7]=_vertex3f(0.5,1,-0.5);

  // triangles
  Triangles.resize(12);
  Triangles[0]=_vertex3i(2,0,1);
  Triangles[1]=_vertex3i(1,3,2);
  Triangles[2]=_vertex3i(3,1,5);
  Triangles[3]=_vertex3i(5,7,3);
  Triangles[4]=_vertex3i(7,5,4);
  Triangles[5]=_vertex3i(4,6,7);
  Triangles[6]=_vertex3i(6,4,0);
  Triangles[7]=_vertex3i(0,2,6);
  Triangles[8]=_vertex3i(0,4,5);
  Triangles[9]=_vertex3i(5,1,0);
  Triangles[10]=_vertex3i(6,2,3);
  Triangles[11]=_vertex3i(3,7,6);

  // vertices colors
  Vertices_colors.resize(8);
  Vertices_colors[0]=_vertex3f(1,0,0);
  Vertices_colors[1]=_vertex3f(0,1,0);
  Vertices_colors[2]=_vertex3f(0,0,1);
  Vertices_colors[3]=_vertex3f(0,1,1);
  Vertices_colors[4]=_vertex3f(1,0,1);
  Vertices_colors[5]=_vertex3f(1,1,0);
  Vertices_colors[6]=_vertex3f(0.5,0.5,0.5);
  Vertices_colors[7]=_vertex3f(0.4,0.5,0.6);

  // vertices normals
  _vertex3f Normal;
  Vertices_normals.resize(8);
  Normal=_vertex3f(-1,-1,1);
  Vertices_normals[0]=Normal.normalize();
  Normal=_vertex3f(1,-1,1);
  Vertices_normals[1]=Normal.normalize();
  Normal=_vertex3f(-1,1,1);
  Vertices_normals[2]=Normal.normalize();
  Normal=_vertex3f(1,1,1);
  Vertices_normals[3]=Normal.normalize();
  Normal=_vertex3f(-1,-1,-1);
  Vertices_normals[4]=Normal.normalize();
  Normal=_vertex3f(1,-1,-1);
  Vertices_normals[5]=Normal.normalize();
  Normal=_vertex3f(-1,1,-1);
  Vertices_normals[6]=Normal.normalize();
  Normal=_vertex3f(1,1,-1);
  Vertices_normals[7]=Normal.normalize();

  // triangles normals
  Triangles_normals.resize(12);
  Triangles_normals[0]=_vertex3f(0,0,1);
  Triangles_normals[1]=_vertex3f(0,0,1);
  Triangles_normals[2]=_vertex3f(1,0,0);
  Triangles_normals[3]=_vertex3f(1,0,0);
  Triangles_normals[4]=_vertex3f(0,0,-1);
  Triangles_normals[5]=_vertex3f(0,0,-1);
  Triangles_normals[6]=_vertex3f(-1,0,0);
  Triangles_normals[7]=_vertex3f(-1,0,0);
  Triangles_normals[8]=_vertex3f(0,-1,0);
  Triangles_normals[9]=_vertex3f(0,-1,0);
  Triangles_normals[10]=_vertex3f(0,1,0);
  Triangles_normals[11]=_vertex3f(0,1,0);


  // create drawarrays
  // vertices
  Vertices_drawarray.resize(Triangles.size()*3);
  for (unsigned int i=0;i<Triangles.size();i++){
    Vertices_drawarray[i*3]=Vertices[Triangles[i]._0];
    Vertices_drawarray[i*3+1]=Vertices[Triangles[i]._1];
    Vertices_drawarray[i*3+2]=Vertices[Triangles[i]._2];
  }
  // vertices colors
  Vertices_colors_drawarray.resize(Triangles.size()*3);
  for (unsigned int i=0;i<Triangles.size();i++){
    Vertices_colors_drawarray[i*3]=Vertices_colors[Triangles[i]._0];
    Vertices_colors_drawarray[i*3+1]=Vertices_colors[Triangles[i]._1];
    Vertices_colors_drawarray[i*3+2]=Vertices_colors[Triangles[i]._2];
  }
  // vertices triangle normals
  Vertices_triangles_normals_drawarray.resize(Triangles.size()*3);
  for (unsigned int i=0;i<Triangles.size();i++){
    Vertices_triangles_normals_drawarray[i*3]=Triangles_normals[i];
    Vertices_triangles_normals_drawarray[i*3+1]=Triangles_normals[i];
    Vertices_triangles_normals_drawarray[i*3+2]=Triangles_normals[i];
  }

  // vertices normals
  // the cube must appear like a cube not like a sphere
  Vertices_normals_drawarray.resize(Triangles.size()*3);
  for (unsigned int i=0;i<Vertices_triangles_normals_drawarray.size();i++){
    Vertices_normals_drawarray[i]=Vertices_triangles_normals_drawarray[i];
  }

  // texture coordinates
  Vertices_texture_coordinates_drawarray.resize(36);
  // face 0
  Vertices_texture_coordinates_drawarray[0]=_vertex2f(0,1);
  Vertices_texture_coordinates_drawarray[1]=_vertex2f(0,0);
  Vertices_texture_coordinates_drawarray[2]=_vertex2f(1,0);
  // face 1
  Vertices_texture_coordinates_drawarray[3]=_vertex2f(1,0);
  Vertices_texture_coordinates_drawarray[4]=_vertex2f(1,1);
  Vertices_texture_coordinates_drawarray[5]=_vertex2f(0,1);
  // face 2
  Vertices_texture_coordinates_drawarray[6]=_vertex2f(0,1);
  Vertices_texture_coordinates_drawarray[7]=_vertex2f(0,0);
  Vertices_texture_coordinates_drawarray[8]=_vertex2f(1,0);
  // face 3
  Vertices_texture_coordinates_drawarray[9]=_vertex2f(1,0);
  Vertices_texture_coordinates_drawarray[10]=_vertex2f(1,1);
  Vertices_texture_coordinates_drawarray[11]=_vertex2f(0,1);
  // face 4
  Vertices_texture_coordinates_drawarray[12]=_vertex2f(0,1);
  Vertices_texture_coordinates_drawarray[13]=_vertex2f(0,0);
  Vertices_texture_coordinates_drawarray[14]=_vertex2f(1,0);
  // face 5
  Vertices_texture_coordinates_drawarray[15]=_vertex2f(1,0);
  Vertices_texture_coordinates_drawarray[16]=_vertex2f(1,1);
  Vertices_texture_coordinates_drawarray[17]=_vertex2f(0,1);
  // face 6
  Vertices_texture_coordinates_drawarray[18]=_vertex2f(0,1);
  Vertices_texture_coordinates_drawarray[19]=_vertex2f(0,0);
  Vertices_texture_coordinates_drawarray[20]=_vertex2f(1,0);
  // face 7
  Vertices_texture_coordinates_drawarray[21]=_vertex2f(1,0);
  Vertices_texture_coordinates_drawarray[22]=_vertex2f(1,1);
  Vertices_texture_coordinates_drawarray[23]=_vertex2f(0,1);
  // face 8
  Vertices_texture_coordinates_drawarray[24]=_vertex2f(0,1);
  Vertices_texture_coordinates_drawarray[25]=_vertex2f(0,0);
  Vertices_texture_coordinates_drawarray[26]=_vertex2f(1,0);
  // face 9
  Vertices_texture_coordinates_drawarray[27]=_vertex2f(1,0);
  Vertices_texture_coordinates_drawarray[28]=_vertex2f(1,1);
  Vertices_texture_coordinates_drawarray[29]=_vertex2f(0,1);
  // face 10
  Vertices_texture_coordinates_drawarray[30]=_vertex2f(0,1);
  Vertices_texture_coordinates_drawarray[31]=_vertex2f(0,0);
  Vertices_texture_coordinates_drawarray[32]=_vertex2f(1,0);
  // face 11
  Vertices_texture_coordinates_drawarray[33]=_vertex2f(1,0);
  Vertices_texture_coordinates_drawarray[34]=_vertex2f(1,1);
  Vertices_texture_coordinates_drawarray[35]=_vertex2f(0,1);
}

//*************************************************************************
//
//*************************************************************************

//void _cube::draw()
//{
//  glUniformMatrix4fv(10,1,GL_FALSE,Pile.top());
//  glUniformMatrix3fv(13,1,GL_FALSE,Pile.top_matrix().normalMatrix().data());
//  glDrawArrays(GL_TRIANGLES,Initial_position,Num_vertices);
//}
