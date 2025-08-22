
#include "Appliance.h"

Appliance::Appliance(const std::string &id) : id(id) {}

Refrigerator::Refrigerator(const std::string &id, const std::string &type, bool hasFreezer): Appliance(id ), type(type), hasFreezer(hasFreezer) {}

std::string Refrigerator::getType() {
    return this->type;
}

bool Refrigerator::getFreezer() {
    return this->hasFreezer;
}

double Refrigerator::consumedElectricity() {
    double c=0;
    if (type == "A") {
        c= 3*30;
    }
    else {
        c= 2*30;
    }
    if (hasFreezer) {
        c+=20;
    }
    return c;
}

std::string Refrigerator::toString() {
    std::string freezer="false";
    if (hasFreezer)
        freezer="true";
    return "Refrigerator,"+id+","+freezer+","+std::to_string(consumedElectricity());
}

DishWasher::DishWasher(const std::string &id, double consumation): Appliance(id), consumation(consumation) {}

double DishWasher::getConsumation() {
    return this->consumation;
}

double DishWasher::consumedElectricity() {
    return 20*consumation;
}

std::string DishWasher::toString() {
    return "Dishwasher,"+id+","+std::to_string(consumedElectricity());
}




