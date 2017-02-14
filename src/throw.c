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

#define _THROW_C

#include <ctype.h>
#include <math.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include "lvt.h"
#include "move.h"

void throwObject(creature *creature, moveDirection dir, item *item){
  unsigned int weight;
  statList stats;
  unsigned int strength;
  unsigned int distance;
  moveMatrix move;
  coord3D pos;
  mapSpaceContents *contents;
  mapSpaceContents *thisContent;
  
  weight = getItemWeight(item);
  getCreatureCurStats(creature, &stats);
  strength = stats.strength;
  
  distance = (unsigned int)floor(strength / weight);
  
  if (distance == 0){
    addToMsgQueue("You are not strong enough to throw that!", true);
    return;
  }
  
  directionToUnitMatrix(dir, &move);
  pos = getCreatureLocation(creature);
  
  removeCreatureInventoryItem(creature, item);
  addContents(dungeon[pos.level], pos.x, pos.y, item);
  
  while (distance){
    distance--;
    
    calcRicochetDirection(pos, &move);
    
    contents = getContents(dungeon[pos.level], pos.x, pos.y);
    dungeon[pos.level][pos.x][pos.y].contents = 0;
    do {
      thisContent = contents;
      if (thisContent->item != item){
	addContents(dungeon[pos.level], pos.x, pos.y, thisContent->item);
      }
      contents = thisContent->next;
      free(thisContent);
    } while (contents);
    
    pos.x += move.x;
    pos.y += move.y;
    
    addContents(dungeon[pos.level], pos.x, pos.y, item);
    displayLevel(dungeon[pos.level]);
    
    usleep(250000);
    
    
    /*if (hasCreatureOccupant(pos.level, pos.x, pos.y)){
      switch(throwAttack(creature, getCreatureOccupant(pos.x, pos.y), item){
	case ATTACK_MISSED:
	  addToMsgQueue(ATTACK_MISSED_MSG, false);
	  break;
	case ATTACK_NODAMAGE:
	  addToMsgQueue(ATTACK_NODAMAGE_MSG, false);
	  break;
	case ATTACK_SUCCEEDED:
	  addToMsgQueue(ATTACK_SUCCEEDED_MSG, false);
	  break;
	case ATTACK_KILLED:
	  addToMsgQueue(ATTACK_KILLED_MSG, false);
	default:
	  break;
      }
    } */
  }
  
  return;
}

void calcRicochetDirection(coord3D pos, moveMatrix *move){
  coord2D newPos;
  moveMatrix old;
  
  old.x = move->x;
  old.y = move->y;
  
  switch(getMapSpaceTerrain(dungeon[pos.level], pos.x + move->x, pos.y + move->y)){
    case WALL:
    case PERMANENTROCK:
    case DOOR:
    case HIDDENDOOR:
      break;
    default:
      return;
  }

  switch(getMapSpaceTerrain(dungeon[pos.level], pos.x - old.x, pos.y + old.y)){
    case WALL:
    case PERMANENTROCK:
    case DOOR:
    case HIDDENDOOR:
      // if changing the x doesn't fix it, then we need to invert the y
      move->y = -(move->y);
      break;
    default:
      break;
  }
  
  switch(getMapSpaceTerrain(dungeon[pos.level], pos.x + old.x, pos.y - old.y)){
    case WALL:
    case PERMANENTROCK:
    case DOOR:
    case HIDDENDOOR:
      // and if changing the y doesn't fix it, then we need to invert the x
      // we don't make this an either-or since there are times we may need to change both
      // e.g. when hitting a corner, we need to reverse direction completely
      move->x = -(move->x);
      break;
    default:
      break;
  }
  
  return;
}

void doThrow(){
  unsigned int c = 1;
  unsigned int i = 0;
  bool checked[52];
  unsigned int j = 0;
  item *inventory[52];
  
  item *thrownItem;
  moveDirection dir;
  
  for (j = 0; j < 52; j++){
    checked[j] = false;
  }
  
  getCreatureInventory(&player, inventory);
  
  addToMsgQueue("Throw which item? (space to cancel)", false);
  procMsgQueue();
  
  while (c){
    displayInventoryWindow(i, checked);
    c = getch();
    switch (c){
      case KEY_UP:
	i == 0 ? : i--;
	break;
      case KEY_DOWN:
	i == 51 ? : i++;
	break;
      case ' ':
	freeAction = true;
	return;
      default:
	if (isupper(c) || islower(c)){
	  if (isInventoryLetter(c)){
	    thrownItem = inventory[inventoryLetterToIndex(c)];
	    c = 0;	// causes us to exit the while loop
	    break;
	  } else {
	    break;
	  }
	} else {
	  break;
	}
    }
    
    delwin(invWin);
  }
  
  refreshPlayArea();
  
  addToMsgQueue("Which direction? (space to cancel)", false);
  procMsgQueue();
  
  c = 1;
  
  while (c){
    c = getch();
    switch (c){
      case KEY_UP:
	dir = UP;
	c = 0;
	break;
      case KEY_DOWN:
	dir = DOWN;
	c = 0;
	break;
      case KEY_RIGHT:
	dir = RIGHT;
	c = 0;
	break;
      case KEY_LEFT:
	dir = LEFT;
	c = 0;
	break;
      case KEY_UPRIGHT:
	dir = UPRIGHT;
	c = 0;
	break;
      case KEY_UPLEFT:
	dir = UPLEFT;
	c = 0;
	break;
      case KEY_DOWNRIGHT:
	dir = DOWNRIGHT;
	c = 0;
	break;
      case KEY_DOWNLEFT:
	dir = DOWNLEFT;
	c = 0;
	break;
      case ' ':
	freeAction = true;
	return;
      default:
	break;
    }
  }
  
  throwObject(&player, dir, thrownItem);
  
  return;
}