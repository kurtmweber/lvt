#ifndef _TYPES_H
#define _TYPES_H

#include "pcg_basic.h"

typedef pcg32_random_t rng;

typedef enum coin{
  HEADS,
  TAILS
} coin;

typedef struct coord2D{
  unsigned int x;
  unsigned int y;
} coord2D;

typedef struct coord3D{
  unsigned int x;
  unsigned int y;
  unsigned int level;
} coord3D;

#endif