#include "player.h"
#include <stdio.h>

void initializedPlayer(Player *player, int x, int y){
    // initialzing player with initial x and y coordinate
    player->x = x; 
    player->y= y; 
};
void updatePlayerPosition(Player *player, int newX, int newY){
    player->x = newX; // updating x coordinate
    player->y = newY; // updating y coordinate
};
void displayPlayerPosition(Player *player){
    // display current player position(x, y)
    printf("Player Position:(%d,%d)\n", player->x, player->y);
};