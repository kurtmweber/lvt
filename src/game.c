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
  
  return;
}