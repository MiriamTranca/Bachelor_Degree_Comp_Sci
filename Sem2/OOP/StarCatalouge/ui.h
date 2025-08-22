#ifndef UI_H
#define UI_H

#include <QMainWindow>

#include <QTableView>
#include <QCheckBox>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QPainter>
#include "service.h"

class StarModel : public QAbstractTableModel {
    Q_OBJECT

private:
    service* serv;
    std::string astronomerName;
    std::string constellation;
    bool showOnlyConstellation = false;
    std::string searchText;
    std::vector<Star> filteredStars;

    void updateFilteredStars();

public:
    StarModel(service* s, const std::string& astroName, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void setConstellationFilter(bool enabled);
    void setSearchFilter(const std::string& search);
    void refreshData();
};

class astroWindow : public QMainWindow {
    Q_OBJECT

private:
    service* serv;
    std::string astroName;
    QTableView* starsList;
    StarModel* starsModel;
    QCheckBox* checkbox;
    QPushButton* addButton;
    QPushButton* viewButton;
    QLineEdit* searchBox;

    void setupUI();

public:
    astroWindow(const std::string& name, service* s, QWidget* parent = nullptr);
    signals:
        void starAdded();

    private slots:
        void onCheckbox();
    void onAddButton();
    void onViewButton();
    void onSearchTextChanged();

    public slots:
        void addStarOtherWindows();
};

#endif // UI_H
