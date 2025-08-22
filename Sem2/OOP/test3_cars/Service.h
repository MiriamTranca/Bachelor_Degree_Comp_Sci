#pragma once
#include "Repository.h"
class Service
{
private:
	Repository repo;
public:
	Service() {};
	std::vector<Domain> getAll();
	std::vector<Domain> sortByManufacturer();
	std::vector<Domain> getAllMan( std::string manName);
	~Service() {};
};

