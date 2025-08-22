//
// Created by tranc on 3/31/2025.
//

#include "Ui.h"
#include <iostream>
void Ui::printMenu() {
    std::cout<<"Menu:"<<std::endl;
    std::cout<<"1. Remove school"<<std::endl;
    std::cout<<"2. Show all schools"<<std::endl;
    std::cout<<"3. Show all schools to be visited"<<std::endl;
    std::cout<<"4.Exit"<<std::endl;
}

void Ui::run() {
    while (true) {
        printMenu();
        std::string input;
        std::cin>>input;
        if(input == "1") {
            try {
                std::string schoolName;
                std::cout<<"Please enter the school name: ";
                std::cin>>schoolName;
                this->Service.removeSchoolService(schoolName);
                std::cout<<"School deleted";
            }
            catch (const std::invalid_argument& e) {
                std::cout<<e.what()<<std::endl;
            }
        }
        else if(input == "2") {
            std::vector<school> schools = this->Service.getSchoolsSorted();
            for (auto& school : schools) {
                std::cout<<school.get_name()<<" | "<<school.get_address()<<" | "<<school.get_date()<<" | "<<school.get_visited()<<std::endl;
            }
        }
        else if(input == "3") {
            std::string d;
            std::cout<<"Please enter date: ";
            std::cin>>d;
            this->Service.markSchoolsVisited(d);
            std::vector<school> schools = this->Service.getSchoolsToVisit();
            for (auto& school : schools) {
                std::cout<<school.get_name()<<" | "<<school.get_address()<<" | "<<school.get_date()<<" | "<<school.get_visited()<<std::endl;
            }
        }
        else if(input == "4") {
            break;
        }
    }
}
