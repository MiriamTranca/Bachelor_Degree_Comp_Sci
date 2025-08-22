//
// Created by tranc on 4/1/2025.
//

#include "Repo.h"

Repo::Repo() {
    this->addPatient(Patient("Jessica", 42, false, 3));
    this->addPatient(Patient("Lidia", 30, true, 3));
    this->addPatient(Patient("Scott", 86, false, 2));
    this->addPatient(Patient("Zeno", 37, true, 2));
    this->addPatient(Patient("Andrew", 62, false, 3));
}

bool Repo::addPatient(Patient newPatient) {
    for (int i=0;i<this->length();i++) {
        if (newPatient.get_name()  == this->patients[i].get_name()) {
            return false;
        }
    }
    this->patients.push_back(newPatient);
    return true;
}

const std::vector<Patient> & Repo::getPatients() {
    return patients;
}

void Repo::updatePatients(const std::vector<Patient>& updatedPatients) {
    this->patients = updatedPatients;
}

int Repo::length() {
    return this->patients.size();
}
