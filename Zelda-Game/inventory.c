
#include "inventory.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    Allocates memory for the player's inventory, which is represented as a 2D array of characters.
    Each row corresponds to an inventory slot, and each column stores the name of a treasure item. 
    The inventory is initialized with empty strings for each slot.
*/
char** createInventory(){
    char** inventory;

    /* Allocate memory for row*/
    inventory = (char**)malloc(sizeof(char*) * MAX_INVENTORY_SIZE);
    
    /* Allocate memory for column*/
    for(int i =0; i< MAX_INVENTORY_SIZE; i++){
        inventory[i] = (char*)malloc(sizeof(char) * MAX_TREASURE_NAME_LENGTH);
        /* Initialized with null character*/ 
        inventory[i][0] = '\0';
    }

    return inventory;
}


/*
    Adds a treasure item to the player's inventory. It searches for an empty slot in the inventory, 
    copies the treasure name into that slot, and ensures null-termination to prevent memory issues.
*/
void addItemToInventory(char **inventory, char* treasure){
    // Find an empty slot in the inventory
    for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
        // Check if the current slot is empty (has a length of 0)
        if (strlen(inventory[i]) == 0) {
            // Copy the treasure name into the inventory
            strncpy(inventory[i], treasure, MAX_TREASURE_NAME_LENGTH - 1);
            // Ensure null-termination to ensure the last string
            inventory[i][MAX_TREASURE_NAME_LENGTH - 1] = '\0';       
            break;
        }
    }
}


/* Displays the contents of the player's inventory on the terminal. Prints each item in a tab-separated format. */

void displayInventoryList(char **inventory){
    for(int i=0; i< MAX_INVENTORY_SIZE; i++){
        printf("%s\t", inventory[i]);
    }
}


/*
    Counts and returns the number of items in the player's inventory. 
    Iterates through the inventory, checking the length of each item's name to determine if the slot is occupied.
*/
int getInventoryItemLength(char **inventory){
    int itemCount = 0;
    for(int i =0; i< MAX_INVENTORY_SIZE; i++){
        if(strlen(inventory[i]) > 0){
            itemCount ++;
        }
    }
    return itemCount;
}


/*
    Frees the memory allocated for the player's inventory. Releases both the rows and columns of the 2D array,
    ensuring that all memory used for storing treasure names is properly deallocated.

*/
void destroyInventory(char** inventory) {
    for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
        free(inventory[i]);
    }
    free(inventory);
}


