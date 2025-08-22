//
// Created by tranc on 5/6/2025.
//

#ifndef HOSPITALDEPARTMENT_H
#define HOSPITALDEPARTMENT_H
#include <string>


class HospitalDepartment {
protected:
    std::string name;
    int doctors;
public:
    HospitalDepartment(const std::string& name, int doctors);
    virtual bool isEfficient()=0;
    virtual std::string toString()=0;
    virtual ~HospitalDepartment()=default;
};

class Surgery: public HospitalDepartment {
private:
    int patients;
public:
    Surgery(const std::string& name, int doctors, int patients);
    bool isEfficient() override;
    std::string toString() override;
    ~Surgery() override = default;
};

class Neonatal: public HospitalDepartment {
private:
    int mothers;
    int newborns;
    double grade;
public:
    Neonatal(const std::string& name, int doctors, int mothers, int newborns, double grade);
    bool isEfficient() override;
    std::string toString() override;
    ~Neonatal()override =default;
};


#endif //HOSPITALDEPARTMENT_H
