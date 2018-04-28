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

#define _TARGETING_C

#include <stdlib.h>

#include "lvt.h"


#include "targeting.h"

#include "creature.h"
#include "creaturemgmt.h"
#include "levelgen.h"

void findClosestEnemiesLevel(positionList *positions){
	unsigned int i = 0;
	creature *closestEnemy;
	
	while (positions[i].creature){
		closestEnemy = findClosestEnemyLevel(positions[i].creature, positions);
		setCreatureTarget(positions[i].creature, closestEnemy);
		i++;
	}
}

creature *findClosestEnemyLevel(creature *ref, positionList *positions){
	unsigned int i = 0;
	creature *curClosest = NULL;
	struct coord2D refCoords, tgtCoords;
	unsigned int distSquared = 0;
	// initialize shortestDistSquared to a value bigger than what is possible on the current map,
	// so that when we check any real value found will be less than it
	unsigned int shortestDistSquared = (dimMapX * dimMapY) + 1;    // in a 100x100 map, biggest should
	unsigned int maxRangeSquared = targetRangeLimit * targetRangeLimit;
	
	refCoords.x = ref->location.x;
	refCoords.y = ref->location.y;
	
	while (positions[i].creature){
		if (positions[i].creature != ref){
			tgtCoords.x = positions[i].creature->location.x;
			tgtCoords.y = positions[i].creature->location.y;
			distSquared = getDistanceSquared2D(refCoords, tgtCoords);
			// no need to complete the distance formula with an expensive sqrt() since we only care about
			// relative distance, and absolute distance only matters to the extent that it's less than 7 (which
			// we can leave squared by comparing to 7*7=49)
			if ((distSquared < shortestDistSquared) && (distSquared <= 49) && (getCreatureFaction(ref) != getCreatureFaction(positions[i].creature))){
				shortestDistSquared = distSquared;
				curClosest = positions[i].creature;
			}
		}
		i++;
	}
	
	return curClosest;
}

void findTargets(){
	positionList **positionList;
	unsigned int i;
	
	positionList = generatePositionList();
	
	for (i = 0; i < 100; i++){
		findClosestEnemiesLevel(positionList[i]);
	}
	
	return;
}

positionList **generatePositionList(){
	creatureList *curCreatureNode;
	creature *curCreature;
	
	positionList **posList = NULL;
	unsigned int numCreatures[100] = {0};
	unsigned int level;
	unsigned int i = 0;
	unsigned int playerLevel;
	
	curCreatureNode = creatures;
	if (!curCreatureNode){
		return NULL;
	}
	
	posList = malloc(sizeof(positionList *) * 100);
	
	for (i = 0; i < 100; i++){
		posList[i] = NULL;
	}
	
	do {
		curCreature = curCreatureNode->creature;
		
		level = curCreature->location.level;
		
		numCreatures[level]++;
		posList[level] = realloc(posList[level], numCreatures[level] * sizeof(positionList));
		posList[level][numCreatures[level] - 1].creature = curCreature;
		posList[level][numCreatures[level] - 1].location = curCreature->location;
		
		curCreatureNode = curCreatureNode->next;
	} while (curCreatureNode);
	
	// since the creature list doesn't include the player, we've got to add that separately
	playerLevel = player.location.level;
	numCreatures[playerLevel]++;
	posList[playerLevel] = realloc(posList[playerLevel], numCreatures[playerLevel] * sizeof(positionList));
	posList[playerLevel][numCreatures[playerLevel] - 1].creature = &player;
	posList[playerLevel][numCreatures[playerLevel] - 1].location = player.location;
	
	
	for (i = 0; i < 100; i++){
		posList[i] = realloc(posList[i], (numCreatures[i] + 1) * sizeof(positionList));
		posList[i][numCreatures[i]].creature = NULL;
	}
	
	return posList;
}

creature *getCreatureTarget(creature *creature){
	return creature->currentTarget;
}

void setCreatureTarget(struct creature *creature, struct creature *target){
	creature->currentTarget = target;
	
	return;
}