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

const unsigned int dimMapX = 100;	// map dimensions
const unsigned int dimMapY = 100;
const unsigned int minRoomX = 2;	// max and min sizes of a room
const unsigned int minRoomY = 2;
const unsigned int maxRoomX = 10;
const unsigned int maxRoomY = 10;

//const unsigned int doorLikelihood = 500;	// likelihood (out of 1000) that a door-eligible floor will
						// become a door
const unsigned int doorLikelihood = 0;
const unsigned int hiddenDoorLikelihood = 500;	// likelihood (out of 1000) that a door will be hidden

const unsigned int numLevels = 1;

rng levelGenRNG;

void initializeLevelGen(){  
  initializeRNG(&levelGenRNG);
  
  return;
}

map generateMap(){
  map map;
  int i = 0;
  
  map = calloc(100, sizeof(level *));
  
  for (i = 0; i < 100; i++){
    map[i] = generateLevel(i);
  }
  
  return map;
}

level generateLevel(unsigned int levelNum){
  
  unsigned int coverageGoal = 0;	// goal for # of spaces to be covered by floor
					// we don't shoot for this exactly; instead, we test the #
					// of floors after generating and placing each room, and once
					// the # of floors meets or exceeds this value, we're done
  
  level level;
  
  do {
    coverageGoal = (unsigned int)round(normalRandomInt(&levelGenRNG, roomCoverageMu, roomCoverageSigma));
  } while ((coverageGoal < roomCoverageFloor) || (coverageGoal > roomCoverageCeiling));
  
  level = initLevel();
  
  digLevel(level, coverageGoal);
  placeDoors(level);
  placeStairs(level, levelNum);
  
  return level;
}

void placeStairs(level level, unsigned int levelNum){
  coord2D *floors;
  unsigned int i = 0;
  unsigned int j = 0;
  unsigned int k = 0;
  
  floors = enumerateFloors(level);
  
  while(floors[i].x){
    i++;
  }
  
  j = uniformRandomRangeInt(&levelGenRNG, 0, i - 1);
  setMapSpaceTerrain(level, floors[j].x, floors[j].y, UPSTAIR);
  
  do {
    k = uniformRandomRangeInt(&levelGenRNG, 0, i - 1);
  } while (k == j);	// just want to make sure we're not putting the downstair on the same space as
			// the upstair
  
  if (levelNum != 99){
    setMapSpaceTerrain(level, floors[k].x, floors[k].y, DOWNSTAIR);
  }
  
  free(floors);
  
  return;
}

coord2D *findDoorEligible(level level){
  coord2D *doorEligible = 0;
  coord2D *floors = 0;
  unsigned int i = 0;
  unsigned int numEligible = 0;
  
  floors = enumerateFloors(level);
  
  while(floors[i].x){	// since index 0 is impenetrable rock...yeah, you get the idea
    if (isDoorEligible(level, floors[i])){
      numEligible++;
      doorEligible = realloc(doorEligible, (numEligible + 1) * sizeof(coord2D));
      doorEligible[numEligible - 1].x = floors[i].x;
      doorEligible[numEligible - 1].y = floors[i].y;
      doorEligible[numEligible].x = 0;
      doorEligible[numEligible].y = 0;
    }
    i++;
  }
  
  free(floors);
  
  return doorEligible;  
}

