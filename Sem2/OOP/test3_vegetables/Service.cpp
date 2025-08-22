#include "Service.h"

std::vector<std::string> Service::getFamilies()
{
    std::vector<std::string> families;
    int ok = 0;
    for (int i = 0; i < repo.getAllRepo().size(); i++) {
        std::string family = repo.getAllRepo()[i].getFamily();
        for (int j = 0; j < families.size(); j++) {
            if (families[j] == family)
                ok = 1;
        }
        if (ok == 0) {
            families.push_back(family);
        }
        ok = 0;
    }
    return families;
}

std::vector<Domain> Service::getForFamily(std::string family)
{
    std::vector<Domain> vegForFam;
    for (int i = 0; i < repo.getAllRepo().size(); i++) {
        if (repo.getAllRepo()[i].getFamily() == family) {
            vegForFam.push_back(repo.getAllRepo()[i]);
        }
    }
    return vegForFam;
}
