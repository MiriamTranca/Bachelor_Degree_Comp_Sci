//
// Created by tranc on 6/23/2025.
//

#ifndef SERVICE_H
#define SERVICE_H
#include "Repository.h"


class Service {
private:
    Repository repository;
    public:
    Service(){}
    vector<Idea> getAllIdeas(){return repository.loadIdeas();}
    vector<Idea> getSortedIdeas();
    vector<Writers> getAllWriters(){return repository.loadWriters();}
    void addNewIdea(string desc, string act, string writer);
    void acceptIdea(const std::string& desc);
    void saveIdea( std::string desc, std::string newdesc);
};


#endif //SERVICE_H
