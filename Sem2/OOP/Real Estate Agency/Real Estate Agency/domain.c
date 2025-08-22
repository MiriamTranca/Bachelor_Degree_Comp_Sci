#include <string.h>
#include "domain.h"

Estate createEstate(char address[], char type[], float surface, float price) {
	Estate e;
	strcpy(e.address, address);
	strcpy(e.type, type);
	e.surface = surface;
	e.price = price;
	return e;
}

char* getEstateAddress(Estate* e) {
	return e->address;
}

char* getEstateType(Estate* e) {
	return e->type;
}

float getEstateSurface(Estate* e) {
	return e->surface;
}

float getEstatePrice(Estate* e) {
	return e->price;
}