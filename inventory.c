#include "inventory.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static ItemNode* copyList(ItemNode* src) {
    if (!src) return NULL;
    ItemNode* node = (ItemNode*)malloc(sizeof(ItemNode));
    node->id = src->id;
    strncpy(node->name, src->name, 49);
    node->name[49] = '\0';
    node->quantity = src->quantity;
    node->value = src->value;
    node->next = copyList(src->next);
    return node;
}

Inventory* createInventory() {
    Inventory* inv = (Inventory*)malloc(sizeof(Inventory));
    inv->head = NULL;
    return inv;
}

void freeInventory(Inventory* inv) {
    ItemNode* current = inv->head;
    while (current) {
        ItemNode* temp = current->next;
        free(current);
        current = temp;
    }
    free(inv);
}

void addItem(Inventory* inv, int id, const char* name, int quantity, float value) {
    ItemNode* node = (ItemNode*)malloc(sizeof(ItemNode));
    node->id = id;
    strncpy(node->name, name, 49);
    node->name[49] = '\0';
    node->quantity = quantity;
    node->value = value;
    node->next = inv->head;
    inv->head = node;
}

void removeItem(Inventory* inv, int id) {
    ItemNode* current = inv->head;
    ItemNode* prev = NULL;
    while (current) {
        if (current->id == id) {
            if (prev) {
                prev->next = current->next;
            } else {
                inv->head = current->next;
            }
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }
}

void updateQuantity(Inventory* inv, int id, int newQuantity) {
    ItemNode* current = inv->head;
    while (current) {
        if (current->id == id) {
            current->quantity = newQuantity;
            break;
        }
        current = current->next;
    }
}

static void splitList(ItemNode* source, ItemNode** front, ItemNode** back) {
    ItemNode* slow = source;
    ItemNode* fast = source->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

static ItemNode* mergeById(ItemNode* a, ItemNode* b) {
    if (!a) return b;
    if (!b) return a;
    if (a->id <= b->id) {
        a->next = mergeById(a->next, b);
        return a;
    } else {
        b->next = mergeById(a, b->next);
        return b;
    }
}

static ItemNode* mergeSortById(ItemNode* head) {
    if (!head || !head->next) return head;
    ItemNode* front = NULL;
    ItemNode* back = NULL;
    splitList(head, &front, &back);
    front = mergeSortById(front);
    back = mergeSortById(back);
    return mergeById(front, back);
}

void sortInventory(Inventory* inv) {
    inv->head = mergeSortById(inv->head);
}

ItemNode* findHighestValue(Inventory* inv) {
    if (!inv->head) return NULL;
    ItemNode* current = inv->head;
    ItemNode* best = inv->head;
    while (current) {
        if (current->value > best->value) {
            best = current;
        }
        current = current->next;
    }
    return best;
}

void saveToFile(Inventory* inv, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) return;
    int total = 0;
    ItemNode* c = inv->head;
    while (c) {
        total++;
        c = c->next;
    }
    fprintf(file, "%d\n", total);
    c = inv->head;
    while (c) {
        fprintf(file, "%d,%s,%d,%.2f\n", c->id, c->name, c->quantity, c->value);
        c = c->next;
    }
    fclose(file);
}

void loadFromFile(Inventory* inv, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return;
    int total = 0;
    fscanf(file, "%d\n", &total);
    for (int i = 0; i < total; i++) {
        int tId;
        char tName[50];
        int tQty;
        float tVal;
        int r = fscanf(file, "%d,%49[^,],%d,%f\n", &tId, tName, &tQty, &tVal);
        if (r == 4) {
            addItem(inv, tId, tName, tQty, tVal);
        }
    }
    fclose(file);
}

static Inventory** undoStack = NULL;
static Inventory** redoStack = NULL;
static int undoCount = 0;
static int redoCount = 0;
static int undoCap = 0;
static int redoCap = 0;

static Inventory* copyInventory(Inventory* source) {
    Inventory* newInv = createInventory();
    newInv->head = copyList(source->head);
    return newInv;
}

void initUndoSystem() {
    undoCap = 5;
    redoCap = 5;
    undoStack = (Inventory**)malloc(sizeof(Inventory*) * undoCap);
    redoStack = (Inventory**)malloc(sizeof(Inventory*) * redoCap);
    undoCount = 0;
    redoCount = 0;
}

static void expandUndoStack() {
    undoCap *= 2;
    Inventory** temp = (Inventory**)realloc(undoStack, undoCap * sizeof(Inventory*));
    if (!temp) exit(1);
    undoStack = temp;
}

static void expandRedoStack() {
    redoCap *= 2;
    Inventory** temp = (Inventory**)realloc(redoStack, redoCap * sizeof(Inventory*));
    if (!temp) exit(1);
    redoStack = temp;
}

static void freeStack(Inventory** stack, int count) {
    for (int i = 0; i < count; i++) {
        freeInventory(stack[i]);
    }
}

void freeUndoSystem() {
    freeStack(undoStack, undoCount);
    freeStack(redoStack, redoCount);
    free(undoStack);
    free(redoStack);
}

static void pushUndo(Inventory* inv) {
    if (undoCount >= undoCap) expandUndoStack();
    undoStack[undoCount++] = copyInventory(inv);
}

static Inventory* popUndo() {
    if (undoCount == 0) return NULL;
    return undoStack[--undoCount];
}

static void clearRedoStack() {
    freeStack(redoStack, redoCount);
    redoCount = 0;
}

static void pushRedo(Inventory* inv) {
    if (redoCount >= redoCap) expandRedoStack();
    redoStack[redoCount++] = copyInventory(inv);
}

static Inventory* popRedo() {
    if (redoCount == 0) return NULL;
    return redoStack[--redoCount];
}

void saveUndoState(Inventory* inv) {
    pushUndo(inv);
    clearRedoStack();
}

void undo(Inventory* inv) {
    if (undoCount == 0) return;
    Inventory* oldCurrent = copyInventory(inv);
    Inventory* revertTo = popUndo();
    freeInventory(inv);
    inv->head = revertTo->head;
    free(revertTo);
    pushRedo(oldCurrent);
}


void redo(Inventory* inv) {
    if (redoCount == 0) return;
    Inventory* oldCurrent = copyInventory(inv);
    Inventory* next = popRedo();
    freeInventory(inv);
    inv->head = next->head;
    free(next);
    pushUndo(oldCurrent);
}
