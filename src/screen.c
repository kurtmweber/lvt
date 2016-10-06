#define _SCREEN_C

#include <ncurses.h>

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