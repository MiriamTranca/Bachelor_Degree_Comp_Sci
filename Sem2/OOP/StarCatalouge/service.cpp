//
// Created by tranc on 6/22/2025.
//

#include "service.h"

#include <sstream>

std::vector<Star> service::getAllStarsSorted() {
    std::vector<Star> stars = repo.loadStars();
    for (int i=0;i<stars.size()-1;i++) {
        for (int j=i;j<stars.size();j++) {
            if (stars[i].getCons()>stars[j].getCons()) {
                swap(stars[i],stars[j]);
            }
        }
    }
    repo.saveStars(stars);
    return stars;

}

void service::addStar(string text, string astroName) {
    std::vector<Star> stars=repo.loadStars();
    std::string cons="";
    for (auto& astro:repo.loadAstro()) {
        if (astro.getName()==astroName) {
            cons=astro.getCons();
        }
    }
    std::stringstream ss(text);
    std::string name, raStr, decStr, diamStr;
    if (std::getline(ss,name,',')&&std::getline(ss,raStr,',')&&std::getline(ss,decStr,',')&&std::getline(ss,diamStr)) {
        int ra,dec,diam;
        ra=std::stoi(raStr);
        dec=std::stoi(decStr);
        diam=std::stoi(diamStr);
        int ok=0;
        for (auto& str:repo.loadStars()) {
            if (str.getName()==name) {
                ok=1;
            }
        }
        if (name == "" || ok==1 || diam <=0) {
            throw runtime_error("Name or diameter not good.");
        }
        else{
            stars.push_back(Star(name,cons,ra,dec,diam));
        }
    }
    repo.saveStars(stars);
}
