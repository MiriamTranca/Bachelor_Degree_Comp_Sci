//
// Created by tranc on 6/23/2025.
//

#ifndef UI_H
#define UI_H
#include <qtmetamacros.h>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QPushButton>
#include "Service.h"
using namespace std;

class WindowDriver : public QMainWindow {
    Q_OBJECT
    private:
        string nameDriver;
        Service *service;
        QListWidget *listReports;
        QListWidget* chats;
        QLineEdit *writeChat;
        QPushButton *sendButton;
        QPushButton* addButton;
        void setupUI();
    public:
        WindowDriver(const string& nameDriver, Service* service, QWidget *parent = nullptr);
        void loadReports();
        void loadChats();
        signals:
        void Changed();
        void Changed1();
    private slots:
        void onAddButton();
        void onWriteChat();
        void validateReport();
};




#endif //UI_H
