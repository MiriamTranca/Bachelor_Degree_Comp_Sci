#pragma once
#ifndef CAR_H
#define CAR_H
#include <string>


class Car {
private:
    std::string man_name;
    std::string model;
    int year;
    std::string colour;
public:
    //constructors
    Car(const std::string& man_name,const std::string& model, int year, const std::string& colour);
    Car() : Car("", "", 0, "") {}

    //getters
    std::string getManName() const {return man_name;}
    std::string getModel() const {return model;}
    int getYear() const {return year;}
    std::string getColour() const {return colour;}

    //setters
    void setManName(const std::string& man_name) {this->man_name = man_name;};
    void setModel(const std::string& model) {this->model = model;};
    void setYear(int year) {this->year = year;};
    void setColour(const std::string& colour) {this->colour = colour;};


};



#endif //CAR_H
