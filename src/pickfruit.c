/*  This file is part of Lavender Throne.
 *  Copyright 2016-7 by Kurt Weber
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

#define _PICKFRUIT_C

#include <stdbool.h>

#include "lvt.h"

#include "creaturemgmt.h"
#include "messages.h"
#include "types.h"

void doPickFruit(){
  coord3D curLoc;
  coord2D curLoc2d;
  bool pickCurSpace;
  plant *plant;
  item *fruit;
  unsigned int c = 1;
  moveDirection dir;
  coord2D pickLoc2d;
  coord3D pickLoc;
  
  curLoc = getCreatureLocation(&player);
  
  if (hasPlantOccupant(dungeon[curLoc.level], curLoc.x, curLoc.y)){
    pickCurSpace = askQuestionYesNo(PICK_CURRENT_SPACE_Q);
    if (pickCurSpace){
      plant = getPlantOccupant(dungeon[curLoc.level], curLoc.x, curLoc.y);
      fruit = pickFruitFromPlant(plant);
      if (!fruit){
	freeAction = true;
	addToMsgQueue(NO_FRUIT_MSG, false);
      } else {
	if (!addCreatureInventoryItem(&player, fruit)){
	  addToMsgQueue(INVENTORY_FULL_MSG, false);
	}
      }
      return;
    }
  }
  
  addToMsgQueue("Which direction? (space to cancel)", false);
  procMsgQueue();
  
  c = 1;
  
  while (c){
    c = getch();
    switch (c){
      case KEY_UP:
	dir = UP;
	c = 0;
	break;
      case KEY_DOWN:
	dir = DOWN;
	c = 0;
	break;
      case KEY_RIGHT:
	dir = RIGHT;
	c = 0;
	break;
      case KEY_LEFT:
	dir = LEFT;
	c = 0;
	break;
      case KEY_UPRIGHT:
	dir = UPRIGHT;
	c = 0;
	break;
      case KEY_UPLEFT:
	dir = UPLEFT;
	c = 0;
	break;
      case KEY_DOWNRIGHT:
	dir = DOWNRIGHT;
	c = 0;
	break;
      case KEY_DOWNLEFT:
	dir = DOWNLEFT;
	c = 0;
	break;
      case ' ':
	freeAction = true;
	return;
      default:
	break;
    }
  }
  
  curLoc2d.x = curLoc.x;
  curLoc2d.y = curLoc.y;
  
  pickLoc2d = getSpaceDirectionCoordinates(curLoc2d, dir);
  pickLoc.level = curLoc.level;
  pickLoc.x = pickLoc2d.x;
  pickLoc.y = pickLoc2d.y;
  
  if (hasPlantOccupant(dungeon[pickLoc.level], pickLoc.x, pickLoc.y)){
    plant = getPlantOccupant(dungeon[pickLoc.level], pickLoc.x, pickLoc.y);
    fruit = pickFruitFromPlant(plant);
    if (!fruit){
      freeAction = true;
      addToMsgQueue(NO_FRUIT_MSG, false);
    } else {
      if (!addCreatureInventoryItem(&player, fruit)){
	addToMsgQueue(INVENTORY_FULL_MSG, false);
      }
    }
  } else {
    freeAction = true;
    addToMsgQueue(NO_PLANT_MSG, false);
  }
  
  return;
}

item *pickFruitFromPlant(plant *plant){
  unsigned int curProd;
  unsigned int growthRate;
  unsigned int maturityLevel;
  unsigned int nutrition;
  unsigned int productionTime;
  unsigned int maxProduction;
  item *fruit;
  
  curProd = getPlantCurProduction(plant);
  
  if (curProd == 0){
    return NULL;
  }
  
  fruit = spawnItem(ITEM_TYPE_FRUIT, getPlantSpecies(plant));
  
  growthRate = getPlantGrowthRate(plant);
  maturityLevel = getPlantMaxGrowth(plant);
  productionTime = getPlantProductionTime(plant);
  maxProduction = getPlantMaxProduction(plant);
  
  nutrition = ((maturityLevel / maxProduction) + productionTime) / growthRate;
  setFruitNutrition(fruit, nutrition);
  
  setPlantCurProduction(plant, curProd - 1);
  
  return fruit;
}