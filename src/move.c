#ifndef _MOVE_C
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
#endif