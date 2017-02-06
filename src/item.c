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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "colors.h"
#include "item.h"
#include "lvt.h"

itemType *itemTypes[ITEM_TYPE_MAX];

void initItems(){
  initCorpses();
  initLongswords();
  initAxes();
  initDaggers();
  initShirts();
  initUnderarmor();
  
  return;
}

void initUnderarmor(){
 underarmorSubClassId i;
 char dispChar = ']';
 
 itemTypes[ITEM_TYPE_UNDERARMOR] = calloc(ITEM_UNDERARMOR_MAX, sizeof(itemType));
 
 // underarmor
 {
   itemTypes[ITEM_TYPE_UNDERARMOR][ITEM_UNDERARMOR_CHAINMAIL].baseDamage = 0;
   itemTypes[ITEM_TYPE_UNDERARMOR][ITEM_UNDERARMOR_CHAINMAIL].baseToHit = 0;
   itemTypes[ITEM_TYPE_UNDERARMOR][ITEM_UNDERARMOR_CHAINMAIL].baseArmor = 5;
   itemTypes[ITEM_TYPE_UNDERARMOR][ITEM_UNDERARMOR_CHAINMAIL].throwable = false;
   itemTypes[ITEM_TYPE_UNDERARMOR][ITEM_UNDERARMOR_CHAINMAIL].twoHandedWield = false;
   itemTypes[ITEM_TYPE_UNDERARMOR][ITEM_UNDERARMOR_CHAINMAIL].fragile = false;
   itemTypes[ITEM_TYPE_UNDERARMOR][ITEM_UNDERARMOR_CHAINMAIL].itemName = calloc(11, sizeof(char));
   strcpy(itemTypes[ITEM_TYPE_UNDERARMOR][ITEM_UNDERARMOR_CHAINMAIL].itemName, "chain mail");
   itemTypes[ITEM_TYPE_UNDERARMOR][ITEM_UNDERARMOR_CHAINMAIL].dispChar = dispChar;
   itemTypes[ITEM_TYPE_UNDERARMOR][ITEM_UNDERARMOR_CHAINMAIL].color = WhiteBlack;
   itemTypes[ITEM_TYPE_UNDERARMOR][ITEM_UNDERARMOR_CHAINMAIL].attrs = A_BOLD;
   itemTypes[ITEM_TYPE_UNDERARMOR][ITEM_UNDERARMOR_CHAINMAIL].weight = 10;
   itemTypes[ITEM_TYPE_UNDERARMOR][ITEM_UNDERARMOR_CHAINMAIL].possibleSlots = ARMOR_UNDERARMOR;
 }
 
 return;
}

