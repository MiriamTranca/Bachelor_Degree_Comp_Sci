//
// Created by tranc on 6/23/2025.
//

#include "Service.h"

#include <cmath>
#include <qstring.h>
#include <stdexcept>

vector<Driver> Service::getAllDrivers() {\
    return repo.loadDrivers();
}

vector<Report> Service::getAllReports() {
    return repo.loadReports();
}

vector<Report> Service::getAllReportsForDriver(const string &nameDr) {
    vector<Report>reports=repo.loadReports();
    vector<Report>reportsDriver;
    Driver dr = repo.loadDrivers()[0];
    for (auto driver : repo.loadDrivers()) {
        if (driver.getName() == nameDr) {
            dr = driver;
        }
    }
    for (auto report: reports) {
        double distance = ::sqrt((dr.getLat()-report.getLat())*(dr.getLat()-report.getLat())+(dr.getLon()-report.getLon())*(dr.getLon()-report.getLon()));
        if (distance<=10.0) {
            reportsDriver.push_back(report);
        }
    }
    return reportsDriver;
}

void Service::addReport(int lat, int lon, const string &desc, const string &nameDr) {
    vector<Report>reports=repo.loadReports();
    Driver dr = repo.loadDrivers()[0];
    for (auto driver : repo.loadDrivers()) {
        if (driver.getName() == nameDr) {
            dr = driver;
        }
    }
    double distance = ::sqrt((dr.getLat()-lat)*(dr.getLat()-lat)+(dr.getLon()-lon)*(dr.getLon()-lon));
    if (distance>20.0 || desc=="" ) {
        throw runtime_error("Invalid report");
    }
    reports.push_back(Report(desc,nameDr,lat,lon,false));
    repo.saveReports(reports);
}

void Service::validateReport(QListWidgetItem* item, const string& currentDriver) {
    vector<Report> reports = repo.loadReports();
    bool updated = false;

    for (auto& report : reports) {
        string fullText = report.getDesc() + " " + report.getReporter() + " " +
                          to_string(report.getLat()) + " " + to_string(report.getLon()) + " " +
                          to_string(report.getValid());

        if (QString::fromStdString(fullText) == item->text()) {
            if (report.getReporter() == currentDriver) return; // can't validate your own report
            if (report.getValid()) return;

            report.setValidation();

            if (report.getValidation() >= 2) {
                report = Report(report.getDesc(), report.getReporter(), report.getLat(), report.getLon(), true);
            }

            updated = true;
            break;
        }
    }

    if (updated) {
        repo.saveReports(reports);
    }
}
