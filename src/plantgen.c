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

#define _PLANTGEN_C

#include <stdbool.h>
#include <stdlib.h>
#include "lvt.h"
#include "plant.h"
#include "allocator.h"

unsigned int placePlantChance = 100;	// likelihood (out of 10,000) that a plant will be placed
					// on a floor

plantList *generateStartingPlants(){
  plantList *node = 0;
  plantList *list = 0;
  coord2D *floors;
  unsigned int i = 0, j = 0;
  
  for (i = 0; i < numLevels; i++){
    floors = enumerateFloors(dungeon[i]);
    j = 0;
    while (floors[j].x){
      if (decidePlacePlant(floors[j], i)){
	node = allocatePlantListEntry();
	list = insertNewPlantNode(list, node);
	node->plant = newRandomOrphanPlant(floors[j], i);
      }
      j++;
    }
  }
  return list;
}

plant *spawnOrphanPlant(plantSpecies species){
  plant *newPlant;
  static rng localRng;
  static bool rngInitd = false;
  
  if (!rngInitd){
    initializeRNG(&localRng);
    rngInitd = true;
  }
  
  newPlant = (plant *)calloc(1, sizeof(plant));
  
  setPlantSpecies(newPlant, species);
  setPlantClass(newPlant, plantSpeciesData[species].plantClass);
  setPlantCurToughness(newPlant, plantSpeciesData[species].toughness);
  setPlantMaxToughness(newPlant, plantSpeciesData[species].toughness);
  setPlantCurGrowth(newPlant, plantSpeciesData[species].maturityLevel);
  setPlantMaxGrowth(newPlant, plantSpeciesData[species].maturityLevel);
  setPlantCurProduction(newPlant, plantSpeciesData[species].maxProduction);
  setPlantMaxProduction(newPlant, plantSpeciesData[species].maxProduction);
  setPlantGrowthRate(newPlant, plantSpeciesData[species].growthRate);
  setPlantProductionTime(newPlant, plantSpeciesData[species].productionTime);
  setPlantProductionProgress(newPlant, 0);
  setPlantDispChar(newPlant, plantSpeciesData[species].dispChar);
  setPlantDispColor(newPlant, plantSpeciesData[species].color);
  setPlantAttrs(newPlant, 0);
  
  return newPlant;
}

plant *spawnPlantFromSeed(plantSpecies species){
  plant *newPlant;
  static rng localRng;
  static bool rngInitd = false;
  
  if (!rngInitd){
    initializeRNG(&localRng);
    rngInitd = true;
  }
  
  newPlant = (plant *)calloc(1, sizeof(plant));
  
  setPlantSpecies(newPlant, species);
  setPlantClass(newPlant, plantSpeciesData[species].plantClass);
  setPlantCurToughness(newPlant, plantSpeciesData[species].toughness);
  setPlantMaxToughness(newPlant, plantSpeciesData[species].toughness);
  setPlantCurGrowth(newPlant, 0);
  setPlantMaxGrowth(newPlant, plantSpeciesData[species].maturityLevel);
  setPlantCurProduction(newPlant, 0);
  setPlantMaxProduction(newPlant, plantSpeciesData[species].maxProduction);
  setPlantGrowthRate(newPlant, plantSpeciesData[species].growthRate);
  setPlantProductionTime(newPlant, plantSpeciesData[species].productionTime);
  setPlantProductionProgress(newPlant, 0);
  setPlantDispChar(newPlant, plantSpeciesData[species].dispChar);
  setPlantDispColor(newPlant, plantSpeciesData[species].color);
  setPlantAttrs(newPlant, 0);
  
  return newPlant;
}

plant *newRandomOrphanPlant(coord2D floor, unsigned int level){
  static rng localRng;
  static bool rngInitd = false;
  plantSpecies newSpecies;
  plant *newPlant;
  coord3D newLocation;
  
  if (!rngInitd){
    initializeRNG(&localRng);
    rngInitd = true;
  }
  
  newSpecies = (plantSpecies)uniformRandomRangeInt(&localRng, 0, MAXPLANTSPECIES - 1);
  
  newPlant = spawnOrphanPlant(newSpecies);
  
  newLocation.x = floor.x;
  newLocation.y = floor.y;
  newLocation.level = level;
  
  placeNewPlant(newPlant, newLocation);
  
  return newPlant;
}

void placeNewPlant(plant *plant, coord3D location){
  setPlantLocation(plant, location);
  setPlantOccupant(dungeon[location.level], location.x, location.y, plant);
  
  return;
}

bool decidePlacePlant(coord2D floor, unsigned int level){
  static rng localRng;
  static bool rngInitd = false;
  
  if (!rngInitd){
    initializeRNG(&localRng);
    rngInitd = true;
  }
  
  if (uniformRandomRangeInt(&localRng, 1, 10000) <= placePlantChance){
    return true;
  } else {
    return false;
  }
}