/*  This file is part of Lavender Throne.
 *  Copyright 2016-2017 by Kurt Weber
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

//#define _D_DEBUG

#include <stdbool.h>
#include <ncurses.h>

#include "types.h"
#include "level.h"
#include "creature.h"
#include "move.h"
#include "item.h"
#include "plant.h"
#include "save.h"

#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define ISODD(a) ((a) % 2 ? true : false)
#define ISEVEN(a) ((a) % 2 ? false : true)

#ifndef _GAME_C
void startGame();
void playerDead();
extern bool freeAction;
void initializeGameStatus();
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
void doLook(unsigned int c);
#else
#endif

#ifndef _INVENTORY_C
void doInventory();
void doPickup();
void doNameItem();
void doUnNameItem();
void doWield();
void doUnwield();
void doDrop();
void doWear();
void doRemove();
void displayInventoryWindow(unsigned int i, bool checked[52]);
extern WINDOW *invWin;
#else
void displayInventoryWindow(unsigned int i, bool checked[52]);
#endif

#ifndef _ITEM_C
extern itemType *itemTypes[ITEM_TYPE_MAX];
void initItems();
void removeItemName(item *item);
void setItemWorn(item *item, bool status);
#else
void initCorpses();
void initLongswords();
void initAxes();
void initDaggers();
void initShirts();
void initUnderarmor();
void initShields();
void initFruit();
void initSeeds();
void initItemType(itemType *in);
#endif

#ifndef _ITEMMGMT_C
void setCorpseNutrition(item *corpse, unsigned int nutrition);
void setFruitNutrition(item *fruit, unsigned int nutrition);
unsigned int getFruitNutrition(item *fruit);
unsigned int getCorpseNutrition(item *corpse);
char getItemDispChar(item *item);
void setItemLocation(item *item, coord3D location);
colorPairs getItemColor(item *item);
void setItemName(item *item, char *name);
void setItemClass(item *item, itemClassId class);
unsigned int getEffectiveArmor(item *item);
unsigned int getItemAttrs(item *item);
unsigned int getItemWeight(item *item);
void setItemWeight(item *item, unsigned int weight);
itemClassId getItemClass(item *item);
coord3D getItemLocation(item *item);
void setItemOwned(item *item, bool status);
bool getItemOwned(item *item);
void setSeedRest(item *seed, unsigned int rest);
void setSeedDormancy(item *seed, unsigned int dormancy);
unsigned int getSeedRest(item *seed);
unsigned int getSeedDormancy(item *seed);
bool isSeed(item *item);
void setItemOwner(item *item, creature *owner);
creature *getItemOwner(item *item);
unsigned int getItemNutrition(item *item);
bool isWeapon(item *item);
char *getItemClassName(item *item);
char *getItemName(item *item);
bool isArmor(item *item);
bool armorSlotMatch(item *item, armorSlots slotMatch);
bool isWorn(item *item);
void setItemWielded(item *item, bool status);
#else
itemClassId getItemClass(item *item);
unsigned int getFruitNutrition(item *fruit);
unsigned int getCorpseNutrition(item *corpse);
bool isArmor(item *item);
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

#ifndef _LOOK_C
void doLook(unsigned int c);
#else
void lookCreatureOccupant(coord3D mapLoc);
void lookContents(coord3D mapLoc);
void lookPlantOccupant(coord3D mapLoc);
#endif

#ifndef _MAIN_C
extern const double pi;
extern creature player;
extern map dungeon;
extern gameStatus status;
extern creatureList *creatures;
extern plantList *plants;
extern seedList *seeds;
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
void addContents(unsigned int mapLevel, unsigned int x, unsigned int y, item *item);
mapSpaceContents *getContents(level level, unsigned int x, unsigned int y);
void setPlantOccupant(level level, unsigned int x, unsigned int y, plant *plant);
plant *getPlantOccupant(level level, unsigned x, unsigned int y);
void clearPlantOccupant(level level, unsigned int x, unsigned int y);
void removeContent(unsigned int mapLevel, unsigned int x, unsigned int y, item *item);
creature *getCreatureOccupant(level level, unsigned int x, unsigned int y);
#else
void addContents(unsigned int mapLevel, unsigned int x, unsigned int y, item *item);
mapSpaceContents *getContents(level level, unsigned int x, unsigned int y);
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

#ifndef _PICKFRUIT_C
void doPickFruit();
item *pickFruitFromPlant(plant *plant);
#else
item *pickFruitFromPlant(plant *plant);
#endif

#ifndef _PLANTGEN_C
plantList *generateStartingPlants();
void placeNewPlant(plant *plant, coord3D location);
plant *spawnOrphanPlant(plantSpecies species);
plant *spawnPlantFromSeed(plantSpecies species);
#else
bool decidePlacePlant(coord2D floor, unsigned int level);
plant *newRandomOrphanPlant(coord2D floor, unsigned int level);
void placeNewPlant(plant *plant, coord3D location);
plant *spawnOrphanPlant(plantSpecies species);
#endif

#ifndef _PLANTLIST_C
plantList *insertNewPlantNode(plantList *list, plantList *node);
plantList *findPlantListEntry(plantList *list, plant *plant);
plantList *removePlantNode(plantList *list, plantList *node);
#endif

#ifndef _PLANTMGMT_C
void setPlantSpecies(plant *plant, plantSpecies species);
void setPlantClass(plant *plant, plantClass plantClass);
void setPlantCurToughness(plant *plant, unsigned int toughness);
void setPlantMaxToughness(plant *plant, unsigned int toughness);
void setPlantCurGrowth(plant *plant, unsigned int growth);
void setPlantMaxGrowth(plant *plant, unsigned int growth);
void setPlantCurProduction(plant *plant, unsigned int production);
void setPlantMaxProduction(plant *plant, unsigned int production);
void setPlantGrowthRate(plant *plant, unsigned int growthRate);
void setPlantProductionTime(plant *plant, unsigned int productionTime);
void setPlantProductionProgress(plant *plant, unsigned int progress);
void setPlantDispChar(plant *plant, char dispChar);
void setPlantDispColor(plant *plant, colorPairs color);
void setPlantAttrs(plant *plant, unsigned int attrs);
void setPlantLocation(plant *plant, coord3D location);
char getPlantDispChar(plant *plant);
colorPairs getPlantColor(plant *plant);
unsigned int getPlantCurToughness(plant *plant);
unsigned int getPlantMaxToughness(plant *plant);
void tramplePlant(plant *plant, creature *creature);
plantSpecies getPlantSpecies(plant *plant);
unsigned int getPlantCurProduction(plant *plant);
unsigned int getPlantGrowthRate(plant *plant);
unsigned int getPlantCurGrowth(plant *plant);
unsigned int getPlantMaxGrowth(plant *plant);
unsigned int getPlantMaxProduction(plant *plant);
unsigned int getPlantProductionProgress(plant *plant);
unsigned int getPlantProductionTime(plant *plant);
coord3D getPlantLocation(plant *plant);
#endif

#ifndef _PLANTS_C
void updatePlants();
#endif

#ifndef _QUESTIONS_C
bool askQuestionYesNo(char *question);
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

#ifndef _READSAVE_C
bool readSaveFile();
#else
fileObjectInfo getFileObjectInfo(FILE *file);
void getFileObjectData(void *data, size_t size, FILE *saveFile);
void addToObjectList(void *data, uintptr_t id, encapsulatedTypes type,size_t size);
void readSavedPlayerObject(creature *object);
void *findInObjectList(uintptr_t object);
void readSavedStringObject(char *object);
void readSavedItemObject(item *object);
void setPlayerObjectPtr(creature *playerPtr);
void readSavedGlobalStatusObject(gameStatus *object);
void readSavedMapSpaceObject(mapSpace *object);
void readSavedCreatureObject(creature *object);
void readPlantObject(plant *object);
#endif

#ifndef _SAVE_C
void doSave();
#else
uintptr_t storeObject(void *object, encapsulatedTypes type);
uintptr_t storeCreature(creature *object, encapsulatedTypes type);
void resetObjectReferences();
uintptr_t storeString(char *object, encapsulatedTypes type);
uintptr_t getObjectId(void *object);
void encapsulateAndWrite(void *object, encapsulatedTypes type, size_t objectSize, uintptr_t objectId);
uintptr_t storeItem(item *object, encapsulatedTypes type);
void setStored(void *object);
bool alreadyStored(void *object);
uintptr_t storeGlobalStatus(gameStatus *object, encapsulatedTypes type);
uintptr_t storeMapSpace(mapSpace *object, encapsulatedTypes type);
uintptr_t storePlant(plant *object, encapsulatedTypes type);
uintptr_t getObjectIdGuaranteedUnique(void *object);
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
coord2D definePlayAreaDisplay();
void displayQuestionYesNo(char *msg);
char *getLineInput(char *prompt);
#else
coord2D definePlayAreaDisplay();
#endif

#ifndef _SEEDLIST_C
seedList *insertNewSeedNode(seedList *list, seedList *node);
seedList *findSeedListEntry(seedList *list, item *seed);
seedList *removeSeedNode(seedList *list, seedList *node);
#endif

#ifndef _SEEDS_C
void updateSeeds();
#endif

#ifndef _SPAWNITEM_C
item *spawnItem(itemClassId class, int subClass);
#else
item *spawnCorpse(int subClass);
item *spawnLongsword(int subClass);
item *spawnAxe(int subClass);
item *spawnDagger(int subClass);
item *spawnShirt(int subClass);
item *spawnUnderarmor(int subClass);
item *spawnShield(int subClass);
item *spawnFruit(int subClass);
item *spawnSeed(int subClass);
#endif

#ifndef _SPECIESINFO_C
extern speciesInfo speciesData[MAXCREATURESPECIES];
extern plantSpeciesInfo plantSpeciesData[MAXPLANTSPECIES];
void initSpeciesData();
void getSpeciesModifiers(creatureSpecies species, statList *list);
unsigned int getSpeciesLifePace(creatureSpecies species);
unsigned int getSpeciesBaseHp(creatureSpecies species);
void initPlantSpeciesData();
speciesAggression getSpeciesAggression(creatureSpecies species);
#else
void initSpeciesDataHuman();
void initSpeciesDataHalfling();
void initSpeciesDataElf();
void initSpeciesDataDwarf();
void initSpeciesDataBlueberry();
void initSpeciesDataStrawberry();
void initSpeciesDataRaspberry();
#endif

#ifndef _STRINGLOOKUPS_C
#else
#endif

#ifndef _THROW_C
void doThrow();
void throwObject(creature *creature, moveDirection dir, item *item);
#else
void calcRicochetDirection(coord3D pos, moveMatrix *move);
#endif

#ifndef _UTIL_C
int clampRangeIntSigned(int value, int min, int max);
bool sameFactions(creature *creature1, creature *creature2);
unsigned int sumArrayInt(int *array, unsigned int numElements);
void *randomizeArray(void *array, unsigned int numElements, size_t size);
coord2D getSpaceDirectionCoordinates(coord2D point, moveDirection dir);
char *autoGenerateCorpseName(creature *creature);
char inventoryIndexToLetter(char c);
bool isInventoryLetter(char c);
int inventoryLetterToIndex(char c);
void directionToUnitMatrix(moveDirection dir, moveMatrix *matrix);
item *checkAdjacentFood(coord3D location);
item *checkAdjacentFruitingBush(coord3D location);
unsigned int returnIndexMaxValLongDouble(long double *array, unsigned int numElements);
bool isInRange2D(coord2D reference, coord2D target, unsigned int range);
unsigned int getDistanceSquared2D(coord2D reference, coord2D target);
moveDirection findDirection(coord2D point1, coord2D point2);
coord2D get2DCoordPart(coord3D ref);
#else
#endif

#endif