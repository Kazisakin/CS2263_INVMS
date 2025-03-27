#include "filesystem.h"

void initializeRoot(Directory **root) {
    *root = (Directory*)malloc(sizeof(Directory));
    if (!(*root)) {
        fprintf(stderr, "Memory allocation for root directory failed!\n");
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

int createFile(Directory *parent, const char *name, int size) {
    if (!parent || !name || strlen(name) == 0) {
        printf("Invalid file creation request.\n");
        return -1;
    }
    if (directoryExists(parent->subdirs, name) || fileExists(parent->files, name)) {
        printf("Error: An item named '%s' already exists in directory '%s'.\n",
               name, parent->name);
        return -1;
    }
    File *newFile = (File*)malloc(sizeof(File));
    if (!newFile) {
        printf("Memory allocation failed.\n");
        return -1;
    }
    strcpy(newFile->name, name);
    newFile->size = size;
    newFile->next = parent->files;
    parent->files = newFile;
    return 0;
}

void listDirectory(const Directory *dir, int depth) {
    if (!dir) return;
    printIndent(depth);
    printf("[%s]\n", dir->name);
    File *f = dir->files;
    while (f) {
        printIndent(depth + 1);
        printf("%s (size=%d)\n", f->name, f->size);
        f = f->next;
    }
    Directory *sub = dir->subdirs;
    while (sub) {
        listDirectory(sub, depth + 1);
        sub = sub->nextSibling;
    }
}

void searchItem(const Directory *dir, const char *target, char *path) {
    if (!dir) return;
    char oldPath[1024];
    strcpy(oldPath, path);
    if (strcmp(dir->name, "root") == 0) {
        sprintf(path, "/%s", dir->name);
    } else {
        sprintf(path, "%s/%s", path, dir->name);
    }
    if (strcmp(dir->name, target) == 0) {
        printf("Found directory: %s\n", path);
    }
    File *f = dir->files;
    while (f) {
        if (strcmp(f->name, target) == 0) {
            printf("Found file: %s/%s\n", path, f->name);
        }
        f = f->next;
    }
    Directory *sub = dir->subdirs;
    while (sub) {
        searchItem(sub, target, path);
        sub = sub->nextSibling;
    }
    strcpy(path, oldPath);
}

void freeDirectory(Directory *dir) {
    if (!dir) return;
    Directory *sub = dir->subdirs;
    while (sub) {
        Directory *nextSub = sub->nextSibling;
        freeDirectory(sub);
        sub = nextSub;
    }
    File *f = dir->files;
    while (f) {
        File *nextFile = f->next;
        free(f);
        f = nextFile;
    }
    free(dir);
}

Directory* findDirectory(Directory *start, const char *name) {
    if (!start) return NULL;
    if (strcmp(start->name, name) == 0) {
        return start;
    }
    Directory *found = findDirectory(start->subdirs, name);
    if (found) return found;
    return findDirectory(start->nextSibling, name);
}

int directoryExists(Directory *start, const char *name) {
    while (start) {
        if (strcmp(start->name, name) == 0) {
            return 1;
        }
        start = start->nextSibling;
    }
    return 0;
}

int fileExists(File *head, const char *name) {
    while (head) {
        if (strcmp(head->name, name) == 0) {
            return 1;
        }
        head = head->next;
    }
    return 0;
}

void printIndent(int depth) {
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
}
