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

#define _CREATUREGEN_C

#include <stdbool.h>
#include <stdlib.h>
#include "lvt.h"
#include "creature.h"
#include "types.h"

unsigned int placeCreatureChance = 100;	// likelihood (out of 10,000) that a creature will be placed
					// on a floor

creatureList *generateStartingCreatures(){
  creatureList *node = 0;
  creatureList *list = 0;
  coord2D *floors;
  unsigned int i = 0, j = 0;
  
  for (i = 0; i < numLevels; i++){
    floors = enumerateFloors(dungeon[i]);
    j = 0;
    while (floors[j].x){
      if (decidePlaceCreature(floors[j], i)){
	node = allocateCreatureListEntry();
	list = insertNewCreatureNode(list, node);
	node->creature = newRandomOrphanCreature(floors[j], i);
      }
      j++;
    }
  }
  return list;
}

creature *spawnOrphanCreature(creatureSpecies species, creatureClass class){
  creature *newCreature;
  newCreature = (creature *)calloc(1, sizeof(creature));
  setCreatureSpecies(newCreature, species);
  setCreatureClass(newCreature, class);
  static rng localRng;
  static bool rngInitd = false;
  bioSex sex;
  unsigned int faction;
  
  if (!rngInitd){
    initializeRNG(&localRng);
    rngInitd = true;
  }
  
  genOrphanCreatureStats(newCreature);
  changeDispChar(newCreature, speciesData[species].dispChar);
  setCreatureColor(newCreature, speciesData[species].color);
  setCreatureAttribute(newCreature, 0);
  
  sex = (bioSex)coinFlip(&localRng);
  faction = uniformRandomRangeInt(&localRng, 1, getNumFactions());
  
  setCreatureBioSex(newCreature, sex);
  setCreatureFaction(newCreature, faction);
  
  setCreatureName(newCreature, generateName());
  setCreatureSpeed(newCreature, speciesData[species].speed);
  setCreatureWeight(newCreature, speciesData[species].weight);
  setCreatureLifePace(newCreature, speciesData[species].lifePace);
  
  setCreatureLastMove(newCreature, 4);
  initCreatureArmor(newCreature);
  initCreatureWeapon(newCreature);
  initCreatureInventory(newCreature);
  
  return newCreature;
}

void placeNewCreature(creature *creature, coord3D location){
  setCreatureLocation(creature, location);
  setCreatureOccupant(dungeon[location.level], location.x, location.y, creature);
  
  return;
}

creature *newRandomOrphanCreature(coord2D floor, unsigned int level){
  static rng localRng;
  static bool rngInitd = false;
  creatureSpecies newSpecies;
  creatureClass newClass;
  creature *newCreature;
  coord3D newLocation;
  
  if (!rngInitd){
    initializeRNG(&localRng);
    rngInitd = true;
  }
  
  newSpecies = (creatureSpecies)uniformRandomRangeInt(&localRng, 0, MAXCREATURESPECIES - 1);
  newClass = (creatureClass)uniformRandomRangeInt(&localRng, 0, MAXCREATURECLASS - 1);
  
  newCreature = spawnOrphanCreature(newSpecies, newClass);
  
  newLocation.x = floor.x;
  newLocation.y = floor.y;
  newLocation.level = level;
  
  placeNewCreature(newCreature, newLocation);
  
  return newCreature;
}

bool decidePlaceCreature(coord2D floor, unsigned int level){
  static rng localRng;
  static bool rngInitd = false;
  
  if (!rngInitd){
    initializeRNG(&localRng);
    rngInitd = true;
  }
  
  if (uniformRandomRangeInt(&localRng, 1, 10000) <= placeCreatureChance){
    return true;
  } else {
    return false;
  }
}