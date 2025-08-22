//
// Created by tranc on 3/31/2025.
//
#pragma once
#ifndef UI_H
#define UI_H
#include "Service.h"


class Ui {
private:
    Service& service;
    public:
    explicit Ui(Service& serv): service(serv) {};
    void printMenu();
    void run();
};



#endif //UI_H
