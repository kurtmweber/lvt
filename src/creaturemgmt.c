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
#include <stdlib.h>

#include "lvt.h"

#include "creaturemgmt.h"

#include "allocator.h"
#include "creature.h"
#include "creaturelist.h"
#include "game.h"
#include "item.h"

/* ALWAYS check the return value of addCreatureInventoryItem().  If the list is full, then the item
 * is not added to inventory, and so you need to do something appropriate with it
 */
char addCreatureInventoryItem(creature *creature, item *item){
	char i = 0;
	
	while (creature->inventory[i] && (i < 51)){
		i++;
	}
	
	if (creature->inventory[i] && (i == 51)){
		return 0;   // list is full
	}
	
	item->owned = true;
	
	creature->inventory[i] = item;
	setItemOwned(item, true);
	setItemOwner(item, creature);
	
	if (isSeed(item)){
		setSeedRest(item, 0);
		setSeedDormancy(item, 0);
	}
	
	return inventoryIndexToLetter(i);    
}

void changeDispChar(creature *creature, char c){
	creature->dispChar = c;
	
	return;
}

void decrementCreatureSpeedCounter(creature *creature, unsigned int decrAmount){
	creature->moveInfo.speedCounter -= decrAmount;
	
	return;
}

item *findInventoryWeapon(creature *creature){
	unsigned int i = 0;
	
	for (i = 0; i < 52; i++){
		if (creature->inventory[i]){
			if (isWeapon(creature->inventory[i])){
				return creature->inventory[i];
			}
		}
	}
}

item *getArmor(creature *creature){
	if (creature->armor.armor){
		return creature->armor.armor;
	} else {
		return NULL;
	}
}

item *getCloak(creature *creature){
	if (creature->armor.cloak){
		return creature->armor.cloak;
	} else {
		return NULL;
	}
}

