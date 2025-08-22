//
// Created by tranc on 6/23/2025.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <vector>

#include "Domain.h"

using namespace std;

class Repository {
public:
    Repository(){}
    vector<Writers> loadWriters();
    vector<Idea> loadIdeas();
    void saveIdea(const vector<Idea>& ideas);
};



#endif //REPOSITORY_H
