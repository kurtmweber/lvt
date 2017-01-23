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

#define _ITEM_C

#include <stdlib.h>
#include <string.h>
#include "colors.h"
#include "item.h"
#include "lvt.h"

itemType *itemTypes[ITEM_TYPE_MAX];

item *spawnItem(itemClassId class, int subClass){
  item *item;
  
  switch(class){
    case ITEM_TYPE_CORPSE:
      item =  spawnCorpse(subClass);
      break;
    case ITEM_TYPE_LONGSWORD:
      item = spawnLongsword(subClass);
      break;
    default:
      return 0;
  }
  
  item->name = 0;
  
  return item;
}

item *spawnLongsword(int subClass){
  item *longsword;
  
  longsword = allocateItem();
  setItemClass(longsword, ITEM_TYPE_LONGSWORD);
  longsword->longswordSubClass = subClass;
  longsword->itemData = itemTypes[ITEM_TYPE_LONGSWORD][subClass];
  
  return longsword;
}

item *spawnCorpse(int subClass){
  item *corpse;
  
  corpse = allocateItem();
  
  setItemClass(corpse, ITEM_TYPE_CORPSE);
  corpse->corpseSubClass = subClass;
  corpse->itemData = itemTypes[ITEM_TYPE_CORPSE][subClass];
  
  return corpse;
}

void setItemClass(item *item, itemClassId class){
  item->itemClass = class;
  
  return;
}

void initItems(){
  initCorpses();
  initLongswords();
  
  return;
}

void initLongswords(){
  longswordSubClassId i;
  char dispChar = '/';
  
  itemTypes[ITEM_TYPE_LONGSWORD] = calloc(ITEM_LONGSWORD_MAX, sizeof(itemType));
  
  // steel longsword
  {
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_STEEL].baseDamage = 5;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_STEEL].baseToHit = 2;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_STEEL].baseArmor = 0;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_STEEL].itemName = calloc(16, sizeof(char));
    strcat(itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_STEEL].itemName, "steel longsword");
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_STEEL].dispChar = dispChar;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_STEEL].color = WhiteBlack;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_STEEL].weight = 8;
  }
  
  // I use braces like this because it lets me code-fold these blocks out of the way in my text editor
  
  // silver longsword
  {
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_SILVER].baseDamage = 7;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_SILVER].baseToHit = 1;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_SILVER].baseArmor = 0;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_SILVER].itemName = calloc(17, sizeof(char));
    strcat(itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_SILVER].itemName, "silver longsword");
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_SILVER].dispChar = dispChar;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_SILVER].color = CyanBlack;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_SILVER].weight = 10;
  }
  
  return;
}

void initCorpses(){
  corpseSubClassId i;
  char *corpseSubClassNames[] = {"human", "halfling", "elf", "dwarf", "bear"};
  colorPairs corpseColors[] = {WhiteBlack, BlueBlack, GreenBlack, RedBlack, MagentaBlack};
  
  itemTypes[ITEM_TYPE_CORPSE] = calloc(ITEM_CORPSE_MAX, sizeof(itemType));
  
  for (i = 0; i < ITEM_CORPSE_MAX; i++){
    itemTypes[ITEM_TYPE_CORPSE][i].baseDamage = 0;
    itemTypes[ITEM_TYPE_CORPSE][i].baseArmor = 0;
    itemTypes[ITEM_TYPE_CORPSE][i].baseToHit = 0;
    itemTypes[ITEM_TYPE_CORPSE][i].itemName = calloc(strlen(corpseSubClassNames[i] + 1), sizeof(char));
    strcat(itemTypes[ITEM_TYPE_CORPSE][i].itemName, corpseSubClassNames[i]);
    itemTypes[ITEM_TYPE_CORPSE][i].dispChar = '%';
    itemTypes[ITEM_TYPE_CORPSE][i].color = corpseColors[i];
  }
  
  return;
}