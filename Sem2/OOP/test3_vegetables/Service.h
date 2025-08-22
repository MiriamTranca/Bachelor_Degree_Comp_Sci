#pragma once
#include "Repository.h"

class Service
{
private:
	Repository repo;
public:
	Service() {};
	std::vector<std::string> getFamilies();
	std::vector<Domain> getForFamily(std::string family);
	std::vector<Domain> getAll() { return repo.getAllRepo(); }
	~Service() {};
};

