#include <string.h>
#include <stdlib.h>
#include "services.h"

EstateService createEstateService(EstateRepository* repo) {
    EstateService service;
    service.repo = repo;
    return service;
}

Estate* getFilteredEstatesByTypeAndSurface(EstateService* service, char* type, float surface, int* count) {
    *count = 0;
    Estate* filtered = (Estate*)malloc(service->repo->size * sizeof(Estate));
    for (int i = 0; i < service->repo->size; i++) {
        Estate e = service->repo->estates[i];
        if (strcmp(e.type, type) == 0 && e.surface > surface) {
            filtered[(*count)++] = e;
        }
    }
    return filtered;
}

Estate* getFilteredEstatesByAddress(EstateService* service, char* address, int* count) {
    *count = 0;
    Estate* filtered = (Estate*)malloc(service->repo->size * sizeof(Estate));
    for (int i = 0; i < service->repo->size; i++) {
        if (strstr(service->repo->estates[i].address, address)) {
            filtered[(*count)++] = service->repo->estates[i];
        }
    }
    return filtered;
}

Estate* getSortedEstates(EstateService* service, char* address, int* count) {
    Estate* filtered = getFilteredEstatesByAddress(service, address, count);
    sortEstatesByPrice2(filtered);  // Sorting by price after filtering by address
    return filtered;
}

Estate* getFilteredEstatesBySurfaceAndByPrice(EstateService* service, float surface, int* count) {
	*count = 0;
	Estate* filtered = (Estate*)malloc(service->repo->size * sizeof(Estate));
    for (int i = 0; i < service->repo->size; i++) {
        Estate e = service->repo->estates[i];
        if (e.surface == surface) {
            filtered[(*count)++] = e;
        }
    }
	return filtered;
}

Estate* getSortedEstatesSurfaceAndPrice(EstateService* service, float surface, int* count) {
	Estate* filtered = getFilteredEstatesBySurfaceAndByPrice(service, surface, count);

	sortEstatesByPrice2(filtered);  
	return filtered;
}

ActionStack createActionStack() {
    ActionStack stack;
    stack.size = 0;
    stack.capacity = 10;
    stack.actions = (Action*)malloc(sizeof(Action) * stack.capacity);
    return stack;
}

void destroyActionStack(ActionStack* stack) {
    free(stack->actions);
    stack->actions = NULL;
}


void pushAction(ActionStack* stack, Action action) {
    if (stack->size == stack->capacity) {
        stack->capacity *= 2;
        Action* aux = (Action*)realloc(stack->actions, stack->capacity * sizeof(Action));
        stack->actions = aux;
    }
    stack->actions[stack->size++] = action;
}

Action popAction(ActionStack* stack) {
    if (stack->size == 0) {
        // Stack is empty, return a default action
        Action emptyAction = { ADD, {0}, "" };
        return emptyAction;
    }
    Action action = stack->actions[--stack->size];

    return action;
}

void undo(EstateService* service, ActionStack* undoStack, ActionStack* redoStack) {
    if (undoStack->size == 0) {
        printf("Nothing to undo!\n");
        return;
    }
    Action action = popAction(undoStack);
    switch (action.type) {
    case ADD:
        deleteEstate(service->repo, action.estate.address);
        break;
    case DELETE:
        addEstate(service->repo, action.estate);
        break;
    case UPDATE:
        updateEstate(service->repo, action.address, action.estate);
        break;
    }
    pushAction(redoStack, action);
}

void redo(EstateService* service, ActionStack* undoStack, ActionStack* redoStack) {
    if (redoStack->size == 0) {
        printf("Nothing to redo!\n");
        return;
    }
    Action action = popAction(redoStack);
    switch (action.type) {
    case ADD:
        addEstate(service->repo, action.estate);
        break;
    case DELETE:
        deleteEstate(service->repo, action.address);
        break;
    case UPDATE:
        updateEstate(service->repo, action.address, action.estate);
        break;
    }
    pushAction(undoStack, action);
}