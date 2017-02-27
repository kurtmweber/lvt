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

#include "plant.h"
#include "types.h"

void setPlantSpecies(plant *plant, plantSpecies species){
  plant->species = species;
  
  return;
}

void setPlantClass(plant *plant, plantClass plantClass){
  plant->plantClass = plantClass;
  
  return;
}

void setPlantCurToughness(plant *plant, unsigned int toughness){
  plant->curToughness = toughness;
  
  return;
}

void setPlantMaxToughness(plant *plant, unsigned int toughness){
  plant->maxToughness = toughness;
  
  return;
}

void setPlantCurGrowth(plant *plant, unsigned int growth){
  plant->curGrowth = growth;
  
  return;
}

void setPlantMaxGrowth(plant *plant, unsigned int growth){
  plant->maxGrowth = growth;
  
  return;
}

void setPlantCurProduction(plant *plant, unsigned int production){
  plant->curProduction = production;
  
  return;
}

void setPlantMaxProduction(plant *plant, unsigned int production){
  plant->maxProduction = production;
  
  return;
}

void setPlantGrowthRate(plant *plant, unsigned int growthRate){
  plant->growthRate = growthRate;
  
  return;
}

void setPlantProductionTime(plant *plant, unsigned int productionTime){
  plant->productionTime = productionTime;
  
  return;
}

void setPlantProductionProgress(plant *plant, unsigned int progress){
  plant->productionProgress = progress;
  
  return;
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