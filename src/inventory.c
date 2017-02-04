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

#define _INVENTORY_C

#include <ctype.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "lvt.h"
#include "messages.h"

WINDOW *invWin;

void doInventory(){
  unsigned int i = 0;
  unsigned int j = 0;
  bool checked[52];
  unsigned int c = 0;
  
  freeAction = true;
  
  for (j = 0; j < 52; j++){
    checked[j] = false;
  }
  
  addToMsgQueue("(press space to continue)", false);
  procMsgQueue();
  
  while (c != ' '){
    displayInventoryWindow(i, checked);
    c = getch();
    switch (c){
      case KEY_UP:
	i == 0 ? : i--;
	break;
      case KEY_DOWN:
	i == 51 ? : i++;
	break;
      default:
	break;
    }
    
    delwin(invWin);
  }
  
  return;
}

void displayInventoryWindow(unsigned int i, bool checked[52]){
  item *inventory[52];
  unsigned int j;
  char invLetter;
  unsigned int k;
  bool hasInventory = false;
  
  for (k = 0; k < 52; k++){
    inventory[k] = 0;
  }
  
  getCreatureInventory(&player, inventory);
  
  invWin = newwin(13, 84, 1, 0);
  
  for (j = i; j < (i + 13); j++){
    if (inventory[j]){
      hasInventory = true;
      invLetter = inventoryIndexToLetter(j);
      waddch(invWin, '(');
      waddch(invWin, invLetter);
      waddch(invWin, ')');
      waddch(invWin, ' ');
      waddstr(invWin, inventory[j]->itemData.itemName);
      if (inventory[j]->name){
	waddstr(invWin, " named ");
	waddstr(invWin, inventory[j]->name);
      }
      if (inventory[j]->wielded){
	waddstr(invWin, " (wielded)");
      }
      waddch(invWin, '\n');
    }
  }
  
  if (!hasInventory){
    waddstr(invWin, "You have no inventory to display");
  }
  
  wrefresh(invWin);
  return;
}

void doWield(){
  unsigned int c = 1;
  unsigned int i = 0;
  bool checked[52];
  unsigned int j = 0;
  char *itemName = 0;
  item *inventory[52];
  
  for (j = 0; j < 52; j++){
    checked[j] = false;
  }
  
  getCreatureInventory(&player, inventory);
  
  addToMsgQueue("Wield which item? (space to cancel)", false);
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
	return;
      default:
	if (isupper(c) || islower(c)){
	  if (isInventoryLetter(c)){
	    wieldItem(&player, inventory[inventoryLetterToIndex(c)]);
	    return;
	  } else {
	    break;
	  }
	} else {
	  break;
	}
    }
    
    delwin(invWin);
  }
  
  return;
}

void doUnwield(){
  unwieldWeapon(&player);
  
  addToMsgQueue("You are no longer wielding a weapon", false);
  
  return;
}

void doNameItem(){
  unsigned int c = 1;
  unsigned int i = 0;
  bool checked[52];
  unsigned int j = 0;
  char *itemName = 0;
  item *inventory[52];
  
  freeAction = true;
  
  for (j = 0; j < 52; j++){
    checked[j] = false;
  }
  
  getCreatureInventory(&player, inventory);
  
  addToMsgQueue("Name or rename which item? (space to cancel)", false);
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
	return;
      default:
	if (isupper(c) || islower(c)){
	  if (isInventoryLetter(c)){
	    itemName = getLineInput("What do you wish to name this item?");
	    setItemName(inventory[inventoryLetterToIndex(c)], itemName);
	    return;
	  } else {
	    break;
	  }
	} else {
	  break;
	}
    }
    
    delwin(invWin);
  }
  
  return;
}

void doUnNameItem(){
  unsigned int c = 1;
  unsigned int i = 0;
  bool checked[52];
  unsigned int j = 0;
  char *itemName = 0;
  item *inventory[52];
  
  freeAction = true;
  
  for (j = 0; j < 52; j++){
    checked[j] = false;
  }
  
  getCreatureInventory(&player, inventory);
  
  addToMsgQueue("Unname which item? (space to cancel)", false);
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
	return;
      default:
	if (isupper(c) || islower(c)){
	  if (isInventoryLetter(c)){
	    removeItemName(inventory[inventoryLetterToIndex(c)]);
	    return;
	  } else {
	    break;
	  }
	} else {
	  break;
	}
    }
    
    delwin(invWin);
  }
  
  return;
}

