#include "player.h"
#include "inventory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Initializes the player structure with the provided x and y coordinates.
    Sets the initial position of the player on the game map.
 
*/
void initializedPlayer(Player *player, int x, int y){
    /* Initialzed player with initial x and y coordinate */
    player->x = x; 
    player->y= y; 
};

/*
    Updates the player's position with the provided x and y coordinates.
*/
void updatePlayerPosition(Player *player, int newX, int newY){
    player->x = newX; /* updating x coordinate */
    player->y = newY; /* updating y coordinate */
};

/*
    Displays the current position of the player on the game map.
*/
void displayPlayerPosition(Player *player){
    printf("Player Position:(%d,%d)\n", player->x, player->y);
}

/*
    Moves the player to a new position on the game map.
    Updates the player's position, direction, and clears the previous position on the map.
*/
void movePlayer(Player *player, char **map, int newPosX, int newPosY, char currentPlayerDirection){
    map[newPosX][newPosY] = currentPlayerDirection;
    map[player->x][player->y] = '\0'; 
    updatePlayerPosition(player, newPosX, newPosY);
}

/*
    Collects a treasure and adds it to the player's inventory if there is space.
    Checks the length of the inventory before adding to prevent exceeding the maximum capacity.
    Prints a message if the inventory is full.
*/
void collectTreasure(char** inventory, char *treasure){
    /* Before adding check if length of inventory is greater than 10 */
    if((getInventoryItemLength(inventory)) <=10){
        addItemToInventory(inventory, treasure);
    }else{
        printf("Inventory is full");
    }
}
