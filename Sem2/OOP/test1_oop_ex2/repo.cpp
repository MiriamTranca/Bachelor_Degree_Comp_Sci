//
// Created by tranc on 3/31/2025.
//

#include "repo.h"

#include <string.h>

repo::repo() {
    addSchoolRepo(school("Avram Iancu", "46.77, 23.60", "15.04.2022", true));
    addSchoolRepo(school("George Cosbuc", "46.77, 23.58", "18.04.2022", false));
    addSchoolRepo(school("Alexandru Vaida", "46.77, 23.63", "23.04.2022", false));
    addSchoolRepo(school("Romulus", "46.77, 23.57", "04.05.2022", false));
    addSchoolRepo(school("Transilvania", "46.77, 23.33", "03.05.2022", false));
}

bool repo::addSchoolRepo(const school &newSchool) {
    this->schools.push_back(newSchool);
    return true;
}

/**
 * Function to delete an element from the repository
 * @param thisSchool
 * @return true, if school if found and deleted, false otherwise
 */
bool repo::removeSchoolRepo(const std::string& thisSchool) {
    for (auto it = this->schools.begin(); it != this->schools.end(); it++) {
        if (it->get_name() == thisSchool) {
            this->schools.erase(it);
            return true;
        }
    }
    return false;
}

std::vector<school> & repo::getSchools() {
    return this->schools;
}
