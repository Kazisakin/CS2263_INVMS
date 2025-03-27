#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LENGTH 64

typedef struct File {
    char name[NAME_LENGTH];
    int size;
    struct File *next;
} File;

typedef struct Directory {
    char name[NAME_LENGTH];
    struct Directory *parent;
    struct Directory *subdirs;
    struct Directory *nextSibling;
    File *files;
} Directory;

void initializeRoot(Directory **root);


int createDirectory(Directory *parent, const char *name);

#endif
