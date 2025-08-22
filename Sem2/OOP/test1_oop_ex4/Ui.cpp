//
// Created by tranc on 4/1/2025.
//

#include "Ui.h"
#include <iostream>

void Ui::showMenu() {
    std::cout<<"Print menu:"<<std::endl;
    std::cout<<"1.Add patient"<<std::endl;
    std::cout<<"2.Show all patients"<<std::endl;
    std::cout<<"3.Show infected patients"<<std::endl;
    std::cout<<"4.Exit"<<std::endl;
}

void Ui::run() {
    while (true) {
        showMenu();
        std::string input;
        std::cin>>input;
        if (input == "1") {
            std::string name;
            int age, room;
            bool infected;
            std::cout<<"Give name: ";
            std::cin>>name;
            std::cout<<"Give age: ";
            std::cin>>age;
            std::cout<<"Give infected: ";
            std::cin>>infected;
            std::cout<<"Give room: ";
            std::cin>>room;
            try {
                this->service.addPatientService(name,age, infected, room);
                std::cout<<"Patient added"<<std::endl;
            } catch (const std::exception& e) {
                std::cout<<e.what()<<std::endl;
            }
        }
        else if (input == "2") {
            std::vector<Patient> patients = this->service.showALL();
            for (int i=0;i<patients.size();i++) {
                std::cout<<patients[i].get_name()<<" | "<<patients[i].get_age()<<" | "<<patients[i].get_infected()<<" | "<<patients[i].get_room()<<std::endl;
            }
        }
        else if (input == "3") {
            int age;
            std::cout<<"Give age: ";
            std::cin>>age;
            this->service.updateStatus(age);
            std::vector<Patient> infected_patients = this->service.infectedPatients();
            for (int i=0;i<infected_patients.size();i++) {
                std::cout<<infected_patients[i].get_name()<<" | "<<infected_patients[i].get_age()<<" | "<<infected_patients[i].get_infected()<<" | "<<infected_patients[i].get_room()<<std::endl;
            }
        }
        else if (input == "4") {
            break;
        }
    }
}
