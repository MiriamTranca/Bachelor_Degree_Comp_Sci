//
// Created by tranc on 5/2/2025.
//
#include <iostream>
#include "ui.h"

void ui::printMenu() {
    std::cout<< "1.Add new analysis."<<std::endl;
    std::cout<< "2.Show all analysis."<<std::endl;
    std::cout<<"3.Is ill"<<std::endl;
    std::cout<<"4.Save to  file."<<std::endl;
    std::cout<<"0.Exit"<<std::endl;
}

void ui::run() {
    char choice;
    while (true) {
        printMenu();
        std::cin>>choice;
        if (choice =='1') {
            std::string type, date;
            int value;
            double systolicValue, diastolicValue;
            std::cout<<"Give type: \n";
            std::cin>>type;
            std::cout<<"Give date(yyyy.mm.dd): \n";
            std::cin>>date;
            if (type == "BMI") {
                std::cout<<"Give value: \n";
                std::cin>>value;
                person.addAnalysis(std::make_unique<BMI>(date, value));
            }
            else {
                std::cout<<"Give systolic: \n";
                std::cin>>systolicValue;
                std::cout<<"Give distolic: \n";
                std::cin>>diastolicValue;
                person.addAnalysis(std::make_unique<BP>(date,systolicValue,diastolicValue));

            }
        } else if (choice == '2') {
            const auto& analyses = person.getAllAnalyses();

            for (const auto& analysis : analyses) {
                std::cout << analysis->toString() << std::endl;
            }

        } else if (choice == '3') {
            int month;
            std::cout << "Enter month (1-12): ";
            std::cin >> month;

            if (person.isIll(month)) {
                std::cout << "The person is ill for the given month." << std::endl;
            } else {
                std::cout << "The person's health analyses are within normal limits." << std::endl;
            }

        } else if (choice == '4') {
            std::string filename, date1, date2;
            std::cout << "Enter filename: ";
            std::cin >> filename;
            std::cout << "Enter start date (yyyy.mm.dd): ";
            std::cin >> date1;
            std::cout << "Enter end date (yyyy.mm.dd): ";
            std::cin >> date2;

            person.writeToFile(filename, date1, date2);
            std::cout << "Analyses saved to " << filename << std::endl;
        } else if (choice == '0') {
            return;
        }
    }
}
