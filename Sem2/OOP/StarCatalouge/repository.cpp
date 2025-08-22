//
// Created by tranc on 6/22/2025.
//

#include "repository.h"

#include <fstream>
#include <sstream>

vector<Astronomer> repository::loadAstro() {
    vector<Astronomer> astros;
    std::ifstream file("C:/Users/tranc/CLionProjects/StarCatalouge/astronomers.txt");
    std::string line;
    while (std::getline(file,line)) {
        std::stringstream ss(line);
        std::string name,conste;
        std::getline(ss,name,',');
        std::getline(ss,conste);
        astros.push_back(Astronomer(name,conste));
    }
    file.close();
    return astros;
}

vector<Star> repository::loadStars() {
    vector<Star> stars;
    std::ifstream file("C:/Users/tranc/CLionProjects/StarCatalouge/starts.txt");
    std::string line;
    while (std::getline(file,line)) {
        std::stringstream ss(line);
        std::string name, conste, raStr,desStr,diamStr;
        if (std::getline(ss,name,',')&&std::getline(ss,conste,',')&&std::getline(ss,raStr,',')&&std::getline(ss,desStr,',')&&std::getline(ss,diamStr)) {
            int ra,dec,diam;
            ra=std::stoi(raStr);
            dec=std::stoi(desStr);
            diam=std::stoi(diamStr);
            stars.push_back(Star(name,conste,ra,dec,diam));
        }
    }
    file.close();
    return stars;
}

void repository::saveStars(vector<Star> &stars) {
     std::ofstream file("C:/Users/tranc/CLionProjects/StarCatalouge/starts.txt");
    for (auto& star: stars) {
        file<<star.getName()<<","<<star.getCons()<<","<<star.getRa()<<","<<star.getDec()<<","<<star.getDiam()<<std::endl;
    }
    file.close();
}
