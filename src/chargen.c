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
  while((c = getch())){
    if ((c == '\n') && (i >= 2)){
      break;
    }
    if (i == 17){
      beep();
    } else if ((c >= 32) && (c <= 126)){
      i++;
      charName = realloc(charName, i * sizeof(char));
      charName[i - 2] = c;
      charName[i - 1] = '\0';
      addch(c);
      refresh();
    }
  }
  
  setCreatureName(&player, charName);
  setIsPlayer(&player);
  changeDispChar(&player, '@');
  
  return;
}