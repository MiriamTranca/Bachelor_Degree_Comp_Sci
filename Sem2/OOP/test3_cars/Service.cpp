#include "Service.h"

std::vector<Domain> Service::getAll()
{
    return this->sortByManufacturer();
}

std::vector<Domain> Service::sortByManufacturer()
{
    std::vector<Domain> cars = repo.readFromFile();
    for (int i = 0; i < cars.size() - 1; i++) {
        for (int j = i; j < cars.size(); j++) {
            if (cars[i].getManName() > cars[j].getManName()) {
                std::swap(cars[i],cars[j]);
            }
        }
    }
    return cars;
}

std::vector<Domain> Service::getAllMan(std::string manName)
{
    std::vector<Domain> carsMan;
    for (Domain& car : this->repo.readFromFile()) {
        if (car.getManName() == manName) {
            carsMan.push_back(car);
        }
    }
    return carsMan;
}
