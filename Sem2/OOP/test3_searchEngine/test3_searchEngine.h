#pragma once

#include <QtWidgets/QWidget>
#include "ui_test3_searchEngine.h"
#include "Service.h"

class test3_searchEngine : public QWidget
{
    Q_OBJECT

public:
    test3_searchEngine(QWidget *parent = nullptr);
    ~test3_searchEngine();

private:
    Ui::test3_searchEngineClass ui;
    Service service;
    void getAllUi();
    void bestMatch();
    void findText();
};
