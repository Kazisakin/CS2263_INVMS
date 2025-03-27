#include "filesystem.h"

int main(void) {
    Directory *root = NULL;
    initializeRoot(&root);

    while (1) {
        int choice = 0;
        printf("\n========== FILE SYSTEM MENU ==========\n");
        printf("1) Create a New Directory\n");
        printf("2) Create a New File\n");
        printf("3) List Contents (recursive)\n");
        printf("4) Search for an Item\n");
        printf("5) Exit\n");
        printf("======================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (choice == 5) {
            printf("Exiting program. Goodbye!\n");
            break;
        }

        switch (choice) {
            case 1: {
                char parentName[NAME_LENGTH], dirName[NAME_LENGTH];
                printf("Enter the parent directory name (or 'root' for the root directory): ");
                fgets(parentName, NAME_LENGTH, stdin);
                parentName[strcspn(parentName, "\n")] = '\0';
                printf("Enter the new directory name: ");
                fgets(dirName, NAME_LENGTH, stdin);
                dirName[strcspn(dirName, "\n")] = '\0';
                Directory *parentDir = findDirectory(root, parentName);
                if (!parentDir) {
                    printf("Parent directory '%s' not found.\n", parentName);
                } else {
                    if (createDirectory(parentDir, dirName) == 0) {
                        printf("Directory '%s' created under '%s'.\n", dirName, parentName);
                    }
                }
                break;
            }
            case 2: {
                char parentName[NAME_LENGTH], fileName[NAME_LENGTH];
                int size = 0;

                printf("Enter the name of the parent directory (type 'root' for the root): ");
                fgets(parentName, NAME_LENGTH, stdin);
                parentName[strcspn(parentName, "\n")] = '\0';

                printf("Enter the new file name: ");
                fgets(fileName, NAME_LENGTH, stdin);
                fileName[strcspn(fileName, "\n")] = '\0';

                printf("Enter the file size (integer): ");
                scanf("%d", &size);
                while (getchar() != '\n');

                Directory *parentDir = findDirectory(root, parentName);
                if (!parentDir) {
                    printf("Parent directory '%s' not found.\n", parentName);
                } else {
                    if (createFile(parentDir, fileName, size) == 0) {
                        printf("File '%s' created under '%s'.\n", fileName, parentName);
                    }
                }

                break;
            }
            case 3: {
                char dirName[NAME_LENGTH];
                printf("Enter the directory to list (type 'root' for the root): ");
                fgets(dirName, NAME_LENGTH, stdin);
                dirName[strcspn(dirName, "\n")] = '\0';

                Directory *targetDir = findDirectory(root, dirName);
                if (!targetDir) {
                    printf("Directory '%s' not found.\n", dirName);
                } else {
                    listDirectory(targetDir, 0);
                }
                break;
            }
            case 4: {
                break;
            }
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    freeDirectory(root);
    return 0;
}