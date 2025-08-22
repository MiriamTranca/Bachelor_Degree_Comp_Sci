#include <cassert>
#include "Repo.h"
#include "Service.h"
#include "Tests.h"
#include <stdexcept>
void Tests::testAddInRepo() {
    Repo repo;
    assert(repo.addPatient(Patient("Ana", 30, false, 2)) == true);
    assert(repo.addPatient(Patient("Ana", 30, false, 2)) == false); // Duplicate should fail
}

void Tests::testAddInService() {
    Repo repo;
    Service service;

    service.addPatientService("John", 25, false, 1);
    assert(service.showALL().size() == 6); // 5 default patients + 1 new

    try {
        service.addPatientService("John", 25, false, 1);
        assert(false); // Should not reach here
    } catch (const std::invalid_argument &e) {
        assert(true); // Exception expected
    }
}

void Tests::testUpdateInfected() {
    Repo repo;
    Service service;

    service.updateStatus(35);

    std::vector<Patient> infected = service.infectedPatients();
    bool newInfection = false;
    for (auto &patient : infected) {
        if (patient.get_age() > 35) {
            newInfection = true;
        }
    }
    assert(newInfection == true);
}

void Tests::allTests() {
    testAddInRepo();
    testAddInService();
    testUpdateInfected();
}
