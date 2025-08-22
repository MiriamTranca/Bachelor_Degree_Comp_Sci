//
// Created by tranc on 5/5/2025.
//
#include <iostream>
#include "UI.h"

#include <emmintrin.h>

void UI::menu() {
    std::cout<<"1.Add appl\n";
    std::cout<<"2.Show all\n";
    std::cout<<"3.Show innef\n";
    std::cout<<"4.Save to file\n";
    std::cout<<"0.Exit\n";
}

void UI::run() {
    std::string c,c1,id ,type, filename;
    bool has;
    double cons, maxEl;
    while (true) {
        menu();
        std::cin>>c;
        if (c=="1") {
            std::cout<<"Refrigirator or dishwasher\n";
            std::cin>> c1;
            if (c1 == "1") {
                std::cout<<"Give id\n";
                std::cin>> id;
                std::cout<<"Give type(A or A++)\n";
                std::cin>> type;
                std::cout<<"Has freezer\n";
                std::cin>> has;
                service.addAppliance(std::make_shared<Refrigerator>(id,type,has));
                std::cout<<"Added\n";
            }
            else {
                std::cout<<"Give id\n";
                std::cin>> id;
                std::cout<<"Give cons\n";
                std::cin>> cons;
                service.addAppliance(std::make_shared<DishWasher>(id,cons));
                std::cout<<"Added\n";
            }
        } else if (c == "2") {
            const auto& appl = service.getAll();
            for (int i=0;i<appl.size();i++) {
                std::cout<<appl[i]->toString()<<std::endl;
            }

        }else if (c=="3") {
            const auto& appl = service.getAll();
            for (int i=0;i<appl.size();i++) {
                if (appl[i]->consumedElectricity()>100) {
                    std::cout<<appl[i]->toString()<<std::endl;
                }
            }
        }else if (c=="4") {
            std::cout<<"Give filename: ";
            std::cin>>filename;
            std::cout<<"Give max el: ";
            std::cin>>maxEl;
            service.writeToFile(filename,maxEl);
        }else if (c=="0") {
            return;
        }
    }
}