creatureAggression getCreatureAggression(creature *creature){
	return creature->aggression;
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

unsigned int getCreatureAttribute(creature *creature){
	return creature->attrs;
}

bioSex getCreatureBioSex(creature *creature){
	return creature->sex;
}

creatureClass getCreatureClass(creature *creature){
	return creature->class;
}

colorPairs getCreatureColor(creature *creature){
	return creature->color;
}

unsigned int getCreatureCurHp(creature *creature){
	return creature->curHitPoints;
}

int getCreatureCurInt(creature *creature){
	return creature->curStats[INTELLIGENCE];
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

char getCreatureDispChar(creature *creature){
	return creature->dispChar;
}

unsigned int getCreatureFaction(creature *creature){
	return creature->faction;
}

void getCreatureInventory(creature *creature, item *inventory[52]){
	unsigned int i;
	
	for (i = 0; i < 52; i++){
		inventory[i] = creature->inventory[i];
	}
	
	return;
}

unsigned int getCreatureLastMove(creature *creature){
	return creature->moveInfo.lastMove;
}

unsigned int getCreatureLevel(creature *creature){
	return creature->level;
}

coord3D getCreatureLocation(creature *creature){
	return creature->location;
}

unsigned int getCreatureMapLevel(creature *creature){
	return creature->location.level;
}

bool getCreatureMatured(creature *creature){
	return creature->hasMatured;
}

unsigned int getCreatureMaxHp(creature *creature){
	return creature->maxHitPoints;
}

char *getCreatureName(creature *creature){
	return creature->name;
}

unsigned int getCreatureNutrition(creature *creature){
	return creature->nutrition;
}

creatureSpecies getCreatureSpecies(creature *creature){
	return creature->species;
}

unsigned int getCreatureSpeed(creature *creature){
	return creature->moveInfo.speed;
}

unsigned int getCreatureSpeedCounter(creature *creature){
	return creature->moveInfo.speedCounter;
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

item *getCreatureWeapon(creature *creature){
	return creature->weapon;
}

unsigned int getCreatureWeight(creature *creature){
	return creature->weight;
}

unsigned int getCreatureXp(creature *creature){
	return creature->experience;
}

bool getInCombat(creature *creature){
	return creature->inCombat;
}

item *getGloves(creature *creature){
	if (creature->armor.gloves){
		return creature->armor.gloves;
	} else {
		return NULL;
	}
}

item *getLeggings(creature *creature){
	if (creature->armor.leggings){
		return creature->armor.leggings;
	} else {
		return NULL;
	}
}

item *getHelmet(creature *creature){
	if (creature->armor.helmet){
		return creature->armor.helmet;
	} else {
		return NULL;
	}
}

item *getShield(creature *creature){
	if (creature->armor.shield){
		return creature->armor.shield;
	} else {
		return NULL;
	}
}

item *getShirt(creature *creature){
	if (creature->armor.shirt){
		return creature->armor.shirt;
	} else {
		return NULL;
	}
}

item *getShoes(creature *creature){
	if (creature->armor.shoes){
		return creature->armor.shoes;
	} else {
		return NULL;
	}
}

item *getUnderarmor(creature *creature){
	if (creature->armor.underarmor){
		return creature->armor.underarmor;
	} else {
		return NULL;
	}
}

item *getWieldNextTurn(creature *creature){
	return creature->wieldNextTurn;
}

bool hasArmor(creature *creature){
	if (creature->armor.armor){
		return true;
	} else {
		return false;
	}
}

bool hasCloak(creature *creature){
	if (creature->armor.cloak){
		return true;
	} else {
		return false;
	}
}

bool hasCreatureMatured(creature *creature){
	unsigned int i;
	
	if (getCreatureMatured(creature)){    // Obviously, the tests below will also pass if current stats
		return true;                        // have started to decline due to aging, so if the matured flag
	}                                     // is set, we skip them outright
	
	for (i = 0; i < MAXSTATNAME; i++){
		if (creature->curStats[i] != creature->maxStats[i]){
			return false;
		}
	}
	
	return true;
}

bool hasFoodInventory(creature *creature){
	unsigned int i = 0;
	itemClassId cId;
	
	for (i = 0; i < 52; i++){
		if (creature->inventory[i]){
			cId = getItemClass(creature->inventory[i]);
			if ((cId == ITEM_TYPE_FRUIT) || (cId == ITEM_TYPE_CORPSE)){
				return true;
			}
		}
	}
	
	return false;
}

bool hasGloves(creature *creature){
	if (creature->armor.gloves){
		return true;
	} else {
		return false;
	}
}

bool hasHelmet(creature *creature){
	if (creature->armor.helmet){
		return true;
	} else {
		return false;
	}
}

bool hasLeggings(creature *creature){
	if (creature->armor.leggings){
		return true;
	} else {
		return false;
	}
}

bool hasShield(creature *creature){
	if (creature->armor.shield){
		return true;
	} else {
		return false;
	}
}

bool hasShirt(creature *creature){
	if (creature->armor.shirt){
		return true;
	} else {
		return false;
	}
}

bool hasShoes(creature *creature){
	if (creature->armor.shoes){
		return true;
	} else {
		return false;
	}
}

bool hasUnderarmor(creature *creature){
	if (creature->armor.underarmor){
		return true;
	} else {
		return false;
	}
}

bool hasWeapon(creature *creature){
	if (creature->weapon){
		return true;
	} else {
		return false;
	}
}

void incrementCreatureSpeedCounter(creature *creature, unsigned int incrAmount){
	creature->moveInfo.speedCounter += incrAmount;
	
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

void initCreatureInventory(creature *creature){
	unsigned int i;
	
	for (i = 0; i < 52; i++){
		creature->inventory[i] = 0;
	}
	
	return;
}

void initCreatureWeapon(creature *creature){
	creature->weapon = NULL;
	
	return;
}

bool isAggressive(struct creature *creature, struct creature *target){
	speciesAggression cSA;
	creatureAggression cCA;
	unsigned int cLevel, tLevel;
	unsigned int lDiff = 0;
	static rng localRng;
	static bool rngInitd = false;
	unsigned int random;
	
	if (!rngInitd){
		initializeRNG(&localRng);
		rngInitd = true;
	}
	
	
	cSA = getSpeciesAggression(getCreatureSpecies(creature));
	
	cCA = getCreatureAggression(creature);
	
	cLevel = getCreatureLevel(creature);
	tLevel = getCreatureLevel(target);
	
	if (cLevel < tLevel){
		lDiff = tLevel - cLevel;
	}
	
	// scenario: creature level 8, species aggression SPECIES_HITLER, creature aggression CREATURE_PEEVISH
	// target level 10
	// creature is weaker than target, so we take level difference into account, in this case 2
	// SPECIES_HITLER = 9, CREATURE_PEEVISH = 3
	// so we find a random number between 1 and (9 + 2 =)11
	// a CREATURE_PEEVISH creature has an (11 - 3 =)8/11 chance of not attacking
	// so if the number is greater than 8, we are aggressive this time
	
	random = uniformRandomRangeInt(&localRng, 1, cSA + lDiff);
	if (random > ((cSA + lDiff) - cCA)){
		return true;
	} else {
		return false;
	}
}

bool isCreatureHungry(creature *creature){
	return creature->hungry;
}

bool isInventoryFull(creature *creature){
	unsigned int i = 0;
	
	for (i = 0; i < 52; i++){
		if (!creature->inventory[i]){
			return false;
		}
	}
	
	return true;
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
	
	addContents(creatureLoc.level, creatureLoc.x, creatureLoc.y, creatureCorpse);
	setItemLocation(creatureCorpse, creatureLoc);
	
	corpseName = autoGenerateCorpseName(creature);
	setItemName(creatureCorpse, corpseName);
	setItemWeight(creatureCorpse, speciesData[getCreatureSpecies(creature)].weight);
	
	cNode = findCreatureListEntry(creatures, creature);
	creatures = removeCreatureNode(creatures, cNode);
	freeCreatureListEntry(cNode);
	return;
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
		if (chp == getCreatureMaxHp(creature) - 1){
			setInCombat(creature, false);
		}
	}
	
	return;
}

void removeCreatureInventoryItem(creature *creature, item *item){
	unsigned int i = 0;
	
	item->worn = false;
	item->wielded = false;
	setItemOwned(item, false);
	
	if (creature->weapon == item){
		creature->weapon = 0;
	}
	
	setItemOwner(item, NULL);
	
	for (i = 0; i < 52; i++){
		if (creature->inventory[i] == item){
			creature->inventory[i] = 0;
		}
	}
	
	return;
}

removeOutcome removeItem(creature *creature, item *item){
	if (!item){
		return REMOVE_FAILED_NOT_ITEM;
	}
	
	if (!item->worn){
		return REMOVE_FAILED_NOT_WORN;
	}
	
	item->worn = false;
	
	switch(item->itemClass){
		case ITEM_TYPE_SHIRT:
			creature->armor.shirt = NULL;
			break;
		case ITEM_TYPE_UNDERARMOR:
			creature->armor.underarmor = NULL;
			break;
		case ITEM_TYPE_ARMOR:
			creature->armor.armor = NULL;
			break;
		case ITEM_TYPE_HELMET:
			creature->armor.helmet = NULL;
			break;
		case ITEM_TYPE_CLOAK:
			creature->armor.cloak = NULL;
			break;
		case ITEM_TYPE_GLOVES:
			creature->armor.gloves = NULL;
			break;
		case ITEM_TYPE_LEGGINGS:
			creature->armor.leggings = NULL;
			break;
		case ITEM_TYPE_SHOES:
			creature->armor.shoes = NULL;
			break;
		case ITEM_TYPE_SHIELD:
			creature->armor.shield = NULL;
			break;
	}
	
	return REMOVE_SUCCEEDED;
}

item *selectOptimalFoodInventory(creature *creature){  
	unsigned int nutDiff;
	item *bestNutDiffItem = 0;
	itemClassId cId;
	unsigned int i = 0;
	int curNutDiff = 0;
	int bestNutDiff = 0;
	
	nutDiff = getCreatureWeight(creature) - getCreatureNutrition(creature);
	bestNutDiff = nutDiff;
	
	for (i = 0; i < 52; i++){
		if (creature->inventory[i]){
			cId = getItemClass(creature->inventory[i]);
			if ((cId == ITEM_TYPE_FRUIT) || (cId == ITEM_TYPE_CORPSE)){
				curNutDiff = nutDiff - getItemNutrition(creature->inventory[i]);
				if (abs(curNutDiff) < abs(bestNutDiff)){
					bestNutDiff = curNutDiff;
					bestNutDiffItem = creature->inventory[i];
				}
			}
		}
	}
	
	return bestNutDiffItem;
}

void setCreatureAggression(creature *creature, creatureAggression aggression){
	creature->aggression = aggression;
	
	return;
}

void setCreatureAttribute(creature *creature, unsigned int attribute){
	creature->attrs = attribute;
	
	return;
}

void setCreatureBioSex(creature *creature, bioSex sex){
	creature->sex = sex;
	
	return;
}

void setCreatureClass(creature *creature, creatureClass class){
	creature->class = class;
	
	return;
}

void setCreatureColor(creature *creature, colorPairs colorPair){
	creature->color = colorPair;
	
	return;
}

void setCreatureCurHp(creature *creature, unsigned int curHp){
	creature->curHitPoints = curHp;
	
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

void setCreatureFaction(creature *creature, unsigned int faction){
	creature->faction = faction;
	
	return;
}

void setCreatureHungry(creature *creature){
	creature->hungry = true;
	
	return;
}

void setCreatureLastMove(creature *creature, unsigned int move){
	creature->moveInfo.lastMove = move;
	
	return;
}

void setCreatureLevel(creature *creature, unsigned int level){
	creature->level = level;
	
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
		newLevel = MAX((unsigned int)floor(log2(Xp)), 1);   // can't run log2() on 0, gives error
	}
	
	setCreatureLevel(creature, newLevel);
	
	newMaxHp = (unsigned int)ceil(pow(1.1, newLevel - 1) * getSpeciesBaseHp(getCreatureSpecies(creature)));
	// newLevel - 1 so that level 1 gets base, level 2 gets base * 1.1, etc.
	
	newCurHp = newMaxHp - hpDiff;
	
	setCreatureMaxHp(creature, newMaxHp);
	setCreatureCurHp(creature, newCurHp);
	
	return;
}

void setCreatureLifePace(creature *creature, unsigned int lifePace){
	creature->lifePace = lifePace;
	
	return;
}

void setCreatureLocation(creature *creature, coord3D location){
	creature->location.x = location.x;
	creature->location.y = location.y;
	creature->location.level = location.level;
	
	return;
}

void setCreatureMatured(creature *creature, bool matured){
	creature->hasMatured = matured;
	
	return;
}

void setCreatureMaxHp(creature *creature, unsigned int maxHp){
	creature->maxHitPoints = maxHp;
	
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

void setCreatureName(creature *creature, char *name){
	creature->name = name;
	
	return;
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

void setCreatureSpecies(creature *creature, creatureSpecies species){
	creature->species = species;
	
	return;
}

void setCreatureSpeed(creature *creature, unsigned int speed){
	creature->moveInfo.speed = speed;
	
	return;
}

void setCreatureWeight(creature *creature, unsigned int weight){
	creature->weight = weight;
}

void setCreatureXp(creature *creature, unsigned int Xp){
	creature->experience = Xp;
	
	return;
}

void setInCombat(creature *creature, bool status){
	creature->inCombat = status;
	
	return;
}

void setIsPlayer(creature *creature){
	creature->isPlayer = true;
	
	return;
}

void setWieldNextTurn(creature *creature, item *item){
	creature->wieldNextTurn = item;
	
	return;
}

void unsetCreatureHungry(creature *creature){
	creature->hungry = false;
	
	return;
}

void unwieldWeapon(creature *creature){  
	if (creature->weapon){
		setItemWielded(creature->weapon, false);
	}
	
	creature->weapon = 0;
	
	return;
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

wearOutcome wearItem(creature *creature, item *item){
	
	if (item == getCreatureWeapon(creature)){
		return WEAR_FAILED_WIELDED;
	}
	
	/* If there's already something being worn in the given slot, we don't give an error,
	 * we just replace it.  Might want to change this in the future?
	 */
	switch(item->itemClass){
		case ITEM_TYPE_SHIRT:
			if (creature->armor.shirt){
				setItemWorn(creature->armor.shirt, false);
			}
			creature->armor.shirt = item;
			setItemWorn(item, true);
			break;
		case ITEM_TYPE_UNDERARMOR:
			if (creature->armor.underarmor){
				setItemWorn(creature->armor.underarmor, false);
			}
			creature->armor.underarmor = item;
			setItemWorn(item, true);
			break;
		case ITEM_TYPE_ARMOR:
			if (creature->armor.armor){
				setItemWorn(creature->armor.armor, false);
			}
			creature->armor.armor = item;
			setItemWorn(item, true);
			break;
		case ITEM_TYPE_HELMET:
			if  (creature->armor.helmet){
				setItemWorn(creature->armor.helmet, false);
			}
			creature->armor.helmet = item;
			setItemWorn(item, true);
			break;
		case ITEM_TYPE_CLOAK:
			if (creature->armor.cloak){
				setItemWorn(creature->armor.cloak, false);
			}
			creature->armor.cloak = item;
			setItemWorn(item, true);
			break;
		case ITEM_TYPE_GLOVES:
			if (creature->armor.gloves){
				setItemWorn(creature->armor.gloves, false);
			}
			creature->armor.gloves = item;
			setItemWorn(item, true);
			break;
		case ITEM_TYPE_LEGGINGS:
			if (creature->armor.leggings){
				setItemWorn(creature->armor.leggings, false);
			}
			creature->armor.leggings = item;
			setItemWorn(item, true);
			break;
		case ITEM_TYPE_SHOES:
			if (creature->armor.shoes){
				setItemWorn(creature->armor.shoes, false);
			}
			creature->armor.shoes = item;
			setItemWorn(item, true);
			break;
		case ITEM_TYPE_SHIELD:
			if (creature->armor.shield){
				setItemWorn(creature->armor.shield, false);
			}
			creature->armor.shield = item;
			setItemWorn(item, true);
			break;
		default:
			return WEAR_FAILED_NOT_ARMOR;
	}
	
	return WEAR_SUCCEEDED;
}

wieldOutcome wieldItem(creature *creature, item *item){  
	if ((creature->armor.shield) && (item->itemData.twoHandedWield)){
		return WIELD_FAILED_TWOHANDED;
	}
	
	if (isWorn(item)){
		return WIELD_FAILED_WORN;
	}
	
	if (creature->weapon){
		creature->weapon->wielded = false;
		creature->weapon = 0;
	}
	
	setItemWielded(item, true);
	creature->weapon = item;
	
	return WIELD_SUCCEEDED;
}