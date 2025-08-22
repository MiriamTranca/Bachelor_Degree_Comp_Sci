//
// Created by tranc on 6/22/2025.
//

#ifndef DOMAIN_H
#define DOMAIN_H
#include<string>
using namespace std;


class Astronomer {
private:
    string name,constellation;
public:
    Astronomer(const string& name,const string& conste):name(name),constellation(conste){}
    string getName(){return name;}
    string getCons(){return constellation;}
};

class Star {
private:
    string name, constellation;
    int ra,dec,diameter;
public:
    Star(const string& name, const string& conste, int ra, int dec, int d): name(name),constellation(conste),ra(ra),dec(dec),diameter(d){}
    string getName(){return name;}
    string getCons(){return constellation;}
    int getRa(){return ra;}
    int getDec(){return dec;}
    int getDiam(){return diameter;}
};



#endif //DOMAIN_H
