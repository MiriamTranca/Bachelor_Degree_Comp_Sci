#pragma once
#include "domain.h"

typedef struct {
    Estate* estates;
    int size;
    int capacity;
} EstateRepository;

/**
 * Creates and returns an EstateRepository object with initial data.
 *
 * @return A new EstateRepository object initialized with sample estates.
 */

EstateRepository createEstateRepository();

/**
 * Destroys the EstateRepository and frees any allocated memory.
 *
 * @param repo A pointer to the EstateRepository to destroy.
 */

void destroyEstateRepository(EstateRepository* repo);

/**
 * Adds an estate to the repository.
 *
 * @param repo A pointer to the EstateRepository.
 * @param e The estate to add.
 */

void addEstate(EstateRepository* repo, Estate e);

/**
 * Deletes an estate from the repository.
 *
 * @param repo A pointer to the EstateRepository.
 * @param address The address of the estate to delete.
 */

void deleteEstate(EstateRepository* repo, char* address);

/**
 * Updates an estate in the repository.
 *
 * @param repo A pointer to the EstateRepository.
 * @param address The address of the estate to update.
 * @param newEstate The new estate data.
 * @return 1 if the estate was updated, 0 otherwise.
 */

int updateEstate(EstateRepository* repo, char* address, Estate newEstate); // int because 1 if success, 0 if not 

/**
 * Finds an estate by address in the repository.
 *
 * @param repo A pointer to the EstateRepository.
 * @param address The address of the estate to find.
 * @return A pointer to the estate if found, NULL otherwise.
 */

Estate* findEstateByAddress(EstateRepository* repo, char* address);

/**
 * Returns all estates in the repository.
 *
 * @param repo A pointer to the EstateRepository.
 * @return An array of all estates in the repository.
 */

Estate* getAllEstates(EstateRepository* repo);

/**
 * Returns the number of estates in the repository.
 *
 * @param repo A pointer to the EstateRepository.
 * @return The number of estates in the repository.
 */

int getEstateRepositorySize(EstateRepository* repo);

/**
 * Sorts the estates in the repository by price (ascending).
 *
 * @param repo A pointer to the EstateRepository.
 */

void sortEstatesByPrice(EstateRepository* repo);

/**
 * Sorts the estates in the repository by price (ascending).
 *
 * @param repo A pointer to the EstateRepository.
 */

void sortEstatesByPrice2(EstateRepository* repo);