bool isDoorEligible(level level, coord2D coords){
  // this is going to be complicated
  // basically, we want any of the following situations:
  // X.X     #.#     X##     ##X     
  // #o#     #o#     .o.     .o.
  // #.#     X.X     X##     ##X
  // where:
  // o is the point we're looking at
  // . is an adjacent point that MUST be a floor
  // # is an adjacent point that MUST be a wall
  // X is an adjacent point that MAY be EITHER a wall or a floor, but AT LEAST one point indicated
  //   with this symbol MUST be a floor
  // hold on to your hats, it'll be a wild ride
  
  unsigned int i = 0, j = 0;
  unsigned int numTrue = 0;
  
  terrain neighborMap[3][3];
  bool mapMatch[3][3];
  
  neighborMap[0][0] = getMapSpaceTerrain(level, coords.x - 1, coords.y - 1);
  neighborMap[0][1] = getMapSpaceTerrain(level, coords.x - 1, coords.y);
  neighborMap[0][2] = getMapSpaceTerrain(level, coords.x - 1, coords.y + 1);
  neighborMap[1][0] = getMapSpaceTerrain(level, coords.x, coords.y - 1);
  neighborMap[1][1] = getMapSpaceTerrain(level, coords.x, coords.y);
  neighborMap[1][2] = getMapSpaceTerrain(level, coords.x, coords.y + 1);
  neighborMap[2][0] = getMapSpaceTerrain(level, coords.x + 1, coords.y - 1);
  neighborMap[2][1] = getMapSpaceTerrain(level, coords.x + 1, coords.y);
  neighborMap[2][2] = getMapSpaceTerrain(level, coords.x + 1, coords.y + 1);

  // first option
  numTrue = 0;
  
  for (i = 0; i < 3; i++){
    for (j = 0; j < 3; j++){
      mapMatch[i][j] = false;
    }
  }
  
  mapMatch[1][1] = true;
  
  if ((neighborMap[0][0] == FLOOR) || (neighborMap[2][0] == FLOOR)){
    mapMatch[0][0] = true;
    mapMatch[2][0] = true;
  }
  
  if ((neighborMap[1][0] == FLOOR) && (neighborMap[1][2] == FLOOR)){
    mapMatch[1][0] = true;
    mapMatch[1][2] = true;
  }
  
  if ((neighborMap[0][1] == WALL) && (neighborMap[2][1] == WALL)){
    mapMatch[0][1] = true;
    mapMatch[2][1] = true;
  }
  
  if ((neighborMap[0][2] == WALL) && (neighborMap[2][2] == WALL)){
    mapMatch[0][2] = true;
    mapMatch[2][2] = true;
  }
  
  for (i = 0; i < 3; i++){
    for (j = 0; j < 3; j++){
      if (mapMatch[i][j] == true){
	numTrue++;
      }
    }
  }
    
    if (numTrue == 9){
      return true;
    }
    
  // second option
  numTrue = 0;
  
  for (i = 0; i < 3; i++){
    for (j = 0; j < 3; j++){
      mapMatch[i][j] = false;
    }
  }
  
  mapMatch[1][1] = true;
  
  if ((neighborMap[0][2] == FLOOR) || (neighborMap[2][2] == FLOOR)){
    mapMatch[0][2] = true;
    mapMatch[2][2] = true;
  }
  
  if ((neighborMap[1][0] == FLOOR) && (neighborMap[1][2] == FLOOR)){
    mapMatch[1][0] = true;
    mapMatch[1][2] = true;
  }
  
  if ((neighborMap[0][1] == WALL) && (neighborMap[2][1] == WALL)){
    mapMatch[0][1] = true;
    mapMatch[2][1] = true;
  }
  
  if ((neighborMap[0][0] == WALL) && (neighborMap[2][0] == WALL)){
    mapMatch[0][0] = true;
    mapMatch[2][0] = true;
  }
  
  for (i = 0; i < 3; i++){
    for (j = 0; j < 3; j++){
      if (mapMatch[i][j] == true){
	numTrue++;
      }
    }
  }
    
    if (numTrue == 9){
      return true;
    }
    
  // third option
  numTrue = 0;
  
  for (i = 0; i < 3; i++){
    for (j = 0; j < 3; j++){
      mapMatch[i][j] = false;
    }
  }
  
  mapMatch[1][1] = true;
  
  if ((neighborMap[0][0] == FLOOR) || (neighborMap[0][2] == FLOOR)){
    mapMatch[0][0] = true;
    mapMatch[0][2] = true;
  }
  
  if ((neighborMap[0][1] == FLOOR) && (neighborMap[2][1] == FLOOR)){
    mapMatch[0][1] = true;
    mapMatch[2][1] = true;
  }
  
  if ((neighborMap[1][0] == WALL) && (neighborMap[1][2] == WALL)){
    mapMatch[1][0] = true;
    mapMatch[1][2] = true;
  }
  
  if ((neighborMap[2][0] == WALL) && (neighborMap[2][2] == WALL)){
    mapMatch[2][0] = true;
    mapMatch[2][2] = true;
  }
  
  for (i = 0; i < 3; i++){
    for (j = 0; j < 3; j++){
      if (mapMatch[i][j] == true){
	numTrue++;
      }
    }
  }
    
    if (numTrue == 9){
      return true;
    }

  // fourth option
  numTrue = 0;
  
  for (i = 0; i < 3; i++){
    for (j = 0; j < 3; j++){
      mapMatch[i][j] = false;
    }
  }
  
  mapMatch[1][1] = true;
  
  if ((neighborMap[2][0] == FLOOR) || (neighborMap[2][2] == FLOOR)){
    mapMatch[2][0] = true;
    mapMatch[2][2] = true;
  }
  
  if ((neighborMap[0][1] == FLOOR) && (neighborMap[2][1] == FLOOR)){
    mapMatch[0][1] = true;
    mapMatch[2][1] = true;
  }
  
  if ((neighborMap[1][0] == WALL) && (neighborMap[1][2] == WALL)){
    mapMatch[1][0] = true;
    mapMatch[1][2] = true;
  }
  
  if ((neighborMap[0][0] == WALL) && (neighborMap[0][2] == WALL)){
    mapMatch[0][0] = true;
    mapMatch[0][2] = true;
  }
  
  for (i = 0; i < 3; i++){
    for (j = 0; j < 3; j++){
      if (mapMatch[i][j] == true){
	numTrue++;
      }
    }
  }
    
    if (numTrue == 9){
      return true;
    }
  
  // and if we haven't returned true yet, then there was a match for none of the possibilities
  return false;
  
  // this function is why code folding was invented
  // it's ugly, I know
  // sorry about that
}

