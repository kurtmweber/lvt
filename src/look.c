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

#define _LOOK_C

#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "attack.h"
#include "lvt.h"
#include "move.h"
#include "messages.h"
#include "plant.h"
#include "stringlookups.h"

void doLook(unsigned int c){
  coord3D mapLoc;
  coord2D cursorLoc;
  coord2D corner;
  unsigned int inputChar;
  bool noOccupants = true;
  
  freeAction = true;
  
  mapLoc = getCreatureLocation(&player);
  
  corner = definePlayAreaDisplay();
  
  cursorLoc.y = mapLoc.y - corner.y + 1;
  cursorLoc.x = mapLoc.x - corner.x;
  
  addToMsgQueue(SELECT_LOCATION_MSG, false);
  procMsgQueue();
  setCursorLoc();
  
  while ((inputChar = getch()) != '\n'){
    switch(inputChar){
      case KEY_UP:
	cursorLoc.y--;
	if (cursorLoc.y == 0){
	  cursorLoc.y = 1;
	} else if (mapLoc.y == 0) {
	  mapLoc.y = 0;
	} else {
	  mapLoc.y--;
	}
	move(cursorLoc.y, cursorLoc.x);
	refresh();
	break;
      case KEY_DOWN:
	cursorLoc.y++;
	if (cursorLoc.y == LINES - 3){
	  cursorLoc.y = LINES - 4;
	} else if (mapLoc.y == dimMapY){
	  mapLoc.y = dimMapY;
	} else {
	  mapLoc.y++;
	}
	move(cursorLoc.y, cursorLoc.x);
	refresh();
	break;
      case KEY_LEFT:
	if (cursorLoc.x != 0){
	  cursorLoc.x--;
	}
	
	if (mapLoc.x != 0){
	  mapLoc.x--;
	}
	
	move(cursorLoc.y, cursorLoc.x);
	refresh();
	break;
      case KEY_RIGHT:
	if ((cursorLoc.x != COLS - 1) && (mapLoc.x != dimMapX - 1)){
	  cursorLoc.x++;
	  mapLoc.x++;
	}
	
	move(cursorLoc.y, cursorLoc.x);
	refresh();
	break;
      case KEY_UPLEFT:
	if ((cursorLoc.y != 1) && (cursorLoc.x != 0) && (mapLoc.y != 0) && (mapLoc.x != 0)){
	  cursorLoc.y--;
	  mapLoc.y--;
	  cursorLoc.x--;
	  mapLoc.x--;
	}
	
	move(cursorLoc.y, cursorLoc.x);
	refresh();
	break;
      case KEY_UPRIGHT:
	if ((cursorLoc.y != 1) && (cursorLoc.x != COLS - 1) && (mapLoc.y != 0) && (mapLoc.x != dimMapX - 1)){
	  cursorLoc.y--;
	  mapLoc.y--;
	  cursorLoc.x++;
	  mapLoc.x++;
	}
	
	move(cursorLoc.y, cursorLoc.x);
	refresh();
	break;
      case KEY_DOWNRIGHT:
	if ((cursorLoc.y != LINES - 4) && (cursorLoc.x != COLS - 1) && (mapLoc.y != dimMapY - 1) && (mapLoc.x != dimMapX - 1)){
	  cursorLoc.y++;
	  mapLoc.y++;
	  cursorLoc.x++;
	  mapLoc.x++;
	}
	
	move(cursorLoc.y, cursorLoc.x);
	refresh();
	break;
      case KEY_DOWNLEFT:
	if ((cursorLoc.y != LINES - 4) && (cursorLoc.x != 0) && (mapLoc.y != dimMapY - 1) && (mapLoc.x != 0)){
	  cursorLoc.y++;
	  mapLoc.y++;
	  cursorLoc.x--;
	  mapLoc.x--;
	}
	
	move(cursorLoc.y, cursorLoc.x);
	refresh();
	break;
      default:
	break;
    }
  }
  
  if (hasCreatureOccupant(dungeon[mapLoc.level], mapLoc.x, mapLoc.y)){
    lookCreatureOccupant(mapLoc);
    noOccupants = false;
  }
  
  if (hasPlantOccupant(dungeon[mapLoc.level], mapLoc.x, mapLoc.y)){
    lookPlantOccupant(mapLoc);
    noOccupants = false;
  }
  
  if (hasContents(dungeon[mapLoc.level], mapLoc.x, mapLoc.y)){
    lookContents(mapLoc);
    noOccupants = false;
  }
  
  if (noOccupants){
    addToMsgQueue(NOTHING_THERE_MSG, true);
  }
  
  procMsgQueue();
  
  return;
}

