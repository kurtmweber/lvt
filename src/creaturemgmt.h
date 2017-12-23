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

#ifndef _CREATUREMGMT_H
#define _CREATUREMGMT_H

typedef enum wieldOutcome{
  WIELD_SUCCEEDED,
  WIELD_FAILED_TWOHANDED,	// could not wield because it is a two-handed object and creature is
				// equipped with a shield
  WIELD_FAILED_WEIGHT,
  WIELD_FAILED
} wieldOutcome;

typedef enum wearOutcome{
  WEAR_SUCCEEDED,
  WEAR_FAILED_NOT_ARMOR
} wearOutcome;

typedef enum removeOutcome{
  REMOVE_SUCCEEDED,
  REMOVE_FAILED_NOT_WORN,
  REMOVE_FAILED_NOT_ITEM
} removeOutcome;

#ifndef _CREATUREMGMT_C
char addCreatureInventoryItem(creature *creature, item *item);
void changeDispChar(creature *creature, char c);
void decrementCreatureSpeedCounter(creature *creature, unsigned int decrAmount);
item *findInventoryWeapon(creature *creature);
item *getArmor(creature *creature);
item *getCloak(creature *creature);
creatureAggression getCreatureAggression(creature *creature);
unsigned int getCreatureArmorClass(creature *creature);
unsigned int getCreatureAttribute(creature *creature);
bioSex getCreatureBioSex(creature *creature);
creatureClass getCreatureClass(creature *creature);
colorPairs getCreatureColor(creature *creature);
unsigned int getCreatureCurHp(creature *creature);
int getCreatureCurInt(creature *creature);
void getCreatureCurStats(creature *creature, statList *stats);
char getCreatureDispChar(creature *creature);
unsigned int getCreatureFaction(creature *creature);
void getCreatureInventory(creature *creature, item *inventory[52]);
unsigned int getCreatureLastMove(creature *creature);
unsigned int getCreatureLevel(creature *creature);
coord3D getCreatureLocation(creature *creature);
unsigned int getCreatureMapLevel(creature *creature);
bool getCreatureMatured(creature *creature);
unsigned int getCreatureMaxHp(creature *creature);
void getCreatureMaxStats(creature *creature, statList *stats);
char *getCreatureName(creature *creature);
unsigned int getCreatureNutrition(creature *creature);
creatureSpecies getCreatureSpecies(creature *creature);
unsigned int getCreatureSpeed(creature *creature);
unsigned int getCreatureSpeedCounter(creature *creature);
unsigned int getCreatureWeight(creature *creature);
unsigned int getCreatureXp(creature *creature);
item *getGloves(creature *creature);
item *getHelmet(creature *creature);
bool getInCombat(creature *creature);
item *getLeggings(creature *creature);
item *getShield(creature *creature);
item *getShirt(creature *creature);
item *getShoes(creature *creature);
item *getUnderarmor(creature *creature);
item *getWieldNextTurn(creature *creature);
bool hasArmor(creature *creature);
bool hasCloak(creature *creature);
bool hasCreatureMatured(creature *creature);
bool hasFoodInventory(creature *creature);
bool hasGloves(creature *creature);
bool hasHelmet(creature *creature);
bool hasLeggings(creature *creature);
bool hasShield(creature *creature);
bool hasShirt(creature *creature);
bool hasShoes(creature *creature);
bool hasUnderarmor(creature *creature);
bool hasWeapon(creature *creature);
void incrementCreatureSpeedCounter(creature *creature, unsigned int incrAmount);
void initCreatureArmor(creature *creature);
void initCreatureInventory(creature *creature);
void initCreatureWeapon(creature *creature);
bool isAggressive (struct creature *creature, struct creature *target);
bool isCreatureHungry(creature *creature);
bool isInventoryFull(creature *creature);
void killCreature(creature *creature);
void regenerateHitPoints(creature *creature);
void removeCreatureInventoryItem(creature *creature, item *item);
removeOutcome removeItem(creature *creature, item *item);
item *selectOptimalFoodInventory(creature *creature);
void setCreatureAggression(creature *creature, creatureAggression aggression);
void setCreatureAttribute(creature *creature, unsigned int attribute);
void setCreatureBioSex(creature *creature, bioSex sex);
void setCreatureClass(creature *creature, creatureClass class);
void setCreatureColor(creature *creature, colorPairs colorPair);
void setCreatureCurHp(creature *creature, unsigned int curHp);
void setCreatureCurStats(creature *creature, int stats[MAXSTATNAME]);
void setCreatureFaction(creature *creature, unsigned int faction);
void setCreatureHungry(creature *creature);
void setCreatureLastMove(creature *creature, unsigned int move);
void setCreatureLevel(creature *creature, unsigned int level);
void setCreatureLevelHpXp(creature *creature, unsigned int Xp);
void setCreatureLifePace(creature *creature, unsigned int lifePace);
void setCreatureLocation(creature *creature, coord3D location);
void setCreatureMatured(creature *creature, bool matured);
void setCreatureMaxHp(creature *creature, unsigned int maxHp);
void setCreatureMaxStats(creature *creature, int stats[MAXSTATNAME]);
void setCreatureName(creature *creature, char *name);
void setCreatureNutrition (creature *creature, unsigned int nutrition);
void setCreatureSpecies(creature *creature, creatureSpecies species);
void setCreatureSpeed(creature *creature, unsigned int speed);
void setCreatureWeight(creature *creature, unsigned int weight);
void setCreatureXp(creature *creature, unsigned int Xp);
void setInCombat(creature *creature, bool status);
void setIsPlayer(creature *creature);
void setWieldNextTurn(creature *creature, item *item);
bool updateCreatureLifeCycle(creature *creature);
bool updateCreatureNutrition(creature *creature);
void unsetCreatureHungry(creature *creature);
void unwieldWeapon(creature *creature);
wearOutcome wearItem(creature *creature, item *item);
wieldOutcome wieldItem(creature *creature, item *item);
#else
creatureAggression getCreatureAggression(creature *creature);
unsigned int getCreatureCurHp(creature *creature);
void getCreatureCurStats(creature *creature, statList *stats);
unsigned int getCreatureMaxHp(creature *creature);
coord3D getCreatureLocation(creature *creature);
void getCreatureMaxStats(creature *creature, statList *stats);
unsigned int getCreatureNutrition(creature *creature);
unsigned int getCreatureWeight(creature *creature);
void setCreatureCurHp(creature *creature, unsigned int curHp);
void setCreatureCurStats(creature *creature, int stats[MAXSTATNAME]);
void setCreatureLevel(creature *creature, unsigned int level);
void setCreatureMaxHp(creature *creature, unsigned int maxHp);
void setCreatureMaxStats(creature *creature, int stats[MAXSTATNAME]);
void setCreatureNutrition (creature *creature, unsigned int nutrition);
void setCreatureXp(creature *creature, unsigned int Xp);
void setInCombat(creature *creature, bool status);
bool updateCreatureLifeCycleMatured(creature *creature);
bool updateCreatureLifeCycleNotMatured(creature *creature);
#endif

#endif