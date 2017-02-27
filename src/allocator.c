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

#define _ALLOCATOR_C

#include <stdlib.h>
#include "creature.h"
#include "item.h"
#include "level.h"
#include "plant.h"

creatureList *allocateCreatureListEntry(){
  creatureList *node;
  
  node = (creatureList *)calloc(1, sizeof(creatureList));
  
  node->creature = (creature *)calloc(1, sizeof(creature));
  
  return node;
}

plantList *allocatePlantListEntry(){
  plantList *node;
  
  node = (plantList *)calloc(1, sizeof(plantList));
  
  node->plant = (plant *)calloc(1, sizeof(plant));
  
  return node;
}

mapSpaceContents *allocateMapSpaceContentsListEntry(){
  mapSpaceContents *node;
  
  node = (mapSpaceContents *)calloc(1, sizeof(mapSpaceContents));
  
  return node;
}

void freeCreatureListEntry(creatureList *node){
  if (node->creature->name){
    free(node->creature->name);
  }
  
  free(node->creature);
  free(node);
  
  return;
}

item *allocateItem(){
  item *newItem;
  
  newItem = (item *)calloc(1, sizeof(item));
  
  return newItem;
}