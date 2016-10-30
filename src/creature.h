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

#ifndef _CREATURE_H
#define _CREATURE_H

#include <stdbool.h>
#include "types.h"

typedef struct statList{
  int strength;
  int wisdom;
  int intelligence;
  int constitution;
  int charisma;
  int dexterity;
} statList;

typedef enum bioSex{
  FEMALE,
  MALE
} bioSex;

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

typedef enum creatureClass{
  POET,
  PEACEMAKER,
  PALADIN,
  RANGER,
  WARRIOR,
  MERCHANT,
  PEASANT,
  SCHOLAR,
  BEGGAR,
  CRAFTSPERSON,
  MESHCHANIN,
  NOBLE,
  WHITECLERIC,
  BLACKCLERIC,
  MAXCREATURECLASS
} creatureClass;

typedef enum creatureStats{
  STRENGTH,
  WISDOM,
  INTELLIGENCE,
  CONSTITUTION,
  CHARISMA,
  DEXTERITY,
  MAXSTATNAME
} creatureStats;

typedef struct speciesActions{
} speciesActions;

typedef struct speciesInfo{
  int statModifiers[MAXSTATNAME];
  unsigned int lifePace;
  speciesActions actions;
  unsigned int baseHp;
  char dispChar;
} speciesInfo;

typedef struct creature{
  char *name;
  bool isPlayer;
  unsigned int lifePace;
  bool hasMatured;
  coord3D location;
  creatureSpecies species;
  creatureClass class;
  char dispChar;
  unsigned int curHitPoints;
  unsigned int maxHitPoints;
  unsigned int level;
  unsigned int experience;
  unsigned int effStats[6];
  unsigned int curStats[6];
  unsigned int maxStats[6];
  bioSex sex;
} creature;

typedef struct creatureList{
  struct creatureList *prev;
  struct creatureList *next;
  creature *creature;
} creatureList;

#endif