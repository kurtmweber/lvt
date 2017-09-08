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

#define _READSAVE_C

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "lvt.h"
#include "save.h"
#include "allocator.h"

uintptr_t numObjects;
readObjectList *objectList;
uintptr_t numItems;
item **itemList;

bool readSaveFile(){
  FILE *saveFile;
  fileObjectInfo info;
  uintptr_t i;
  void *data = 0;
  coord3D itemLoc;
  
  objectList = 0;
  numObjects = 0;
  
  itemList = 0;
  numItems = 0;
  
  saveFile = fopen("lvtsave", "r");
  if (!saveFile){
    return false;
  }
  
  while (!feof(saveFile)){
    info = getFileObjectInfo(saveFile);
    data = malloc(info.size);
    getFileObjectData(data, info.size, saveFile);
    addToObjectList(data, info.id, info.type, info.size);
  }
  
  numObjects--;	// b/c of how feof works, we'll always get one junk entry at the end of objectList,
		// which we want to ignore in the future
  
  // we have to read the player object first because we have to reset the pointer in
  // objectList to &player for player's inventory item ownership to be set properly
  for (i = 0; i < numObjects; i++){
    switch(objectList[i].type){
      case ENCAP_TYPE_PLAYER:
	readSavedPlayerObject((creature *)objectList[i].ptr);
	break;
      default:
	break;
    }
  }
  
  for (i = 0; i < numObjects; i++){
    switch(objectList[i].type){
      case ENCAP_TYPE_CREATURE:
	readSavedCreatureObject((creature *)objectList[i].ptr);
	break;
      case ENCAP_TYPE_STRING:
	readSavedStringObject((char *)objectList[i].ptr);
	break;
      case ENCAP_TYPE_ITEM:
	readSavedItemObject((item *)objectList[i].ptr);
	break;
      case ENCAP_TYPE_GLOBALSTATUS:
	readSavedGlobalStatusObject((gameStatus *)objectList[i].ptr);
	break;
      case ENCAP_TYPE_MAPSPACE:
	readSavedMapSpaceObject((mapSpace *)objectList[i].ptr);
	break;
      case ENCAP_TYPE_PLANT:
	readPlantObject((plant *)objectList[i].ptr);
	break;
      default:
	break;
    }
  }
  
  for (i = 0; i < numItems; i++){
    if (!getItemOwned(itemList[i])){
      itemLoc = getItemLocation(itemList[i]);
      addContents(itemLoc.level, itemLoc.x, itemLoc.y, itemList[i]);
    }
  }
  
  free(itemList);
}

void readSavedMapSpaceObject(mapSpace *object){
  static unsigned int i = 0, j = 0, k = 0;
  static bool initialized = false;
  unsigned int a = 0, b = 0;
  
  if (i == numLevels){
    return;
  }
  
  if (!initialized){
    dungeon = calloc(numLevels, sizeof(level *));
    for (a = 0; a < numLevels; a++){
      dungeon[a] = (mapSpace **)calloc(dimMapX, sizeof(mapSpace *));
      for (b = 0; b < dimMapX; b++){
	dungeon[a][b] = (mapSpace *)calloc(dimMapY, sizeof(mapSpace));
      }
    }
    initialized = true;
  }
  
  object->creatureOccupant = findInObjectList((uintptr_t)object->creatureOccupant);
  object->plantOccupant = findInObjectList((uintptr_t)object->plantOccupant);
  
  dungeon[i][j][k] = *object;
  
  if (j == (dimMapX - 1) && k == (dimMapY - 1)){
    j = 0;
    k = 0;
    i++;
  } else if (k == (dimMapY - 1)){
    k = 0;
    j++;
  } else {
    k++;
  }
  
  return;
}

void readSavedGlobalStatusObject(gameStatus *object){
  status = *object;
  
  return;
}

void readSavedItemObject(item *object){
  object->name = findInObjectList((uintptr_t)object->name);
  
  object->owner = findInObjectList((uintptr_t)object->owner);
  
  object->itemData.itemName = findInObjectList((uintptr_t)object->itemData.itemName);
  
  // add to the seed linked list if that's what we've got here
  if (object->itemClass == ITEM_TYPE_SEED){
    seedList *newSeed;
    
    newSeed = allocateSeedListEntry();
    newSeed->seed = object;
    seeds = insertNewSeedNode(seeds, newSeed);
  }
  
  numItems++;
  
  itemList = realloc(itemList, numItems * sizeof(item *));
  itemList[numItems - 1] = object;
  
  return;
}

