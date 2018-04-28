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

#define _CREATUREMOVE_C

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "lvt.h"

#include "creaturemove.h"

#include "attack.h"
#include "creatureeat.h"
#include "creatureinventory.h"
#include "creaturemgmt.h"
#include "messages.h"
#include "targeting.h"

const unsigned int straightMoveChance = 900;	// Likelihood (out of 1000) that a creature will, if
// possible, continue moving in a straight line

void changeCreatureLocation(creature *creature, coord3D newPos){
	coord3D curPos;
	
	curPos = getCreatureLocation(creature);
	
	if (hasPlantOccupant(dungeon[curPos.level], newPos.x, newPos.y)){
		tramplePlant(getPlantOccupant(dungeon[curPos.level], newPos.x, newPos.y), creature);
	}
	
	clearCreatureOccupant(dungeon[curPos.level], curPos.x, curPos.y);
	setCreatureOccupant(dungeon[newPos.level], newPos.x, newPos.y, creature);
	setCreatureLocation(creature, newPos);
	
	return;
}

creature *doMoveCreature(creature *creature){
	coord3D moves[9];
	coord3D curCreatureLoc;
	static rng localRng;
	static bool rngInitd = false;
	unsigned int location;
	unsigned int lastMove;
	terrain t;
	struct creature *target;
	moveDirection attackMove;
	coord3D cLoc3, tLoc3;
	coord2D cLoc2, tLoc2;
	unsigned int attackVal = 0;
	char *attackMsg = NULL;
	
	if (!rngInitd){
		initializeRNG(&localRng);
		rngInitd = true;
	}
	
	curCreatureLoc = getCreatureLocation(creature);
	
	t = getMapSpaceTerrain(dungeon[curCreatureLoc.level], curCreatureLoc.x, curCreatureLoc.y);
	
	if ((t == UPSTAIR) && (curCreatureLoc.level != 0)){
		if (coinFlip(&localRng) == HEADS){
			moveCreatureUpStair(creature);
			setCreatureLastMove(creature, 4);
			return NULL;
		}
	} else if ((t == DOWNSTAIR) && (curCreatureLoc.level != numLevels - 1)){
		if (coinFlip(&localRng) == TAILS){
			moveCreatureDownStair(creature);
			setCreatureLastMove(creature, 4);
			return NULL;
		}
	}
	
	{
		moves[0].x = MAX(curCreatureLoc.x - 1, 0);
		moves[0].y = MAX(curCreatureLoc.y - 1, 0);
		moves[0].level = curCreatureLoc.level;
		
		moves[1].x = MAX(curCreatureLoc.x - 1, 0);
		moves[1].y = curCreatureLoc.y;
		moves[1].level = curCreatureLoc.level;
		
		moves[2].x = MAX(curCreatureLoc.x - 1, 0);
		moves[2].y = MIN(curCreatureLoc.y + 1, dimMapY - 1);
		moves[2].level = curCreatureLoc.level;
		
		moves[3].x = curCreatureLoc.x;
		moves[3].y = MAX(curCreatureLoc.y - 1, 0);
		moves[3].level = curCreatureLoc.level;
		
		moves[4].x = curCreatureLoc.x;
		moves[4].y = curCreatureLoc.y;
		moves[4].level = curCreatureLoc.level;
		
		moves[5].x = curCreatureLoc.x;
		moves[5].y = MIN(curCreatureLoc.y + 1, dimMapY - 1);
		moves[5].level = curCreatureLoc.level;
		
		moves[6].x = MIN(curCreatureLoc.x + 1, dimMapX - 1);
		moves[6].y = MAX(curCreatureLoc.y - 1, 0);
		moves[6].level = curCreatureLoc.level;
		
		moves[7].x = MIN(curCreatureLoc.x + 1, dimMapX - 1);
		moves[7].y = curCreatureLoc.y;
		moves[7].level = curCreatureLoc.level;
		
		moves[8].x = MIN(curCreatureLoc.x + 1, dimMapX - 1);
		moves[8].y = MIN(curCreatureLoc.y + 1, dimMapY - 1);
		moves[8].level = curCreatureLoc.level;
	}
	
	target = getCreatureTarget(creature);
	
	if (target && (isAggressive(creature, getCreatureTarget(creature)) || getInCombat(creature))){
		cLoc3 = getCreatureLocation(creature);
		tLoc3 = getCreatureLocation(getCreatureTarget(creature));
		cLoc2.x = cLoc3.x;
		cLoc2.y = cLoc3.y;
		tLoc2.x = tLoc3.x;
		tLoc2.y = tLoc3.y;
		
		location = findDirection(cLoc2, tLoc2);
		setCreatureLastMove(creature, location);
	} else {
		
		lastMove = getCreatureLastMove(creature);
		
		if ((uniformRandomRangeInt(&localRng, 1, 1000) <= straightMoveChance) && (lastMove != 4)){
			// 4 is the "stay put" move in the array above
			location = lastMove;
		} else {
			location = uniformRandomRangeInt(&localRng, 1, 9) - 1;
			setCreatureLastMove(creature, location);
		}
	}
	
	switch (getMapSpaceTerrain(dungeon[moves[location].level], moves[location].x, moves[location].y)){
		case FLOOR:
		case UPSTAIR:
		case DOWNSTAIR:
		case OPENDOOR:
			if (!hasCreatureOccupant(dungeon[moves[location].level], moves[location].x, moves[location].y)){
				changeCreatureLocation(creature, moves[location]);
				return NULL;
			} else {
				target = getCreatureOccupant(dungeon[moves[location].level], moves[location].x, moves[location].y);
				if (getCreatureFaction(creature) != getCreatureFaction(target)){
					attackVal = meleeAttack(creature, target);
					if (target == &player){
						switch (attackVal){
							case ATTACK_MISSED:
							case ATTACK_NODAMAGE:
								attackMsg = calloc(MSGLEN(ATTACKED_BY_FAILED_MSG) + strlen(getCreatureName(creature)) + 1, sizeof(char));
								sprintf(attackMsg, ATTACKED_BY_FAILED_MSG, getCreatureName(creature));
								break;
							case ATTACK_SUCCEEDED:
								attackMsg = calloc(MSGLEN(ATTACKED_BY_MSG) + strlen(getCreatureName(creature)) + 1, sizeof(char));
								sprintf(attackMsg, ATTACKED_BY_MSG, getCreatureName(creature));
								break;
							case ATTACK_KILLED:
								attackMsg = calloc(MSGLEN(KILLED_BY_MSG) + strlen(getCreatureName(creature)) + 1, sizeof(char));
								sprintf(attackMsg, KILLED_BY_MSG, getCreatureName(creature));
								break;
							default:
								break;     
						}
						addToMsgQueue(attackMsg, true);
						free(attackMsg);
					}
					if (attackVal == ATTACK_KILLED){
						killCreature(target);
						return target;
					}
				} else {
					setCreatureLastMove(creature, 4);
				}
			}
			break;
							case DOOR:
								if (speciesData[getCreatureSpecies(creature)].hasHands){
									setMapSpaceTerrain(dungeon[moves[location].level], moves[location].x, moves[location].y, OPENDOOR);
								}
								break;
							default:
								setCreatureLastMove(creature, 4);
								//doMoveCreature(creature);
								break;    
	}
	
	return NULL;
}