void initShirts(){
  shirtSubClassId i;
  char dispChar = ']';
  
  itemTypes[ITEM_TYPE_SHIRT] = calloc(ITEM_SHIRT_MAX, sizeof(itemType));
  
  // t-shirt
  {
    itemTypes[ITEM_TYPE_SHIRT][ITEM_SHIRT_TSHIRT].baseDamage = 0;
    itemTypes[ITEM_TYPE_SHIRT][ITEM_SHIRT_TSHIRT].baseToHit = 0;
    itemTypes[ITEM_TYPE_SHIRT][ITEM_SHIRT_TSHIRT].baseArmor = 1;
    itemTypes[ITEM_TYPE_SHIRT][ITEM_SHIRT_TSHIRT].throwable = false;
    itemTypes[ITEM_TYPE_SHIRT][ITEM_SHIRT_TSHIRT].twoHandedWield = false;
    itemTypes[ITEM_TYPE_SHIRT][ITEM_SHIRT_TSHIRT].fragile = false;
    itemTypes[ITEM_TYPE_SHIRT][ITEM_SHIRT_TSHIRT].itemName = calloc(8, sizeof(char));
    strcpy(itemTypes[ITEM_TYPE_SHIRT][ITEM_SHIRT_TSHIRT].itemName, "t-shirt");
    itemTypes[ITEM_TYPE_SHIRT][ITEM_SHIRT_TSHIRT].dispChar = dispChar;
    itemTypes[ITEM_TYPE_SHIRT][ITEM_SHIRT_TSHIRT].color = WhiteBlack;
    itemTypes[ITEM_TYPE_SHIRT][ITEM_SHIRT_TSHIRT].attrs = 0;
    itemTypes[ITEM_TYPE_SHIRT][ITEM_SHIRT_TSHIRT].weight = 1;
    itemTypes[ITEM_TYPE_SHIRT][ITEM_SHIRT_TSHIRT].possibleSlots = ARMOR_SHIRT;
  }
  
  // Hawaiian shirt
  {
    itemTypes[ITEM_TYPE_SHIRT][ITEM_SHIRT_HAWAIIAN].baseDamage = 0;
    itemTypes[ITEM_TYPE_SHIRT][ITEM_SHIRT_HAWAIIAN].baseToHit = 0;
    itemTypes[ITEM_TYPE_SHIRT][ITEM_SHIRT_HAWAIIAN].baseArmor = 1;
    itemTypes[ITEM_TYPE_SHIRT][ITEM_SHIRT_HAWAIIAN].throwable = false;
    itemTypes[ITEM_TYPE_SHIRT][ITEM_SHIRT_HAWAIIAN].twoHandedWield = false;
    itemTypes[ITEM_TYPE_SHIRT][ITEM_SHIRT_HAWAIIAN].fragile = false;
    itemTypes[ITEM_TYPE_SHIRT][ITEM_SHIRT_HAWAIIAN].itemName = calloc(15, sizeof(char));
    strcpy(itemTypes[ITEM_TYPE_SHIRT][ITEM_SHIRT_HAWAIIAN].itemName, "Hawaiian shirt");
    itemTypes[ITEM_TYPE_SHIRT][ITEM_SHIRT_HAWAIIAN].dispChar = dispChar;
    itemTypes[ITEM_TYPE_SHIRT][ITEM_SHIRT_HAWAIIAN].color = MagentaBlack;
    itemTypes[ITEM_TYPE_SHIRT][ITEM_SHIRT_HAWAIIAN].attrs = 0;
    itemTypes[ITEM_TYPE_SHIRT][ITEM_SHIRT_HAWAIIAN].weight = 1;
    itemTypes[ITEM_TYPE_SHIRT][ITEM_SHIRT_HAWAIIAN].possibleSlots = ARMOR_SHIRT;
  }
  
  return;
}

