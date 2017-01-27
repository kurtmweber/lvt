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
  ITEM_TYPE_MAX
} itemClassId;

typedef struct uniqueDataLongsword{
  int i;
} uniqueDataLongsword;

typedef enum longswordSubClassId{
  ITEM_LONGSWORD_STEEL,
  ITEM_LONGSWORD_SILVER,
  ITEM_LONGSWORD_MAX
} longswordSubClassId;

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
  union {
    uniqueDataLongsword longswordUniqueData;
    uniqueDataCorpse corpseUniqueData;
  };
  colorPairs color;
  char dispChar;
} itemType;

typedef struct item{
  itemClassId itemClass;
  union {
    longswordSubClassId longswordSubClass;
    corpseSubClassId corpseSubClass;
  };
  itemType itemData;
  int damageModifier;
  int toHitModifier;
  int armorModifier;
  int weightModifier;
  char *name;
  armorSlots possibleSlots;
  bool owned;
  bool wielded;
  coord3D location;
} item;

typedef struct itemList itemList;

typedef struct itemList{
  itemList *prev;
  item *item;
  itemList *next;
} itemList;

#endif