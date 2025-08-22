#ifndef UI_H
#define UI_H

#include "Service.h"

class UI {
private:
    Service& service;
public:
    explicit UI(Service& service) : service(service) {}
    ~UI() = default;

    static void printMenu();
    void run();
};

#endif // UI_H