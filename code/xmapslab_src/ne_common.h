/*************************************************************************
Copyright (c) 2022, 2023, 2024 Domingo Martin Perandrés (dmartin@ugr.es)

This software is under GPL v3 license

Please refer to the project web site to get all the information

https://calipso.ugr.es/xmapslog.org

In case that you use this software, include a reference to this paper: PAPER_XXX

*************************************************************************/

#ifndef NE_COMMON_H
#define NE_COMMON_H

#include <QString>

namespace _ne_common_ns {
  const int SCENE_ORIGIN=-200;
  const int SCENE_WIDTH=6000;

  const int NUM_MAX_ROWS=10;
  const int NUM_MAX_COLS=10;

  const int MIN_INDEX_GRID_LINES=-10;
  const int MAX_INDEX_GRID_LINES=50;
  const int MAX_LINE_VALUE=10000;

//  const unsigned char LINE_RED=200;
//  const unsigned char LINE_GREEN=200;
//  const unsigned char LINE_BLUE=200;

  // for the size of the block
  const unsigned int NUM_CHARS_LINE_BLOCK=18;
  // for the space between blocks
  const unsigned int NUM_CHARS_SPACE_BLOCK=20;
  // For the height of the block
  const unsigned int NUM_LINES_BLOCK=5;

  const float STEP_WIDTH_FACTOR=1.5;
  const float STEP_HEIGHT_FACTOR=2;

  const int STEP_HEIGHT_DEFAULT=150;
  const int STEP_WIDTH_DEFAULT=300;

  const int CHANNEL_WIDTH_OFFSET=5;
  const int CHANNEL_HEIGHT_OFFSET=5; // 60
  const int WIRE_OFFSET=5;

  const int RADIUS=5;
  const int MARGIN=2;

  struct _color{
    unsigned char Red;
    unsigned char Green;
    unsigned char Blue;
  };

  const _color Colors[]={{255,0,0},
{0,200,0},
{0,0,255},
{0,200,200},
{200,0,200}};
  const int MAX_NUM_COLORS=5;
  const _color Gray={200,200,200};

}
#endif
