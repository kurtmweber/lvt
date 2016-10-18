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

#define _CREATUREMGMT_C

#include "lvt.h"
#include "creature.h"

void setCreatureName(creature *creature, char *name){
  creature->name = name;
  
  return;
}

void setCreatureSpecies(creature *creature, creatureSpecies species){
  creature->species = species;
  
  return;
}

void setCreatureClass(creature *creature, creatureClass class){
  creature->class = class;
  
  return;
}

void setCreatureMatured(creature *creature, bool matured){
  creature->hasMatured = matured;
  
  return;
}

bool getCreatureMatured(creature *creature){
  return creature->hasMatured;
}

void setCreatureMaxStats(creature *creature, int stats[6]){
  creature->maxStats[STRENGTH] = stats[STRENGTH];
  creature->maxStats[INTELLIGENCE] = stats[INTELLIGENCE];
  creature->maxStats[WISDOM] = stats[WISDOM];
  creature->maxStats[CONSTITUTION] = stats[CONSTITUTION];
  creature->maxStats[CHARISMA] = stats[CHARISMA];
  creature->maxStats[DEXTERITY] = stats[DEXTERITY];
  
  return;
}

void setCreatureCurStats(creature *creature, int stats[6]){
  creature->curStats[STRENGTH] = stats[STRENGTH];
  creature->curStats[INTELLIGENCE] = stats[INTELLIGENCE];
  creature->curStats[WISDOM] = stats[WISDOM];
  creature->curStats[CONSTITUTION] = stats[CONSTITUTION];
  creature->curStats[CHARISMA] = stats[CHARISMA];
  creature->curStats[DEXTERITY] = stats[DEXTERITY];
  
  return;
}

void getCreatureCurStats(creature *creature, statList *stats){
  stats->strength = creature->curStats[STRENGTH];
  stats->intelligence = creature->curStats[INTELLIGENCE];
  stats->wisdom = creature->curStats[WISDOM];
  stats->constitution = creature->curStats[CONSTITUTION];
  stats->charisma = creature->curStats[CHARISMA];
  stats->dexterity = creature->curStats[DEXTERITY];
  
  return;
}

creatureClass getCreatureClass(creature *creature){
  return creature->class;
}

creatureSpecies getCreatureSpecies(creature *creature){
  return creature->species;
}

char *getCreatureName(creature *creature){
  return creature->name;
}

void setIsPlayer(creature *creature){
  creature->isPlayer = true;
  
  return;
}

void changeDispChar(creature *creature, char c){
  creature->dispChar = c;
  
  return;
}

char getCreatureDispChar(creature *creature){
  return creature->dispChar;
}

coord3D getCreatureLocation(creature *creature){
  return creature->location;
}

unsigned int getCreatureMapLevel(creature *creature){
  return creature->location.level;
}

void setCreatureLocation(creature *creature, coord3D location){
  creature->location.x = location.x;
  creature->location.y = location.y;
  creature->location.level = location.level;
  
  return;
}