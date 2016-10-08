#define _MAIN_C

#include <stdio.h>
#include <ncurses.h>
#include "lvt.h"
#include "level.h"
#include "creature.h"

const double pi = 3.141592;
creature player;

int main(int argc, char *argv[]){
  map map;

  coord2D initUpstair;
  coord3D initLocation;
  
  initializeLevelGen();
  
  map = generateMap();
  
  initializeNcurses();
  //displayLevel(map[0]);
  initializeCharacter();
  clear();
    
  initUpstair = findLevelUpstair(map[0]);
  initLocation.x = initUpstair.x;
  initLocation.y = initUpstair.y;
  initLocation.level = 0;
  setCreatureLocation(&player, initLocation);
  setCreatureOccupant(map[initLocation.level], initLocation.x, initLocation.y, &player);
  updateRegionExploredState(map[initLocation.level], initLocation.x, initLocation.y, true);
  
  initializeGameScreen();
  
  startGame(map);
  
  destroyNcurses();

  return 0;
  }