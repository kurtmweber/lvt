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

#define _UTIL_C

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "lvt.h"
#include "level.h"
#include "move.h"
#include "stringlookups.h"
#include "types.h"

int clampRangeIntSigned(int value, int min, int max){
  if (value < min){
    return min;
  } else if (value > max){
    return max;
  } else {
    return value;
  }
}

bool sameFactions(creature *creature1, creature *creature2){
  if (getCreatureFaction(creature1) == getCreatureFaction(creature2)){
    return true;
  } else {
    return false;
  }
}

unsigned int sumArrayInt(int *array, unsigned int numElements){
  unsigned int i = 0;
  unsigned int a;
  unsigned int sum;
  
  for (i = 0; i < numElements; i++){
    sum += array[i];
  }
  
  return sum;
}

void *randomizeArray(void *array, unsigned int numElements, size_t size){
  unsigned int i;
  unsigned int a;
  char tmp[size];
  char *cArray = array;
  static rng localRng;
  static bool rngInitd = false;
  
  if (!rngInitd){
    initializeRNG(&localRng);
    rngInitd = true;
  }
  
  for (i = 0; i < numElements - 2; i++){
    a = uniformRandomRangeInt(&localRng, i, numElements - 1);
    
    memcpy(tmp, cArray + (size * i), size);
    memcpy(cArray + (size *i ), cArray + (size * a), size);
    memcpy(cArray + (size * a), tmp, size);
  }
  
  return array;
}

coord2D getSpaceDirectionCoordinates(coord2D point, moveDirection dir){
  coord2D tmp;
  
  tmp.x = point.x;
  tmp.y = point.y;
  
  switch (dir){
    case UP:
      tmp.y = MAX(point.y - 1, 0);
      break;
    case DOWN:
      tmp.y = MIN(point.y + 1, dimMapY - 1);
      break;
    case LEFT:
      tmp.x = MAX(point.x - 1, 0);
      break;
    case RIGHT:
      tmp.x = MIN(point.x + 1, dimMapX - 1);
      break;
    case UPLEFT:
      tmp.y = MAX(point.y - 1, 0);
      tmp.x = MAX(point.x - 1, 0);
      break;
    case UPRIGHT:
      tmp.y = MAX(point.y - 1, 0);
      tmp.x = MIN(point.x + 1, dimMapX - 1);
      break;
    case DOWNLEFT:
      tmp.y = MIN(point.y + 1, dimMapY - 1);
      tmp.x = MAX(point.x - 1, 0);
      break;
    case DOWNRIGHT:
      tmp.y = MIN(point.y + 1, dimMapY - 1);
      tmp.x = MIN(point.x + 1, dimMapX - 1);
      break;
  }
  
  return tmp;
}

char *autoGenerateCorpseName(creature *creature){
  char *corpseName;
  char *creatureName;
  creatureSpecies creatureSpecies;
  
  corpseName = calloc(15, sizeof(char));
  strcat(corpseName, "the corpse of ");
  
  creatureName = getCreatureName(creature);
  corpseName = realloc(corpseName, (strlen(corpseName) + strlen(creatureName) + 1) * sizeof(char));
  
  strcat(corpseName, creatureName);
  
  corpseName = realloc(corpseName, (strlen(corpseName) + 5) * sizeof(char));
  strcat(corpseName, ", a ");	// at some point this should be updated to use "an" when appropriate
  
  creatureSpecies = getCreatureSpecies(creature);
    
  corpseName = realloc(corpseName, (strlen(corpseName) + strlen(speciesNames[creatureSpecies]) + 1) * sizeof(char));
  strcat(corpseName, speciesNames[creatureSpecies]);
  
  return corpseName;
}

char inventoryIndexToLetter(char c){
  // unfortunately, ASCII doesn't just put a break between lowercase and uppercase characters, but in fact
  // places lowercase AFTER uppercase in numerical order, but we do this fuckery because nevertheless it
  // seems more natural to use lowercase letters before uppercase ones.
  
  if (c < 26){
    return c + 'a';
  } else {
    return (c - 26) + 'A';
  }
}

int inventoryLetterToIndex(char c){
  if ((c >= 'A') && (c <= 'Z')){
    return c - 'A' + 26;
  } else if ((c >= 'a') && (c <= 'z')){
    return c - 'a';
  } else {
    return -1;
  }
}

void directionToUnitMatrix(moveDirection dir, moveMatrix *matrix){
  matrix->x = 0;
  matrix->y = 0;
  
  switch (dir){
    case UP:
    case UPLEFT:
    case UPRIGHT:
      matrix->y = -1;
      break;
    case DOWN:
    case DOWNLEFT:
    case DOWNRIGHT:
      matrix->y = 1;
      break;
    default:
      break;
  }
  
  switch (dir){
    case UPLEFT:
    case LEFT:
    case DOWNLEFT:
      matrix->x = -1;
      break;
    case UPRIGHT:
    case RIGHT:
    case DOWNRIGHT:
      matrix->x = 1;
      break;
    default:
      break;
  }
  
  return;
}

