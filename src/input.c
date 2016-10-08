#ifndef _INPUT_C
#define _INPUT_C

#include "lvt.h"
#include "move.h"
#include "messages.h"

void doMoveKey(unsigned int c, map map){
  moveDirection dir;
  
  switch (c){
    case KEY_UP:
      dir = UP;
      break;
    case KEY_DOWN:
      dir = DOWN;
      break;
    case KEY_RIGHT:
      dir = RIGHT;
      break;
    case KEY_LEFT:
      dir = LEFT;
      break;
    case KEY_UPLEFT:
      dir = UPLEFT;
      break;
    case KEY_UPRIGHT:
      dir = UPRIGHT;
      break;
    case KEY_DOWNLEFT:
      dir = DOWNLEFT;
      break;
    case KEY_DOWNRIGHT:
      dir = DOWNRIGHT;
      break;
  }
  
  switch(moveCreature(&player, dir, map)){
    case MOVE_FAILED_WALL:
      displayMsgNoWait(MOVE_WALL_MSG);
      break;
    case MOVE_FAILED_CREATURE:
      displayMsgNoWait(MOVE_CREATURE_MSG);
      break;
    case MOVE_SUCCESS:
      displayLevel(map[getCreatureMapLevel(&player)]);
      break;
  }
  
  return;
}


#endif