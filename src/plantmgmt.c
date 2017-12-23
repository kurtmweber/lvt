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

#define _PLANTMGMT_C


#include <math.h>

#include "lvt.h"

#include "allocator.h"
#include "creature.h"
#include "creaturemgmt.h"
#include "level.h"
#include "plant.h"
#include "types.h"


void setPlantSpecies(plant *plant, plantSpecies species){
  plant->species = species;
  
  return;
}

plantSpecies getPlantSpecies(plant *plant){
  return plant->species;
}

void setPlantClass(plant *plant, plantClass plantClass){
  plant->plantClass = plantClass;
  
  return;
}

void setPlantCurToughness(plant *plant, unsigned int toughness){
  plant->curToughness = toughness;
  
  return;
}

unsigned int getPlantCurToughness(plant *plant){
  return plant->curToughness;
}

unsigned int getPlantMaxToughness(plant *plant){
  return plant->maxToughness;
}

void setPlantMaxToughness(plant *plant, unsigned int toughness){
  plant->maxToughness = toughness;
  
  return;
}

void setPlantCurGrowth(plant *plant, unsigned int growth){
  plant->curGrowth = growth;
  
  return;
}

unsigned int getPlantCurGrowth(plant *plant){
  return plant->curGrowth;
}

void setPlantMaxGrowth(plant *plant, unsigned int growth){
  plant->maxGrowth = growth;
  
  return;
}

unsigned int getPlantMaxGrowth(plant *plant, unsigned int growth){
  return plant->maxGrowth;
}

void setPlantCurProduction(plant *plant, unsigned int production){
  plant->curProduction = production;
  
  return;
}

unsigned int getPlantCurProduction(plant *plant){
  return plant->curProduction;
}

void setPlantMaxProduction(plant *plant, unsigned int production){
  plant->maxProduction = production;
  
  return;
}

unsigned int getPlantMaxProduction(plant *plant){
  return plant->maxProduction;
}

void setPlantGrowthRate(plant *plant, unsigned int growthRate){
  plant->growthRate = growthRate;
  
  return;
}

unsigned int getPlantGrowthRate(plant *plant){
  return plant->growthRate;
}

void setPlantProductionTime(plant *plant, unsigned int productionTime){
  plant->productionTime = productionTime;
  
  return;
}

unsigned int getPlantProductionTime(plant *plant){
  return plant->productionTime;
}

void setPlantProductionProgress(plant *plant, unsigned int progress){
  plant->productionProgress = progress;
  
  return;
}

unsigned int getPlantProductionProgress(plant *plant){
  return plant->productionProgress;
}

void setPlantDispChar(plant *plant, char dispChar){
  plant->dispChar = dispChar;
  
  return;
}

void setPlantDispColor(plant *plant, colorPairs color){
  plant->dispColor = color;
  
  return;
}

void setPlantAttrs(plant *plant, unsigned int attrs){
  plant->attrs = attrs;
  
  return;
}

void setPlantLocation(plant *plant, coord3D location){
  plant->location = location;
  
  return;
}

char getPlantDispChar(plant *plant){
  return plant->dispChar;
}

colorPairs getPlantColor(plant *plant){
  return plant->dispColor;
}

coord3D getPlantLocation(plant *plant){
  return plant->location;
}

void killPlant(plant *plant){
  plantList *pNode;
  coord3D plantLoc;
  
  plantLoc = getPlantLocation(plant);
  
  clearPlantOccupant(dungeon[plantLoc.level], plantLoc.x, plantLoc.y);
  
  pNode = findPlantListEntry(plants, plant);
  removePlantNode(plants, pNode);
  freePlantListEntry(pNode);
  return;
}

void tramplePlant(plant *plant, creature *creature){
  unsigned int curPlantToughness;
  unsigned int damageAmount;

  curPlantToughness = getPlantCurToughness(plant);
    
  damageAmount = (unsigned int)floor((double)getCreatureWeight(creature) / 100.0);
    
  if (damageAmount >= curPlantToughness){
    setPlantCurToughness(plant, 0);
    killPlant(plant);
  } else {
    setPlantCurToughness(plant, curPlantToughness - damageAmount);
  }
}