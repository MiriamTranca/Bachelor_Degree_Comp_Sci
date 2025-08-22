#include "Repository.h"
#include <fstream>
#include <sstream>
std::vector<Domain> Repository::readFromFile()
{
    std::vector<Domain> veg;
    veg.clear();
    std::ifstream fin("vegetables.txt");
    std::string line;
    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        std::string family, name, list;
        if (std::getline(ss, family, '|') &&
            std::getline(ss, name, '|') &&
            std::getline(ss, list, '|')) {
            Domain vegatable(family, name, list);
            veg.push_back(vegatable);
        }
    }
    return veg;

}
