//
// Created by tranc on 5/2/2025.
//

#ifndef MEDICALANALYSIS_H
#define MEDICALANALYSIS_H
#include <string>


class MedicalAnalysis {
protected:
    std::string date;
public:
    explicit MedicalAnalysis(const std::string& date);
    bool virtual isResultOK()=0;
    std::string virtual toString()=0;
    std::string getDate(){return this->date;}
    virtual ~MedicalAnalysis()= default;
};

class BMI: public MedicalAnalysis {
private:
    double value;
public:
    BMI(const std::string& date, double value);
    bool isResultOK() override;
    std::string toString() override
    ~BMI() override = default;
};

class BP: public MedicalAnalysis {
private:
    int systolicValue;
    int diastolicValue;
public:
    BP(const std::string& date, int systolicValue, int diastolicValue);
    bool isResultOK() override;
    std::string toString() override;
    ~BP() override = default;
};


#endif //MEDICALANALYSIS_H
