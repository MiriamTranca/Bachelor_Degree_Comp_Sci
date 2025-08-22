#include <QApplication>
#include <QPushButton>

#include "service.h"
#include "ui.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    service serv;
    std::vector<Astronomer> astros=serv.getAllAstro();
    std::vector<astroWindow*> windows;

    for (auto& astro: astros) {
        astroWindow* window = new astroWindow(astro.getName(),&serv);
        windows.push_back(window);
        window->show();
    }
    for (auto* senderWindow : windows) {
        for (auto* receiverWindow : windows) {
            if (senderWindow!=receiverWindow) {
                QObject::connect(senderWindow, &astroWindow::starAdded,
                                 receiverWindow, &astroWindow::addStarOtherWindows);
            }
        }
    }
    int result = a.exec();
    for (auto* window: windows) {
        delete window;
    }
    return result;
}

