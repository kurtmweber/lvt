#ifndef _LEVEL_H
#define _LEVEL_H

typedef enum terrain{
  WALL,
  FLOOR,
  DOOR
} terrain;

typedef struct mapSpace{
  terrain terrain;
} mapSpace;

typedef mapSpace **level;

#endif