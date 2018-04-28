/*  This file is part of Lavender Throne.
 *  Copyright 2017 by Kurt Weber
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

#ifndef _TARGETING_H
#define _TARGETING_H

#include "creature.h"

typedef struct positionList{
	creature *creature;
	coord3D location;
} positionList;

#ifndef _TARGETING_C
void findTargets();
creature *getCreatureTarget(creature *creature);
void setCreatureTarget(struct creature *creature, struct creature *target);

extern const unsigned int targetRangeLimit;
#else
void findClosestEnemiesLevel(positionList *positions);
creature *findClosestEnemyLevel(creature *ref, positionList *positions);
positionList **generatePositionList();
void setCreatureTarget(struct creature *creature, struct creature *target);

const unsigned int targetRangeLimit = 7;
#endif

#endif