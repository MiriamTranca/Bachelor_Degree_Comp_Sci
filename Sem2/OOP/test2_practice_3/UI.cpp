//
// Created by tranc on 5/6/2025.
//
#include <iostream>
#include "UI.h"
#include <string>

void UI::printMenu() {
    std::cout<<"1. Add department.\n";
    std::cout<<"2. Show all.\n";
    std::cout<<"3. Show efficient.\n";
    std::cout<<"4. Save to file.\n";
    std::cout<<"0. Exit.\n";
}

void UI::run() {
    std::string c;
    while (true) {
        printMenu();
        std::cin>>c;
        if (c=="1") {
            std::string name;
            int doctors, patiens, mothers, newborns;
            double grade;
            std::cout<<"Give name: ";
            std::cin>>name;
            std::cout<<"Doctors: ";
            std::cin>>doctors;
            if (name == "Surgery") {
                std::cout<<"Give patients: ";
                std::cin>>patiens;
                controller.addDepart(std::make_shared<Surgery>(name,doctors,patiens));
            }
            else {
                std::cout<<"Give mothers: ";
                std::cin>>mothers;
                std::cout<<"Give newborns: ";
                std::cin>>newborns;
                std::cout<<"Give grade: ";
                std::cin>>grade;
                controller.addDepart(std::make_shared<Neonatal>(name,doctors,mothers,newborns,grade));
            }

        } else if (c=="2") {
            const auto& dep = controller.showAll();
            for (int i=0;i<dep.size();i++) {
                std::cout<<dep[i]->toString()<<"\n";
            }

        }else if (c=="3") {
            const auto& eff = controller.showEff();
            for (int i=0;i<eff.size();i++) {
                std::cout<<eff[i]->toString()<<"\n";
            }

        }else if (c=="4") {
            std::string filename;
            std::cout<<"Give file: ";
            std::cin>>filename;
            controller.saveToFile(filename);

        }else if (c=="0") {
            return;
        }
    }
}
