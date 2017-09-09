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

#include "chargen.h"
#include "colors.h"
#include "creature.h"

void initializeCharacter(){
  char *charName = 0;
  char c = '\0';
  unsigned int i = 1;
  creatureSpecies species;
  creatureClass class;
  
  charName = inputPlayerName();
  species = inputPlayerSpecies();
  class = inputPlayerClass();
  
  setCreatureName(&player, charName);
  setCreatureSpecies(&player, species);
  setCreatureClass(&player, class);
  setCreatureMatured(&player, false);
  genOrphanCreatureStats(&player);
  setIsPlayer(&player);
  changeDispChar(&player, '@');
  setCreatureLifePace(&player, getSpeciesLifePace(species));
  setCreatureColor(&player, BlackGreen);
  setCreatureAttribute(&player, 0);
  setCreatureFaction(&player, 1);
  initCreatureArmor(&player);
  initCreatureWeapon(&player);
  initCreatureInventory(&player);
  
  return;
}

creatureClass inputPlayerClass(){
  char c = '\0';
  
  erase();
  printw("Class?\n");
  printw("\t(a) Poet\n");
  printw("\t(b) Peacemaker\n");
  printw("\t(c) Paladin\n");
  printw("\t(d) Ranger\n");
  printw("\t(e) Warrior\n");
  printw("\t(f) Merchant\n");
  printw("\t(g) Peasant\n");
  printw("\t(h) Scholar\n");
  printw("\t(i) Beggar\n");
  printw("\t(j) Craftsperson\n");
  printw("\t(k) Meshchanin\n");
  printw("\t(l) Noble\n");
  printw("\t(m) White cleric\n");
  printw("\t(n) Black cleric\n");
  refresh();
  
  while (c = getch()){
    switch (c){
      case 'a':
        return POET;
      case 'b':
        return PEACEMAKER;
      case 'c':
        return PALADIN;
      case 'd':
        return RANGER;
      case 'e':
        return WARRIOR;
      case 'f':
        return MERCHANT;
      case 'g':
        return PEASANT;
      case 'h':
        return SCHOLAR;
      case 'i':
        return BEGGAR;
      case 'j':
        return CRAFTSPERSON;
      case 'k':
        return MESHCHANIN;
      case 'l':
        return NOBLE;
      case 'm':
        return WHITECLERIC;
      case 'n':
        return BLACKCLERIC;
      default:
        break;
    }
  }
}

char *inputPlayerName(){
  char c = '\0';
  unsigned int i = 1;
  char *charName = 0;
  
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
  
  return charName;
}

creatureSpecies inputPlayerSpecies(){
  char c = '\0';
  
  erase();
  printw("Species?\n");
  printw("\t(a) Human\n");
  printw("\t(b) Halfling\n");
  printw("\t(c) Elf\n");
  printw("\t(d) Dwarf\n");
  refresh();
  
  while (c = getch()){
    switch (c){
      case 'a':
	return HUMAN;
      case 'b':
	return HALFLING;
      case 'c':
	return ELF;
      case 'd':
	return DWARF;
      default:
	break;
    }
  }
}