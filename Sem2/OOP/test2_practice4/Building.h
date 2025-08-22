
#ifndef DOMAIN_H
#define DOMAIN_H


#include <string>
class Building {
protected:
    std::string address;
    int year;
public:
    Building(const std::string& address, int year);
    virtual bool Restored()=0;
    virtual bool Demolished()=0;
    virtual std::string toString()=0;
    std::string getAdd();
    virtual ~Building()=default;
};

class Block: public Building {
private:
    int apart;
    int occupied;
public:
    Block(const std::string& address, int year, int apart, int occupied);
    bool Restored() override;
    bool Demolished() override;
    std::string toString() override;
    ~Block() override=default;
};

class House: public Building {
private:
    std::string type;
    bool hist;
public:
    House(const std::string& address, int year, const std::string& type, bool hist);
    bool Restored() override;
    bool Demolished() override;
    std::string toString() override;
    ~House() override=default;
};


#endif //DOMAIN_H
