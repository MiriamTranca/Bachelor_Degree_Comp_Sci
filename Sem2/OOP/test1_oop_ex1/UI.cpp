#include "UI.h"
#include <iostream>

void UI::printMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Add new car.\n";
    std::cout << "2. Delete car.\n";
    std::cout << "3. Print all cars.\n";
    std::cout << "4. Print vintage cars.\n";
    std::cout << "5. Exit.\n";
}

void UI::run() {
    while (true) {
        printMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                try {
                    std::cout << "Enter manufacturer name: ";
                    std::string man_name;
                    std::cin >> man_name;

                    std::cout << "Enter model: ";
                    std::string model;
                    std::cin >> model;

                    std::cout << "Enter year: ";
                    int year;
                    std::cin >> year;

                    std::cout << "Enter color: ";
                    std::string colour;
                    std::cin >> colour;

                    this->service.addCarService(man_name, model, year, colour);
                    std::cout << "Car added successfully!\n";
                }
                catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                break;
            }

            case 2: {
                std::cout << "Enter model: ";
                std::string model;
                std::cin >> model;

                std::cout << "Enter year: ";
                int year;
                std::cin >> year;

                this->service.removeCarService(model, year);
                break;
            }

            case 3: {
                std::vector<Car> cars = this->service.displayAllSorted();
                std::cout << "\nAll Cars (Sorted by Manufacturer & Model):\n";
                for (const auto& car : cars) {
                    std::cout << car.getManName() << " | " << car.getModel() << " | " << car.getYear() << " | " << car.getColour() << std::endl;
                }
                break;
            }

            case 4: {
                std::vector<Car> vintageCars = this->service.displayVintage();
                std::cout << "\nVintage Cars (Older than 45 years, sorted by color):\n";
                for (const auto& car : vintageCars) {
                    std::cout << car.getManName() << " | " << car.getModel() << " | " << car.getYear() << " | " << car.getColour() << std::endl;
                }
                break;
            }

            case 5:
                std::cout << "Exiting program...\n";
                return;

            default:
                std::cout << "Invalid choice. Please enter a valid option.\n";
                break;
        }
    }
}
