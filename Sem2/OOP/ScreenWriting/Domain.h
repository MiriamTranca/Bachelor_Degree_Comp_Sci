//
// Created by tranc on 6/23/2025.
//

#ifndef DOMAIN_H
#define DOMAIN_H
#include <string>
using namespace std;


class Writers {
private:
    string name;
    string expertise;
    public:
    Writers(const string& name, const string& expertise): name(name),expertise(expertise) {}
    string getName(){return name;}
    string getExpertise(){return expertise;}
};

class Idea {
private:
    string description;
    string status;
    string creator;
    string act;
    public:
    Idea(const string& description, const string& status, const string& creator, const string& act):description(description),status(status),creator(creator),act(act){}
    string getDescription(){return description;}
    string getStatus(){return status;}
    string getCreator(){return creator;}
    string getAct(){return act;}
    void setStatus(string s){status =s ;}
    void setDescription(string s){description = s ;}

};



#endif //DOMAIN_H
