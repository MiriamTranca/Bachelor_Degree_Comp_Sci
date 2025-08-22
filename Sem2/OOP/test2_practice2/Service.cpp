//
// Created by tranc on 5/5/2025.
//

#include "Service.h"
#include <fstream>
#include <algorithm>
Service::Service() {
    appliances.push_back(std::make_shared<Refrigerator>("1","A++", true));
    appliances.push_back(std::make_shared<Refrigerator>("2","A", false));
    appliances.push_back(std::make_shared<DishWasher>("3",30.3));
}

void Service::addAppliance(std::shared_ptr<Appliance> a) {
    appliances.push_back(std::move(a));
}

const std::vector<std::shared_ptr<Appliance>> & Service::getAll() {
    return appliances;
}

std::vector<std::shared_ptr<Appliance>> Service::getAllWithConsumedLess(double maxEl) {
    std::vector<std::shared_ptr<Appliance>> lessthan;
    for (int i=0;i<appliances.size();i++) {
        if (appliances[i]->consumedElectricity()<maxEl) {
            lessthan.push_back(appliances[i]);
        }
    }
    return lessthan;
}

void Service::writeToFile(std::string filename, double maxEl) {
    std::ofstream fout(filename);
    auto lessthan = getAllWithConsumedLess(maxEl);

    std::sort(lessthan.begin(),lessthan.end(),[](std::shared_ptr<Appliance>& a, std::shared_ptr<Appliance>& b) {
        return a->getID() < b->getID();
    });

    for (int i=0;i<lessthan.size();i++) {
        fout<<lessthan[i]->toString()<<"\n";
    }
    fout.close();
}
