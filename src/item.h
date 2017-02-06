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
  ITEM_TYPE_MAX
} itemClassId;

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
  };
  itemType itemData;
  int damageModifier;
  int toHitModifier;
  int armorModifier;
  int weightModifier;
  char *name;
  bool owned;
  bool wielded;
  bool worn;
  coord3D location;
} item;

typedef struct itemList itemList;

typedef struct itemList{
  itemList *prev;
  item *item;
  itemList *next;
} itemList;

#endif