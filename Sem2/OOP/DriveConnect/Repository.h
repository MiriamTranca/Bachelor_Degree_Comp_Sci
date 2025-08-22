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
    Repository(){};
    vector<Driver> loadDrivers();
    vector<Report> loadReports();
    void saveReports(const vector<Report>& reports);
};



#endif //REPOSITORY_H
