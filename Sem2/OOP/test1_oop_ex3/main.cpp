#include "Repo.h"
#include "Service.h"
#include "Tests.h"
#include "Ui.h"

int main() {
    Tests tests;
    tests.AllTests();
    Repo repo;
    Service service(repo);
    Ui ui(service);
    ui.run();

    return 0;
}
