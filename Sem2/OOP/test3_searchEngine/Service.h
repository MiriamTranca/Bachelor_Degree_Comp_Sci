#pragma once
#include "Repository.h"
class Service
{
private:
	Repository repo;
public:
	Service() {};
	std::vector<Domain> sortAll();
	double similarity(std::string text, std::string text2);
	bool findNameOrList(std::string text, std::string name);
	~Service() {};
};

