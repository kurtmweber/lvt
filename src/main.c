#define _MAIN_C

#include <stdio.h>
#include "lvt.h"
#include "level.h"

const double pi = 3.141592;

int main(int argc, char *argv[]){
  mapSpace **level;
  
  initializeLevelGen();
  
  level = generateLevel();
  displayLevel(level);

  return 0;
  }