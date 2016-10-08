#define _SCREEN_C

#include <ncurses.h>
#include "lvt.h"

WINDOW *msgWin = 0;
WINDOW *statWin = 0;
WINDOW *playArea = 0;

void initializeNcurses(){
  initscr();
  clear();
  noecho();
  cbreak();
  
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

void displayMsg(char *msg){
  wprintw(msgWin, msg);
  wrefresh(msgWin);
  while (getch() != '\n'){
    beep();
  }

  return;
}

void displayMsgNoWait(char *msg){
  wprintw(msgWin, msg);
  wrefresh(msgWin);
  
  return;
}

void writeLinePlayArea(char *mapLine, unsigned int y){
  mvwaddstr(playArea, y, 0, mapLine);
  
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
  
  return coords;
}

void refreshPlayArea(){
  coord2D corner;
  
  corner = definePlayAreaDisplay();
  
  prefresh(playArea, corner.y, corner.x, 1, 0, LINES - 4, MIN(dimMapX, COLS) - 1);
  
  return;
}