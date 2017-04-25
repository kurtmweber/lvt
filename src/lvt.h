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

//#define _D_DEBUG

#include <stdbool.h>
#include <ncurses.h>
#include "colors.h"
#include "types.h"
#include "level.h"
#include "creature.h"
#include "move.h"
#include "item.h"
#include "creaturemgmt.h"
#include "plant.h"
#include "save.h"

#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define ISODD(a) ((a) % 2 ? true : false)
#define ISEVEN(a) ((a) % 2 ? false : true)

#ifndef _ALLOCATOR_C
creatureList *allocateCreatureListEntry();
void freeCreatureListEntry(creatureList *node);
item *allocateItem();
mapSpaceContents *allocateMapSpaceContentsListEntry();
plantList *allocatePlantListEntry();
void freePlantListEntry(plantList *node);
seedList *allocateSeedListEntry();
void freeSeedListEntry(seedList *node);
void freeItem(item *item);
#else
void freeItem(item *item);
#endif

#ifndef _ATTACK_C
unsigned int meleeAttack(creature *attacker, creature *defender);
unsigned int throwAttack(creature *attacker, creature *defender, item *weapon, unsigned int distanceLeft);
#else
unsigned int toHit(creature *attacker, item *weapon);
unsigned int toDefend(creature *defender);
unsigned int calcAttackVal(creature *attacker, item *weapon);
unsigned int calcDefenseVal(creature *defender);
unsigned int attack(creature *attacker, creature *defender, unsigned int toHitVal, unsigned int toDefendVal, unsigned int attackVal, unsigned int defenseVal);
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
creature *spawnOrphanCreature(creatureSpecies species, creatureClass class);
void placeNewCreature(creature *creature, coord3D location);
#endif

#ifndef _CREATUREINIT_C
void genOrphanCreatureStats(creature *creature);
#else
void getClassModifiers(creatureClass class, statList *list);
#endif

#ifndef _CREATURELIST_C
creatureList *insertNewCreatureNode(creatureList *list, creatureList *node);
creatureList *removeCreatureNode(creatureList *list, creatureList *node);
creatureList *findCreatureListEntry(creatureList *list, creature *creature);
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
bioSex getCreatureBioSex(creature *creature);
void setCreatureSpeed(creature *creature, unsigned int speed);
unsigned int getCreatureSpeed(creature *creature);
void incrementCreatureSpeedCounter(creature *creature, unsigned int incrAmount);
void decrementCreatureSpeedCounter(creature *creature, unsigned int decrAmount);
unsigned int getCreatureSpeedCounter(creature *creature);
unsigned int getCreatureLastMove(creature *creature);
void setCreatureLastMove(creature *creature, unsigned int move);
void initCreatureArmor(creature *creature);
void initCreatureWeapon(creature *creature);
void initCreatureInventory(creature *creature);
void killCreature(creature *creature);
void setCreatureLevelHpXp(creature *creature, unsigned int Xp);
void setCreatureWeight(creature *creature, unsigned int weight);
unsigned int getCreatureWeight(creature *creature);
bool hasWeapon(creature *creature);
char addCreatureInventoryItem(creature *creature, item *item);
void getCreatureInventory(creature *creature, item *inventory[52]);
wieldOutcome wieldItem(creature *creature, item *item);
void unwieldWeapon(creature *creature);
void removeCreatureInventoryItem(creature *creature, item *item);
wearOutcome wearItem(creature *creature, item *item);
unsigned int getCreatureArmorClass(creature *creature);
removeOutcome removeItem(creature *creature, item *item);
void regenerateHitPoints(creature *creature);
void setCreatureNutrition (creature *creature, unsigned int nutrition);
unsigned int getCreatureNutrition(creature *creature);
bool updateCreatureNutrition(creature *creature);
#else
bool updateCreatureLifeCycleNotMatured(creature *creature);
bool updateCreatureLifeCycleMatured(creature *creature);
void getCreatureMaxStats(creature *creature, statList *stats);
void setCreatureMaxStats(creature *creature, int stats[MAXSTATNAME]);
void getCreatureCurStats(creature *creature, statList *stats);
void setCreatureCurStats(creature *creature, int stats[MAXSTATNAME]);
void setCreatureXp(creature *creature, unsigned int Xp);
void setCreatureLevel(creature *creature, unsigned int level);
unsigned int getCreatureCurHp(creature *creature);
unsigned int getCreatureMaxHp(creature *creature);
void setCreatureMaxHp(creature *creature, unsigned int maxHp);
void setCreatureCurHp(creature *creature, unsigned int curHp);
coord3D getCreatureLocation(creature *creature);
unsigned int getCreatureWeight(creature *creature);
void setCreatureNutrition (creature *creature, unsigned int nutrition);
unsigned int getCreatureNutrition(creature *creature);
#endif

#ifndef _CREATUREMOVE_C
void moveCreatures();
#else
bool hasAction(creature *creature);
void doMoveCreature(creature *creature);
void moveCreatureUpStair(creature *creature);
void moveCreatureDownStair(creature *creature);
void changeCreatureLocation(creature *creature, coord3D newPos);
#endif

#ifndef _EAT_C
void doEat();
#else
void eatItem(creature *creature, item *foodItem);
#endif

#ifndef _FACTIONS_C
unsigned int getNumFactions();
void initializeFactions();
#else
#endif

#ifndef _FLOORITEMS_C
void generateFloorItems();
#else
bool decidePlaceItem(coord2D floor, unsigned int level);
void randomFloorItem(coord2D floor, unsigned int level);
item *randomWeapon();
item *randomLongsword();
item *randomAxe();
item *randomDagger();
item *randomArmor();
item *randomShirt();
item *randomUnderarmor();
item *randomShield();
#endif

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
void addToObjectList(void *data, uintptr_t id, encapsulatedTypes type);
void readSavedPlayerObject(creature *object);
void *findInObjectList(uintptr_t object);
void readSavedStringObject(char *object);
void readSavedItemObject(item *object);
void setPlayerObjectPtr(creature *playerPtr);
void readSavedGlobalStatusObject(gameStatus *object);
void readSavedMapSpaceObject(mapSpace *object);
void readSavedCreatureObject(creature *object);
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
uintptr_t storeDungeon(map object, encapsulatedTypes type);
uintptr_t storeLevel(level object, encapsulatedTypes type);
uintptr_t storeMapSpace(mapSpace *object, encapsulatedTypes type);
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
#else
#endif

#endif