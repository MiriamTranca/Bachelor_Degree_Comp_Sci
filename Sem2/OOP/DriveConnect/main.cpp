#include <QApplication>
#include <QMainWindow>

#include "Domain.h"
#include "Service.h"
#include "UI.h"
using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Service service;
    vector<Driver> drivers=service.getAllDrivers();
    vector<WindowDriver*> windows;
    for (auto driver : drivers) {
        WindowDriver* window = new WindowDriver(driver.getName(),&service);
        windows.push_back(window);
        window->show();
    }
    for (auto transmitterWindow : windows) {
        for (auto receiverWindow : windows) {
            if (transmitterWindow!=receiverWindow) {
                QObject::connect(transmitterWindow,&WindowDriver::Changed,receiverWindow,&WindowDriver::loadReports);
                QObject::connect(transmitterWindow,&WindowDriver::Changed1,receiverWindow,&WindowDriver::loadChats);
            }
        }
    }
    return QApplication::exec();
}
