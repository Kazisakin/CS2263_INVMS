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

                break;
            }
            case 3: {

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