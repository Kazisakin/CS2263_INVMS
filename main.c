#include "inventory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    Inventory* inventory = createInventory();
    initializeUndoRedo();
    int choice;
    int id;
    char name[50];
    int quantity;
    float value;
    char filename[50];

    while (1) {
        printf("\n1. Add Item\n");
        printf("2. Remove Item\n");
        printf("3. Update Quantity\n");
        printf("4. Display All Items\n");
        printf("5. Find Highest Value\n");
        printf("6. Sort Items By Value\n");
        printf("7. Sort Items By Quantity\n");
        printf("8. Save\n");
        printf("9. Load\n");
        printf("10. Undo\n");
        printf("11. Redo\n");
        printf("12. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("That is not a valid selection. Please choose an option from the menu.\n");
            while (getchar() != '\n');
            continue;
        }

        if (choice == 1) {
            printf("Enter ID: ");
            if (scanf("%d", &id) != 1) {
                printf("This must be a valid integer ID.\n");
                while (getchar() != '\n');
                continue;
            }
            printf("Enter Name: ");
            scanf("%s", name);
            printf("Enter Quantity: ");
            if (scanf("%d", &quantity) != 1) {
                printf("Quantity must be an integer.\n");
                while (getchar() != '\n');
                continue;
            }
            printf("Enter Value: ");
            if (scanf("%f", &value) != 1) {
                printf("Value must be numeric.\n");
                while (getchar() != '\n');
                continue;
            }
            saveUndoState(inventory);
            if (addItem(inventory, id, name, quantity, value)) {
                printf("Item successfully added!\n");
            } else {
                ItemNode* current = inventory->head;
                int idExists = 0;
                int nameExists = 0;
                while (current != NULL) {
                    if (current->id == id) {
                        idExists = 1;
                    }
                    if (strcmp(current->name, name) == 0) {
                        nameExists = 1;
                    }
                    current = current->next;
                }
                if (idExists) {
                    printf("The ID %d is already taken!\n", id);
                } else if (nameExists) {
                    printf("The name '%s' is already in use!\n", name);
                } else {
                    printf("ID, quantity, and value cannot be negative, and the name cannot be empty.\n");
                }
            }
            printInventory(inventory->head);
        } else if (choice == 2) {
            printf("Enter ID to remove: ");
            if (scanf("%d", &id) != 1) {
                printf("This must be a valid integer ID.\n");
                while (getchar() != '\n');
                continue;
            }
            saveUndoState(inventory);
            if (removeItem(inventory, id)) {
                printf("Item removed successfully.\n");
            } else {
                printf("That ID was not found in the inventory.\n");
            }
            printInventory(inventory->head);
        } else if (choice == 3) {
            printf("Enter ID: ");
            if (scanf("%d", &id) != 1) {
                printf("ID must be an integer!\n");
                while (getchar() != '\n');
                continue;
            }
            printf("Enter new quantity: ");
            if (scanf("%d", &quantity) != 1) {
                printf("Please provide a valid integer for the new quantity.\n");
                while (getchar() != '\n');
                continue;
            }
            saveUndoState(inventory);
            if (updateQuantity(inventory, id, quantity)) {
                printf("Quantity updated successfully.\n");
            } else {
                printf("That ID was not found in the inventory.\n");
            }
            printInventory(inventory->head);
        } else if (choice == 4) {
            printInventory(inventory->head);
        } else if (choice == 5) {
            ItemNode* highest = findHighValueItem(inventory->head, NULL);
            if (highest != NULL) {
                printf("Highest value item: %d %s %d %.2f\n", highest->id, highest->name, highest->quantity, highest->value);
            } else {
                printf("No items currently exist in the inventory.\n");
            }
        } else if (choice == 6) {
            saveUndoState(inventory);
            sortInventoryByValue(inventory);
            printf("Inventory successfully sorted by value.\n");
            printInventory(inventory->head);
        } else if (choice == 7) {
            saveUndoState(inventory);
            sortInventoryByQuantity(inventory);
            printf("Inventory successfully sorted by quantity.\n");
            printInventory(inventory->head);
        } else if (choice == 8) {
            printf("Enter filename: ");
            scanf("%s", filename);
            saveToFile(inventory, filename);
            printf("Inventory has been successfully saved.\n");
            printInventory(inventory->head);
        } else if (choice == 9) {
            printf("Enter filename: ");
            scanf("%s", filename);
            saveUndoState(inventory);
            loadFromFile(inventory, filename);
            printf("Inventory has been successfully loaded.\n");
            printInventory(inventory->head);
        } else if (choice == 10) {
            undo(inventory);
            printf("Undo operation performed successfully.\n");
            printInventory(inventory->head);
        } else if (choice == 11) {
            redo(inventory);
            printf("Redo operation performed successfully.\n");
            printInventory(inventory->head);
        } else if (choice == 12) {
            break;
        } else {
            printf("Please pick a valid number between 1 and 12!\n");
        }
        while (getchar() != '\n');
    }

    freeUndoRedo();
    freeInventory(inventory);
    return 0;
}
