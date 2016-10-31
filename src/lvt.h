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

#ifndef _LVT_H
#define _LVT_H

#include <stdbool.h>
#include <ncurses.h>
#include "colors.h"
#include "types.h"
#include "level.h"
#include "creature.h"
#include "move.h"

#define MAX(a, b) (a < b ? b : a)
#define MIN(a, b) (a > b ? b : a)
#define ISODD(a) (a % 2 ? true : false)
#define ISEVEN(a) (a % 2 ? false : true)

#ifndef _ALLOCATOR_C
creatureList *allocateCreatureListEntry();
void freeCreatureListEntry(creatureList *node);
#else
#endif

#ifndef _CHARGEN_C
void initializeCharacter();
#else
char *inputPlayerName();
creatureSpecies inputPlayerSpecies();
creatureClass inputPlayerClass();
#endif

#ifndef _COLORS_C
void initializeColors();
#else
#endif

#ifndef _CREATUREGEN_C
creatureList *generateStartingCreatures();
#else
bool decidePlaceCreature(coord2D floor, unsigned int level);
creature *newRandomOrphanCreature(coord2D floor, unsigned int level);
creatureList *insertNewCreatureNode(creatureList *list, creatureList *node);
creature *spawnOrphanCreature(creatureSpecies species, creatureClass class);
void placeNewCreature(creature *creature, coord3D location);
#endif

#ifndef _CREATUREINIT_C
void genOrphanCreatureStats(creature *creature);
#else
void getClassModifiers(creatureClass class, statList *list);
#endif

#ifndef _CREATUREMGMT_C
void setCreatureName(creature *creature, char *name);
char *getCreatureName(creature *creature);
void setIsPlayer(creature *creature);
void changeDispChar(creature *creature, char c);
char getCreatureDispChar(creature *creature);
creature *getCreatureOccupant(level level, unsigned int x, unsigned int y);
void setCreatureLocation(creature *creature, coord3D location);
coord3D getCreatureLocation(creature *creature);
unsigned int getCreatureMapLevel(creature *creature);
void setCreatureSpecies(creature *creature, creatureSpecies species);
creatureSpecies getCreatureSpecies(creature *creature);
void setCreatureClass(creature *creature, creatureClass class);
creatureClass getCreatureClass(creature *creature);
void setCreatureMatured(creature *creature, bool matured);
bool getCreatureMatured(creature *creature);
void getCreatureMaxStats(creature *creature, statList *stats);
void setCreatureMaxStats(creature *creature, int stats[MAXSTATNAME]);
void getCreatureCurStats(creature *creature, statList *stats);
void setCreatureCurStats(creature *creature, int stats[MAXSTATNAME]);
void setCreatureLifePace(creature *creature, unsigned int lifePace);
bool updateCreatureLifeCycle(creature *creature);
bool hasCreatureMatured(creature *creature);
void setCreatureLevel(creature *creature, unsigned int level);
void setCreatureMaxHp(creature *creature, unsigned int maxHp);
void setCreatureCurHp(creature *creature, unsigned int curHp);
void setCreatureXp(creature *creature, unsigned int Xp);
unsigned int getCreatureLevel(creature *creature);
unsigned int getCreatureXp(creature *creature);
unsigned int getCreatureCurHp(creature *creature);
unsigned int getCreatureMaxHp(creature *creature);
void setCreatureBioSex(creature *creature, bioSex sex);
void setCreatureColor(creature *creature, colorPairs colorPair);
void setCreatureAttribute(creature *creature, unsigned int attribute);
colorPairs getCreatureColor(creature *creature);
unsigned int getCreatureAttribute(creature *creature);
void setCreatureFaction(creature *creature, unsigned int faction);
unsigned int getCreatureFaction(creature *creature);
#else
bool updateCreatureLifeCycleNotMatured(creature *creature);
bool updateCreatureLifeCycleMatured(creature *creature);
void getCreatureMaxStats(creature *creature, statList *stats);
void setCreatureMaxStats(creature *creature, int stats[MAXSTATNAME]);
void getCreatureCurStats(creature *creature, statList *stats);
void setCreatureCurStats(creature *creature, int stats[MAXSTATNAME]);
#endif

#ifndef _FACTIONS_C
unsigned int getNumFactions();
void initializeFactions();
#else
#endif

#ifndef _GAME_C
void startGame();
#else
void gameLoop();
bool doQuit();
void processKey(unsigned int c);
void updateTurnCounter();
#endif

#ifndef _INPUT_C
void doMoveKey(unsigned int c);
void doOpenDoor(unsigned int c);
void doSearchDoors(unsigned int c);
void doStairs(unsigned int c);
#else
#endif

