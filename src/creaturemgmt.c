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

#include <math.h>
#include <stdbool.h>
#include "creaturemgmt.h"
#include "lvt.h"
#include "creature.h"
#include "item.h"

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

bool updateCreatureNutrition(creature *creature){
  unsigned int curNut;

  curNut = getCreatureNutrition(creature);
  
  if (curNut == 1){
    return false;
  } else {
    setCreatureNutrition(creature, curNut - 1);
    return true;
  }
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

void setCreatureBioSex(creature *creature, bioSex sex){
  creature->sex = sex;
  
  return;
}

bioSex getCreatureBioSex(creature *creature){
  return creature->sex;
}

void setCreatureColor(creature *creature, colorPairs colorPair){
  creature->color = colorPair;
  
  return;
}

void setCreatureAttribute(creature *creature, unsigned int attribute){
  creature->attrs = attribute;
  
  return;
}

colorPairs getCreatureColor(creature *creature){
  return creature->color;
}

unsigned int getCreatureAttribute(creature *creature){
  return creature->attrs;
}

void setCreatureFaction(creature *creature, unsigned int faction){
  creature->faction = faction;
  
  return;
}

unsigned int getCreatureFaction(creature *creature){
  return creature->faction;
}

void setCreatureSpeed(creature *creature, unsigned int speed){
  creature->moveInfo.speed = speed;
  
  return;
}

unsigned int getCreatureSpeed(creature *creature){
  return creature->moveInfo.speed;
}

void incrementCreatureSpeedCounter(creature *creature, unsigned int incrAmount){
  creature->moveInfo.speedCounter += incrAmount;
  
  return;
}

void decrementCreatureSpeedCounter(creature *creature, unsigned int decrAmount){
  creature->moveInfo.speedCounter -= decrAmount;
  
  return;
}

unsigned int getCreatureSpeedCounter(creature *creature){
  return creature->moveInfo.speedCounter;
}

unsigned int getCreatureLastMove(creature *creature){
  return creature->moveInfo.lastMove;
}

void setCreatureLastMove(creature *creature, unsigned int move){
  creature->moveInfo.lastMove = move;
  
  return;
}

void initCreatureArmor(creature *creature){
  creature->armor.shirt = NULL;
  creature->armor.underarmor = NULL;
  creature->armor.armor = NULL;
  creature->armor.helmet = NULL;
  creature->armor.cloak = NULL;
  creature->armor.gloves = NULL;
  creature->armor.leggings = NULL;
  creature->armor.shirt = NULL;
  creature->armor.shield = NULL;
  
  return;
}

void initCreatureWeapon(creature *creature){
  creature->weapon = NULL;
  
  return;
}

void initCreatureInventory(creature *creature){
  unsigned int i;
  
  for (i = 0; i < 52; i++){
    creature->inventory[i] = 0;
  }
  
  return;
}

char addCreatureInventoryItem(creature *creature, item *item){
  char i = 0;
  
  while (creature->inventory[i] && (i < 51)){
    i++;
  }
  
  if (creature->inventory[i] && (i == 51)){
    return 0;	// list is full
  }
  
  item->owned = true;
  
  creature->inventory[i] = item;
  
  return inventoryIndexToLetter(i);    
}

void removeCreatureInventoryItem(creature *creature, item *item){
  unsigned int i = 0;
  
  item->worn = false;
  item->wielded = false;
  item->owned = false;
  
  if (creature->weapon == item){
    creature->weapon = 0;
  }
  
  for (i = 0; i < 52; i++){
    if (creature->inventory[i] == item){
      creature->inventory[i] = 0;
    }
  }
  
  return;
}

void getCreatureInventory(creature *creature, item *inventory[52]){
  unsigned int i;
  
  for (i = 0; i < 52; i++){
   inventory[i] = creature->inventory[i];
  }
  
  return;
}

void unwieldWeapon(creature *creature){
  item *weapon;
  
  creature->weapon->wielded = false;
  
  creature->weapon = 0;
  
  return;
}

wieldOutcome wieldItem(creature *creature, item *item){  
  if ((creature->armor.shield) && (item->itemData.twoHandedWield)){
    return WIELD_FAILED_TWOHANDED;
  }
  
  if (creature->weapon){
    creature->weapon->wielded = false;
    creature->weapon = 0;
  }
  
  item->wielded = true;
  creature->weapon = item;
  
  return WIELD_SUCCEEDED;
}

wearOutcome wearItem(creature *creature, item *item){
  switch(item->itemClass){
    case ITEM_TYPE_SHIRT:
      if (creature->armor.shirt){
	creature->armor.shirt->worn = false;
      }
      creature->armor.shirt = item;
      creature->armor.shirt->worn = true;
      break;
    case ITEM_TYPE_UNDERARMOR:
      if (creature->armor.underarmor){
	creature->armor.underarmor->worn = false;
      }
      creature->armor.underarmor = item;
      creature->armor.underarmor->worn = true;
      break;
    case ITEM_TYPE_ARMOR:
      if (creature->armor.armor){
	creature->armor.armor->worn = false;
      }
      creature->armor.armor = item;
      creature->armor.armor->worn = true;
      break;
    case ITEM_TYPE_HELMET:
      if  (creature->armor.helmet){
	creature->armor.helmet->worn = false;
      }
      creature->armor.helmet = item;
      creature->armor.helmet->worn = true;
      break;
    case ITEM_TYPE_CLOAK:
      if (creature->armor.cloak){
	creature->armor.cloak->worn = false;
      }
      creature->armor.cloak = item;
      creature->armor.cloak->worn = true;
      break;
    case ITEM_TYPE_GLOVES:
      if (creature->armor.gloves){
	creature->armor.gloves->worn = false;
      }
      creature->armor.gloves = item;
      creature->armor.gloves->worn = true;
      break;
    case ITEM_TYPE_LEGGINGS:
      if (creature->armor.leggings){
	creature->armor.leggings->worn = false;
      }
      creature->armor.leggings = item;
      creature->armor.leggings->worn = true;
      break;
    case ITEM_TYPE_SHOES:
      if (creature->armor.shoes){
	creature->armor.shoes->worn = false;
      }
      creature->armor.shoes = item;
      creature->armor.shoes->worn = true;
      break;
    case ITEM_TYPE_SHIELD:
      if (creature->armor.shield){
	creature->armor.shield->worn = false;
      }
      creature->armor.shield = item;
      creature->armor.shield->worn = true;
      break;
    default:
      return WEAR_FAILED_NOT_ARMOR;
  }
  
  return WEAR_SUCCEEDED;
}

removeOutcome removeItem(creature *creature, item *item){
  if (!item->worn){
    return REMOVE_FAILED_NOT_WORN;
  }
  
  item->worn = false;
  
  switch(item->itemClass){
    case ITEM_TYPE_SHIRT:
      creature->armor.shirt = false;
      break;
    case ITEM_TYPE_UNDERARMOR:
      creature->armor.underarmor = false;
      break;
    case ITEM_TYPE_ARMOR:
      creature->armor.armor = false;
      break;
    case ITEM_TYPE_HELMET:
      creature->armor.helmet = false;
      break;
    case ITEM_TYPE_CLOAK:
      creature->armor.cloak = false;
      break;
    case ITEM_TYPE_GLOVES:
      creature->armor.gloves = false;
      break;
    case ITEM_TYPE_LEGGINGS:
      creature->armor.leggings = false;
      break;
    case ITEM_TYPE_SHOES:
      creature->armor.shoes = false;
      break;
    case ITEM_TYPE_SHIELD:
      creature->armor.shield = false;
      break;
  }
  
  return REMOVE_SUCCEEDED;
}

unsigned int getCreatureArmorClass(creature *creature){
  unsigned int ac = 0;
  
  if (creature->armor.shirt){
    ac += getEffectiveArmor(creature->armor.shirt);
  }
  
  if (creature->armor.underarmor){
    ac += getEffectiveArmor(creature->armor.underarmor);
  }
  
  if (creature->armor.armor){
    ac+= getEffectiveArmor(creature->armor.armor);
  }
  
  if (creature->armor.helmet){
    ac += getEffectiveArmor(creature->armor.helmet);
  }
  
  if (creature->armor.cloak){
    ac += getEffectiveArmor(creature->armor.cloak);
  }
  
  if (creature->armor.gloves){
    ac += getEffectiveArmor(creature->armor.gloves);
  }
  
  if (creature->armor.leggings){
    ac += getEffectiveArmor(creature->armor.leggings);
  }
  
  if (creature->armor.shoes){
    ac += getEffectiveArmor(creature->armor.shoes);
  }
  
  if (creature->armor.shield){
    ac += getEffectiveArmor(creature->armor.shield);
  }
  
  return ac;
}

void setCreatureNutrition (creature *creature, unsigned int nutrition){
  unsigned int weight;
  
  weight = getCreatureWeight(creature);
  
  if (nutrition >= weight){
    creature->nutrition = weight;
  } else {
    creature->nutrition = nutrition;
  }
}

unsigned int getCreatureNutrition(creature *creature){
  return creature->nutrition;
}

void killCreature(creature *creature){
  creatureList *cNode;
  coord3D creatureLoc;
  item *creatureCorpse;
  char *corpseName;
  
  if (creature == &player){
    playerDead();
  }
  
  creatureLoc = getCreatureLocation(creature);
  
  clearCreatureOccupant(dungeon[creatureLoc.level], creatureLoc.x, creatureLoc.y);
  
  creatureCorpse = spawnItem(ITEM_TYPE_CORPSE, getCreatureSpecies(creature));
  setCorpseNutrition(creatureCorpse, getCreatureWeight(creature));
  
  addContents(dungeon[creatureLoc.level], creatureLoc.x, creatureLoc.y, creatureCorpse);
  setItemLocation(creatureCorpse, creatureLoc);
  
  corpseName = autoGenerateCorpseName(creature);
  setItemName(creatureCorpse, corpseName);
  setItemWeight(creatureCorpse, speciesData[getCreatureSpecies(creature)].weight);
  
  cNode = findCreatureListEntry(creatures, creature);
  creatures = removeCreatureNode(creatures, cNode);
  freeCreatureListEntry(cNode);
  return;
}

void setCreatureLevelHpXp(creature *creature, unsigned int Xp){
  unsigned int hpDiff;
  unsigned int newLevel;
  unsigned int newMaxHp, newCurHp;
  
  setCreatureXp(creature, Xp);
  hpDiff = getCreatureMaxHp(creature) - getCreatureCurHp(creature);
  
  if (Xp == 0){
    newLevel = 1;
  } else {
    newLevel = MAX((unsigned int)floor(log2(Xp)), 1);	// can't run log2() on 0, gives error
  }
  
  setCreatureLevel(creature, newLevel);
  
  newMaxHp = (unsigned int)ceil(pow(1.1, newLevel - 1) * getSpeciesBaseHp(getCreatureSpecies(creature)));
  // newLevel - 1 so that level 1 gets base, level 2 gets base * 1.1, etc.

  newCurHp = newMaxHp - hpDiff;
  
  setCreatureMaxHp(creature, newMaxHp);
  setCreatureCurHp(creature, newCurHp);
  
  return;
}

void setCreatureWeight(creature *creature, unsigned int weight){
  creature->weight = weight;
}

unsigned int getCreatureWeight(creature *creature){
  return creature->weight;
}

bool hasWeapon(creature *creature){
  if (creature->weapon){
    return true;
  } else {
    return false;
  }
}

void regenerateHitPoints(creature *creature){
  unsigned int strength;
  unsigned int constitution;
  unsigned int chp;
  statList stats;
  static rng localRng;
  static bool rngInitd = false;
  unsigned int num;
  
  if (!rngInitd){
    initializeRNG(&localRng);
    rngInitd = true;
  }
  
  getCreatureCurStats(creature, &stats);
  strength = stats.strength;
  constitution = stats.constitution;
  
  chp = getCreatureCurHp(creature);
  
  num = uniformRandomRangeInt(&localRng, 1, strength + constitution + chp);
  if (num > strength + constitution){
    setCreatureCurHp(creature, chp + 1);
  }
  
  return;
}