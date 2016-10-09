#ifndef _LEVEL_H
#define _LEVEL_H

#include "creature.h"

typedef enum terrain{
  WALL,
  PERMANENTROCK,
  FLOOR,
  DOOR,
  HIDDENDOOR,
  OPENDOOR,
  UPSTAIR,
  DOWNSTAIR,
  DOWNTON,
  ABBEY,
  THRONE
} terrain;

typedef enum objectClasses{
  WEAPON
} objectClasses;

typedef struct mapSpaceContents mapSpaceContents;

struct mapSpaceContents{
  mapSpaceContents *prev;
  objectClasses class;
  union {
    creature *creature;
  } contents;
  mapSpaceContents *next;
};
  

typedef struct mapSpace{
  terrain terrain;
  union {
    unsigned int searchCountdown;
  } terrainData;
  bool explored;
  mapSpaceContents *contents;
  creature *creatureOccupant;
  //plant *plantOccupant;
  void *plantOccupant;
} mapSpace;

#ifndef _MAP_TYPE
#define _MAP_TYPE
typedef mapSpace **level;
typedef level *map;
#endif

#endif