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

#define _INPUT_C

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "attack.h"
#include "lvt.h"
#include "move.h"
#include "messages.h"
#include "stringlookups.h"

const unsigned int maxSearchCountdown = 1;

void doMoveKey(unsigned int c){
  moveDirection dir;
  
  switch (c){
    case KEY_UP:
      dir = UP;
      break;
    case KEY_DOWN:
      dir = DOWN;
      break;
    case KEY_RIGHT:
      dir = RIGHT;
      break;
    case KEY_LEFT:
      dir = LEFT;
      break;
    case KEY_UPLEFT:
      dir = UPLEFT;
      break;
    case KEY_UPRIGHT:
      dir = UPRIGHT;
      break;
    case KEY_DOWNLEFT:
      dir = DOWNLEFT;
      break;
    case KEY_DOWNRIGHT:
      dir = DOWNRIGHT;
      break;
  }
  
  switch(moveCreature(&player, dir)){
      creature *target = 0;
      coord3D creatureLoc;
      coord2D curPoint, newPoint;
      
    case MOVE_FAILED_WALL:
      addToMsgQueue(MOVE_WALL_MSG, false);
      break;
    case MOVE_FAILED_CREATURE:
  
      creatureLoc = getCreatureLocation(&player);
      curPoint.x = creatureLoc.x;
      curPoint.y = creatureLoc.y;
      newPoint = getSpaceDirectionCoordinates(curPoint, dir);
      target = getCreatureOccupant(dungeon[creatureLoc.level], newPoint.x, newPoint.y);
      if (sameFactions(target, &player)){
	if (!askQuestionYesNo(ATTACK_ALLIED_Q)){
	  addToMsgQueue(MOVE_CREATURE_MSG, false);
	  return;
	}
      }
      
      freeAction = false;
      switch(attack(&player, target)){
	case ATTACK_MISSED:
	  addToMsgQueue(ATTACK_MISSED_MSG, false);
	  break;
	case ATTACK_NODAMAGE:
	  addToMsgQueue(ATTACK_NODAMAGE_MSG, false);
	  break;
	case ATTACK_SUCCEEDED:
	  addToMsgQueue(ATTACK_SUCCEEDED_MSG, false);
	  break;
	case ATTACK_KILLED:
	  addToMsgQueue(ATTACK_KILLED_MSG, false);
	default:
	  break;
      }
      break;
    case MOVE_FAILED_DOOR:
      addToMsgQueue(MOVE_DOOR_MSG, false);
      break;
    case MOVE_SUCCESS:
      displayLevel(dungeon[getCreatureMapLevel(&player)]);
      break;
    default:
      break;
  }
  
  return;
}

void doOpenDoor(unsigned int c){
  unsigned int dir;
  coord3D doorPos;
  coord3D curPos;
  terrain doorPosTerrain;
  
  curPos = getCreatureLocation(&player);
  
  
  addToMsgQueue(WHICH_DIRECTION_MSG, false);
  procMsgQueue();
  
  dir = getch();
  clearMsg();
  
  switch(dir){
    case KEY_UP:
      doorPos.x = curPos.x;
      doorPos.y = curPos.y - 1;
      break;
    case KEY_DOWN:
      doorPos.x = curPos.x;
      doorPos.y = curPos.y + 1;
      break;
    case KEY_LEFT:
      doorPos.x = curPos.x - 1;
      doorPos.y = curPos.y;
      break;
    case KEY_RIGHT:
      doorPos.x = curPos.x + 1;
      doorPos.y = curPos.y;
      break;
    case KEY_UPLEFT:
      doorPos.x = curPos.x - 1;
      doorPos.y = curPos.y - 1;
      break;
    case KEY_UPRIGHT:
      doorPos.x = curPos.x + 1;
      doorPos.y = curPos.y - 1;
      break;
    case KEY_DOWNLEFT:
      doorPos.x = curPos.x - 1;
      doorPos.y = curPos.y + 1;
      break;
    case KEY_DOWNRIGHT:
      doorPos.x = curPos.x + 1;
      doorPos.y = curPos.y + 1;
      break;
    default:
      clearMsg();
      addToMsgQueue(NEVER_MIND_MSG, false);
      freeAction = true;
      return;
  }
  
  doorPos.level = curPos.level;
  
  doorPosTerrain = getMapSpaceTerrain(dungeon[doorPos.level], doorPos.x, doorPos.y);
  
  switch (c){
    case 'o':
      if (doorPosTerrain == OPENDOOR){
	addToMsgQueue(DOOR_ALREADY_OPEN_MSG, false);
	freeAction = true;
	return;
      } else if (doorPosTerrain != DOOR){
	addToMsgQueue(NO_DOOR_THERE_MSG, false);
	freeAction = true;
	return;
      } else {
	setMapSpaceTerrain(dungeon[doorPos.level], doorPos.x, doorPos.y, OPENDOOR);
      }
      break;
    case'c':
      if (doorPosTerrain == DOOR){
	addToMsgQueue(DOOR_ALREADY_CLOSED_MSG, false);
	freeAction = true;
	return;
      } else if (doorPosTerrain != OPENDOOR){
	addToMsgQueue(NO_DOOR_THERE_MSG, false);
	freeAction = true;
	return;
      } else {
	setMapSpaceTerrain(dungeon[doorPos.level], doorPos.x, doorPos.y, DOOR);
      }
      break;
  }
  
  
  return;
}

