#ifndef SERVICE_H
#define SERVICE_H
#include "Repository.h"

class Service {
private:
    Repository& repo;
public:
    explicit Service(Repository& repo) : repo(repo) {}
    void addCarService(const std::string& name_man, const std::string& model, int year, const std::string& colour);
    void removeCarService(const std::string& model, int year);
    std::vector<Car> displayAllSorted() const;
    std::vector<Car> displayVintage() const;
};

#endif //SERVICE_H
