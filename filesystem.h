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

int createFile(Directory *parent, const char *name, int size);

void listDirectory(const Directory *dir, int depth);

void freeDirectory(Directory *dir);

Directory* findDirectory(Directory *start, const char *name);

int directoryExists(Directory *start, const char *name);

int fileExists(File *head, const char *name);

#endif
