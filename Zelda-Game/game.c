#include "game.h"
#include "player.h"
#include "mapmaker.h"
#include "terminal.h"
#include "inventory.h"
#include "ucpSleep.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/*
    This function serves as the entry point for running the game. It calls 
    the setUpGame() function to initialize and start the game.
*/
void runGame() 
{
    /* First setup the game like setting, creating, and displaying the map */
    setUpGame();
    
}


/*  
    This function sets up the game environment by obtaining map metadata, creating the game map 
    and inventory, parsing the initial player position and type, initializing the player, and 
    starting the game with the provided settings.

*/
void setUpGame()
{
    int itemCount, mapRowSize, mapColSize;

    /* Get map metadata and initialize variables */
    char** mapMetaData = getItemData(&itemCount, &mapRowSize, &mapColSize);
    
    /* Create the game map and inventory */
    char** map = createMap(mapMetaData, mapRowSize, mapColSize, itemCount);
    char** inventory = createInventory();

    /* Parse initial player position and type */
    int initialX, initialY;
    char type, description[MAX_STRING_LENGTH];
    sscanf(mapMetaData[0], "%d,%d %c %[^\n]", &initialX, &initialY, &type, description);
    
    /* Initialize the player */
    Player mainPlayer;
    initializedPlayer(&mainPlayer, initialX, initialY);
    
    /* Initialize map information */
    MapInfo mapInfo = 
    {
        .map = map,
        .mapMetaData = mapMetaData,
        .mapRowSize = mapRowSize,
        .mapColSize = mapColSize,
        .itemCount = itemCount
    };

    /* Start the game with initialized settings */
    startGame(&mapInfo, &mainPlayer, inventory);

    /* Free allocated memory for map metadata */
    freeMapItemData(mapMetaData, itemCount);
}

