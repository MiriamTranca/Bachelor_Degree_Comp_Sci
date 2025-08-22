#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

void displayFilteredEstatesByTypeAndSurface(EstateService* service) {
    char type[20];
    float minSurface;
    printf("Enter estate type: ");
    scanf("%s", type);
    printf("Enter minimum surface: ");
    scanf("%f", &minSurface);

    int count;
    Estate* filtered = getFilteredEstatesByTypeAndSurface(service, type, minSurface, &count);
    for (int i = 0; i < count; i++) {
        printf("Estate Address: %s, Price: %.2f, Surface: %.2f\n", filtered[i].address, filtered[i].price, filtered[i].surface);
    }
    free(filtered);
}

void displayFilteredEstatesByAddress(EstateService* service) {
    char addressSubstring[100];
    printf("Enter address substring: ");
    scanf("%s", addressSubstring);

    int count;
    Estate* filtered = getSortedEstates(service, addressSubstring, &count);
    for (int i = 0; i < count; i++) {
        printf("Estate Address: %s, Price: %.2f, Type: %s\n", filtered[i].address, filtered[i].price, filtered[i].type);
    }
    free(filtered);
}

void displayFilteredEstatesBySurfaceAndPrice(EstateService* service) {
	float surface;
	printf("Enter surface: ");
	scanf("%f", &surface);
	int count;
	Estate* filtered = getSortedEstatesSurfaceAndPrice(service, surface, &count);
	for (int i = 0; i < count; i++) {
		printf("Estate Address: %s, Price: %.2f, Type: %s\n", filtered[i].address, filtered[i].price, filtered[i].type);
	}
	free(filtered);
}

void showMenu() {
    printf("1. Add Estate\n");
    printf("2. Update Estate\n");
    printf("3. Delete Estate\n");
    printf("4. Filter Estates by Address\n");
    printf("5. Filter Estates by Type and Surface\n");
    printf("6. For a given surface, display all offers, sorted ascending by price\n");
    printf("7. Undo\n");
    printf("8. Redo\n");
    printf("0. Exit\n");
}

void handleUserInput(EstateService* service) {
    int choice;
    char address[100], type[20], addressSubstring[100];
    float price, surface;
    char validTypes[3][20] = { "house", "apartment", "penthouse" };
    int valid;
    int ok = 0;
    ActionStack undoStack = createActionStack();
    ActionStack redoStack = createActionStack();
    while (ok == 0) {
        showMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter address, type, surface, price: ");
            scanf("%s %s %f %f", address, type, &surface, &price);
            valid = 0;
            for (int i = 0; i < 3; i++) {
                if (strcmp(type, validTypes[i]) == 0) {
                    valid = 1;
                    break;
                }
            }
            if (!valid) {
                printf("Invalid type. \n");
                break;
            }
            addEstate(service->repo, createEstate(address, type, surface, price));

            //for undo
            Action addAction = { ADD, createEstate(address, type, surface, price), "" };
            pushAction(&undoStack, addAction);
            break;
        case 2:
            printf("Enter address to update: ");
            scanf("%s", address);
            printf("Enter new details: ");
            scanf("%s %f %f", type, &surface, &price);
            valid = 0;
            for (int i = 0; i < 3; i++) {
                if (strcmp(type, validTypes[i]) == 0) {
                    valid = 1;
                    break;
                }
            }
            if (!valid) {
                printf("Invalid type. \n");
                break;
            }
            //for undo
            Estate* oldEstate = findEstateByAddress(service->repo, address);
            Estate oldEstateCopy = *oldEstate;
            Action updateAction = { UPDATE, oldEstateCopy, "" };
            strcpy(updateAction.address, address);
            pushAction(&undoStack, updateAction);

            updateEstate(service->repo, address, createEstate(address, type, surface, price));
            break;
        case 3:
            printf("Enter address to delete: ");
            scanf("%s", address);
            Estate* estateToDelete = findEstateByAddress(service->repo, address);
            if (estateToDelete != NULL) {
                // for undo
                Action deleteAction = { DELETE, *estateToDelete, "" };
                strcpy(deleteAction.address, address);
                pushAction(&undoStack, deleteAction);

                deleteEstate(service->repo, address);
            }
            else {
                printf("Estate not found.\n");
            }
            break;

        case 4:
            displayFilteredEstatesByAddress(service);
            break;
        case 5:
            displayFilteredEstatesByTypeAndSurface(service);
            break;
        case 6:
			displayFilteredEstatesBySurfaceAndPrice(service);
			break;
        case 7:
            undo(service, &undoStack, &redoStack);
            break;
        case 8:
            redo(service, &undoStack, &redoStack);
            break;
        case 0:
            ok = 1;
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }
    destroyActionStack(&undoStack);
    destroyActionStack(&redoStack);
}