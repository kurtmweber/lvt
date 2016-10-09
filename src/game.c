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

#define _GAME_C

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "lvt.h"
#include "creature.h"
#include "messages.h"

void startGame(map map){
  char *welcomeMsg = 0;
  
  displayLevel(map[0]);
  
  welcomeMsg = calloc(MSGLEN(WELCOME_MSG) + strlen(getCreatureName(&player)) + 1 , sizeof(char));
  sprintf(welcomeMsg, WELCOME_MSG, getCreatureName(&player));
  displayMsg(welcomeMsg);
  
  free(welcomeMsg);
  
  gameLoop(map);
  
  return;
}

bool doQuit(){
  return true;
}

void gameLoop(map map){
  unsigned int c = '\0';
  
  while(1){
    updateStatWin();
    c = getch();
    clearMsg();
    if (c == 'Q'){
      if (doQuit()){
	break;
      }
    }
    processKey(c, map);
    displayLevel(map[getCreatureMapLevel(&player)]);
  }
  
  return;
}

void processKey(unsigned int c, map map){
  switch (c){
    case KEY_UP:
    case KEY_DOWN:
    case KEY_LEFT:
    case KEY_RIGHT:
    case KEY_UPLEFT:
    case KEY_UPRIGHT:
    case KEY_DOWNLEFT:
    case KEY_DOWNRIGHT:
      doMoveKey(c, map);
      break;
    case 'o':
    case 'c':
      doOpenDoor(c, map);
      break;
    case 's':
      doSearchDoors(c, map);
      break;
    case '<':
    case '>':
      doStairs(c, map);
      break;
    default:
      break;
  }
  return;
}