
#include "service.h"


#include <algorithm>
#include <iomanip>
#include <stdexcept>

bool service::compareDates(const std::string &date1, const std::string &date2) {
    std::istringstream ss1(date1);
    std::istringstream ss2(date2);
    std::tm tm1 = {}, tm2 = {};
    ss1 >> std::get_time(&tm1, "%Y-%m-%d");
    ss2 >> std::get_time(&tm2, "%Y-%m-%d");
    return std::mktime(&tm1) < std::mktime(&tm2);
}

/**
 * Function throws exception if school cannot be deleted from the repo
 * @param school
 */
void service::removeSchoolService(const std::string &school) {
    if (!this->Repo.removeSchoolRepo(school)) {
        throw std::invalid_argument("School cannot be deleted");
    }
}

std::vector<school> service::getSchoolsSorted() {
    std::vector<school> schools = this->Repo.getSchools();
    std::sort(schools.begin(), schools.end(), [](school first, school other) {
        return first.get_name() < other.get_name();
    });
    return schools;
}

/**
 * Function to check if schools where visited
 * @param d : string of the date
 */
void service::markSchoolsVisited(const std::string &d) {
    for (auto&  s: this->Repo.getSchools()) {
        if (this->compareDates(d, s.get_name())) {
            s.set_visited(true);
        }
    }
}

std::vector<school> service::getSchoolsToVisit() {
    std::vector<school> schoolsToVisit;
    for (auto &s: this->Repo.getSchools()) {
        if (!s.get_visited()) {
            schoolsToVisit.push_back(s);
        }
    }
    return schoolsToVisit;
}
