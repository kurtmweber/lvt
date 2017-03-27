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

#define _PLANTS_C

#include "lvt.h"

void updatePlants(){
  plantList *curPlantNode;
  plant *curPlant;
  unsigned long long i;
  char numPlants[32];
  unsigned int curToughness;
  
  curPlantNode = plants;
  
  do {
    curPlant = curPlantNode->plant;    
    // we have to do this before we update the life cycle, because if the plant dies as a result of
    // the update, the current node in the plant list is destroyed.
    curPlantNode = curPlantNode->next;

  } while (curPlantNode);
  
  return;
}