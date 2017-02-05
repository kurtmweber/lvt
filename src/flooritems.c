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

#define _FLOORITEMS_C

#include <stdbool.h>
#include "lvt.h"

const unsigned int placeItemChance = 100;	// likelihood (out of 10,000) that an item will be placed
						// on a floor
						
const unsigned int weaponLikelihood = 100;	// % chance of a generated item being a weapon

const unsigned int longswordLikelihood = 50;	// % chance of a generated weapon being a longsword
const unsigned int axeLikelihood =  75;
const unsigned int daggerLikelihood = 100;

const unsigned int steelLongswordLikelihood = 50;
const unsigned int silverLongswordLikelihood = 100;

const unsigned int throwingAxeLikelihood = 75;
const unsigned int battleAxeLikelihood = 100;

const unsigned int stilettoDaggerLikelihood = 50;
const unsigned int baselardDaggerLikelihood = 100;

void generateFloorItems(){
  coord2D *floors;
  unsigned int i = 0, j = 0;
  
  for (i = 0; i < numLevels; i++){
    floors = enumerateFloors(dungeon[i]);
    j = 0;
    while (floors[j].x){
      if (decidePlaceItem(floors[j], i)){
	randomFloorItem(floors[j], i);
      }
      
      j++;
    }
  }
  
  return;  
}

void randomFloorItem(coord2D floor, unsigned int level){
  static rng localRng;
  static bool rngInitd = false;
  item *newItem;
  unsigned int choice;
  
  if (!rngInitd){
    initializeRNG(&localRng);
    rngInitd = true;
  }
  
  choice = uniformRandomRangeInt(&localRng, 1, 100);
  
  if (choice <= weaponLikelihood){
    newItem = randomWeapon();
  }
  
  addContents(dungeon[level], floor.x, floor.y, newItem);

  
  return;
}

item *randomWeapon(){
  static rng localRng;
  static bool rngInitd = false;
  unsigned int choice;

  if (!rngInitd){
    initializeRNG(&localRng);
    rngInitd = true;
  }
  
  choice = uniformRandomRangeInt(&localRng, 1, 100);
  
  if (choice <= longswordLikelihood){
    return randomLongsword();
  } else if (choice <= axeLikelihood){
    return randomAxe();
  } else if (choice <= daggerLikelihood){
    return randomDagger();
  }
}

item *randomDagger(){
  static rng localRng;
  static bool rngInitd = false;
  unsigned int choice;
  
  if (!rngInitd){
    initializeRNG(&localRng);
    rngInitd = true;
  }
  
  choice = uniformRandomRangeInt(&localRng, 1, 100);
  
  if (choice <= stilettoDaggerLikelihood){
    return spawnItem(ITEM_TYPE_DAGGER, ITEM_DAGGER_STILETTO);
  } else if (choice <= baselardDaggerLikelihood){
    return spawnItem(ITEM_TYPE_DAGGER, ITEM_DAGGER_BASELARD);
  }
}

item *randomAxe(){
  static rng localRng;
  static bool rngInitd = false;
  unsigned int choice;
  
  if (!rngInitd){
    initializeRNG(&localRng);
    rngInitd = true;
  }
  
  choice = uniformRandomRangeInt(&localRng, 1, 100);
  
  if (choice <= throwingAxeLikelihood){
    return spawnItem(ITEM_TYPE_AXE, ITEM_AXE_THROWING);
  } else if (choice <= battleAxeLikelihood){
    return spawnItem(ITEM_TYPE_AXE, ITEM_AXE_BATTLE);
  }
}

item *randomLongsword(){
  static rng localRng;
  static bool rngInitd = false;
  unsigned int choice;
  
  if (!rngInitd){
    initializeRNG(&localRng);
    rngInitd = true;
  }
  
  choice = uniformRandomRangeInt(&localRng, 1, 100);
  
  if (choice <= steelLongswordLikelihood){
    return spawnItem(ITEM_TYPE_LONGSWORD, ITEM_LONGSWORD_STEEL);
  } else if (choice <= silverLongswordLikelihood){
    return spawnItem(ITEM_TYPE_LONGSWORD, ITEM_LONGSWORD_SILVER);
  }
}

bool decidePlaceItem(coord2D floor, unsigned int level){
  static rng localRng;
  static bool rngInitd = false;
  
  if (!rngInitd){
    initializeRNG(&localRng);
    rngInitd = true;
  }
  
  if (uniformRandomRangeInt(&localRng, 1, 10000) <= placeItemChance){
    return true;
  } else {
    return false;
  }
}