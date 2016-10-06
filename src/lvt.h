#ifndef _LVT_H
#define _LVT_H

#include <stdbool.h>
#include "level.h"
#include "pcg_basic.h"
#include "creature.h"

typedef pcg32_random_t rng;

typedef enum coin{
  HEADS,
  TAILS
} coin;

typedef struct coord2D{
  unsigned int x;
  unsigned int y;
} coord2D;

typedef struct coord3D{
  unsigned int x;
  unsigned int y;
  unsigned int level;
} coord3D;

#ifndef _CHARGEN_C
void initializeCharacter();
#else
#endif

#ifndef _LEVELDISP_C
void displayLevel(level level);
#endif

#ifndef _LEVELGEN_C
map generateMap();
void initializeLevelGen();
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
#else
#endif

#endif