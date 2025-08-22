//
// Created by tranc on 5/5/2025.
//

#ifndef UI_H
#define UI_H
#include "Service.h"


class UI {
private:
    Service service;
public:
    UI()=default;
    void menu();
    void run();
    ~UI() =default;
};



#endif //UI_H
