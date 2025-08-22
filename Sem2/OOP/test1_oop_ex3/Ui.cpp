//
// Created by tranc on 3/31/2025.
//

#include "Ui.h"
#include <iostream>
void Ui::printMenu() {
    std::cout<<"Menu"<<std::endl;
    std::cout<<"1. Add Task"<<std::endl;
    std::cout<<"2. Show All Tasks"<<std::endl;
    std::cout<<"3. Show Tasks By Priority"<<std::endl;
    std::cout<<"4. Exit"<<std::endl;
}

void Ui::run() {
    while (true) {
        printMenu();
        std::string input;
        std::cin>>input;
        if (input == "1") {
            try {
                std::string description;
                int minutes, priority;
                std::cout<<"Enter Description: ";
                std::cin>>description;
                std::cout<<"Enter Minutes: ";
                std::cin>>minutes;
                std::cout<<"Enter Priority: ";
                std::cin>>priority;
                this->service.addTaskService(description, minutes, priority);
                std::cout<<"Task Added"<<std::endl;
            }
            catch (const std::exception& e) {
                std::cout<<e.what()<<std::endl;
            }
        }
        else if (input == "2") {
            std::vector<Task> tasks = this->service.showAllTasks();
            for (int i=0;i<tasks.size();i++) {
                std::cout<<tasks[i].getDescription()<<" | "<< tasks[i].getMinutes()<<" | "<< tasks[i].getPriority()<< std::endl;
            }

        }
        else if (input == "3") {
            int p;
            std::cout<<"Enter Priority: ";
            std::cin>>p;
            std::vector<Task> tasks = this->service.showTasksPriority(p);
            tasks = this->service.sortTasks(tasks);
            for (int i=0;i<tasks.size();i++) {
                std::cout<<tasks[i].getDescription()<<" | "<< tasks[i].getMinutes()<<" | "<< tasks[i].getPriority()<< std::endl;
            }
        }
        else if (input == "4") {
            break;
        }
    }
}
