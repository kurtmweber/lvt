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

#define _SPECIESINFO_C

#include "lvt.h"
#include "colors.h"
#include "creature.h"
#include "plant.h"

speciesInfo speciesData[MAXCREATURESPECIES];
plantSpeciesInfo plantSpeciesData[MAXPLANTSPECIES];

void getSpeciesModifiers(creatureSpecies species, statList *list){
  list->strength = speciesData[species].statModifiers[STRENGTH];
  list->wisdom = speciesData[species].statModifiers[WISDOM];
  list->intelligence = speciesData[species].statModifiers[INTELLIGENCE];
  list->constitution = speciesData[species].statModifiers[CONSTITUTION];
  list->charisma = speciesData[species].statModifiers[CHARISMA];
  list->dexterity = speciesData[species].statModifiers[DEXTERITY];
  
  return;
}

unsigned int getSpeciesLifePace(creatureSpecies species){
  return speciesData[species].lifePace;
}

unsigned int getSpeciesBaseHp(creatureSpecies species){
  return speciesData[species].baseHp;
}

speciesAggression getSpeciesAggression(creatureSpecies species){
  return speciesData[species].aggression;
}

// Stats should sum to +7

void initSpeciesDataBear(){
  speciesData[BEAR].statModifiers[STRENGTH] = 5;
  speciesData[BEAR].statModifiers[WISDOM] = -1;
  speciesData[BEAR].statModifiers[INTELLIGENCE] = -3;
  speciesData[BEAR].statModifiers[CONSTITUTION] = 5;
  speciesData[BEAR].statModifiers[CHARISMA] = 0;
  speciesData[BEAR].statModifiers[DEXTERITY] = 1;
  
  speciesData[BEAR].dispChar = 'B';
  speciesData[BEAR].color = MagentaBlack;
  speciesData[BEAR].hasHands = false;
  
  speciesData[BEAR].weight = 500;
  
  speciesData[BEAR].aggression = SPECIES_TRUMP;
  
  return;
}

void initSpeciesDataDwarf(){
  speciesData[DWARF].statModifiers[STRENGTH] = 5;
  speciesData[DWARF].statModifiers[WISDOM] = 3;
  speciesData[DWARF].statModifiers[INTELLIGENCE] = 2;
  speciesData[DWARF].statModifiers[CONSTITUTION] = 5;
  speciesData[DWARF].statModifiers[CHARISMA] = -3;
  speciesData[DWARF].statModifiers[DEXTERITY] = -5;
  
  speciesData[DWARF].dispChar = 'h';
  speciesData[DWARF].color = RedBlack;
  speciesData[DWARF].hasHands = true;
  
  speciesData[DWARF].weight = 200;
  
  speciesData[DWARF].aggression = SPECIES_HYPERAGGRESSIVE;
  
  return;
}

void initSpeciesDataElf(){
  speciesData[ELF].statModifiers[STRENGTH] = -2;
  speciesData[ELF].statModifiers[WISDOM] = 5;
  speciesData[ELF].statModifiers[INTELLIGENCE] = 4;
  speciesData[ELF].statModifiers[CONSTITUTION] = -2;
  speciesData[ELF].statModifiers[CHARISMA] = 0;
  speciesData[ELF].statModifiers[DEXTERITY] = 2;
  
  speciesData[ELF].dispChar = '@';
  speciesData[ELF].color = GreenBlack;
  speciesData[ELF].hasHands = true;
  
  speciesData[ELF].weight = 300;
  
  speciesData[ELF].aggression = SPECIES_CALM;
  
  return;
}

void initSpeciesDataHalfling(){
  speciesData[HALFLING].statModifiers[STRENGTH] = -4;
  speciesData[HALFLING].statModifiers[WISDOM] = 1;
  speciesData[HALFLING].statModifiers[INTELLIGENCE] = 3;
  speciesData[HALFLING].statModifiers[CONSTITUTION] = 5;
  speciesData[HALFLING].statModifiers[CHARISMA] = -3;
  speciesData[HALFLING].statModifiers[DEXTERITY] = 5;
  
  speciesData[HALFLING].dispChar = 'h';
  speciesData[HALFLING].color = BlueBlack;
  speciesData[HALFLING].hasHands = true;
  
  speciesData[HALFLING].weight = 200;
  
  speciesData[HALFLING].aggression = SPECIES_CHILL;
  
  return;
}

