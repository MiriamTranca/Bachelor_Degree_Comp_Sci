//
// Created by tranc on 5/5/2025.
//

#ifndef SERVICE_H
#define SERVICE_H
#include <memory>
#include <vector>

#include "Appliance.h"


class Service {
private:
    std::vector<std::shared_ptr<Appliance>> appliances;
public:
    Service();
    void addAppliance(std::shared_ptr<Appliance> a);
    const std::vector<std::shared_ptr<Appliance>>& getAll();
    std::vector<std::shared_ptr<Appliance>> getAllWithConsumedLess(double maxEl);
    void writeToFile(std::string filename, double maxEl);
    ~Service() = default;
};



#endif //SERVICE_H
