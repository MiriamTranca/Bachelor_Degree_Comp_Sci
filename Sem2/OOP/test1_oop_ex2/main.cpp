#include "repo.h"
#include "service.h"
#include "Ui.h"
#include "test.cpp"

int main() {
    //testAll();
    repo Repo;
    service Service(Repo);
    Ui ui(Service);
    ui.run();
    return 0;
}