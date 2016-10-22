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

#define _MESSAGES_C

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "lvt.h"
#include "types.h"

msgQueueEntry *msgQueue = 0;
unsigned int numMsgQueueEntries = 0;

void addToMsgQueue(char *msg, bool confirm){
  msgQueue = realloc(msgQueue, sizeof(msgQueueEntry) * (numMsgQueueEntries + 2));
  
  msgQueue[numMsgQueueEntries].msg = calloc(sizeof(char), strlen(msg) + 1);
  strcpy(msgQueue[numMsgQueueEntries].msg, msg);
  msgQueue[numMsgQueueEntries].confirm = confirm;
  
  numMsgQueueEntries++;
  
  return;
}

void procMsgQueue(){
  unsigned int i;
  
  for (i = 0; i < numMsgQueueEntries; i++){
    if ((i < (numMsgQueueEntries - 1)) || msgQueue[i].confirm == true){
      displayMsg(msgQueue[i].msg, i);
    } else {
      displayMsgNoWait(msgQueue[i].msg, i);
    }
    free(msgQueue[i].msg);
  }
  
  free(msgQueue);
  numMsgQueueEntries = 0;
  msgQueue = 0;
  return;
}