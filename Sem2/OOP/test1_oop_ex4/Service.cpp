//
// Created by tranc on 4/1/2025.
//

#include "Service.h"

#include <stdexcept>

void Service::addPatientService(const std::string &name, int age, bool infected, int room) {
    Patient newPatient = Patient(name, age, infected, room);
    if (!this->repo.addPatient(newPatient)) {
        throw std::invalid_argument("Patient already exists.");
    }
}

const std::vector<Patient> & Service::showALL() {
    return this->repo.getPatients();
}

void Service::updateStatus(int age) {
    std::vector<Patient> patients= this->repo.getPatients();
    for (int i=0;i<this->repo.length();i++) {
        if (patients[i].get_infected()) {
            for (int j = 0; j < patients.size(); j++) {
                if (i != j && patients[i].get_room() == patients[j].get_room() &&
                    patients[j].get_age() > age) {
                    patients[j].set_infected(true);
                    }
            }
        }
    }
    this->repo.updatePatients(patients);
}

std::vector<Patient> Service::infectedPatients() {
    std::vector<Patient> infectedPatients;
    for (int i=0;i<this->repo.length();i++) {
        Patient patient = this->repo.getPatients()[i];
        if (patient.get_infected()) {
            infectedPatients.push_back(patient);
        }
    }
    return infectedPatients;
}
