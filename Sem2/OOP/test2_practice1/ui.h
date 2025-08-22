//
// Created by tranc on 5/2/2025.
//

#ifndef UI_H
#define UI_H
#include "person.h"


class ui {
private:
    Person person;
public:
    explicit ui(const Person& p) : person(p) {}
    void printMenu();
    void run();
};



#endif //UI_H
