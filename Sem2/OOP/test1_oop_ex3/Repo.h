//
// Created by tranc on 3/31/2025.
//
#pragma once
#ifndef REPO_H
#define REPO_H
#include <vector>

#include "Task.h"


class Repo {
private:
    std::vector<Task> tasks;
    public:
    Repo();
    ~Repo();
    /**
     * Function that checks if the task is added to the list
     * @param task : object of Task class
     * @return true, if Task can be added, false otherwise
     */
    bool addTask(Task& task);
    std::vector<Task>& getTasks();
    int length();
};



#endif //REPO_H
