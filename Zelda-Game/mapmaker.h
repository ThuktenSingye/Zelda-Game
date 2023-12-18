#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char** map;
    char **mapMetaData;
    int mapRowSize;
    int mapColSize;
    int itemCount;
} MapInfo;

#define MAX_STRING_LENGTH 256
char **getItemData(int *itemCount, int *mapRowSize, int *mapColSize);
void freeMapItem(char** mapMetaData, int itemCount);
char *getObjectDescription(int posX,int posY);
#endif