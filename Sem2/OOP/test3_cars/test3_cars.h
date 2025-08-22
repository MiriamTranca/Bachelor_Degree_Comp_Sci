#pragma once

#include <QtWidgets/QWidget>
#include "ui_test3_cars.h"
#include "Service.h"
class test3_cars : public QWidget
{
    Q_OBJECT

public:
    test3_cars(QWidget *parent = nullptr);
    ~test3_cars();

private:
    Ui::test3_carsClass ui;
    Service service;
    void showAllWithColor();
    void showByMan();
};
