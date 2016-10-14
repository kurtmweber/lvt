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
  BOAR,
  DEER,
  ORC,
  GOBLIN,
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

typedef struct creature{
  char *name;
  bool isPlayer;
  coord3D location;
  creatureSpecies species;
  creatureClass class;
  char dispChar;
  unsigned int curHitPoints;
  unsigned int maxHitPoints;
  unsigned int effStrength;
  unsigned int curStrength;
  unsigned int maxStrength;
  unsigned int effWisdom;
  unsigned int curWisdom;
  unsigned int maxWisdom;
  unsigned int effIntelligence;
  unsigned int curIntelligence;
  unsigned int maxIntelligence;
  unsigned int effConstitution;
  unsigned int curConstitution;
  unsigned int maxConstitution;
  unsigned int effCharisma;
  unsigned int curCharisma;
  unsigned int maxCharisma;
  unsigned int effDexterity;
  unsigned int curDexterity;
  unsigned int maxDexterity;
  bioSex sex;
} creature;

#endif