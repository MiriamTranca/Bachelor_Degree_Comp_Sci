//
// Created by tranc on 3/31/2025.
//

#include "Tests.h"
#include <cassert>
#include <stdexcept>

#include "Repo.h"
#include "Service.h"

void Tests::testsRepo() {
    Repo repo;
    Task task = Task("OOP",12 ,3);
    assert(repo.addTask(task)==true);
    assert(repo.addTask(task)==false);
}

void Tests::testsService() {
    Repo repo;
    Service service(repo);
    Task task = Task("OOP",12 ,3);
    /*repo.addTask(task);

    try {
        service.addTaskService("OOP", 12, 3);
        assert(false && "Expected std::invalid_argument, but no exception was thrown.");
    } catch (const std::invalid_argument&) {
    }
    service.addTaskService("OOP", 12, 3);
    service.addTaskService("DSA", 15, 2);
    service.addTaskService("AI", 10, 1);

    std::vector<Task> filteredTasks = service.showTasksPriority(3);
    assert(filteredTasks.size() == 2);
    assert(filteredTasks[0].getDescription() == "DSA");
    assert(filteredTasks[1].getDescription() == "AI");
*/
}

void Tests::AllTests() {
    testsRepo();
    testsService();
}
