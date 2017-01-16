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

#ifndef _SPECIES_H
#define _SPECIES_H

#include "colors.h"

typedef enum creatureStats{
  STRENGTH,
  WISDOM,
  INTELLIGENCE,
  CONSTITUTION,
  CHARISMA,
  DEXTERITY,
  MAXSTATNAME
} creatureStats;


// remember to add a corpseSubClassId in item.h for each new species type!

typedef enum creatureSpecies{
  HUMAN,
  HALFLING,
  ELF,
  DWARF,
  BEAR,
  //BOAR,
  //DEER,
  //ORC,
  //GOBLIN,
  MAXCREATURESPECIES
} creatureSpecies;

typedef struct speciesActions{
} speciesActions;

typedef struct speciesInfo{
  int statModifiers[MAXSTATNAME];
  unsigned int lifePace;
  speciesActions actions;
  unsigned int baseHp;
  char dispChar;
  colorPairs color;
  unsigned int speed;
  bool hasHands;
  unsigned int weight;
  //speciesAggression aggression;
} speciesInfo;

#endif