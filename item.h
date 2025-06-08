#ifndef ITEM_H
#define ITEM_H

typedef struct ItemNode {
    int id;
    char name[50];
    int quantity;
    float value;
    struct ItemNode* next;
} ItemNode;

ItemNode* createItem(int id, char* name, int quantity, float value);

void freeItemList(ItemNode* head);

void printInventory(ItemNode* head);

#endif