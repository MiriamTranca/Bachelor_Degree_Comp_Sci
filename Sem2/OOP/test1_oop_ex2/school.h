#pragma once
#ifndef SCHOOL_H
#define SCHOOL_H
#include <string>

class school {
private:
    std::string name;
    std::string address;
    std::string date;
    bool visited;
public:
    school();
    school(const std::string& name, const std::string& address, const std::string& date, bool visited);
    std::string get_name();
    std::string get_address();
    std::string get_date();
    bool get_visited();
    void set_visited(bool visited);
};

#endif //SCHOOL_H
