//
// Created by tranc on 5/2/2025.
//

#include "MedicalAnalysis.h"

MedicalAnalysis::MedicalAnalysis(const std::string& date): date(date){}

BMI::BMI(const std::string& date, double value): MedicalAnalysis(date), value(value) {}

bool BMI::isResultOK() {
    if (value<18.5 || value > 25) {
        return false;
    }
    return true;
}

std::string BMI::toString() {
    std::string result;
    if (isResultOK()) {
        result = "true";
    }
    else {
        result = "false";
    }
    return "BMI,"+date +"," + std::to_string(value) +","+ result;
}

BP::BP(const std::string &date, int systolicValue, int diastolicValue) : MedicalAnalysis(date), systolicValue(systolicValue), diastolicValue(diastolicValue){}

bool BP::isResultOK() {
    if (systolicValue < 90 || systolicValue > 119 || diastolicValue < 60 || diastolicValue > 79) {
        return false;
    }
    return true;
}

std::string BP::toString() {
    std::string result;
    if (isResultOK()) {
        result = "true";
    }
    else {
        result = "false";
    }
    return "BP,"+date +"," + std::to_string(systolicValue) + "," + std::to_string(diastolicValue) +","+ result;
}


