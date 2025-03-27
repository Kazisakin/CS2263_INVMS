#include "filesystem.h"

void initializeRoot(Directory **root) {
    *root = (Directory*)malloc(sizeof(Directory));
    if (!(*root)) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    strcpy((*root)->name, "root");
    (*root)->parent = NULL;
    (*root)->subdirs = NULL;
    (*root)->nextSibling = NULL;
    (*root)->files = NULL;

}

int createDirectory(Directory *parent, const char *name) {
    if (!parent || !name || strlen(name) == 0) {
        printf("Invalid directory creation request.\n");
        return -1;
    }
    if (directoryExists(parent->subdirs, name) || fileExists(parent->files, name)) {
        printf("Error: An item named '%s' already exists in directory '%s'.\n",
               name, parent->name);
        return -1;
    }
    Directory *newDir = (Directory*)malloc(sizeof(Directory));
    if (!newDir) {
        printf("Memory allocation failed.\n");
        return -1;
    }
    strcpy(newDir->name, name);
    newDir->parent = parent;
    newDir->subdirs = NULL;
    newDir->nextSibling = NULL;
    newDir->files = NULL;
    newDir->nextSibling = parent->subdirs;
    parent->subdirs = newDir;
    return 0;
}
