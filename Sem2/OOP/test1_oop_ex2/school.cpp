//
// Created by tranc on 3/31/2025.
//

#include "school.h"

school::school() {
    this->name = "";
    this->address = "";
    this->date = "";
    this->visited = false;
}

school::school(const std::string& name, const std::string& address, const std::string& date, bool visited) {
    this->name = name;
    this->address = address;
    this->date = date;
    this->visited = visited;
}

std::string school::get_name() {
    return this->name;
}

std::string school::get_address() {
    return this->address;
}

std::string school::get_date() {
    return this->date;
}

bool school::get_visited() {
    return this->visited;
}

void school::set_visited(bool visited) {
    this->visited = visited;
}
