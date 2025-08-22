#pragma once
#include "car.h"
#include <vector>
#ifndef REPOSITORY_H
#define REPOSITORY_H

class Repository {
private:
    std::vector<Car> cars;
public:
    Repository();
    bool addCar(const Car& car);
    void removeCar(const Car& car);
    const std::vector<Car>& getCars() const {return this->cars;};

};

#endif //REPOSITORY_H
