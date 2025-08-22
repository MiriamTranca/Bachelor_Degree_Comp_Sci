//
// Created by tranc on 3/31/2025.
//

#include "Repo.h"

Repo::Repo() {
    Task task = Task("Solve_OOP",120,1);
    addTask(task);
    task = Task("Respond",45,2);
    addTask(task);
    task = Task("Eat",30,3);
    addTask(task);
    task = Task("visit",240,1);
    addTask(task);
    task = Task("Buy",120,2);
    addTask(task);
}

Repo::~Repo() = default;

bool Repo::addTask(Task& task) {
    for (auto it = tasks.begin(); it != tasks.end(); ++it) {
        if (it->getDescription() == task.getDescription()) {
            return false;
        }
    }
    tasks.push_back(task);
    return true;
}

 std::vector<Task> & Repo::getTasks() {
    return this->tasks;
}

int Repo::length() {
    return this->tasks.size();
}
