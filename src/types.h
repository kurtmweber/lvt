/*  This file is part of Lavender Throne.
 *  Copyright 2016 by Kurt Weber
 *
 *  Lavender Throne is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Lavender Throne is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Lavender Throne.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _TYPES_H
#define _TYPES_H

#include <stdbool.h>

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

typedef struct moveMatrix{
  int x;
  int y;
} moveMatrix;

typedef enum color{
  RED,
  WHITE,
  BRIGHTWHITE
} color;

typedef struct gameStatus{
  unsigned int turnNum;
  unsigned int speedCounter;
  unsigned int playerSpeed;
} gameStatus;

typedef struct msgQueueEntry{
  bool confirm;
  char *msg;
} msgQueueEntry;

typedef struct screenDisplayCell{
  char dispChar;
  bool hasAttrs;
  unsigned int attrs;
} screenDisplayCell;

#endif