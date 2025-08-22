#include "ui.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QInputDialog>

StarModel::StarModel(service* s, const std::string& astroName, QObject* parent)
    : QAbstractTableModel(parent), serv(s), astronomerName(astroName) {
    for (auto& astro : serv->getAllAstro()) {
        if (astro.getName() == astronomerName) {
            constellation = astro.getCons();
            break;
        }
    }
    updateFilteredStars();
}

int StarModel::rowCount(const QModelIndex&) const {
    return static_cast<int>(filteredStars.size());
}

int StarModel::columnCount(const QModelIndex&) const {
    return 4; // Name, RA, Dec, Diameter
}

QVariant StarModel::data(const QModelIndex& index, int role) const {
    if (role != Qt::DisplayRole) return {};

    Star s = filteredStars[index.row()];
    switch (index.column()) {
        case 0: return QString::fromStdString(s.getName());
        case 1: return s.getRa();
        case 2: return s.getDec();
        case 3: return s.getDiam();
        default: return {};
    }
}

QVariant StarModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal) return {};
    switch (section) {
        case 0: return "Name";
        case 1: return "RA";
        case 2: return "Dec";
        case 3: return "Diameter";
        default: return {};
    }
}

void StarModel::setConstellationFilter(bool enabled) {
    showOnlyConstellation = enabled;
    updateFilteredStars();
}

void StarModel::setSearchFilter(const std::string& search) {
    searchText = search;
    updateFilteredStars();
}

void StarModel::refreshData() {
    updateFilteredStars();
}

void StarModel::updateFilteredStars() {
    beginResetModel();
    filteredStars.clear();

    for (auto& s : serv->getAllStars()) {
        if (showOnlyConstellation && s.getCons() != constellation) continue;

        std::string nameLower = s.getName();
        std::transform(nameLower.begin(), nameLower.end(), nameLower.begin(), ::tolower);
        std::string searchLower = searchText;
        std::transform(searchLower.begin(), searchLower.end(), searchLower.begin(), ::tolower);

        if (!searchLower.empty() && nameLower.find(searchLower) == std::string::npos) continue;

        filteredStars.push_back(s);
    }
    endResetModel();
}

astroWindow::astroWindow(const std::string& name, service* s, QWidget* parent)
    : astroName(name), serv(s), QMainWindow(parent) {
    setWindowTitle(QString::fromStdString(name));
    setupUI();
}

void astroWindow::setupUI() {
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* layout = new QVBoxLayout();
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    starsList = new QTableView();
    starsModel = new StarModel(serv, astroName, this);
    starsList->setModel(starsModel);

    checkbox = new QCheckBox("Show stars in cons");
    connect(checkbox, &QCheckBox::clicked, this, &astroWindow::onCheckbox);

    addButton = new QPushButton("Add star");
    connect(addButton, &QPushButton::clicked, this, &astroWindow::onAddButton);

    viewButton = new QPushButton("View");
    connect(viewButton, &QPushButton::clicked, this, &astroWindow::onViewButton);

    searchBox = new QLineEdit();
    searchBox->setPlaceholderText("Type star name to search...");
    connect(searchBox, &QLineEdit::textChanged, this, &astroWindow::onSearchTextChanged);

    buttonLayout->addWidget(searchBox);
    buttonLayout->addWidget(viewButton);
    buttonLayout->addWidget(checkbox);
    buttonLayout->addWidget(addButton);

    layout->addLayout(buttonLayout);
    layout->addWidget(starsList);
    centralWidget->setLayout(layout);
}

void astroWindow::onCheckbox() {
    starsModel->setConstellationFilter(checkbox->isChecked());
}

void astroWindow::onAddButton() {
    bool ok;
    QString text = QInputDialog::getText(this, "Add star", "Star (name ra dec diam):", QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
        try {
            serv->addStar(text.toStdString(), astroName);
            starsModel->refreshData();
            emit starAdded();
        } catch (const std::exception&) {

        }
    }
}

void astroWindow::onSearchTextChanged() {
    starsModel->setSearchFilter(searchBox->text().toStdString());
}

void astroWindow::onViewButton() {

}

void astroWindow::addStarOtherWindows() {
    starsModel->refreshData();
}
