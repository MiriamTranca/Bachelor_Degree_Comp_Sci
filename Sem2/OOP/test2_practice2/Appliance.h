
#ifndef APPLIANCE_H
#define APPLIANCE_H
#include <string>


class Appliance {
protected:
    std::string id;
public:
    explicit Appliance(const std::string& id);
    const std::string& getID(){return id;}
    virtual double consumedElectricity() =0;
    virtual std::string toString() =0;
    virtual ~Appliance() = default;
};

class Refrigerator: public Appliance {
private:
    std::string type;
    bool hasFreezer;
public:
    Refrigerator(const std::string& id, const std::string& type, bool hasFreezer);
    std::string getType();
    bool getFreezer();
    double consumedElectricity() override;
    std::string toString() override;
    ~Refrigerator() override = default ;
};

class DishWasher: public Appliance {
private:
    double consumation;
public:
    DishWasher(const std::string& id, double consumation);
    double getConsumation();
    double consumedElectricity() override;
    std::string toString() override;
    ~DishWasher() override = default;
};




#endif //APPLIANCE_H
