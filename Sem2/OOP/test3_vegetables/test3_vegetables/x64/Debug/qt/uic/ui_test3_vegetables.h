/********************************************************************************
** Form generated from reading UI file 'test3_vegetables.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST3_VEGETABLES_H
#define UI_TEST3_VEGETABLES_H

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

class Ui_test3_vegetablesClass
{
public:
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QListWidget *listOfFamilies;
    QVBoxLayout *verticalLayout;
    QLineEdit *giveVegetable;
    QPushButton *searchButton;
    QLineEdit *showParts;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QListWidget *listWidget;

    void setupUi(QWidget *test3_vegetablesClass)
    {
        if (test3_vegetablesClass->objectName().isEmpty())
            test3_vegetablesClass->setObjectName("test3_vegetablesClass");
        test3_vegetablesClass->resize(600, 400);
        widget = new QWidget(test3_vegetablesClass);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 10, 526, 312));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(widget);
        label->setObjectName("label");

        verticalLayout_2->addWidget(label);

        listOfFamilies = new QListWidget(widget);
        listOfFamilies->setObjectName("listOfFamilies");

        verticalLayout_2->addWidget(listOfFamilies);


        verticalLayout_4->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");
        giveVegetable = new QLineEdit(widget);
        giveVegetable->setObjectName("giveVegetable");

        verticalLayout->addWidget(giveVegetable);

        searchButton = new QPushButton(widget);
        searchButton->setObjectName("searchButton");

        verticalLayout->addWidget(searchButton);

        showParts = new QLineEdit(widget);
        showParts->setObjectName("showParts");

        verticalLayout->addWidget(showParts);


        verticalLayout_4->addLayout(verticalLayout);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");

        verticalLayout_3->addWidget(label_2);

        listWidget = new QListWidget(widget);
        listWidget->setObjectName("listWidget");

        verticalLayout_3->addWidget(listWidget);


        horizontalLayout->addLayout(verticalLayout_3);


        retranslateUi(test3_vegetablesClass);

        QMetaObject::connectSlotsByName(test3_vegetablesClass);
    } // setupUi

    void retranslateUi(QWidget *test3_vegetablesClass)
    {
        test3_vegetablesClass->setWindowTitle(QCoreApplication::translate("test3_vegetablesClass", "test3_vegetables", nullptr));
        label->setText(QCoreApplication::translate("test3_vegetablesClass", "Families: ", nullptr));
        searchButton->setText(QCoreApplication::translate("test3_vegetablesClass", "Search", nullptr));
        label_2->setText(QCoreApplication::translate("test3_vegetablesClass", "Vegetables of the family:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class test3_vegetablesClass: public Ui_test3_vegetablesClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST3_VEGETABLES_H
