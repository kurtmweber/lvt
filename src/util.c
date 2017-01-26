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