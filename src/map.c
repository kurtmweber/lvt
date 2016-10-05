#define _MAP_C

#include "lvt.h"
#include "level.h"

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