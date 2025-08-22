//
// Created by tranc on 5/6/2025.
//

#ifndef UI_H
#define UI_H
#include "Controller.h"


class UI {
private:
    Controller controller;
public:
    UI()=default;
    void printMenu();
    void run();
    ~UI()=default;
};



#endif //UI_H
