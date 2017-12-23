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

#define _CREATUREEAT_C

#include <stdbool.h>

#include "lvt.h"

#include "creatureeat.h"

#include "creature.h"
#include "creaturemgmt.h"

bool hungerAction(creature *curCreature){
  item *foodItem = 0;
  coord3D itemLoc;
  
  if (getCreatureNutrition(curCreature) <= (getCreatureWeight(curCreature) / 2)){
    setCreatureHungry(curCreature);
  }
  
  if (isCreatureHungry(curCreature)){
    if (hasFoodInventory(curCreature)){
      foodItem = selectOptimalFoodInventory(curCreature);
      if (foodItem){
	eatItem(curCreature, foodItem);
	return true;
      }
    }
    
    foodItem = checkAdjacentFood(getCreatureLocation(curCreature));
    if (foodItem){
      itemLoc = getItemLocation(foodItem);
      if (addCreatureInventoryItem(curCreature, foodItem)){
	removeContent(itemLoc.level, itemLoc.x, itemLoc.y, foodItem);
	return true;
      }
    }
    
    foodItem = checkAdjacentFruitingBush(getCreatureLocation(curCreature));
    if (foodItem){
      if (addCreatureInventoryItem(curCreature, foodItem)){
	return true;
      }
    }      
  }
  
  return false;
}