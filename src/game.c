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
    default:
      break;
  }
  return;
}