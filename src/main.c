#define _MAIN_C

#include <stdio.h>
#include "lvt.h"
#include "level.h"
#include "creature.h"

const double pi = 3.141592;
creature player;

int main(int argc, char *argv[]){
  map map;
  
  initializeLevelGen();
  
  map = generateMap();
  
  initializeNcurses();
  //displayLevel(map[0]);
  initializeCharacter();
  
  destroyNcurses();

  return 0;
  }