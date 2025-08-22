#pragma once
#ifndef REPO_H
#define REPO_H
#include <vector>

#include "school.h"

class repo {
private:
    std::vector<school> schools;
public:
    repo();
    bool addSchoolRepo(const school& newSchool);
    bool removeSchoolRepo(const std::string& thisSchool);
    std::vector<school>& getSchools();
};

#endif //REPO_H
