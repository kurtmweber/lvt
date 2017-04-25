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

#define _SAVE_C

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lvt.h"
#include "save.h"

uintptr_t objectId;
void **objectIdMap;
void **storedObjects;
unsigned int numStoredObjects;
FILE *saveFile;

// at the moment this whole thing ignores endianness--don't assume that savefiles will be portable

uintptr_t storeCreature(creature *object, encapsulatedTypes type){
  uintptr_t localId;
  creature tmp;
  unsigned int i;
  
  if (!object){
    return 0;
  }
  
  tmp = *object;
  
  CHECK_ALREADY_STORED
  
  setStored((void *)object);
  
  tmp.name = (char *)storeObject(object->name, ENCAP_TYPE_STRING);
  
  tmp.weapon = (item *)storeObject(object->weapon, ENCAP_TYPE_ITEM);
  
  tmp.armor.shirt = (item *)storeObject(object->armor.shirt, ENCAP_TYPE_ITEM);
  tmp.armor.underarmor = (item *)storeObject(object->armor.underarmor, ENCAP_TYPE_ITEM);
  tmp.armor.armor = (item *)storeObject(object->armor.armor, ENCAP_TYPE_ITEM);
  tmp.armor.helmet = (item *)storeObject(object->armor.helmet, ENCAP_TYPE_ITEM);
  tmp.armor.cloak = (item *)storeObject(object->armor.cloak, ENCAP_TYPE_ITEM);
  tmp.armor.gloves = (item *)storeObject(object->armor.gloves, ENCAP_TYPE_ITEM);
  tmp.armor.leggings = (item *)storeObject(object->armor.leggings, ENCAP_TYPE_ITEM);
  tmp.armor.shoes = (item *)storeObject(object->armor.shoes, ENCAP_TYPE_ITEM);
  tmp.armor.shield = (item *)storeObject(object->armor.shield, ENCAP_TYPE_ITEM);
  
  for (i = 0; i < 52; i++){
    tmp.inventory[i] = (item *)storeObject(object->inventory[i], ENCAP_TYPE_ITEM);
  }
  
  encapsulateAndWrite(&tmp, type, sizeof(creature), localId);
  
  return localId;
}

void setStored(void *object){
  storedObjects = realloc(storedObjects, sizeof(void *) * (numStoredObjects + 1));
  
  storedObjects[numStoredObjects] = object;
  
  numStoredObjects++;
  
  return;
}

bool alreadyStored(void *object){
  unsigned int i;
  
  for (i = 0; i < numStoredObjects; i++){
    if (storedObjects[i] == object){
      return true;
    }
  }
  
  return false;
}

uintptr_t storeString(char *object, encapsulatedTypes type){
  uintptr_t localId;
  
  if (!object){
    return 0;
  }
  
  CHECK_ALREADY_STORED
  
  setStored((void *)object);
  
  encapsulateAndWrite(object, type, strlen(object) + 1, localId);
  return localId;
}

uintptr_t storeGlobalStatus(gameStatus *object, encapsulatedTypes type){
  uintptr_t localId;
  
  if (!object){
    return 0;
  }
  
  CHECK_ALREADY_STORED
  
  setStored((void *)object);
  
  encapsulateAndWrite(object, type, sizeof(gameStatus), localId);
}

uintptr_t storeItem(item *object, encapsulatedTypes type){
  uintptr_t localId;
  item tmp;
  
  if (!object){
    return 0;
  }
  
  tmp = *object;
  
  CHECK_ALREADY_STORED
  
  setStored((void *)object);
  
  tmp.owner = (creature *)storeObject(object->owner, ENCAP_TYPE_CREATURE);
  tmp.name = (char *)storeObject(object->name, ENCAP_TYPE_STRING);
  tmp.itemData.itemName = (char *)storeObject(object->itemData.itemName, ENCAP_TYPE_STRING);
  
  encapsulateAndWrite(&tmp, type, sizeof(item), localId);
  return localId;
}

uintptr_t storeMapSpace(mapSpace *object, encapsulatedTypes type){
  uintptr_t localId;
  mapSpace tmp;
  
  if (!object){
    return 0;
  }
  
  // No need to CHECK_ALREADY_STORED here, because there is no way it would be
  // This also saves us on the order of a trillion searches through a list
  
  // CHECK_ALREADY_STORED
  
  tmp = *object;
  
  if (object->creatureOccupant != &player){
    tmp.creatureOccupant = (creature *)storeObject(object->creatureOccupant, ENCAP_TYPE_CREATURE);
  }
  //tmp.creatureOccupant = 0;
  tmp.contents = 0;
  tmp.plantOccupant = 0;
  
  encapsulateAndWrite(&tmp, type, sizeof(mapSpace), localId);
  
  return 0;	// map spaces will never be referenced, so we can use id = 0
}

uintptr_t getObjectId(void *object){  
  uintptr_t i;
  
  if (object == 0){
    return 0;
  }
  
  for (i = 0; i < (objectId - 1); i++){
    if (objectIdMap[i] == object){
      return i + 1;
    }
  }
  
  objectIdMap = realloc(objectIdMap, sizeof(void *) * (objectId));
  objectIdMap[objectId - 1] = object;
  
  return objectId++;
}

void encapsulateAndWrite(void *object, encapsulatedTypes type, size_t objectSize, uintptr_t objectId){
  char *serialData = 0;
  
  fwrite(&objectId, sizeof(uintptr_t), 1, saveFile);
  fwrite(&type, sizeof(encapsulatedTypes), 1, saveFile);
  fwrite(&objectSize, sizeof(size_t), 1, saveFile);
  
  serialData = malloc(objectSize * sizeof(char));
  
  memcpy(serialData, object, objectSize);
  fwrite(serialData, objectSize, 1, saveFile);
  
  free(serialData);
  
  return;
}

uintptr_t storeObject(void *object, encapsulatedTypes type){
  switch(type){
    case ENCAP_TYPE_CREATURE:
      return storeCreature((creature *)object, type);
      break;
    case ENCAP_TYPE_PLAYER:
      return storeCreature((creature *)object, type);
      break;
    case ENCAP_TYPE_STRING:
      return storeString((char *)object, type);
      break;
    case ENCAP_TYPE_ITEM:
      return storeItem((item *)object, type);
      break;
    case ENCAP_TYPE_GLOBALSTATUS:
      return storeGlobalStatus((gameStatus *)object, type);
      break;
    case ENCAP_TYPE_MAPSPACE:
      return storeMapSpace((mapSpace *)object, type);
      break;
    default:
      return 0;
  }
}


void doSave(){
  unsigned int i, j, k;
  level curLevel;
  
  resetObjectReferences();
  
  // when reading, the first creature object encountered will be the player
  // so it must be the first to be written
  
  storeObject(&player, ENCAP_TYPE_PLAYER);
  storeObject(&status, ENCAP_TYPE_GLOBALSTATUS);
  
  for (i = 0; i < numLevels; i++){
    for (j = 0; j < dimMapX; j++){
      for (k = 0; k < dimMapY; k++){
	storeObject(&dungeon[i][j][k], ENCAP_TYPE_MAPSPACE);
      }
    }
  }
  
  fclose(saveFile);
  
  free(objectIdMap);
}

void resetObjectReferences(){
  objectIdMap = 0;
  objectId = 1;	// we start objectId at 1, so we can use 0 to represent a null pointer
  storedObjects = 0;
  numStoredObjects = 0;
  
  saveFile = fopen("lvtsave", "wb");
  
  if (!saveFile){
    exit(EXIT_FAILURE);
  }
  
  return;
}