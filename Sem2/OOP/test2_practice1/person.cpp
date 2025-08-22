
#include "person.h"
#include <string>
#include <fstream>
#include <iostream>

Person::Person(const std::string &name): name(name) {
    analyses.push_back(std::make_shared<BMI>("2025.05.01", 22.5));
    analyses.push_back(std::make_shared<BP>("2025.05.02", 110, 70));
}

void Person::addAnalysis(std::shared_ptr<MedicalAnalysis> a) {
    analyses.push_back(std::move(a));
}

const std::vector<std::shared_ptr<MedicalAnalysis>>& Person::getAllAnalyses() {
    return analyses;
}

std::vector<std::shared_ptr<MedicalAnalysis>> Person::getAnalysesByMonth(int month) {
    std::vector<std::shared_ptr<MedicalAnalysis>> analysesMonth;
    for (int i=0;i < analyses.size();i++) {
        std::string date = analyses[i]->getDate();
        int aMonth = stoi(date.substr(5,2));
        if (month == aMonth) {
            analysesMonth.push_back(analyses[i]);
        }
    }
    return analysesMonth;
}

std::vector<std::shared_ptr<MedicalAnalysis>> Person::getBetweenDates(const std::string& date1,const std::string& date2) {
    std::vector<std::shared_ptr<MedicalAnalysis>> analysesDates;
    for (int i=0;i < analyses.size();i++) {
        if (analyses[i]->getDate()>date1 && analyses[i]->getDate()<date2) {
            analysesDates.push_back(analyses[i]);
        }
    }
    return analysesDates;
}

bool Person::isIll(int month) {
    std::vector<std::shared_ptr<MedicalAnalysis>> analysesMonth = this->getAnalysesByMonth(month);
    for (int i=0;i<analysesMonth.size();i++) {
        if (analysesMonth[i]->isResultOK()) {
            return false;
        }
    }
    return true;
}

void Person::writeToFile(const std::string& filename,const std::string& date1,const std::string& date2) {
    std::ofstream fout(filename);
    if (!fout) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    std::vector<std::shared_ptr<MedicalAnalysis>> analysesDates=this->getBetweenDates(date1,date2);
    for (const auto& analysis : analysesDates) {
        fout<< analysis->toString()<< std::endl;
    }
    fout.close();
}