#ifndef _LEVELDISP_C
void displayLevel(level level);
char *generateLevelRepresentation(level level, unsigned int line);
#endif

#ifndef _LEVELGEN_C
map generateMap();
void initializeLevelGen();
extern const unsigned int dimMapX;	// map dimensions
extern const unsigned int dimMapY;
extern const unsigned int numLevels;
coord2D *enumerateFloors(level level);
#else
typedef struct centerPoint{
  unsigned int x;
  unsigned int y;
  bool complete;
} centerPoint;

level initLevel();
level generateLevel(unsigned int levelNum);
void digLevel(level level, unsigned int coverageGoal);
unsigned int currentCoverage(level level);
void digTunnels(level level, centerPoint *centerPoints);
unsigned int findNearestNeighbor(unsigned int i, centerPoint *centerPoints);
void placeDoors(level level);
coord2D *findDoorEligible(level level);
coord2D *enumerateFloors(level level);
bool isDoorEligible(level level, coord2D coords);
void placeStairs(level level, unsigned int levelNum);
#endif

#ifndef _MAIN_C
extern const double pi;
extern creature player;
extern map dungeon;
extern gameStatus status;
extern creatureList *creatures;
#else
#endif

#ifndef _MAP_C
void setMapSpaceTerrain(level level, unsigned int x, unsigned int y, terrain terrain);
terrain getMapSpaceTerrain(level level, unsigned int x, unsigned int y);
bool getMapSpaceExploredState(level level, unsigned int i, unsigned int j);
void setMapSpaceExploredState(level level, unsigned int i, unsigned int j, bool state);
coord2D findLevelUpstair(level level);
void initializeMapSpaceContents(level level, unsigned int x, unsigned int y);
bool hasContents(level level, unsigned int x, unsigned int y);
bool hasPlantOccupant(level level, unsigned int x, unsigned int y);
bool hasCreatureOccupant(level level, unsigned int x, unsigned int y);
void updateRegionExploredState(level level, unsigned int x, unsigned int y, bool state);
void setCreatureOccupant(level level, unsigned int x, unsigned int y, creature *creature);
void clearCreatureOccupant(level level, unsigned int x, unsigned int y);
void setTerrainData(level level, unsigned int x, unsigned int y, terrain terrain, void *data);
void *getTerrainData(level level, unsigned int x, unsigned int y, terrain terrain);
coord2D findLevelDownstair(level level);
#else
#endif

#ifndef _MESSAGES_C
void addToMsgQueue(char *msg, bool confirm);
void procMsgQueue();
#else
#endif

#ifndef _MOVE_C
moveOutcome moveCreature(creature *creature, moveDirection dir);
#else
moveOutcome moveCreature(creature *creature, moveDirection dir);
#endif

#ifndef _NAME_C
char *generateName();
#else
#endif

#ifndef _RANDOM_C
void initializeRNG(rng *rng);
coin coinFlip(rng *rng);
double normalRandomInt(rng *rng, double mu, double sigma);
unsigned int uniformRandomRangeInt(rng *rng, unsigned int lower, unsigned int upper);
#else
unsigned int boundedRand(rng *rng, unsigned int bound);
double randomDouble(rng *rng);
coin coinFlip(rng *rng);
#endif

#ifndef _SCREEN_C
void initializeNcurses();
void destroyNcurses();
void initializeGameScreen();
void displayMsg(char *msg, int a);
void displayMsgNoWait(char *msg, int a);
extern WINDOW *msgWin;
extern WINDOW *statWin;
extern WINDOW *playArea;
void writeLinePlayArea(screenDisplayCell *mapLine, unsigned int y);
void refreshPlayArea();
void clearMsg();
void clearPlayArea();
void updateStatWin();
void setCursorLoc();
#else
coord2D definePlayAreaDisplay();
#endif

#ifndef _SPECIESINFO_C
extern speciesInfo speciesData[MAXCREATURESPECIES];
void initSpeciesData();
void getSpeciesModifiers(creatureSpecies species, statList *list);
unsigned int getSpeciesLifePace(creatureSpecies species);
unsigned int getSpeciesBaseHp(creatureSpecies species);
#else
void initSpeciesDataHuman();
void initSpeciesDataHalfling();
void initSpeciesDataElf();
void initSpeciesDataDwarf();
#endif

#ifndef _STRINGLOOKUPS_C
#else
#endif

#ifndef _UTIL_C
int clampRangeIntSigned(int value, int min, int max);
bool sameFactions(creature *creature1, creature *creature2);
unsigned int sumArrayInt(int *array, unsigned int numElements);
#else
#endif

#endif