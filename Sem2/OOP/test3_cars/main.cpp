#include "test3_cars.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    test3_cars w;
    w.show();
    return a.exec();
}
