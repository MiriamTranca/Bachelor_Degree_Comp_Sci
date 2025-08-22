#include "car.h"

Car::Car(const std::string &man_name, const std::string &model, int year, const std::string &colour) {
    this->man_name = man_name;
    this->model = model;
    this->year = year;
    this->colour = colour;
}
