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

#ifndef _MOVE_H
#define _MOVE_H

#include <ncurses.h>

#define KEY_UPLEFT KEY_HOME
#define KEY_UPRIGHT KEY_PPAGE
#define KEY_DOWNLEFT KEY_END
#define KEY_DOWNRIGHT KEY_NPAGE
#define KEY_STAY KEY_DC

typedef enum moveOutcome{
  MOVE_SUCCESS,
  MOVE_FAILED_WALL,
  MOVE_FAILED_CREATURE,
  MOVE_FAILED_DOOR
} moveOutcome;

typedef enum moveDirection{
  UPLEFT,
  UP,
  UPRIGHT,
  LEFT,
  NOMOVE,
  RIGHT,
  DOWNLEFT,
  DOWN,
  DOWNRIGHT
} moveDirection;

#endif