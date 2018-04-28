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

#ifndef _PLANT_H
#define _PLANT_H

#include "species.h"
#include "types.h"

typedef struct plant{
	plantClass plantClass;
	plantSpecies species;
	unsigned int curToughness;
	unsigned int maxToughness;
	unsigned int curGrowth;
	unsigned int maxGrowth;
	unsigned int curProduction;
	unsigned int maxProduction;
	unsigned int growthRate;
	unsigned int productionTime;
	unsigned int productionProgress;
	char dispChar;
	colorPairs dispColor;
	unsigned int attrs;
	coord3D location;
} plant;

typedef struct plantList{
	struct plantList *next;
	plant *plant;
	struct plantList *prev;
} plantList;

typedef struct seedList{
	struct seedList *next;
	item *seed;
	struct seedList *prev;
} seedList;

#endif