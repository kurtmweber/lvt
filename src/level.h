#ifndef _LEVEL_H
#define _LEVEL_H

typedef enum terrain{
  WALL,
  FLOOR
} terrain;

typedef struct mapSpace{
  terrain terrain;
} mapSpace;

typedef mapSpace **level;

#endif