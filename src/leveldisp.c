#define _LEVELDISP_C

#include <stdio.h>
#include <stdlib.h>
#include "lvt.h"
#include "level.h"

char *generateLevelRepresentation(level level, unsigned int line){
  char *mapLine = 0;
  unsigned int x = 0;
  char c = 0;
  
  mapLine = calloc(dimMapX + 1, sizeof(char));
  
  for (x = 0; x < dimMapX; x++){
    if (getMapSpaceExploredState(level, x, line)){
      // a creature occupant will always appear on top of contents, and contents will always appear on
      // top of a plant occupant, so we only need to worry about the highest level that appears and if
      // it's there, then we don't need to worry about the lower levels for display purposes
      if (hasCreatureOccupant(level, x, line)){
	mapLine[x] = getCreatureDispChar(getCreatureOccupant(level, x, line));
      } else if (hasContents(level, x, line)){
      } else if (hasPlantOccupant(level, x, line)){
      } else {
	  switch (getMapSpaceTerrain(level, x, line)){
	    case WALL:
	    case PERMANENTROCK:
	      mapLine[x] = '#';
	      break;
	    case FLOOR:
	      mapLine[x] = '.';
	      break;
	    case DOOR:
	      mapLine[x] = '+';
	      break;
	    case HIDDENDOOR:
	      mapLine[x] = '#';
	      break;
	    case OPENDOOR:
	      mapLine[x] = '\'';
	      break;
	    case UPSTAIR:
	      mapLine[x] = '<';
	      break;
	    case DOWNSTAIR:
	      mapLine[x] = '>';
	      break;
	    default:
	      mapLine[x] = '?';
	      break;
	  }
      }
    } else {
      mapLine[x] = ' ';
    }
  }
  
  mapLine[x + 1] = '\0';
  
  return mapLine;
}

void displayLevel(level level){
  unsigned int y = 0;
  char *mapLine = 0;
  
  for (y = 0; y < dimMapY; y++){
    mapLine = generateLevelRepresentation(level, y);
    writeLinePlayArea(mapLine, y);
    free(mapLine);
  }
  
  refreshPlayArea();
  
  return;
}
  