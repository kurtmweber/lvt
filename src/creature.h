#ifndef _CREATURE_H
#define _CREATURE_H

#include "types.h"

typedef struct creature{
  char *name;
  bool isPlayer;
  coord3D location;
  char dispChar;
} creature;

#endif