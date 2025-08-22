#include "Repository.h"
#include <fstream>
#include <sstream>
std::vector<Domain> Repository::readFromFile()
{
    cars.clear();
    std::ifstream fin("cars.txt");
    std::string line;
    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        std::string manName, model, strYear, colour;

        if (std::getline(ss, manName, '|') &&
            std::getline(ss, model, '|') &&
            std::getline(ss, strYear, '|') &&
            std::getline(ss, colour))
        {
            int year = std::stoi(strYear);
            Domain car(manName, model, year, colour);
            this->cars.push_back(car);
        }
    }
    return cars;
}
