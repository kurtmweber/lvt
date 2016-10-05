#define _MAIN_C

#include <stdio.h>
#include "lvt.h"
#include "level.h"

const double pi = 3.141592;

int main(int argc, char *argv[]){
  map map;
  
  initializeLevelGen();
  
  map = generateMap();
  displayLevel(map[0]);

  return 0;
  }