bool isInventoryLetter(char c){
  item *inventory[52];
  
  getCreatureInventory(&player, inventory);
  
  if ((c >= 'A') && (c <= 'Z')){
    c -= 'A';
  } else if ((c >= 'a') && (c <= 'z')){
    c -= 'a';
  } else {
    return false;
  }
  
  if (inventory[c]){
    return true;
  } else {
    return false;
  }
}

item *checkAdjacentFood(coord3D location){
  coord3D moves[9];
  unsigned int i;
  mapSpaceContents *curContents;
  itemClassId cId;
  
  {
    moves[0].x = MAX(location.x - 1, 0);
    moves[0].y = MAX(location.y - 1, 0);
    moves[0].level = location.level;
  
    moves[1].x = MAX(location.x - 1, 0);
    moves[1].y = location.y;
    moves[1].level = location.level;
  
    moves[2].x = MAX(location.x - 1, 0);
    moves[2].y = MIN(location.y + 1, dimMapY - 1);
    moves[2].level = location.level;
  
    moves[3].x = location.x;
    moves[3].y = MAX(location.y - 1, 0);
    moves[3].level = location.level;
  
    moves[4].x = location.x;
    moves[4].y = location.y;
    moves[4].level = location.level;
  
    moves[5].x = location.x;
    moves[5].y = MIN(location.y + 1, dimMapY - 1);
    moves[5].level = location.level;
  
    moves[6].x = MIN(location.x + 1, dimMapX - 1);
    moves[6].y = MAX(location.y - 1, 0);
    moves[6].level = location.level;
  
    moves[7].x = MIN(location.x + 1, dimMapX - 1);
    moves[7].y = location.y;
    moves[7].level = location.level;
  
    moves[8].x = MIN(location.x + 1, dimMapX - 1);
    moves[8].y = MIN(location.y + 1, dimMapY - 1);
    moves[8].level = location.level;
  }
  
  for (i = 0; i < 9; i++){
    curContents = getContents(dungeon[moves[i].level], moves[i].x, moves[i].y);
    while (curContents){
      cId = getItemClass(curContents->item);
      if ((cId == ITEM_TYPE_CORPSE) || (cId == ITEM_TYPE_FRUIT)){
	return curContents->item;
      }
      curContents = curContents->next;
    }
  }
  
  return NULL;
}

item *checkAdjacentFruitingBush(coord3D location){
  coord3D moves[9];
  unsigned int i;
  plant *plantOccupant;
  item *berry;
  
  {
    moves[0].x = MAX(location.x - 1, 0);
    moves[0].y = MAX(location.y - 1, 0);
    moves[0].level = location.level;
  
    moves[1].x = MAX(location.x - 1, 0);
    moves[1].y = location.y;
    moves[1].level = location.level;
  
    moves[2].x = MAX(location.x - 1, 0);
    moves[2].y = MIN(location.y + 1, dimMapY - 1);
    moves[2].level = location.level;
  
    moves[3].x = location.x;
    moves[3].y = MAX(location.y - 1, 0);
    moves[3].level = location.level;
  
    moves[4].x = location.x;
    moves[4].y = location.y;
    moves[4].level = location.level;
  
    moves[5].x = location.x;
    moves[5].y = MIN(location.y + 1, dimMapY - 1);
    moves[5].level = location.level;
  
    moves[6].x = MIN(location.x + 1, dimMapX - 1);
    moves[6].y = MAX(location.y - 1, 0);
    moves[6].level = location.level;
  
    moves[7].x = MIN(location.x + 1, dimMapX - 1);
    moves[7].y = location.y;
    moves[7].level = location.level;
  
    moves[8].x = MIN(location.x + 1, dimMapX - 1);
    moves[8].y = MIN(location.y + 1, dimMapY - 1);
    moves[8].level = location.level;
  }
  
  for (i = 0; i < 9; i++){
    if (hasPlantOccupant(dungeon[moves[i].level], moves[i].x, moves[i].y)){
      plantOccupant = getPlantOccupant(dungeon[moves[i].level], moves[i].x, moves[i].y);
      if (getPlantCurProduction(plantOccupant) > 0){
	berry = pickFruitFromPlant(plantOccupant);
	return berry;
      }
    }
  }
  
  return NULL;
}

unsigned int returnIndexMaxValLongDouble(long double *array, unsigned int numElements){
  unsigned int indexMax = 0;
  unsigned int i = 0;
  
  for (i = 0; i < (numElements - 1); i++){
    if (array[i] > array[indexMax]){
      indexMax = i;
    }
  }
  
  return indexMax;
}