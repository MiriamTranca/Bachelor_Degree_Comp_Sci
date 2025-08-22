#pragma once
#include "Domain.h"
#include <vector>
class Repository
{
private:
	std::vector<Domain> cars;
public:
	Repository() {};
	std::vector<Domain> readFromFile();
	~Repository() {};
};

