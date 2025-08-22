//
// Created by tranc on 4/1/2025.
//
#pragma once
#ifndef SERVICE_H
#define SERVICE_H

#include "Repo.h"

class Service {
private:
    Repo repo;
public:
    Service(){};

    /**
     * Adds patient to repo, else throws exception
     * @param name pointer to string
     * @param age integer
     * @param infected boolean
     * @param room integer
     */
    void  addPatientService(const std::string& name, int age, bool infected, int room);
    const std::vector<Patient>& showALL();
    /**
     * Changes the parameter infected to patients, older than given age and in room with infected people
     * @param age integer
     */
    void updateStatus(int age);

    std::vector<Patient> infectedPatients();
};



#endif //SERVICE_H
