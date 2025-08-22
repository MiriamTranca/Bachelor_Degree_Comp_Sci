//
// Created by tranc on 6/23/2025.
//

#include "Repository.h"

#include <fstream>
#include <sstream>

vector<Writers> Repository::loadWriters() {
    vector<Writers> writers;
        std::ifstream file("C:/Users/tranc/CLionProjects/ScreenWriting/writers.txt");
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string name,expertise;
            if (std::getline(ss, name, ',')&&std::getline(ss,expertise)) {
                writers.push_back(Writers(name,expertise));
            }
        }
    file.close();
    return writers;
}

vector<Idea> Repository::loadIdeas() {
    vector<Idea> ideas;
    std::ifstream file("C:/Users/tranc/CLionProjects/ScreenWriting/ideas.txt");
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string desc,status,creator,act;
        if (std::getline(ss, desc, ',')&&std::getline(ss,status,',')&&std::getline(ss,creator,',')&&std::getline(ss,act)) {
            ideas.push_back(Idea(desc,status,creator,act));
        }
    }
    file.close();
    return ideas;
}

void Repository::saveIdea(const vector<Idea> &ideas) {
    std::ofstream file("C:/Users/tranc/CLionProjects/ScreenWriting/ideas.txt");
    for (auto idea : ideas) {
        file << idea.getDescription()<<","<<idea.getStatus()<<","<<idea.getCreator()<<","<<idea.getAct()<<std::endl;
    }
    file.close();
}
