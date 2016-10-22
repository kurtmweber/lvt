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

#define _CREATUREINIT_C

#include "lvt.h"
#include "creature.h"

void getClassModifiers(creatureClass class, statList *list){
  // total 13 for each class
  static int modifierTable[MAXCREATURECLASS][6] = {
    // STRENGTH	WISDOM	INTELLIGENCE	CONSTITUTION	CHARISMA	DEXTERITY
    {	-2,	5,	4,		4,		2,		0},		// Poet
    {	-1,	5,	3,		4,		5,		-5},		// Peacemaker
    {	4,	3,	0,		4,		5,		-3},		// Paladin
    {	2,	4,	4,		2,		-2,		3},		// Ranger
    {	5,	-2,	-1,		5,		5,		1},		// Warrior
    {	0,	1,	4,		2,		4,		2},		// Merchant
    {	3,	5,	4,		5,		-5,		1},		// Peasant
    {	-1,	5,	5,		3,		2,		-1},		// Scholar
    {	-3,	2,	4,		3,		3,		4},		// Beggar
    {	-2,	4,	5,		4,		-2,		5},		// Craftsperson
    {	2,	2,	2,		3,		2,		2},		// Meshchanin
    {	-4,	3,	3,		4,		5,		2},		// Noble
    {	3,	2,	0,		4,		0,		4},		// White cleric
    {	0,	5,	5,		-2,		2,		3}		// Black cleric
  };
  
  list->strength = modifierTable[class][STRENGTH];
  list->wisdom = modifierTable[class][WISDOM];
  list->intelligence = modifierTable[class][INTELLIGENCE];
  list->constitution = modifierTable[class][CONSTITUTION];
  list->charisma = modifierTable[class][CHARISMA];
  list->dexterity = modifierTable[class][DEXTERITY];
  
  return;
}

void genOrphanCreatureStats(creature *creature){
  creatureSpecies species;
  creatureClass class;
  int statModifiers[6];
  int tmpMaxStats[6];
  unsigned int maxStats[6];
  unsigned int curStats[6];
  statList speciesModifiers;
  statList classModifiers;
  static rng localRng;
  static bool rngInitd = false;
  
  if (!rngInitd){
    initializeRNG(&localRng);
    rngInitd = true;
  }
  
  species = getCreatureSpecies(creature);
  class = getCreatureClass(creature);
  
  getClassModifiers(class, &classModifiers);
  getSpeciesModifiers(species, &speciesModifiers);
  
  statModifiers[STRENGTH] = classModifiers.strength + speciesModifiers.strength;
  statModifiers[INTELLIGENCE] = classModifiers.intelligence + speciesModifiers.intelligence;
  statModifiers[WISDOM] = classModifiers.wisdom + speciesModifiers.wisdom;
  statModifiers[CONSTITUTION] = classModifiers.constitution + speciesModifiers.constitution;
  statModifiers[CHARISMA] = classModifiers.charisma + speciesModifiers.charisma;
  statModifiers[DEXTERITY] = classModifiers.dexterity + speciesModifiers.dexterity;
  
  tmpMaxStats[STRENGTH] = uniformRandomRangeInt(&localRng, 5, 15) + statModifiers[STRENGTH];
  tmpMaxStats[INTELLIGENCE] = uniformRandomRangeInt(&localRng, 5, 15) + statModifiers[INTELLIGENCE];
  tmpMaxStats[WISDOM] = uniformRandomRangeInt(&localRng, 5, 15) + statModifiers[WISDOM];
  tmpMaxStats[CONSTITUTION] = uniformRandomRangeInt(&localRng, 5, 15) + statModifiers[CONSTITUTION];
  tmpMaxStats[CHARISMA] = uniformRandomRangeInt(&localRng, 5, 15) + statModifiers[CHARISMA];
  tmpMaxStats[DEXTERITY] = uniformRandomRangeInt(&localRng, 5, 15) + statModifiers[DEXTERITY];
  
  maxStats[STRENGTH] = clampRangeIntSigned(tmpMaxStats[STRENGTH], 3, 25);
  maxStats[INTELLIGENCE] = clampRangeIntSigned(tmpMaxStats[INTELLIGENCE], 3, 25);
  maxStats[WISDOM] = clampRangeIntSigned(tmpMaxStats[WISDOM], 3, 25);
  maxStats[CONSTITUTION] = clampRangeIntSigned(tmpMaxStats[CONSTITUTION], 3, 25);
  maxStats[CHARISMA] = clampRangeIntSigned(tmpMaxStats[CHARISMA], 3, 25);
  maxStats[DEXTERITY] = clampRangeIntSigned(tmpMaxStats[DEXTERITY], 3, 25);
  
  setCreatureMaxStats(creature, maxStats);
  
  curStats[STRENGTH] = (maxStats[STRENGTH] * 2) / 3;
  curStats[INTELLIGENCE] = (maxStats[INTELLIGENCE] * 2) / 3;
  curStats[WISDOM] = (maxStats[WISDOM] * 2) / 3;
  curStats[CONSTITUTION] = (maxStats[CONSTITUTION] * 2) / 3;
  curStats[CHARISMA] = (maxStats[CHARISMA] * 2) / 3;
  curStats[DEXTERITY] = (maxStats[DEXTERITY] * 2) / 3;
  
  setCreatureCurStats(creature, curStats);
  
  return;
}