
#ifndef PERSON_H
#define PERSON_H
#include <memory>
#include <string>
#include <vector>
#include "MedicalAnalysis.h"

class Person {
    private:
      std::string name;
      std::vector<std::shared_ptr<MedicalAnalysis>> analyses;
public:
    Person() = default;
    explicit Person(const std::string& name);
    void addAnalysis(std::shared_ptr<MedicalAnalysis> a);
    const std::vector<std::shared_ptr<MedicalAnalysis>>& getAllAnalyses();
    std::vector<std::shared_ptr<MedicalAnalysis>> getAnalysesByMonth(int month);
    std::vector<std::shared_ptr<MedicalAnalysis>> getBetweenDates(const std::string& date1,const std::string& date2);
    bool isIll(int month);
    void writeToFile(const std::string& filename,const std::string& date1,const std::string& date2);
    ~Person() = default;
};



#endif //PERSON_H
