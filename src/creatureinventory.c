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

#define _CREATUREINVENTORY_C

#include <stdbool.h>
#include <stdlib.h>

#include "lvt.h"

#include "creatureinventory.h"

#include "attack.h"
#include "creature.h"
#include "creaturemgmt.h"

bool creaturePickupArmor(creature *curCreature){
	coord3D curLoc;
	mapSpaceContents *contents, *thisContent;
	unsigned int numArmor = 0;
	item **armorList = 0;
	unsigned int i = 0;
	unsigned int curVal;
	item *testArmor;
	
	if (isInventoryFull(curCreature)){
		return false;
	}
	
	curLoc = getCreatureLocation(curCreature);
	contents = getContents(dungeon[curLoc.level], curLoc.x, curLoc.y);
	dungeon[curLoc.level][curLoc.x][curLoc.y].contents = 0;
	
	thisContent = contents;
	
	while (thisContent){
		if (isArmor(thisContent->item)){
			numArmor++;
			armorList = realloc(armorList, numArmor * sizeof(item *));
			armorList[numArmor - 1] = thisContent->item;
		}
		thisContent = thisContent->next;
	}
	
	if (!numArmor){
		while (contents){
			addContents(curLoc.level, curLoc.x, curLoc.y, contents->item);
			contents = contents->next;
		}
		free(armorList);
		return false;
	}
	
	for (i = 0; i < numArmor; i++){
		if (armorSlotMatch(armorList[i], ARMOR_SHIRT)){
			if (hasShirt(curCreature)){
				testArmor = getShirt(curCreature);
				if (getEffectiveArmor(testArmor) < getEffectiveArmor(armorList[i])){
					addCreatureInventoryItem(curCreature, armorList[i]);
					free(armorList);
					return true;
				}
			} else {
				addCreatureInventoryItem(curCreature, armorList[i]);
				free(armorList);
				return true;
			}
		}
		
		if (armorSlotMatch(armorList[i], ARMOR_UNDERARMOR)){
			if (hasUnderarmor(curCreature)){
				testArmor = getUnderarmor(curCreature);
				if (getEffectiveArmor(testArmor) < getEffectiveArmor(armorList[i])){
					addCreatureInventoryItem(curCreature, armorList[i]);
					free(armorList);
					return true;
				}
			} else {
				addCreatureInventoryItem(curCreature, armorList[i]);
				free(armorList);
				return true;
			}
		}
		
		if (armorSlotMatch(armorList[i], ARMOR_ARMOR)){
			if (hasArmor(curCreature)){
				testArmor = getUnderarmor(curCreature);
				if (getEffectiveArmor(testArmor) < getEffectiveArmor(armorList[i])){
					addCreatureInventoryItem(curCreature, armorList[i]);
					free(armorList);
					return true;
				}
			} else {
				addCreatureInventoryItem(curCreature, armorList[i]);
				free(armorList);
				return true;
			}
		}
		
		if (armorSlotMatch(armorList[i], ARMOR_HELMET)){
			if (hasHelmet(curCreature)){
				testArmor = getHelmet(curCreature);
				if (getEffectiveArmor(testArmor) < getEffectiveArmor(armorList[i])){
					addCreatureInventoryItem(curCreature, armorList[i]);
					free(armorList);
					return true;
				}
			} else {
				addCreatureInventoryItem(curCreature, armorList[i]);
				free(armorList);
				return true;
			}
		}
		
		if (armorSlotMatch(armorList[i], ARMOR_CLOAK)){
			if (hasCloak(curCreature)){
				testArmor = getCloak(curCreature);
				if (getEffectiveArmor(testArmor) < getEffectiveArmor(armorList[i])){
					addCreatureInventoryItem(curCreature, armorList[i]);
					free(armorList);
					return true;
				}
			} else {
				addCreatureInventoryItem(curCreature, armorList[i]);
				free(armorList);
				return true;
			}
		}
		
		if (armorSlotMatch(armorList[i], ARMOR_GLOVES)){
			if (hasGloves(curCreature)){
				testArmor = getGloves(curCreature);
				if (getEffectiveArmor(testArmor) < getEffectiveArmor(armorList[i])){
					addCreatureInventoryItem(curCreature, armorList[i]);
					free(armorList);
					return true;
				}
			} else {
				addCreatureInventoryItem(curCreature, armorList[i]);
				free(armorList);
				return true;
			}
		}
		
		if (armorSlotMatch(armorList[i], ARMOR_LEGGINGS)){
			if (hasLeggings(curCreature)){
				testArmor = getLeggings(curCreature);
				if (getEffectiveArmor(testArmor) < getEffectiveArmor(armorList[i])){
					addCreatureInventoryItem(curCreature, armorList[i]);
					free(armorList);
					return true;
				}
			} else {
				addCreatureInventoryItem(curCreature, armorList[i]);
				free(armorList);
				return true;
			}
		}
		
		if (armorSlotMatch(armorList[i], ARMOR_SHOES)){
			if (hasShoes(curCreature)){
				testArmor = getShoes(curCreature);
				if (getEffectiveArmor(testArmor) < getEffectiveArmor(armorList[i])){
					addCreatureInventoryItem(curCreature, armorList[i]);
					free(armorList);
					return true;
				}
			} else {
				addCreatureInventoryItem(curCreature, armorList[i]);
				free(armorList);
				return true;
			}
		}
		
		if (armorSlotMatch(armorList[i], ARMOR_SHIELD)){
			if (hasShield(curCreature)){
				testArmor = getShield(curCreature);
				if (getEffectiveArmor(testArmor) < getEffectiveArmor(armorList[i])){
					addCreatureInventoryItem(curCreature, armorList[i]);
					free(armorList);
					return true;
				}
			} else {
				addCreatureInventoryItem(curCreature, armorList[i]);
				free(armorList);
				return true;
			}
		}
		
		addContents(curLoc.level, curLoc.x, curLoc.y, armorList[i]);
	}
	
	free(armorList);
	return false;
}

