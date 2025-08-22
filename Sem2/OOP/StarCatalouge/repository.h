//
// Created by tranc on 6/22/2025.
//

#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <vector>

#include "domain.h"
using namespace std;

class repository {
public:
    vector<Astronomer> loadAstro();
    vector<Star> loadStars();
    void saveStars(vector<Star>& stars);
};



#endif //REPOSITORY_H
