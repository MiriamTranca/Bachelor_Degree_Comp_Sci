#pragma once
#include "services.h"

void displayFilteredEstatesByTypeAndSurface(EstateService* service);
void displayFilteredEstatesByAddress(EstateService* service);
void displayFilteredEstatesBySurfaceAndPrice(EstateService* service);
void showMenu();
void handleUserInput(EstateService* service);
