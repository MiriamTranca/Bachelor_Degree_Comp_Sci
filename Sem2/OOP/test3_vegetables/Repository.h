#pragma once
#include <vector>
#include "Domain.h"
class Repository
{
private:
	std::vector<Domain> readFromFile();
public:
	std::vector<Domain> getAllRepo() { return this->readFromFile(); }
};

