#ifndef PLAYER_H
#define PLAYER_H


typedef struct{
    int x; /* to store x coordinate */
    int y; /* to store y-coordinate */
} Player;


void initializedPlayer(Player *player, int x, int y);
void updatePlayerPosition(Player *player, int newX, int newY);
void displayPlayerPosition(Player *player);
void movePlayer(Player *player, char **map, int newPosX, int newPosY, char currentPlayerDirection);
void collectTreasure(char** inventory, char *treasure); 


#endif