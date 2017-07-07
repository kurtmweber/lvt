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

#define _CREATUREINVENTORY_C

#include <stdbool.h>
#include <stdlib.h>

#include "lvt.h"
#include "creature.h"

bool inventoryAction(creature *curCreature){
  if (creaturePickupWeapon(curCreature)){
    return true;
  }
  
  return false;
}

bool creaturePickupWeapon(creature *curCreature){
  coord3D curLoc;
  mapSpaceContents *contents, *thisContent;
  item **weaponList = 0;
  unsigned int numWeapons = 0;
  long double *weaponValues = 0;
  unsigned int i, j;
  static rng localRng;
  static bool rngInitd = false;
  int curInt;
  item *curWeapon = 0, *secWeapon = 0, *testWeapon = 0;
  long double curWeaponValue = 0, secWeaponValue = 0, testWeaponValue = 0;
  
  
  if (!rngInitd){
    initializeRNG(&localRng);
    rngInitd = true;
    }
  
  curLoc = getCreatureLocation(curCreature);
  
  contents = getContents(dungeon[curLoc.level], curLoc.x, curLoc.y);
  dungeon[curLoc.level][curLoc.x][curLoc.y].contents = 0;
  
  thisContent = contents;
  
  while (thisContent){
    if (isWeapon(thisContent->item)){
      numWeapons++;
      weaponList = realloc(weaponList, numWeapons * sizeof(item *));
      weaponList[numWeapons - 1] = thisContent->item;
    }
    thisContent = thisContent->next;
  }
  
  if (!numWeapons){
    while (contents){
      addContents(curLoc.level, curLoc.x, curLoc.y, contents->item);
      contents = contents->next;
    }
    return false;
  }
  
  weaponValues = calloc(numWeapons, sizeof(long double));
  
  curInt = getCreatureCurInt(curCreature);
  
  for (i = 0; i < curInt; i++){
    for (j = 0; j < numWeapons; j++){
      weaponValues[j] += uniformRandomRangeInt(&localRng, 0, calcAttackVal(curCreature, weaponList[j]));
    }
  }
  
  for (i = 0; i < numWeapons; i++){
    weaponValues[i] /= curInt;
  }
  
  i = returnIndexMaxValLongDouble(weaponValues, numWeapons);
  testWeapon = weaponList[i];
  testWeaponValue = weaponValues[i];
  
  if (hasWeapon(curCreature)){
    curWeapon = curCreature->weapon;
    for (i = 0; i < curInt; i++){
      curWeaponValue += uniformRandomRangeInt(&localRng, 0, calcAttackVal(curCreature, curWeapon));
    }
    
    curWeaponValue /= curInt;
  }
  
  if (secWeapon = findInventoryWeapon(curCreature)){
    for (i = 0; i < curInt; i++){
      secWeaponValue += uniformRandomRangeInt(&localRng, 0, calcAttackVal(curCreature, secWeapon));
    }
    
    secWeaponValue /= curInt;
  }
  
  if (testWeaponValue < secWeaponValue){
    while (contents){
      addContents(curLoc.level, curLoc.x, curLoc.y, contents->item);
      contents = contents->next;
    }
    return false;
  } else {
    while (contents){
      if (contents->item != testWeapon){
	addContents(curLoc.level, curLoc.x, curLoc.y, contents->item);
      }
      contents = contents->next;
    }
    addCreatureInventoryItem(curCreature, testWeapon);
    if (secWeapon){
      removeCreatureInventoryItem(curCreature, secWeapon);
      addContents(curLoc.level, curLoc.x, curLoc.y, secWeapon);
    }
  }
  
  if (testWeaponValue > curWeaponValue){
    if (curWeapon && hasWeapon(curCreature)){
      unwieldWeapon(curCreature);
    }
    wieldItem(curCreature, testWeapon);
  }
    
  
  return true;
}