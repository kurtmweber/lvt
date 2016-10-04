#ifndef _LVT_H
#define _LVT_H

#include "level.h"
#include "pcg_basic.h"

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

#ifndef _MAIN_C
extern const double pi;
#else
#endif

#ifndef _LEVELGEN_C
level generateLevel();
void initializeLevelGen();
void setLevelTerrain(level level, unsigned int i, unsigned int j, terrain terrain);
terrain getLevelTerrain(level level, unsigned int i, unsigned int j);
#else
typedef struct centerPoint{
  unsigned int x;
  unsigned int y;
  bool complete;
} centerPoint;

level initLevel();
void digLevel(level level, unsigned int coverageGoal);
unsigned int currentCoverage(level level);
void digTunnels(level level, centerPoint *centerPoints);
unsigned int findNearestNeighbor(unsigned int i, centerPoint *centerPoints);
void setLevelTerrain(level level, unsigned int i, unsigned int j, terrain terrain);
terrain getLevelTerrain(level level, unsigned int i, unsigned int j);
#endif

#ifndef _LEVELDISP_C
void displayLevel(level level);
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

#endif