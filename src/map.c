#define _MAP_C

#include "lvt.h"
#include "level.h"

const unsigned int exploreRadius = 1;

void setMapSpaceTerrain(level level, unsigned int i, unsigned int j, terrain terrain){
  level[i][j].terrain = terrain;
  
  return;
}

terrain getMapSpaceTerrain(level level, unsigned int i, unsigned int j){
  return level[i][j].terrain;
}

void setMapSpaceExploredState(level level, unsigned int i, unsigned int j, bool state){
  level[i][j].explored = state;
  
  return;
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

bool hasPlantOccupant(level level, unsigned int x, unsigned int y){
  if (level[x][y].plantOccupant){
    return true;
  } else {
    return false;
  }
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

creature *getCreatureOccupant(level level, unsigned int x, unsigned int y){
  return level[x][y].creatureOccupant;
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