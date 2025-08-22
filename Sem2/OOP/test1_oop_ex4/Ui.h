//
// Created by tranc on 4/1/2025.
//
#pragma once
#ifndef UI_H
#define UI_H
#include "Service.h"


class Ui {
private:
    Service service;
public:
    Ui(){};
    void showMenu();
    void run();
};



#endif //UI_H