void initDaggers(){
  axeSubClassId i;
  char dispChar = '/';
  
  itemTypes[ITEM_TYPE_DAGGER] = calloc(ITEM_DAGGER_MAX, sizeof(itemType));
  
  // stiletto dagger
  {
    itemTypes[ITEM_TYPE_DAGGER][ITEM_DAGGER_STILETTO].baseDamage = 2;
    itemTypes[ITEM_TYPE_DAGGER][ITEM_DAGGER_STILETTO].baseToHit = 20;
    itemTypes[ITEM_TYPE_DAGGER][ITEM_DAGGER_STILETTO].baseArmor = 0;
    itemTypes[ITEM_TYPE_DAGGER][ITEM_DAGGER_STILETTO].throwable = true;
    itemTypes[ITEM_TYPE_DAGGER][ITEM_DAGGER_STILETTO].twoHandedWield = false;
    itemTypes[ITEM_TYPE_DAGGER][ITEM_DAGGER_STILETTO].fragile = false;
    itemTypes[ITEM_TYPE_DAGGER][ITEM_DAGGER_STILETTO].itemName = calloc(16, sizeof(char));
    strcpy(itemTypes[ITEM_TYPE_DAGGER][ITEM_DAGGER_STILETTO].itemName, "stiletto dagger");
    itemTypes[ITEM_TYPE_DAGGER][ITEM_DAGGER_STILETTO].dispChar = dispChar;
    itemTypes[ITEM_TYPE_DAGGER][ITEM_DAGGER_STILETTO].color = BlueBlack;
    itemTypes[ITEM_TYPE_DAGGER][ITEM_DAGGER_STILETTO].attrs = 0;
    itemTypes[ITEM_TYPE_DAGGER][ITEM_DAGGER_STILETTO].weight = 1;
    itemTypes[ITEM_TYPE_DAGGER][ITEM_DAGGER_STILETTO].possibleSlots = 0;
  }
  
  // baselard dagger
  {
    itemTypes[ITEM_TYPE_DAGGER][ITEM_DAGGER_BASELARD].baseDamage = 4;
    itemTypes[ITEM_TYPE_DAGGER][ITEM_DAGGER_BASELARD].baseToHit = 15;
    itemTypes[ITEM_TYPE_DAGGER][ITEM_DAGGER_BASELARD].baseArmor = 0;
    itemTypes[ITEM_TYPE_DAGGER][ITEM_DAGGER_BASELARD].throwable = true;
    itemTypes[ITEM_TYPE_DAGGER][ITEM_DAGGER_BASELARD].twoHandedWield = false;
    itemTypes[ITEM_TYPE_DAGGER][ITEM_DAGGER_BASELARD].fragile = false;
    itemTypes[ITEM_TYPE_DAGGER][ITEM_DAGGER_BASELARD].itemName = calloc(16, sizeof(char));
    strcpy(itemTypes[ITEM_TYPE_DAGGER][ITEM_DAGGER_BASELARD].itemName, "baselard dagger");
    itemTypes[ITEM_TYPE_DAGGER][ITEM_DAGGER_BASELARD].dispChar = dispChar;
    itemTypes[ITEM_TYPE_DAGGER][ITEM_DAGGER_BASELARD].color = BlueBlack;
    itemTypes[ITEM_TYPE_DAGGER][ITEM_DAGGER_BASELARD].attrs = 0;
    itemTypes[ITEM_TYPE_DAGGER][ITEM_DAGGER_BASELARD].weight = 1;
    itemTypes[ITEM_TYPE_DAGGER][ITEM_DAGGER_BASELARD].possibleSlots = 0;
  }
  
  return;
}

void initAxes(){
  axeSubClassId i;
  char dispChar = '/';
  
  itemTypes[ITEM_TYPE_AXE] = calloc(ITEM_AXE_MAX, sizeof(itemType));
  
  // throwing axe
  {
    itemTypes[ITEM_TYPE_AXE][ITEM_AXE_THROWING].baseDamage = 3;
    itemTypes[ITEM_TYPE_AXE][ITEM_AXE_THROWING].baseToHit = 7;
    itemTypes[ITEM_TYPE_AXE][ITEM_AXE_THROWING].baseArmor = 0;
    itemTypes[ITEM_TYPE_AXE][ITEM_AXE_THROWING].throwable = true;
    itemTypes[ITEM_TYPE_AXE][ITEM_AXE_THROWING].twoHandedWield = false;
    itemTypes[ITEM_TYPE_AXE][ITEM_AXE_THROWING].fragile = false;
    itemTypes[ITEM_TYPE_AXE][ITEM_AXE_THROWING].itemName = calloc(13, sizeof(char));
    strcpy(itemTypes[ITEM_TYPE_AXE][ITEM_AXE_THROWING].itemName, "throwing axe");
    itemTypes[ITEM_TYPE_AXE][ITEM_AXE_THROWING].dispChar = dispChar;
    itemTypes[ITEM_TYPE_AXE][ITEM_AXE_THROWING].color = BrownBlack;
    itemTypes[ITEM_TYPE_AXE][ITEM_AXE_THROWING].attrs = 0;
    itemTypes[ITEM_TYPE_AXE][ITEM_AXE_THROWING].weight = 2;
    itemTypes[ITEM_TYPE_AXE][ITEM_AXE_THROWING].possibleSlots = 0;
  }
  
  // battle axe
  {
    itemTypes[ITEM_TYPE_AXE][ITEM_AXE_BATTLE].baseDamage = 9;
    itemTypes[ITEM_TYPE_AXE][ITEM_AXE_BATTLE].baseToHit = 5;
    itemTypes[ITEM_TYPE_AXE][ITEM_AXE_BATTLE].baseArmor = 0;
    itemTypes[ITEM_TYPE_AXE][ITEM_AXE_BATTLE].throwable = true;
    itemTypes[ITEM_TYPE_AXE][ITEM_AXE_BATTLE].twoHandedWield = true;
    itemTypes[ITEM_TYPE_AXE][ITEM_AXE_BATTLE].fragile = false;
    itemTypes[ITEM_TYPE_AXE][ITEM_AXE_BATTLE].itemName = calloc(11, sizeof(char));
    strcpy(itemTypes[ITEM_TYPE_AXE][ITEM_AXE_BATTLE].itemName, "battle axe");
    itemTypes[ITEM_TYPE_AXE][ITEM_AXE_BATTLE].dispChar = dispChar;
    itemTypes[ITEM_TYPE_AXE][ITEM_AXE_BATTLE].color = BrownBlack;
    itemTypes[ITEM_TYPE_AXE][ITEM_AXE_BATTLE].attrs = 0;
    itemTypes[ITEM_TYPE_AXE][ITEM_AXE_BATTLE].weight = 2;
    itemTypes[ITEM_TYPE_AXE][ITEM_AXE_THROWING].possibleSlots = 0;
  }
  
  return;
}

