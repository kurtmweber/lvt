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

#ifndef _STRINGLOOKUPS_H
#define _STRINGLOOKUPS_H

#include "creature.h"

#ifdef _STRINGLOOKUPS_C

const char *speciesNames[] = {
  "human",
  "halfling",
  "elf",
  "dwarf",
  "bear",
  "boar",
  "deer",
  "orc",
  "goblin"
};

const char *classNames[] = {
  "poet",
  "peacemaker",
  "paladin",
  "ranger",
  "warrior",
  "merchant",
  "peasant",
  "scholar",
  "beggar",
  "craftsperson",
  "meshchanin",
  "noble",
  "white cleric",
  "black cleric"
};

#else

extern const char *speciesNames[MAXCREATURESPECIES];
extern const char *classNames[MAXCREATURECLASS];

#endif

#endif