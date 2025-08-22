#pragma once
#include <string>
class Domain {
private:
	std::string family, name, list;
public:
	Domain(std::string family, std::string name, std::string list):
		family(family), name(name), list(list){}
	std::string getFamily() const { return family; }
	std::string getName() const { return name; }
	std::string getList() const { return list; }
	~Domain(){}
};