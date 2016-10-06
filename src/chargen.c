#define _CHARGEN_C

#include <ncurses.h>
#include <stdlib.h>
#include "lvt.h"
#include "creature.h"

void initializeCharacter(){
  char *charName = 0;
  char c = '\0';
  unsigned int i = 1;
  
  printw("Character name? ");
  refresh();

  // we'll worry about how to handle backspaces and shit later
  while((c = getch()) != '\n'){
    if ((c >= 32) && (c <= 126)){
      i++;
      charName = realloc(charName, i * sizeof(char));
      charName[i - 2] = c;
      charName[i - 1] = '\0';
      addch(c);
      refresh();
    }
  }
  
  player.name = charName;
  
  return;
}