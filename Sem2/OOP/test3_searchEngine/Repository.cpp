#include "Repository.h"
#include <fstream>
#include <sstream>
std::vector<Domain> Repository::readFile()
{
    std::vector<Domain> docs;
    docs.clear();
    std::ifstream fin("Docs.txt");
    std::string line;
    while (getline(fin, line)) {
        std::stringstream ss(line);
        std::string name, list, content;
        if (std::getline(ss, name, '|') &&
            std::getline(ss, list, '|') &&
            std::getline(ss, content)) {
            Domain doc(name, list, content);
            docs.push_back(doc);
        }
    }
    return docs;
}
