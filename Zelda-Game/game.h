#ifndef GAME_H
#define GAME_H

void startGame();
void setUpGame();
char** createMap(char** mapMetadata, int mapRowSize,int mapColSize, int itemCount);
void displayMap(char** map, int mapRowSize, int mapColSize);
void runGame(char** map,int mapRowSize, int mapColSize);
#endif