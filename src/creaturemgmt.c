#define _CREATUREMGMT_C

#include "lvt.h"
#include "creature.h"

void setCreatureName(creature *creature, char *name){
  creature->name = name;
  
  return;
}

char *getCreatureName(creature *creature){
  return creature->name;
}

void setIsPlayer(creature *creature){
  creature->isPlayer = true;
  
  return;
}

void changeDispChar(creature *creature, char c){
  creature->dispChar = c;
  
  return;
}

char getCreatureDispChar(creature *creature){
  return creature->dispChar;
}

coord3D getCreatureLocation(creature *creature){
  return creature->location;
}

void setCreatureLocation(creature *creature, coord3D location){
  creature->location.x = location.x;
  creature->location.y = location.y;
  creature->location.level = location.level;
  
  return;
}