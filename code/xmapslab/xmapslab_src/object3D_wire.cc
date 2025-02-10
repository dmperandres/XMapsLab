//LIC

#include "object3D_wire.h"

//HEA

void _object3D_wire::bounding_box()
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
