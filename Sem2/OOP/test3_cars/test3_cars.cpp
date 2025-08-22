#include "test3_cars.h"
#include <string>
test3_cars::test3_cars(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    showAllWithColor();
    connect(ui.showcars, &QPushButton::clicked, this, &test3_cars::showByMan);
}

test3_cars::~test3_cars()
{}

void test3_cars::showAllWithColor()
{
    ui.getAllSorted->clear();
    service.sortByManufacturer();
    for (const Domain& car : service.getAll()) {
        QString itemText = QString::fromStdString(car.getManName() + " " + car.getModel());
        QListWidgetItem* item = new QListWidgetItem(itemText);
        std::string color = car.getColor();  
        QColor qcolor(QString::fromStdString(color));
        item->setBackground(qcolor);

        ui.getAllSorted->addItem(item);
    }

}

void test3_cars::showByMan()
{
    QString manName = ui.gievManName->text();
    std::vector<Domain> cars = service.getAllMan(manName.toStdString());
    ui.getallMan->clear();
    for (const Domain& car : cars) {
        QString itemText = QString::fromStdString(car.getManName() + " " + car.getModel());
        QListWidgetItem* item = new QListWidgetItem(itemText);
        std::string color = car.getColor();
        QColor qcolor(QString::fromStdString(color));
        item->setBackground(qcolor);

        ui.getallMan->addItem(item);
    }
    int number = cars.size();
    QString item = QString::fromStdString(std::to_string(number));
    ui.giveNumberCars->setText(item);

}
