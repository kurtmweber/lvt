#define _RANDOM_C

#include <time.h>
#include <math.h>
#include "lvt.h"
#include "pcg_basic.h"

void initializeRNG(rng *rng){
  pcg32_srandom_r((pcg32_random_t *)rng, time(NULL), (intptr_t)rng);
  
  return;
}

unsigned int boundedRand(rng *rng, unsigned int bound){
  // we do bound + 1 because I prefer the semantics of boundary to be inclusive,
  // but pcg makes it 0 <= x < bound, so it's non-inclusive
  return pcg32_boundedrand_r(rng, bound + 1);
}

double randomDouble(rng *rng){
  return ldexp(pcg32_random_r(rng), -32);
}

coin coinFlip(rng *rng){
  return boundedRand(rng, 1);
}

unsigned int uniformRandomRangeInt(rng *rng, unsigned int lower, unsigned int upper){
  // this is an inclusive range (e.g. [lower, upper])
  // boundedRand() starts at 0, so we have to do some arithmetic to move it into the specified range
  
  return (boundedRand(rng, (upper - lower)) + lower);
}

double normalRandomInt(rng *rng, double mu, double sigma){
  double a, b;
  double x, y;
  
  a = randomDouble(rng);
  b = randomDouble(rng);
  
  x = sqrt((double)-2 * log(a)) * cos(2 * pi * b);
  y = sqrt(-2 * log(a)) * sin(2 * pi * b);
  
  if (coinFlip(rng) == HEADS){
    return (x * sigma) + mu;
  } else {
    return (y * sigma) + mu;
  }
}