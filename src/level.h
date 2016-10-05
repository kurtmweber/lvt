#ifndef _LEVEL_H
#define _LEVEL_H

typedef enum terrain{
  WALL,
  FLOOR,
  DOOR,
  HIDDENDOOR,
  UPSTAIR,
  DOWNSTAIR,
  DOWNTON,
  ABBEY,
  THRONE
} terrain;

typedef struct mapSpace{
  terrain terrain;
  bool explored;
} mapSpace;

typedef mapSpace **level;

#endif