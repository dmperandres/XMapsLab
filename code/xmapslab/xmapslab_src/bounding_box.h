//LIC

#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <vector>
#include "vertex.h"
#include <random>
#include "object3D_wire.h"

class _bounding_box:public _object3D_wire
{
public:

  void	create(float Width1, float Height1, float Depth1);

protected:
  _vertex3f Bottom_left1;
  _vertex3f Top_right1;
};
#endif
