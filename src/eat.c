/*  This file is part of Lavender Throne.
 *  Copyright 2016-2017 by Kurt Weber
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

#define _EAT_C

#include <ctype.h>

#include "lvt.h"

#include "eat.h"

#include "creaturemgmt.h"
#include "item.h"
#include "game.h"
#include "messages.h"
#include "allocator.h"

void doEat(){
  unsigned int c = 1;
  unsigned int i = 0;
  bool checked[52];
  unsigned int j = 0;
  item *inventory[52];
  item *chosenItem;
  itemClassId itemClass;
  
  for (j = 0; j < 52; j++){
    checked[j] = false;
  }
  
  getCreatureInventory(&player, inventory);
  
  addToMsgQueue("Eat which item? (space to cancel)", false);
  procMsgQueue();
  
  while (c){
    displayInventoryWindow(i, checked);
    c = getch();
    switch (c){
      case KEY_UP:
        i == 0 ? : i--;
        break;
      case KEY_DOWN:
        i == 39 ? : i++;
        break;
      case ' ':
        freeAction = true;
        delwin(invWin);
        clearMsg();
        return;
      default:
        if (isupper(c) || islower(c)){
          if (isInventoryLetter(c)){
            chosenItem = inventory[inventoryLetterToIndex(c)];
            itemClass = getItemClass(chosenItem);
            if ((itemClass != ITEM_TYPE_CORPSE) && (itemClass != ITEM_TYPE_FRUIT)){
              addToMsgQueue(NOT_FOOD_MSG, false);
              return;
            }
            eatItem(&player, chosenItem);
            /*removeCreatureInventoryItem(&player, chosenItem);
            creaturePos = getCreatureLocation(&player);
            addContents(dungeon[creaturePos.level], creaturePos.x, creaturePos.y, chosenItem);*/
            return;
          } else {
            break;
          }
        } else {
          break;
        }
    }
    
    delwin(invWin);
  }
  return;
}

void eatItem(creature *creature, item *foodItem){
  item *newSeedItem;
  unsigned int curNutrition;
  unsigned int itemNutrition;
  itemClassId itemClass;
  int itemSubClass;
  char newSeedInv;
  coord3D curLoc;
  
  itemClass = getItemClass(foodItem);
  
  switch (itemClass){
    case ITEM_TYPE_CORPSE:
      itemNutrition = getCorpseNutrition(foodItem);
      break;
    case ITEM_TYPE_FRUIT:
      itemNutrition = getFruitNutrition(foodItem);
      break;
    default:	// can't happen
      return;
  }
  
  curNutrition = getCreatureNutrition(creature);
  setCreatureNutrition(creature, curNutrition + itemNutrition);
  
  if (itemClass == ITEM_TYPE_FRUIT){
    itemSubClass = foodItem->fruitSubClass;
    newSeedItem = spawnItem(ITEM_TYPE_SEED, itemSubClass);
    newSeedInv = addCreatureInventoryItem(creature, newSeedItem);
    if (!newSeedInv){
      curLoc = getCreatureLocation(creature);
      addContents(curLoc.level, curLoc.x, curLoc.y, newSeedItem);
    }
  }
  
  removeCreatureInventoryItem(creature, foodItem);
  freeItem(foodItem);
  
  return;
}