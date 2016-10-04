#define _LEVELGEN_C

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "lvt.h"
#include "level.h"

// some tuning constants
const unsigned int roomCoverageMu = 3000;
const unsigned int roomCoverageSigma = 500;
const unsigned int roomCoverageFloor = 500;
const unsigned int roomCoverageCeiling = 5000;
const unsigned int straightness = 850;	// likelihood (out of 1000) that the next space dug out for a tunnel
					// will be towards the target

const unsigned int numLevels = 1;

rng levelGenRNG;

void initializeLevelGen(){  
  initializeRNG(&levelGenRNG);
  
  return;
}

level generateLevel(){
  
  unsigned int coverageGoal = 0;
  
  level level;
  
  do {
    coverageGoal = (unsigned int)round(normalRandomInt(&levelGenRNG, roomCoverageMu, roomCoverageSigma));
  } while ((coverageGoal < roomCoverageFloor) || (coverageGoal > roomCoverageCeiling));
  
  level = initLevel();
  
  digLevel(level, coverageGoal);
  
  return level;
}

unsigned int currentCoverage(level level){
  unsigned int i = 0, j = 0, coverage = 0;
  
  for (i = 0; i < 100; i++){
    for (j = 0; j < 100; j++){
      if (getLevelTerrain(level, i, j) == FLOOR){
	coverage++;
      }
    }
  }
  
  return coverage;
}

void digLevel(level level, unsigned int coverageGoal){
  unsigned int a = 0, b = 0, i = 0, j = 0, x = 0, y = 0;
  unsigned int numRooms = 0;
  
  centerPoint *centerPoints = 0;
  
  while (currentCoverage(level) < coverageGoal){
    // grow the array of centerPoints by 1
    numRooms++; // leave room for the null pointer at the end to signify the end of the list
    centerPoints = realloc(centerPoints, (numRooms + 1) * sizeof(centerPoint));
    
    // we generate the room size first, so we know how far down or over it can be located
    a = uniformRandomRangeInt(&levelGenRNG, 2, 10);
    b = uniformRandomRangeInt(&levelGenRNG, 2, 10);
    x = uniformRandomRangeInt(&levelGenRNG, 1, 98 - (a - 1));
    y = uniformRandomRangeInt(&levelGenRNG, 1, 98 - (b - 1));
    
    centerPoints[numRooms - 1].x = ((a / 2) + x); // zero-based array indexing sucks sometimes
    centerPoints[numRooms - 1].y = ((b / 2) + y);
    centerPoints[numRooms - 1].complete = false;
    centerPoints[numRooms].x = 0;	// we'll only ever check x, but we'll set y too in case I'm an
    centerPoints[numRooms].y = 0;	// idiot at some point in the future
    centerPoints[numRooms].complete = false;
    
    for (i = x; i < x + a; i++){
      for (j = y; j < y + b; j++){
	setLevelTerrain(level, i, j, FLOOR);
      }
    }
  }
  
  digTunnels(level, centerPoints);
  
  return;
}

void digTunnels(level level, centerPoint *centerPoints){
  unsigned int i = 0;
  unsigned int nearestNeighbor = 0;
  int xDist = 0, yDist = 0;
  unsigned int absDist = 0;
  unsigned int curX = 0, curY = 0;
  unsigned int newX = 0, newY = 0;
  unsigned int tgtX = 0, tgtY = 0;
  
  while(centerPoints[i].x){	
    // No room will have a centerpoint at (0, y) since that's the permanent wall at the edge of the map,
    // so we can use it as a flag for the end of the list.  Additionally, since the first call to
    // findNearestNeighbor is to i = 0, and since we always have at least two (max i = 1) rooms, i = 0
    // will always have a nearest neighbor that's not itself, and so the first call to findNearestNeighbor
    // will always be non-zero.  And since we mark i = 0 complete, no future calls to findNearestNeighbor
    // will find room 0 as a non-complete nearest neighbor, so we can use a return value of 0 to indicate
    // that there was no incomplete nearest neighbor
    nearestNeighbor = findNearestNeighbor(i, centerPoints);
    if (!nearestNeighbor){
      i++;
      continue;
    }
    
    tgtX = centerPoints[nearestNeighbor].x;
    tgtY = centerPoints[nearestNeighbor].y;
    curX = centerPoints[i].x;
    curY = centerPoints[i].y;
    
    do {
      xDist = tgtX - curX;
      yDist = tgtY - curY;
      absDist = abs(xDist) + abs(yDist);
      
      if (uniformRandomRangeInt(&levelGenRNG, 1, 1000) <= straightness){
	if (uniformRandomRangeInt(&levelGenRNG, 0, absDist) < abs(xDist)){
	  ((xDist < 0) ? (newX = curX - 1) : (newX = curX + 1));
	  newY = curY;
	} else {
	  newX = curX;
	  ((yDist < 0) ? (newY = curY - 1) : (newY = curY + 1));
	}
      } else {
	if (uniformRandomRangeInt(&levelGenRNG, 0, absDist) < abs(xDist)){
	  ((xDist < 0) ? (newX = curX + 1) : (newX = curX - 1));
	  newY = curY;
	} else {
	  newX = curX;
	  ((yDist < 0) ? (newY = curY + 1) : (newY = curY + 1));
	}
      }
      
      // want to make sure we don't dig into permanent rock; if we do, try again
      if ((newX != 0) && (newX != 99) && (newY != 0) && (newY != 99)){
	setLevelTerrain(level, newX, newY, FLOOR);
	curX = newX;
	curY = newY;
      }
    } while ((curX != tgtX) || (curY  != tgtY)); 
    
    centerPoints[i].complete = true;
    i++;
  }
  
  return;
}

unsigned int findNearestNeighbor(unsigned int i, centerPoint *centerPoints){
  unsigned int j = 0;
  unsigned int nearestNeighbor = 0;
  unsigned int tmpNearestNeighborDistanceX, tmpNearestNeighborDistanceY, tmpNearestNeighborDistance;
  unsigned int nearestNeighborDistance;
  
  while(centerPoints[j].x){
    if ((j == i) || (centerPoints[j].complete == true)){
      j++;
      continue;
    }
    tmpNearestNeighborDistanceX = abs(centerPoints[i].x - centerPoints[j].x);
    tmpNearestNeighborDistanceY = abs(centerPoints[i].y - centerPoints[j].y);
    tmpNearestNeighborDistance = tmpNearestNeighborDistanceX + tmpNearestNeighborDistanceY;
    
    if (tmpNearestNeighborDistance < nearestNeighborDistance){
      nearestNeighborDistance = tmpNearestNeighborDistance;
      nearestNeighbor = j;
    }
    j++;
  }
  
  return nearestNeighbor;
}

void setLevelTerrain(level level, unsigned int i, unsigned int j, terrain terrain){
  level[i][j].terrain = terrain;
  
  return;
}

terrain getLevelTerrain(level level, unsigned int i, unsigned int j){
  return level[i][j].terrain;
}

level initLevel(){
  level level;
  unsigned int i = 0, j = 0;
  
  // should be the only place where the internals of level as an array of mapSpaces should matter
  
  level = (mapSpace **)calloc(100, sizeof(mapSpace *));
  if (!level){
    perror("lvt: ");
  }
  
  for (i = 0; i < 100; i++){
    level[i] = (mapSpace *)calloc(100, sizeof(mapSpace));
    if (!level){
      perror("lvt: ");
    }
  }
  
   for (i = 0; i < 100; i++){
    for (j = 0; j < 100; j++){
      setLevelTerrain(level, i, j, WALL);
    }
  }
  
  return level;
}
