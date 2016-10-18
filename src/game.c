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

void startGame(){
  char *welcomeMsg = 0;
  
  status.turnNum = 0;
  status.playerSpeed = 5;
  status.speedCounter = 5;
  
  displayLevel(dungeon[0]);
  
  welcomeMsg = calloc(MSGLEN(WELCOME_MSG) + strlen(getCreatureName(&player)) + 1 , sizeof(char));
  sprintf(welcomeMsg, WELCOME_MSG, getCreatureName(&player));
  displayMsg(welcomeMsg);
  
  free(welcomeMsg);
  
  gameLoop();
  
  return;
}

bool doQuit(){
  return true;
}

void updateTurnCounter(){
  status.speedCounter--;
  
  if (status.speedCounter == 0){
    status.speedCounter = status.playerSpeed;
    status.turnNum++;
  }
  
  return;
}

void gameLoop(){
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
    processKey(c);
    updateTurnCounter();
    displayLevel(dungeon[getCreatureMapLevel(&player)]);
  }
  
  return;
}

void processKey(unsigned int c){
  switch (c){
    case KEY_UP:
    case KEY_DOWN:
    case KEY_LEFT:
    case KEY_RIGHT:
    case KEY_UPLEFT:
    case KEY_UPRIGHT:
    case KEY_DOWNLEFT:
    case KEY_DOWNRIGHT:
      doMoveKey(c);
      break;
    case 'o':
    case 'c':
      doOpenDoor(c);
      break;
    case 's':
      doSearchDoors(c);
      break;
    case '<':
    case '>':
      doStairs(c);
      break;
    default:
      break;
  }
  return;
}