/********************************************************************************
** Form generated from reading UI file 'test3_cars.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST3_CARS_H
#define UI_TEST3_CARS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_test3_carsClass
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListWidget *getAllSorted;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *gievManName;
    QPushButton *showcars;
    QListWidget *getallMan;
    QLineEdit *giveNumberCars;

    void setupUi(QWidget *test3_carsClass)
    {
        if (test3_carsClass->objectName().isEmpty())
            test3_carsClass->setObjectName("test3_carsClass");
        test3_carsClass->resize(600, 400);
        widget = new QWidget(test3_carsClass);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 10, 524, 286));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(widget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        getAllSorted = new QListWidget(widget);
        getAllSorted->setObjectName("getAllSorted");

        verticalLayout->addWidget(getAllSorted);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName("verticalLayout_2");
        gievManName = new QLineEdit(widget);
        gievManName->setObjectName("gievManName");

        verticalLayout_2->addWidget(gievManName);

        showcars = new QPushButton(widget);
        showcars->setObjectName("showcars");

        verticalLayout_2->addWidget(showcars);

        getallMan = new QListWidget(widget);
        getallMan->setObjectName("getallMan");

        verticalLayout_2->addWidget(getallMan);

        giveNumberCars = new QLineEdit(widget);
        giveNumberCars->setObjectName("giveNumberCars");

        verticalLayout_2->addWidget(giveNumberCars);


        horizontalLayout->addLayout(verticalLayout_2);


        retranslateUi(test3_carsClass);

        QMetaObject::connectSlotsByName(test3_carsClass);
    } // setupUi

    void retranslateUi(QWidget *test3_carsClass)
    {
        test3_carsClass->setWindowTitle(QCoreApplication::translate("test3_carsClass", "test3_cars", nullptr));
        label->setText(QCoreApplication::translate("test3_carsClass", "All  cars: ", nullptr));
        gievManName->setText(QCoreApplication::translate("test3_carsClass", "Manufacurer", nullptr));
        showcars->setText(QCoreApplication::translate("test3_carsClass", "Show cars", nullptr));
    } // retranslateUi

};

namespace Ui {
    class test3_carsClass: public Ui_test3_carsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST3_CARS_H
