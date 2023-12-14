#include "game.h"
#include "player.h"
#include "mapmaker.h"
#include "terminal.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void startGame() {
    // Your game logic goes here
    printf("The game has started!\n");
    // first setup the game like setting creating and displaying map
    setUpGame();

}

void setUpGame(){
    printf("Setting up the game\n");
    int itemCount, mapRowSize, mapColSize;

    // setting up the player
    Player mainPlayer;
    initializedPlayer(&mainPlayer, 0, 0);
    displayPlayerPosition(&mainPlayer);
    // get map meta data 
    char** mapMetaData = getItemData(&itemCount, &mapRowSize, &mapColSize);
    
    printf("%s\n",mapMetaData[0]);

    // outputting the meta data
    // for (int i = 0; i < itemCount; i++) {
    //     printf("%s\n", mapMetaData[i]);
    // }

    // creating the map
    char** map = createMap(mapMetaData,mapRowSize, mapColSize, itemCount);
    // display the map
    // displayMap(map, mapRowSize, mapColSize);
    runGame(map, mapRowSize, mapColSize);

    


};

void displayMap(char** map, int mapRowSize, int mapColSize){
    // display map
    printf("This is the world map:\n");
    for (int i = 0; i < mapRowSize; i++) {
        for (int j = 0; j < mapColSize; j++) {
            if (map[i][j] == '\0') {
                printf(". ");
            } else {
                printf("%c ", map[i][j]);
            }
        }
        printf("\n");
    }

}

char** createMap(char** mapMetaData, int mapRowSize, int mapColSize, int itemCount){
    // this function will be used to create dynamic 2D map
    char** map = (char**)malloc(sizeof(char*) * mapRowSize); // allocating for rows

    // allocating memory for each rows
    for(int i=0; i< mapRowSize; i++){
        map[i] = (char*)malloc(sizeof(char) * mapColSize);
    };

    // parse and allocate item to the map
    for(int i =0; i< itemCount; i++){
        int x, y;
        char type, description[MAX_STRING_LENGTH];
        // reading x, y, type and description
        sscanf(mapMetaData[i], "%d,%d %c %[^\n]", &x, &y, &type, description);
        // allocating type to map based on its (x, y)
        map[x][y] = type;
    }


    return map;
};

void runGame(char** map, int mapRowSize, int mapColSize){
    // this is where main game logic lies
    bool gameEnded = false;
    bool hasSword = false;

    // disabling buffering and echoing
    disableBuffer();
    while(!gameEnded){
        printf("Game running\n");
        displayMap(map, mapRowSize, mapColSize);
        printf("\n\nWhere do you want to go?\nW, A, S, D, (Q)uit, (I)nventory\n");
        // get an input from user using terminal
        char input;
        scanf("%c", &input);
        printf("The user has entered %c\n", input);

         


        gameEnded = true;
    }
    enableBuffer();
}