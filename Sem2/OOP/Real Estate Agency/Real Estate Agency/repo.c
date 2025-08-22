#include <stdlib.h>
#include <string.h>
#include "repo.h"

int compareByPrice(const void* a, const void* b) {
    Estate* estateA = (Estate*)a;
    Estate* estateB = (Estate*)b;
    return (estateA->price > estateB->price) - (estateA->price < estateB->price);
}

EstateRepository createEstateRepository() {
    EstateRepository repo;
    repo.size = 0;
    repo.capacity = 10;
    repo.estates = (Estate*)malloc(sizeof(Estate) * repo.capacity);

    addEstate(&repo, createEstate("123", "house", 120, 25000));
    addEstate(&repo, createEstate("456", "apartment", 85, 10000));
    addEstate(&repo, createEstate("789", "house", 150, 2000));
    addEstate(&repo, createEstate("101", "penthouse", 150, 5000));
    addEstate(&repo, createEstate("202", "apartment", 150, 10000));
    addEstate(&repo, createEstate("303", "house", 135, 27000));
    addEstate(&repo, createEstate("404", "house", 145, 32000));
    addEstate(&repo, createEstate("505", "apartment", 80, 1700));
    addEstate(&repo, createEstate("606", "penthouse", 210, 50000));
    addEstate(&repo, createEstate("707", "house", 160, 3000));

    return repo;
}


void destroyEstateRepository(EstateRepository* repo) {
    free(repo->estates);
    repo->estates = NULL;
}

void addEstate(EstateRepository* repo, Estate e) {
    if (repo->size == repo->capacity) {
        repo->capacity *= 2;
        Estate* aux = (Estate*)realloc(repo->estates, sizeof(Estate) * repo->capacity);
        repo->estates = aux;
    }
    repo->estates[repo->size++] = e;
}

void deleteEstate(EstateRepository* repo, char* address) {
    for (int i = 0; i < repo->size; i++) {
        if (strcmp(repo->estates[i].address, address) == 0) {
            for (int j = i; j < repo->size - 1; j++) {
                repo->estates[j] = repo->estates[j + 1];
            }
            repo->size--;
            return;
        }
    }
}

int updateEstate(EstateRepository* repo, char* address, Estate newEstate) {
    for (int i = 0; i < repo->size; i++) {
        if (strcmp(repo->estates[i].address, address) == 0) {
            repo->estates[i] = newEstate;
            return 1;
        }
    }
    return 0;
}

Estate* findEstateByAddress(EstateRepository* repo, char* address) {
    for (int i = 0; i < repo->size; i++) {
        if (strcmp(repo->estates[i].address, address) == 0) {
            return &repo->estates[i];
        }
    }
    return NULL;
}

Estate* getAllEstates(EstateRepository* repo) {
    return repo->estates;
}

int getEstateRepositorySize(EstateRepository* repo) {
    return repo->size;
}

void sortEstatesByPrice(EstateRepository* repo) {
    qsort(repo->estates, repo->size, sizeof(Estate), compareByPrice);
}

void sortEstatesByPrice2(EstateRepository* repo) { // Bubble sort
    for (int i = 0; i < repo->size - 1; i++) {
        for (int j = i + 1; j < repo->size; j++) {
            if (repo->estates[i].price > repo->estates[j].price) {
                Estate aux = repo->estates[i];
                repo->estates[i] = repo->estates[j];
                repo->estates[j] = aux;
            }
        }
    }
}