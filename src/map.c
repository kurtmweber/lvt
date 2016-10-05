#define _MAP_C

#include "lvt.h"
#include "level.h"

void setLevelTerrain(level level, unsigned int i, unsigned int j, terrain terrain){
  level[i][j].terrain = terrain;
  
  return;
}

terrain getLevelTerrain(level level, unsigned int i, unsigned int j){
  return level[i][j].terrain;
}