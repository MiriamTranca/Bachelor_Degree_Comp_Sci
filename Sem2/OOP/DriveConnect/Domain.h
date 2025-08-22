//
// Created by tranc on 6/23/2025.
//

#ifndef DOMAIN_H
#define DOMAIN_H

#include <string>
using namespace std;

class Driver {
    private:
    string name;
    int lat;
    int lon;
    int score;
    public:
    Driver(const string& name, int lat, int lon, int score): name(name), score(score), lat(lat), lon(lon) {};
    string getName(){return name;};
    int getLat(){return lat;};
    int getLon(){return lon;};
    int getScore(){return score;};
};

class Report {
private:
    string desc;
    string reporter;
    int lat;
    int lon;
    int validation=0;
    bool valid;
    public:
    Report(const string& desc, const string& reporter, int lat, int lon, bool valid): desc(desc), reporter(reporter), lat(lat), lon(lon), valid(valid) {};
    string getDesc(){return desc;};
    string getReporter(){return reporter;};
    int getLat(){return lat;};
    int getLon(){return lon;};
    bool getValid(){return valid;};
    void setValidation(){validation++;}
    int getValidation(){return validation;}
};



#endif //DOMAIN_H
