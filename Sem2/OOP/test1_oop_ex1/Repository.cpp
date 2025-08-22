
#include "Repository.h"

#include <stdexcept>

Repository::Repository() {
    this->addCar(Car("Fiat", "Bravo", 2007, "red"));
    this->addCar(Car("Fiat", "Idea", 2003, "black"));
    this->addCar(Car("Audi", "A5", 2007, "blue"));
    this->addCar(Car("BMW", "Coupe", 2013, "pink"));
    this->addCar(Car("Ford", "Fiesta", 1976, "yellow"));
}

bool Repository::addCar(const Car &car) {
    for (const auto& existingCar : this->cars) {
        if (existingCar.getModel() == car.getModel() && existingCar.getYear() == car.getYear()) {
            return false;
        }
    }
    this->cars.push_back(car);
    return true;
}

void Repository::removeCar(const Car &car) {
    for (auto it = this->cars.begin(); it != this->cars.end(); ++it) {
        if (it->getModel() == car.getModel() && it->getYear() == car.getYear()) {
            this->cars.erase(it);
            return;
        }
    }
}

