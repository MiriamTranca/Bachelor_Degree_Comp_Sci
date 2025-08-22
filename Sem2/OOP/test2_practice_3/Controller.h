//
// Created by tranc on 5/6/2025.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <memory>
#include <vector>

#include "HospitalDepartment.h"


class Controller {
private:
    std::vector<std::shared_ptr<HospitalDepartment>> departments;
public:
    Controller();
    void addDepart(std::shared_ptr<HospitalDepartment> d);
    const std::vector<std::shared_ptr<HospitalDepartment>>& showAll();
    std::vector<std::shared_ptr<HospitalDepartment>> showEff();
    void saveToFile(const std::string& filename);
    ~Controller()=default;
};



#endif //CONTROLLER_H
