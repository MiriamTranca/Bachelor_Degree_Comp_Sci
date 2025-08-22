#pragma once
#include "repo.h"

typedef struct {
	EstateRepository* repo;
} EstateService;

typedef enum {
	ADD,
	UPDATE,
	DELETE
} ActionType;

typedef struct {
	ActionType type;
	Estate estate;
	char address[100];
} Action;

typedef struct {
	Action* actions;
	int size;
	int capacity;
} ActionStack;

/**
 * Creates and returns an EstateService object for the given repository.
 *
 * @param repo A pointer to an EstateRepository object.
 * @return A new EstateService object initialized with the given repository.
 */

EstateService createEstateService(EstateRepository* repo);

/**
 * Filters estates by type and minimum surface area.
 *
 * @param service A pointer to the EstateService.
 * @param type The type of the estate (e.g., house, apartment).
 * @param surface The minimum surface area for filtering estates.
 * @param count A pointer to an integer that will hold the number of filtered estates.
 * @return An array of estates that match the given type and surface area.
 */

Estate* getFilteredEstatesByTypeAndSurface(EstateService* service, char* type, float surface, int* count);

/**
 * Filters estates by address substring.
 *
 * @param service A pointer to the EstateService.
 * @param address The substring of the address to filter estates.
 * @param count A pointer to an integer that will hold the number of filtered estates.
 * @return An array of estates whose address contains the given substring.
 */

Estate* getFilteredEstatesByAddress(EstateService* service, char* address, int* count);

/**
 * Filters estates by address substring and sorts them by price.
 *
 * @param service A pointer to the EstateService.
 * @param address The substring of the address to filter estates.
 * @param count A pointer to an integer that will hold the number of filtered estates.
 * @return An array of estates filtered by address and sorted by price.
 */

Estate* getSortedEstates(EstateService* service, char* address, int* count);

/**
 * Pushes an action onto the action stack.
 *
 * @param stack A pointer to the ActionStack to which the action will be added.
 * @param action The action to be pushed onto the stack.
 */

Estate* getFilteredEstatesBySurfaceAndByPrice(EstateService* service, float surface, int* count);
Estate* getSortedEstatesSurfaceAndPrice(EstateService* service, float surface, int* count);

void pushAction(ActionStack* stack, Action action);

/**
 * Pops and returns the top action from the action stack.
 *
 * @param stack A pointer to the ActionStack.
 * @return The top Action in the stack. If the stack is empty, returns a default Action.
 */

Action popAction(ActionStack* stack);

/**
 * Pops and returns the top action from the action stack.
 *
 * @param stack A pointer to the ActionStack.
 * @return The top Action in the stack. If the stack is empty, returns a default Action.
 */

void undo(EstateService* service, ActionStack* undoStack, ActionStack* redoStack);

/**
 * Redoes the most recent action from the redo stack and re-applies the effect.
 *
 * @param service A pointer to the EstateService.
 * @param undoStack A pointer to the undo stack.
 * @param redoStack A pointer to the redo stack.
 */

void redo(EstateService* service, ActionStack* undoStack, ActionStack* redoStack);

/**
 * Creates and returns a new empty action stack.
 *
 * @return A new ActionStack initialized with a size of 0 and a default capacity.
 */

ActionStack createActionStack();

/**
 * Destroys the action stack and frees any allocated memory.
 *
 * @param stack A pointer to the ActionStack to be destroyed.
 */

void destroyActionStack(ActionStack* stack);