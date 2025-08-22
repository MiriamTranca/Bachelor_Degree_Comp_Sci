#pragma once

typedef struct {
	char address[100];
	char type[100];
	float surface;
	float price;
} Estate;

/**
 * Creates and returns an Estate with the given details.
 *
 * @param address The address of the estate.
 * @param type The type of the estate (e.g., house, apartment).
 * @param surface The surface area of the estate.
 * @param price The price of the estate.
 * @return A new Estate object.
 */

Estate createEstate(char address[], char type[], float surface, float price);
char* getEstateAddress(Estate* e);
char* getEstateType(Estate* e);
float getEstateSurface(Estate* e);
float getEstatePrice(Estate* e);