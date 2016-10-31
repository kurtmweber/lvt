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

#define _SPECIESINFO_C

#include "lvt.h"
#include "creature.h"

speciesInfo speciesData[MAXCREATURESPECIES];

void getSpeciesModifiers(creatureSpecies species, statList *list){
  list->strength = speciesData[species].statModifiers[STRENGTH];
  list->wisdom = speciesData[species].statModifiers[WISDOM];
  list->intelligence = speciesData[species].statModifiers[INTELLIGENCE];
  list->constitution = speciesData[species].statModifiers[CONSTITUTION];
  list->charisma = speciesData[species].statModifiers[CHARISMA];
  list->dexterity = speciesData[species].statModifiers[DEXTERITY];
  
  return;
}

unsigned int getSpeciesLifePace(creatureSpecies species){
  return speciesData[species].lifePace;
}

unsigned int getSpeciesBaseHp(creatureSpecies species){
  return speciesData[species].baseHp;
}

// Stats should sum to +7

void initSpeciesDataBear(){
  speciesData[BEAR].statModifiers[STRENGTH] = 5;
  speciesData[BEAR].statModifiers[WISDOM] = -1;
  speciesData[BEAR].statModifiers[INTELLIGENCE] = -3;
  speciesData[BEAR].statModifiers[CONSTITUTION] = 5;
  speciesData[BEAR].statModifiers[CHARISMA] = 0;
  speciesData[BEAR].statModifiers[DEXTERITY] = 1;
  
  speciesData[BEAR].dispChar = 'B';
  speciesData[BEAR].color = MagentaBlack;
  
  return;
}

void initSpeciesDataDwarf(){
  speciesData[DWARF].statModifiers[STRENGTH] = 5;
  speciesData[DWARF].statModifiers[WISDOM] = 3;
  speciesData[DWARF].statModifiers[INTELLIGENCE] = 2;
  speciesData[DWARF].statModifiers[CONSTITUTION] = 5;
  speciesData[DWARF].statModifiers[CHARISMA] = -3;
  speciesData[DWARF].statModifiers[DEXTERITY] = -5;
  
  speciesData[DWARF].dispChar = 'h';
  speciesData[DWARF].color = RedBlack;
  
  return;
}

void initSpeciesDataElf(){
  speciesData[ELF].statModifiers[STRENGTH] = -2;
  speciesData[ELF].statModifiers[WISDOM] = 5;
  speciesData[ELF].statModifiers[INTELLIGENCE] = 4;
  speciesData[ELF].statModifiers[CONSTITUTION] = -2;
  speciesData[ELF].statModifiers[CHARISMA] = 0;
  speciesData[ELF].statModifiers[DEXTERITY] = 2;
  
  speciesData[ELF].dispChar = '@';
  speciesData[ELF].color = GreenBlack;
  
  return;
}

void initSpeciesDataHalfling(){
  speciesData[HALFLING].statModifiers[STRENGTH] = -4;
  speciesData[HALFLING].statModifiers[WISDOM] = 1;
  speciesData[HALFLING].statModifiers[INTELLIGENCE] = 3;
  speciesData[HALFLING].statModifiers[CONSTITUTION] = 5;
  speciesData[HALFLING].statModifiers[CHARISMA] = -3;
  speciesData[HALFLING].statModifiers[DEXTERITY] = 5;
  
  speciesData[HALFLING].dispChar = 'h';
  speciesData[HALFLING].color = BlueBlack;
  
  return;
}

void initSpeciesDataHuman(){
  speciesData[HUMAN].statModifiers[STRENGTH] = -2;
  speciesData[HUMAN].statModifiers[WISDOM] = 3;
  speciesData[HUMAN].statModifiers[INTELLIGENCE] = 4;
  speciesData[HUMAN].statModifiers[CONSTITUTION] = -3;
  speciesData[HUMAN].statModifiers[CHARISMA] = 3;
  speciesData[HUMAN].statModifiers[DEXTERITY] = 2;
  
  speciesData[HUMAN].dispChar = '@';
  speciesData[HUMAN].color = WhiteBlack;
  
  return;
}

void initSpeciesData(){
  unsigned int i;
  
  initSpeciesDataHuman();
  initSpeciesDataHalfling();
  initSpeciesDataElf();
  initSpeciesDataDwarf();
  initSpeciesDataBear();
  
  for (i = 0; i < MAXCREATURESPECIES; i++){
    speciesData[i].lifePace = 1000;
    speciesData[i].baseHp = 20;
  }
  
  return;
}