bool creaturePickupWeapon(creature *curCreature){
	coord3D curLoc;
	mapSpaceContents *contents, *thisContent;
	item **weaponList = 0;
	unsigned int numWeapons = 0;
	long double *weaponValues = 0;
	unsigned int i, j;
	static rng localRng;
	static bool rngInitd = false;
	int curInt;
	item *curWeapon = 0, *secWeapon = 0, *testWeapon = 0;
	long double curWeaponValue = 0, secWeaponValue = 0, testWeaponValue = 0;
	
	if (isInventoryFull(curCreature)){
		return false;
	}
	
	if (!rngInitd){
		initializeRNG(&localRng);
		rngInitd = true;
	}
	
	curLoc = getCreatureLocation(curCreature);
	
	contents = getContents(dungeon[curLoc.level], curLoc.x, curLoc.y);
	dungeon[curLoc.level][curLoc.x][curLoc.y].contents = 0;
	
	thisContent = contents;
	
	while (thisContent){
		if (isWeapon(thisContent->item)){
			numWeapons++;
			weaponList = realloc(weaponList, numWeapons * sizeof(item *));
			weaponList[numWeapons - 1] = thisContent->item;
		}
		thisContent = thisContent->next;
	}
	
	if (!numWeapons){
		while (contents){
			addContents(curLoc.level, curLoc.x, curLoc.y, contents->item);
			contents = contents->next;
		}
		
		free(weaponList);
		return false;
	}
	
	weaponValues = calloc(numWeapons, sizeof(long double));
	
	curInt = getCreatureCurInt(curCreature);
	
	for (i = 0; i < curInt; i++){
		for (j = 0; j < numWeapons; j++){
			weaponValues[j] += uniformRandomRangeInt(&localRng, 0, calcAttackVal(curCreature, weaponList[j]));
		}
	}
	
	for (i = 0; i < numWeapons; i++){
		weaponValues[i] /= curInt;
	}
	
	i = returnIndexMaxValLongDouble(weaponValues, numWeapons);
	testWeapon = weaponList[i];
	testWeaponValue = weaponValues[i];
	
	if (hasWeapon(curCreature)){
		curWeapon = curCreature->weapon;
		for (i = 0; i < curInt; i++){
			curWeaponValue += uniformRandomRangeInt(&localRng, 0, calcAttackVal(curCreature, curWeapon));
		}
		
		curWeaponValue /= curInt;
	}
	
	if (secWeapon = findInventoryWeapon(curCreature)){
		for (i = 0; i < curInt; i++){
			secWeaponValue += uniformRandomRangeInt(&localRng, 0, calcAttackVal(curCreature, secWeapon));
		}
		
		secWeaponValue /= curInt;
	}
	
	if (testWeaponValue < secWeaponValue){
		while (contents){
			addContents(curLoc.level, curLoc.x, curLoc.y, contents->item);
			contents = contents->next;
		}
		free(weaponList);
		return false;
	} else {
		while (contents){
			if (contents->item != testWeapon){
				addContents(curLoc.level, curLoc.x, curLoc.y, contents->item);
			}
			contents = contents->next;
		}
		addCreatureInventoryItem(curCreature, testWeapon);
		if (secWeapon){
			removeCreatureInventoryItem(curCreature, secWeapon);
			addContents(curLoc.level, curLoc.x, curLoc.y, secWeapon);
		}
	}
	
	if (testWeaponValue > curWeaponValue){
		/*if (curWeapon && hasWeapon(curCreature)){
		 *     unwieldWeapon(curCreature);
	}
	wieldItem(curCreature, testWeapon);*/
		setWieldNextTurn(curCreature, testWeapon);
	}
	
	free(weaponList);
	return true;
}