void initLongswords(){
  longswordSubClassId i;
  char dispChar = '/';
  
  itemTypes[ITEM_TYPE_LONGSWORD] = calloc(ITEM_LONGSWORD_MAX, sizeof(itemType));
  
  // steel longsword
  {
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_STEEL].baseDamage = 5;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_STEEL].baseToHit = 4;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_STEEL].baseArmor = 0;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_STEEL].throwable = false;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_STEEL].twoHandedWield = false;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_STEEL].fragile = false;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_STEEL].itemName = calloc(16, sizeof(char));
    strcpy(itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_STEEL].itemName, "steel longsword");
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_STEEL].dispChar = dispChar;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_STEEL].color = WhiteBlack;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_STEEL].attrs = 0;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_STEEL].weight = 8;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_STEEL].possibleSlots = 0;
  }
  
  // I use braces like this because it lets me code-fold these blocks out of the way in my text editor
  
  // silver longsword
  {
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_SILVER].baseDamage = 7;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_SILVER].baseToHit = 3;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_SILVER].baseArmor = 0;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_SILVER].throwable = false;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_SILVER].twoHandedWield = false;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_SILVER].fragile = false;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_SILVER].itemName = calloc(17, sizeof(char));
    strcpy(itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_SILVER].itemName, "silver longsword");
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_SILVER].dispChar = dispChar;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_SILVER].color = CyanBlack;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_SILVER].attrs = 0;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_SILVER].weight = 10;
    itemTypes[ITEM_TYPE_LONGSWORD][ITEM_LONGSWORD_SILVER].possibleSlots = 0;
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
    itemTypes[ITEM_TYPE_CORPSE][i].throwable = false;
    itemTypes[ITEM_TYPE_CORPSE][i].twoHandedWield = false;
    itemTypes[ITEM_TYPE_CORPSE][i].fragile = false;
    itemTypes[ITEM_TYPE_CORPSE][i].itemName = calloc(strlen(corpseSubClassNames[i]) + 8, sizeof(char));
    strcpy(itemTypes[ITEM_TYPE_CORPSE][i].itemName, corpseSubClassNames[i]);
    strcat(itemTypes[ITEM_TYPE_CORPSE][i].itemName, " corpse");
    itemTypes[ITEM_TYPE_CORPSE][i].dispChar = '%';
    itemTypes[ITEM_TYPE_CORPSE][i].color = corpseColors[i];
    itemTypes[ITEM_TYPE_CORPSE][i].attrs = 0;
    itemTypes[ITEM_TYPE_CORPSE][i].possibleSlots = 0;
  }
  
  return;
}