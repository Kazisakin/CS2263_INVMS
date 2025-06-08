#include "item.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

ItemNode* createItem(int id, char* name, int quantity, float value) {
    ItemNode* newItem = (ItemNode*)malloc(sizeof(ItemNode));
    newItem->id = id;
    strncpy(newItem->name, name, 49);
    newItem->name[49] = '\0';
    newItem->quantity = quantity;
    newItem->value = value;
    newItem->next = NULL;
    return newItem;
}

void freeItemList(ItemNode* head) {
    ItemNode* current = head;
    while (current != NULL) {
        ItemNode* next = current->next;
        free(current);
        current = next;
    }
}

void printInventory(ItemNode* head) {
    ItemNode* current = head;
    if (current == NULL) {
        printf("No items in inventory.\n");
    }
    while (current != NULL) {
        printf("%d %s %d %.2f\n", current->id, current->name, current->quantity, current->value);
        current = current->next;
    }
}