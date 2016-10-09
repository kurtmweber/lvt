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

#define _MOVE_C

#include <ncurses.h>
#include "lvt.h"
#include "move.h"

moveOutcome moveCreature(creature *creature, moveDirection dir, map map){
  coord3D curPos;
  coord3D newPos;
  
  curPos = getCreatureLocation(creature);
  
  switch (dir){
    case UP:
      newPos.x = curPos.x;
      newPos.y = curPos.y - 1;
      break;
    case DOWN:
      newPos.x = curPos.x;
      newPos.y = curPos.y + 1;
      break;
    case LEFT:
      newPos.x = curPos.x - 1;
      newPos.y = curPos.y;
      break;
    case RIGHT:
      newPos.x = curPos.x + 1;
      newPos.y = curPos.y;
      break;
    case UPLEFT:
      newPos.y = curPos.y - 1;
      newPos.x = curPos.x - 1;
      break;
    case UPRIGHT:
      newPos.y = curPos.y - 1;
      newPos.x = curPos.x + 1;
      break;
    case DOWNLEFT:
      newPos.y = curPos.y + 1;
      newPos.x = curPos.x - 1;
      break;
    case DOWNRIGHT:
      newPos.y = curPos.y + 1;
      newPos.x = curPos.x + 1;
      break;
  }
  
  switch (getMapSpaceTerrain(map[curPos.level], newPos.x, newPos.y)){
    case WALL:
    case PERMANENTROCK:
    case HIDDENDOOR:
      return MOVE_FAILED_WALL;
    case DOOR:
      return MOVE_FAILED_DOOR;
    default:
      break;
  }
  
  if (hasCreatureOccupant(map[curPos.level], newPos.x, newPos.y)){
    return MOVE_FAILED_CREATURE;
  }
  
  newPos.level = curPos.level;
  
  clearCreatureOccupant(map[curPos.level], curPos.x, curPos.y);
  setCreatureOccupant(map[curPos.level], newPos.x, newPos.y, creature);
  setCreatureLocation(creature, newPos);
  updateRegionExploredState(map[curPos.level], newPos.x, newPos.y, true);
  
  return MOVE_SUCCESS;
}