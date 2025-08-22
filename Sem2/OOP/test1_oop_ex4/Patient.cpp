//
// Created by tranc on 4/1/2025.
//

#include "Patient.h"

Patient::Patient() {
    this->name ="";
    this->age=0;
    this->infected=false;
    this->room=0;
}

Patient::Patient(const std::string &name, int age, bool infected, int room) {
    this->name = name;
    this->age= age;
    this->infected=infected;
    this->room= room;
}

Patient::~Patient() = default;

std::string Patient::get_name() {
    return this->name;
}

int Patient::get_age() {
    return this->age;
}

bool Patient::get_infected() {
    return this->infected;
}

int Patient::get_room() {
    return this->room;
}

void Patient::set_infected(bool infected) {
    this->infected=infected;
}