void doSearchDoors(unsigned int c, map map){
  static rng searchRng;
  static bool rngInitd = false;
  coord3D playerLoc;
  coord3D searchLoc;
  unsigned int searchLocIndex;
  unsigned int *searchCountdownPtr;
  unsigned int searchCountdown;
  terrain searchSquareTerrain;
  
  if (!rngInitd){
    initializeRNG(&searchRng);
    rngInitd = true;
  }
  
  playerLoc = getCreatureLocation(&player);
  
  // first we pick a # from 1-8, for each surrounding square
  // we don't care whether or not it's a square that could have a door (maybe fix that later)
  // then, we do a random likelihood of whether or not *that* square has a door
  searchLocIndex = uniformRandomRangeInt(&searchRng, 1, 8);
  switch (searchLocIndex){
    case 1:
      searchLoc.x = playerLoc.x - 1;
      searchLoc.y = playerLoc.y - 1;
      break;
    case 2:
      searchLoc.x = playerLoc.x;
      searchLoc.y = playerLoc.y - 1;
      break;
    case 3:
      searchLoc.x = playerLoc.x + 1;
      searchLoc.y = playerLoc.y - 1;
      break;
    case 4:
      searchLoc.x = playerLoc.x - 1;
      searchLoc.y = playerLoc.y;
      break;
    case 5:
      searchLoc.x = playerLoc.x + 1;
      searchLoc.y = playerLoc.y;
      break;
    case 6:
      searchLoc.x = playerLoc.x - 1;
      searchLoc.y = playerLoc.y + 1;
      break;
    case 7:
      searchLoc.x = playerLoc.x;
      searchLoc.y = playerLoc.y + 1;
      break;
    case 8:
      searchLoc.x = playerLoc.x + 1;
      searchLoc.y = playerLoc.y + 1;
      break;
    default:	// can't happen
      return;
      break;
  }
  
  searchSquareTerrain = getMapSpaceTerrain(dungeon[playerLoc.level], searchLoc.x, searchLoc.y);
  if (searchSquareTerrain == HIDDENDOOR){
    searchCountdownPtr = getTerrainData(dungeon[playerLoc.level], searchLoc.x, searchLoc.y, HIDDENDOOR);
    searchCountdown = *searchCountdownPtr;
    free(searchCountdownPtr);
    if (!searchCountdown){
      searchCountdown = uniformRandomRangeInt(&searchRng, 1, maxSearchCountdown);
    }
    searchCountdown--;
    if (!searchCountdown){
      setMapSpaceTerrain(dungeon[playerLoc.level], searchLoc.x, searchLoc.y, DOOR);
    }
    setTerrainData(dungeon[playerLoc.level], searchLoc.x, searchLoc.y, HIDDENDOOR, (void *)&searchCountdown);
  }
  
  return;
}

void doStairs(unsigned int c, map map){
  coord3D newPos;
  coord3D curPos;
  coord2D stairPos;
  
  curPos = getCreatureLocation(&player);
  
  if (c == '<'){
    if (getMapSpaceTerrain(dungeon[curPos.level], curPos.x, curPos.y) == UPSTAIR){
      if (curPos.level == 0){
	addToMsgQueue(UP_IS_EXIT_MSG, false);
	return;
      }
      newPos.level = curPos.level - 1;
      stairPos = findLevelDownstair(dungeon[curPos.level - 1]);
      newPos.x = stairPos.x;
      newPos.y = stairPos.y;
    } else {
      addToMsgQueue(CANNOT_UP_HERE_MSG, false);
      freeAction = true;
      return;
    }
  }
    
  if (c == '>'){
    if (getMapSpaceTerrain(dungeon[curPos.level], curPos.x, curPos.y) == DOWNSTAIR){
      newPos.level = curPos.level + 1;
      stairPos = findLevelUpstair(dungeon[curPos.level + 1]);
      newPos.x = stairPos.x;
      newPos.y = stairPos.y;
    } else {
      addToMsgQueue(CANNOT_DOWN_HERE_MSG, false);
      freeAction = true;
      return;
    }
  }
    
  clearCreatureOccupant(dungeon[curPos.level], curPos.x, curPos.y);
  setCreatureOccupant(dungeon[newPos.level], newPos.x, newPos.y, &player);
  setCreatureLocation(&player, newPos);
  updateRegionExploredState(dungeon[newPos.level], newPos.x, newPos.y, true);
    
  return;
  }