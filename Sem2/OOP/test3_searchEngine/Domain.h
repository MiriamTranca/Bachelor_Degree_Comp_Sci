#pragma once
#include <string>
class Domain {
private:
	std::string name, list, content;
public:
	Domain(std::string name, std::string list, std::string content) :
		name(name), list(list), content(content) {
	}
	std::string getName() const { return name; }
	std::string getList() const{ return list; }
	std::string getContent() const{ return content; }
	~Domain(){}

};