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
#include <string.h>
#include "lvt.h"

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