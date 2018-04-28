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

#ifndef _LEVEL_H
#define _LEVEL_H

#include "creature.h"
#include "item.h"
#include "plant.h"

typedef enum terrain{
	WALL,
	PERMANENTROCK,
	FLOOR,
	DOOR,
	HIDDENDOOR,
	OPENDOOR,
	UPSTAIR,
	DOWNSTAIR,
	DOWNTON,
	ABBEY,
	THRONE
} terrain;

/*typedef enum objectClasses{
 W EAP*ON
 } objectClasses; */

typedef struct mapSpaceContents mapSpaceContents;

struct mapSpaceContents{
	mapSpaceContents *prev;
	item *item;
	mapSpaceContents *next;
};


typedef struct mapSpace{
	terrain terrain;
	union {
		unsigned int searchCountdown;
	} terrainData;
	bool explored;
	mapSpaceContents *contents;
	creature *creatureOccupant;
	plant *plantOccupant;
	//void *plantOccupant;
} mapSpace;

#ifndef _MAP_TYPE
#define _MAP_TYPE
typedef mapSpace **level;
typedef level *map;
#endif

#endif