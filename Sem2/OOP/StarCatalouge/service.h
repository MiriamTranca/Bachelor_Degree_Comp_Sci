//
// Created by tranc on 6/22/2025.
//

#ifndef SERVICE_H
#define SERVICE_H

#include "repository.h"


class service {
private:
    repository repo;
public:
    service(){};
    std::vector<Star> getAllStars(){return getAllStarsSorted();}
    std::vector<Star> getAllStarsSorted();
    std::vector<Astronomer> getAllAstro(){return repo.loadAstro();}
    void addStar(string text, string astroName);
};



#endif //SERVICE_H
