/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

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
