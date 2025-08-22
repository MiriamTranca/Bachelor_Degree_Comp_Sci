#include "test3_searchEngine.h"

test3_searchEngine::test3_searchEngine(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    connect(ui.buttonBestMatching, &QPushButton::clicked, this, &test3_searchEngine::bestMatch);
    connect(ui.searchinText, &QLineEdit::textChanged, this, &test3_searchEngine::findText);
    getAllUi();
}

test3_searchEngine::~test3_searchEngine()
{}

void test3_searchEngine::getAllUi()
{
    ui.listAllDocs->clear();
    for (const Domain& doc : service.sortAll()) {
        QString textItem = QString::fromStdString(doc.getName() + ", " + doc.getList() + ", " + doc.getContent());
        QListWidgetItem* item = new QListWidgetItem(textItem);
        ui.listAllDocs->addItem(item);
    }

}

void test3_searchEngine::bestMatch()
{
    std::string text = ui.giveText->text().toStdString();
    double best = 0;
    QString bmatch;
    for (const Domain& doc : service.sortAll()) {
        double match = service.similarity(text, doc.getName());
        if (match > best) {
            best = match;
            bmatch = QString::fromStdString(doc.getName() + ", " + doc.getList() + ", " + doc.getContent());
        }
    }
    ui.printBestMatch->setText(bmatch);
}

void test3_searchEngine::findText()
{
    std::string text = ui.searchinText->text().toStdString();

    ui.listAllDocs->clear();
    for (const Domain& doc : service.sortAll()) {
        if (service.findNameOrList(text, doc.getName()) || service.findNameOrList(text, doc.getContent())) {
            QString textItem = QString::fromStdString(doc.getName() + ", " + doc.getList() + ", " + doc.getContent());
            QListWidgetItem* item = new QListWidgetItem(textItem);
            ui.listAllDocs->addItem(item);
        }
    }
}
