//
// Created by tranc on 4/1/2025.
//
#pragma once
#ifndef PATIENT_H
#define PATIENT_H
#include  <string>


class Patient {
private:
    std::string name;
    int age;
    bool infected;
    int room;
public:
    Patient();
    Patient(const std::string& name, int age, bool infected, int room);
    ~Patient();
    std::string get_name();
    int get_age();
    bool get_infected();
    int get_room();
    void set_infected(bool infected);

};



#endif //PATIENT_H