void initSpeciesDataHuman(){
  speciesData[HUMAN].statModifiers[STRENGTH] = -2;
  speciesData[HUMAN].statModifiers[WISDOM] = 3;
  speciesData[HUMAN].statModifiers[INTELLIGENCE] = 4;
  speciesData[HUMAN].statModifiers[CONSTITUTION] = -3;
  speciesData[HUMAN].statModifiers[CHARISMA] = 3;
  speciesData[HUMAN].statModifiers[DEXTERITY] = 2;
  
  speciesData[HUMAN].dispChar = '@';
  speciesData[HUMAN].color = WhiteBlack;
  speciesData[HUMAN].hasHands = true;
  
  speciesData[HUMAN].weight = 300;
  
  speciesData[HUMAN].aggression = SPECIES_PEEVISH;
  
  return;
}

void initSpeciesData(){
  unsigned int i;
  
  for (i = 0; i < MAXCREATURESPECIES; i++){
    speciesData[i].lifePace = 1000;
    speciesData[i].baseHp = 20;
    speciesData[i].speed = 5;
  }
  
  initSpeciesDataHuman();
  initSpeciesDataHalfling();
  initSpeciesDataElf();
  initSpeciesDataDwarf();
  initSpeciesDataBear();
  
  return;
}

void initSpeciesDataBlueberry(){
  plantSpeciesData[BLUEBERRY].toughness = 12;
  plantSpeciesData[BLUEBERRY].growthRate = 3;
  plantSpeciesData[BLUEBERRY].productionTime = 50;
  plantSpeciesData[BLUEBERRY].maturityLevel = 300;
  plantSpeciesData[BLUEBERRY].maxProduction = 10;
  plantSpeciesData[BLUEBERRY].plantClass = BERRYBUSH;
  plantSpeciesData[BLUEBERRY].dispChar = ':';
  plantSpeciesData[BLUEBERRY].color = CyanBlack;
  
  return;
}

void initSpeciesDataBlackberry(){
  plantSpeciesData[BLACKBERRY].toughness = 7;
  plantSpeciesData[BLACKBERRY].growthRate = 5;
  plantSpeciesData[BLACKBERRY].productionTime = 40;
  plantSpeciesData[BLACKBERRY].maturityLevel = 500;
  plantSpeciesData[BLACKBERRY].maxProduction = 20;
  plantSpeciesData[BLACKBERRY].plantClass = BERRYBUSH;
  plantSpeciesData[BLACKBERRY].dispChar = ':';
  plantSpeciesData[BLACKBERRY].color = BlueBlack;
  
  return;
}

void initSpeciesDataStrawberry(){
  plantSpeciesData[STRAWBERRY].toughness = 20;
  plantSpeciesData[STRAWBERRY].growthRate = 4;
  plantSpeciesData[STRAWBERRY].productionTime = 100;
  plantSpeciesData[STRAWBERRY].maturityLevel = 500;
  plantSpeciesData[STRAWBERRY].maxProduction = 15;
  plantSpeciesData[STRAWBERRY].plantClass = BERRYBUSH;
  plantSpeciesData[STRAWBERRY].dispChar = ':';
  plantSpeciesData[STRAWBERRY].color = RedBlack;
  
  return;
}

void initSpeciesDataRaspberry(){
  plantSpeciesData[RASPBERRY].toughness = 10;
  plantSpeciesData[RASPBERRY].growthRate = 5;
  plantSpeciesData[RASPBERRY].productionTime = 50;
  plantSpeciesData[RASPBERRY].maturityLevel = 1000;
  plantSpeciesData[RASPBERRY].maxProduction = 100;
  plantSpeciesData[RASPBERRY].plantClass = BERRYBUSH;
  plantSpeciesData[RASPBERRY].dispChar = ':';
  plantSpeciesData[RASPBERRY].color = MagentaBlack;
  
  return;
}

void initPlantSpeciesData(){
  initSpeciesDataBlueberry();
  initSpeciesDataBlackberry();
  initSpeciesDataStrawberry();
  initSpeciesDataRaspberry();
  /*initSpeciesDataFennel();
  initSpeciesDataHibiscus();
  initSpeciesDataLinden();
  initSpeciesDataZoysia();*/
  
  return;
}