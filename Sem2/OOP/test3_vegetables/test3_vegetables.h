#pragma once

#include <QtWidgets/QWidget>
#include "ui_test3_vegetables.h"
#include "Service.h"
class test3_vegetables : public QWidget
{
    Q_OBJECT

public:
    test3_vegetables(QWidget *parent = nullptr);
    ~test3_vegetables();

private:
    Ui::test3_vegetablesClass ui;
    Service serv;
    void showFamilies();
    void showVegForFamilies(QListWidgetItem* item);
    void showFamAndParts();
};