bool hasAction(creature *creature){
	unsigned int creatureSpeedCounter;
	
	creatureSpeedCounter = getCreatureSpeedCounter(creature);
	
	if (creatureSpeedCounter >= status.playerSpeed){
		decrementCreatureSpeedCounter(creature, status.playerSpeed);
		return true;
	} else {
		return false;
	}
}

void moveCreatureDownStair(creature *creature){
	coord3D newPos;
	coord3D curPos;
	coord2D stairPos;
	
	curPos = getCreatureLocation(creature);
	
	newPos.level = curPos.level + 1;
	
	stairPos = findLevelUpstair(dungeon[newPos.level]);
	newPos.x = stairPos.x;
	newPos.y = stairPos.y;
	
	if (!hasCreatureOccupant(dungeon[newPos.level], stairPos.x, stairPos.y)){
		changeCreatureLocation(creature, newPos);
	}
	
	return;  
}

void moveCreatures(){
	creatureList *curCreatureNode;
	creatureList *contingentJumpNext = NULL;
	creature *curCreature;
	creature *contingentCreatureComp = NULL;
	creature *killedCreature = NULL;
	unsigned long long i;
	char numCreatures[32];
	
	findTargets();
	
	curCreatureNode = creatures;
	
	if (!curCreatureNode){
		return;
	}
	
	do {
		curCreature = curCreatureNode->creature;
		// if this creature kills another creature this turn, and it by chance is the next creature in the list,
		// then its creature struct and node will have been destroyed and so a reference to curCreatureNode->
		// next would be a Very Bad Idea.  So in case we do, we save the pointer to the creature AFTER the next
		// one, and if the return value from doMoveCreature equals the address of the current next creature,
		// we skip over it.
		// The need to do this is an example of very poor planning and lack of foresight on my part.  The day
		// will come when I feel embarrassed enough to fix that, but it is not this day.
		
		// if curCreatureNode->next is null, then we're the last creature in the list, and so killing the
		// subsequent creature isn't an issue
		if (curCreatureNode->next){
			contingentJumpNext = curCreatureNode->next->next;
			contingentCreatureComp = curCreatureNode->next->creature;
		}
		incrementCreatureSpeedCounter(curCreature, getCreatureSpeed(curCreature));
		while (hasAction(curCreature)){
			if (hungerAction(curCreature)){
				continue;
			}
			
			if (inventoryAction(curCreature)){
				continue;
			}
			
			killedCreature = doMoveCreature(curCreature);
		}
		
		// we have to do this before we update the life cycle, because if the creature dies as a result of
		// the update, the current node in the creature list is destroyed.
		if ((killedCreature == contingentCreatureComp) && (contingentJumpNext)){
			curCreatureNode = contingentJumpNext;
		} else {
			curCreatureNode = curCreatureNode->next;
		}
		
	} while (curCreatureNode);
	
	return;
}

void moveCreatureUpStair(creature *creature){
	coord3D newPos;
	coord3D curPos;
	coord2D stairPos;
	
	curPos = getCreatureLocation(creature);
	
	newPos.level = curPos.level - 1;
	
	stairPos = findLevelDownstair(dungeon[newPos.level]);
	newPos.x = stairPos.x;
	newPos.y = stairPos.y;
	
	if (!hasCreatureOccupant(dungeon[newPos.level], stairPos.x, stairPos.y)){
		changeCreatureLocation(creature, newPos);
	}
	
	return;  
}