#ifndef INVENTORY_H
#define INVENTORY_H

#include "item.h"
#include <time.h>

typedef struct {
    ItemNode* head;
} Inventory;

Inventory* createInventory();

void freeInventory(Inventory* inventory);

int addItem(Inventory* inventory, int id, char* name, int quantity, float value);

int removeItem(Inventory* inventory, int id);

int updateQuantity(Inventory* inventory, int id, int newQuantity);

ItemNode* findHighValueItem(ItemNode* head, ItemNode* currentBest);

void sortInventoryByValue(Inventory* inventory);

void sortInventoryByQuantity(Inventory* inventory);

void saveToFile(Inventory* inventory, char* filename);

void loadFromFile(Inventory* inventory, char* filename);

void saveUndoState(Inventory* inventory);

void undo(Inventory* inventory);

void redo(Inventory* inventory);

void initializeUndoRedo();

void freeUndoRedo();

#endif