#ifndef _LVT_H
#define _LVT_H

#include <stdbool.h>
#include <ncurses.h>
#include "types.h"
#include "level.h"
#include "creature.h"

#define MAX(a, b) (a < b ? b : a)
#define MIN(a, b) (a > b ? b : a)
#define ISODD(a) (a % 2 ? true : false)
#define ISEVEN(a) (a % 2 ? false : true)

#ifndef _CHARGEN_C
void initializeCharacter();
#else
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
#else
#endif

#ifndef _GAME_C
void startGame(map map);
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
#else
typedef struct centerPoint{
  unsigned int x;
  unsigned int y;
  bool complete;
} centerPoint;

level initLevel();
level generateLevel();
void digLevel(level level, unsigned int coverageGoal);
unsigned int currentCoverage(level level);
void digTunnels(level level, centerPoint *centerPoints);
unsigned int findNearestNeighbor(unsigned int i, centerPoint *centerPoints);
void placeDoors(level level);
coord2D *findDoorEligible(level level);
coord2D *enumerateFloors(level level);
bool isDoorEligible(level level, coord2D coords);
void placeStairs(level level);
#endif

#ifndef _MAIN_C
extern const double pi;
extern creature player;
#else
#endif

#ifndef _MAP_C
void setMapSpaceTerrain(level level, unsigned int i, unsigned int j, terrain terrain);
terrain getMapSpaceTerrain(level level, unsigned int i, unsigned int j);
bool getMapSpaceExploredState(level level, unsigned int i, unsigned int j);
void setMapSpaceExploredState(level level, unsigned int i, unsigned int j, bool state);
coord2D findLevelUpstair(level level);
void initializeMapSpaceContents(level level, unsigned int x, unsigned int y);
bool hasContents(level level, unsigned int x, unsigned int y);
bool hasPlantOccupant(level level, unsigned int x, unsigned int y);
bool hasCreatureOccupant(level level, unsigned int x, unsigned int y);
void updateRegionExploredState(level level, unsigned int x, unsigned int y, bool state);
void setCreatureOccupant(level level, unsigned int x, unsigned int y, creature *creature);
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
void displayMsg(char *msg);
extern WINDOW *msgWin;
extern WINDOW *statWin;
extern WINDOW *playArea;
void writeLinePlayArea(char *mapLine, unsigned int y);
void refreshPlayArea();
#else
coord2D definePlayAreaDisplay();
#endif

#endif