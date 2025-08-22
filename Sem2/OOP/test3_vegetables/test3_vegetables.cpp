#include "test3_vegetables.h"

test3_vegetables::test3_vegetables(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    connect(ui.searchButton, &QPushButton::clicked, this, &test3_vegetables::showFamAndParts);
    showFamilies();
}

test3_vegetables::~test3_vegetables()
{}

void test3_vegetables::showFamilies()
{
   ui.listOfFamilies->clear();
   std::vector<std::string> families = serv.getFamilies();
   for (const std::string& family : families) {
       QString itemText = QString::fromStdString(family);
       QListWidgetItem* item = new QListWidgetItem(itemText);
       ui.listOfFamilies->addItem(item);
   }
   connect(ui.listOfFamilies, &QListWidget::itemClicked, this, &test3_vegetables::showVegForFamilies);
}

void test3_vegetables::showVegForFamilies(QListWidgetItem* item)
{
    ui.listWidget->clear();
    std::string family = item->text().toStdString();
    std::vector<Domain> veg = serv.getForFamily(family);
    for (const Domain& v : veg) {
        QString vegText = QString::fromStdString(v.getName() + " | " + v.getList());
        ui.listWidget->addItem(vegText);
    }   

}

void test3_vegetables::showFamAndParts()
{
    QString vegetable = ui.giveVegetable->text();
    for (int i = 0; i < serv.getAll().size(); i++) {
        if (serv.getAll()[i].getName() == vegetable) {
            for (int j = 0; j < ui.listOfFamilies->count(); ++j) {
                QListWidgetItem* item = ui.listOfFamilies->item(j);
                if (item->text().toStdString() == serv.getAll()[i].getFamily()) {
                    ui.listOfFamilies->setCurrentItem(item);
                    break;
                }
            }
            ui.showParts->setText(QByteArray::fromStdString(serv.getAll()[i].getList()));
        }
    }
}
