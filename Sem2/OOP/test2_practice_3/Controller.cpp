//
// Created by tranc on 5/6/2025.
//

#include "Controller.h"
#include <fstream>
Controller::Controller() {
    departments.push_back(std::make_shared<Surgery>("Surgery",6,2));
    departments.push_back(std::make_shared<Surgery>("Surgery",5,4));
}

void Controller::addDepart(std::shared_ptr<HospitalDepartment> d) {
    departments.push_back(std::move(d));
}

const std::vector<std::shared_ptr<HospitalDepartment>> & Controller::showAll() {
    return departments;
}

std::vector<std::shared_ptr<HospitalDepartment>> Controller::showEff() {
    std::vector<std::shared_ptr<HospitalDepartment>> eff;
    for (int i=0;i<departments.size();i++) {
        if (departments[i]->isEfficient()) {
            eff.push_back(departments[i]);
        }
    }
    return eff;
}

void Controller::saveToFile(const std::string& filename) {
    std::ofstream fout(filename);
    for (int i=0;i<departments.size();i++) {
        fout<<departments[i]->toString()+", "+std::to_string(departments[i]->isEfficient())+"\n";
    }
    fout.close();
}
