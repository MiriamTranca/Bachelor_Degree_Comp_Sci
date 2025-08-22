//
// Created by tranc on 3/31/2025.
//
#pragma once
#ifndef SERVICE_H
#define SERVICE_H
#include "Repo.h"


class Service {
private:
    Repo& repo;
    public:
    explicit Service(Repo& repo): repo(repo) {};
    /**
     * Function that throws invalid argument if Task cannot pe added to the repo
     * @param description string
     * @param minutes integer
     * @param priority integer
     */
    void addTaskService(const std::string& description, int minutes, int priority);
    std::vector<Task>& showAllTasks();
    std::vector<Task> showTasksPriority(int p);
    std::vector<Task> sortTasks(std::vector<Task>& tasks);
};



#endif //SERVICE_H
