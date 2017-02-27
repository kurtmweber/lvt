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

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "lvt.h"
#include "level.h"
#include "types.h"

//#define _D_DEBUG

screenDisplayCell *generateLevelRepresentation(level level, unsigned int line){
  screenDisplayCell *mapLine = 0;
  unsigned int x = 0;
  char c = 0;
  creature *creatureOccupant;
  mapSpaceContents *contents;
  plant *plantOccupant;
  
  mapLine = calloc(dimMapX + 1, sizeof(screenDisplayCell));
  
  for (x = 0; x < dimMapX; x++){
#ifndef _D_DEBUG
    if (getMapSpaceExploredState(level, x, line)){
#endif
      // a creature occupant will always appear on top of contents, and contents will always appear on
      // top of a plant occupant, so we only need to worry about the highest level that appears and if
      // it's there, then we don't need to worry about the lower levels for display purposes
      if (hasCreatureOccupant(level, x, line)){
	creatureOccupant = getCreatureOccupant(level, x, line);
	mapLine[x].dispChar = getCreatureDispChar(creatureOccupant);
	mapLine[x].hasAttrs = true;
	mapLine[x].attrs = COLOR_PAIR(getCreatureColor(creatureOccupant));
	if (sameFactions(&player, creatureOccupant)){
	  mapLine[x].attrs = mapLine[x].attrs | A_BOLD;
	}
      } else if (hasContents(level, x, line)){
	contents = getContents(level, x, line);
	mapLine[x].dispChar = getItemDispChar(contents->item);
	mapLine[x].hasAttrs = true;
	mapLine[x].attrs = COLOR_PAIR(getItemColor(contents->item)) | getItemAttrs(contents->item);
      } else if (hasPlantOccupant(level, x, line)){
	plantOccupant = getPlantOccupant(level, x, line);
	mapLine[x].dispChar = getPlantDispChar(plantOccupant);
	mapLine[x].hasAttrs = true;
	mapLine[x].attrs = COLOR_PAIR(getPlantColor(plantOccupant));
      } else {
	  switch (getMapSpaceTerrain(level, x, line)){
	    case WALL:
	    case PERMANENTROCK:
	      mapLine[x].dispChar = '#';
	      mapLine[x].hasAttrs = false;
	      break;
	    case FLOOR:
	      mapLine[x].dispChar = '.';
	      mapLine[x].hasAttrs = false;
	      break;
	    case DOOR:
	      mapLine[x].dispChar = '+';
	      mapLine[x].hasAttrs = false;
	      break;
	    case HIDDENDOOR:
#ifndef _D_DEBUG
	      mapLine[x].dispChar = '#';
#else
	      mapLine[x].dispChar = '?';
#endif
	      mapLine[x].hasAttrs = false;
	      break;
	    case OPENDOOR:
	      mapLine[x].dispChar = '\'';
	      mapLine[x].hasAttrs = false;
	      break;
	    case UPSTAIR:
	      mapLine[x].dispChar = '<';
	      mapLine[x].hasAttrs = true;
	      mapLine[x].attrs = A_BOLD;
	      break;
	    case DOWNSTAIR:
	      mapLine[x].dispChar = '>';
	      mapLine[x].hasAttrs = true;
	      mapLine[x].attrs = A_BOLD;
	      break;
	    default:
	      mapLine[x].dispChar = '?';
	      mapLine[x].hasAttrs = false;
	      break;
	  }
      }
#ifndef _D_DEBUG
    } else {
      mapLine[x].dispChar = ' ';
      mapLine[x].hasAttrs = false;
    }
#endif
  }
  
  mapLine[dimMapX].dispChar = '\0';
  
  return mapLine;
}

void displayLevel(level level){
  unsigned int y = 0;
  screenDisplayCell *mapLine = 0;
  
  for (y = 0; y < dimMapY; y++){
    mapLine = generateLevelRepresentation(level, y);
    writeLinePlayArea(mapLine, y);
    free(mapLine);
  }
  
  refreshPlayArea();
  
  return;
}
  