#define _LEVELDISP_C

#include <stdio.h>
#include "lvt.h"
#include "level.h"

void displayLevel(level level){
  int i = 0, j = 0;
  
  for (i = 0; i < 100; i++){
    for (j = 0; j < 100; j++){
      switch(getLevelTerrain(level, i, j)){
	case WALL:
	  putchar('#');
	  break;
	case FLOOR:
	  putchar('.');
	  break;
	default:
	  break;
      }
    }
    putchar('\n');
  }
  
  return;
}
  