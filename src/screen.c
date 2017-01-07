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

#define _SCREEN_C

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lvt.h"
#include "stringlookups.h"

WINDOW *msgWin = 0;
WINDOW *statWin = 0;
WINDOW *playArea = 0;

void updateStatWin(){
  char dLvl[4];
  statList stats;
  
  wclear(statWin);
  wprintw(statWin, getCreatureName(&player));
  wprintw(statWin, ", the ");
  
  wprintw(statWin, speciesNames[getCreatureSpecies(&player)]);
  wprintw(statWin, " ");
  wprintw(statWin, classNames[getCreatureClass(&player)]);

  wprintw(statWin, " Dlvl: ");
  sprintf(dLvl, "%i", getCreatureMapLevel(&player) + 1);
  wprintw(statWin, dLvl);

  wprintw(statWin, " Turn: %i Speed: %i", status.turnNum, status.playerSpeed);
  wprintw(statWin, " Lvl/XP: %i/%i", getCreatureLevel(&player), getCreatureXp(&player));
  wprintw(statWin, "\n");
  
  getCreatureCurStats(&player, &stats);
  
  wprintw(statWin, "STR: %i ", stats.strength);
  wprintw(statWin, "INT: %i ", stats.intelligence);
  wprintw(statWin, "WIS: %i ", stats.wisdom);
  wprintw(statWin, "CON: %i ", stats.constitution);
  wprintw(statWin, "CHR: %i ", stats.charisma);
  wprintw(statWin, "DEX: %i ", stats.dexterity);
  wprintw(statWin, "HP/Max: %i/%i", getCreatureCurHp(&player), getCreatureMaxHp(&player));
  wrefresh(statWin);
  return;
}

void initializeNcurses(){
  initscr();
  clear();
  noecho();
  cbreak();
  leaveok(playArea, true);
  
  return;
}

void destroyNcurses(){
  endwin();
  
  return;
}

void initializeGameScreen(){
  msgWin = newwin(1, MIN(dimMapX, COLS), 0, 0);
  statWin = newwin(2, MIN(dimMapX, COLS), LINES - 3, 0);
  playArea = newpad(dimMapX, dimMapY);
  scrollok(playArea, false);
  keypad(stdscr,true);
  refresh();
  
  return;
}

void clearMsg(){
  werase(msgWin);
  wrefresh(msgWin);
  
  return;
}

void displayMsg(char *msg, int a){
  clearMsg();
  wprintw(msgWin, msg);
  wprintw(msgWin, " (enter to continue)");
  wrefresh(msgWin);
  while (getch() != '\n'){
    beep();
  }

  return;
}

void displayQuestionYesNo(char *msg){
  clearMsg();
  wprintw(msgWin, msg);
  wprintw(msgWin, " (y/n)");
  wrefresh(msgWin);
  
  return;
}

void displayMsgNoWait(char *msg, int a){
  clearMsg();
  wprintw(msgWin, msg);
  wrefresh(msgWin);
  
  return;
}

void writeLinePlayArea(screenDisplayCell *mapLine, unsigned int y){
  char *dispLine;
  unsigned int i = 0;
  unsigned int j = 0;
  unsigned int x = 0;
  
  dispLine = (char *)calloc(dimMapX + 2, sizeof(char));
  
  while (mapLine[i].dispChar){
    if (!mapLine[i].hasAttrs){
      dispLine[j] = mapLine[i].dispChar;
      j++;
    } else {
      mvwaddstr(playArea, y, x, dispLine);
      x = i;
      memset(dispLine, dimMapX + 2, 0);
      j = 0;
      mvwaddch(playArea, y, x, (chtype)mapLine[i].dispChar | (chtype)mapLine[i].attrs);
      x++;
    }
    i++;
  }
  
  mvwaddstr(playArea, y, x, dispLine);
  strcat(dispLine, "\n");
  
  free(dispLine);
  
  return;
}

coord2D definePlayAreaDisplay(){
  coord3D location;
  coord2D coords;
  
  unsigned int dispWidth = MIN(dimMapX, COLS);
  unsigned int halfWidth;
  unsigned int dispHeight = LINES - 4;
  unsigned int halfHeight;
  
  location = getCreatureLocation(&player);
  
  if (ISEVEN(dispWidth)){
    halfWidth = dispWidth / 2;
  } else {
    halfWidth = ((dispWidth - 1) / 2) + 1;
  }
  
  if (location.x < halfWidth){
    coords.x = 0;
  } else {
    coords.x = location.x - halfWidth;
  }
  
  if (ISEVEN(dispHeight)){
    halfHeight = dispHeight / 2;
  } else {
    halfHeight = ((dispHeight - 1) / 2) + 1;
  }
  
  if (location.y < halfHeight){
    coords.y = 0;
  } else {
    coords.y = location.y - halfHeight;
  }
  
  coords.y = MIN(coords.y, dimMapY - dispHeight);
  coords.x = MIN(coords.x, dimMapX - dispWidth);
  
  return coords;
}

void clearPlayArea(){
  werase(playArea);
  
  return;
}

void refreshPlayArea(){
  coord2D corner;
  
  corner = definePlayAreaDisplay();
  
  prefresh(playArea, corner.y, corner.x, 1, 0, LINES - 4, MIN(dimMapX, COLS) - 1);
  
  return;
}

void setCursorLoc(){
  coord3D playerLoc;
  coord2D corner;
  
  playerLoc = getCreatureLocation(&player);
  corner = definePlayAreaDisplay();
  
  move(playerLoc.y - corner.y + 1, playerLoc.x - corner.x);
  refresh();
  return;
}