void lookContents(coord3D mapLoc){
  mapSpaceContents *contents;
  item *curItem;
  
  contents = getContents(dungeon[mapLoc.level], mapLoc.x, mapLoc.y);
  
  if (!contents){	// can't happen, since we don't call this without first checking to see that there are contents
    destroyNcurses;
    exit(EXIT_FAILURE);
  }
  
  do {  
    curItem = contents->item;
    if (curItem->name){
      addToMsgQueue(curItem->name, true);
    } else if (curItem->itemData.itemName){
      addToMsgQueue(curItem->itemData.itemName, true);
    } else {
      addToMsgQueue("an unknown object", true);
    }
    contents = contents->next;
  } while (contents);
  
  return;
}

void lookPlantOccupant(coord3D mapLoc){
  plant *infoPlant;
  char *infoMsg;
  plantSpecies infoPlantSpecies;
  
  infoPlant = getPlantOccupant(dungeon[mapLoc.level], mapLoc.x, mapLoc.y);
  infoMsg = (char *)calloc(11, sizeof(char));
  strcat(infoMsg, "You see a ");
  infoPlantSpecies = getPlantSpecies(infoPlant);
  infoMsg = realloc(infoMsg, (strlen(infoMsg) + strlen(plantSpeciesNames[infoPlantSpecies]) + 1) * sizeof(char));
  strcat(infoMsg, plantSpeciesNames[infoPlantSpecies]);
  
  if (getPlantCurProduction(infoPlant) > 0){
    infoMsg = realloc(infoMsg, (strlen(infoMsg) + 14 + 1) * sizeof(char));
    strcat(infoMsg, " bearing fruit");
  }
  
  addToMsgQueue(infoMsg, true);
  
  free(infoMsg);
  
  return;
}

void lookCreatureOccupant(coord3D mapLoc){
  creature *infoCreature;
  char *infoCreatureName;
  creatureSpecies infoCreatureSpecies;
  char *infoMsg;
  char levelNumText[10];
  
  infoCreature = getCreatureOccupant(dungeon[mapLoc.level], mapLoc.x, mapLoc.y);
  infoMsg = (char *)calloc(9, sizeof(char));
  strcat(infoMsg, "You see ");
  infoCreatureName = getCreatureName(infoCreature);
  infoMsg = realloc(infoMsg, (strlen(infoMsg) + strlen(infoCreatureName) + 1) * sizeof(char));
  strcat(infoMsg, infoCreatureName);
  
  if (sameFactions(&player, infoCreature)){
    infoMsg = realloc(infoMsg, (strlen(infoMsg) + 13) * sizeof(char));
    strcat(infoMsg, ", an allied ");
  } else {
    infoMsg = realloc(infoMsg, (strlen(infoMsg) + 15) * sizeof(char));
    strcat(infoMsg, ", an unallied ");
  }
    
  sprintf(levelNumText, "level %i ", getCreatureLevel(infoCreature));
  infoMsg = realloc(infoMsg, (strlen(infoMsg) + strlen(levelNumText) + 1) * sizeof(char));
  strcat(infoMsg, levelNumText);
    
  if (getCreatureBioSex(infoCreature) == MALE){
    infoMsg = realloc(infoMsg, (strlen(infoMsg) + 6) * sizeof(char));
    strcat(infoMsg, "male ");
  } else {
    infoMsg = realloc(infoMsg, (strlen(infoMsg) + 8) * sizeof(char));
    strcat(infoMsg, "female ");
  }
    
  infoCreatureSpecies = getCreatureSpecies(infoCreature);
    
  infoMsg = realloc(infoMsg, (strlen(infoMsg) + strlen(speciesNames[infoCreatureSpecies]) + 1) * sizeof(char));
  strcat(infoMsg, speciesNames[infoCreatureSpecies]);
    
  addToMsgQueue(infoMsg, true);
  
  free(infoMsg);
}