coord2D *enumerateFloors(level level){
  coord2D *floors = 0;
  unsigned int i = 0, j = 0;
  unsigned int numFloors = 0;
  
  for (i = 1; i < dimMapX; i++){
    for (j = 1; j < dimMapY; j++){
      if (getMapSpaceTerrain(level, i, j) == FLOOR){
	numFloors++;
	floors = realloc(floors, (numFloors + 1) * sizeof(coord2D));
	floors[numFloors - 1].x = i;
	floors[numFloors - 1].y = j;
	floors[numFloors].x = 0;
	floors[numFloors].y = 0;
      }
    }
  }
  
  return floors;
}

void placeDoors(level level){
  coord2D *doorEligible = 0;
  unsigned int i = 0;
  unsigned int searchCountdownInit = 0;
  
  doorEligible = findDoorEligible(level);
  
  while (doorEligible[i].x){
    if (uniformRandomRangeInt(&levelGenRNG, 1, 1000) < doorLikelihood){
      if (uniformRandomRangeInt(&levelGenRNG, 1, 1000) < hiddenDoorLikelihood){
	setMapSpaceTerrain(level, doorEligible[i].x, doorEligible[i].y, HIDDENDOOR);
	setTerrainData(level, doorEligible[i].x, doorEligible[i].y, HIDDENDOOR, (void *)&searchCountdownInit);
      } else {
	setMapSpaceTerrain(level, doorEligible[i].x, doorEligible[i].y, DOOR);
      }
    }
    i++;
  }
  
  free(doorEligible);
  
  return;
}

unsigned int numberFloors(level level){
  unsigned int i = 0, j = 0, coverage = 0;
  
  for (i = 0; i < dimMapX; i++){
    for (j = 0; j < dimMapY; j++){
      if (getMapSpaceTerrain(level, i, j) == FLOOR){
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
  
  // since it's possible for (very likely that) rooms will overlap, and we don't care if they do, we
  // can't just add the size of the room to a running total; instead, we have to recount the # of floors
  // across the whole level every time we add a room
  // this is probably hugely inefficient, but for reasonably-sized maps on modern equipment no one will
  // notice, or at least I haven't in my tests
  while (numberFloors(level) < coverageGoal){
    // grow the array of centerPoints by 1
    numRooms++; // leave room for the null pointer at the end to signify the end of the list
    centerPoints = realloc(centerPoints, (numRooms + 1) * sizeof(centerPoint));
    
    // we generate the room size first, so we know how far down or over it can be located
    a = uniformRandomRangeInt(&levelGenRNG, minRoomX, maxRoomX);
    b = uniformRandomRangeInt(&levelGenRNG, minRoomY, maxRoomY);
    x = uniformRandomRangeInt(&levelGenRNG, 1, (dimMapX - minRoomX) - (a - 1));
    y = uniformRandomRangeInt(&levelGenRNG, 1, (dimMapY - minRoomY) - (b - 1));
    
    centerPoints[numRooms - 1].x = ((a / 2) + x); // zero-based array indexing sucks sometimes
    centerPoints[numRooms - 1].y = ((b / 2) + y);
    centerPoints[numRooms - 1].complete = false;
    centerPoints[numRooms].x = 0;	// we'll only ever check x, but we'll set y too in case I'm an
    centerPoints[numRooms].y = 0;	// idiot at some point in the future
    centerPoints[numRooms].complete = false;
    
    for (i = x; i < x + a; i++){
      for (j = y; j < y + b; j++){
	setMapSpaceTerrain(level, i, j, FLOOR);
      }
    }
  }
  
  digTunnels(level, centerPoints);
  
  free(centerPoints);
  
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
      if ((newX != 0) && (newX != dimMapX - 1) && (newY != 0) && (newY != dimMapY - 1)){
	setMapSpaceTerrain(level, newX, newY, FLOOR);
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

level initLevel(){
  level level;
  unsigned int i = 0, j = 0;
  
  // should be the only place where the internals of level as an array of mapSpaces should matter
  
  level = (mapSpace **)calloc(dimMapX, sizeof(mapSpace *));
  if (!level){
    perror("lvt: ");
  }
  
  for (i = 0; i < dimMapX; i++){
    level[i] = (mapSpace *)calloc(dimMapY, sizeof(mapSpace));
    if (!level){
      perror("lvt: ");
    }
  }
  
   for (i = 0; i < dimMapX; i++){
    for (j = 0; j < dimMapY; j++){
      setMapSpaceTerrain(level, i, j, WALL);
      setMapSpaceExploredState(level, i, j, false);
      initializeMapSpaceContents(level, i, j);
    }
  }
  
  return level;
}
