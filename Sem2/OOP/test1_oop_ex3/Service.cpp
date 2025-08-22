//
// Created by tranc on 3/31/2025.
//

#include "Service.h"

#include <algorithm>
#include <stdexcept>

void Service::addTaskService(const std::string &description, int minutes, int priority) {
    Task task = Task(description, minutes, priority);
    if (!this->repo.addTask(task)) {
        throw std::invalid_argument("Failed to add task");
    }
}

std::vector<Task>& Service::showAllTasks() {
    return this->repo.getTasks();
}

/**
 * 
 * @param p 
 * @return 
 */
std::vector<Task> Service::showTasksPriority(int p) {
    std::vector<Task> tasks;
    for (int i=0;i<this->repo.length();i++) {
        if (this->repo.getTasks()[i].getPriority() < p) {
            tasks.push_back(this->repo.getTasks()[i]);
        }
    }
    return tasks;
}

std::vector<Task> Service::sortTasks(std::vector<Task>& tasks) {
    std::sort(tasks.begin(), tasks.end(), [](Task &t1, Task &t2) {
        return t1.getMinutes() > t2.getMinutes();
    });
    return tasks;
    
}
