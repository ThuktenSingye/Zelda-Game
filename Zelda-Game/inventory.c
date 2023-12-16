
#include "inventory.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** createInventory(){
    char** inventory;

    // allocate for rows
    inventory = (char**)malloc(sizeof(char*) * MAX_INVENTORY_SIZE);
    // for column
    for(int i =0; i< MAX_INVENTORY_SIZE; i++){
        inventory[i] = (char*)malloc(sizeof(char) * MAX_TREASURE_NAME_LENGTH);
        // initialized with emoty 
        inventory[i][0] = '\0';
    }

    return inventory;
}
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

void displayInventoryList(char **inventory){
    for(int i=0; i< MAX_INVENTORY_SIZE; i++){
        printf("%s\t", inventory[i]);
    }
}

int getInventoryItemLength(char **inventory){
    int itemCount = 0;
    for(int i =0; i< MAX_INVENTORY_SIZE; i++){
        if(strlen(inventory[i]) > 0){
            itemCount ++;
        }
    }
    return itemCount;
}

void destroyInventory(char** inventory) {
    for (int i = 0; i < MAX_INVENTORY_SIZE; i++) {
        free(inventory[i]);
    }
    free(inventory);
}


