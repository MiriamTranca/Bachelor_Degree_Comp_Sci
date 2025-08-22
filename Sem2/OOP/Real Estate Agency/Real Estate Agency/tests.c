#include <assert.h>
#include "domain.h"
#include "repo.h"
#include "services.h"

void testCreateEstate() {
    Estate estate = createEstate("123 Test St", "house", 100.0, 50000.0);

    assert(strcmp(estate.address, "123 Test St") == 0);
    assert(strcmp(estate.type, "house") == 0);
    assert(estate.surface == 100.0);
    assert(estate.price == 50000.0);
}

void testGetEstateAddress() {
    Estate estate = createEstate("123 Test St", "house", 100.0, 50000.0);

    assert(strcmp(getEstateAddress(&estate), "123 Test St") == 0);
}

void testGetEstateType() {
    Estate estate = createEstate("123 Test St", "house", 100.0, 50000.0);

    assert(strcmp(getEstateType(&estate), "house") == 0);
}

void testGetEstateSurface() {
    Estate estate = createEstate("123 Test St", "house", 100.0, 50000.0);

    assert(getEstateSurface(&estate) == 100.0);
}

void testGetEstatePrice() {
    Estate estate = createEstate("123 Test St", "house", 100.0, 50000.0);

    assert(getEstatePrice(&estate) == 50000.0);
}

void testCreateEstateRepository() {
    EstateRepository repo = createEstateRepository();

    assert(repo.size == 10); 
    assert(repo.capacity == 10); 
}

void testAddEstate() {
    EstateRepository repo = createEstateRepository();
    Estate newEstate = createEstate("999 New St", "house", 120.0, 40000.0);

    addEstate(&repo, newEstate);
    assert(repo.size == 11);  
    assert(strcmp(repo.estates[repo.size - 1].address, "999 New St") == 0);
}

void testDeleteEstate() {
    EstateRepository repo = createEstateRepository();

    deleteEstate(&repo, "123");
    assert(repo.size == 9);  
    Estate* estate = findEstateByAddress(&repo, "123");
    assert(estate == NULL);  
}

void testUpdateEstate() {
    EstateRepository repo = createEstateRepository();
    Estate updatedEstate = createEstate("123", "house", 140.0, 30000.0);

    int result = updateEstate(&repo, "123", updatedEstate);
    assert(result == 1);  
    Estate* estate = findEstateByAddress(&repo, "123");
    assert(estate != NULL);
    assert(estate->surface == 140.0);
    assert(estate->price == 30000.0);
}

void testFindEstateByAddress() {
    EstateRepository repo = createEstateRepository();

    Estate* estate = findEstateByAddress(&repo, "123");
    assert(estate != NULL);
    assert(strcmp(estate->address, "123") == 0);

    Estate* nonExistentEstate = findEstateByAddress(&repo, "nonexistent");
    assert(nonExistentEstate == NULL);  
}

void testCreateEstateService() {
    EstateRepository repo = createEstateRepository();
    EstateService service = createEstateService(&repo);

    assert(service.repo == &repo);
}

void testGetFilteredEstatesByTypeAndSurface() {
    EstateRepository repo = createEstateRepository();
    EstateService service = createEstateService(&repo);

    int count;
    Estate* filtered = getFilteredEstatesByTypeAndSurface(&service, "house", 100.0, &count);

    assert(count > 0); 
    for (int i = 0; i < count; i++) {
        assert(filtered[i].surface > 100.0);
        assert(strcmp(filtered[i].type, "house") == 0);
    }
    free(filtered);
}

void testGetFilteredEstatesByAddress() {
    EstateRepository repo = createEstateRepository();
    EstateService service = createEstateService(&repo);

    int count;
    Estate* filtered = getFilteredEstatesByAddress(&service, "Test", &count);

    assert(count > 0); 
    for (int i = 0; i < count; i++) {
        assert(strstr(filtered[i].address, "Test") != NULL);
    }
    free(filtered);
}

void testGetSortedEstates() {
    EstateRepository repo = createEstateRepository();
    EstateService service = createEstateService(&repo);

    int count;
    Estate* sorted = getSortedEstates(&service, "Test", &count);

    assert(count > 0); 
    for (int i = 1; i < count; i++) {
        assert(sorted[i - 1].price >= sorted[i].price);  
    }
    free(sorted);
}
void testCreateActionStack() {
    ActionStack stack = createActionStack();

    assert(stack.size == 0);
    assert(stack.capacity == 10);
}

void testPushAction() {
    ActionStack stack = createActionStack();
    Estate estate = createEstate("123", "house", 100.0, 50000.0);
    Action action = { ADD, estate, "" };

    pushAction(&stack, action);

    assert(stack.size == 1);
    assert(stack.actions[0].type == ADD);
}

void testPopAction() {
    ActionStack stack = createActionStack();
    Estate estate = createEstate("123", "house", 100.0, 50000.0);
    Action action = { ADD, estate, "" };

    pushAction(&stack, action);
    Action poppedAction = popAction(&stack);

    assert(stack.size == 0);
    assert(poppedAction.type == ADD);
}

void testUndoRedo() {
    EstateRepository repo = createEstateRepository();
    EstateService service = createEstateService(&repo);
    ActionStack undoStack = createActionStack();
    ActionStack redoStack = createActionStack();

    Estate estate1 = createEstate("999", "house", 120.0, 40000.0);
    addEstate(&repo, estate1);
    Action addAction = { ADD, estate1, "" };
    pushAction(&undoStack, addAction);

    undo(&service, &undoStack, &redoStack); 
    assert(repo.size == 10);  

    redo(&service, &undoStack, &redoStack);
    assert(repo.size == 11);  
}

void testAll() {
	testCreateEstate();
	testGetEstateAddress();
	testGetEstateType();
	testGetEstateSurface();
	testGetEstatePrice();
	testCreateEstateRepository();
	testAddEstate();
	testDeleteEstate();
	testUpdateEstate();
	testFindEstateByAddress();
	testCreateEstateService();
	testGetFilteredEstatesByTypeAndSurface();
	testGetFilteredEstatesByAddress();
	testGetSortedEstates();
	testCreateActionStack();
	testPushAction();
	testPopAction();
	testUndoRedo();
    printf("All tests passed!\n");
}