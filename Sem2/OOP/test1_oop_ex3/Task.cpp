//
// Created by tranc on 3/31/2025.
//

#include "Task.h"

Task::Task() {
    this->description = "";
    this->minutes = 0;
    this->priority = 0;
}

Task::Task(const std::string& description, int minutes, int priority) {
    this->description = description;
    this->minutes = minutes;
    this->priority = priority;
}

Task::~Task() = default;

std::string Task::getDescription() {
    return this->description;
}

int Task::getMinutes() {
    return this->minutes;
}

int Task::getPriority() {
    return this->priority;
}
