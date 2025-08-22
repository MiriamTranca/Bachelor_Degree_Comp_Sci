//
// Created by tranc on 4/1/2025.
//
#pragma once

#ifndef REPO_H
#define REPO_H
#include "Patient.h"
#include <vector>

class Repo {
private:
    std::vector<Patient> patients;
public:
    Repo();
    /**
     * Function that checks if patient can be added and adds it to the Repo
     * @param newPatient an Patient object
     * @return true, if patient was added, false otherwise
     */
    bool addPatient(Patient newPatient);
    const std::vector<Patient>& getPatients();
    void updatePatients(const std::vector<Patient>& updatedPatients);
    int length();

};



#endif //REPO_H
