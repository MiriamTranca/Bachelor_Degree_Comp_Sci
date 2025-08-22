//
// Created by tranc on 5/7/2025.
//

#include "UI.h"

#include <iostream>

void UI::printMenu() {
    std::cout<<"1. Add building\n";
    std::cout<<"2. Show all\n";
    std::cout<<"3. Save to file\n";
    std::cout<<"0. Exit\n";
}

void UI::run() {
    std::string build, c, add, type, file1, file2;
    int year, occ, apart;
    bool hist;
    while (true) {
        printMenu();
        std::cin>>c;
        if (c=="1") {
            std::cout<<"Building: ";
            std::cin>>build;
            std::cout<<"Give add: ";
            std::cin>>add;
            std::cout<<"Give year: ";
            std::cin>>year;
            if (build=="Block") {
                std::cout<<"Give apart: ";
                std::cin>>apart;
                std::cout<<"Give occupied: ";
                std::cin>>occ;
                serv.addB(std::make_shared<Block>(add,year,apart,occ));
            }
            else {
                std::cout<<"Give type: ";
                std::cin>>type;
                std::cout<<"Give hist: ";
                std::cin>>hist;
                serv.addB(std::make_shared<House>(add,year,type,hist));
            }
        }else if (c=="2") {
            const auto& b=serv.showAll();
            for (int i=0;i<b.size();i++) {
                std::cout<<b[i]->toString();
            }
        }else if (c=="3") {
            std::cout<<"Give file restored: ";
            std::cin>>file1;
            std::cout<<"Give file demolished: ";
            std::cin>>file2;
            serv.writeToFile(file1,file2);

        }else if (c=="0") {
            return;
        }
    }
}