bool creatureWearArmor(creature *curCreature){
	item *inventory[52];
	unsigned int i = 0;
	coord3D creaturePos;
	
	getCreatureInventory(curCreature, inventory);
	
	for (i = 0; i < 52; i++){
		if (inventory[i]){
			if (isArmor(inventory[i]) && !isWorn(inventory[i])){
				if (armorSlotMatch(inventory[i], ARMOR_SHIRT)){   
					if (getEffectiveArmor(inventory[i]) > getEffectiveArmor(getShirt(curCreature))){
						removeItem(curCreature, getShirt(curCreature));
						wearItem(curCreature, inventory[i]);
					} else {
						removeCreatureInventoryItem(curCreature, inventory[i]);
						creaturePos = getCreatureLocation(curCreature);
						addContents(creaturePos.level, creaturePos.x, creaturePos.y, inventory[i]);
					}
					return true;
				}
				
				if (armorSlotMatch(inventory[i], ARMOR_UNDERARMOR)){
					if (getEffectiveArmor(inventory[i]) > getEffectiveArmor(getUnderarmor(curCreature))){
						removeItem(curCreature, getUnderarmor(curCreature));
						wearItem(curCreature, inventory[i]);
					} else {
						removeCreatureInventoryItem(curCreature, inventory[i]);
						creaturePos = getCreatureLocation(curCreature);
						addContents(creaturePos.level, creaturePos.x, creaturePos.y, inventory[i]);
					}
					return true;
				}
				
				if (armorSlotMatch(inventory[i], ARMOR_ARMOR)){
					if (getEffectiveArmor(inventory[i]) > getEffectiveArmor(getArmor(curCreature))){
						removeItem(curCreature, getArmor(curCreature));
						wearItem(curCreature, inventory[i]);
					} else {
						removeCreatureInventoryItem(curCreature, inventory[i]);
						creaturePos = getCreatureLocation(curCreature);
						addContents(creaturePos.level, creaturePos.x, creaturePos.y, inventory[i]);
					}
					return true;
				}
				
				if (armorSlotMatch(inventory[i], ARMOR_HELMET)){
					if (getEffectiveArmor(inventory[i]) > getEffectiveArmor(getHelmet(curCreature))){
						removeItem(curCreature, getHelmet(curCreature));
						wearItem(curCreature, inventory[i]);
					} else {
						removeCreatureInventoryItem(curCreature, inventory[i]);
						creaturePos = getCreatureLocation(curCreature);
						addContents(creaturePos.level, creaturePos.x, creaturePos.y, inventory[i]);
					}
					return true;
				}
				
				if (armorSlotMatch(inventory[i], ARMOR_CLOAK)){
					if (getEffectiveArmor(inventory[i]) > getEffectiveArmor(getCloak(curCreature))){
						removeItem(curCreature, getCloak(curCreature));
						wearItem(curCreature, inventory[i]);
					} else {
						removeCreatureInventoryItem(curCreature, inventory[i]);
						creaturePos = getCreatureLocation(curCreature);
						addContents(creaturePos.level, creaturePos.x, creaturePos.y, inventory[i]);
					}
					return true;
				}
				
				if (armorSlotMatch(inventory[i], ARMOR_GLOVES)){
					if (getEffectiveArmor(inventory[i]) > getEffectiveArmor(getGloves(curCreature))){
						removeItem(curCreature, getGloves(curCreature));
						wearItem(curCreature, inventory[i]);
					} else {
						removeCreatureInventoryItem(curCreature, inventory[i]);
						creaturePos = getCreatureLocation(curCreature);
						addContents(creaturePos.level, creaturePos.x, creaturePos.y, inventory[i]);
					}
					return true;
				}
				
				if (armorSlotMatch(inventory[i], ARMOR_LEGGINGS)){
					if (getEffectiveArmor(inventory[i]) > getEffectiveArmor(getLeggings(curCreature))){
						removeItem(curCreature, getLeggings(curCreature));
						wearItem(curCreature, inventory[i]);
					} else {
						removeCreatureInventoryItem(curCreature, inventory[i]);
						creaturePos = getCreatureLocation(curCreature);
						addContents(creaturePos.level, creaturePos.x, creaturePos.y, inventory[i]);
					}
					return true;
				}
				
				if (armorSlotMatch(inventory[i], ARMOR_SHOES)){
					if (getEffectiveArmor(inventory[i]) > getEffectiveArmor(getShoes(curCreature))){
						removeItem(curCreature, getShoes(curCreature));
						wearItem(curCreature, inventory[i]);
					} else {
						removeCreatureInventoryItem(curCreature, inventory[i]);
						creaturePos = getCreatureLocation(curCreature);
						addContents(creaturePos.level, creaturePos.x, creaturePos.y, inventory[i]);
					}
					return true;
				}
				
				if (armorSlotMatch(inventory[i], ARMOR_SHIELD)){
					if (getEffectiveArmor(inventory[i]) > getEffectiveArmor(getShield(curCreature))){
						removeItem(curCreature, getShield(curCreature));
						wearItem(curCreature, inventory[i]);
					} else {
						removeCreatureInventoryItem(curCreature, inventory[i]);
						creaturePos = getCreatureLocation(curCreature);
						addContents(creaturePos.level, creaturePos.x, creaturePos.y, inventory[i]);
					}
					return true;
				}
			}
		}
	}
	
	return false;
}

bool creatureWieldWeapon(creature *curCreature){
	item *toWield;
	
	toWield = getWieldNextTurn(curCreature);
	
	// this does not take any steps to rectify the situation if wielding fails, e.g. because it's a two-handed
	// weapon and the creature is wearing a shield
	if (toWield){
		if (hasWeapon(curCreature)){
			unwieldWeapon(curCreature);
		}
		
		wieldItem(curCreature, toWield);
		setWieldNextTurn(curCreature, NULL);
		
		return true;
	}
	
	return false;
}

bool inventoryAction(creature *curCreature){
	if (creaturePickupWeapon(curCreature)){
		return true;
	} else if (creatureWieldWeapon(curCreature)){
		return true;
	} else if (creaturePickupArmor(curCreature)){
		return true;
	} else if (creatureWearArmor(curCreature)){
		return true;
	}
	
	return false;
}