void readPlantObject(plant *object){
  plantList *newPlant;
  
  newPlant = allocatePlantListEntry();
  newPlant->plant = object;
  plants = insertNewPlantNode(plants, newPlant);
}

void readSavedStringObject(char *object){
  return;
}

void readSavedCreatureObject(creature *object){
  unsigned int i;
  creatureList *node = 0;
  
  object->name = findInObjectList((uintptr_t)object->name);
  object->armor.shirt = findInObjectList((uintptr_t)object->armor.shirt);
  object->armor.underarmor = findInObjectList((uintptr_t)object->armor.underarmor);
  object->armor.armor = findInObjectList((uintptr_t)object->armor.armor);
  object->armor.helmet = findInObjectList((uintptr_t)object->armor.helmet);
  object->armor.cloak = findInObjectList((uintptr_t)object->armor.cloak);
  object->armor.gloves = findInObjectList((uintptr_t)object->armor.gloves);
  object->armor.leggings = findInObjectList((uintptr_t)object->armor.leggings);
  object->armor.shoes = findInObjectList((uintptr_t)object->armor.shoes);
  object->armor.shield = findInObjectList((uintptr_t)object->armor.shield);
  
  object->weapon = findInObjectList((uintptr_t)object->weapon);
  
  object->wieldNextTurn = findInObjectList((uintptr_t)object->wieldNextTurn);
  
  for (i = 0; i < 52; i++){
    object->inventory[i] = findInObjectList((uintptr_t)object->inventory[i]);
  }
  
  node = allocateCreatureListEntry();
  node->creature = object;
  
  creatures = insertNewCreatureNode(creatures, node);
    
  return;
}

void readSavedPlayerObject(creature *object){
  unsigned int i;
  
  player = *object;
  
  player.name = findInObjectList((uintptr_t)object->name);
  player.armor.shirt = findInObjectList((uintptr_t)object->armor.shirt);
  player.armor.underarmor = findInObjectList((uintptr_t)object->armor.underarmor);
  player.armor.armor = findInObjectList((uintptr_t)object->armor.armor);
  player.armor.helmet = findInObjectList((uintptr_t)object->armor.helmet);
  player.armor.cloak = findInObjectList((uintptr_t)object->armor.cloak);
  player.armor.gloves = findInObjectList((uintptr_t)object->armor.gloves);
  player.armor.leggings = findInObjectList((uintptr_t)object->armor.leggings);
  player.armor.shoes = findInObjectList((uintptr_t)object->armor.shoes);
  player.armor.shield = findInObjectList((uintptr_t)object->armor.shield);
  
  player.weapon = findInObjectList((uintptr_t)object->weapon);
  
  for (i = 0; i < 52; i++){
    player.inventory[i] = findInObjectList((uintptr_t)object->inventory[i]);
  }
  
  setPlayerObjectPtr(&player);
  
  return;
}

void setPlayerObjectPtr(creature *playerPtr){
  uintptr_t i;
  
  for (i = 0; i < numObjects; i++){
    if (objectList[i].type == ENCAP_TYPE_PLAYER){
      objectList[i].ptr = playerPtr;
    }
  }
  
  return;
}

void *findInObjectList(uintptr_t object){
  uintptr_t i;
  
  if (object == 0){
    return 0;
  }
  
  for (i = 0; i < numObjects; i++){
    if (objectList[i].id == object){
      return objectList[i].ptr;
    }
  }
  
  return 0;
}

void addToObjectList(void *data, uintptr_t id, encapsulatedTypes type, size_t size){
  objectList = realloc(objectList, (numObjects + 1) * sizeof(readObjectList));
  
  objectList[numObjects].id = id;
  objectList[numObjects].ptr = data;
  objectList[numObjects].type = type;
  
  numObjects++;
  
  return;
}

void getFileObjectData(void *data, size_t size, FILE *saveFile){
  fread(data, size, 1, saveFile);
}

fileObjectInfo getFileObjectInfo(FILE *saveFile){
  fileObjectInfo info;
  
  fread(&(info.id), sizeof(uintptr_t), 1, saveFile);
  fread(&(info.type), sizeof(encapsulatedTypes), 1, saveFile);
  fread(&(info.size), sizeof(size_t), 1, saveFile);
  
  return info;
}