
#ifndef SERVICE_H
#define SERVICE_H
#include <memory>
#include <vector>

#include "Building.h"


class Service {
private:
    std::vector<std::shared_ptr<Building>> buildings;
public:
    Service();
    void addB(std::shared_ptr<Building>b);
    const std::vector<std::shared_ptr<Building>>& showAll();
    std::vector<std::shared_ptr<Building>> showR();
    std::vector<std::shared_ptr<Building>> showD();
    void writeToFile(const std::string& filename1, const std::string& filename2);
    ~Service()=default;
};



#endif //SERVICE_H
