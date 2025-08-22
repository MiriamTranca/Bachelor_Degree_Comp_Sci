
#include "Controller.h"
#include <fstream>

Service::Service() {
    buildings.push_back(std::make_shared<Block>("a1", 1900, 81, 70));
    buildings.push_back(std::make_shared<House>("a2", 1000, "duplex", 0));
}

void Service::addB(std::shared_ptr<Building> b) {
    int ok=0;
    for (int i=0;i<buildings.size();i++)
        if (buildings[i]->getAdd() == b->getAdd()) ok=1;
    if (ok==0) buildings.push_back(std::move(b));
}

const std::vector<std::shared_ptr<Building>> & Service::showAll() {
    return buildings;
}

std::vector<std::shared_ptr<Building>> Service::showR() {
    std::vector<std::shared_ptr<Building>> rest;
    for (int i=0;i<buildings.size();i++) {
        if (buildings[i]->Restored()) {
            rest.push_back(buildings[i]);
        }
    }
    return rest;
}

std::vector<std::shared_ptr<Building>> Service::showD() {
    std::vector<std::shared_ptr<Building>> demo;
    for (int i=0;i<buildings.size();i++) {
        if (buildings[i]->Demolished()) {
            demo.push_back(buildings[i]);
        }
    }
    return demo;
}

void Service::writeToFile(const std::string& filename1, const std::string& filename2) {
    std::ofstream fout1(filename1);
    std::ofstream fout2(filename2);
    const auto& demo = showD();
    const auto& rest = showR();
    for (int i=0;i<rest.size();i++) {
        fout1<<rest[i]->toString();
    }
    for (int i=0;i<demo.size();i++) {
        fout2<<demo[i]->toString();
    }

}
