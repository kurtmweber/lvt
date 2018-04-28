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

#ifndef _ITEM_H
#define _ITEM_H

#include <stdbool.h>
#include "creature.h"
#include "species.h"
#include "types.h"

typedef enum armorSlots{
	ARMOR_SHIRT		=	0b000000001,
	ARMOR_UNDERARMOR	=	0b000000010,
	ARMOR_ARMOR		=	0b000000100,
	ARMOR_HELMET		=	0b000001000,
	ARMOR_CLOAK		=	0b000010000,
	ARMOR_GLOVES		=	0b000100000,
	ARMOR_LEGGINGS	=	0b001000000,
	ARMOR_SHOES		=	0b010000000,
	ARMOR_SHIELD		=	0b100000000,
} armorSlots;

// if adding a new weapon class, be sure to update isWeapon() in itemmgmt.c so it catches it
// and isArmor() if armor, etc.
typedef enum itemClassId{
	ITEM_TYPE_LONGSWORD,
	ITEM_TYPE_CORPSE,
	ITEM_TYPE_AXE,
	ITEM_TYPE_DAGGER,
	ITEM_TYPE_SHIRT,
	ITEM_TYPE_UNDERARMOR,
	ITEM_TYPE_ARMOR,
	ITEM_TYPE_HELMET,
	ITEM_TYPE_CLOAK,
	ITEM_TYPE_GLOVES,
	ITEM_TYPE_LEGGINGS,
	ITEM_TYPE_SHOES,
	ITEM_TYPE_SHIELD,
	ITEM_TYPE_FRUIT,
	ITEM_TYPE_SEED,
	ITEM_TYPE_MAX
} itemClassId;

typedef struct uniqueDataShield{
	int i;
} uniqueDataShield;

typedef enum shieldSubClassId{
	ITEM_SHIELD_WOOD,
	ITEM_SHIELD_STEEL,
	ITEM_SHIELD_SILVER,
	ITEM_SHIELD_MAX
} shieldSubClassId;

typedef struct uniqueDataUnderarmor{
	int i;
} uniqueDataUnderarmor;

typedef enum underarmorSubClassId{
	ITEM_UNDERARMOR_CHAINMAIL,
	ITEM_UNDERARMOR_MAX
} underarmorSubClassId;

typedef struct uniqueDataShirt{
	int i;
} uniqueDataShirt;

typedef enum shirtSubClassId{
	ITEM_SHIRT_TSHIRT,
	ITEM_SHIRT_HAWAIIAN,
	ITEM_SHIRT_MAX
} shirtSubClassId;

typedef struct uniqueDataLongsword{
	int i;
} uniqueDataLongsword;

typedef enum longswordSubClassId{
	ITEM_LONGSWORD_STEEL,
	ITEM_LONGSWORD_SILVER,
	ITEM_LONGSWORD_MAX
} longswordSubClassId;

typedef struct uniqueDataAxe{
	int i;
} uniqueDataAxe;

typedef enum axeSubClassId{
	ITEM_AXE_THROWING,
	ITEM_AXE_BATTLE,
	ITEM_AXE_MAX
} axeSubClassId;

typedef struct uniqueDataDagger{
	int i;
} uniqueDataDagger;

typedef enum daggerSubClassId{
	ITEM_DAGGER_STILETTO,
	ITEM_DAGGER_BASELARD,
	ITEM_DAGGER_MAX
} daggerSubClassId;

typedef struct uniqueDataCorpse{
	unsigned int nutrition;
} uniqueDataCorpse;

typedef enum corpseSubClassId{
	ITEM_CORPSE_HUMAN,
	ITEM_CORPSE_HALFLING,
	ITEM_CORPSE_ELF,
	ITEM_CORPSE_DWARF,
	ITEM_CORPSE_BEAR,
	ITEM_CORPSE_MAX
} corpseSubClassId;

typedef struct uniqueDataFruit{
	unsigned int nutrition;
} uniqueDataFruit;

/* A lot of functions assume that a given enum value in seedSubClassId will correspond to the correct
 * value in fruitSubClassId, so to be safe, (a) always add a fruit and its seed subclass id together and
 * (b) make sure they are in the same order
 */

typedef enum fruitSubClassId{
	ITEM_FRUIT_BLUEBERRY,
	ITEM_FRUIT_BLACKBERRY,
	ITEM_FRUIT_STRAWBERRY,
	ITEM_FRUIT_RASPBERRY,
	ITEM_FRUIT_MAX
} fruitSubClassId;

typedef struct uniqueDataSeed{
	unsigned int dormancy;
	unsigned int rest;
} uniqueDataSeed;

typedef enum seedSubClassId{
	ITEM_SEED_BLUEBERRY,
	ITEM_SEED_BLACKBERRY,
	ITEM_SEED_STRAWBERRY,
	ITEM_SEED_RASPBERRY,
	ITEM_SEED_MAX
} seedSubClassId;

typedef struct itemType{
	char *itemName;
	unsigned int baseDamage;
	unsigned int baseToHit;
	unsigned int baseArmor;
	unsigned int weight;
	bool throwable;
	bool twoHandedWield;
	bool fragile;
	armorSlots possibleSlots;
	union {
		uniqueDataLongsword longswordUniqueData;
		uniqueDataCorpse corpseUniqueData;
		uniqueDataAxe axeUniqueData;
		uniqueDataDagger daggerUniqueData;
		uniqueDataShirt shirtUniqueData;
		uniqueDataUnderarmor underarmorUniqueData;
		uniqueDataShield shieldUniqueData;
		uniqueDataFruit fruitUniqueData;
		uniqueDataSeed seedUniqueData;
	};
	colorPairs color;
	char dispChar;
	unsigned int attrs;
} itemType;

typedef struct item{
	itemClassId itemClass;
	union {
		longswordSubClassId longswordSubClass;
		corpseSubClassId corpseSubClass;
		axeSubClassId axeSubClass;
		daggerSubClassId daggerSubClass;
		shirtSubClassId shirtSubClass;
		underarmorSubClassId underarmorSubClass;
		shieldSubClassId shieldSubClass;
		fruitSubClassId fruitSubClass;
		seedSubClassId seedSubClass;
	};
	itemType itemData;
	int damageModifier;
	int toHitModifier;
	int armorModifier;
	int weightModifier;
	char *name;
	bool owned;
	struct creature *owner;
	bool wielded;
	bool worn;
	coord3D location;	// only trust if owned = FALSE
} item;

/*typedef struct itemList itemList;
 * 
 t ypede*f struct itemList{
 itemList *prev;
 item *item;
 itemList *next;
 } itemList;*/

#endif