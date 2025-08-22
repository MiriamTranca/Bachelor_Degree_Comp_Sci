//
// Created by tranc on 6/23/2025.
//

#include "Service.h"

#include <iostream>
#include <qtextstream.h>
#include <stdexcept>


vector<Idea> Service::getSortedIdeas() {
    vector<Idea> ideas = repository.loadIdeas();
    for (int i=0; i<ideas.size()-1; i++) {
        for (int j=i+1; j<ideas.size(); j++) {
            if (ideas[i].getAct() > ideas[j].getAct()) {
                swap(ideas[i], ideas[j]);
            }
        }
    }
    return ideas;
}

void Service::addNewIdea(string desc, string act, string writer) {
    vector<Idea> ideas = repository.loadIdeas();
    bool ok=1;
    for (auto idea : ideas) {
        if (idea.getDescription()==desc) {
            ok=0;
        }
    }
    if (ok==1 && (act=="1" || act=="2"|| act=="3")&& desc!="") {
        ideas.push_back(Idea(desc,"proposed",writer, act));
        repository.saveIdea(ideas);
    } else {
        throw runtime_error("Descripiton or act nor ok.");
   }
}


void Service::acceptIdea(const std::string& desc) {
    auto ideas = repository.loadIdeas();
    bool found = false;
    for (auto& idea : ideas) {
        if (idea.getDescription() == desc && idea.getStatus() == "proposed") {
            idea.setStatus("accepted");
            found = true;
        }
    }
    if (!found) throw std::runtime_error("Idea not found or already accepted.");
    repository.saveIdea(ideas);
}

void Service::saveIdea(std::string desc, std::string newdesc) {
    vector<Idea> ideas = repository.loadIdeas();
    for (auto idea : ideas) {
        if (idea.getDescription() == desc) {
            idea.setDescription(newdesc);
        }
    }
    repository.saveIdea(ideas);
}

