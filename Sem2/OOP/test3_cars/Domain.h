#pragma once
#include <string>

class Domain
{
private:
	std::string manName;
	std::string model;
	int year;
	std::string color;
public:
	Domain(std::string manName, std::string model, int year, std::string colour): 
		manName(manName), model(model), year(year), color(colour){}
	std::string getManName() const { return manName; }
	std::string getModel() const { return model; }
	int getyear() const { return year; }
	std::string getColor() const { return color; }
	
	~Domain() {};

};

