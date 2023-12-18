#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "mapmaker.h"
#include <stdbool.h>

void runGame();
void setUpGame();
char** createMap(char **mapMetadata, int mapRowSize,int mapColSize, int itemCount);
void displayMap(char **map, int mapRowSize, int mapColSize);
void mainGame(char **map, char **inventory,Player *player, char currentPlayerDirection);
void startGame(MapInfo *mapInfo, Player *player,char **inventory);
bool destroyDummy(int *dummyLife);
void attackSquare(char currentPlayerDirection);
void clearScreen();
void freeMap(char** map, int mapRowSize);
void freeMapItemData(char** mapMetaData,int itemCount);



#endif