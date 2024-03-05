/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#include "bounding_box.h"

/*************************************************************************/

void _bounding_box::create(float Width1, float Height1, float Depth1)
{
  // Clear vectors
  Vertices.clear();

  Vertices_drawarray.clear();

  Vertices.resize(8);

  Vertices[0].x=-Width1/2;
  Vertices[0].y=-Height1/2;
  Vertices[0].z=Depth1/2;

  Vertices[1].x=Width1/2;
  Vertices[1].y=-Height1/2;
  Vertices[1].z=Depth1/2;

  Vertices[2].x=-Width1/2;
  Vertices[2].y=Height1/2;
  Vertices[2].z=Depth1/2;

  Vertices[3].x=Width1/2;
  Vertices[3].y=Height1/2;
  Vertices[3].z=Depth1/2;

  Vertices[4].x=-Width1/2;
  Vertices[4].y=-Height1/2;
  Vertices[4].z=-Depth1/2;

  Vertices[5].x=Width1/2;
  Vertices[5].y=-Height1/2;
  Vertices[5].z=-Depth1/2;

  Vertices[6].x=-Width1/2;
  Vertices[6].y=Height1/2;
  Vertices[6].z=-Depth1/2;

  Vertices[7].x=Width1/2;
  Vertices[7].y=Height1/2;
  Vertices[7].z=-Depth1/2;

  // drawarrays
  //
  Vertices_drawarray.resize(12);
  int Position=0;
  for (unsigned int i=0;i<4;i++){
    Vertices_drawarray[Position++]=Vertices[i];
    Vertices_drawarray[Position++]=Vertices[i+4];
  }
}

