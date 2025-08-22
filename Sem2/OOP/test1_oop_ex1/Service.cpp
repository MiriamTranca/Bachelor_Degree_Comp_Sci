#include "Service.h"
#include <algorithm>
#include <stdexcept>

void Service::addCarService(const std::string &name_man, const std::string &model, int year, const std::string &colour) {
    Car newCar(name_man, model, year, colour);
    if (!repo.addCar(newCar)) {
        throw std::invalid_argument("Car already exists in the repository.");
    }
}

void Service::removeCarService(const std::string& model, int year) {
    Car tempCar("", model, year, "");
    repo.removeCar(tempCar);
}

std::vector<Car> Service::displayAllSorted() const {
    std::vector<Car> sortedCars = repo.getCars();
    std::sort(sortedCars.begin(), sortedCars.end(), [](const Car &car1, const Car &car2) {
        return (car1.getManName() < car2.getManName()) ||
               (car1.getManName() == car2.getManName() && car1.getModel() < car2.getModel());
    });
    return sortedCars;
}

std::vector<Car> Service::displayVintage() const {
    std::vector<Car> vintageCars;
    int currentYear = 2025;
    for (const auto& car : repo.getCars()) {
        if (currentYear - car.getYear() > 45) {
            vintageCars.push_back(car);
        }
    }
    std::sort(vintageCars.begin(), vintageCars.end(), [](const Car &car1, const Car &car2) {
        return car1.getColour() < car2.getColour();
    });
    return vintageCars;
}
