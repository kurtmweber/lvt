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

#define _ITEMMGMT_C

#include <stdlib.h>
#include <string.h>
#include "item.h"

void setCorpseNutrition(item *corpse, unsigned int nutrition){
  corpse->itemData.corpseUniqueData.nutrition = nutrition;
  
  return;
}

unsigned int getCorpseNutrition(item *corpse){
  return corpse->itemData.corpseUniqueData.nutrition;
}

void setSeedRest(item *seed, unsigned int rest){
  seed->itemData.seedUniqueData.rest = rest;
  
  return;
}

void setSeedDormancy(item *seed, unsigned int dormancy){
  seed->itemData.seedUniqueData.dormancy = dormancy;
  
  return;
}

unsigned int getSeedRest(item *seed){
  return seed->itemData.seedUniqueData.rest;
}

unsigned int getSeedDormancy(item *seed){
  return seed->itemData.seedUniqueData.dormancy;
}

bool isSeed(item *item){
  if (item->itemClass == ITEM_TYPE_SEED){
    return true;
  } else {
    return false;
  }
}

void setFruitNutrition(item *fruit, unsigned int nutrition){
  fruit->itemData.fruitUniqueData.nutrition = nutrition;
  
  return;
}

unsigned int getFruitNutrition(item *fruit){
  return fruit->itemData.fruitUniqueData.nutrition;
}

void setItemLocation(item *item, coord3D location){
  item->location = location;
  
  return;
}

char getItemDispChar(item *item){
  return item->itemData.dispChar;
}

colorPairs getItemColor(item *item){
  return item->itemData.color;
}

void setItemName(item *item, char *name){
  if (item->name){
    free(item->name);
  }
  
  item->name = name;
  
  return;
}

void removeItemName(item *item){
  if (item->name){
    free(item->name);
  }
  
  item->name = 0;
  return;
}

void setItemClass(item *item, itemClassId class){
  item->itemClass = class;
  
  return;
}

itemClassId getItemClass(item *item){
  return item->itemClass;
}

unsigned int getEffectiveArmor(item *item){
  unsigned int ac;
  
  ac = item->itemData.baseArmor + item->armorModifier;
  
  return ac;
}

unsigned int getItemAttrs(item *item){
  return item->itemData.attrs;
}

unsigned int getItemWeight(item *item){
  int retval;
  
  retval = ((int)(item->itemData.weight) + item->weightModifier);
  
  if (retval < 0){
    return 0;
  } else {
    return (unsigned int)retval;
  }
}

void setItemWeight(item *item, unsigned int weight){
  item->itemData.weight = weight;
  return;
}

coord3D getItemLocation(item *item){
  // only trust this if item is unowned
  return item->location;
}

void setItemOwned(item *item, bool status){
  item->owned = status;
  
  return;
}

bool getItemOwned(item *item){
  return item->owned;
}

void setItemOwner(item *item, creature *owner){
  item->owner = owner;
  
  return;
}

creature *getItemOwner(item *item){
  return item->owner;
}