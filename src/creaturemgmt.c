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

void setCreatureLifePace(creature *creature, unsigned int lifePace){
  creature->lifePace = lifePace;
  
  return;
}

bool hasCreatureMatured(creature *creature){
  unsigned int i;
  
  if (getCreatureMatured(creature)){	// Obviously, the tests below will also pass if current stats
    return true;			// have started to decline due to aging, so if the matured flag
  }					// is set, we skip them outright
  
  for (i = 0; i < MAXSTATNAME; i++){
    if (creature->curStats[i] != creature->maxStats[i]){
      return false;
    }
  }
    
    return true;
}

bool updateCreatureLifeCycle(creature *creature){
  if (!getCreatureMatured(creature) && hasCreatureMatured(creature)){
    setCreatureMatured(creature, true);
    return true;
  }
  
  if (!getCreatureMatured(creature)){
    if (!updateCreatureLifeCycleNotMatured(creature)){
      setCreatureMatured(creature, true);
      return true;
    }
  } else {
    if (!updateCreatureLifeCycleMatured(creature)){
      return false;
    }
  }
}

bool updateCreatureLifeCycleNotMatured(creature *creature){
  unsigned int i = 0;
  unsigned int statsNotMature[6];
  static rng lifeCycleRng;
  static bool rngInitd = false;
  statList curStats, maxStats;
  unsigned int rand;
  unsigned int stats[6];
  
  if (!rngInitd){
    initializeRNG(&lifeCycleRng);
    rngInitd = true;
  }
  
  getCreatureMaxStats(creature, &maxStats);
  getCreatureCurStats(creature, &curStats);
  
  if (curStats.strength < maxStats.strength){
    statsNotMature[i] = STRENGTH;
    i++;
  }
  
  if (curStats.intelligence < maxStats.intelligence){
    statsNotMature[i] = INTELLIGENCE;
    i++;
  }
  
  if (curStats.wisdom < maxStats.wisdom){
    statsNotMature[i] = WISDOM;
    i++;
  }
  
  if (curStats.constitution < maxStats.constitution){
    statsNotMature[i] = CONSTITUTION;
    i++;
  }
  
  if (curStats.charisma < maxStats.charisma){
    statsNotMature[i] = CHARISMA;
    i++;
  }
  
  if (curStats.dexterity < maxStats.dexterity){
    statsNotMature[i] = DEXTERITY;
    i++;
  }
  
  if (i == 0){
    return false;
  }
  
  if (uniformRandomRangeInt(&lifeCycleRng, 1, creature->lifePace) == creature->lifePace){
    rand = uniformRandomRangeInt(&lifeCycleRng, 1, i);
    switch (statsNotMature[rand - 1]){
      case STRENGTH:
	curStats.strength++;
	break;
      case INTELLIGENCE:
	curStats.intelligence++;
	break;
      case WISDOM:
	curStats.wisdom++;
	break;
      case CONSTITUTION:
	curStats.constitution++;
	break;
      case CHARISMA:
	curStats.charisma++;
	break;
      case DEXTERITY:
	curStats.dexterity++;
	break;
      default:
	break;
    }
    
    stats[STRENGTH] = curStats.strength;
    stats[INTELLIGENCE] = curStats.intelligence;
    stats[WISDOM] = curStats.wisdom;
    stats[CONSTITUTION] = curStats.constitution;
    stats[CHARISMA] = curStats.charisma;
    stats[DEXTERITY] = curStats.dexterity;
    
    setCreatureCurStats(creature, stats);
  }
  
  return true;
}

bool updateCreatureLifeCycleMatured(creature *creature){
  static rng lifeCycleRng;
  static bool rngInitd = false;
  statList curStats;
  unsigned int rand;
  unsigned int stats[6];
  
  if (!rngInitd){
    initializeRNG(&lifeCycleRng);
    rngInitd = true;
  }
  
 getCreatureCurStats(creature, &curStats);
  
  if (uniformRandomRangeInt(&lifeCycleRng, 1, creature->lifePace) == creature->lifePace){
    rand = uniformRandomRangeInt(&lifeCycleRng, 1, MAXSTATNAME);
    switch (rand - 1){
      case STRENGTH:
	curStats.strength--;
	break;
      case INTELLIGENCE:
	curStats.intelligence--;
	break;
      case WISDOM:
	curStats.wisdom--;
	break;
      case CONSTITUTION:
	curStats.constitution--;
	break;
      case CHARISMA:
	curStats.charisma--;
	break;
      case DEXTERITY:
	curStats.dexterity--;
	break;
      default:
	break;
    }
    
    stats[STRENGTH] = curStats.strength;
    stats[INTELLIGENCE] = curStats.intelligence;
    stats[WISDOM] = curStats.wisdom;
    stats[CONSTITUTION] = curStats.constitution;
    stats[CHARISMA] = curStats.charisma;
    stats[DEXTERITY] = curStats.dexterity;
    
    setCreatureCurStats(creature, stats);
  }
  
  if ((stats[STRENGTH] == 0) || (stats[INTELLIGENCE] == 0) || (stats[WISDOM] == 0) || \
      (stats[CONSTITUTION] == 0) || (stats[CHARISMA] == 0) || (stats[DEXTERITY] == 0)){
    return false;
  }
  
  return true;
}

void getCreatureMaxStats(creature *creature, statList *stats){
  stats->strength = creature->maxStats[STRENGTH];
  stats->intelligence = creature->maxStats[INTELLIGENCE];
  stats->wisdom = creature->maxStats[WISDOM];
  stats->constitution = creature->maxStats[CONSTITUTION];
  stats->charisma = creature->maxStats[CHARISMA];
  stats->dexterity = creature->maxStats[DEXTERITY];
  
  return;
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

void setCreatureLevel(creature *creature, unsigned int level){
  creature->level = level;
  
  return;
}

void setCreatureMaxHp(creature *creature, unsigned int maxHp){
  creature->maxHitPoints = maxHp;
  
  return;
}

void setCreatureCurHp(creature *creature, unsigned int curHp){
  creature->curHitPoints = curHp;
  
  return;
}

void setCreatureXp(creature *creature, unsigned int Xp){
  creature->experience = Xp;
  
  return;
}

unsigned int getCreatureLevel(creature *creature){
  return creature->level;
}

unsigned int getCreatureXp(creature *creature){
  return creature->experience;
}

unsigned int getCreatureCurHp(creature *creature){
  return creature->curHitPoints;
}

unsigned int getCreatureMaxHp(creature *creature){
  return creature->maxHitPoints;
}