void doDrop(){
  unsigned int c = 1;
  unsigned int i = 0;
  bool checked[52];
  unsigned int j = 0;
  item *inventory[52];
  coord3D creaturePos;
  item *chosenItem;
  
  for (j = 0; j < 52; j++){
    checked[j] = false;
  }
  
  getCreatureInventory(&player, inventory);
  
  addToMsgQueue("Drop which item? (space to cancel)", false);
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
	return;
      default:
	if (isupper(c) || islower(c)){
	  if (isInventoryLetter(c)){
	    chosenItem = inventory[inventoryLetterToIndex(c)];
	    removeCreatureInventoryItem(&player, chosenItem);
	    creaturePos = getCreatureLocation(&player);
	    addContents(dungeon[creaturePos.level], creaturePos.x, creaturePos.y, chosenItem);
	    return;
	  } else {
	    break;
	  }
	} else {
	  break;
	}
    }
    
    delwin(invWin);
  }
  
  return;
}

void doPickup(){
  coord3D curLoc;
  mapSpaceContents *contents;
  mapSpaceContents *thisContent;
  item *thisItem;
  char *pickupMsg = 0;
  char c = 0;
  char label = 0;
  
  curLoc = getCreatureLocation(&player);
  
  contents = getContents(dungeon[curLoc.level], curLoc.x, curLoc.y);
  
  // the easiest way to deal with the problem of some items being picked up and some being left behind
  // seems to be to clear out the list and then replace those that are left behind.  We don't free()
  // the list because we still need to process the contents, but we set the pointer to 0 so we can
  // start from scratch when we re-add them.
  dungeon[curLoc.level][curLoc.x][curLoc.y].contents = 0;
  
  if (!contents){
    addToMsgQueue(NOTHING_THERE_MSG, false);
    
    return;
  }
  
  do {
    thisContent = contents;
    
    thisItem = thisContent->item;
    if (thisItem->name){
      pickupMsg = calloc(10 + strlen(thisItem->itemData.itemName) + 7 + strlen(thisItem->name) + 2, sizeof(char));
      strcat(pickupMsg, "Pick up a ");
      strcat(pickupMsg, thisItem->itemData.itemName);
      strcat(pickupMsg, " named ");
      strcat(pickupMsg, thisItem->name);
      strcat(pickupMsg, "?");
    } else {
      pickupMsg = calloc(10 + strlen(thisItem->itemData.itemName) + 2, sizeof(char));
      strcat(pickupMsg, "Pick up a ");
      strcat(pickupMsg, thisItem->itemData.itemName);
      strcat(pickupMsg, "?");
    }
    
    displayQuestionYesNo(pickupMsg);
    
    while ((c != 'y') && (c != 'n')){
      c = getch();
    }
    
    contents = thisContent->next;
    
    if (c == 'y'){
      label = addCreatureInventoryItem(&player, thisItem);
      
      if (!label){	// inventory table is full
	addToMsgQueue(INVENTORY_FULL_MSG, false);
	addContents(dungeon[curLoc.level], curLoc.x, curLoc.y, thisItem);
	free(thisContent);
	return;
      }
      
      free(pickupMsg);
      pickupMsg = 0;
      pickupMsg = calloc(4 + strlen(thisItem->itemData.itemName) + 1, sizeof(char));
      sprintf(pickupMsg, "(%c) %s", label, thisItem->itemData.itemName);
      if (thisItem->name){
	pickupMsg = realloc(pickupMsg, (strlen(pickupMsg) + 7 + strlen(thisItem->name) + 1) * sizeof(char));
	strcat(pickupMsg, " named ");
	strcat(pickupMsg, thisItem->name);
      } 
      addToMsgQueue(pickupMsg, true);
    } else {
      addContents(dungeon[curLoc.level], curLoc.x, curLoc.y, thisItem);
    }
    
    contents = thisContent->next;
    
    free(thisContent);
    
    c = 0;
  } while (contents);
  
  return;
}