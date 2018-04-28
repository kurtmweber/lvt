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

#define _CREATURELIST_C

#include "lvt.h"

#include "creature.h"

#include"creaturelist.h"

creatureList *findCreatureListEntry(creatureList *list, creature *creature){
	if (!list){
		return 0;
	}
	
	do {
		if (list->creature == creature){
			return list;
		}
		
		list = list->next;
	} while(list);
	
	return 0;
}

creatureList *insertNewCreatureNode(creatureList *list, creatureList *node){
	if (list){
		list->prev = node;
		node->next = list;
		node->prev = 0;
	} else {
		node->next = 0;
		node->prev = 0;
	}
	
	//node->next = list;
	
	return node;
}

creatureList *removeCreatureNode(creatureList *list, creatureList *node){
	creatureList *prev;
	creatureList *next;
	
	if (!node){
		return 0;
	}
	
	if (!list){
		return 0;
	}
	
	if (list == node){
		list = node->next;
		if (list){
			list->prev = 0;
		}
	} else {
		prev = node->prev;
		next = node->next;
		if (prev){
			prev->next = next;
		}
		if (next){
			next->prev = prev;
		}
	}
	
	return list;
}