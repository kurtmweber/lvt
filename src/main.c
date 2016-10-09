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

#define _MAIN_C

#include <stdio.h>
#include <ncurses.h>
#include <config.h>
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
  
  printw("Lavender Throne version "PACKAGE_VERSION".  Copyright 2016 Kurt Weber");
  refresh();
  getch();
  clear();
  
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