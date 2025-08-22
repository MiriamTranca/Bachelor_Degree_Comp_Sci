#pragma once
#ifndef SERVICE_H
#define SERVICE_H
#include "repo.h"


class service {
private:
    repo& Repo;
public:
    explicit service(repo& repo) : Repo(repo) {};
    bool compareDates(const std::string& date1, const std::string& date2);
    void removeSchoolService(const std::string& school);
    std::vector<school> getSchoolsSorted();
    void markSchoolsVisited(const std::string& day);
    std::vector<school> getSchoolsToVisit();

};


#endif //SERVICE_H
