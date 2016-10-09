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

#define _LEVELDISP_C

#include <stdio.h>
#include <stdlib.h>
#include "lvt.h"
#include "level.h"

#define _D_DEBUG

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
#ifndef _D_DEBUG
	      mapLine[x] = '#';
#else
	      mapLine[x] = '?';
#endif
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
  