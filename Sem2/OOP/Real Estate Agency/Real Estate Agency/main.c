
#include <stdlib.h>
#include <crtdbg.h>
#include "repo.h"
#include "services.h"
#include "ui.h"
#include "tests.h"

int main() {

    EstateRepository repo = createEstateRepository();
    EstateService service = createEstateService(&repo);

    handleUserInput(&service);

    destroyEstateRepository(&repo);

    _CrtDumpMemoryLeaks();
    return 0;
}