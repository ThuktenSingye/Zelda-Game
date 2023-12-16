
#ifndef INVENTORY_H
#define INVENTORY_H

#define MAX_INVENTORY_SIZE 10
#define MAX_TREASURE_NAME_LENGTH 50

char **createInventory();
void addItemToInventory(char **inventory, char *treasure);
int getInventoryItemLength(char **inventory);
void displayInventoryList(char **inventory);
void destroyInventory(char **inventory);

#endif