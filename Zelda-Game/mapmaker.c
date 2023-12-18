#include<stdlib.h>
#include<string.h>
#include"mapmaker.h"

/*  This file and the corresponding header file (mapmaker.c and mapmaker.h) contains a
    single function you can use to get some metadata that you need to create
    the 2D map array in your game. 
    
    If you want to make your own metadata for the map (e.g adding wall),
    you can modify the metadata table here. Keep in mind that
    we will test your assignment with our own metadata. */
char** getItemData(int* itemCount, int* mapRowSize, int* mapColSize)
{
    int i;
    char** table;

    *itemCount = 36;        /* The number of items in the playable area */
    *mapRowSize = 8;       /* The map row size you will create later */
    *mapColSize = 8;       /* The map column size you will create later */

    /* Now it is time to malloc the array of strings */
    table = (char**) malloc(sizeof(char*) * (*itemCount));

    for(i = 0 ; i < (*itemCount) ; i++)
    {
        /*each string is also mallocc'd, don't forget to free them! */
        table[i] = (char*) malloc(sizeof(char) * MAX_STRING_LENGTH);
    }
    
    /* Now it is time to fill the array of strings with the data */
    strcpy(table[0], "4,4 > Player|The Player Starting Location");
    strcpy(table[1], "1,4 T Treasure|Pretty Gems : D");
    strcpy(table[2], "2,6 T Treasure|Candle ");
    strcpy(table[3], "3,7 # Wall|a wall");
    strcpy(table[4], "4,7 # Wall|a wall");
    strcpy(table[5], "5,7 # Wall|a wall");
    strcpy(table[6], "6,7 # Wall|a wall");
    strcpy(table[7], "7,7 # Wall|a wall");
    strcpy(table[8], "7,6 # Wall|a wall");
    strcpy(table[9], "7,5 # Wall|a wall");
    strcpy(table[10], "7,2 # Wall|a wall");
    strcpy(table[11], "7,4 # Wall|a wall");
    strcpy(table[12], "7,1 # Wall|a wall");
    strcpy(table[13], "6,0 # Wall|a wall");
    strcpy(table[14], "7,0 # Wall|a wall");
    strcpy(table[15], "5,0 # Wall|a wall");
    strcpy(table[16], "4,0 # Wall|a wall");
    strcpy(table[17], "6,1 # Wall|a wall");
    strcpy(table[18], "5,1 # Wall|a wall");
    strcpy(table[19], "4,1 # Wall|a wall");
    strcpy(table[20], "6,2 # Wall|a wall");
    strcpy(table[21], "5,2 # Wall|a wall");
    strcpy(table[22], "2,7 # Wall|a wall");
    strcpy(table[23], "1,7 # Wall|a wall");
    strcpy(table[24], "0,7 # Wall|a wall");
    strcpy(table[25], "0,6 # Wall|a wall");
    strcpy(table[26], "0,5 # Wall|a wall");
    strcpy(table[27], "0,4 # Wall|a wall");
    strcpy(table[28], "0,0 # Wall|a wall");
    strcpy(table[29], "0,1 # Wall|a wall");
    strcpy(table[30], "0,2 # Wall|a wall");
    strcpy(table[31], "1,0 # Wall|a wall");
    strcpy(table[32], "2,0 # Wall|a wall");
    strcpy(table[33], "2,1 # Wall|a wall");
    strcpy(table[34], "1,1 O NPC|It's dangerous to go alone! Take this.");
    strcpy(table[35], "5,5 D Dummy|A training dummy. It's pretty weak.");

    return table; /* return the array */

    /* remember, you need to free this 2D table at some point once you finish
       extracting its information to create your own 2D map array in
       the main function. */
}


/*
    Retrieves the description associated with a specific position on the game map.
    It extracts map metadata using getItemData(), iterates through the metadata to find
    a match for the given position (posX, posY), and returns the description found after '|'.
*/
char* getObjectDescription(int posX, int posY) {
    int itemCount, mapRowSize, mapColSize;

    /* get map meta data */ 
    char** mapMetaData = getItemData(&itemCount, &mapRowSize, &mapColSize);

    for (int i = 0; i < itemCount; i++) {
        int x, y;
        char type;
        char description[MAX_STRING_LENGTH];
        sscanf(mapMetaData[i], "%d,%d %c %[^\n]", &x, &y, &type, description);
        char* des = strchr(description, '|');
        if (des != NULL && x == posX && y == posY) {
            /* Duplicate the substring after '|' */
            char* des2 = strdup(des + 1);
            if (des2 != NULL) {
                /* Return the duplicated string */
                freeMapItem(mapMetaData, itemCount);  /* Free mapMetaData before returning */
                return des2;
            } else {
                /* Handle memory allocation failure */
                printf("Error: Memory allocation failed.\n");
                freeMapItem(mapMetaData, itemCount);  /* Free mapMetaData before returning */
                return NULL;
            }
        }
    }

    /* Free mapMetaData if no matching position is found */
    freeMapItem(mapMetaData, itemCount);
    /* Return NULL if no matching position is found */
    return NULL;
}


/*
    Frees the memory allocated for map metadata. Ensures that each string in the mapMetaData
    array and the array itself are properly deallocated. Handles the case where mapMetaData is NULL.

*/
void freeMapItem(char** mapMetaData, int itemCount) {
    if (mapMetaData != NULL) {
        for (int i = 0; i < itemCount; i++) {
            if (mapMetaData[i] != NULL) {
                free(mapMetaData[i]);
                mapMetaData[i] = NULL;
            }
        }
        free(mapMetaData);
    } else {
        // Optional: Print a message or handle the case where mapMetaData is NULL
    }
}
