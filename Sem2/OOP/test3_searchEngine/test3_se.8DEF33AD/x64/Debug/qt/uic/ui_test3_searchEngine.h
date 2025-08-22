/********************************************************************************
** Form generated from reading UI file 'test3_searchEngine.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST3_SEARCHENGINE_H
#define UI_TEST3_SEARCHENGINE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_test3_searchEngineClass
{
public:
    QListWidget *listAllDocs;
    QLabel *label;
    QLineEdit *giveText;
    QPushButton *buttonBestMatching;
    QLineEdit *printBestMatch;
    QLineEdit *searchinText;
    QLabel *label_2;

    void setupUi(QWidget *test3_searchEngineClass)
    {
        if (test3_searchEngineClass->objectName().isEmpty())
            test3_searchEngineClass->setObjectName("test3_searchEngineClass");
        test3_searchEngineClass->resize(600, 400);
        listAllDocs = new QListWidget(test3_searchEngineClass);
        listAllDocs->setObjectName("listAllDocs");
        listAllDocs->setGeometry(QRect(21, 33, 331, 192));
        label = new QLabel(test3_searchEngineClass);
        label->setObjectName("label");
        label->setGeometry(QRect(21, 11, 42, 16));
        giveText = new QLineEdit(test3_searchEngineClass);
        giveText->setObjectName("giveText");
        giveText->setGeometry(QRect(21, 301, 108, 24));
        buttonBestMatching = new QPushButton(test3_searchEngineClass);
        buttonBestMatching->setObjectName("buttonBestMatching");
        buttonBestMatching->setGeometry(QRect(21, 271, 122, 24));
        printBestMatch = new QLineEdit(test3_searchEngineClass);
        printBestMatch->setObjectName("printBestMatch");
        printBestMatch->setGeometry(QRect(21, 331, 331, 24));
        searchinText = new QLineEdit(test3_searchEngineClass);
        searchinText->setObjectName("searchinText");
        searchinText->setGeometry(QRect(380, 280, 161, 24));
        label_2 = new QLabel(test3_searchEngineClass);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(380, 250, 111, 16));

        retranslateUi(test3_searchEngineClass);

        QMetaObject::connectSlotsByName(test3_searchEngineClass);
    } // setupUi

    void retranslateUi(QWidget *test3_searchEngineClass)
    {
        test3_searchEngineClass->setWindowTitle(QCoreApplication::translate("test3_searchEngineClass", "test3_searchEngine", nullptr));
        label->setText(QCoreApplication::translate("test3_searchEngineClass", "All docs", nullptr));
        buttonBestMatching->setText(QCoreApplication::translate("test3_searchEngineClass", "Show best matching", nullptr));
        label_2->setText(QCoreApplication::translate("test3_searchEngineClass", "Search doc", nullptr));
    } // retranslateUi

};

namespace Ui {
    class test3_searchEngineClass: public Ui_test3_searchEngineClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST3_SEARCHENGINE_H
