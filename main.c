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