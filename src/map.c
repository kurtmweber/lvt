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

#define _MAP_C

#include <stdlib.h>
#include "lvt.h"
#include "level.h"

const unsigned int exploreRadius = 1;

void setMapSpaceTerrain(level level, unsigned int x, unsigned int y, terrain terrain){
  level[x][y].terrain = terrain;
  
  return;
}

terrain getMapSpaceTerrain(level level, unsigned int x, unsigned int y){
  return level[x][y].terrain;
}

void setMapSpaceExploredState(level level, unsigned int i, unsigned int j, bool state){
  level[i][j].explored = state;
  
  return;
}

void setTerrainData(level level, unsigned int x, unsigned int y, terrain terrain, void *data){
  unsigned int *searchCountdown;
  
  switch (terrain){
    case HIDDENDOOR:
      searchCountdown = (unsigned int *)data;
      level[x][y].terrainData.searchCountdown = *searchCountdown;
      break;
    default:
      break;
  }
  return;
}

void *getTerrainData(level level, unsigned int x, unsigned int y, terrain terrain){
  unsigned int *searchCountdown;
  
  switch (terrain){
    case HIDDENDOOR:
      searchCountdown = calloc(1, sizeof(level[x][y].terrainData.searchCountdown));
      *searchCountdown = level[x][y].terrainData.searchCountdown;
      return (void *)searchCountdown;
    default:
      break;
  }
  
  return 0;
}

bool getMapSpaceExploredState(level level, unsigned int i, unsigned int j){
  return level[i][j].explored;
}

coord2D findLevelUpstair(level level){
  unsigned int x = 0, y = 0;
  coord2D coords;
  
  for (x = 0; x < dimMapX; x++){
    for (y = 0; y < dimMapY; y++){
      if (getMapSpaceTerrain(level, x, y) == UPSTAIR){
	coords.x = x;
	coords.y = y;
	return coords;
      }
    }
  }
  
  coords.x = 0;
  coords.y = 0;
  return coords;
}

coord2D findLevelDownstair(level level){
  unsigned int x = 0, y = 0;
  coord2D coords;
  
  for (x = 0; x < dimMapX; x++){
    for (y = 0; y < dimMapY; y++){
      if (getMapSpaceTerrain(level, x, y) == DOWNSTAIR){
	coords.x = x;
	coords.y = y;
	return coords;
      }
    }
  }
  
  coords.x = 0;
  coords.y = 0;
  return coords;
}

void initializeMapSpaceContents(level level, unsigned int x, unsigned int y){
  level[x][y].contents = NULL;
  level[x][y].plantOccupant = NULL;
  level[x][y].creatureOccupant = NULL;
  return;
}

bool hasContents(level level, unsigned int x, unsigned int y){
  if (level[x][y].contents){
    return true;
  } else {
    return false;
  }
}

void addContents(level level, unsigned int x, unsigned int y, item *item){
  mapSpaceContents *node;
  
  node = allocateMapSpaceContentsListEntry();
  
  if (level[x][y].contents){
    node->next = level[x][y].contents;
    level[x][y].contents->prev = node;
  }
  
  node->prev = 0;
  level[x][y].contents = node;
  node->item = item;
  
  return;
}

mapSpaceContents *getContents(level level, unsigned int x, unsigned int y){
  return level[x][y].contents;
}

bool hasPlantOccupant(level level, unsigned int x, unsigned int y){
  if (level[x][y].plantOccupant){
    return true;
  } else {
    return false;
  }
}

void setPlantOccupant(level level, unsigned int x, unsigned int y, plant *plant){
  level[x][y].plantOccupant = plant;
  
  return;
}

bool hasCreatureOccupant(level level, unsigned int x, unsigned int y){
  if (level[x][y].creatureOccupant){
    return true;
  } else {
    return false;
  }
}

void setCreatureOccupant(level level, unsigned int x, unsigned int y, creature *creature){
  level[x][y].creatureOccupant = creature;
  
  return;
}

void clearCreatureOccupant(level level, unsigned int x, unsigned int y){
  level[x][y].creatureOccupant = 0;
  
  return;
}

void clearPlantOccupant(level level, unsigned int x, unsigned int y){
  level[x][y].plantOccupant = 0;
  
  return;
}

creature *getCreatureOccupant(level level, unsigned int x, unsigned int y){
  return level[x][y].creatureOccupant;
}

plant *getPlantOccupant(level level, unsigned x, unsigned int y){
  return level[x][y].plantOccupant;
}

void updateRegionExploredState(level level, unsigned int x, unsigned int y, bool state){
  setMapSpaceExploredState(level, x, y - 1, state);
  setMapSpaceExploredState(level, x, y, state);
  setMapSpaceExploredState(level, x, y + 1, state);
  setMapSpaceExploredState(level, x - 1, y - 1, state);
  setMapSpaceExploredState(level, x - 1, y, state);
  setMapSpaceExploredState(level, x - 1, y + 1, state);
  setMapSpaceExploredState(level, x + 1, y - 1, state);
  setMapSpaceExploredState(level, x + 1, y, state);
  setMapSpaceExploredState(level, x + 1, y + 1, state);
  
  return;
}