/*
    Displays the game map on the terminal, showing the layout of the current game world. 
    Empty squares are represented by periods ('.'), and other characters represent different 
    elements in the game.
*/
void displayMap(char** map, int mapRowSize, int mapColSize)
{
    /* Display the map */
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

/*
    Allocates memory for the game map, reads item data from map metadata, and assigns items to 
    their corresponding positions on the map based on x and y coordinates.
*/
char** createMap(char** mapMetaData, int mapRowSize, int mapColSize, int itemCount)
{
    /* Allocate memory for the map */
    char** map = (char**)malloc(sizeof(char*) * mapRowSize);
    
    /* Allocate memory for each row */
    for(int i = 0; i < mapRowSize; i++){
        map[i] = (char*)malloc(sizeof(char) * mapColSize);
    }

    /* Parse and allocate items to the map */
    for(int i = 0; i < itemCount; i++){
        int x, y;
        char type, description[MAX_STRING_LENGTH];
        /* Read x, y, type, and description */
        sscanf(mapMetaData[i], "%d,%d %c %[^\n]", &x, &y, &type, description);
        /* Allocate type to map based on its (x, y) */
        map[x][y] = type;
    }
 
    return map;
}

/*
    Initiates the main game loop, processing player input and updating the game state accordingly.
    Manages player movement, interactions with map elements, inventory handling, and the overall flow of the game.
*/
void startGame(MapInfo *mapInfo, Player* player, char** inventory) 
{
    /* Game variables and flags */
    bool gameEnded = false;
    bool hasSword = false;
    bool foundDummy = false;
    int dummyLife = 10;
    char currentPlayerDirection = '>';
    int newPosX = player->x;
    int newPosY = player->y;

    /* Display the initial world map */
    printf("This is the world map:\n");
    displayMap(mapInfo->map, mapInfo->mapRowSize, mapInfo->mapColSize);

    /* Disable terminal buffering and echoing */
    disableBuffer();
    
    // Main game loop
    while (!gameEnded) 
    {
        /* Display movement options to the player */
        printf("\n\nWhere do you want to go?\nW, A, S, D, (Q)uit, (I)nventory\n\n");

        /* Get input from the user using terminal */
        char input;
        if (scanf("%c", &input) != 1) 
        {
            fprintf(stderr, "Error reading input.\n");
            exit(EXIT_FAILURE);
        }
        clearScreen();

        /* Process player input */
        switch (input) {
            /* Cases for different player actions */
            case 'w':
                /* Move the player north */
                printf("Going North\n");
                newPosX--;
                currentPlayerDirection = '^';
                break;
            case 's':
                /* Move the player south */
                printf("Going South\n");
                newPosX++;
                currentPlayerDirection = 'v';
                break;
            case 'a':
                /* Move the player west */
                printf("Going West\n");
                newPosY--;
                currentPlayerDirection = '<';
                break;
            case 'd':
                /* Move the player east */
                printf("Going East\n");
                newPosY++;
                currentPlayerDirection = '>';
                break;
            case 'i':
                /* Display the inventory list */
                displayInventoryList(inventory);
                break;
            case ' ':
                /* Perform an action when the space key is pressed */
                if (hasSword) {
                    if (!foundDummy) 
                    {
                        /* Attack the square infront */
                        attackSquare(currentPlayerDirection);
                    } 
                    else 
                    {
                        /* Attack the training dummies */
                        gameEnded = destroyDummy(&dummyLife);
                        if (gameEnded) {
                            printf("The Training Dummies have been destroyed!\nYou Win!\n");
                        }
                    }
                }
                break;
            case 'q':
                /* Quit the game */
                printf("Quitting the game\n");
                gameEnded = true;
                break;
            default:
                /* Ignore other keys; nothing should change in the world map */
                printf("Ignoring other key, nothing should change in the world map\n");
                break;
        }


        /* Check if the new position is within boundaries to avoid segmentation fault */
        if (newPosX >= 0 && newPosX < mapInfo->mapRowSize && newPosY >= 0 && newPosY < mapInfo->mapColSize) 
        {
            /* Check map elements and update game state */
            switch (mapInfo->map[newPosX][newPosY]) 
            {
                case '\0':
                    /* Empty square, move the player to the new position */
                    movePlayer(player, mapInfo->map, newPosX, newPosY, currentPlayerDirection);
                    foundDummy = false;
                    break;
                case '#':
                    /* Wall square, stay in the current position */
                    newPosX = player->x;
                    newPosY = player->y;
                    mapInfo->map[newPosX][newPosY] = currentPlayerDirection;
                    foundDummy = false;
                    break;
                case 'T':
                    /* Treasure square, move the player, collect treasure, and update inventory */
                    movePlayer(player, mapInfo->map, newPosX, newPosY, currentPlayerDirection);
                    /* Collect treasure description */
                    char* treasure = getObjectDescription(newPosX, newPosY);
                    printf("You found a Treasure! %s\n", treasure);
                    foundDummy = false;
                    collectTreasure(inventory, treasure);
                    /* Free treasure memory */
                    free(treasure);
                    break;
                case 'O':
                    /* Old man square, provide information and give sword if the player doesn't have one */
                    if (!hasSword) 
                    {
                        /* Get the object description */
                        char* objectDescription = getObjectDescription(newPosX, newPosY);
                        if (objectDescription != NULL) 
                        {
                            printf("You see an old man: He says: %s\n", objectDescription);
                            /* Give sword to the player */
                            hasSword = true;
                            /* Free the object description memory */
                            free(objectDescription);
                        } 
                        else 
                        {
                            /* Handle error or memory allocation failure when getting object description */
                            printf("Error: Failed to get object description.\n");
                        }
                    }
                    /* Set the player's position to the initial position */
                    newPosX = player->x;
                    newPosY = player->y;
                    mapInfo->map[newPosX][newPosY] = currentPlayerDirection;
                    foundDummy = false;
                    break;
                case 'D':
                    /* Dummy square, provide information and set foundDummy to true */
                    char* dummyDescription = getObjectDescription(newPosX, newPosY);
                    printf("You see %s\n", dummyDescription);
                    foundDummy = true;
                    /* Keep the player at the initial position */
                    newPosX = player->x;
                    newPosY = player->y;
                    mapInfo->map[newPosX][newPosY] = currentPlayerDirection;
                    free(dummyDescription);
                    break;
                default:
                    /* Default case, no action needed */
                    break;
            }

        } else 
        {
            /* Handle reaching the edge or do nothing */
            newPosX = player->x;
            newPosY = player->y;
            mapInfo->map[newPosX][newPosY] = currentPlayerDirection;
        }

        /* Display the updated world map */
        printf("\nThis is the world map:\n");
        displayMap(mapInfo->map, mapInfo->mapRowSize, mapInfo->mapColSize);
    }

    /* Free allocated memory and enable terminal buffering */
    freeMap(mapInfo->map, mapInfo->mapRowSize);
    destroyInventory(inventory);  
    enableBuffer();
}

/*
    Simulates the destruction of a training dummy during combat. Reduces the dummy's hitpoints 
    and checks if the dummy is destroyed, signaling a win condition.
*/
bool destroyDummy(int *dummyLife)
{
    if (*dummyLife > 0)
    {
        (*dummyLife)--;
        printf("You hit the Training Dummy!\nIt has %d hitpoints remaining\n", *dummyLife);
        if(*dummyLife == 0)
        {
            /* Win game */
            return true;
        }
        return false;
    }
    return false;
}

/*
    Simulates the player attacking a square in the game world. Depending on 
    the player's direction, it displays a vertical or horizontal line to represent the attack.
*/
void attackSquare(char currentPlayerDirection) 
{
    if (currentPlayerDirection == '^' || currentPlayerDirection == 'v') 
    {
        ucpSleep(0.5);
        printf("|\n");
    } 
    else 
    {
        ucpSleep(0.5);
        printf("-\n");
    }
}

/*
    Frees the memory allocated for the game map. Releases both the rows and columns of the 2D map array.
*/
void freeMap(char** map, int mapRowSize)
{
    for (int i = 0; i < mapRowSize; i++) 
    {
        free(map[i]);
    }
    free(map);
}

/*
    Frees the memory allocated for map item data obtained from map metadata. Releases the memory for 
    each string in the array of strings and the array itself.
*/
void freeMapItemData(char** table, int itemCount) 
{
    for (int i = 0; i < itemCount; i++) 
    {
        free(table[i]);  /* Free each string in the table */
    }
    free(table);  /* Free the array of strings */
}

/*
    Clears the terminal screen, providing a cleaner interface for displaying the game.
    Uses the system command "clear" to clear the screen, and reports an error if the command fails.
*/
void clearScreen() 
{
    if (system("clear") != 0) 
    {
        printf("Error clearing the screen.\n");
    }
}
