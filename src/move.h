#ifndef _MOVE_H
#define _MOVE_H

#include <ncurses.h>

#define KEY_UPLEFT KEY_HOME
#define KEY_UPRIGHT KEY_PPAGE
#define KEY_DOWNLEFT KEY_END
#define KEY_DOWNRIGHT KEY_NPAGE


typedef enum moveOutcome{
  MOVE_SUCCESS,
  MOVE_FAILED_WALL,
  MOVE_FAILED_CREATURE,
  MOVE_FAILED_DOOR
} moveOutcome;

typedef enum moveDirection{
  UP,
  DOWN,
  LEFT,
  RIGHT,
  UPLEFT,
  UPRIGHT,
  DOWNLEFT,
  DOWNRIGHT
} moveDirection;

#endif