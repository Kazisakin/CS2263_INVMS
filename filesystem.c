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
