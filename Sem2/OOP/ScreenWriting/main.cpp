#include <QtWidgets/QApplication>

#include "Service.h"
#include "UI.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Service service;
    vector<Writers> writers=service.getAllWriters();
    ApplicationController controller(&service);
    for (auto writer : writers) {
        controller.createWriterWindow(QString::fromStdString(writer.getName()));
    }
    return app.exec();
}