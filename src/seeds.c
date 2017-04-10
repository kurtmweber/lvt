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

#define _SEEDS_C

#include "lvt.h"

const unsigned int seedDormancyLimit = 100;
const unsigned int seedRestLimit = 100;

void updateSeeds(){
  seedList *curSeedNode;
  item *curSeed;
  unsigned int dormancy;
  unsigned int rest;
  creature *owner;
  seedList *sNode;
  
  curSeedNode = seeds;
  if (!curSeedNode){
    return;
  }
  
  do {
    curSeed = curSeedNode->seed;
    curSeedNode = curSeedNode->next;
    
    if (getItemOwned(curSeed)){
      dormancy = getSeedDormancy(curSeed);
      dormancy++;
      if (dormancy == seedDormancyLimit){
	owner = getItemOwner(curSeed);
	removeCreatureInventoryItem(owner, curSeed);
	sNode = findSeedListEntry(seeds, curSeed);
	seeds = removeSeedNode(seeds, sNode);
	freeSeedListEntry(sNode);
	//freeItem(curSeed);
      } else {
	setSeedDormancy(curSeed, dormancy);
      }
    }
  } while (curSeedNode);
  
  return;
}