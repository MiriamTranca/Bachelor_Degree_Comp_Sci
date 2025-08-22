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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_test3_carsClass
{
public:

    void setupUi(QWidget *test3_carsClass)
    {
        if (test3_carsClass->objectName().isEmpty())
            test3_carsClass->setObjectName("test3_carsClass");
        test3_carsClass->resize(600, 400);

        retranslateUi(test3_carsClass);

        QMetaObject::connectSlotsByName(test3_carsClass);
    } // setupUi

    void retranslateUi(QWidget *test3_carsClass)
    {
        test3_carsClass->setWindowTitle(QCoreApplication::translate("test3_carsClass", "test3_cars", nullptr));
    } // retranslateUi

};

namespace Ui {
    class test3_carsClass: public Ui_test3_carsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST3_CARS_H
