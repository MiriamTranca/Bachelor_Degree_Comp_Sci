//
// Created by tranc on 3/31/2025.
//
#pragma once
#ifndef TASK_H
#define TASK_H
#include <string>


class Task {
private:
    std::string description;
    int minutes;
    int priority;
public:
    Task();
    Task(const std::string& description, int minutes, int priority);
    ~Task();
    std::string getDescription();
    int getMinutes();
    int getPriority();
};



#endif //TASK_H
