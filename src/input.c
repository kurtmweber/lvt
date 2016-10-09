#ifndef _INPUT_C
#define _INPUT_C

#include <stdlib.h>
#include "lvt.h"
#include "move.h"
#include "messages.h"

const unsigned int maxSearchCountdown = 10;

void doMoveKey(unsigned int c, map map){
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
  
  switch(moveCreature(&player, dir, map)){
    case MOVE_FAILED_WALL:
      displayMsgNoWait(MOVE_WALL_MSG);
      break;
    case MOVE_FAILED_CREATURE:
      displayMsgNoWait(MOVE_CREATURE_MSG);
      break;
    case MOVE_FAILED_DOOR:
      displayMsgNoWait(MOVE_DOOR_MSG);
      break;
    case MOVE_SUCCESS:
      displayLevel(map[getCreatureMapLevel(&player)]);
      break;
  }
  
  return;
}

void doOpenDoor(unsigned int c, map map){
  unsigned int dir;
  coord3D doorPos;
  coord3D curPos;
  terrain doorPosTerrain;
  
  curPos = getCreatureLocation(&player);
  
  
  displayMsgNoWait(WHICH_DIRECTION_MSG);
  
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
      displayMsgNoWait(NEVER_MIND_MSG);
      return;
  }
  
  doorPosTerrain = getMapSpaceTerrain(map[doorPos.level], doorPos.x, doorPos.y);
  
  switch (c){
    case 'o':
      if (doorPosTerrain == OPENDOOR){
	clearMsg();
	displayMsgNoWait(DOOR_ALREADY_OPEN_MSG);
	return;
      } else if (doorPosTerrain != DOOR){
	clearMsg();
	displayMsgNoWait(NO_DOOR_THERE_MSG);
	return;
      } else {
	setMapSpaceTerrain(map[doorPos.level], doorPos.x, doorPos.y, OPENDOOR);
      }
      break;
    case'c':
      if (doorPosTerrain == DOOR){
	clearMsg();
	displayMsgNoWait(DOOR_ALREADY_CLOSED_MSG);
	return;
      } else if (doorPosTerrain != OPENDOOR){
	clearMsg();
	displayMsgNoWait(NO_DOOR_THERE_MSG);
	return;
      } else {
	setMapSpaceTerrain(map[doorPos.level], doorPos.x, doorPos.y, DOOR);
      }
      break;
  }
  
  
  return;
}

void doSearchDoors(unsigned int c, map map){
  static rng searchRng;
  bool rngInitd = false;
  coord3D playerLoc;
  coord3D searchLoc;
  unsigned int searchLocIndex;
  unsigned int *searchCountdownPtr;
  unsigned int searchCountdown;
  terrain searchSquareTerrain;
  
  if (!rngInitd){
    initializeRNG(&searchRng);
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
  
  searchSquareTerrain = getMapSpaceTerrain(map[playerLoc.level], searchLoc.x, searchLoc.y);
  if (searchSquareTerrain == HIDDENDOOR){
    searchCountdownPtr = getTerrainData(map[playerLoc.level], searchLoc.x, searchLoc.y, HIDDENDOOR);
    searchCountdown = *searchCountdownPtr;
    free(searchCountdownPtr);
    if (!searchCountdown){
      searchCountdown = uniformRandomRangeInt(&searchRng, 1, maxSearchCountdown);
    }
    searchCountdown--;
    if (!searchCountdown){
      setMapSpaceTerrain(map[playerLoc.level], searchLoc.x, searchLoc.y, DOOR);
    }
    setTerrainData(map[playerLoc.level], searchLoc.x, searchLoc.y, HIDDENDOOR, (void *)&searchCountdown);
  }
  
  return;
}

#endif