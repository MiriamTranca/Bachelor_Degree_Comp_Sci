//
// Created by tranc on 6/23/2025.
//

#include "UI.h"
#include <QStandardItem>
#include <QVBoxLayout>
#include <QInputDialog>

void writerWindow::setupUI() {
    ideas = new QTableView(this);
    ideas->setModel(ideasModel);
    ideas->setEditTriggers(QAbstractItemView::DoubleClicked);
    connect(ideasModel, &QStandardItemModel::dataChanged, this, &writerWindow::onModelChanged);
    QWidget *centralWidget = new QWidget();
    setCentralWidget(centralWidget);
    QVBoxLayout *layout = new QVBoxLayout();
    centralWidget->setLayout(layout);
    layout->addWidget(ideas);

    //add button
    addButton = new QPushButton("Add");
    layout->addWidget(addButton);
    connect(addButton, &QPushButton::clicked, this, &writerWindow::onAddButton);

    //revise button
    for (auto writer: service->getAllWriters()) {
        if (writer.getName()==writerName && writer.getExpertise() == "Senior") {
            reviseButton = new QPushButton("Revise");
            layout->addWidget(reviseButton);
            connect(reviseButton, &QPushButton::clicked, this, &writerWindow::onRevisedButton);
        }
    }
    //develop button
    QPushButton* developButton = new QPushButton("Develop");
    layout->addWidget(developButton);
    connect(developButton, &QPushButton::clicked, this, &writerWindow::onDevelopButton);
    developButton->setEnabled(false);

    connect(ideas, &QTableView::clicked, [this, developButton](const QModelIndex& index){
        int row = index.row();
        if (ideasModel->item(row, 1)->text() == "accepted") {
            developButton->setEnabled(true);
        } else {
            developButton->setEnabled(false);
        }
    });


    ideas->resizeColumnsToContents();
}

writerWindow::writerWindow( string writerName, Service *service,QStandardItemModel* ideasModel, QWidget *parent):writerName(writerName),service(service),ideasModel(ideasModel) {
    setWindowTitle(QString::fromStdString(writerName));
    setupUI();
}

void writerWindow::onAddButton() {
    bool ok;
    QString text = QInputDialog::getText(this, "Add new act", "Give desc,act", QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
        std::string txt = text.toStdString();
        std::string desc,act;
        std::stringstream ss(txt);
        if (std::getline(ss,desc,',')&&std::getline(ss,act)) {
            try {
                service->addNewIdea(desc,act,writerName);
                emit dataChanged();
            } catch (runtime_error& e) {}
        }
    }
}
void writerWindow::onRevisedButton() {
    QModelIndex index = ideas->currentIndex();
    if (!index.isValid()) return;

    int row = index.row();
    std::string desc = ideasModel->item(row, 0)->text().toStdString();

    try {
        service->acceptIdea(desc);
        emit dataChanged();
    } catch (std::exception& e) {

    }
}
void writerWindow::onDevelopButton() {
    QModelIndex index = ideas->currentIndex();
    if (!index.isValid()) return;

    int row = index.row();
    QString desc = ideasModel->item(row, 0)->text();

    bool ok;
    QString developedText = QInputDialog::getMultiLineText(this, "Develop Idea", "Edit and save:", desc, &ok);
    if (ok && !developedText.isEmpty()) {
        service->saveIdea(desc.toStdString(), developedText.toStdString());
    }
}

