#pragma once
#include "Domain.h"
#include <vector>
class Repository
{
public:
	Repository() {};
	~Repository() {};
	std::vector<Domain> readFile();
};

