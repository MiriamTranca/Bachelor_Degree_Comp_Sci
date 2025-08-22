//
// Created by tranc on 6/23/2025.
//

#include "Repository.h"

#include <fstream>
#include <sstream>

vector<Driver> Repository::loadDrivers() {
        vector<Driver> drivers;
        std::ifstream file("C:/Users/tranc/CLionProjects/DriveConnect/drivers.txt");
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string name,latStr,lonStr,scoreStr;
            if (std::getline(ss, name, ',')&&std::getline(ss, latStr, ',')&&std::getline(ss, lonStr, ',')&&std::getline(ss, scoreStr) ) {
                int lat=std::stoi(latStr);
                int lon=std::stoi(lonStr);
                int score=std::stoi(scoreStr);
                drivers.push_back(Driver(name,lat,lon,score));
            }
        }
    file.close();
    return drivers;
}

vector<Report> Repository::loadReports() {
    vector<Report> reports;
    std::ifstream file("C:/Users/tranc/CLionProjects/DriveConnect/reports.txt");
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string desc,reporter,latStr,lonStr,validStr;
        if (std::getline(ss, desc, ',')&&std::getline(ss, reporter, ',')&&std::getline(ss, latStr, ',')&&std::getline(ss, lonStr,',')&&std::getline(ss,validStr) ) {
            int lat=std::stoi(latStr);
            int lon=std::stoi(lonStr);
            bool valid=std::stoi(validStr);
            reports.push_back(Report(desc,reporter,lat,lon,valid));
        }
    }
    file.close();
    return reports;
}

void Repository::saveReports(const vector<Report> &reports) {
        std::ofstream file("C:/Users/tranc/CLionProjects/DriveConnect/reports.txt");
        for (auto report : reports) {
            file <<report.getDesc()<<","<<report.getReporter()<<","<<report.getLat()<<","<<report.getLon()<<","<<report.getValid()<<"\n";
        }
    file.close();
}
