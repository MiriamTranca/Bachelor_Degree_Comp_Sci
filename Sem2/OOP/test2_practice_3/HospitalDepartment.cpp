//
// Created by tranc on 5/6/2025.
//

#include "HospitalDepartment.h"

HospitalDepartment::HospitalDepartment(const std::string &name, int doctors): name(name), doctors(doctors) {
}

Surgery::Surgery(const std::string &name, int doctors, int patients): HospitalDepartment(name, doctors), patients(patients) {
}

bool Surgery::isEfficient() {
    if ((this->patients/this->doctors)>=2) {
        return true;
    }
    return false;
}

std::string Surgery::toString() {
    return name+", "+std::to_string(doctors)+", "+std::to_string(patients);
}

Neonatal::Neonatal(const std::string &name, int doctors, int mothers, int newborns, double grade): HospitalDepartment(name,doctors), mothers(mothers), newborns(newborns),grade(grade) {
}

bool Neonatal::isEfficient() {
    if (this->grade>=8.5 && this->newborns>=this->mothers) {
        return true;
    }
    return false;
}

std::string Neonatal::toString() {
    return name+", "+std::to_string(doctors)+", "+std::to_string(mothers)+", "+std::to_string(newborns)+", "+std::to_string(grade);
}
