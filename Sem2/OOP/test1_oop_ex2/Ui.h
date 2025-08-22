
#pragma once
#ifndef UI_H
#define UI_H

#include "service.h"


class Ui {
private:
    service Service;
public:
    Ui(service service) : Service(service) {};
    void printMenu();
    void run();
};



#endif //UI_H
