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

typedef enum itemTypeId{
  ITEM_TYPE_LONGSWORDSTEEL,
} itemTypeId;

typedef struct item{
  itemTypeId type;
  armorSlots possibleSlots;
  bool owned;
} item;

#endif