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

#define _NAME_C

#include <stdlib.h>
#include <string.h>
#include "lvt.h"
#include "types.h"

char *generateName(){
  static rng localRng;
  static bool rngInitd = false;
  char *creatureName = 0;
  unsigned int numSyls = 0;
  unsigned int syl[5] = {0, 0, 0, 0, 0};
  unsigned int sylLen[5] = {0, 0, 0, 0, 0};
  unsigned int i = 0;

  char *syllables[5][10] = {
    {"Nar", "Vel", "Sin", "Fan", "Gar", "Lek", "Mil", "Tein", "Sher", "Koin"},
    {"tark", "thrond", "dil", "gorn", "min", "tal", "rend", "fad", "parn", "tip"},
    {"fod", "kan", "dar", "wip", "mar", "toin", "sled", "lat", "pin", "ced"},
    {"kar", "dan", "gor", "nib", "sek", "bryn", "mawr", "pak", "ben", "zik"},
    {"ger", "hod", "nis", "wok", "pier", "trak", "zes", "cof", "ger", "ham"}
  };  
    
  if (!rngInitd){
    initializeRNG(&localRng);
    rngInitd = true;
  }
  
  
  numSyls = uniformRandomRangeInt(&localRng, 1, 5);
  
  for (i = 0; i < numSyls; i++){
    syl[i] = uniformRandomRangeInt(&localRng, 1, 10) - 1;
  }
  
  for (i = 0; i < numSyls; i++){
    sylLen[i] = strlen(syllables[i][syl[i]]);		// we've initialized all elements of sylLen to 0, so later when we
					// calculate the sum of the array elements, unused elements won't
					// affect it
  }
  
  creatureName = (char *)calloc(sumArrayInt(sylLen, 5) + 1, sizeof(char));
  
  for (i = 0; i < numSyls; i++){
    strcat(creatureName, syllables[i][syl[i]]);
  }
  
  return creatureName;
}