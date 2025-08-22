#ifndef UI_H
#define UI_H
#include <QMainWindow>
#include <QStandardItemModel>
#include <QTableView>
#include <QPushButton>
#include <QObject>
#include <QString>
#include <QList>

#include "Service.h"

class ApplicationController;

class writerWindow : public QMainWindow {
    Q_OBJECT
private:
    Service* service;
    std::string writerName;
    QTableView* ideas;
    QStandardItemModel* ideasModel;
    QPushButton* addButton;
    QPushButton* reviseButton;

    void setupUI();

public:
    writerWindow(std::string writerName, Service* service, QStandardItemModel* ideasModel, QWidget *parent = nullptr);

signals:
    void dataChanged();

private slots:
    void onAddButton();
    void onRevisedButton();
    void onDevelopButton();
    void onModelChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight) {
        emit dataChanged();
    }
};

class ApplicationController : public QObject {
    Q_OBJECT
private:
    QStandardItemModel* sharedModel;
    Service* service;
    QList<writerWindow*> windows;
public:
    ApplicationController(Service* service, QObject* parent = nullptr)
        : QObject(parent), service(service) {
        sharedModel = new QStandardItemModel(this);
        sharedModel->setHorizontalHeaderLabels({"Description","Status","Creator","Act"});
        loadIdeas();
    }
    void createWriterWindow(QString writerName) {
        auto* window = new writerWindow(writerName.toStdString(), service, sharedModel);
        windows.append(window);
        window->show();

        connect(window, &writerWindow::dataChanged, this, &ApplicationController::refreshModel);
    }
private slots:
    void refreshModel() {
        loadIdeas();
    }
private:
    void loadIdeas() {
        auto ideasData = service->getSortedIdeas();
        int newRowCount = ideasData.size();
        int currentRowCount = sharedModel->rowCount();

        if (currentRowCount > newRowCount) {
            sharedModel->removeRows(newRowCount, currentRowCount - newRowCount);
        }
        if (newRowCount > currentRowCount) {
            sharedModel->insertRows(currentRowCount, newRowCount - currentRowCount);
        }
        for (size_t row = 0; row < ideasData.size(); ++row) {
            auto idea = ideasData[row];
            auto descItem = sharedModel->item(row, 0);
            if (!descItem) {
                descItem = new QStandardItem();
                sharedModel->setItem(row, 0, descItem);
            }
            auto statItem = sharedModel->item(row, 1);
            if (!statItem) {
                statItem = new QStandardItem();
                sharedModel->setItem(row, 1, statItem);
            }
            auto creatorItem = sharedModel->item(row, 2);
            if (!creatorItem) {
                creatorItem = new QStandardItem();
                sharedModel->setItem(row, 2, creatorItem);
            }
            auto actItem = sharedModel->item(row, 3);
            if (!actItem) {
                actItem = new QStandardItem();
                sharedModel->setItem(row, 3, actItem);
            }
            descItem->setText(QString::fromStdString(idea.getDescription()));
            statItem->setText(QString::fromStdString(idea.getStatus()));
            creatorItem->setText(QString::fromStdString(idea.getCreator()));
            actItem->setText(QString::fromStdString(idea.getAct()));
        }
    }
};

#endif //UI_H



