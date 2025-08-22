//
// Created by tranc on 6/23/2025.
//

#include "UI.h"
#include <QLabel>
#include <QInputDialog>

void WindowDriver::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainlayout = new QVBoxLayout();
    listReports= new QListWidget();

    QWidget *datadriver = new QWidget();
    QVBoxLayout *datalayout = new QVBoxLayout();
    std::vector<Driver> drivers=service->getAllDrivers();
    for (auto driver : drivers) {
        if (driver.getName() == nameDriver) {
            datalayout->addWidget(new QLabel("Latitude: " + QString::fromStdString(to_string(driver.getLat()))));
            datalayout->addWidget(new QLabel("Longitude: "+ QString::fromStdString(to_string(driver.getLon()))));
            datalayout->addWidget(new QLabel("Score: "+ QString::fromStdString(to_string(driver.getScore()))));
        }
    }
    datadriver->setLayout(datalayout);

    mainlayout->addWidget(datadriver);
    mainlayout->addWidget(listReports);

    //add button
    addButton = new QPushButton("Add");
    mainlayout->addWidget(addButton);
    connect(addButton, &QPushButton::clicked, this, &WindowDriver::onAddButton);
    QPushButton *ok = new QPushButton("Validate");
    mainlayout->addWidget(ok);

    //chatcontrol
    chats = new QListWidget();
    mainlayout->addWidget(chats);
    writeChat = new QLineEdit();
    mainlayout->addWidget(writeChat);
    sendButton = new QPushButton("Send");
    mainlayout->addWidget(sendButton);
    connect(sendButton, &QPushButton::clicked,this, &WindowDriver::onWriteChat);

    //validate report

    connect(ok, &QPushButton::clicked, this, &WindowDriver::validateReport);
    centralWidget->setLayout(mainlayout);
}



WindowDriver::WindowDriver(const string &nameDriver, Service* service, QWidget *parent):nameDriver(nameDriver), service(service) {
    setWindowTitle(QString::fromStdString(nameDriver));
    setupUI();
    loadReports();
}

void WindowDriver::loadReports() {
    listReports->clear();
    for (auto report: service->getAllReportsForDriver(nameDriver)) {
        QString text=QString::fromStdString(report.getDesc()+" "+report.getReporter()+" "+to_string(report.getLat())+" "+to_string(report.getLon())+" "+to_string(report.getValid()));
        if (to_string(report.getValid())=="1") {
            QListWidgetItem *item = new QListWidgetItem();
            item->setText(text);
            QFont font;
            font.setBold(true);
            item->setFont(font);
            listReports->addItem(item);
        } else {
            listReports->addItem(text);
        }
    }
}

void WindowDriver::loadChats() {
    chats->clear();
    for (const auto& msg : service->getChatMessages()) {
        chats->addItem(QString::fromStdString(msg));
    }
}

void WindowDriver::onAddButton() {
    bool ok;
    QString text = QInputDialog::getText(this, "Add Report", "descripiton,lat,lon", QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
            std::string txt = text.toStdString();
            std::stringstream ss(txt);
            std::string desc,latStr,lonStr;
            if (std::getline(ss, desc, ',')&&std::getline(ss, latStr, ',')&&std::getline(ss, lonStr,',')) {
                int lat=std::stoi(latStr);
                int lon=std::stoi(lonStr);
                try {
                    service->addReport(lat,lon,desc,nameDriver);
                    emit Changed();
                } catch(runtime_error& e) {}
            }
    }
    loadReports();
}



void WindowDriver::onWriteChat(){
    QString text = writeChat->text();
    QString driver = QString::fromStdString(nameDriver);
    string fullMessage = driver.toStdString()+": "+text.toStdString();
    service->addChatMessage(fullMessage);
    emit Changed1();
    loadChats();
}

void WindowDriver::validateReport() {
    QListWidgetItem *item = listReports->currentItem();
    service->validateReport(item, nameDriver);
    emit Changed();
    loadReports();
}

