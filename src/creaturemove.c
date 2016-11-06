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

#define _CREATUREMOVE_C

#include <stdbool.h>
#include "lvt.h"

void moveCreatures(){
  creatureList *curCreatureNode;
  unsigned long long i;
  char numCreatures[32];
  
  curCreatureNode = creatures;
  
  while (curCreatureNode->next){
    incrementCreatureSpeedCounter(curCreatureNode->creature, getCreatureSpeed(curCreatureNode->creature));
    while (hasAction(curCreatureNode->creature)){
      doMoveCreature(curCreatureNode->creature);
    }
    curCreatureNode = curCreatureNode->next;
  }
  
  return;
}

void moveCreatureUpStair(creature *creature){
  coord3D newPos;
  coord3D curPos;
  coord2D stairPos;
  
  curPos = getCreatureLocation(creature);
  
  newPos.level = curPos.level - 1;
  
  stairPos = findLevelDownstair(dungeon[newPos.level]);
  newPos.x = stairPos.x;
  newPos.y = stairPos.y;
  
  if (!hasCreatureOccupant(dungeon[newPos.level], stairPos.x, stairPos.y)){
    clearCreatureOccupant(dungeon[curPos.level], curPos.x, curPos.y);
    setCreatureOccupant(dungeon[newPos.level], newPos.x, newPos.y, creature);
    setCreatureLocation(creature, newPos);
  }
  
  return;  
}

void moveCreatureDownStair(creature *creature){
  coord3D newPos;
  coord3D curPos;
  coord2D stairPos;
  
  curPos = getCreatureLocation(creature);
  
  newPos.level = curPos.level + 1;
  
  stairPos = findLevelUpstair(dungeon[newPos.level]);
  newPos.x = stairPos.x;
  newPos.y = stairPos.y;
  
  if (!hasCreatureOccupant(dungeon[newPos.level], stairPos.x, stairPos.y)){
    clearCreatureOccupant(dungeon[curPos.level], curPos.x, curPos.y);
    setCreatureOccupant(dungeon[newPos.level], newPos.x, newPos.y, creature);
    setCreatureLocation(creature, newPos);
  }
  
  return;  
}

void doMoveCreature(creature *creature){
  coord3D moves[9];
  coord3D curCreatureLoc;
  static rng localRng;
  static bool rngInitd = false;
  unsigned int location;
  terrain t;
  
  if (!rngInitd){
    initializeRNG(&localRng);
    rngInitd = true;
  }
  
  curCreatureLoc = getCreatureLocation(creature);
  
  t = getMapSpaceTerrain(dungeon[curCreatureLoc.level], curCreatureLoc.x, curCreatureLoc.y);
  
  if ((t == UPSTAIR) && (curCreatureLoc.level != 0)){
    if (coinFlip(&localRng) == HEADS){
      moveCreatureUpStair(creature);
      return;
    }
  } else if ((t == DOWNSTAIR) && (curCreatureLoc.level != numLevels - 1)){
    if (coinFlip(&localRng) == TAILS){
      moveCreatureDownStair(creature);
      return;
    }
  }
  
  {
  moves[0].x = MAX(curCreatureLoc.x - 1, 0);
  moves[0].y = MAX(curCreatureLoc.y - 1, 0);
  moves[0].level = curCreatureLoc.level;
  
  moves[1].x = MAX(curCreatureLoc.x - 1, 0);
  moves[1].y = curCreatureLoc.y;
  moves[1].level = curCreatureLoc.level;
  
  moves[2].x = MAX(curCreatureLoc.x - 1, 0);
  moves[2].y = MIN(curCreatureLoc.y + 1, dimMapY - 1);
  moves[2].level = curCreatureLoc.level;
  
  moves[3].x = curCreatureLoc.x;
  moves[3].y = MAX(curCreatureLoc.y - 1, 0);
  moves[3].level = curCreatureLoc.level;
  
  moves[4].x = curCreatureLoc.x;
  moves[4].y = curCreatureLoc.y;
  moves[4].level = curCreatureLoc.level;
  
  moves[5].x = curCreatureLoc.x;
  moves[5].y = MIN(curCreatureLoc.y + 1, dimMapY - 1);
  moves[5].level = curCreatureLoc.level;
  
  moves[6].x = MIN(curCreatureLoc.x + 1, dimMapX - 1);
  moves[6].y = MAX(curCreatureLoc.y - 1, 0);
  moves[6].level = curCreatureLoc.level;
  
  moves[7].x = MIN(curCreatureLoc.x + 1, dimMapX - 1);
  moves[7].y = curCreatureLoc.y;
  moves[7].level = curCreatureLoc.level;
  
  moves[8].x = MIN(curCreatureLoc.x + 1, dimMapX - 1);
  moves[8].y = MIN(curCreatureLoc.y + 1, dimMapY - 1);
  moves[8].level = curCreatureLoc.level;
  }

  location = uniformRandomRangeInt(&localRng, 1, 9) - 1;
  
  switch (getMapSpaceTerrain(dungeon[moves[location].level], moves[location].x, moves[location].y)){
    case FLOOR:
    case UPSTAIR:
    case DOWNSTAIR:
    case OPENDOOR:
      if (!hasCreatureOccupant(dungeon[moves[location].level], moves[location].x, moves[location].y)){
	clearCreatureOccupant(dungeon[moves[location].level], curCreatureLoc.x, curCreatureLoc.y);
	setCreatureOccupant(dungeon[moves[location].level], moves[location].x, moves[location].y, creature);
	setCreatureLocation(creature, moves[location]);
	return;
      }
      break;
  }
  
  return;
}
bool hasAction(creature *creature){
  unsigned int creatureSpeedCounter;
  
  creatureSpeedCounter = getCreatureSpeedCounter(creature);
  
  if (creatureSpeedCounter >= status.playerSpeed){
    decrementCreatureSpeedCounter(creature, status.playerSpeed);
    return true;
  } else {
    return false;
  }
}