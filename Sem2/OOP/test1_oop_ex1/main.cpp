#include "UI.h"
#include "Repository.h"
#include "Service.h"

int main() {
    Repository repo;
    Service service(repo);
    UI Ui(service);
    Ui.run();
    return 0;
}
