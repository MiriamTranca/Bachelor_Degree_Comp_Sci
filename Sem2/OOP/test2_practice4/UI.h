#ifndef UI_H
#define UI_H
#include "Controller.h"


class UI {
private:
    Service serv;
public:
    UI()=default;
    void printMenu();
    void run();
    ~UI()=default;

};



#endif //UI_H
